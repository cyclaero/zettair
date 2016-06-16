/* stem.c is a small tool for stemming terms.  Invoke to enter terms
 * on the command line, or optionally from a file (use -i file or
 * --input=file).  Stemming algorithm (light by default) can be
 * changed using -s [eds|light|porters] or --stem=eds|light|porters.
 *
 * written nml 2006-08-21
 *
 */

#include "stem.h"
#include "str.h"
#include "getlongopt.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *input = stdin;
    char buf[BUFSIZ + 1];
    char *str;
    char **word;
    unsigned int words,
                 i;
    void (*stem)(void *opaque, char *term) = stem_light;
    struct getlongopt *parser;   /* option parser */
    int id;                      /* id of parsed option */
    const char *arg;             /* argument of parsed option */
    enum getlongopt_ret ret;     /* return value from option parser */

    struct getlongopt_opt opts[] = {
        {"input", 'i', GETLONGOPT_ARG_REQUIRED, 'i'},
        {"stem", 's', GETLONGOPT_ARG_REQUIRED, 's'}
    };

    if ((parser = getlongopt_new(argc - 1, (const char **) &argv[1], opts, 
        sizeof(opts) / sizeof(*opts)))) {
        /* succeeded, do nothing */
    } else {
        fprintf(stderr, "failed to initialise options parser\n");
        return EXIT_FAILURE;
    }

    while ((ret = getlongopt(parser, &id, &arg)) == GETLONGOPT_OK) {
        switch (id) {
        case 'i':
            /* take input from another file */
            if ((input = fopen(arg, "rb"))) {
                /* succeeded, do nothing */
            } else {
                fprintf(stderr, "failed to open file '%s' for reading: %s\n", 
                  arg, strerror(errno));
                return EXIT_FAILURE;
            }
            break;

        case 's':
            if (!str_casecmp(arg, "light")) {
                stem = stem_light;
            } else if (!str_casecmp(arg, "eds")) {
                stem = stem_eds;
            } else if (!str_casecmp(arg, "porters") 
              || !str_casecmp(arg, "porter")) {
                stem = stem_porters;
            } else {
                fprintf(stderr, "unrecognised stemming algorithm '%s', valid "
                  "options are 'eds', 'light' and 'porters'\n", arg);
                return EXIT_FAILURE;
            }
            break;

        default:
            assert("can't get here" && 0);
            fprintf(stderr, "unrecognised option\n");
            return EXIT_FAILURE;
        }
    }
    getlongopt_delete(parser);

    buf[BUFSIZ] = '\0';
    while (fgets(buf, BUFSIZ, input)) {
        char *rpos = buf, 
             *wpos = buf;

        /* remove punctuation from string */
        while (*rpos) {
            if (isalnum(*rpos) || isspace(*rpos)) {
                *wpos++ = tolower(*rpos);
            }
            rpos++;
        }
        *wpos = '\0';

        str_rtrim(buf);
        str = (char *) str_ltrim(buf);
        if (str_len(str)) {
            if ((word = str_split(str, " \t\v\n\r", &words))) {
                for (i = 0; i < words; i++) {
                    stem(NULL, word[i]);
                    printf("%s ", word[i]);
                }
                free(word);
            } else {
                fprintf(stderr, "failed to split line '%s'\n", buf);
                return EXIT_FAILURE;
            }
        }
        printf("\n");
    }

    fclose(input);
    return EXIT_SUCCESS;
}

