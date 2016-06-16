/*
 *  Testing the vecarr module.
 *
 *  Each line of the input file is a simple command script.  First
 *  identifier is the name of the run.  The remaining are commands,
 *  possibly followed by "=<arg>".  The commands are:
 *
 *     ADD=<num>
 *         Add <num> num of elements
 *
 *     CHECK
 *         Check that all added elements exist
 *
 *     DUMP_LOAD
 *         Dump, then load, vecarr.
 *
 *   The following configuration directives may appear on a line by
 *   themselves:
 *
 *     @VERBOSE
 *         Switch to verbose mode
 *     @NOVERBOSE
 *         Switch out of verbose mode
 *     @DATATYPE {int|struct}
 *         Set the data type to INT (default) or STRUCT
 *     @VEC_MAX_LENGTH <len>
 *         Maximum length of in-memory vectors
 */

#include "firstinclude.h"
#include "test.h"
#include "testutils.h"
#include "vecarr.h"
#include "str.h"
#include "vec.h"
#include "error.h"
#include "_vecarr.h"

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define DEFAULT_SEED 59u
#define MAX_FILE_SIZE (2u * 1024u * 1024u * 1024u)
#define VECARR_TEST_FD_TYPE 71
#define MAX_VAL INT_MAX
#define MAX_DBL_VAL 10000.0
#define DEFAULT_VEC_MAX_LENGTH 100

static int verbose = 0;
static enum { INT, STRUCT, DOUBLE } datatype = INT;

static unsigned vec_max_length = DEFAULT_VEC_MAX_LENGTH;

struct data_struct {
    int a;
    int b;
};

union datatype {
    int i;
    struct data_struct s;
    double d;
};

/* ops for the different types. */
enum vecarr_ret int_load(struct vec * vec, void * data) {
    unsigned long int val;
    if (!vec_vbyte_read(vec, &val)) {
        if (VEC_LEN(vec) >= vec_vbyte_len(ULONG_MAX))
            return VECARR_FMT_ERROR;
        else
            return VECARR_SPACE_ERROR;
    }
    *((int *) data) = val;
    return VECARR_OK;
}

enum vecarr_ret int_store(struct vec * vec, const void * data) {
    int val = *((int *) data);
    if (!vec_vbyte_write(vec, val))
        return VECARR_SPACE_ERROR;
    else
        return VECARR_OK;
}

enum vecarr_ret struct_load(struct vec * vec, void * data) {
    unsigned long int val;
    struct data_struct * ds = data;
    struct vec mark;

    mark = *vec;
    if (!vec_vbyte_read(vec, &val)) {
        if (VEC_LEN(vec) >= vec_vbyte_len(ULONG_MAX)) {
            *vec = mark;
            return VECARR_FMT_ERROR;
        } else {
            *vec = mark;
            return VECARR_SPACE_ERROR;
        }
    }
    ds->a = val;
    val = 0;
    if (!vec_vbyte_read(vec, &val)) {
        if (VEC_LEN(vec) >= vec_vbyte_len(ULONG_MAX)) {
            *vec = mark;
            return VECARR_FMT_ERROR;
        } else {
            *vec = mark;
            return VECARR_SPACE_ERROR;
        }
    }
    ds->b = val;
    return VECARR_OK;
}

enum vecarr_ret struct_store(struct vec * vec, const void * data) {
    const struct data_struct * ds = data;
    struct vec mark;

    mark = *vec;
    if (!vec_vbyte_write(vec, ds->a) || !vec_vbyte_write(vec, ds->b)) {
        *vec = mark;
        return VECARR_SPACE_ERROR;
    } else
        return VECARR_OK;
}

static int fdset_freemap_addfile(void * opaque, unsigned int file,
  unsigned int *maxsize) {
    struct fdset * fdset = (struct fdset *) opaque;
    int fd;
    *maxsize = MAX_FILE_SIZE;
    fd = fdset_create(fdset, VECARR_TEST_FD_TYPE, file);
    if (fd == -EEXIST) {
        fd = fdset_pin(fdset, VECARR_TEST_FD_TYPE, file, 0, SEEK_CUR);
        if (fd < 0)
            return -1;
    }
    fdset_unpin(fdset, VECARR_TEST_FD_TYPE, file, fd);
    return 1;
}

int process_config(char * config) {
    if (strncmp(config, "VERBOSE", 7) == 0) {
        verbose = 1;
        fprintf(stderr, "... VERBOSE mode on\n");
    } else if (strncmp(config, "NOVERBOSE", 9) == 0) {
        verbose = 0;
    } else if (strncmp(config, "SEED", 4) == 0) {
        unsigned seed = atoi(config + 4);
        if (seed < 1)
            return 0;
        tu_init_rand_or_die(seed);
    } else if (strncmp(config, "DATATYPE", 8) == 0) {
        char * arg = config + 8;
        arg = (char *) str_ltrim(arg);
        str_rtrim(arg);
        if (strncmp(arg, "INT", 3) == 0) {
            datatype = INT;
        } else if (strncmp(arg, "STRUCT", 6) == 0) {
            datatype = STRUCT;
        } else if (strncmp(arg, "DOUBLE", 6) == 0) {
            datatype = DOUBLE;
        } else {
            ERROR1("unknown data type '%s'" ,arg);
            return 0;
        }
    } else if (strncmp(config, "VEC_MAX_LENGTH", 14) == 0) {
        unsigned max_length = atoi(config + 14);
        if (max_length < 1)
            return 0;
        vec_max_length = max_length;
    } else {
        return 0;
    }
    return 1;
}

int do_run(char ** cmds, int num_cmds) {
    int c;
    char * id;
    struct fdset * fdset = NULL;
    struct freemap * freemap = NULL;
    struct vecarr * vecarr = NULL;
    enum vecarr_ret va_ret;
    size_t element_size = 0;
    struct vecarr_ops ops;
    union datatype * data = NULL;
    unsigned data_size = 0;
    unsigned num_data = 0;
    int ret;

    id = cmds[0];
    if (verbose) {
        fprintf(stderr, "... Starting run '%s'\n", id);
    }
    fdset = fdset_new(0777, 1);
    if (fdset == NULL) {
        ERROR("creating fdset");
        goto ERROR;
    }
    fdset_set_type_name(fdset, VECARR_TEST_FD_TYPE, "vecarrtest",
      strlen("vecarrtest"), 1 /* writeable */);
    freemap = freemap_new(FREEMAP_STRATEGY_FIRST, 0 /* append */, fdset,
      fdset_freemap_addfile);
    if (freemap == NULL) {
        ERROR("creating freemap");
        goto ERROR;
    }

    switch (datatype) {
    case INT:
        element_size = sizeof(int);
        ops.load = int_load;
        ops.store = int_store;
        break;
    case STRUCT:
        element_size = sizeof(struct data_struct);
        ops.load = struct_load;
        ops.store = struct_store;
        break;
    case DOUBLE:
        element_size = sizeof(double);
        ops = vecarr_double_ops;
        break;
    }
    vecarr = vecarr_new(freemap, fdset, VECARR_TEST_FD_TYPE, element_size,
      ops, &va_ret);
    if (vecarr == NULL) {
        ERROR("create vecarr");
        goto ERROR;
    }
    vecarr->vec_max_length = vec_max_length;

    for (c = 1; c < num_cmds; c++) {
        char * cmd = cmds[c];

        if (verbose) 
            fprintf(stderr, "... command '%s'\n", cmd);

        /*
         *  ADD=<num>
         */
        if (strncmp(cmd, "ADD=", 4) == 0) {
            int num_adds = atoi(cmd + 4);
            unsigned d;

            if (num_adds < 1) {
                ERROR("invalid ADD command");
                goto ERROR;
            }
            while (num_data + num_adds > data_size) {
                if (data_size == 0)
                    data_size = 4096;
                else
                    data_size *= 2;
                if ( (data = realloc(data, sizeof(*data)
                          * data_size)) == NULL) {
                    ERROR("reallocating data");
                    exit(EXIT_FAILURE);
                }
            }
            for (d = 0; d < num_adds; d++) {
                int idat;
                struct data_struct sdat;
                double ddat;
                switch (datatype) {
                case INT:
                    idat = tu_rand_limit(MAX_VAL);
                    if (vecarr_add(vecarr, &idat) != VECARR_OK) {
                        ERROR("adding to vecarr");
                        goto ERROR;
                    }
                    data[num_data].i = idat;
                    break;
                case STRUCT:
                    sdat.a = tu_rand_limit(MAX_VAL);
                    sdat.b = tu_rand_limit(MAX_VAL);
                    if (vecarr_add(vecarr, &sdat) != VECARR_OK) {
                        ERROR("adding to vecarr");
                        goto ERROR;
                    }
                    data[num_data].s = sdat;
                    break;
                case DOUBLE:
                    ddat = tu_rand_double_limit((double) MAX_DBL_VAL);
                    if (vecarr_add(vecarr, &ddat) != VECARR_OK) {
                        ERROR("adding double to vecarr");
                        goto ERROR;
                    }
                    data[num_data].d = ddat;
                }
                num_data++;
            }
        }

        /*
         *  CHECK
         */
        else if (strncmp(cmd, "CHECK", 5) == 0) {
            unsigned d;

            for (d = 0; d < num_data; d++) {
                int idat;
                struct data_struct sdat;
                double ddat;
                enum vecarr_ret va_ret;
                switch (datatype) {
                case INT:
                    va_ret = vecarr_get(vecarr, d, &idat);
                    break;
                case STRUCT:
                    va_ret = vecarr_get(vecarr, d, &sdat);
                    break;
                case DOUBLE:
                    va_ret = vecarr_get(vecarr, d, &ddat);
                    break;
                default:
                    assert("can't get here" && 0);
                    return -1;
                }
                if (va_ret != VECARR_OK) {
                    ERROR("retrieving data from vecarr");
                    goto ERROR;
                }
                switch (datatype) {
                case INT:
                    if (idat != data[d].i) {
                        ERROR4("vecarr_get retrieved %d, should have "
                          "retrieved %d, on element %d of %d", 
                          idat, data[d].i, d, num_data);
                        goto FAILURE;
                    }
                    break;
                case STRUCT:
                    if (sdat.a != data[d].s.a || sdat.b != data[d].s.b) {
                        ERROR4("vecarr_get retrieved [%d, %d], should "
                          "have retrieved [%d, %d]", sdat.a, sdat.b,
                          data[d].s.a, data[d].s.b);
                        ERROR1("element number is %u", d);
                        goto FAILURE;
                    }
                    break;
                case DOUBLE:
                    /* allow for loss of precision */
                    if (fabs(ddat - data[d].d) > 0.2) {
                        ERROR2("vecarr_get retrieved %lf, should "
                          "have retrieved %lf", ddat, data[d].d);
                        goto FAILURE;
                    }
                }
            }
        }

        /*
         *  DUMP_LOAD
         */
        else if (strncmp(cmd, "DUMP_LOAD", 9) == 0) {
            enum vecarr_ret va_ret;
            unsigned fileno_out;
            unsigned long offset_out;
            unsigned len_out;

            va_ret = vecarr_save(vecarr, &fileno_out, &offset_out, &len_out);
            if (va_ret != VECARR_OK) {
                ERROR("saving vecarr");
                goto ERROR;
            }
            vecarr_delete(&vecarr);
            freemap_delete(freemap);
            /* XXX freemap_malloc */
            freemap = freemap_new(FREEMAP_STRATEGY_FIRST, 0 /* append */, 
              fdset, fdset_freemap_addfile);
            vecarr = vecarr_prep(freemap, fdset, VECARR_TEST_FD_TYPE,
              element_size, ops, num_data, fileno_out, offset_out,
              len_out, &va_ret);
            if (vecarr == NULL) {
                ERROR("load vecarr");
                goto ERROR;
            }
        }

        else {
            ERROR1("unknown command: '%s'", cmd);
            goto ERROR;
        }
    }

    ret = 1;
    goto END;

FAILURE:
    ret = 0;
    goto END;

ERROR:
    ret = -1;
    goto END;

END:
    if (fdset != NULL) {
        int i;
        for (i = 0; i < 256; i++) 
            fdset_unlink(fdset, VECARR_TEST_FD_TYPE, i);
        fdset_delete(fdset);
    }
    if (freemap != NULL) {
        freemap_delete(freemap);
    }
    if (vecarr != NULL) {
        vecarr_delete(&vecarr);
    }
    if (data != NULL)
        free(data);
    return ret;
}

int test_file(FILE * fp, int argc, char ** argv) {
    char buf[4096];
    int line_num = 0;
    char * ptr;
    int all_passed = 1;

    tu_init_rand_or_die(DEFAULT_SEED);

    while (fgets((char *) buf, 4095, fp)) {
        line_num++;
        ptr = (char *) str_ltrim(buf);
        str_rtrim(ptr);
        if (*ptr == '@') {
            if (!process_config(ptr + 1))
                fprintf(stderr, "Error with config on line %d, '%s'\n",
                  line_num, ptr);
        } else if (*ptr != '#' && *ptr != '\0') {
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
