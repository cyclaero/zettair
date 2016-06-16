#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "mlparse.h"

#define TEST(cond, descript) if (!(cond)) {\
    fprintf(stderr, "%s\n", descript); \
    return 0; \
}

int test_hanging_tag() {
    const char *txt = "<html";
    struct mlparse parser;
    char buf[53];
    unsigned len;
    enum mlparse_ret ret;

    mlparse_new(&parser, 50, 200);
    parser.next_in = txt;
    parser.avail_in = strlen(txt);
    ret = mlparse_parse(&parser, buf, &len, 1);
    TEST(ret == MLPARSE_INPUT, "Failed to ask for more input!");
    mlparse_eof(&parser);
    ret = mlparse_parse(&parser, buf, &len, 1);
    TEST(ret != MLPARSE_INPUT, "Asked for more input after mlparse_eof()!");
    return 1;
}

int test_end_sentence() {
    const char * txt = "<p>Hello there.</p>";
    struct mlparse parser;
    char buf[53];
    unsigned len;
    enum mlparse_ret ret;

    mlparse_new(&parser, 50, 200);
    parser.next_in = txt;
    parser.avail_in = strlen(txt);
    ret = mlparse_parse(&parser, buf, &len, 1);
    TEST(ret == MLPARSE_TAG, "Not tag");
    ret = mlparse_parse(&parser, buf, &len, 1);
    TEST(ret == MLPARSE_WORD, "Not word");
    ret = mlparse_parse(&parser, buf, &len, 1);
    TEST(ret & MLPARSE_END, "Not end of sentence");
    ret = mlparse_parse(&parser, buf, &len, 1);
    TEST(ret & MLPARSE_TAG, "Not tag");
    return 1;
}

int test_file(FILE *fp, int argc, char **argv) {
    int all_ok = 1;

    all_ok &= test_hanging_tag();
    all_ok &= test_end_sentence();
    return all_ok;
}
    
