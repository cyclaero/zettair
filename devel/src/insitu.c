/* insitu.c implements regular and insitu merging as specified by the
 * insitu.h interface.
 *
 * In situ merging is a typical piece of Alistair (Moffat) cleverness (though
 * it should be noted that in-situ merging of constant-size items was explored
 * previously to Moffat and Bell (1995)).
 * During merging, multiple sources are read, and merged into a single output.
 * Each source is read in pages of a particular size, b.
 * In regular merging, each source comes (notionally) from a separate file, 
 * and the output is written to a separate file.
 * The trick to in situ merging is to recognise that, once a portion of 
 * an input has been read, it can be used to hold the output from the merge.
 * This introduces two complications.  First, input and
 * output buffer sizes must be fixed, and match, so that output blocks
 * can fit into the space left by input blocks.
 * Second, the output is written in a permuted manner.  This can be
 * corrected by having a post-processing permutation stage fix up the ordering.
 * This requires that the permuted order of output blocks be stored in 
 * main memory.
 *
 * The in situ merge is performed as a single, multi-way merge that
 * runs once all runs have been committed to disk.
 * However, there are limitations that prevent us from doing this when
 * there are a great many different runs.
 * The primary constraint that we wish to satisfy is to perform the
 * final merge in a limited amount of main memory.
 * As such, we require that the number of runs be (possibly) reduced
 * so that each run can be allocated a buffer at least the size of one
 * disk page (as specified by the storage structure).
 * To ensure this, intermediate merges may have to be performed.
 * In order to efficient merging, we wish to keep the runs as uniform
 * in size as possible.  Therefore, we (possibly) perform multiple 
 * intermediate merges, reducing the number of runs to, but not below,
 * the maximum number that can be handled by the final merge.
 * Each run will be merged a maximum of twice (one intermediate and
 * one final) and a minimum of once.
 *
 * written nml 2006-09-20
 *
 */

/* TODO: 
         - test true insitu
         - remove (or refactor) debugging junk
 */

#include "firstinclude.h"

#include "insitu.h"

#include "binsearch.h"
#include "bit.h"
#include "btbulk.h"
#include "def.h"
#include "fdset.h"
#include "heap.h"
#include "mem.h"
#include "rbtree.h"
#include "storagep.h"
#include "str.h"
#include "vec.h"
#include "vocab.h"
#include "zstdint.h"
#include "zvalgrind.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define INSITU_END 1

/* internal representation of a run */
struct run {
    unsigned int id;                   /* numeric identifier of this run */
    unsigned int padding;              /* number of bytes of padding in run */
    uintmax_t content;                 /* number of bytes of content in run */
};

/* struct represents an 'external' run object, which outside code interacts 
 * with */
struct insitu_run {
    struct insitu *situ;               /* the insitu merge object */
    struct run *run;                   /* pointer to internal run rep */
    char *buf;
    unsigned int bufsize;
    struct vec v;
    int committed;
};

/* struct to represent the location of a block or blocks of bytes in
 * the temporary files */
struct loc {
    unsigned int runid;                /* id of the run that these bytes 
                                        * belong to */
    uintmax_t logical;                 /* logical position in the run */

    struct {                           /* physical file and offset */
        unsigned int file;
        unsigned long int offset;
    } physical;

    unsigned int bytes;                /* number of bytes at this location 
                                        * (including padding) */
};

struct insitu {
    struct fdset *fds;                 /* fdset for file access */
    unsigned int tmp_type;             /* type of temporary files */
    unsigned int idx_type;             /* type of index files */
    unsigned int vocab_type;           /* type of vocabulary files */
    struct storagep *storage;          /* storage parameters */
    unsigned long int max_filesize;    /* (rounded) maximum file size */
    unsigned int memory;               /* approximate amount of memory to use*/
    int insitu;                        /* whether we are merging in situ */
    int stress;                        /* whether to perform merging and 
                                        * permutation with minimal memory */
    unsigned int b;                    /* current blocksize */
    unsigned int id;                   /* next id */

    unsigned int file;                 /* file number for next run */
    unsigned long int offset;          /* offset for next run */

    struct rbtree *locs;               /* mapping of disk locations to logical 
                                        * run positions */
    struct rbtree *freelocs;           /* free locations within temporary 
                                        * files */

    struct run *run;                   /* array of runs */
    unsigned int run_size;             /* size of run array */
    unsigned int run_capacity;         /* capacity of run array */
};

/* internal function to compare locations by logical location */
static int loc_logical_cmp(const void *vone, const void *vtwo) {
    const struct loc *one = vone,
                     *two = vtwo;

    if (one->runid < two->runid) {
        return -1;
    } else if (one->runid > two->runid) {
        return 1;
    } else if (one->logical < two->logical) {
        return -1;
    } else if (one->logical > two->logical) {
        return 1;
    } else {
        return 0;
    }
}

/* internal function to compare locations by physical location */
static int loc_physical_cmp(const void *vone, const void *vtwo) {
    const struct loc *one = vone,
                     *two = vtwo;

    if (one->physical.file < two->physical.file) {
        return -1;
    } else if (one->physical.file > two->physical.file) {
        return 1;
    } else if (one->physical.offset < two->physical.offset) {
        return -1;
    } else if (one->physical.offset > two->physical.offset) {
        return 1;
    } else {
        return 0;
    }
}

void insitu_print_loc(struct insitu *situ, unsigned int line) {
    struct rbtree_iter *rbi;
    enum rbtree_ret rbret;
    void *key,
         **data;

    rbi = rbtree_iter_new(situ->locs, RBTREE_ITER_INORDER, 0);
    assert(rbi);
    printf("used(%u): ", line);
    while ((rbret = rbtree_iter_ptr_ptr_next(rbi, &key, &data)) == RBTREE_OK) {
        struct loc *loc = key;

        printf("(id %u log %lup ph %u %lup b %up) ", loc->runid, 
          (unsigned long int) loc->logical / situ->b, 
          loc->physical.file, loc->physical.offset / situ->b, 
          loc->bytes / situ->b);
    }

    rbtree_iter_delete(rbi);
    if (rbret != RBTREE_ITER_END) {
        printf("failed!!");
    }
    printf("\n");

    rbi = rbtree_iter_new(situ->freelocs, RBTREE_ITER_INORDER, 0);
    assert(rbi);
    printf("free: ");
    while ((rbret = rbtree_iter_ptr_ptr_next(rbi, &key, &data)) == RBTREE_OK) {
        struct loc *loc = key;

        printf("(ph %u %lup b %up) ", 
          loc->physical.file, loc->physical.offset / situ->b, 
          loc->bytes / situ->b);
    }

    rbtree_iter_delete(rbi);
    if (rbret != RBTREE_ITER_END) {
        printf("failed!!");
    }
    printf("\n");

    return;
}

/* initial capacity of the run array */
#define INIT_RUNS 8

struct insitu *insitu_new(struct fdset *fds, unsigned int tmp_type, 
  unsigned int idx_type, unsigned int vocab_type, struct storagep *storage,
  int insitu, unsigned int memory, int stress) {
    struct insitu *situ;

    if ((situ = malloc(sizeof(*situ)))
      && (situ->locs = rbtree_ptr_new(loc_logical_cmp))
      && (situ->freelocs = rbtree_ptr_new(loc_physical_cmp))
      && (situ->run = malloc(sizeof(*situ->run) * INIT_RUNS))) {
        situ->run_size = 0;
        situ->run_capacity = INIT_RUNS;
        situ->b = 0;
        situ->stress = stress;
        situ->insitu = insitu;
        situ->fds = fds;
        situ->tmp_type = tmp_type;
        situ->idx_type = idx_type;
        situ->vocab_type = vocab_type;
        situ->storage = storage;
        situ->memory = memory;
        situ->id = 0;

        /* note that we will later ensure that max_filesize is an integral
         * number of pages by rounding it to the initial page size */
        situ->max_filesize = situ->storage->max_filesize;

        /* initialise file and offset so that first run will create the first
         * output file */
        situ->file = -1;
        situ->offset = -1;

        if (situ->insitu) {
            situ->tmp_type = situ->idx_type;
        }
    } else if (situ) {
        if (situ->locs) {
            if (situ->freelocs) {
                if (situ->run) {
                    free(situ->run);
                }
                rbtree_delete(situ->freelocs);
            }
            rbtree_delete(situ->locs);
        }
    }

    return situ;
}

static void node_free(void *opaque, void *key, void **data) {
    free(key);
}

void insitu_delete(struct insitu *situ) {
    if (situ->run) {
        free(situ->run);
    }
    rbtree_ptr_ptr_foreach(situ->locs, NULL, node_free);
    rbtree_ptr_ptr_foreach(situ->freelocs, NULL, node_free);
    rbtree_delete(situ->locs);
    rbtree_delete(situ->freelocs);
    free(situ);
    return;
}

static unsigned int page_overhead(struct storagep *storage);

struct insitu_run *insitu_run_new(struct insitu *situ, unsigned int sizehint) {
    struct insitu_run *run;
    unsigned int pagesize = situ->storage->pagesize;

    /* create new record for this run */
    if (situ->run_size >= situ->run_capacity) {
        void *ptr 
          = realloc(situ->run, sizeof(*situ->run) * situ->run_capacity * 2);

        if (ptr) {
            situ->run = ptr;
            situ->run_capacity *= 2;
        } else {
            return NULL;
        }
    }

    if (situ->b == 0) {
        /* first run, use the sizehint to choose an appropriate b 
         * value (must be a power of two) */
        situ->b = bit_pow2(bit_log2(sizehint));
        situ->b /= 8;  /* initially, allow around than one eighth of space 
                        * to be wasted.  Note that we should possibly monitor
                        * this, and ensure that the wasted space doesn't rise
                        * (due to variation in run sizes), but we don't
                        * anticipate variation in run sizes, so we won't. */

        if (situ->b < pagesize || situ->stress) {
            situ->b = pagesize;
        }
        situ->max_filesize = (situ->max_filesize / situ->b) * situ->b;
        printf("sizehint %u, initial pagesize %u\n", sizehint, situ->b);
    } else {
        /* fiddle b parameter */
        while (situ->b > pagesize 
          && situ->memory / (situ->run_size + 1) 
            < situ->b + page_overhead(situ->storage)) {

            /* must reduce b (by halving, so that all previous runs remain
             * properly aligned) */
            situ->b /= 2;
            printf("pagesize reduced to %u\n", situ->b);
        }
        assert(situ->b >= pagesize);
    }

    /* allocate run object, with one page of memory */
    if ((run = malloc(sizeof(*run) + situ->b))) {
        run->v.pos = run->buf = (void *) &run[1];
        run->bufsize = situ->b;
        run->run = &situ->run[situ->run_size];
        run->situ = situ;
        run->v.end = run->v.pos + run->bufsize;
        run->committed = 0;

        situ->run[situ->run_size].id = situ->id;
        situ->run[situ->run_size].content = 0;
        situ->run[situ->run_size].padding = 0;
        situ->run_size++;
        situ->id++;
        return run;
    } else {
        return NULL;
    }
}

enum insitu_ret insitu_run_empty(struct insitu_run *run) {
    struct insitu *situ = run->situ;
    struct loc loc,
               *locptr;
    void **data,
         *found;
    int fd;
    enum rbtree_ret rbret;
    unsigned int written;

    assert(!VEC_LEN(&run->v));
    assert(!run->committed);

    /* see if we're at the correct file */
    if (situ->offset >= situ->max_filesize) {
        /* we're not, so create a new one */
        assert(situ->offset == situ->max_filesize 
          || (situ->file == -1 && situ->offset == -1));
        situ->file++;

        if ((fd = fdset_create(situ->fds, situ->tmp_type, situ->file)) >= 0) {

            /* unpin the new fd, we'll repin it below */
            situ->offset = 0;
            fdset_unpin(situ->fds, situ->tmp_type, situ->file, fd);
        } else if (situ->insitu && situ->file == 0) {
            /* just pass, first index file has already been created */
            situ->offset = 0;
        } else {
            assert(!CRASH);
            situ->file--;
            return INSITU_EFILE;
        }
    } else {
        assert(situ->offset + situ->b <= situ->max_filesize);
    }

    /* try to find and extend previous location for this run */
    loc.runid = run->run->id;
    loc.logical = run->run->content;

    if ((rbret 
        = rbtree_ptr_ptr_find_near(run->situ->locs, &loc, &found, &data)) 
          == RBTREE_OK
      && (locptr = found)
      && locptr->runid == loc.runid
      && locptr->logical + locptr->bytes == loc.logical
      && locptr->physical.file == situ->file
      && locptr->physical.offset + locptr->bytes == situ->offset) {
        /* found existing record which we can extend */
        locptr->bytes += run->bufsize;
    } else if ((rbret == RBTREE_OK || rbret == RBTREE_EEXIST) 
      && (locptr = malloc(sizeof(*locptr)))) {
        /* allocated new record to insert into locations */
        locptr->runid = loc.runid;
        locptr->logical = loc.logical;
        locptr->physical.file = situ->file;
        locptr->physical.offset = situ->offset;
        locptr->bytes = run->bufsize;

        if ((rbret = rbtree_ptr_ptr_insert(run->situ->locs, locptr, locptr))
          == RBTREE_OK) {
            /* insert succeeded, do nothing */
        } else {
            assert(!CRASH);
            assert(rbret == RBTREE_ENOMEM);
            free(locptr);
            return INSITU_ENOMEM;
        }
    } else {
        assert(!CRASH);
        assert(rbret == RBTREE_OK || rbret == RBTREE_EEXIST);
        return INSITU_ENOMEM;
    }

    /* pin the correct fd, and write the output to file */
    VALGRIND_CHECK_READABLE(run->buf, run->bufsize);
    if ((fd = fdset_pin(situ->fds, situ->tmp_type, situ->file, situ->offset, 
        SEEK_SET)) >= 0
      && (written = write(fd, run->buf, run->bufsize)) == run->bufsize) {
        /* succeeded, remove space from merge */
        assert(situ->offset <= situ->max_filesize);
        assert((situ->offset / situ->storage->pagesize) 
          * situ->storage->pagesize == situ->offset);
        situ->offset += run->bufsize;
        assert(situ->offset <= situ->max_filesize);
        assert((situ->offset / situ->storage->pagesize) 
          * situ->storage->pagesize == situ->offset);
        fdset_unpin(situ->fds, situ->tmp_type, situ->file, fd);
        run->v.pos = run->buf;
        run->v.end = run->buf + run->bufsize;
        run->run->content += run->bufsize;
        VALGRIND_MAKE_WRITABLE(run->buf, run->bufsize);
        return INSITU_OK;
    } else {
        if (fd >= 0) {
            assert(!CRASH);
            fdset_unpin(situ->fds, situ->tmp_type, situ->file, fd);
            return INSITU_EIO;
        } else {
            assert(!CRASH);
            return INSITU_EFILE;
        }
    }
}

struct vec *insitu_run_buffer(struct insitu_run *run) {
    return &run->v;
}

void *insitu_run_buffer_start(struct insitu_run *run) {
    return run->buf;
}

enum insitu_ret insitu_run_commit(struct insitu_run *run) {
    enum insitu_ret iret;
    unsigned int padding = VEC_LEN(&run->v);

    assert(!run->committed);

    if (run->v.pos > run->buf) {
        /* write out last block, padding it with zeros */
        memset(run->v.pos, 0, padding);
        run->v.pos = run->v.end;  /* run_empty asserts !vec_len(&run->v) */

        if ((iret = insitu_run_empty(run)) == INSITU_OK) {
            /* write succeeded, adjust content and padding values */
            run->run->content -= padding;
            run->run->padding += padding;
            printf("run %u, %llu content, %u padding\n", run->run->id, 
              run->run->content, run->run->padding);
        } else {
            assert(!CRASH);
            return iret;
        }
    }

    run->committed = 1;
    return INSITU_OK;
}

void insitu_run_delete(struct insitu_run *run) {
    free(run);
    return;
}

struct runhead {
    struct run *run;                
    unsigned int pages;              /* number of pages of data */
    unsigned int lastpage;           /* number of bytes on last page of data */
    struct loc *inloc;               /* input location record */
    uintmax_t logical;               /* logical position in input run 
                                      * (after current inloc) */

    char *term;                      /* current term */
    unsigned int termlen;            /* current term length */
    struct {
        unsigned int docs;           /* documents for current entry */
        unsigned int occurs;         /* occurances for current entry */
        unsigned int last;           /* last document id for current entry */
        unsigned int size;           /* number of bytes for current entry */
        unsigned long int first;     /* first docno in entry, if applicable */
    } entry;

    unsigned int entries_read;       /* number of entries read through this 
                                      * structure (just used for debugging) */
    unsigned int pages_read;         /* number of pages read through this 
                                      * structure (just used for debugging) */

    char *buf;                       /* input buffer */
    char *pos;                       /* position in input buffer */
    char *end;                       /* end of input buffer */
    unsigned int bufsize;            /* size of input buffer */
};

struct output {
    unsigned int runid;

    /* logical file and offset in the current entry (basically just 
     * a counter) */
    struct {
        unsigned int file;
        unsigned int offset;
    } logical;

    struct {
        unsigned int file;           /* current file to write to */
        unsigned int offset;         /* current offset to write to */
        unsigned int capacity;       /* capacity remaining at this location */
    } physical;

    char *buf;
    char *pos;
    char *end;
    unsigned int bufsize;

    /* array of the last offset in each logical file prior to the current one */
    unsigned long int *last_offsets;  
};

/* internal function to return the maximum overhead per page for memory used 
 * in merging */
static unsigned int page_overhead(struct storagep *storage) {
    unsigned int structover = sizeof(struct runhead) + storage->max_termlen 
      + 1 + 2; /* + 1 for \0 termination, + 2 bytes for redzones */
    assert(sizeof(struct runhead) > sizeof(struct output));

    /* round up to nearest alignment boundary */
    structover = ((structover + mem_align_max() - 1) / mem_align_max()) 
      * mem_align_max();
    return structover;
}

/* internal function to empty the output buffer */
static enum insitu_ret output_flush(struct insitu *situ, struct output *output, 
  int intermediate, int insitu) {
    struct fdset *fds = situ->fds;
    int fd;
    unsigned int file,
                 type,
                 bytes = 0,
                 written;
    unsigned long int offset;
    enum rbtree_ret rbret;

    /* all bufferloads should be full (we truncate later) */
    assert(output->pos - output->buf == output->bufsize);

    /* loop, so that we can grab space in small pieces for insitu and 
     * intermediate merges */
    VALGRIND_CHECK_READABLE(output->buf, output->pos - output->buf);
    do {
        unsigned int transfer = (output->pos - output->buf) - bytes;

        /* grab output space.  If this an in situ merge (intermediate or final),
         * grab output space from free locations.  If not, and this is an 
         * intermediate merge, grab it from the location indicated by situ 
         * position.  If this is a final, regular merge, just use logical 
         * output position. */
        if (insitu) {
            struct loc loc,
                       *found;
            void *key,
                 **data,
                 *rdata;

            type = situ->tmp_type;

            /* search for a free location near the current logical output
             * position */
            loc.physical.file = output->logical.file;
            loc.physical.offset = output->logical.offset;
            if ((((rbret = rbtree_ptr_ptr_find_near(situ->freelocs, &loc, 
                    &key, &data)) == RBTREE_OK)
                && (found = key))
              /* couldn't find one before the current logical output position, 
               * just grab anything from the list of free locations */
              || ((loc.physical.file = situ->file), 
                  (loc.physical.offset = situ->offset), 1
                && ((rbret = rbtree_ptr_ptr_find_near(situ->freelocs, &loc, 
                    &key, &data)) == RBTREE_OK)
                && (found = key))) {
                /* found a suitable free location */

                file = found->physical.file;
                offset = found->physical.offset;
                if (transfer >= found->bytes) {
                    transfer = found->bytes;

                    /* remove the free location, as we consume it */
                    rbret 
                      = rbtree_ptr_ptr_remove(situ->freelocs, found, &rdata);
                    assert(rbret == RBTREE_OK);
                    free(rdata);
                } else {
                    found->bytes -= transfer;
                    found->physical.offset += transfer;
                }
                printf("id %u produced %u %lup %up\n", output->runid,
                  file, offset / situ->b, transfer / situ->b);
                insitu_print_loc(situ, __LINE__);
            } else {
                /* no free space available.  Ideally, this means that the merge
                 * has expanded the output by quite a bit, and the output is
                 * proceeding the input.  Since the current merge doesn't do
                 * this, we shouldn't get here (probably a bug), but this 
                 * situation is simply handled by using additional free space, 
                 * pointed to by the situ cursor */
                assert("shouldn't get here");
                file = situ->file;
                offset = situ->offset;

                /* output buffer crosses output files, write only a part */
                if (transfer > situ->max_filesize - offset) {
                    transfer = situ->max_filesize - offset;
                }

                /* adjust free space cursor */
                situ->offset += transfer;
                assert(situ->offset <= situ->max_filesize);
                assert((situ->offset / situ->storage->pagesize) 
                  * situ->storage->pagesize == situ->offset);
            }

            /* insert record into locs describing our use of this space */
            if ((found = malloc(sizeof(*found)))
              && (found->runid = output->runid, 
                found->logical = output->logical.offset 
                  + situ->max_filesize * (uintmax_t) output->logical.file, 
                found->physical.file = file, found->physical.offset = offset, 
                found->bytes = transfer)
              && (rbret = rbtree_ptr_ptr_insert(situ->locs, found, found)) 
                == RBTREE_OK) {
                
                /* success, do nothing */
            } else {
                assert(!found || rbret == RBTREE_ENOMEM);
                if (found) {
                    free(found);
                }
                return INSITU_ENOMEM;
            }
        } else {
            assert(!intermediate);
            type = situ->idx_type;
            file = output->logical.file;
            offset = output->logical.offset;

            /* shouldn't have trouble fitting this into the current space, as we
             * check prior to stuffing things into the buffer */
            assert(transfer <= situ->max_filesize - offset);

            /* create new file, if necessary (first file is created for us) */
            if (!offset && file) {
                if ((fd = fdset_create(situ->fds, type, file)) >= 0) {
                    fdset_unpin(situ->fds, type, file, fd);
                } else {
                    assert(!CRASH);
                    return INSITU_EFILE;
                }
            }
        }

        if (((fd = fdset_pin(fds, type, file, offset, SEEK_SET)) >= 0)
          && (written = write(fd, output->buf + bytes, transfer)) == written) {
            /* adjust logical output file and offset */
            while (transfer > situ->max_filesize - output->logical.offset) {
                transfer -= situ->max_filesize - output->logical.offset;
                output->logical.file++;
                output->logical.offset = 0;
            }
            output->logical.offset += transfer;
            output->pos = output->buf;
            fdset_unpin(fds, type, file, fd);
            bytes += transfer;
        } else {
            if (fd >= 0) {
                assert(!CRASH);
                fdset_unpin(fds, type, file, fd);
                return INSITU_EIO;
            } else {
                assert(!CRASH);
                return INSITU_EFILE;
            }
        }
    } while (bytes < output->pos - output->buf);

    return INSITU_OK;
}

static enum insitu_ret add_free_loc(struct insitu *situ, unsigned int file, 
  unsigned long int offset, unsigned int bytes) {
    struct loc loc,
               *found;
    void *key, 
         **data;
    enum rbtree_ret rbret;

    /* XXX: coalesce records? */

    loc.physical.file = file;
    loc.physical.offset = offset;
    if (((rbret = rbtree_ptr_ptr_find_near(situ->freelocs, &loc, &key, &data))
        == RBTREE_OK) 
      && (found = key)
      && (found->physical.file == file)
      && (found->physical.offset + found->bytes == offset)) {
        /* found correct record, condense them */
        found->bytes += bytes;
        return INSITU_OK;
    } else if ((rbret == RBTREE_OK || rbret == RBTREE_EEXIST) 
      && (found = malloc(sizeof(*found)))) {
        /* create new record */
        found->physical.file = file;
        found->physical.offset = offset;
        found->bytes = bytes;

        if ((rbret = rbtree_ptr_ptr_insert(situ->freelocs, found, found)) 
          == RBTREE_OK) {
            return INSITU_OK;
        } else {
            assert(!CRASH);
            assert(rbret == RBTREE_ENOMEM);
            return INSITU_ENOMEM;
        }
    } else {
        assert(!CRASH);
        assert(rbret == RBTREE_OK || rbret == RBTREE_EEXIST);
        return INSITU_ENOMEM;
    }
}

/* internal function to fill an input buffer */
static enum insitu_ret input_fill(struct insitu *situ, struct runhead *input) {
    struct loc loc,
               *found;
    void *key,
         **data,
         *rdata;
    int fd;
    enum rbtree_ret rbret;
    unsigned int wanted;
    enum insitu_ret iret;

    assert(input->pos == input->end);

    if (!input->inloc || input->inloc->bytes == 0) {
        if (input->inloc) {
            assert(input->inloc->bytes == 0);
            printf("freeing id %u log %llup\n", input->inloc->runid, 
              input->inloc->logical / situ->b);
            free(input->inloc);
            input->inloc = NULL;
        }

        /* find next segment */
        printf("searching for id %u log %llup\n", input->run->id, 
          input->logical / situ->b);
        insitu_print_loc(situ, __LINE__);
        loc.runid = input->run->id;
        loc.logical = input->logical;
        found = NULL;
        if (((rbret = rbtree_ptr_ptr_find_near(situ->locs, &loc, &key, &data))
            == RBTREE_OK) 
          && (found = key, found->runid == loc.runid)
          && found->logical == input->logical) {
            /* found correct record */
            input->inloc = found;
            input->logical += found->bytes;
            printf("id %u grabbed %u %lup %up\n", input->run->id, 
              input->inloc->physical.file, 
              input->inloc->physical.offset / situ->b, 
              input->inloc->bytes / situ->b);

            /* remove this record from the list of used locations */
            rbret = rbtree_ptr_ptr_remove(situ->locs, input->inloc, &rdata);
            assert(rbret == RBTREE_OK);
        } else {
            if (found) {
                printf("found id %u log %llup\n", found->runid, 
                  found->logical / situ->b);
            }
            if ((rbret == RBTREE_OK || rbret == RBTREE_EEXIST)
              && (input->pages == 0)) {
                return INSITU_END;
            } else {
                assert("can't get here" && 0);
                return INSITU_EINVAL;
            }
        }
    }
    assert(input->inloc->bytes >= situ->b);
    assert((input->inloc->bytes / situ->b) * situ->b == input->inloc->bytes);

    /* read from disk */
    iret = INSITU_OK;
    if (((fd = fdset_pin(situ->fds, situ->tmp_type, 
          input->inloc->physical.file, input->inloc->physical.offset, SEEK_SET))
        >= 0)
      && (wanted = input->inloc->bytes > input->bufsize 
        ? input->bufsize : input->inloc->bytes)
      && printf("read from %u (id %u) at '%.*s', %lu (%lup), %u pages\n", 
          input->inloc->physical.file, input->run->id, input->termlen, 
          input->term, input->inloc->physical.offset, 
          input->inloc->physical.offset / situ->b, wanted / situ->b)
      && read(fd, input->buf, wanted) == wanted
      && (iret = add_free_loc(situ, input->inloc->physical.file, 
          input->inloc->physical.offset, wanted)) == INSITU_OK) {

        printf("id %u consumed %u %lup %up\n", input->run->id, 
          input->inloc->physical.file, 
          input->inloc->physical.offset / situ->b, 
          wanted / situ->b);
        fdset_unpin(situ->fds, situ->tmp_type, input->inloc->physical.file, fd);
        input->pages_read += wanted / situ->b;

        assert(wanted);
        input->inloc->bytes -= wanted;
        input->inloc->physical.offset += wanted;
        input->inloc->logical += wanted;
        input->pos = input->buf;
        input->end = input->buf + wanted;
        input->pages -= wanted / situ->b;
        assert(input->pos < input->end);
        insitu_print_loc(situ, __LINE__);

        /* adjust last page to remove padding */
        if (input->pages == 0) {
            input->end -= situ->b - input->lastpage;
            input->lastpage = 0;
        }
        return INSITU_OK;
    } else {
        if (fd >= 0) {
            fdset_unpin(situ->fds, situ->tmp_type, 
              input->inloc->physical.file, fd);
            if (iret == INSITU_OK) {
                assert(!CRASH);
                return INSITU_EIO;
            } else {
                return iret;
            }
        } else {
            assert(!CRASH);
            return INSITU_EFILE;
        }
    }
}

static enum insitu_ret read_input(struct insitu *situ, struct runhead *input) {
    struct vec v;
#define READ_INTS 5
    unsigned long int tmparr[READ_INTS];
    unsigned int i;
    enum insitu_ret iret;

    /* read the header series of ints and a string from the input.  
     * Use of temporary space is a bit hacky, but the operations are very 
     * repetitive otherwise */

    v.pos = input->pos;
    v.end = input->end;

    for (i = 0; i < READ_INTS; i++) {
        /* read term length */
        if (vec_vbyte_read(&v, &tmparr[i]) == 0) {
            char buf[VEC_VBYTE_MAX];
            unsigned int before = v.end - v.pos,
                         len;

            /* copy first part of vbyte into buffer */
            input->pos = v.pos;
            input->end = v.end;
            memcpy(buf, input->pos, before);
            input->pos += before;
            if ((iret = input_fill(situ, input)) == INSITU_OK) {
                /* copy last part of vbyte into buffer */
                v.pos = buf;
                if (input->end - input->pos > VEC_VBYTE_MAX - before) {
                    memcpy(buf + before, input->pos, VEC_VBYTE_MAX - before);
                    v.end = buf + VEC_VBYTE_MAX;
                } else {
                    memcpy(buf + before, input->pos, input->end - input->pos);
                    v.end = (buf + before) + (input->end - input->pos);
                }
                len = vec_vbyte_read(&v, &tmparr[i]);
                assert(len > before);
                input->pos += len - before;
                v.pos = input->pos;
                v.end = input->end;
            } else {
                /* shouldn't end unless it's at the start */
                if ((before > 0 || i != 0) && iret == INSITU_END) {
                    assert("shouldn't get here" && 0);
                    return INSITU_EINVAL;
                } else {
                    return iret;
                }
            }
        }

        if (i == 0) {
            unsigned int bytes = 0;
            assert(tmparr[i] > 0 && tmparr[i] <= situ->storage->max_termlen);

            do {
                unsigned int transfer = tmparr[i] - bytes;

                if (!VEC_LEN(&v)) {
                    /* refill input buffer */
                    input->pos = v.pos;
                    if ((iret = input_fill(situ, input)) == INSITU_OK) {
                        v.pos = input->pos;
                        v.end = input->end;
                    } else {
                        if (iret == INSITU_END) {
                            assert("shouldn't get here" && 0);
                            return INSITU_EINVAL;
                        } else {
                            assert(!CRASH);
                            return iret;
                        }
                    }
                }

                if (transfer > VEC_LEN(&v)) {
                    transfer = VEC_LEN(&v);
                }
                vec_byte_read(&v, input->term + bytes, transfer);
                bytes += transfer;
            } while (bytes < tmparr[i]);
        }
    }

    input->pos = v.pos;
    input->end = v.end;

    i = 0;
    VALGRIND_CHECK_READABLE(tmparr, sizeof(tmparr));
    input->termlen = tmparr[i++];
    input->term[input->termlen] = '\0';
    input->entry.docs = tmparr[i++];
    input->entry.occurs = tmparr[i++];
    input->entry.last = tmparr[i++];
    input->entry.size = tmparr[i++];
    assert(i == READ_INTS);
#undef READ_INTS

    for (i = 0; i < input->termlen; i++) {
        assert(!iscntrl(input->term[i]));
    }

    input->entries_read++;

    return INSITU_OK;
}

/* trim end padding pages off of a run, placing them on the empty location 
 * list.  Note that this can only be (definitively) used once final merging 
 * has begun, and the final b value is set */
static enum insitu_ret insitu_trim(struct insitu *situ, struct run *run) {
    enum rbtree_ret rbret;
    struct loc loc;

    /* free pure padding pages at the end of the run */
    loc.runid = run->id;
    loc.logical = ((run->content + situ->b - 1) / situ->b) * situ->b;
    while (run->padding > situ->b) {
        struct loc *newloc,
                   *found;
        void *key,
             **data,
             *rdata;

        printf("pretrim\n");
        insitu_print_loc(situ, __LINE__);

        /* find record containing padding pages */
        if ((rbret = rbtree_ptr_ptr_find_near(situ->locs, &loc, &key, &data)) 
          == RBTREE_OK) {
            found = key;
            assert(found->runid == loc.runid);
            assert(found->logical <= loc.logical);
        } else {
            assert("can't get here" && 0);
            return INSITU_EINVAL;
        }

        if (found->logical < loc.logical) {
            /* record contains data pages too, split it */
            if ((newloc = malloc(sizeof(*newloc)))) {
                unsigned int diff = (loc.logical - found->logical);

                newloc->physical.file = found->physical.file;
                newloc->bytes = found->bytes - diff;
                newloc->physical.offset = found->physical.offset + diff;

                /* insert into free records */
                if ((rbret 
                    = rbtree_ptr_ptr_insert(situ->freelocs, newloc, newloc)) 
                  == RBTREE_OK) {

                    /* adjust existing record */
                    found->bytes = diff;
                } else {
                    assert(!CRASH);
                    assert(rbret == RBTREE_ENOMEM);
                    return INSITU_ENOMEM;
                }
            } else {
                assert(!CRASH);
                return INSITU_ENOMEM;
            }
        } else {
            /* whole record is padding, just free it */
            assert(found->logical == loc.logical);
            if ((rbret = rbtree_ptr_ptr_remove(situ->locs, found, &rdata)) 
                == RBTREE_OK
              && (rbret = rbtree_ptr_ptr_insert(situ->freelocs, found, found)) 
                == RBTREE_OK) {

                newloc = found;
            } else {
                assert(!CRASH);
                assert(rbret == RBTREE_ENOMEM);
                return INSITU_ENOMEM;
            }
        }

        loc.logical += newloc->bytes;
        run->padding -= newloc->bytes;

        printf("trimmed id %u\n", run->id);
        insitu_print_loc(situ, __LINE__);
    }

    return INSITU_OK;
}

/* internal function to initialise a run input */
static enum insitu_ret init_input(struct insitu *situ, struct runhead *input,
  struct run *run, char *termbuf, void *buf, unsigned int pages) {
    enum insitu_ret iret;

    /* initialise members */
    input->run = run;
    input->pages = (input->run->content + situ->b - 1) / situ->b;
    input->lastpage = situ->b 
      - (input->pages * situ->b - input->run->content);
    assert(input->lastpage <= situ->b);
    /* note that lastpage may not be the same as the padding on the run, 
     * because the pagesize may have changed in the mean time */
    input->inloc = NULL;
    input->logical = 0;
    input->term = termbuf;
    input->termlen = 0;
    input->buf = buf;
    input->bufsize = situ->b * pages;
    input->pos = input->end = input->buf + input->bufsize;

    /* read from disk */
    if (((iret = input_fill(situ, input)) == INSITU_OK)
      /* read first entry */
      && ((iret = read_input(situ, input)) == INSITU_OK)) {
        return INSITU_OK;
    } else {
        assert(!CRASH);
        return iret;
    }
}

/* internal function to order runs during merge by term entry */
static int runhead_cmp(const void *vone, const void *vtwo) {
    const struct runhead *one = vone, 
                         *two = vtwo;
    int ret;

    if ((ret = str_nncmp(one->term, one->termlen, two->term, two->termlen)) 
      == 0) {
        if (one->entry.last < two->entry.last) {
            return -1;
        } else {
            assert(one->entry.last > two->entry.last);
            return 1;
        }
    } else {
        return ret;
    } 
}

/* internal function to handle the dirty work of writing out the btree */
static enum insitu_ret vocab_handle(struct insitu *situ, struct btbulk *vocab, 
  struct insitu_stats *stats, enum btbulk_ret btret) {
    int fd;
    unsigned int written;

    switch (btret) {
    case BTBULK_OK: 
        break;

    case BTBULK_WRITE:
        VALGRIND_CHECK_READABLE(vocab->output.write.next_out, 
          vocab->output.write.avail_out);
        if (((fd = fdset_pin(situ->fds, situ->vocab_type, vocab->fileno, 
            vocab->offset, SEEK_SET)) >= 0)
          && (written 
            = write(fd, vocab->output.write.next_out, 
                vocab->output.write.avail_out)) 
              == vocab->output.write.avail_out) {

            vocab->offset += written;
            fdset_unpin(situ->fds, situ->vocab_type, vocab->fileno, fd);
        } else {
            if (fd >= 0) {
                fdset_unpin(situ->fds, situ->vocab_type, 
                  vocab->fileno, fd);
                return INSITU_EIO;
            } else {
                return INSITU_EFILE;
            }
        }
        break;

    case BTBULK_FLUSH: 
        /* create a new vocabulary file */
        if ((fd = fdset_create(situ->fds, situ->vocab_type, vocab->fileno + 1)) 
            >= 0) {

            stats->vocab_files++;
            vocab->fileno++;
            vocab->offset = 0;
            fdset_unpin(situ->fds, situ->vocab_type, vocab->fileno, fd);
        } else {
            return INSITU_EFILE;
        }
        break;

    case BTBULK_ERR:
    default:
        return INSITU_EINVAL;
    }
    return INSITU_OK;
}

/* internal function to finish up bulk-loading a btree */
static enum insitu_ret vocab_finish(struct insitu *situ, 
  struct btbulk *vocab, struct insitu_stats *stats) {
    enum btbulk_ret btret;
    enum insitu_ret iret;

    /* insert buffered entry into the vocab */
    do {
        btret = btbulk_finalise(vocab, 
            &stats->vocab_root_file, &stats->vocab_root_offset);
        switch (btret) {
        case BTBULK_OK: 
        case BTBULK_FINISH: 
            btret = BTBULK_FINISH;
            break;

        default: 
            if ((iret = vocab_handle(situ, vocab, stats, btret)) 
              == INSITU_OK) {
                /* do nothing */
            } else {
                return iret;
            }
            break;
        }
    } while (btret != BTBULK_FINISH);

    return INSITU_OK;
}

/* internal function to insert an entry into the vocabulary */
static enum insitu_ret vocab_insert(struct insitu *situ, 
  struct btbulk *vocab, struct insitu_stats *stats, void *data) {
    enum btbulk_ret btret;
    enum insitu_ret iret;

    /* insert buffered entry into the vocab */
    do {
        btret = btbulk_insert(vocab);
        switch (btret) {
        case BTBULK_OK:
            memcpy(vocab->output.ok.data, data, vocab->datasize);
            break;

        default: 
            if ((iret = vocab_handle(situ, vocab, stats, btret)) 
              == INSITU_OK) {
                /* do nothing */
            } else {
                return iret;
            }
            break;
        }
    } while (btret != BTBULK_OK);

    return INSITU_OK;
}

/* internal function to physically perform a merge.  If vocab is NULL, an
 * intermediate merge is performed. */
static enum insitu_ret merge(struct insitu *situ, struct runhead *input,
  unsigned int inputs, struct output *output, struct btbulk *vocab,
  char *vterm, struct insitu_stats *stats, int insitu) {
    struct fdset *fds = situ->fds;
    struct runhead *end,              /* cursors into input array */
                   *min,
                   *curr;
    unsigned int popped,              /* number of inputs out of heap */
                 i,
                 rem,
                 vtermlen;
    struct vocab_vector vv;           /* unencoded vocab entry */
    struct vec v;                     /* vector into buffered vocab entry */
    char *vbuf = NULL;                /* buffered vocab entry */
    int fd;
    enum insitu_ret iret;
    enum vocab_ret vret;
    unsigned int dterms = 0;
    unsigned int terms_low = 0;
    unsigned int terms_high = 0;
    void *ptr;

    if (vocab) {
        vocab->term = vterm;

        /* allocate vocabulary buffer (half a page, as vocab entries certainly 
         * can't get longer than this and still fit in the btree) */
        if ((vbuf = malloc(situ->storage->pagesize / 2))) {
            v.pos = vbuf;
            v.end = vbuf + situ->storage->pagesize / 2;
        } else {
            assert(!CRASH);
            return INSITU_ENOMEM;
        }
    }

    /* create first vocabulary file */
    if (vocab && (fd = fdset_create(fds, situ->vocab_type, 0)) >= 0) {
        vocab->fileno = 0;
        vocab->offset = 0;
        fdset_unpin(fds, situ->vocab_type, vocab->fileno, fd);
        stats->vocab_files = 1;
    } else if (vocab) {
        assert(!CRASH);
        free(vbuf);
        return INSITU_EFILE;
    } else {
        stats->vocab_files = 0;
        stats->vocab_root_file = 0;
        stats->vocab_root_offset = 0;
    }

    /* form heap of inputs */
    heap_heapify(input, inputs, sizeof(*input), runhead_cmp);
    
    vv.type = VOCAB_VTYPE_DOCWP;

    vterm[0] = '\0';
    vtermlen = 0;
    while (inputs) {
        /* select smallest input */
        end = &input[inputs];
        curr = heap_pop(input, &inputs, sizeof(*input), runhead_cmp);
        popped = 1;
        min = heap_peek(input, inputs, sizeof(*input));

        /* update vocab if term doesn't match */
        if (vocab && vterm[0] 
          && str_nncmp(vterm, vtermlen, curr->term, curr->termlen)) {

            /* insert buffered entry into the vocab */
            vocab->datasize = v.pos - vbuf;
            vocab->termlen = vtermlen;
            if ((iret = vocab_insert(situ, vocab, stats, vbuf)) == INSITU_OK) {
                /* clear vocab buffer */
                v.pos = vbuf;
                vterm[0] = '\0';
                vtermlen = 0;
                dterms++;
            } else {
                assert(iret != INSITU_END);
                assert(!CRASH);
                free(vbuf);
                return iret;
            }
        }

        /* select inputs with the same term */
        while (inputs 
          && curr->termlen == min->termlen 
          && !str_nncmp(curr->term, curr->termlen, min->term, min->termlen)) {
            curr = heap_pop(input, &inputs, sizeof(*input), runhead_cmp);
            popped++;
            min = heap_peek(input, inputs, sizeof(*input));
        }

        /* swap the order of occurrance, to avoid inconvenience of backward
         * iteration.  Note that if the number popped is odd, then the middle
         * element is already in the correct location. */
        for (i = 0; i < popped / 2; i++) {
            unsigned int latter = popped - i - 1;
            struct runhead tmp = curr[i];
            curr[i] = curr[latter];
            curr[latter] = tmp;
        }

        /* they should now be ordered correctly */
        for (i = 1; i < popped; i++) {
            assert(runhead_cmp(&curr[i - 1], &curr[i]) < 0);
        }

        memcpy(vterm, curr->term, curr->termlen);
        vterm[curr->termlen] = '\0';
        vtermlen = curr->termlen;
        min = curr;
        do {
            struct runhead *tmpend = curr;

            vv.header.docwp.docs = 0;
            vv.header.docwp.occurs = 0;
            vv.size = 0;

            /* find out how many of the inputs we can join, and form vocab 
             * entry */
            for (vv.size = 0, tmpend = curr; 
              tmpend < end 
                && curr->entry.size < situ->max_filesize - vv.size
                && curr->entry.occurs < UINT_MAX - vv.header.docwp.occurs; 
              tmpend++) {
                unsigned int docno_len = 0;

                /* XXX: should probably switch on vector type */
                vv.header.docwp.docs += tmpend->entry.docs;
                vv.header.docwp.occurs += tmpend->entry.occurs; 
                vv.header.docwp.last = tmpend->entry.last; 

                /* for all but the first run, copy first vbyte from input to 
                 * output, reencoding it (later, should be conditional on 
                 * vector containing docnos).
                 * This is a little tricky if the first docno vbyte crosses 
                 * input buffer boundaries.  Note that this conditional has a
                 * counterpart below (using curr rather than tmpend) which 
                 * controls output of first docnos, so changes must be 
                 * reflected there. */
                if (tmpend > min) {
                    struct vec tmpv;

                    /* read first docno */
                    tmpv.pos = tmpend->pos;
                    tmpv.end = tmpend->end;
                    if ((docno_len 
                      = vec_vbyte_read(&tmpv, &tmpend->entry.first)) > 0) {
                        tmpend->pos += docno_len;
                    } else {
                        /* docno crosses input boundaries */
                        char buf[VEC_VBYTE_MAX];
                        unsigned int before = tmpend->end - tmpend->pos;

                        memset(buf, 0, sizeof(buf));
                        memcpy(buf, tmpend->pos, before);
                        tmpend->pos += before;
                        if ((iret = input_fill(situ, tmpend)) == INSITU_OK) {
                            tmpv.pos = buf;
                            if (tmpend->end - tmpend->pos 
                              > VEC_VBYTE_MAX - before) {
                                memcpy(buf + before, tmpend->pos, 
                                  VEC_VBYTE_MAX - before);
                                tmpv.end = buf + VEC_VBYTE_MAX;
                            } else {
                                /* yes, this can actually happen (not getting
                                 * VEC_VBYTE_MAX bytes to fill the buffer), 
                                 * if the last vector in the input is really 
                                 * small */
                                assert(tmpend->pos < tmpend->end);
                                memcpy(buf + before, tmpend->pos, 
                                  tmpend->end - tmpend->pos);
                                tmpv.end 
                                  = buf + before + (tmpend->end - tmpend->pos);
                            }
                            docno_len 
                              = vec_vbyte_read(&tmpv, &tmpend->entry.first);
                            assert(docno_len);
                            assert(docno_len > before);
                            tmpend->pos += docno_len - before;
                        } else {
                            assert(iret != INSITU_END);
                            assert(!CRASH);
                            return iret;
                        }
                    }

                    /* reencode first docno and fiddle byte counts */
                    assert(docno_len > 0);
                    tmpend->entry.size -= docno_len;
                    assert(tmpend->entry.first > tmpend[-1].entry.last);
                    tmpend->entry.first -= (tmpend[-1].entry.last + 1);
                    vv.size += vec_vbyte_len(tmpend->entry.first);
                } else {
                    tmpend->entry.first = -1;
                }
                assert((tmpend == min && docno_len == 0) 
                  || (tmpend > min && docno_len > 0));

                vv.size += tmpend->entry.size; 
            }

            /* update stats as we go */
            if (vv.header.docwp.occurs > UINT_MAX - terms_low) {
                terms_high++;
            }
            terms_low += vv.header.docwp.occurs;

            /* place merged vector in output file */
            assert(vv.size < situ->max_filesize);
            if (vocab 
              && output->logical.offset + output->pos - output->buf 
                > situ->max_filesize - vv.size) {

                /* pad output to next page boundary (this will be removed by
                 * later truncation, but it is much easier on the intermediate
                 * code if everything occurs in page-sized chunks) */
                if ((rem = ((output->pos - output->buf) % situ->b))) {
                    memset(output->pos, 0, situ->b - rem);
                    output->pos += situ->b - rem;
                    assert(output->pos <= output->end);
                    assert((output->pos - output->buf) % situ->b == 0);
                } else {
                    /* required for offset adjustment below */
                    rem = situ->b;
                }

                /* flush current output */
                if (((iret = output_flush(situ, output, !vocab, insitu)) 
                    == INSITU_OK)
                  && (ptr = realloc(output->last_offsets, 
                      sizeof(*output->last_offsets) 
                        * (output->logical.file + 1)))) {

                    /* record last position in logical file */
                    output->last_offsets = ptr;
                    output->last_offsets[output->logical.file] 
                      = output->logical.offset - situ->b + rem;
                    assert(output->pos == output->buf);

                    /* start new logical output file */
                    output->logical.file++;
                    output->logical.offset = 0;
                } else {
                    assert(!CRASH);
                    free(vbuf);
                    return iret;
                }
            }
            vv.loc.fileno = output->logical.file;
            vv.loc.offset = output->logical.offset + output->pos - output->buf;

            /* write vector header, if it's an intermediate merge */
            if (!vocab) {
#define INTS 5
                unsigned int tmp[INTS];
                unsigned int len;
                struct vec interv;
                i = 0;
                tmp[i++] = curr->termlen;
                tmp[i++] = vv.header.docwp.docs;
                tmp[i++] = vv.header.docwp.occurs;
                tmp[i++] = vv.header.docwp.last;
                tmp[i++] = vv.size;
                assert(i == INTS);

                interv.pos = output->pos;
                interv.end = output->end;
                for (i = 0; i < INTS; i++) {
                    if (vec_vbyte_write(&interv, tmp[i]) > 0) {
                        /* write succeeded */
                    } else {
                        /* write failed, due to lack of space */
                        struct vec tmpv;
                        char vbuf[VEC_VBYTE_MAX];
                        unsigned int before;

                        /* write number into temporary buffer */
                        tmpv.pos = vbuf;
                        tmpv.end = vbuf + VEC_VBYTE_MAX;
                        len = vec_vbyte_write(&tmpv, tmp[i]);
                        assert(len && len < VEC_VBYTE_MAX 
                          && len > VEC_LEN(&interv));

                        /* copy all that will fit into this buffer */
                        before = VEC_LEN(&interv);
                        vec_byte_write(&interv, vbuf, before);
                        tmpv.end = tmpv.pos;
                        tmpv.pos = vbuf + before;

                        /* empty buffer */
                        output->pos = interv.pos;
                        if ((iret 
                            = output_flush(situ, output, !vocab, insitu)) 
                          == INSITU_OK) {
                            /* write remainder of vbyte */
                            interv.pos = output->pos;
                            interv.end = output->end;
                            vec_byte_write(&interv, tmpv.pos, 
                              VEC_LEN(&tmpv));
                        } else {
                            assert(!CRASH);
                            return iret;
                        }
                    }

                    if (i == 0) {
                        /* write term */
                        unsigned int tmpbytes = 0;
                        while (tmp[i] - tmpbytes > VEC_LEN(&interv)) {
                            unsigned int transfer = VEC_LEN(&interv);
                            vec_byte_write(&interv, curr->term + tmpbytes, 
                              VEC_LEN(&interv));
                            tmpbytes += transfer;
                            output->pos = interv.pos;
                            if ((iret = output_flush(situ, output, !vocab, 
                                  insitu)) == INSITU_OK) {
                                interv.pos = output->pos;
                                interv.end = output->end;
                            } else {
                                assert(!CRASH);
                                return iret;
                            }
                        }
                        vec_byte_write(&interv, curr->term + tmpbytes, 
                          tmp[i] - tmpbytes);
                    }
                }

                output->pos = interv.pos;
                assert(output->end == interv.end);
#undef INTS 
            }

            do {
                unsigned int bytes = curr->entry.size;

                /* for all but the first run, copy first vbyte from entry to 
                 * output, reencoding it.  This conditional has a counterpart
                 * above. */
                if (curr > min) {
                    struct vec tmpv;
                    unsigned int docno_len;

                    /* write (pre-reencoded) first docno */
                    tmpv.pos = output->pos;
                    tmpv.end = output->end;
                    if ((docno_len = vec_vbyte_write(&tmpv, curr->entry.first)) 
                      > 0) {
                        output->pos += docno_len;
                    } else {
                        /* crossed output buffer boundary */
                        char buf[VEC_VBYTE_MAX];
                        unsigned int before = output->end - output->pos;

                        /* copy initial part of vbyte into output buffer */
                        tmpv.pos = buf;
                        tmpv.end = buf + VEC_VBYTE_MAX;
                        docno_len = vec_vbyte_write(&tmpv, curr->entry.first);
                        assert(docno_len > before);
                        memcpy(output->pos, buf, before);
                        output->pos += before;
                        assert(output->pos == output->end);

                        if ((iret = output_flush(situ, output, !vocab, insitu)) 
                          == INSITU_OK) {
                            /* copy remainder of vbyte into output buffer */
                            assert(output->end - output->pos > VEC_VBYTE_MAX);
                            memcpy(output->pos, buf + before, 
                              docno_len - before);
                            output->pos += docno_len - before;
                        } else {
                            assert(iret != INSITU_END);
                            assert(!CRASH);
                            free(vbuf);
                            return iret;
                        }
                    }
                }

                /* transfer remaining data from input to output.  Note that 
                 * this is done using memcpy, because the page-aligned 
                 * requirement of in situ merging makes the alternative 
                 * (writing from input buffers directly to the output) 
                 * quite complex. */
                while (bytes) {
                    unsigned int transfer = bytes;

                    /* fill input if necessary (placed before copy, so that we
                     * request too much data from the input) */
                    if (curr->pos >= curr->end) {
                        if ((iret = input_fill(situ, curr)) != INSITU_OK) {
                            assert(iret != INSITU_END);
                            assert(!CRASH);
                            free(vbuf);
                            return iret;
                        }
                    }

                    /* flush output if necessary */
                    if (output->pos >= output->end) {
                        if ((iret = output_flush(situ, output, !vocab, insitu)) 
                          != INSITU_OK) {
                            assert(iret != INSITU_END);
                            assert(!CRASH);
                            free(vbuf);
                            return iret;
                        }
                    }

                    /* limit the number of bytes transferred now to the size of
                     * the buffers involved */
                    if (transfer > curr->end - curr->pos) {
                        transfer = curr->end - curr->pos;
                    }
                    if (transfer > output->end - output->pos) {
                        transfer = output->end - output->pos;
                    }

                    /* copy data */
                    memcpy(output->pos, curr->pos, transfer);
                    output->pos += transfer;
                    curr->pos += transfer;
                    assert(bytes >= transfer);
                    bytes -= transfer;
                }

                curr++;
            } while (curr < tmpend);

            /* add vocab entry to buffer */
            if (vocab && (vret = vocab_encode(&vv, &v)) == VOCAB_OK) {
                /* do nothing */
            } else if (vocab) {
                assert("can't get here" && 0);
                free(vbuf);
                return INSITU_EINVAL;
            }
        } while (curr < end);

        /* read next entries and put them back on the heap */
        for (curr = min; curr < end; curr++, popped--) {
            if ((iret = read_input(situ, curr)) == INSITU_OK) {
                /* put input back onto the heap */
                heap_insert(input, &inputs, sizeof(*input), runhead_cmp, curr);
            } else if (iret == INSITU_END) {
                /* copy this input to the back of the heap, so that we preserve
                 * the buffer pointer until it can be freed */
                if (popped > 1) {
                    struct runhead tmp = *curr;
                    memmove(curr, curr + 1, sizeof(tmp) * (popped - 1));
                    curr[popped - 1] = tmp;
                }
                /* alter iteration to take removal into account */
                end--;
                curr--;
            } else {
                assert(!CRASH);
                free(vbuf);
                return INSITU_OK;
            }
        }
    }

    /* insert buffered entry into the vocab */
    if (vocab) {
        vocab->datasize = v.pos - vbuf;
        vocab->termlen = vtermlen;
        if ((iret = vocab_insert(situ, vocab, stats, vbuf)) == INSITU_OK) {
            /* clear vocab buffer */
            v.pos = vbuf;
            vterm[0] = '\0';
            vtermlen = 0;
            dterms++;
        } else {
            assert(iret != INSITU_END);
            assert(!CRASH);
            free(vbuf);
            return iret;
        }
    }

    /* pad output to next page boundary (this will be removed by
     * later truncation, but it is much easier on the intermediate
     * code if everything occurs in page-sized chunks) */
    if ((rem = ((output->pos - output->buf) % situ->b)) > 0) {
        memset(output->pos, 0, situ->b - rem);
        output->pos += situ->b - rem;
        assert(output->pos <= output->end);
        assert((output->pos - output->buf) % situ->b == 0);
    } else {
        rem = situ->b;
    }

    free(vbuf);

    /* perform final output flush */
    if (((iret = output_flush(situ, output, !vocab, insitu)) == INSITU_OK)
      && (ptr = realloc(output->last_offsets, 
          sizeof(*output->last_offsets) * (output->logical.file + 1)))) {

        /* record last position in logical file */
        output->last_offsets = ptr;
        output->last_offsets[output->logical.file] 
          = output->logical.offset - situ->b + rem;
        assert(output->pos == output->buf);

        /* update stats */
        stats->distinct_terms = dterms;
        stats->terms_low = terms_low;
        stats->terms_high = terms_high;

        if (vocab) {
            /* write out remaining vocab btree */
            iret = vocab_finish(situ, vocab, stats);
        } else {
            iret = INSITU_OK;
        }
    } else if (iret == INSITU_OK) {
        assert(ptr == NULL);
        iret = INSITU_ENOMEM;
    }

    assert(iret != INSITU_END);
    return iret;
}

struct permute_b {
    uintmax_t index;
    char *buf;
};

static int permute_b_cmp(const void *vone, const void *vtwo) {
    const struct permute_b *one = vone,
                           *two = vtwo;

    if (one->index < two->index) {
        return -1;
    } else if (one->index > two->index) {
        return 1;
    } else {
        return 0;
    }
}

/* internal function to insert a new record into in-memory permutation blocks
 * array */
static struct permute_b *permute_insert(struct permute_b *block, 
  unsigned int *blocks, unsigned long int index, char *buf) {
    struct permute_b key,
                     *find;
    unsigned int findidx;

    VALGRIND_CHECK_READABLE(&index, sizeof(index));
    VALGRIND_CHECK_READABLE(&buf, sizeof(buf));

    key.index = index;
    key.buf = NULL;
    
    if ((find = binsearch(&key, block, *blocks, sizeof(*block), permute_b_cmp))
      < block + *blocks) {
        /* need to move existing items down the array */
        assert(find->index != index);
        findidx = find - block;
        memmove(find + 1, find, sizeof(*block) * (*blocks - findidx));
    }
    (*blocks)++;
    assert(find < block + *blocks);
    find->index = index;
    find->buf = buf;
    return find;
}

/* internal function to remove a record from the in-memory permutation blocks
 * array, if it is found. */
static int permute_remove(struct permute_b *block, 
  unsigned int *blocks, unsigned long int index, struct permute_b *ptr) {
    struct permute_b key,
                     *find;
    unsigned int idx;

    key.index = index;
    key.buf = NULL;
    
    if (((find = binsearch(&key, block, *blocks, sizeof(*block), permute_b_cmp))
        < block + *blocks)
      && (find->index == index)) {
        idx = find - block;
        *ptr = *find;
        (*blocks)--;
        memmove(find, find + 1, sizeof(*block) * (*blocks - idx));
        return 1;
    } else {
        return 0;
    }
}

/* internal function to find the buffered index closest to the current index */
static unsigned long int permute_nearest(struct permute_b *block,
  unsigned int blocks, unsigned long int index) {
    struct permute_b key,
                     *find;

    key.index = index;
    key.buf = NULL;
    
    if ((find = binsearch(&key, block, blocks, sizeof(*block), permute_b_cmp))
        < block + blocks) {

        if (find + 1 < block + blocks 
          && find[1].index - index < index - find->index) {
            assert(find[1].index > index);
            return find[1].index;
        } else {
            return find->index;
        }
    } else if (blocks) {
        return block[0].index;
    } else {
        return 0;
    }
}

struct permute_free {
    struct permute_free *next;
};

static unsigned int permute_freelen(struct permute_free *f) {
    unsigned int len = 0;

    while (f) {
        f = f->next;
        len++;
    }

    return len;
}

/* internal function to print out the permutation location array */
void insitu_print_permutation(uintmax_t *loc, unsigned int maxb) {
    unsigned int j;

    for (j = 0; j < maxb; j++) {
        if (loc[j] - 1 == j) {
            printf(" %u:-", j);
        } else if (loc[j] > 0) {
            printf(" %u:%llu", j, loc[j] - 1);
        }
        printf(",");
    }
    printf("\n"); 
}

static enum insitu_ret permute(struct insitu *situ) {
    struct permute_b *block = NULL;
    struct permute_free *freeb = NULL;
    uintmax_t i,
              bperfile = situ->max_filesize / situ->b,
              maxb = bperfile * situ->file + situ->offset / situ->b,
              *offsets = NULL;
    unsigned int blocks = 0,
                 memblocks = (situ->memory - sizeof(uintmax_t) * maxb) 
                   / (situ->b + sizeof(*block)),
                 j;
    uintmax_t *loc = NULL;    /* loc maps physical to logical addresses */
    char *buf = NULL;
    enum rbtree_ret rbret;
    struct rbtree_iter *rbi;
    void *key,
         **data;
    int fd;

    printf("\npermuting\n");
    insitu_print_loc(situ, __LINE__);

    /* we require a minimum of two in-memory blocks to permute */
    if (memblocks < 2 || situ->stress) {
        memblocks = 2;
    }

    /* the permute function runs through the list of used locations and, 
     * for each page where the logical and physical locations disagree, 
     * corrects this situation.  Since the red-black trees we use to record
     * used and free locations can't be changed during iteration, and because
     * they require inversion (from logical to physical to vice versa), 
     * we use an array to simplify things.  Note that this function can be 
     * used to permute the result of intermediate merges, to assist 
     * in debugging. */

#define FAIL(ret) \
    assert(ret == INSITU_OK || !CRASH); \
    if (loc) free(loc); if (block) free(block); \
    if (buf) free(buf); if (offsets) free(offsets); \
    return ret;

    if ((loc = malloc(sizeof(*loc) * maxb))
      && (block = malloc(sizeof(*block) * memblocks)) 
      && (buf = malloc(situ->b * memblocks))
      && (offsets = malloc(sizeof(*offsets) * situ->id))) {
        uintmax_t prev_offset = 0;

        /* initialise loc to all zeroes, though we inform valgrind that this
         * isn't 'real' initialisation.  We add one to subsequent 'real' 
         * entries to distinguish them from the zeroes we write here. */
        memset(loc, 0, sizeof(*loc) * maxb);
        VALGRIND_MAKE_WRITABLE(loc, sizeof(*loc) * maxb);

        /* initialise free list (note that power-of-two values of b should
         * ensure alignment is ok) */
        for (i = 0; i < memblocks; i++) {
            struct permute_free *newf = (void *) (buf + situ->b * i);
            newf->next = freeb;
            freeb = newf;
        }

        /* initialise offsets list */
        for (i = 0; i < situ->id; i++) {
            offsets[i] = 0;
        }
        printf("max blocks %llu offsets:", maxb);
        for (i = 0; i < situ->run_size; i++) {
            unsigned int pages = (situ->run[i].content + situ->b - 1) / situ->b;
            assert(situ->run[i].id < situ->id);
            offsets[situ->run[i].id] = prev_offset;
            prev_offset += pages;
            printf(" %u(%u):%llu", situ->run[i].id, pages, 
              offsets[situ->run[i].id]);
        }
        printf("\n");
        if (permute_freelen(freeb) != memblocks) {
            assert(0);
        }
    } else {
        FAIL(INSITU_ENOMEM);
    }

    /* invert used blocks */
    if ((rbi = rbtree_iter_new(situ->locs, RBTREE_ITER_INORDER, 0))) {
        while ((rbret = rbtree_iter_ptr_ptr_next(rbi, &key, &data)) 
          == RBTREE_OK) {
            struct loc *tmploc = key;
            uintmax_t index = tmploc->physical.offset / situ->b 
              + tmploc->physical.file * bperfile;
            unsigned int pages,
                         locpages = tmploc->bytes / situ->b;
            assert(index < maxb);

            for (pages = 0; pages < locpages; pages++) {
                /* translate the logical offset internal to the run to a global
                 * logical offset using the offsets array calculated earlier.  
                 * Also note +1 below is to ensure that 0 isn't a valid entry */
                loc[index + pages] 
                  = offsets[tmploc->runid] + tmploc->logical / situ->b 
                    + pages + 1;
            }
        }
        assert(rbret == RBTREE_ITER_END);
        rbtree_iter_delete(rbi);
    } else {
        FAIL(INSITU_ENOMEM);
    }

    /* set free block locations to 0, to indicate that we don't need to read
     * stuff from them */
    if ((rbi = rbtree_iter_new(situ->freelocs, RBTREE_ITER_INORDER, 0))) {
        while ((rbret = rbtree_iter_ptr_ptr_next(rbi, &key, &data)) 
          == RBTREE_OK) {
            struct loc *tmploc = key;
            uintmax_t index = tmploc->physical.offset / situ->b 
              + tmploc->physical.file * bperfile;
            assert(index < maxb);

            for (i = 0; i < tmploc->bytes / situ->b; i++) {
                loc[index + i] = 0;
            }
        }
        assert(rbret == RBTREE_ITER_END);
        rbtree_iter_delete(rbi);
    } else {
        FAIL(INSITU_ENOMEM);
    }

    /* all blocks should now have entries in the inverted array */
    VALGRIND_CHECK_READABLE(loc, sizeof(*loc) * maxb);
    for (i = 0; i < maxb; i++) {
        assert(loc[i] < maxb + 1);
    }

    /* perform the permutation */
    for (i = 0; i < maxb; i++) {
        uintmax_t curr = i,
                  prev = -1;

        if (loc[curr] > 0 && loc[curr] - 1 != curr) {
            printf("permute reset to %llu (%llu)\n", curr, loc[curr] - 1);
        }

        /* we should have enough space for this block, plus the one we may 
         * need to move to place it */
        assert(blocks + 1 < memblocks);

        do {
            assert(blocks + permute_freelen(freeb) == memblocks);

            if (loc[curr] != curr + 1) {
                struct permute_b currblock;
                unsigned int file = curr / bperfile;
                unsigned long int offset = (curr % bperfile) * situ->b;

                assert((file < situ->file && offset < situ->max_filesize)
                  || (file == situ->file && offset < situ->offset));

                assert(freeb);
                if (loc[curr]) {
                    /* this block hasn't been read yet, buffer it */
                    struct permute_free *nextfree = freeb->next;
                    struct permute_b *currblock_ptr;

                    /* pin fd and read */
                    if ((fd = fdset_pin(situ->fds, situ->tmp_type, file, 
                        offset, SEEK_SET)) 
                      && read(fd, (void *) freeb, situ->b) == situ->b
                      && fdset_unpin(situ->fds, situ->tmp_type, file, fd) 
                        == FDSET_OK) {

                        insitu_print_permutation(loc, maxb);

                        currblock_ptr = permute_insert(block, &blocks, 
                          loc[curr] - 1, (void *) freeb);

                        printf("permute grabbed %llu from %llu (", 
                          currblock_ptr->index, curr);
                        for (j = 0; j < blocks; j++) {
                            if (j) {
                                printf(", ");
                            }
                            printf("%llu", block[j].index);
                        }
                        printf(") f %u off %lu b %u\n", file, offset, situ->b);

                        loc[curr] = 0;  /* mark block as read */
                        assert(currblock_ptr);
                        assert(currblock_ptr >= block 
                          && currblock_ptr < block + blocks);

                        freeb = nextfree;
                        assert(blocks + permute_freelen(freeb) == memblocks);
                    } else {
                        FAIL(fd >= 0 ? INSITU_EIO: INSITU_EFILE);
                    }
                }
                assert(loc[curr] == 0);
                
                printf("permute searching for %llu\n", curr);

                /* check if we have this block buffered.  If so, remove it and 
                 * write it */
                if ((permute_remove(block, &blocks, curr, &currblock))) {
                    /* pin fd and write */
                    assert(currblock.index == curr);
                    if ((fd = fdset_pin(situ->fds, situ->tmp_type, file, 
                        offset, SEEK_SET)) 
                      && write(fd, currblock.buf, situ->b) == situ->b
                      && fdset_unpin(situ->fds, situ->tmp_type, file, fd) 
                        == FDSET_OK) {

                        /* successfully written */
                        struct permute_free *newf = (void *) currblock.buf;
                        newf->next = freeb;
                        freeb = newf;
                        assert(blocks + permute_freelen(freeb) == memblocks);

                        loc[curr] = curr + 1;
                        printf("permute released %llu (", currblock.index);
                        for (j = 0; j < blocks; j++) {
                            if (j) {
                                printf(", ");
                            }
                            printf("%llu", block[j].index);
                        }
                        printf(") f %u off %lu b %u\n", file, offset, situ->b);


                    } else {
                        FAIL(fd >= 0 ? INSITU_EIO: INSITU_EFILE);
                    }
                } else {
                    /* unless this is the first block in the dependant 'chain',
                     * we should be able to write a block */
                    assert(curr == i);
                }

                /* find next nearest buffered location */
                prev = curr;
                curr = permute_nearest(block, blocks, curr);
            }
        } while (blocks + 1 >= memblocks);

        /* write out all blocks between here and next seek location to
         * give better disk access pattern.  Further improvement could be 
         * gained by doing something similar when jumping to the next write
         * location, but i can't be bothered implementing it at the moment. */

        /* find current location in block array */
        for (curr = 0; curr < blocks && block[curr].index < prev; curr++) ;

        /* while we've got things to write that are between where we are and
         * where we're going... */
        while (curr < blocks 
          && block[curr].index >= prev 
          && block[curr].index < i) {
            /* write them out */
            struct permute_b currblock;
            unsigned int file = block[curr].index / bperfile;
            unsigned long int offset = (block[curr].index % bperfile) * situ->b;
            int ret;

            /* pin fd and write */
            ret = permute_remove(block, &blocks, block[curr].index, &currblock);
            assert(ret);
            if ((fd = fdset_pin(situ->fds, situ->tmp_type, file, 
                offset, SEEK_SET)) 
              && write(fd, currblock.buf, situ->b) == situ->b
              && fdset_unpin(situ->fds, situ->tmp_type, file, fd) 
                == FDSET_OK) {

                /* successfully written */
                struct permute_free *newf = (void *) currblock.buf;
                newf->next = freeb;
                freeb = newf;
                assert(blocks + permute_freelen(freeb) == memblocks);

                loc[currblock.index] = currblock.index + 1;
                printf("permute released(opt) %llu (", currblock.index);
                for (j = 0; j < blocks; j++) {
                    if (j) {
                        printf(", ");
                    }
                    printf("%llu", block[j].index);
                }
                printf(") f %u off %lu b %u\n", file, offset, situ->b);

            } else {
                FAIL(fd >= 0 ? INSITU_EIO: INSITU_EFILE);
            }
        }
    }

    /* need to clear remaining buffered blocks out of memory */
    while (blocks--) {
        struct permute_b *currblock = &block[blocks];
        unsigned int file = (currblock->index) / bperfile;
        unsigned long int offset = (currblock->index % bperfile) * situ->b;

        /* pin fd and write */
        if ((fd = fdset_pin(situ->fds, situ->tmp_type, file, 
            offset, SEEK_SET)) 
          && write(fd, currblock->buf, situ->b) == situ->b
          && fdset_unpin(situ->fds, situ->tmp_type, file, fd) 
            == FDSET_OK) {

            /* successfully written */
            loc[currblock->index] = currblock->index + 1;
        } else {
            FAIL(fd >= 0 ? INSITU_EIO: INSITU_EFILE);
        }
    }

    /* check that everything has been permuted */
    for (i = 0; i < maxb && DEBUG; i++) {
        assert(loc[i] == i + 1 || loc[i] == 0);
    }
 
    insitu_print_permutation(loc, maxb);

    /* update block addresses */
    if ((rbi = rbtree_iter_new(situ->locs, RBTREE_ITER_INORDER, 0))) {
        while ((rbret = rbtree_iter_ptr_ptr_next(rbi, &key, &data)) 
          == RBTREE_OK) {
            struct loc *tmploc = key;
            uintmax_t log 
              = tmploc->logical / situ->b + offsets[tmploc->runid];

            /* translate intra-run logical address into global logical address
             * (above) and then convert that to the physical address that it
             * should now be found at (below) */

            tmploc->physical.file = log / bperfile;
            tmploc->physical.offset = (log % bperfile) * situ->b;
        }
        assert(rbret == RBTREE_ITER_END);
        rbtree_iter_delete(rbi);
    } else {
        FAIL(INSITU_ENOMEM);
    }

    /* update empty addresses */
    if ((rbi = rbtree_iter_new(situ->freelocs, RBTREE_ITER_INORDER, 0))) {
        i = 0;
        while ((rbret = rbtree_iter_ptr_ptr_next(rbi, &key, &data)) 
          == RBTREE_OK) {
            struct loc *tmploc = key;
            unsigned int pages = tmploc->bytes / situ->b;

            /* find next empty location (should be at the back) */
            while (loc[i] > 0) {
                i++;
                assert(i + pages <= maxb);
            }

            /* check that the entire span we require is empty */
            for (j = 0; j < pages; j++) {
                assert(loc[i + j] == 0);
            }

            tmploc->physical.file = i / bperfile;
            tmploc->physical.offset = (i % bperfile) * situ->b;
        }
        assert(rbret == RBTREE_ITER_END);
        rbtree_iter_delete(rbi);
    } else {
        FAIL(INSITU_ENOMEM);
    }

    /* fill empty blocks with zeroes */
    if (DEBUG) {
        memset(buf, 0, situ->b);
        for (i = 0; i < maxb; i++) {
            if (loc[i] == 0) {
                unsigned int file = i / bperfile;
                unsigned long int offset = (i % bperfile) * situ->b;

                /* pin fd and write */
                if ((fd = fdset_pin(situ->fds, situ->tmp_type, file, 
                    offset, SEEK_SET)) 
                  && write(fd, buf, situ->b) == situ->b
                  && fdset_unpin(situ->fds, situ->tmp_type, file, fd) 
                    == FDSET_OK) {

                    /* successfully written, do nothing */
                } else {
                    FAIL(fd >= 0 ? INSITU_EIO: INSITU_EFILE);
                }
            }
        }
    }

    insitu_print_loc(situ, __LINE__);
    FAIL(INSITU_OK);  /* fine, it's not really 'failing', but its convenient */
#undef FAIL
}

enum insitu_ret prep_merge(struct insitu *situ, struct insitu_stats *stats, 
  unsigned int inputs, unsigned int offset, struct btbulk *vocab, 
  char *vterm, struct output *output, int insitu) {
    struct runhead *input;
    unsigned int i,
                 pages,
                 srcpages,
                 mempages,
                 overhead = page_overhead(situ->storage);
    enum insitu_ret iret;

    /* calculate the number of source pages */
    assert(inputs > 0);
    for (srcpages = 0, i = offset; i < offset + inputs; i++) {
        assert((situ->run[i].content + situ->b - 1) / situ->b > 0);
        srcpages += (situ->run[i].content + situ->b - 1) / situ->b;
    }
    assert(srcpages > 0);

    /* round memory down to nearest page size */
    mempages = situ->memory / (situ->b + overhead);
    /* ensure we have at least three pages of memory, as that is the absolute
     * mimimum that we can work with (two input, one output) */
    if (mempages < 3 || situ->stress) {
        mempages = 3;  
    } else if (mempages > srcpages * 2) {
        /* available memory is so large that we can do everything in memory.
         * Don't grab more memory than input and output combined */
        mempages = srcpages * 2;
    }
    assert(inputs <= situ->run_size);
    assert(inputs <= mempages - 1);
    assert(inputs == 2 || !situ->stress);

    /* pages is the number of pages that we can allocate with discretion */
    pages = mempages - (inputs + 1);
    if (DEBUG) {
        /* use a minimum of memory, to help flush out errors, when debugging */
        pages = 0;
    }

    /* Allocate half of the discretionary buffer pages to output, because 
     * it will (approximately) equal the entire input in length. */
    output->bufsize = situ->b * (1 + pages / 2);
    if ((input = malloc(sizeof(*input) * inputs))
      && (output->buf = malloc(output->bufsize))) {
        pages -= (output->bufsize / situ->b) - 1;

        /* initialise all other buffers to NULL, so we can free them easily if
         * necessary. */
        for (i = 0; i < inputs; i++) {
            input[i].buf = NULL;
            input[i].term = NULL;
        }
    } else {
        assert(!CRASH);
        if (input) {
            free(input);
        }
        return INSITU_ENOMEM;
    }

/* macro to clean up memory on exit */
#define EXIT(ret)                                                             \
    if (1) {                                                                  \
        assert(ret == INSITU_OK || !CRASH);                                   \
        if (output->buf) {                                                    \
            free(output->buf);                                                \
        }                                                                     \
        if (input) {                                                          \
            for (i = 0; i < inputs; i++) {                                    \
                if (input[i].buf) {                                           \
                    free(input[i].buf);                                       \
                }                                                             \
                if (input[i].term) {                                          \
                    free(input[i].term);                                      \
                }                                                             \
            }                                                                 \
            free(input);                                                      \
        }                                                                     \
        return ret;                                                           \
    } else

    /* initialise output.  Allocate half of the discretionary buffer pages to 
     * it, because it will (approximately) equal the entire input in length. */
    output->logical.file = 0;
    output->logical.offset = 0;
    output->physical.capacity = 0;
    output->pos = output->buf;
    output->end = output->pos + output->bufsize;

    /* initialise inputs, allocating discretionary pages on the basis of input
     * size as a ratio of remaining pages. */
    printf("\nsrcpages %u, pages %u\n", srcpages, pages);
    for (i = 0; i < inputs; i++) {
        /* pre-init initialisation :o(, required to calculate the buffer size 
         * allocated to this run */
        assert(srcpages > 0);
        input[i].run = &situ->run[i + offset];
        input[i].pages = (input[i].run->content + situ->b - 1) / situ->b;
        input[i].bufsize 
          = (1 + (pages * input[i].pages + srcpages - 1) / srcpages);
        input[i].bufsize *= situ->b;
        input[i].entries_read = 0;
        input[i].pages_read = 0;
        srcpages -= input[i].pages;
        assert(srcpages > 0 || i == inputs - 1);
        pages -= (input[i].bufsize / situ->b) - 1;

        iret = INSITU_ENOMEM;
        if ((input[i].term = malloc(situ->storage->max_termlen + 1))
          && (input[i].buf = malloc(input[i].bufsize))
          && (iret = init_input(situ, &input[i], &situ->run[i + offset], 
              input[i].term, input[i].buf, input[i].bufsize / situ->b)) 
            == INSITU_OK) {

            /* read succeeded */
        } else {
            EXIT(iret);
        }
    }
    printf("srcpages %u pages %u\n", srcpages, pages);
    assert(srcpages == 0 && pages == 0);

    iret = merge(situ, input, inputs, output, vocab, vterm, stats, insitu);
    assert(iret != INSITU_END);
    stats->idx_files = output->logical.file + 1;
    VALGRIND_CHECK_READABLE(stats, sizeof(*stats));

    EXIT(iret);
#undef EXIT
}

enum insitu_ret insitu_merge(struct insitu *situ, struct insitu_stats *stats) {
    struct btbulk vocab_space;
    struct output output;
    struct btbulk *vocab;
    unsigned int overhead = page_overhead(situ->storage),
                 pages,
                 inputs,
                 i;
    enum insitu_ret iret;
    char *vterm;

    pages = situ->memory / (situ->b + overhead);
    if (pages < 3 || situ->stress) {
        inputs = 2;
    } else {
        inputs = pages - 1;
    }
    assert(inputs >= 2);

    vterm = malloc(situ->storage->max_termlen + 1);
    output.last_offsets = malloc(sizeof(*output.last_offsets));
    if (!output.last_offsets || !vterm) {
        if (vterm) {
            free(vterm);
        }
        if (output.last_offsets) {
            free(output.last_offsets);
        }
        return INSITU_ENOMEM;
    }

    /* trim input runs of their excess padding */
    for (i = 0; i < situ->run_size; i++) {
        if ((iret = insitu_trim(situ, &situ->run[i])) != INSITU_OK) {
            assert(!CRASH);
            free(vterm);
            free(output.last_offsets);
            return iret;
        }
    }

    do {
        int inter_merged = 0;  /* track whether we actually perform an 
                                * intermediate merge */

        for (i = 0; situ->run_size > inputs && i < situ->run_size; i++) {
            unsigned int tomerge = inputs;
            unsigned int j;

            for (j = 0; j < situ->run_size; j++) {
                printf("[%u %llu %u], ", situ->run[j].id, situ->run[j].content, 
                  situ->run[j].padding);
            }
            printf("\n");

            if (tomerge > situ->run_size - i) {
                /* not enough remaining runs to merge with all inputs */
                tomerge = situ->run_size - i;
            }
            if (tomerge > situ->run_size + 1 - inputs) {
                /* don't need to merge with all inputs */
                tomerge = situ->run_size + 1 - inputs;
            }
            output.runid = situ->id++;
            printf("intermediate merge from %u - %u (%u els, runsize %u, i %u)\n", 
              situ->run[i].id, situ->run[i + tomerge - 1].id, tomerge,
              situ->run_size, i);
            iret = prep_merge(situ, stats, tomerge, i, NULL, vterm, &output, 1);
            inter_merged = 1;

            if (iret == INSITU_OK) {
                unsigned int j;

                /* calculate attributes of new run */
                situ->run[i].id = output.runid;
                situ->run[i].content = 0;
                for (j = 0; j <= output.logical.file; j++) {
                    situ->run[i].content += output.last_offsets[j];
                }
                assert(situ->run[i].content);
                situ->run[i].padding 
                  = situ->b - (situ->run[i].content % situ->b);
                if (situ->run[i].padding == situ->b) {
                    situ->run[i].padding = 0;
                }
                assert(situ->run[i].padding < situ->b);

                /* remove additional runs that we just merged */
                memmove(&situ->run[i + 1], &situ->run[i + tomerge], 
                  (situ->run_size - i - tomerge) * sizeof(*situ->run));
                situ->run_size -= tomerge - 1;
            } else {
                assert(!CRASH);
                free(output.last_offsets);
                free(vterm);
                return iret;
            }
        }

        if (DEBUG && inter_merged) {
            /* permute the intermediate merge files so that they're
             * debuggable */
            if ((iret = permute(situ)) != INSITU_OK) {
                assert(!CRASH);
                free(output.last_offsets);
                free(vterm);
                return iret;
            }
        }
    } while (situ->run_size > inputs);

    /* initialise vocabulary bulk-loading */
    if ((vocab = btbulk_new(situ->storage->pagesize, 
        situ->storage->max_filesize,
        situ->storage->btleaf_strategy, situ->storage->btnode_strategy, 1.0,
        0, &vocab_space))) {

        output.runid = situ->id++;
        iret = prep_merge(situ, stats, situ->run_size, 0, vocab, vterm, 
            &output, situ->insitu);
        btbulk_delete(vocab);

        if (iret == INSITU_OK) {
            /* perform post-merge cleanup, either permutation or deletion of
             * temporary files */
            if (iret == INSITU_OK && situ->insitu) {
                iret = permute(situ);
                assert(iret == INSITU_OK);

                if (situ->insitu) {
                    /* delete excess index files */
                    i = output.logical.file + 1;
                } else {
                    /* delete all temporary files */
                    i = 0;
                }

                /* remove excess files */
                for (; 
                  i <= situ->file && (situ->file == 0 || situ->offset > 0); 
                  i++) {
                    int fdret = fdset_unlink(situ->fds, situ->tmp_type, i);
                    if (fdret != FDSET_OK) {
                        assert(!CRASH);
                        free(output.last_offsets);
                        free(vterm);
                        return INSITU_EFILE;
                    }
                }
            }

            /* truncate away additional space */
            for (i = 0; i <= output.logical.file; i++) {
                int fd;
                unsigned long int end;

                if ((fd = fdset_pin(situ->fds, situ->idx_type, i, 0, SEEK_END)) 
                     >= 0
                  && (end = lseek(fd, 0, SEEK_END)) != -1
                  && ftruncate(fd, output.last_offsets[i]) == 0) {
                    printf("truncating file %u from %lu to %lu\n", i, end, 
                      output.last_offsets[i]);
                    fdset_unpin(situ->fds, situ->idx_type, i, fd);
                } else {
                    assert(!CRASH);
                    if (fd >= 0) {
                        fdset_unpin(situ->fds, situ->idx_type, i, fd);
                    }
                    free(output.last_offsets);
                    free(vterm);
                    return INSITU_EFILE;
                }
            }
        } else {
            free(output.last_offsets);
            free(vterm);
            return INSITU_ENOMEM;
        }
    } else {
        if (vocab) {
            btbulk_delete(vocab);
        }
        free(output.last_offsets);
        free(vterm);
        return INSITU_ENOMEM;
    }

    free(output.last_offsets);
    free(vterm);

    assert(iret == INSITU_OK);
    return INSITU_OK;
}

