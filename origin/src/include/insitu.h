/* insitu.h declares an interface to a module that performs index
 * merging, with the ability to do this in situ.  
 * In situ merging is a method of merging that cleverly reuses
 * temporary space to reduce the peak disk space requirement, (which is
 * twice the size of the resulting index for regular merging)
 * to fractionally more than the size of the resulting index.
 * It is defined in 'In Situ Generation of Compressed Inverted Files',
 * by Moffat and Bell, 1995.
 *
 * written nml 2006-09-20
 *
 */

#ifndef INSITU_H
#define INSITU_H

#ifdef __cplusplus
extern "C" {
#endif

/* return values from insitu functions */
enum insitu_ret {
    INSITU_OK = 0,                 /* operation completed successfully */

    INSITU_EINVAL = -1,            /* failed unexpectedly, possibly due to 
                                    * corrupt input */
    INSITU_ENOMEM = -2,            /* failed to allocate memory */
    INSITU_EFILE = -3,             /* file manipulation failed */
    INSITU_EIO = -4                /* read/write failed */
};

struct fdset;
struct storagep;

struct insitu;
struct insitu_run;

/* create a new insitu object, given an fdset.  The tmp_type and
 * idx_type variables specify the fdset type of the temporary and
 * final index files generated.  They must be different, regardless of
 * whether in situ merging is desired.
 * The vocab_type specifies the fdset type of the final vocabulary.  
 * The storage structure specifies storage parameters. 
 * The insitu parameter specifies whether insitu merging is desired,
 * the stressed parameter */
struct insitu *insitu_new(struct fdset *fds, unsigned int tmp_type, 
  unsigned int idx_type, unsigned int vocab_type, struct storagep *storage,
  int insitu, unsigned int memory, int stressed);

/* free resources associated with an insitu object */
void insitu_delete(struct insitu *situ);

/* create a new run, for dumping postings to.  sizehint gives the approximate
 * size (in bytes) of the dumped run. */
struct insitu_run *insitu_run_new(struct insitu *situ, unsigned int sizehint);

/* get buffer space to write out material into the run */
struct vec *insitu_run_buffer(struct insitu_run *run);

/* empty the current buffer (which must be full - the last partial bufferload is
 * handled by insitu_run_commit()) */
enum insitu_ret insitu_run_empty(struct insitu_run *run);

/* commit the run into the merge (must be called prior to
 * insitu_run_delete() if the final merge is to succeed) */
enum insitu_ret insitu_run_commit(struct insitu_run *run);

/* free resources associated with an insitu_run */
void insitu_run_delete(struct insitu_run *run);

struct insitu_stats {
    unsigned int idx_files;               /* index files created */
    unsigned int distinct_terms;          /* distinct terms in index */
    unsigned int terms_high;              /* high word counting index terms */
    unsigned int terms_low;               /* low word counting index terms */
    unsigned int vocab_files;             /* vocab files created */
    unsigned int vocab_root_file;         /* file containing vocab root */
    unsigned long int vocab_root_offset;  /* offset of vocab root */
};

/* merge all runs committed into a final index.  The only operation
 * allowed after this call is to delete the insitu object. */
enum insitu_ret insitu_merge(struct insitu *situ, struct insitu_stats *stats);

#ifdef __cplusplus
}
#endif

#endif

