/*
 *  tests the mrbufstuffer module.
 *
 *  The following cases need to be checked:
 *
 *  a. Multiple adds followed by gets, without dump, retrieves
 *      same results as added.
 *  b. After each add, do a get; should retrieve same as added.
 *  c. Dump/loaded mrbufstuffer same as in-memory one.
 *  d. Dumped mrbufstuffer, when loaded, can be added to.
 *  e. mrbufstuffer with no elements.
 *  f. mrbufstuffer with one element.
 *  g. mrbufstuffer with only empty elements.
 *
 *  Each line of the input file represents a "script" for
 *  a test run.  Each line is made up of a series of
 *  space-delimited tokens.  The first token is the "identifier"
 *  of the run.  The remaining tokens are keyword "commands", some
 *  of which are followed by "=<arg>".  The commands are:
 *
 *     ADD=<num>
 *         Add <num> number of objects.
 *
 *     CHECK
 *         Check mrbufstuffer against all the added elements
 *
 *     [NO_]GET_EACH_ADD
 *         Switch to a mode where each add is followed by a get.
 *
 *     DUMP_LOAD
 *         Dump and load mrbufstuffer.
 *
 *     MAXLEN=<len>
 *         Set the maximum element length to <len>
 *
 *  There are also the following global commands: these must occur
 *  on a line by themselves:
 *
 *     @VERBOSE
 *          Switch to verbose mode
 *     @NOVERBOSE
 *          Switch out of verbose mode
 *     @SEED <seed>
 *          Seed the random-number generator with <seed>
 *     @INPUT <filename>
 *          Use <filename> for input, not random data.
 *     @THRESHOLD <val>
 *          Use dump threshold of <val> for future runs
 *     @MAXFILE <bytes>
 *          Limit files to a maximum size of <bytes>
 *
 */

#include "firstinclude.h"
#include "test.h"
#include "testutils.h"
#include "mrbufstuffer.h"
#include "lcrand.h"
#include "str.h"
#include "error.h"
#include "fdset.h"
#include "freemap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define DEFAULT_SEED 43u

static int verbose = 0;

static FILE * input_file = NULL;

static unsigned threshold = 4000u;

static unsigned maxfile = 1024u * 1024u * 1024u * 2 - 1;

int do_run(char ** cmds, int num_cmds);

int test_file(FILE * fp, int argc, char ** argv) {
    char buf[1024];
    int line_num = 0;
    char * ptr;
    int all_passed = 1;

    tu_init_rand_or_die(DEFAULT_SEED);
    while (fgets((char *) buf, 1023, fp)) {
        line_num++;
        ptr = (char *) str_ltrim(buf);
        str_rtrim(ptr);
        if (*ptr == '#' || *ptr == '\0') {
        } else if (*ptr == '@') {
            if (strncmp(ptr + 1, "SEED", strvlen("SEED")) == 0) {
                unsigned seed;
                if (sscanf(ptr + 1 + strvlen("SEED"), "%u", &seed) < 1) {
                    fprintf(stderr, "Can't find seed on SEED directive, "
                      "line %d\n", line_num);
                } else {
                    tu_init_rand_or_die(seed);
                }
            } else if (strncmp(ptr + 1, "VERBOSE", strvlen("VERBOSE")) == 0) {
                verbose = 1;
                fprintf(stderr, "... VERBOSE mode on\n");
            } else if (strncmp(ptr + 1, "NOVERBOSE", strvlen("NOVERBOSE")) 
              == 0) {
                verbose = 0;
            } else if (strncmp(ptr + 1, "INPUT", strvlen("INPUT")) == 0) {
                const char * fname = str_ltrim(buf + strvlen("INPUT") + 1);
                if (input_file != NULL) {
                    fclose(input_file);
                }
                if ( (input_file = fopen(fname, "r")) == NULL) {
                    fprintf(stderr, "Can't open '%s' for input; reverting "
                      "to random data\n", fname);
                }
            } else if (strncmp(ptr + 1, "THRESHOLD", strvlen("THRESHOLD")) 
              == 0) {
                int new_threshold = atoi(ptr + strvlen("THRESHOLD") + 1);
                if (new_threshold >= 0)
                    threshold = new_threshold;
                else 
                    fprintf(stderr, "Invalid THRESHOLD command\n");
            } else if (strncmp(ptr + 1, "MAXFILE", strvlen("MAXFILE")) == 0) {
                int new_maxfile = atoi(ptr + strvlen("MAXFILE") + 1);
                if (new_maxfile > 0)
                    maxfile = new_maxfile;
                else
                    fprintf(stderr, "Invalid MAXFILE command\n");
            } else {
                fprintf(stderr, "Unknown configuration directive '%s' "
                  "on line %d\n", ptr, line_num);
            }
        } else {
            unsigned int parts = 0;
            char ** cmds = str_split(ptr, " ", &parts);
            int ret;

            ret = do_run(cmds, parts);
            if (ret == -1) {
                all_passed = 0;
                fprintf(stderr, "Error doing run on line %d\n", line_num);
            } else if (ret == 0) {
                all_passed = 0;
            }
            free(cmds);
        }
    }
    return all_passed;
}

#define MRBUF_TEST_FD_TYPE 0xBEADu

#define DEFAULT_MAX_LEN 40

static int fdset_freemap_addfile(void * opaque, unsigned int file,
  unsigned int *maxsize) {
    struct fdset * fdset = (struct fdset *) opaque;
    int fd;
    *maxsize = maxfile;
    fd = fdset_create(fdset, MRBUF_TEST_FD_TYPE, file);
    if (fd == -EEXIST) {
        fd = fdset_pin(fdset, MRBUF_TEST_FD_TYPE, file, 0, SEEK_CUR);
        if (fd < 0)
            return -1;
    }
    fdset_unpin(fdset, MRBUF_TEST_FD_TYPE, file, fd);
    return 1;
}

static int check_index(struct mrbufstuffer * mrbfstf, unsigned index,
  struct tu_data_elements * elements, unsigned elem_index) {
    char * buf;
    unsigned out_len;
    unsigned el_len;
    enum mrbfstf_ret mr_ret;

    el_len = elements->elements[elem_index].len;
    buf = malloc(el_len);
    if (buf == NULL) {
        ERROR("out of memory");
        return -1;
    }
    mr_ret = mrbfstf_get(mrbfstf, index, buf, el_len, &out_len);
    if (mr_ret == MRBFSTF_BUFSIZE_ERROR) {
        ERROR2("BUFSIZE_ERROR, el_len %u, out_len %u", el_len, out_len);
        free(buf);
        return 0;
    } else if (mr_ret != MRBFSTF_OK) {
        ERROR1("return value of '%d'", mr_ret);
        free(buf);
        return 0;
    }
    if (out_len != el_len) {
        ERROR2("outlen was %u, should be %u", out_len, el_len);
        free(buf);
        return 0;
    }
    if (elements->elements[elem_index].data != NULL) {
        if (memcmp(buf, elements->elements[elem_index].data, out_len) != 0) {
            ERROR("outbuf not same as inbuf");
            free(buf);
            return 0;
        }
    }
    free(buf);
    return 1;
}

int do_run(char ** cmds, int num_cmds) {
    int c;
    char * id;
    int ret = 1;
    int get_each_add = 0;
    struct fdset * fdset = NULL;
    struct freemap * freemap = NULL;
    struct mrbufstuffer * mrbfstf = NULL;

    struct tu_data_elements_list elements_list = TU_DATA_ELEMENTS_EMPTY_LIST;

    int max_len = DEFAULT_MAX_LEN;
    unsigned num_elements = 0;

    id = cmds[0];
    if (verbose) {
        fprintf(stderr, "... Starting run '%s'\n", id);
    }
    fdset = fdset_new(0777, 1);
    if (fdset == NULL) {
        fprintf(stderr, "Error creating fdset\n");
        goto ERROR;
    }
    fdset_set_type_name(fdset, MRBUF_TEST_FD_TYPE, "mrbuftest", 
      strvlen("mrbuftest"), 1 /* writeable */);

    freemap = freemap_new(FREEMAP_STRATEGY_FIRST, 0 /* append */, fdset,
      fdset_freemap_addfile);
    if (freemap == NULL) {
        fprintf(stderr, "Error creating freemap\n");
        goto ERROR;
    }

    mrbfstf = mrbfstf_new(freemap, fdset, MRBUF_TEST_FD_TYPE, threshold);
    if (mrbfstf == NULL) {
        fprintf(stderr, "Error creating mrbufstuffer\n");
        goto ERROR;
    }

    /* ready to start processing commands */
    for (c = 1; c < num_cmds; c++) {
        char * cmd = cmds[c];

        if (verbose)
            fprintf(stderr, "... command '%s'\n", cmd);
        /* 
         *  ADD=<num>
         */
        if (strncmp(cmd, "ADD=", 4) == 0) {
            struct tu_data_elements * elements;
            int num_adds = atoi(cmd + 4);
            int i;
            if (num_adds < 1) {
                fprintf(stderr, "Invalid ADD command\n");
                goto ERROR;
            }
            elements = tu_generate_elements_or_die(num_adds, max_len);
            elements->next = NULL;
            tu_add_elements_to_list(&elements_list, elements);
            for (i = 0; i < num_adds; i++) {
                unsigned index = 0;
                enum mrbfstf_ret mr_ret;
                mr_ret = mrbfstf_add(mrbfstf, elements->elements[i].data, 
                  elements->elements[i].len, &index);
                if (mr_ret != MRBFSTF_OK) {
                    ERROR1("return value of '%d'", mr_ret);
                    goto FAIL;
                }
                if (index != num_elements) {
                    ERROR2("index %u, num_elements %u", index, num_elements);
                    goto FAIL;
                }
                num_elements++;
                if (get_each_add) {
                    int ret;

                    ret = check_index(mrbfstf, index, elements, i);
                    if (ret == -1)
                        goto ERROR;
                    else if (ret == 0)
                        goto FAIL;
                }
            }
        }

        /*
         *  ADD_NULL
         */
        else if (strncmp(cmd, "ADD_NULL=", 9) == 0) {
            struct tu_data_elements * elements;
            int num_adds = atoi(cmd + 9);
            int i;
            if (num_adds < 1) {
                fprintf(stderr, "Invalid ADD_NULL command\n");
                goto ERROR;
            }
            elements = tu_generate_null_elements_or_die(num_adds);
            elements->next = NULL;
            tu_add_elements_to_list(&elements_list, elements);
            for (i = 0; i < num_adds; i++) {
                unsigned index = 0;
                enum mrbfstf_ret mr_ret;
                mr_ret = mrbfstf_add(mrbfstf, elements->elements[i].data, 
                  elements->elements[i].len, &index);
                if (mr_ret != MRBFSTF_OK) {
                    ERROR1("return value of '%d'", mr_ret);
                    goto FAIL;
                }
                if (index != num_elements) {
                    ERROR2("index %u, num_elements %u", index, num_elements);
                    goto FAIL;
                }
                num_elements++;
                if (get_each_add) {
                    int ret;

                    ret = check_index(mrbfstf, index, elements, i);
                    if (ret == -1)
                        goto ERROR;
                    else if (ret == 0)
                        goto FAIL;
                }
            }
        }

        /*
         *  CHECK
         */
        else if (strncmp(cmd, "CHECK", 5) == 0) {
            struct tu_data_elements * elements;
            unsigned index;

            for (index = 0, elements = elements_list.head; elements != NULL;
              elements = elements->next) {
                unsigned i;
                for (i= 0; i < elements->num_elements; i++, index++) {
                    int ret;

                    ret = check_index(mrbfstf, index, elements, i);
                    if (ret == -1)
                        goto ERROR;
                    else if (ret == 0)
                        goto FAIL;
                }
            }
        }

        /*
         *  GET_EACH_ADD
         */
        else if (strncmp(cmd, "GET_EACH_ADD", 12) == 0) {
            get_each_add = 1;
        }

        /*
         *  NO_GET_EACH_ADD
         */
        else if (strncmp(cmd, "NO_GET_EACH_ADD", 15) == 0) {
            get_each_add = 0;
        }

        /*
         *  DUMP_LOAD
         */
        else if (strncmp(cmd, "DUMP_LOAD", 9) == 0) {
            enum mrbfstf_ret mr_ret;
            unsigned d_header_fileno;
            unsigned long d_header_offset;
            unsigned d_header_size;

            mr_ret = mrbfstf_write(mrbfstf, &d_header_fileno,
              &d_header_offset, &d_header_size);
            if (mr_ret != MRBFSTF_OK) {
                ERROR1("return code of '%d'", mr_ret);
                goto FAIL;
            }
            mrbfstf_delete(&mrbfstf);
            freemap_delete(freemap);
            freemap = freemap_new(FREEMAP_STRATEGY_FIRST, 0 /* append */, 
              fdset, fdset_freemap_addfile);
            if (freemap == NULL) {
                fprintf(stderr, "Error creating freemap\n");
                goto ERROR;
            }
            mrbfstf = mrbfstf_load(d_header_fileno, d_header_offset,
              d_header_size, num_elements, freemap,
              fdset, MRBUF_TEST_FD_TYPE, threshold, 0, &mr_ret);
            if (mr_ret != MRBFSTF_OK) {
                ERROR1("return value of '%d'\n", mr_ret);
                goto FAIL;
            }
        }

        /*
         *  MAXLEN=<len>
         */
        else if (strncmp(cmd, "MAXLEN=", 7) == 0) {
            int new_max_len = atoi(cmd + 7);
            if (new_max_len >= 0)
                max_len = new_max_len;
            else {
                fprintf(stderr ,"invalid MAXLEN command\n");
                goto ERROR;
            }
        } else {
            fprintf(stderr, "invalid command\n");
            goto ERROR;
        }
    }

    goto END;

FAIL:
    ret = 0;
    goto END;

ERROR:
    ret = -1;

END:
    if (fdset != NULL) {
        int i;
        for (i = 0; i < 256; i++) 
            fdset_unlink(fdset, MRBUF_TEST_FD_TYPE, i);
        fdset_delete(fdset);
    }
    if (freemap != NULL) {
        freemap_delete(freemap);
    }
    if (mrbfstf != NULL) {
        mrbfstf_delete(&mrbfstf);
    }
    if (elements_list.head != NULL) {
        struct tu_data_elements * curr, * next;
        for (curr = elements_list.head; curr != NULL; curr = next) {
            next = curr->next;
            tu_delete_elements(curr);
        }
    }
    return ret;
}
