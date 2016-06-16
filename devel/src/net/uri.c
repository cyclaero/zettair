/* uri.c implements the operations from uri.h
 *
 * written nml 2006-02-17
 *
 */

#include "uri.h"
#include "ascii.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum uri_seps {
    URI_SEP_SCHEME = (1 << 0),   /* the scheme: seperator */
    URI_SEP_HIER = (1 << 1),     /* the //hier seperator */
    URI_SEP_USERINFO = (1 << 2), /* the userinfo@ seperator */
    URI_SEP_PORT = (1 << 3),     /* the :port seperator */
    URI_SEP_QUERY = (1 << 4),    /* the ?query seperator */
    URI_SEP_FRAG = (1 << 5)      /* the #fragment seperator */
    /* note that we don't include the path separator, because it's part
     * of the path */
};

enum uri_flags {
    URI_FLAG_REL = (1 << 0),     /* it's a relative URI */
    URI_FLAG_IPV4 = (1 << 1),    /* host part is an IPv4 address */
    URI_FLAG_IPV6 = (1 << 2),    /* host part is an IPv6 address */
    URI_FLAG_IPV = (1 << 3)      /* host part is an IP future address */
};

#define CASE_UNRESERVED \
         ASCII_CASE_LOWER: case ASCII_CASE_UPPER: case ASCII_CASE_DIGIT: \
    case '-': case '.': case '_': case '~'

#define CASE_SUBDELIMS \
         '!': case '$': case '&': case '\'': case '(': case ')': \
    case '*': case '+': case ',': case ';': case '='

/* static variable to keep track of the last line number where a parse
 * error occurred, for debugging purposes.  Not intended for serious use */
static unsigned int uri_parse_line_no;
static const char *uri_parse_char;

/* macro to exit parse function once an illegal character has been 
 * encountered */
#define CHAR_ERR() \
    if (1) { \
        uri_parse_char = uri; \
        uri_parse_line_no = __LINE__; \
        return URI_CHAR_ERR; \
    } else

/* macro to exit parse function once a parsing error occurs */
#define PARSE_ERR() \
    if (1) { \
        uri_parse_char = uri; \
        uri_parse_line_no = __LINE__; \
        return URI_PARSE_ERR; \
    } else

/* macro to exit parse function once parsing is complete */
#define PARSE_OK() \
    if (1) { \
        assert(orig_len == uri_length(parse)); \
        assert(orig_uri + uri_length(parse) == uri); \
        return URI_OK; \
    } else

/* internal function to parse an IPv4 address, returning URI_OK if it
 * parses, URI_PARSE_ERR if not */
static enum uri_ret uri_parse_ipv4(const char *str, unsigned int len);

enum uri_ret uri_parse(const char *uri, unsigned int uri_len, 
  struct uri_parsed *parse) {
    unsigned int count = 0,
                 tmp_count = 0;
#ifndef NDEBUG
    unsigned int orig_len = uri_len;
    const char *orig_uri = uri;
#endif
    int back = 0;
#ifndef URI_STRICT
    back = 1;
#endif


    /* XXX: add IPv6 addr and IP futures */

    /* initialise parse info to defaults */
    parse->scheme_len = parse->userinfo_len = parse->host_len 
      = parse->port_len = parse->path_len = parse->query_len 
      = parse->frag_len = 0;
    parse->seps = parse->flags = 0;

    /* note that we recognise '\' as equivalent to '/', for dickhead windows 
     * users */

/* maybe_scheme_label:   might be scheme, or a relative uri */
    while (uri_len) {
        switch (*uri) {
        case ':':
            /* found a colon, this uri starts with a scheme */
            if (!count) { PARSE_ERR(); }
            parse->scheme_len = count;
            parse->seps |= URI_SEP_SCHEME;
            count = 0;
            uri++; uri_len--;

            /* detect hierarchical part */
            if ((*uri == '/' || (back && *uri == '\\')) 
              && (uri_len > 1) && (uri[1] == '/' 
                || (back && uri[1] == '\\'))) {

                uri += 2; uri_len -= 2;
                parse->seps |= URI_SEP_HIER;
                goto maybe_userinfo_label;
            } else {
                goto path_label;
            }
            break;

        case '?':
            /* must be a relative path, start of query */
            parse->path_len = count;
            parse->seps |= URI_SEP_QUERY;
            parse->flags |= URI_FLAG_REL;
            count = 0;
            uri++; uri_len--;
            goto query_label;

        case '#':
            /* must be a relative path, start of fragment */
            parse->path_len = count;
            parse->seps |= URI_SEP_FRAG;
            parse->flags |= URI_FLAG_REL;
            count = 0;
            uri++; uri_len--;
            goto fragment_label;

        case '\\': case '/':
            /* found a slash, uri starts with either path or hierarchical
             * section */
            uri++; uri_len--;

            /* detect hierarchical part */
            if (uri_len && (*uri == '/' || (back && *uri == '\\'))) {
                uri++; uri_len--;
                parse->seps |= URI_SEP_HIER;
                goto maybe_userinfo_label;
            }

            if (count) {
                parse->flags |= URI_FLAG_REL;
            }
            count++;
            goto path_label;

        case ASCII_CASE_DIGIT:
        case '+': case '-': case '.':
            if (!count) {
                /* can no longer be a scheme */
                parse->flags |= URI_FLAG_REL;
                goto path_label;
            }
        case ASCII_CASE_UPPER:
        case ASCII_CASE_LOWER:
            /* may still be either a scheme or a path */
            uri++; uri_len--;
            count++;
            break;

        case '_': case '~': case '%': case '@':
        /* subdelims, except '+' */
        case '!': case '$': case '&': case '\'': case '(': case ')':
        case '*': case ',': case ';': case '=':
            /* can no longer be a scheme */
            parse->flags |= URI_FLAG_REL;
            goto path_label;

        default: CHAR_ERR();
        }
    }

    /* end of uri, it must be a relative path */
    parse->path_len = count;
    parse->flags |= URI_FLAG_REL;
    PARSE_OK();

maybe_userinfo_label:  /* might be the userinfo, or host */
    while (uri_len) {
        switch (*uri) {
        case '@':
            /* end of userinfo part */
            parse->userinfo_len = count;
            parse->seps |= URI_SEP_USERINFO;
            uri++; uri_len--;
            count = 0;
            goto host_label;

        case ':':
            /* possible transition to port */
            uri++; uri_len--;
            tmp_count = count;
            count = 0;
            goto maybe_port_label;

#ifndef URI_STRICT
        case '\\': 
#endif
        case '/':
            /* end of hostname part */
            parse->host_len = count;

            /* check whether it's an ipv4 address */
            if (uri_parse_ipv4(uri - count, count) == URI_OK) {
                parse->flags |= URI_FLAG_IPV4;
            }

            uri++; uri_len--;
            count = 1;  /* note: / is part of path */
            goto path_label;

        case '%':
            /* percent encoded */
            if (uri_len >= 3 && isxdigit(uri[1]) && isxdigit(uri[2])) {
                uri += 3; uri_len -= 3; count += 3;
            } else {
                PARSE_ERR();
            }
            break;

        case CASE_UNRESERVED: 
        /* sub-delims */
        case '!': case '$': case '&': case '\'': case '(': case ')':
        case '*': case '+': case ',': case ';': case '=':
            uri++; uri_len--;
            count++;
            break;

        default: CHAR_ERR();
        }
    }

    /* end of uri, it must be a hostname */
    parse->host_len = count;

    /* check whether it's an ipv4 address */
    if (uri_parse_ipv4(uri - count, count) == URI_OK) {
        parse->flags |= URI_FLAG_IPV4;
    }

    PARSE_OK();
 
userinfo_label:  /* must be userinfo */
    while (uri_len) {
        switch (*uri) {
        case '@':
            /* end of userinfo part */
            parse->userinfo_len = count;
            parse->seps |= URI_SEP_USERINFO;
            uri++; uri_len--;
            count = 0;
            goto host_label;

#ifndef URI_STRICT
        case '\\': 
#endif
        case '/':
            /* error, need host before end of hostname part */
            PARSE_ERR();
            break;

        case '%':
            /* percent encoded */
            if (uri_len >= 3 && isxdigit(uri[1]) && isxdigit(uri[2])) {
                uri += 3; uri_len -= 3; count += 3;
            } else {
                PARSE_ERR();
            }
            break;

        case CASE_UNRESERVED:
        case ':':
        /* sub-delims */
        case '!': case '$': case '&': case '\'': case '(': case ')':
        case '*': case '+': case ',': case ';': case '=':
            uri++; uri_len--;
            count++;
            break;

        default: CHAR_ERR();
        }
    }

    /* end of uri, error, need host before end of hostname part */
    PARSE_ERR();

maybe_port_label:  /* might be a port, otherwise is part of the userinfo */
    while (uri_len) {
        switch (*uri) {
        case '@':
            /* end of userinfo part */
            parse->userinfo_len = count + tmp_count + 1;
            parse->seps |= URI_SEP_USERINFO;
            uri++; uri_len--;
            count = 0;
            goto host_label;

#ifndef URI_STRICT
        case '\\': 
#endif
        case '/':
            /* end of auth part, it was a port after all */
            parse->host_len = tmp_count;
            parse->seps |= URI_SEP_PORT;
            parse->port_len = count;

            /* check whether host is an ipv4 address */
            if (uri_parse_ipv4(uri - count - tmp_count - 1, tmp_count) 
              == URI_OK) {
                parse->flags |= URI_FLAG_IPV4;
            }

            uri++; uri_len--;
            count = 1;  /* note: / is part of path */
            goto path_label;

        case ASCII_CASE_DIGIT:
            uri++; uri_len--;
            count++;
            break;

        default: 
            count += tmp_count + 1;
            goto userinfo_label;
        }
    }

    /* end of uri, it must be a port */
    parse->host_len = tmp_count;
    parse->seps |= URI_SEP_PORT;
    parse->port_len = count;

    /* check whether host is an ipv4 address */
    if (uri_parse_ipv4(uri - count - tmp_count - 1, tmp_count) == URI_OK) {
        parse->flags |= URI_FLAG_IPV4;
    }

    PARSE_OK();

host_label:  /* must be the host portion */
    while (uri_len) {
        switch (*uri) {
        case ':':
            /* transition to port */
            parse->host_len = count;
            parse->seps |= URI_SEP_PORT;

            /* check whether host is an ipv4 address */
            if (uri_parse_ipv4(uri - count, count) == URI_OK) {
                parse->flags |= URI_FLAG_IPV4;
            }

            uri++; uri_len--;
            count = 0;
            goto port_label;

#ifndef URI_STRICT
        case '\\': 
#endif
        case '/':
            /* end of hostname part */
            parse->host_len = count;

            /* check whether host is an ipv4 address */
            if (uri_parse_ipv4(uri - count, count) == URI_OK) {
                parse->flags |= URI_FLAG_IPV4;
            }

            uri++; uri_len--;
            count = 1;  /* note: / is part of path */
            goto path_label;

        case '%':
            /* percent encoded */
            if (uri_len >= 3 && isxdigit(uri[1]) && isxdigit(uri[2])) {
                uri += 3; uri_len -= 3; count += 3;
            } else {
                PARSE_ERR();
            }
            break;

        case CASE_UNRESERVED:
        /* sub-delims */
        case '!': case '$': case '&': case '\'': case '(': case ')':
        case '*': case '+': case ',': case ';': case '=':
            uri++; uri_len--;
            count++;
            break;

        default: CHAR_ERR();
        }
    }

    /* end of uri during hostname */
    parse->host_len = count;

    /* check whether host is an ipv4 address */
    if (uri_parse_ipv4(uri - count, count) == URI_OK) {
        parse->flags |= URI_FLAG_IPV4;
    }
 
    PARSE_OK();
 
port_label:  /* must be a port */
    while (uri_len) {
        switch (*uri) {
#ifndef URI_STRICT
        case '\\': 
#endif
        case '/':
            /* end of auth part */
            parse->port_len = count;
            uri++; uri_len--;
            count = 1;  /* note: / is part of path */
            goto path_label;

        case ASCII_CASE_DIGIT:
            uri++; uri_len--;
            count++;
            break;

        default: CHAR_ERR();
        }
    }

    /* end of uri, end of port */
    parse->port_len = count;
    PARSE_OK();

path_label:  /* must be in the path */
    while (uri_len) {
        switch (*uri) {
        case '?':
            /* start of query */
            parse->path_len = count;
            parse->seps |= URI_SEP_QUERY;
            count = 0;
            uri++; uri_len--;
            goto query_label;

        case '#':
            /* start of fragment */
            parse->path_len = count;
            parse->seps |= URI_SEP_FRAG;
            count = 0;
            uri++; uri_len--;
            goto fragment_label;

        case '%':
            /* percent encoded */
            if (uri_len >= 3 && isxdigit(uri[1]) && isxdigit(uri[2])) {
                uri += 3; uri_len -= 3; count += 3;
            } else {
                PARSE_ERR();
            }
            break;

#ifndef URI_STRICT
        case '\\': case '|': case '[': case ']':
#endif
        case '/': case ':': case '@':
        case CASE_UNRESERVED:
        case CASE_SUBDELIMS:
            uri++; uri_len--;
            count++;
            break;

        default: CHAR_ERR();
        }
    }

    /* end of uri in path */
    parse->path_len = count;
    PARSE_OK();

query_label:
    while (uri_len) {
        switch (*uri) {
        case '#':
            /* start of fragment */
            parse->query_len = count;
            parse->seps |= URI_SEP_FRAG;
            count = 0;
            uri++; uri_len--;
            goto fragment_label;

        case '%':
            /* percent encoded */
            if (uri_len >= 3 && isxdigit(uri[1]) && isxdigit(uri[2])) {
                uri += 3; uri_len -= 3; count += 3;
            } else {
                PARSE_ERR();
            }
            break;

#ifndef URI_STRICT
        case '\\': case '|':
#endif
        case '/': case '?': case ':': case '@': 
        case CASE_UNRESERVED:
        case CASE_SUBDELIMS:
            uri++; uri_len--;
            count++;
            break;

        default: CHAR_ERR();
        }
    }

    /* end of uri in query */
    parse->query_len = count;
    PARSE_OK();

fragment_label:
    while (uri_len) {
        switch (*uri) {
        case '%':
            /* percent encoded */
            if (uri_len >= 3 && isxdigit(uri[1]) && isxdigit(uri[2])) {
                uri += 3; uri_len -= 3; count += 3;
            } else {
                PARSE_ERR();
            }
            break;

#ifndef URI_STRICT
        case '\\': case '|':
#endif
        case '/': case '?': case ':': case '@': 
        case CASE_UNRESERVED:
        case CASE_SUBDELIMS:
            uri++; uri_len--;
            count++;
            break;

        default: CHAR_ERR();
        }
    }

    /* end of uri in query */
    parse->frag_len = count;
    PARSE_OK();
}

static enum uri_ret uri_parse_ipv4(const char *uri, unsigned int len) {
    unsigned int octet = 1,   /* which octet we're in */
                 val = 0,     /* what value octet currently has */
                 chr = 0;     /* how many characters octet has */

    while (len--) {
        if (*uri == '.') {
            if (chr >= 1 && chr <= 3 && val <= 255) { 
                uri++;
                octet++;
                val = 0;
                chr = 0;
            } else {
                return URI_PARSE_ERR;
            }
        } else if (isdigit(*uri)) {
            chr++;
            val *= 10;
            val += *uri - '0';
            uri++;
        } else {
            return URI_PARSE_ERR;
        }
    }

    /* check value of last octet and that we've received 4 octets, and exit */
    if (octet == 4 && chr >= 1 && chr <= 3 && val <= 255) { 
        return URI_OK;
    } else {
        return URI_PARSE_ERR;
    }
} 

static void string_out(const char *str, unsigned int width, FILE *out) {
    unsigned int i;

    for (i = 0; i < width && *str; i++, str++) {
        putc(*str, out);
    }
    for (; i < width; i++) {
        putc(' ', out);
    }
}

static void print_name(unsigned int len, unsigned int gap, const char **name, 
  unsigned int names, FILE *out) {
    unsigned int space,
                 total = len + gap,
                 ns,
                 i,
                 slen = strlen(name[names - 1]),
                 outc = 0;

    /* figure out how much space we need for last (present) string, and infer
     * how much we have left over */
    if (slen >= total) {
        space = 0;
    } else if (slen >= len / 2) {
        space = total - slen - 1;
    } else {
        space = gap + (len - 1) / 2;
    }

    if (names > 1) {
        ns = space / (names - 1);
    } else {
        ns = 0;
    }

    if (ns >= 2) {
        for (i = 0; i + 1 < names; i++) {
            outc += ns;
            string_out(name[i], ns - 1, out);
            putc(' ', out);
        }
    }

    while (outc < space) {
        putc(' ', out);
        outc++;
    }

    assert(outc + 1 <= total);
    string_out(name[names - 1], total - outc - 1, out);
    putc(' ', out);
}

static void print_lines(unsigned int len, unsigned int gap, const char **name, 
  unsigned int names, FILE *out) {
    unsigned int i;

    for (i = 0; i < gap; i++) {
        putc(' ', out);
    }

    if (len > 1) {
        putc('\\', out);
        for (i = 0; i + 2 < len; i++) {
            putc('_', out);
        }
        putc('/', out);
    } else if (len) {
        putc('|', out);
    }
}

static void print_con(unsigned int len, unsigned int gap, const char **name, 
  unsigned int names, FILE *out) {
    unsigned int i;

    for (i = 0; i < gap; i++) {
        putc(' ', out);
    }

    for (i = 0; i < (len - 1) / 2; i++) {
        putc(' ', out);
    }
    i++;
    putc('|', out);
    for (; i < len; i++) {
        putc(' ', out);
    }
}

void uri_print(const char *uri, const struct uri_parsed *parse, FILE *o) {
    void (*fn[])(unsigned int l, unsigned int g, const char **n, 
        unsigned int ns, FILE *o) 
      = {print_lines, print_con, print_name};
    unsigned int i,
                 j,
                 gap,
                 comps,
                 len = uri_length(parse);
    const char *names[] = {"scheme", "userinfo", "host", "port", "path", 
                         "query", "fragment"};
    fprintf(o, "%.*s\n", len, uri);

    for (j = 0; j < sizeof(fn) / sizeof(*fn); j++) {
        /* scheme */
        comps = 0;
        gap = 0;
        i = 0;
        if (parse->scheme_len) {
            fn[j](parse->scheme_len, 0, &names[0], 1, o);
        }

        /* userinfo */
        comps++;
        i++;
        if (parse->seps & URI_SEP_SCHEME) gap++;
        if (parse->seps & URI_SEP_HIER) gap += 2;
        if (parse->userinfo_len) {
            fn[j](parse->userinfo_len, gap, &names[i - (comps - 1)], comps, o);
            gap = 0;
            comps = 0;
        }

        /* host */
        comps++;
        i++;
        if (parse->seps & URI_SEP_USERINFO) gap++;
        if (parse->host_len) {
            fn[j](parse->host_len, gap, &names[i - (comps - 1)], comps, o);
            gap = 0;
            comps = 0;
        }

        /* port */
        comps++;
        i++;
        if (parse->seps & URI_SEP_PORT) gap++;
        if (parse->port_len) {
            fn[j](parse->port_len, gap, &names[i - (comps - 1)], comps, o);
            gap = 0;
            comps = 0;
        }

        /* path */
        comps++;
        i++;
        /* note no test for PATH, that's included in the path_len */
        if (parse->path_len) {
            fn[j](parse->path_len, gap, &names[i - (comps - 1)], comps, o);
            gap = 0;
            comps = 0;
        }

        /* query */
        comps++;
        i++;
        if (parse->seps & URI_SEP_QUERY) gap++;
        if (parse->query_len) {
            fn[j](parse->query_len, gap, &names[i - (comps - 1)], comps, o);
            gap = 0;
            comps = 0;
        }

        /* fragment */
        comps++;
        i++;
        if (parse->seps & URI_SEP_FRAG) gap++;
        if (parse->frag_len) {
            fn[j](parse->frag_len, gap, &names[i - (comps - 1)], comps, o);
            gap = 0;
            comps = 0;
        }

        for (i = 0; fn[j] == print_name && i < comps; i++) {
            fprintf(o, " %s", names[7 - comps + i]);
        }
        fprintf(o, "\n");
    }
}

unsigned int uri_length(const struct uri_parsed *parse) {
    unsigned int len = parse->scheme_len + parse->userinfo_len 
      + parse->host_len + parse->port_len + parse->path_len + parse->query_len 
      + parse->frag_len;

    if (parse->seps & URI_SEP_SCHEME) len++;
    if (parse->seps & URI_SEP_HIER) len += 2;
    if (parse->seps & URI_SEP_USERINFO) len++;
    if (parse->seps & URI_SEP_PORT) len++;
    /* note no test for PATH, that's included in the path_len */
    if (parse->seps & URI_SEP_QUERY) len++;
    if (parse->seps & URI_SEP_FRAG) len++;

    return len;
}

unsigned int hexval(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else {
        assert(isxdigit(c));
        assert(isalpha(c));
        return tolower(c) - 'a' + 10;
    }
}

static enum uri_ret path_normalise(char *uri, unsigned int *uri_len, 
  int decoding) {
    unsigned int space[10],
                 *seg = space,
                 segs = 0,
                 capacity = sizeof(space) / sizeof(*space);
    char *orig_uri = uri,
         *dst = uri,
         *end = uri + *uri_len;
    int back = 0;
#ifndef URI_STRICT
    back = 1;
#endif

/* macro to pop a segment off of the stack */
#define POP()                                                                 \
    if (segs) {                                                               \
        dst -= seg[segs - 1];                                                 \
        segs--;                                                               \
    } else

    /* algorithm: 
     *   - initial '../' or './' -> ''
     *   - '/./' or '/.'END -> '/'
     *   - '/../' or '/..'END -> '/' (remove last segment)
     *   - '.'END or '..'END -> '' 
     *   - '\' -> '/'
     *   - '//' -> '/'
     */

start_label:
    while (uri < end) {
        switch (*uri) {
#ifndef URI_STRICT
        case '\\':
#endif
        case '/':
            uri++;
            goto slash_label;

        case '.':
            uri++;
            goto dot_label;

        case '%':
            assert(uri + 2 < end || !decoding);
            if (decoding && ((uri[1] == '2' && (tolower(uri[2]) == 'f')) 
              || (back && uri[1] == '5' && (tolower(uri[2]) == 'c')))) {
                /* got a slash (2f == '/', 5c == '\\') */
                uri += 3;
                goto slash_label;
            } else if (decoding 
              && (uri[1] == '2' && (tolower(uri[2]) == 'e'))) {
                /* got a period (2e == '.') */
                uri += 3;
                goto dot_label;
            } else if (decoding) {
                *dst++ = *uri++;
                *dst++ = *uri++;
                *dst++ = *uri++;
                seg[segs] = 3;
                goto seg_label;
            }
            /* else fallthrough to default */

        default:
            *dst++ = *uri++;
            seg[segs] = 1;
            goto seg_label;
        }
    }

    /* end of input */
    *uri_len = dst - orig_uri;
    return URI_OK;

slash_label:
    while (uri < end) {
        switch (*uri) {
#ifndef URI_STRICT
        case '\\':
#endif
        case '/':
            /* eat repeated slashes */
            uri++;
            goto slash_label;

        case '.':
            uri++;
            goto slash_dot_label;

        case '%':
            assert(uri + 2 < end || !decoding);
            if (decoding && ((uri[1] == '2' && (tolower(uri[2]) == 'f')) 
              || (back && uri[1] == '5' && (tolower(uri[2]) == 'c')))) {
                /* got a slash (2f == '/', 5c == '\\') */
                /* eat repeated slashes */
                uri += 3;
                goto slash_label;
            } else if (decoding 
              && (uri[1] == '2' && (tolower(uri[2]) == 'e'))) {
                /* got a period (2e == '.') */
                uri += 3;
                goto slash_dot_label;
            } else if (decoding) {
                *dst++ = '/';
                *dst++ = *uri++;
                *dst++ = *uri++;
                *dst++ = *uri++;
                seg[segs] = 4;
                goto seg_label;
            }
            /* else fallthrough to default */

        default:
            *dst++ = '/';
            *dst++ = *uri++;
            seg[segs] = 2;
            goto seg_label;
        }
    }

    /* end of input */
    *dst++ = '/';
    *uri_len = dst - orig_uri;
    return URI_OK;

dot_label:
    while (uri < end) {
        switch (*uri) {
#ifndef URI_STRICT
        case '\\':
#endif
        case '/':
            /* matched './', remove it */
            uri++;
            goto start_label;

        case '.':
            uri++;
            goto dot_dot_label;

        case '%':
            assert(uri + 2 < end || !decoding);
            if (decoding && ((uri[1] == '2' && (tolower(uri[2]) == 'f')) 
              || (back && uri[1] == '5' && (tolower(uri[2]) == 'c')))) {
                /* got a slash (2f == '/', 5c == '\\') */
                /* matched './', remove it */
                uri += 3;
                goto start_label;
            } else if (decoding 
              && (uri[1] == '2' && (tolower(uri[2]) == 'e'))) {
                /* got a period (2e == '.') */
                uri += 3;
                goto dot_dot_label;
            } else if (decoding) {
                *dst++ = '.';
                *dst++ = *uri++;
                *dst++ = *uri++;
                *dst++ = *uri++;
                seg[segs] = 4;
                goto seg_label;
            } 
            /* else fallthrough to default */

        default:
            *dst++ = '.';
            *dst++ = *uri++;
            seg[segs] = 2;
            goto seg_label;
        }
    }

    /* end of input, remove end '.' */
    *uri_len = dst - orig_uri;
    return URI_OK;

dot_dot_label:
    while (uri < end) {
        switch (*uri) {
#ifndef URI_STRICT
        case '\\':
#endif
        case '/':
            /* recognised '../', remove it */
            assert(segs == 0);
            uri++;
            goto start_label;

        case '%':
            assert(uri + 2 < end || !decoding);
            if (decoding && ((uri[1] == '2' && (tolower(uri[2]) == 'f')) 
              || (back && uri[1] == '5' && (tolower(uri[2]) == 'c')))) {
                /* got a slash (2f == '/', 5c == '\\') */
                /* recognised '../', remove it */
                assert(segs == 0);
                uri += 3;
                goto start_label;
            }
            /* else fallthrough to default */
 
        default:
            *dst++ = '.';
            *dst++ = '.';
            seg[segs] = 2;
            goto seg_label;
        }
    }

    /* end of input, remove end '..' */
    assert(segs == 0);
    *uri_len = dst - orig_uri;
    return URI_OK;

slash_dot_label:
    while (uri < end) {
        switch (*uri) {
#ifndef URI_STRICT
        case '\\':
#endif
        case '/':
            /* recognised '/./', replace with '/' */
            uri++;
            goto slash_label;

        case '.':
            uri++;
            goto slash_dot_dot_label;

        case '%':
            assert(uri + 2 < end || !decoding);
            if (decoding && ((uri[1] == '2' && (tolower(uri[2]) == 'f')) 
              || (back && uri[1] == '5' && (tolower(uri[2]) == 'c')))) {
                /* got a slash (2f == '/', 5c == '\\') */
                /* recognised '/./', replace with '/' */
                uri += 3;
                goto slash_label;
                break;
            } else if (decoding 
              && (uri[1] == '2' && (tolower(uri[2]) == 'e'))) {
                /* got a period (2e == '.') */
                uri += 3;
                goto slash_dot_dot_label;
                break;
            } 
            /* else fallthrough to default */

        default:
            *dst++ = '/';
            *dst++ = '.';
            seg[segs] = 2;
            goto seg_label;
        }
    }

    /* end of input, replace end '/.' with '/' */
    *dst++ = '/';
    *uri_len = dst - orig_uri;
    return URI_OK;

slash_dot_dot_label:
    while (uri < end) {
        switch (*uri) {
#ifndef URI_STRICT
        case '\\':
#endif
        case '/':
            /* recognised '/../', replace with '/' and remove last segment */
            POP();
            uri++;
            goto slash_label;

        case '%':
            assert(uri + 2 < end || !decoding);
            if (decoding && ((uri[1] == '2' && (tolower(uri[2]) == 'f')) 
              || (back && uri[1] == '5' && (tolower(uri[2]) == 'c')))) {
                /* got a slash (2f == '/', 5c == '\\') */
                /* recognised '/../', replace with '/' and remove last 
                 * segment */
                uri += 3;
                POP();
                goto slash_label;
            }
            /* else fallthrough to default */

        default:
            *dst++ = '/';
            *dst++ = '.';
            *dst++ = '.';
            seg[segs] = 3;
            goto seg_label;
        }
    }

    /* end of input, replace end '/..' with '/' and remove last segment */
    POP();
    *dst++ = '/';
    *uri_len = dst - orig_uri;
    return URI_OK;

seg_label:
    while (uri < end) {
        switch (*uri) {
        case '%':
            assert(uri + 2 < end || !decoding);
            if (!decoding || !((uri[1] == '2' && (tolower(uri[2]) == 'f')) 
              || (uri[1] == '5' && (tolower(uri[2]) == 'c')))) {
                /* didn't get a slash, consume it */
                seg[segs] += 3;
                *dst++ = *uri++;
                *dst++ = *uri++;
                *dst++ = *uri++;
                break;  /* don't fallthrough to slash handling */
            } else if (decoding) {
                uri++;
                uri++;   /* third character is consumed below */
                /* fallthrough to slash handling */
            }
            /* otherwise, fallthrough to slash handling */

#ifndef URI_STRICT
        case '\\':
#endif
        case '/':
            /* end of this segment */
            segs++;
            if (segs >= capacity) {
                void *ptr = malloc(sizeof(*seg) * capacity * 2);
                
                if (ptr) {
                    memcpy(ptr, seg, sizeof(*seg) * capacity);
                    capacity *= 2;
                    if (seg != space) {
                        free(seg);
                    }
                    seg = ptr;
                } else {
                    return URI_MEM_ERR;
                }
            }
            uri++;
            goto slash_label;

        default:
            seg[segs]++;
            *dst++ = *uri++;
            break;
        }
    }

    /* end of input */
    *uri_len = dst - orig_uri;
    return URI_OK;
}

enum uri_ret uri_path_normalise(char *uri, unsigned int *uri_len) {
    return path_normalise(uri, uri_len, 0);
}

enum uri_ret uri_normalise(char *uri, struct uri_parsed *parse) {
    char *dst = uri,
         *orig_uri = uri,
         *end;
    unsigned char c;
    unsigned int i, 
                 removed = 0,
                 uri_len = uri_length(parse);
    enum uri_ret ret;

    /* normalisation consists of:
     *   - lowercasing the hostname and scheme
     *   - removing superfluous separators 
     *   - removing superfluous encoded characters
     *   - changing '\' to '/' 
     *   - removing standard ports
     *   - removing leading zeros from ports
     *   - modifying a path of '/' to the empty path
     *   - a bunch of other stuff handled by path_normalise
     *
     * Note that '/' is changed to the empty path rather than vice-versa (as
     * recommended by RFC 3986) because this potentially lengthens the URI,
     * which causes us a lot of problems in this situation.
     * We perform that normalisation here, rather than in path_normalise,
     * because it is a uri-specific normalisation that doesn't apply to paths.
     *
     * Also note that we don't perform aggressive normalisation, such as
     * removing trailing path directory slashes (i.e. 'dir/' to 'dir'),
     * removing the final '.' in hostnames, 
     * removing fragments and removing 'index.html'.  These are useful for 
     * web work, but lose information.  Implement them yourself if you need 
     * them (XXX).  */
    if (!(parse->flags & URI_FLAG_REL)) {
        /* process scheme */
        for (i = 0; i < parse->scheme_len; i++) {
            *dst++ = tolower(*uri++);
        }

        /* scheme separator */
        if (parse->seps & URI_SEP_SCHEME) {
            assert(*uri == ':');
            *dst++ = *uri++;
        }

        /* hierarchical scheme seperator */
        if (parse->seps & URI_SEP_HIER) {
            assert(*uri == '/' || *uri == '\\');
            *dst++ = '/'; uri++;
            assert(*uri == '/' || *uri == '\\');
            *dst++ = '/'; uri++;
        }

        /* process userinfo */
        end = uri + parse->userinfo_len;
        while (uri < end) {
            switch (*uri) {
            case '%':
                assert(i + 2 < parse->userinfo_len);
                c = hexval(uri[1]) * 16 + hexval(uri[2]);
                switch (c) {
                case ':':
                case CASE_UNRESERVED: 
                case CASE_SUBDELIMS:
                    *dst++ = c;
                    uri += 3;
                    parse->userinfo_len -= 2;
                    removed += 2;
                    break;

                default:
                    /* just copy it encoded */
                    *dst++ = *uri++;
                    *dst++ = tolower(*uri++);
                    *dst++ = tolower(*uri++);
                    break;
                }
                break;

            default: *dst++ = *uri++; break;
            }
        }

        /* normalise userinfo separator */
        if (parse->seps & URI_SEP_USERINFO) {
            assert(*uri == '@');
            if (parse->userinfo_len == 0) {
                parse->seps &= ~URI_SEP_USERINFO;
                uri++;
                removed++;
            } else {
                *dst++ = *uri++;
            }
        }

        /* process host */
        end = uri + parse->host_len;
        while (uri < end) {
            switch (*uri) {
            case '%':
                assert(i + 2 < parse->host_len);
                c = hexval(uri[1]) * 16 + hexval(uri[2]);
                switch (c) {
                case ':': case '@':
                case CASE_UNRESERVED: 
                case CASE_SUBDELIMS:
                    *dst++ = c;
                    uri += 3;
                    parse->host_len -= 2;
                    removed += 2;
                    break;

                default:
                    /* just copy it encoded */
                    *dst++ = *uri++;
                    *dst++ = tolower(*uri++);
                    *dst++ = tolower(*uri++);
                    break;
                }
                break;

            case ASCII_CASE_UPPER: *dst++ = tolower(*uri++); break;
            default: *dst++ = *uri++; break;
            }
        }

        /* normalise port separator */
        if (parse->seps & URI_SEP_PORT) {
            assert(*uri == ':');
            if (parse->port_len == 0) {
                parse->seps &= ~URI_SEP_PORT;
                uri++;
                removed++;
            } else {
                *dst++ = *uri++;
            }
        }

        /* process port */
        if ((parse->scheme_len == 4 && orig_uri[0] == 'h'
            && orig_uri[1] == 't' && orig_uri[2] == 't' && orig_uri[3] == 'p'
            && atoi(uri) == 80)
          || (parse->scheme_len == 3 && orig_uri[0] == 'f'
            && orig_uri[1] == 't' && orig_uri[2] == 'p' 
            && atoi(uri) == 21)
          || (parse->scheme_len == 5 && orig_uri[0] == 'h'
            && orig_uri[1] == 't' && orig_uri[2] == 't' 
            && orig_uri[3] == 'p' && orig_uri[4] == 's' 
            && atoi(uri) == 443)) {

            /* remove port ':80' from http URIs,
             * ':21' from ftp URIs,
             * ':443' from https URIs */
            uri += parse->port_len;
            removed += parse->port_len + 1;
            dst--;
            parse->port_len = 0;
            parse->seps &= ~URI_SEP_PORT;
        }

        /* remove leading zeros from port */
        for (i = 0; i + 1 < parse->port_len && *uri == '0'; i++) {
            removed++;
            parse->port_len--;
            uri++;
        }

        /* copy the rest of the port */
        for (i = 0; i < parse->port_len; i++) {
            *dst++ = *uri++;
        }

        /* move the source path to start location of destination path, so that
         * we can normalise the path knowing only the location of the source */
        if (removed) {
            memmove(dst, uri, uri_len - (uri - orig_uri));
            uri = dst;
        }
    }

    /* normalise path */
    assert(!(parse->seps & URI_SEP_QUERY) || uri[parse->path_len] == '?');
    removed = parse->path_len;
    if ((ret = path_normalise(uri, &parse->path_len, 1)) == URI_OK) {
        /* adjust query and fragment so that they follow the newly-normalised
         * path */
        if (removed != parse->path_len) {
            memmove(uri + parse->path_len, uri + removed,
              uri_len - (uri - orig_uri) - removed);
        }
    } else {
        return ret;
    }

    /* turn path '/' into empty path */
    if (parse->path_len == 1 && uri[0] == '/') {
        parse->path_len = 0;
        uri++;
    } else {
        for (i = 0; i < parse->path_len; i++) {
            *dst++ = *uri++;
        }
    }

    /* normalise query separator */
    if (parse->seps & URI_SEP_QUERY) {
        assert(*uri == '?');
        if (parse->query_len == 0) {
            parse->seps &= ~URI_SEP_QUERY;
            uri++;
        } else {
            *dst++ = *uri++;
        }
    }

    /* normalise query */
    end = uri + parse->query_len; 
    while (uri < end) {
        switch (*uri) {
        case '%':
            assert(uri + 2 < end);
            c = hexval(uri[1]) * 16 + hexval(uri[2]);
            switch (c) {
            case ':': case '@': case '/': case '?':
            case CASE_UNRESERVED: 
            /* sub-delims */
            case '!': case '$': case '&': case '\'': case '(': case ')':
            case '*': case '+': case ',': case ';': case '=':
                *dst++ = c;
                uri += 3;
                parse->query_len -= 2;
                break;

#ifndef URI_STRICT
            case '\\': 
                *dst++ = '/'; 
                uri += 3; 
                parse->query_len -= 2;
                break;
#endif

            default:
                /* just copy it encoded */
                *dst++ = *uri++;
                *dst++ = tolower(*uri++);
                *dst++ = tolower(*uri++);
                break;
            }
            break;

#ifndef URI_STRICT
        case '\\': *dst++ = '/'; uri++; break;
#endif
        default: *dst++ = *uri++; break;
        }
    }

    /* normalise fragment separator */
    if (parse->seps & URI_SEP_FRAG) {
        assert(*uri == '#');
        if (parse->frag_len == 0) {
            parse->seps &= ~URI_SEP_FRAG;
            uri++;
        } else {
            *dst++ = *uri++;
        }
    }

    /* normalise fragment */
    end = uri + parse->frag_len;
    while (uri < end) {
        switch (*uri) {
        case '%':
            assert(i + 2 < parse->frag_len);
            c = hexval(uri[1]) * 16 + hexval(uri[2]);
            switch (c) {
            /* note that fragments may NOT contain unencoded '#' */
            case ':': case '@': case '/': case '?':
            case CASE_UNRESERVED: 
            /* sub-delims */
            case '!': case '$': case '&': case '\'': case '(': case ')':
            case '*': case '+': case ',': case ';': case '=':
                *dst++ = c;
                uri += 3;
                parse->frag_len -= 2;
                break;

#ifndef URI_STRICT
            case '\\': 
                *dst++ = '/'; 
                uri += 3; 
                parse->frag_len -= 2;
                break;
#endif

            default:
                /* just copy it encoded */
                *dst++ = *uri++;
                *dst++ = tolower(*uri++);
                *dst++ = tolower(*uri++);
                break;
            }
            break;

#ifndef URI_STRICT
        case '\\': *dst++ = '/'; uri++; break;
#endif
        default: *dst++ = *uri++; break;
        }
    }

    return URI_OK;
}

enum uri_ret uri_part_decode(const char *uri, const struct uri_parsed *parse, 
  enum uri_part part, 
  char *dst, unsigned int dst_max_len, unsigned int *dst_len) {
    unsigned int offset = 0,
                 len,
                 ldst_len = 0;
    const char *end,
               *dst_start = dst;
    int c;

    switch (part) {
    default: return URI_ERR;
    case URI_PART_SCHEME: len = parse->scheme_len; break;
    case URI_PART_USERINFO: len = parse->userinfo_len; break;
    case URI_PART_HOST: len = parse->host_len; break;
    case URI_PART_PORT: len = parse->port_len; break;
    case URI_PART_PATH: len = parse->path_len; break;
    case URI_PART_QUERY: len = parse->query_len; break;
    case URI_PART_FRAGMENT: len = parse->frag_len; break;
    }

    /* note that all cases below fall through */
    switch (part) {
    case URI_PART_FRAGMENT: 
        if (parse->seps & URI_SEP_FRAG) {
            offset++;
        }
        offset += parse->query_len;

    case URI_PART_QUERY: 
        if (parse->seps & URI_SEP_QUERY) {
            offset++;
        }
        offset += parse->path_len;

    case URI_PART_PATH: 
        offset += parse->port_len;
        /* no separator for path */

    case URI_PART_PORT: 
        if (parse->seps & URI_SEP_PORT) {
            offset++;
        }
        offset += parse->host_len;

    case URI_PART_HOST: 
        offset += parse->userinfo_len;
        if (parse->seps & URI_SEP_USERINFO) {
            offset++;
        }

    case URI_PART_USERINFO: 
        offset += parse->scheme_len;
        if (parse->seps & URI_SEP_SCHEME) {
            offset++;
        }
        if (parse->seps & URI_SEP_HIER) {
            offset += 2;
        }

    case URI_PART_SCHEME: break;
    }

    uri += offset;
    end = uri + len;
    while (uri < end && (dst - dst_start) < dst_max_len) {
        switch (*uri) {
        case '%':
            /* decode */
            assert(uri + 2 < end);
            switch (uri[1]) {
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                c = uri[1] - 'a';
                break;

            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                c = uri[1] - 'A';
                break;

            case ASCII_CASE_DIGIT:
                c = uri[1] - '0';
                break;

            default: assert("can't get here" && 0); return URI_ERR;
            }
            c *= 16;
            switch (uri[2]) {
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                c = uri[2] - 'a';
                break;

            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                c = uri[2] - 'A';
                break;

            case ASCII_CASE_DIGIT:
                c = uri[2] - '0';
                break;

            default: assert("can't get here" && 0); return URI_ERR;
            }
            *dst++ = c;
            uri += 3;
            break;

        default: 
            *dst++ = *uri++; 
            break;
        }
    }
    ldst_len = dst - dst_start;

    while (uri < end) {
        switch (*uri) {
        case '%':
            assert(uri + 2 < end);
            uri += 3;
            ldst_len++;
            break;

        default: 
            ldst_len++;
            uri++;
            break;
        }
    }
    *dst_len = ldst_len;

    return URI_OK;
}

int uri_relative(const struct uri_parsed *parse) {
    return parse->flags & URI_FLAG_REL;
}

int uri_hierarchical(const struct uri_parsed *parse) {
    return parse->seps & URI_SEP_HIER;
}

unsigned int uri_append_length(char *base, struct uri_parsed *base_parse,
  const char *end, const struct uri_parsed *end_parse) {
    return uri_length(base_parse) + uri_length(end_parse) + 1;
}

enum uri_ret uri_append(char *base, struct uri_parsed *base_parse,
  const char *end, const struct uri_parsed *end_parse) {
    unsigned int len;
    const char *src = end;
    char c,
         *dst = base;

    /* back indicates whether backslashes delimit paths */
    int back = 0;
#ifndef URI_STRICT
    back = 1;
#endif

    /* this algorithm comes from Section 5.2.2 of RFC 3986 */

    /* if the end uri is hierarchical, it must contain everything.  else if it
     * has a scheme, and it's not the same scheme as the base uri, it must
     * contain everything */
    if ((uri_hierarchical(end_parse) && end_parse->scheme_len)
      || (end_parse->scheme_len 
        && ((end_parse->scheme_len != base_parse->scheme_len) 
          || (strncmp(end, base, end_parse->scheme_len))))) {

        /* relative uri contains everything, just replace base uri */
        len = uri_length(end_parse);
        memcpy(base, end, len);
        *base_parse = *end_parse;
    } else {
        /* scheme remains the same */
        src += end_parse->scheme_len;
        dst += base_parse->scheme_len;
        if (end_parse->seps & URI_SEP_SCHEME) {
            assert(*src == ':');
            src++;
        }
        if (base_parse->seps & URI_SEP_SCHEME) {
            assert(*dst == ':');
            dst++;
        }

        if (end_parse->seps & URI_SEP_HIER) {
            /* copy everything except scheme across */

            /* preserve scheme settings */
            int tmp = base_parse->seps & URI_SEP_SCHEME;
            len = base_parse->scheme_len;

            assert((*src == '/' || *src == '\\') 
              && (src[1] == '/' || src[1] == '\\'));

            *base_parse = *end_parse;
            base_parse->scheme_len = len;
            base_parse->seps &= ~URI_SEP_SCHEME;
            base_parse->seps |= tmp;

            end = end + uri_length(end_parse);
            while (src < end) {
                *dst++ = *src++;
            }
        } else {
            /* authority remains the same */
            if (end_parse->seps & URI_SEP_HIER) {
                assert(*src == '/' || *src == '\\');
                src++;
                assert(*src == '/' || *src == '\\');
                src++;
            }
            if (base_parse->seps & URI_SEP_HIER) {
                assert(*dst == '/' || *dst == '\\');
                dst++;
                assert(*dst == '/' || *dst == '\\');
                dst++;
            }

            dst += base_parse->userinfo_len;
            src += end_parse->userinfo_len;
            if (base_parse->seps & URI_SEP_USERINFO) {
                assert(*dst == '@');
                dst++;
            }
            if (end_parse->seps & URI_SEP_USERINFO) {
                assert(*src == '@');
                src++;
            }
            dst += base_parse->host_len;
            src += end_parse->host_len;
            if (base_parse->seps & URI_SEP_PORT) {
                assert(*dst == ':');
                dst++;
            }
            if (end_parse->seps & URI_SEP_PORT) {
                assert(*src == ':');
                src++;
            }
            dst += base_parse->port_len;
            src += end_parse->port_len;

            if (!end_parse->path_len) {
                /* path remains the same */
                dst += base_parse->path_len;
                src += end_parse->path_len;

                if (!end_parse->query_len) {
                    /* query remains the same */
                    assert(!(end_parse->seps & URI_SEP_QUERY));
                    if (base_parse->seps & URI_SEP_QUERY) {
                        assert(*dst == '?');
                        dst++;
                    }
                    dst += base_parse->query_len;
                    src += end_parse->query_len;
                } else {
                    /* copy query from end to base */
                    if (base_parse->seps & URI_SEP_QUERY) {
                        if (base_parse->seps & URI_SEP_FRAG) {
                            /* need to move the fragment so it is correctly
                             * placed relative to the new query */
                            memmove(dst + 1 + end_parse->query_len, 
                              dst + 1 + base_parse->query_len,
                              base_parse->frag_len + 1);
                        }
                    } else {
                        if (base_parse->seps & URI_SEP_FRAG) {
                            /* need to move the fragment (currently at dst) 
                             * so it is correctly placed relative to the new 
                             * query */
                            assert(*dst == '#');
                            memmove(dst + 1 + end_parse->query_len, 
                              dst, base_parse->frag_len + 1);
                        }
                    }
                    memcpy(dst, src, end_parse->query_len + 1); /* copy query*/
                    src += end_parse->query_len + 1; /* skip over query */
                    dst += end_parse->query_len + 1; /* skip over query */
                }
            } else {
                unsigned int movelen = base_parse->query_len 
                  + base_parse->frag_len;

                if (base_parse->seps & URI_SEP_QUERY) movelen++;
                if (base_parse->seps & URI_SEP_FRAG) movelen++;
    
                /* extract first char from end, see if it is '/' */
                uri_part_decode(end, end_parse, URI_PART_PATH, &c, 1, &len);
                if (end_parse->path_len && ((c == '/')
#ifndef URI_STRICT
                      || (c == '\\')
#endif
                    )) {

                    /* move the query and fragment so they're correctly placed
                     * relative to the new path */
                    if (movelen) {
                        memmove(dst + end_parse->path_len, 
                          dst + base_parse->path_len, movelen);
                    }
                    /* copy path from end */
                    memcpy(dst, src, end_parse->path_len);
                    base_parse->path_len = end_parse->path_len;
                } else {
                    int back = 0;
                    unsigned int pathlen 
                      = uri_path_append_length(dst, base_parse->path_len,
                        src, end_parse->path_len, 1, back);

                    if (uri_hierarchical(base_parse) 
                      && !base_parse->path_len) {
                        /* need to include an extra '/' before end path */
                        pathlen++;
                    }

                    /* move the query and fragment so they're correctly placed
                     * relative to the new path */
                    if (movelen) {
                        memmove(dst + pathlen, dst + base_parse->path_len, 
                          movelen);
                    }

                    if (uri_hierarchical(base_parse) 
                      && !base_parse->path_len) {
                        /* copy extra '/' then end path */
                        *dst++ = '/';
                        memcpy(dst, src, end_parse->path_len);
                        base_parse->path_len = end_parse->path_len + 1;
                        dst += end_parse->path_len;
                        src += end_parse->path_len;
                    } else {
                        uri_path_append(dst, &base_parse->path_len, src, 
                          end_parse->path_len, 1, back);
                        dst += base_parse->path_len;
                        src += end_parse->path_len;
                    }
                }

                /* copy query from end to base */
                if (end_parse->seps & URI_SEP_QUERY) {
                    if (base_parse->seps & URI_SEP_FRAG) {
                        /* need to move the fragment so it is correctly placed
                         * relative to the new query */
                        memmove(dst + 1 + end_parse->query_len, 
                          dst + (base_parse->seps & URI_SEP_QUERY ? 1 : 0)
                            + base_parse->query_len,
                          base_parse->frag_len + 1);
                    }
                    memcpy(dst, src, end_parse->query_len + 1); /* copy query */
                    src += end_parse->query_len + 1; /* skip over query */
                    dst += end_parse->query_len + 1; /* skip over query */
                } 
                base_parse->query_len = end_parse->query_len;
                base_parse->seps &= ~URI_SEP_QUERY;
                base_parse->seps |= end_parse->seps & URI_SEP_QUERY;
            }

            /* copy fragment across */
            if (end_parse->seps & URI_SEP_FRAG) {
                assert(*src == '#');
                /* copy fragment and separator */
                memcpy(dst, src, end_parse->frag_len + 1); 
                src += end_parse->frag_len + 1;
                dst += end_parse->frag_len + 1;
            }
            base_parse->frag_len = end_parse->frag_len;
            base_parse->seps &= ~URI_SEP_FRAG;
            base_parse->seps |= end_parse->seps & URI_SEP_FRAG;
        }
    }
    return URI_OK;
}

/* returns the number of bytes until the last segment in the path.  note that
 * the delimiting slash of the last segment is included in the last segment.
 * forward allows '/' to delimit the segment, back allows '\\'. */
static unsigned int lastseg(char *path, unsigned int len, int forward, 
  int back) {
    unsigned int i;

    for (i = len; i > 0 && (!forward || path[i - 1] != '/') 
      && (!back || path[i - 1] != '\\'); i--) ;

    if (i) {
        return len - i;
    } else {
        return len;
    }
}

void uri_path_append(char *base, unsigned int *base_len, 
  const char *end, unsigned int end_len, int forward, int back) {
    unsigned int pos = *base_len - lastseg(base, *base_len, forward, back);

    assert(forward || back);

    /* step over slash delimiting last segment, if there is one */
    if ((forward && (base[pos] == '/')) 
      || (back && (base[pos] == '\\'))) {
        pos++;
    }

    memcpy(base + pos, end, end_len);
    *base_len = pos + end_len;
}

unsigned int uri_path_append_length(char *base, unsigned int base_len, 
  const char *end, unsigned int end_len, int forward, int back) {
    unsigned int pos = base_len - lastseg(base, base_len, forward, back);

    assert(forward || back);

    /* step over slash delimiting last segment, if there is one */
    if ((forward && (base[pos] == '/')) 
      || (back && (base[pos] == '\\'))) {
        pos++;
    }

    return pos + end_len;
}

#ifdef URI_TEST

#include <string.h>
#include <stdlib.h>

static const char *uri_strerror(enum uri_ret err) {
    switch (err) {
    default: return "unknown error";
    case URI_ERR: return "unexpected error";
    case URI_PARSE_ERR: return "malformed input";
    case URI_CHAR_ERR: return "illegal character in input";
    case URI_MEM_ERR: return "couldn't allocate memory";
    }
}

enum uri_ret uri_parse_str(const char *uri, struct uri_parsed *parse) {
    return uri_parse(uri, strlen(uri), parse);
}

enum uri_ret test_uri(char *uri, int verbose, const char *res) {
    struct uri_parsed p;
    enum uri_ret ret;

    if ((ret = uri_parse_str(uri, &p)) != URI_OK) {
        fprintf(stderr, "failed to parse uri '%s', %s (at '%c' (pos %u))\n", 
          uri, uri_strerror(ret), 
          uri_parse_char ? *uri_parse_char : ' ', 
          uri_parse_char ? uri_parse_char - uri: 0);
        return ret;
    }
    if ((ret = uri_normalise(uri, &p)) != URI_OK) {
        fprintf(stderr, "failed to normalise uri '%s', %s\n", uri,
          uri_strerror(ret));
        return ret;
    }
    if (verbose) {
        uri_print(uri, &p, stdout); 
        putc('\n', stdout);
    }
    if (res) {
        uri[uri_length(&p)] = '\0';
        if (strcmp(uri, res)) {
            fprintf(stderr, 
              "incorrect normalisation: expecting '%s', got '%s'\n", res, uri);
            assert("incorrect result" && 0);
            return URI_ERR;
        }
    }

    return URI_OK;
}

enum uri_ret test_const_uri(const char *uri, int verbose, const char *res) {
    char buf[BUFSIZ + 1];
    assert(strlen(uri) < BUFSIZ);
    strcpy(buf, uri);
    return test_uri(buf, verbose, res);
}

enum uri_ret test_append_uri(const char *base, const char *end, int verbose, 
  const char *res) {
    char buf[BUFSIZ + 1];
    struct uri_parsed bp, ep;
    enum uri_ret ret;

    assert(strlen(base) + strlen(end) + 1 < BUFSIZ);
    strcpy(buf, base);

    if ((ret = uri_parse_str(buf, &bp)) != URI_OK) {
        fprintf(stderr, "failed to parse uri '%s', %s (at '%c' (pos %u))\n", 
          buf, uri_strerror(ret), 
          uri_parse_char ? *uri_parse_char : ' ', 
          uri_parse_char ? uri_parse_char - base: 0);
        return ret;
    }

    if ((ret = uri_parse_str(end, &ep)) != URI_OK) {
        fprintf(stderr, "failed to parse uri '%s', %s (at '%c' (pos %u))\n", 
          end, uri_strerror(ret), 
          uri_parse_char ? *uri_parse_char : ' ', 
          uri_parse_char ? uri_parse_char - end: 0);
        return ret;
    }

    if ((ret = uri_append(buf, &bp, end, &ep)) != URI_OK) {
        fprintf(stderr, "failed to append uri's '%s' and '%s': %s\n", 
          base, end, uri_strerror(ret));
        return ret;
    }

    if ((ret = uri_normalise(buf, &bp)) != URI_OK) {
        fprintf(stderr, "failed to normalise combined uri, %s\n", 
          uri_strerror(ret));
        return ret;
    }

    if (verbose) {
        uri_print(buf, &bp, stdout); 
        putc('\n', stdout);
    }
    if (res) {
        buf[uri_length(&bp)] = '\0';
        if (strcmp(buf, res)) {
            fprintf(stderr, 
              "incorrect normalisation: expecting '%s', got '%s'\n", res, buf);
            assert("incorrect result" && 0);
            return URI_ERR;
        }
    }

    return URI_OK;
}

void test_file(FILE *fp, int verbose) {
    char buf[BUFSIZ + 1];
    unsigned int len;

    while (fgets(buf, BUFSIZ, fp)) {
        len = strlen(buf);
        if (len) {
            assert(buf[len - 1] == '\n');
            buf[len - 1] = '\0';
        }
        if (verbose) {
            printf("parsing '%s'\n", buf);
        }
        test_uri(buf, verbose, NULL);
    }
}

int main(int argc, char **argv) {
    unsigned int i;
    int verbose = 0;
    FILE *fp;

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if ((fp = fopen(argv[i], "rb"))) {
                test_file(fp, verbose);
                fclose(fp);
            } else {
                fprintf(stderr, "failed to open file '%s'\n", argv[i]);
                return EXIT_FAILURE;
            }
        }
    } else {
        test_file(stdin, verbose);
    }

    /* examples from section 5.4 of RFC3986 */

    if (test_append_uri("http://a/b/c/d;p?q", "g:h", verbose, "g:h")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "g", verbose, "http://a/b/c/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "./g", verbose, 
      "http://a/b/c/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "g/", verbose, 
      "http://a/b/c/g/")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "/g", verbose, "http://a/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "//g", verbose, "http://g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "?y", verbose, 
      "http://a/b/c/d;p?y")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "g?y", verbose, 
      "http://a/b/c/g?y")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "#s", verbose, 
      "http://a/b/c/d;p?q#s")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "g#s", verbose, 
      "http://a/b/c/g#s")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "g?y#s", verbose, 
      "http://a/b/c/g?y#s")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", ";x", verbose, 
      "http://a/b/c/;x")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "g;x", verbose, 
      "http://a/b/c/g;x")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "g;x?y#s", verbose, 
      "http://a/b/c/g;x?y#s")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "", verbose, 
      "http://a/b/c/d;p?q")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", ".", verbose, 
      "http://a/b/c/")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "./", verbose, 
      "http://a/b/c/")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "..", verbose, 
      "http://a/b/")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "../g", verbose, 
      "http://a/b/g")) {
        return EXIT_FAILURE;
    }

    /* note: this test differs from the official URI test suite because it
     * involves the empty path, which this parser normalises to '', instead of
     * the recommended '/' */
    if (test_append_uri("http://a/b/c/d;p?q", "../..", verbose, 
      "http://a")) {
        return EXIT_FAILURE;
    }

    /* note: this test differs from the official URI test suite because it
     * involves the empty path, which this parser normalises to '', instead of
     * the recommended '/' */
    if (test_append_uri("http://a/b/c/d;p?q", "../../", verbose, 
      "http://a")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", "../../g", verbose, 
      "http://a/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "../../../g", verbose, "http://a/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "../../../../g", verbose, "http://a/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "/./g", verbose, "http://a/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "/../g", verbose, "http://a/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g.", verbose, "http://a/b/c/g.")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      ".g", verbose, "http://a/b/c/.g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g..", verbose, "http://a/b/c/g..")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "..g", verbose, "http://a/b/c/..g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "./../g", verbose, "http://a/b/g")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "./g/.", verbose, "http://a/b/c/g/")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g/./h", verbose, "http://a/b/c/g/h")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g/../h", verbose, "http://a/b/c/h")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g;x=1/./y", verbose, "http://a/b/c/g;x=1/y")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g;x=1/../y", verbose, "http://a/b/c/y")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g?y/./x", verbose, "http://a/b/c/g?y/./x")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g?y/../x", verbose, "http://a/b/c/g?y/../x")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g#s/./x", verbose, "http://a/b/c/g#s/./x")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "g#s/../x", verbose, "http://a/b/c/g#s/../x")) {
        return EXIT_FAILURE;
    }

    if (test_append_uri("http://a/b/c/d;p?q", 
      "http:g", verbose, "http://a/b/c/g")) {
        return EXIT_FAILURE;
    }

    /* other examples */

    if (test_const_uri(
      "FOO://@EXAmple.com:0008042///o\\../over%2fthere?name=ferret#nose", 
      verbose, "foo://example.com:8042/over/there?name=ferret#nose")) {
        return EXIT_FAILURE;
    }

    if (test_const_uri("", verbose, "")) {
        return EXIT_FAILURE;
    }

    if (test_const_uri("//g", verbose, NULL)) {
        return EXIT_FAILURE;
    }


    if (test_const_uri("%2fa%2fb%2Fc%2F%2e%2F%2e%2e%2f%2e%2e%2fg", 
      verbose, "/a/g")) {
        return EXIT_FAILURE;
    }

    if (test_const_uri("/a/b/c/./../../g", verbose, "/a/g")) {
        return EXIT_FAILURE;
    }

    if (test_const_uri("mid/content=5/../6", verbose, "mid/6")) {
        return EXIT_FAILURE;
    }

    if (test_const_uri("foo://example.com:8042/over/there?name=ferret#nose", 
      verbose, NULL)) {
        return EXIT_FAILURE;
    }

    if (test_const_uri("urn:example:animal:ferret:nose", verbose, NULL)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

#endif

