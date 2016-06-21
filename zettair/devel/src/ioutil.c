#include "zettair.h"

#include "ioutil.h"

#include <unistd.h>

/* internal function to atomically perform a read */
ssize_t ioutil_atomic_read(int fd, void *buf, unsigned int size) {
    unsigned int rlen,
                 len = size;
    char *pos = buf;

    while (len && ((rlen = read(fd, pos, len)) > 0)) {
        pos += rlen;
        len -= rlen;
    }

    if (len) {
        return -1;
    } else {
        return size;
    }
}

/* internal function to atomically perform a write */
ssize_t ioutil_atomic_write(int fd, void *buf, unsigned int size) {
    unsigned int wlen,
                 len = size;
    char *pos = buf;

    while (len && ((wlen = write(fd, pos, len)) != -1)) {
        pos += wlen;
        len -= wlen;
    }

    if (len) {
        return -1;
    } else {
        return size;
    }
}
