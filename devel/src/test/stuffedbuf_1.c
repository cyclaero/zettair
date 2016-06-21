/*
 *  tests the stuffedbuf module.
 *
 *  Since the stuffedbuf is read-only, we have to use the bufstuffer
 *  to create the bufs, so we are also effectively testing that
 *  module.
 *
 *  The following cases need to be checked:
 *
 *  a. A buf with no elements.
 *  b. A buf with only empty elements.
 *  c. A buf with a single element.
 *  d. A buf with multiple elements.
 *
 *  Each case is launched by <keyword> <args ...> lines in the
 *  test input file.  The input format for each case is:
 *
 *  a. NO_ELEMENTS
 *  b. EMPTY_ELEMENTS <num-elements>
 *  c. SINGLE_ELEMENT <element-len>
 *  d. MULTIPLE_ELEMENTS <num-elements> <max-len>
 *
 *  There is also a timing test:
 *
 *  TIMING <num-elements> <max-len> <num-iterations>
 *
 *  There are also some special configuration directives.  These start
 *  with "@":
 *
 *  @SEED <seed>
 *     -- seed the random number generator with integer <seed>
 *  @INPUT <file>
 *     -- take sample input from <file>, not randomly generated.
 *  @VERBOSE
 *     -- turn verbose mode on
 *  @NOVERBOSE
 *     -- turn verbose mode off
 */

#include "zettair.h"
#include "test.h"
#include "str.h"
#include "lcrand.h"
#include "error.h"
#include "bufstuffer.h"
#include "stuffedbuf.h"
#include "testutils.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>

typedef int (*test_case_fn)(char * conf_line);

static int no_elements_test(char * conf_line);
static int empty_elements_test(char * conf_line);
static int single_element_test(char * conf_line);
static int multiple_elements_test(char * conf_line);
static int timing_test(char * conf_line);

struct {
    char * cmd;
    test_case_fn fn;
} test_cases[] = {
    { "NO_ELEMENTS",       no_elements_test },
    { "EMPTY_ELEMENTS",    empty_elements_test },
    { "SINGLE_ELEMENT",    single_element_test },
    { "MULTIPLE_ELEMENTS", multiple_elements_test },
    { "TIMING",            timing_test },
    { NULL, NULL }
};

/* copied from bufstuffer_1.c */

#define DEFAULT_SEED 43u

static int verbose = 0;

static FILE * input_file = NULL;

/* end copied from bufstuffer_1.c */

static int mkstemp_or_die(char * template);

static int dump_elements(struct tu_data_elements * elements, int fd,
  unsigned * len);

static int check(struct stuffedbuf * stfbf, 
  struct tu_data_elements * elements);

static int test_case(unsigned num_elements, unsigned max_len) {
    struct tu_data_elements * elements 
        = tu_generate_elements_or_die(num_elements, max_len);
    char tmpfile_template[] = "sbtest_XXXXXX";
    int fd = mkstemp_or_die(tmpfile_template);
    unsigned dump_len;
    struct stuffedbuf * stfbf = NULL;
    enum stfbf_ret ret;
    int check_ret;

    if (!dump_elements(elements, fd, &dump_len))
        return 0;
    lseek(fd, 0, SEEK_SET);
    stfbf = stfbf_load(fd, dump_len, num_elements, &ret);
    close(fd);
    unlink(tmpfile_template);
    if (stfbf == NULL || ret != STFBF_OK) {
        ERROR3("stfbf_load, %u elements of max_len %u, status %d\n",
          num_elements, max_len, ret);
        tu_delete_elements(elements);
        return 0;
    }
    check_ret = check(stfbf, elements);
    stfbf_delete(&stfbf);
    tu_delete_elements(elements);
    return check_ret;
}

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


/* test cases */
static int no_elements_test(char * conf_line) { 
    return test_case(0, 0);
}

static int empty_elements_test(char * conf_line) { 
    unsigned num_elements;
    if ( (sscanf(conf_line, "%u", &num_elements)) < 1)
        return -1;
    return test_case(num_elements, 0);
}

static int single_element_test(char * conf_line) { 
    unsigned max_len;
    if ( (sscanf(conf_line, "%u", &max_len)) < 1)
        return -1;
    return test_case(1, max_len);
}

static int multiple_elements_test(char * conf_line) { 
    unsigned num_elements;
    unsigned max_len;
    if ( (sscanf(conf_line, "%u %u", &num_elements, &max_len)) < 2)
        return -1;
    return test_case(num_elements, max_len);
}

static int timing_test(char * conf_line) {
    unsigned num_elements;
    unsigned max_len;
    unsigned num_iterations;
    char tmpfile_template[] = "sbtime_XXXXXX";
    int fd = mkstemp_or_die(tmpfile_template);
    unsigned dump_len;
    struct tu_data_elements * elements = NULL; 
    unsigned i;
    char * buf;
    unsigned buf_len;
    unsigned out_len;
    int ret;
    struct timeval start;
    struct timeval end;
    unsigned full_len = 0;

    if ( (sscanf(conf_line, "%u %u %u", &num_elements, &max_len,
              &num_iterations)) < 3)
        return -1;
    elements = tu_generate_elements_or_die(num_elements, max_len);
    for (i = 0; i < num_elements; i++)
        full_len += elements->elements[i].len;
    if (!dump_elements(elements, fd, &dump_len))
        return 0;
    buf_len = max_len * 1.5 + 3;
    buf = malloc(buf_len);
    if (buf == NULL)
        return -1;
    gettimeofday(&start, NULL);
    for (i = 0; i < num_iterations; i++) {
        struct stuffedbuf * stfbf = NULL;
        unsigned int index;

        lseek(fd, 0, SEEK_SET);
        stfbf = stfbf_load(fd, dump_len, num_elements, &ret);
        index = tu_rand_limit(num_elements);
        if ( (ret = stfbf_get(stfbf, index, buf, buf_len, &out_len)) 
          != STFBF_OK) {
            ERROR1("stfbf_get returned %d", ret);
            return 0;
        }
        stfbf_delete(&stfbf);
    }
    gettimeofday(&end, NULL);
    if (verbose) {
        unsigned long diff = (end.tv_sec - start.tv_sec) * 1000000
            + end.tv_usec - start.tv_usec;
        unsigned long usecs_per_get = diff / num_iterations;
  /*      double secs_per_iteration =
            ((double) (end.tv_sec - start.tv_sec) * 1000000 +
            end.tv_usec - start.tv_usec) / (num_iterations * 1000000); */
        fprintf(stderr, "TIMING: %u elements, %u max_len "
          "(full:dump:ratio size %u:%u:%.3f): 0.%06lu secs/get\n", 
          num_elements, max_len, full_len, dump_len,
          (double)full_len / dump_len, usecs_per_get);
    }
    unlink(tmpfile_template);
    tu_delete_elements(elements);
    free(buf);
    return 1;
}

/* utilities */
static int mkstemp_or_die(char * template) {
    int fd = mkstemp(template);
    if (fd < 0) {
        perror("ERROR: failed to make temporary file");
        exit(EXIT_FAILURE);
    }
    return fd;
}

static int dump_elements(struct tu_data_elements * elements, int fd,
  unsigned * len) {
    struct bufstuffer * bfstf;
    unsigned total_elems_len = 0;
    unsigned i;
    int ret;

    for (i = 0; i < elements->num_elements; i++)
        total_elems_len += elements->elements[i].len;
    if ( (bfstf = bfstf_new((unsigned) (total_elems_len * 1.5) + 3))
      == NULL) {
        perror("ERROR: allocating bufstuffer");
        return 0;
    }
    for (i = 0; i < elements->num_elements; i++) {
        if ( (ret = bfstf_add(bfstf, elements->elements[i].data,
              elements->elements[i].len)) != BFSTF_OK) {
            ERROR1("bfstf_add returned %d", ret);
            bfstf_delete(&bfstf);
            return 0;
        }
    }
    if ( (ret = bfstf_finished(bfstf, len)) != BFSTF_OK) {
        ERROR1("bfstf_finished returned %d", ret);
        bfstf_delete(&bfstf);
        return 0;
    }
    if ( (ret = bfstf_dump(bfstf, fd)) != BFSTF_OK) {
        ERROR1("bfstf_dump returned %d", ret);
        bfstf_delete(&bfstf);
        return 0;
    }
    bfstf_delete(&bfstf);
    return 1;
}

static int check(struct stuffedbuf * stfbf, 
  struct tu_data_elements * elements) {
    unsigned i;
    static char * buf = NULL;
    static int buf_len = 0;
    unsigned out_len = 0;
    int ret;

    for (i = 0; i < elements->num_elements; i++) {
        unsigned el_len = elements->elements[i].len;
        if (el_len > buf_len) {
            if ( (buf = realloc(buf, el_len)) == NULL) {
                perror("reallocating buffer");
                exit(EXIT_FAILURE);
            }
        }
        if (el_len > 1) {
            /* check that it rejects buffers that are too small */
            if ( (ret = stfbf_get(stfbf, i, buf, el_len - 1, &out_len))
              != STFBF_BUFSIZE_ERROR) {
                ERROR1("stfbf_get with too small buffer returned %d, not "
                  "STFBF_BUFSIZE_ERROR", ret);
                return 0;
            }
            if (out_len != el_len) {
                ERROR2("stfbf_get returned wrong length for element, should "
                  "be %u, returned %u", el_len, out_len);
                return 0;
            }
        }
        if ( (ret = stfbf_get(stfbf, i, buf, el_len, &out_len)) != STFBF_OK) {
            ERROR1("stfbf_get returned %d, not STFBF_OK", ret);
            return 0;
        }
        if (out_len != el_len) {
            ERROR2("stfbf_get returned wrong length for element, should "
              "be %u, returned %u", el_len, out_len);
            return 0;
        }
        if (memcmp(buf, elements->elements[i].data, el_len) != 0) {
            ERROR("stuffed and unstuffed buffers differ");
            return 0;
        }
    }
    return 1;
}
