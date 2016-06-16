/* hashval.c prints the hash value of a gram given on the command line
 *
 * written nml 2003-03-06
 *
 */

#include "def.h"
#include "gramhash.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s gram\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("%u\n", hGetKey(argv[1], TABLESIZE));

    return EXIT_SUCCESS;
}
