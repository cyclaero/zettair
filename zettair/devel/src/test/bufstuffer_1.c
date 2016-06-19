/*
 *  tests the bufstuffer module.
 *
 *  a bufstuffer is write-only; the buffer is read back using
 *  the stuffedbuf module.  This test therefore can only run
 *  the module through its paces; it can't do much to verify
 *  the correctness of it.  That will be done in a separate
 *  tester, once the stuffedbuf module is written.
 *
 *  The general test procedure is as follows:
 *
 *  1. Created a new bufstuffer.
 *  2. Generate some random data.
 *  3. Stuff the random data into the bufstuffer.
 *  4. Write the stuff out to disk.
 *  5. Delete the bufstuffer object.
 *
 *  The following cases need to be checked:
 *
 *  a. Create a bufstuffer with a threshold of 0.  This should
 *  accept a single stuff, then immediately declare itself full.
 *
 *  b. Stuff a single object that, even compressed, is definitely
 *  bigger than the bufstuffer threshold.  This object should be
 *  accepted, but the bufstuffer should refuse future input.
 *
 *  c. Create a bufstuffer with a threshold of 1, and stuff 1000
 *  0-length objects into it.  This bufstuffer should never declare
 *  itself full (perhaps undesirable, but the current behaviour).
 *  Make sure this can be dumped to disk.
 *
 *  d. Create a bufstuff with a low threshold, and stuff lots of
 *  1-length object into it.  The bufstuffer should eventually
 *  declare itself full.
 *
 *  e. Make sure that, once a bufstuffer has declared itself full,
 *  it keeps declaring itself full.
 *
 *  f. Make sure that, once a bufstuffer has been marked as finished, 
 *  it cannot be added to.
 *
 *  g. Stuff a NULL buffer in, with len 0, and make sure it is accepted.
 *
 *  These edge cases are launched by <keyword> <args ...> lines in
 *  the test input file.  The input format for each case is 
 *  described here.
 *
 *  a. ZERO_THRESHOLD
 *  b. BIG_STUFF <threshold> <big-object-size>
 *  c. ZERO_LEN_INPUTS <threshold> <num-inputs>
 *  d. ONE_LEN_INPUTS <threshold> <num-inputs>
 *  e. ONCE_FULL_ALWAYS_FULL <threshold> <num-inputs> <max-len>
 *  f. ONCE_FINISHED_NOT_WRITEABLE <threshold> <num-inputs> <max-len>
 *  g. NULL_BUF
 *
 *  There are also some special configuration directives.  These
 *  start with "@":
 *
 *  @SEED <seed>
 *     -- seed the random number generator with the integer <seed>
 *  @INPUT <file>
 *     -- take sample input from <file>, not randomly generated
 *  @VERBOSE
 *     -- turn verbose mode on (starts off)
 *  @NOVERBOSE
 *     -- turn verbose mode off
 */

#include "firstinclude.h"
#include "test.h"
#include "str.h"
#include "lcrand.h"
#include "error.h"
#include "bufstuffer.h"
#include "testutils.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

typedef int (*test_case_fn)(char * conf_line);

static int zero_threshold_test(char * conf_line);
static int big_stuff_test(char * conf_line);
static int zero_len_inputs_test(char * conf_line);
static int one_len_inputs_test(char * conf_line);
static int once_full_always_full_test(char * conf_line);
static int once_finished_not_writeable_test(char * conf_line);
static int null_buf_test(char * conf_line);

struct {
    char * cmd;
    test_case_fn fn;
} test_cases[] = {
    { "ZERO_THRESHOLD", zero_threshold_test },
    { "BIG_STUFF", big_stuff_test },
    { "ZERO_LEN_INPUTS", zero_len_inputs_test },
    { "ONE_LEN_INPUTS", one_len_inputs_test },
    { "ONCE_FULL_ALWAYS_FULL", once_full_always_full_test },
    { "ONCE_FINISHED_NOT_WRITEABLE", once_finished_not_writeable_test },
    { "NULL_BUF", null_buf_test },
    { NULL, NULL }
};

#define DEFAULT_SEED 42u

static int verbose = 0;

static FILE * input_file = NULL;

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
            } else {
                fprintf(stderr, "Unknown configuration directive '%s' "
                  "on line %d\n", ptr, line_num);
            }
        } else {
            int i;
            for (i = 0; test_cases[i].cmd != NULL; i++) {
                char * cmd = test_cases[i].cmd;
                if (strncmp(ptr, cmd, strvlen(cmd)) == 0) {
                    char * args = (char *) str_ltrim(buf + strvlen(cmd));
                    int ret;
                    if (verbose)
                        fprintf(stderr, "... Running %s\n", cmd);
                    ret = test_cases[i].fn(args);
                    if (ret < 0) {
                        fprintf(stderr, "Invalid command format, line %d\n",
                          line_num);
                    } else if (ret == 0) {
                        all_passed = 0;
                    }
                    break;
                }
            }
            if (test_cases[i].cmd == NULL) {
                fprintf(stderr, "Unknown command '%s' on line %d\n",
                  ptr, line_num);
            }
        }
    }
    return all_passed;
}

static struct bufstuffer * alloc_bfstf_or_die(unsigned int threshold) {
    struct bufstuffer * bfstf = bfstf_new(threshold);
    if (bfstf == NULL) {
        perror("Error on allocating bufstuffer");
        exit(EXIT_FAILURE);
    }
    return bfstf;
}

static int zero_threshold_test(char * conf_line) {
    /* no args */
    struct bufstuffer * bfstf = bfstf_new(0);
    char * data;
    int ret;
    int all_ret = 0;
    data = tu_get_rand_data(1);
    ret = bfstf_add(bfstf, data, 1);
    if (ret != BFSTF_FILLED) {
        ERROR1("ret code not BFSTF_FILLED, but %d", ret);
        goto END;
    }
    ret = bfstf_add(bfstf, data, 1);
    if (ret != BFSTF_FULL_ERROR) {
        ERROR1("ret code not BFSTF_FULL_ERROR, but %d", ret);
        goto END;
    }
    all_ret = 1;
END:
    bfstf_delete(&bfstf);
    return all_ret;
}

static int big_stuff_test(char * conf_line) {
    /* args: <threshold> <big-object-size> */
    unsigned int threshold;
    unsigned int big_object_size;
    struct bufstuffer * bfstf;
    char * data;
    int ret;
    int all_ret = 0;

    if ( (sscanf(conf_line, "%u %u", &threshold, &big_object_size)) < 2) 
        return -1;
    bfstf = alloc_bfstf_or_die(threshold);
    data = tu_get_rand_data(big_object_size);
    ret = bfstf_add(bfstf, data, big_object_size);
    if (ret != BFSTF_FILLED) {
        ERROR1("ret code not BFSTF_FILLED, but %d", ret);
        goto END;
    }
    ret = bfstf_add(bfstf, data, big_object_size);
    if (ret != BFSTF_FULL_ERROR) {
        ERROR1("ret code not BFSTF_FULL_ERROR, but %d", ret);
        goto END;
    }
    all_ret = 1;
END:
    bfstf_delete(&bfstf);
    return all_ret;
}

static int zero_len_inputs_test(char * conf_line) {
    /* args: <threshold> <num-inputs> */
    unsigned int threshold;
    unsigned int num_inputs;
    struct bufstuffer * bfstf;
    char data[1];
    int ret;
    int all_ret = 0;
    unsigned i;

    if ( (sscanf(conf_line, "%u %u", &threshold, &num_inputs)) < 2)
        return -1;
    bfstf = alloc_bfstf_or_die(threshold);
    for (i = 0; i < num_inputs; i++) {
        ret = bfstf_add(bfstf, data, 0);
        if (ret != BFSTF_OK) {
            ERROR2("ret code not BFSTF_OK, but %d, on %uth iteration",
              ret, i);
            goto END;
        }
    }
    all_ret = 1;
END:
    bfstf_delete(&bfstf);
    return all_ret;
}

static int one_len_inputs_test(char * conf_line) {
    /* args: <threshold> <num-inputs> */
    unsigned int threshold;
    unsigned int num_inputs;
    struct bufstuffer * bfstf;
    char * data;
    int ret;
    int all_ret = 0;
    unsigned i;
    int full_returned = 0;
    
    if ( (sscanf(conf_line, "%u %u", &threshold, &num_inputs)) < 2)
        return -1;
    bfstf = alloc_bfstf_or_die(threshold);
    for (i = 0; i < num_inputs; i++) {
        data = tu_get_rand_data(1);
        ret = bfstf_add(bfstf, data, 1);
        if (full_returned) {
            if (ret != BFSTF_FULL_ERROR) {
                ERROR2("ret code not BFSTF_FULL_ERROR, but %d, on %uth "
                  "iteration", ret, i);
                goto END;
            }
        } else if (ret == BFSTF_FILLED) {
            full_returned = 1;
        } else if (ret != BFSTF_OK) {
            ERROR2("ret code neither BFSTF_FILLED nor BFSTF_OK, but %d, on "
              "%uth iteration", ret, i);
            goto END;
        }
    }
    if (!full_returned) {
        ERROR("BFSTF_FILLED never returned\n");
        goto END;
    }
    all_ret = 1;
END:
    bfstf_delete(&bfstf);
    return all_ret;
}
static int once_full_always_full_test(char * conf_line) {
    /* args: <threshold> <num-inputs> <max-len>*/
    unsigned int threshold;
    unsigned int num_inputs;
    unsigned int max_len;
    struct bufstuffer * bfstf;
    int ret;
    int all_ret = 0;
    unsigned i;
    int full_returned = 0;

    if ( (sscanf(conf_line, "%u %u %u", &threshold, &num_inputs,
              &max_len)) < 3)
        return -1;
    bfstf = alloc_bfstf_or_die(threshold);
    /* NB almost exact copy of previous test */
    for (i = 0; i < num_inputs; i++) {
        unsigned len;
        char * data = tu_get_rand_data_rand_len(max_len, &len);
        ret = bfstf_add(bfstf, data, len);
        if (full_returned) {
            if (ret != BFSTF_FULL_ERROR) {
                ERROR2("ret code not BFSTF_FULL_ERROR, but %d, on %uth "
                  "iteration", ret, i);
                goto END;
            }
        } else if (ret == BFSTF_FILLED) {
            full_returned = 1;
        } else if (ret != BFSTF_OK) {
            ERROR2("ret code neither BFSTF_FILLED nor BFSTF_OK, but %d, on "
              "%uth iteration", ret, i);
            goto END;
        }
    }
    if (!full_returned) {
        ERROR("BFSTF_FILLED never returned\n");
        goto END;
    }
    all_ret = 1;
END:
    bfstf_delete(&bfstf);
    return all_ret;
}

static int once_finished_not_writeable_test(char * conf_line) {
    unsigned int threshold;
    unsigned int num_inputs;
    unsigned int max_len;
    struct bufstuffer * bfstf;
    int ret;
    int all_ret = 0;
    unsigned i;
    int full_returned = 0;
    char  tmpfile_template[] = "bstest_XXXXXX";
    int fd = -1;
    char * more_data;
    unsigned int output_len;
    unsigned int input_len = 0;
    struct stat stats;

    if ( (sscanf(conf_line, "%u %u %u", &threshold, &num_inputs,
              &max_len)) < 3)
        return -1;
    bfstf = alloc_bfstf_or_die(threshold);
    /* NB similar to previous */
    for (i = 0; i < num_inputs; i++) {
        unsigned len;
        char * data = tu_get_rand_data_rand_len(max_len, &len);
        ret = bfstf_add(bfstf, data, len);
        input_len += len;
        if (ret == BFSTF_FILLED) {
            full_returned = 1;
            break;
        } else if (ret != BFSTF_OK) {
            ERROR2("ret code neither BFSTF_FILLED nor BFSTF_OK, but %d, on "
              "%uth iteration", ret, i);
            goto END;
        }
    }

    fd = mkstemp(tmpfile_template);
    if (fd < 0) {
        perror("making temporary file");
        goto END;
    }
    if ( (ret = bfstf_finished(bfstf, &output_len)) != BFSTF_OK) {
        ERROR1("bfstf_finished returned %d, not BFSTF_OK", ret);
        goto END;
    }
    more_data = tu_get_rand_data(1);
    if ( (ret = bfstf_add(bfstf, more_data, 1)) != BFSTF_FINISHED_ERROR) {
        ERROR1("ret code not BFSTF_FINISHED_ERROR, but %d", ret);
        goto END;
    }
    if ( (ret = bfstf_dump(bfstf, fd)) != BFSTF_OK) {
        ERROR1("bfstf_dump returned %d, not BFSTF_OK", ret);
        goto END;
    }
    fstat(fd, &stats);
    if (stats.st_size != output_len) {
        ERROR2("Size of file '%lu' != reported output len '%lu'\n",
          stats.st_size, output_len);
        goto END;
    }
    if (verbose) {
        fprintf(stderr, "... %u bytes in, %u bytes out\n", input_len,
          output_len);
    }
    
    /* should try dumping again, make sure you can, then read both
       dumped files back in, and make sure they're the same... */

    all_ret = 1;
END:
    if (fd != -1) {
        close(fd);
        unlink(tmpfile_template);
    }
    bfstf_delete(&bfstf);
    return all_ret;
}

static int null_buf_test(char * conf_line) {
    /* no args */
    struct bufstuffer * bfstf;
    enum bfstf_ret ret;

    bfstf = alloc_bfstf_or_die(0);
    ret = bfstf_add(bfstf, NULL, 0);
    if (ret != BFSTF_OK) {
        ERROR1("ret code not BFSTF_OK, but %d", ret);
        return 0;
    }
    bfstf_delete(&bfstf);
    return  1;
}
