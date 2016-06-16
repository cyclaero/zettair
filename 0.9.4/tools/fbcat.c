/* fbcat measures the speed of reading a file character by character
 * via FileBuf functions vs by stdio with expanded buffer
 *
 * written nml 2003-02-27
 *
 */

#include "FileBuf.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int stdiocat(FILE* output, FILE* input) {
    int c;

    while ((c = getc(input)) != EOF) {
        putc(c, output);
    }

    return 1;
}

int fbcat(FILE* output, FB_ROOT* input) {
    int c;

    while ((c = cGetChar(input)) != EOF) {
        putc(c, output);
    }

    return 1;
}

void print_usage(FILE* output, const char* progname) {
    fprintf(output, "usage: %s [-m bufsize] [stdio|fb] filename+\n", progname);
}

int main(int argc, char** argv) {
    long int bufsize = 4096;
    char* buf;
    unsigned int i = 1;
    char* end;
    int stdio;
    FILE* fp;
    FB_ROOT* fbfp;

    if (argc < 3) {
        print_usage(stderr, *argv);
        return EXIT_FAILURE;
    }

    if ((argc > 4) && !strcmp("-m", argv[1])) {
        if (((bufsize = strtol(argv[2], &end, 10)) < UINT_MAX) 
          && (bufsize > 0) && (*end == '\0')) {
            i = 3;
        } else {
            fprintf(stderr, "couldn't read -m argument '%s'\n", argv[2]);
            print_usage(stderr, *argv);
            return EXIT_FAILURE;
        }
    }

    /* read the method */
    if (!strcmp(argv[i], "stdio")) {
        stdio = 1;
        i++;
    } else if (!strcmp(argv[i], "fb")) {
        stdio = 0;
        i++;
    } else {
        fprintf(stderr, "couldn't read method argument '%s'\n", argv[i]);
        print_usage(stderr, *argv);
        return EXIT_FAILURE;
    }

    if (((argc - i) > 0) && !stdio) {
        for (; i < argc; i++) {
            if ((fbfp = cOpen(argv[i], C_READ, bufsize, C_NO_FS))) {
                fbcat(stdout, fbfp);
                cClose(fbfp);
            } else {
                perror(argv[i]);
                return EXIT_FAILURE;
            }
        }
    } else if (((argc - i) > 0) && stdio) {
        for (; i < argc; i++) {
            if ((fp = fopen(argv[i], "rb"))
              && (buf = malloc(bufsize)) 
              && (setvbuf(fp, buf, _IOFBF, bufsize) == 0)) {
                stdiocat(stdout, fp);
                fclose(fp);
            } else {
                perror(argv[i]);
                return EXIT_FAILURE;
            }
        }
    } else {
        fprintf(stderr, "no files to cat!\n");
        print_usage(stderr, *argv);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

