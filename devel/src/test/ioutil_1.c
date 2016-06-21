/*
 *  Test the ioutil functions.
 *
 *  written wew 2006-06-20
 *
 *  ioutil_atomic_read and ioutil_atomic_write are designed
 *  to prevent "short" reads.  Simulating a "short" read,
 *  however, is not that straightforward :-).  Here, we
 *  use fork() and communication via pipes.  The parent
 *  manages the fixture, and the child does the test.  The
 *  exit value of the child is used by the parent to determine
 *  whether the test succeeded or failed.
 */

#include "zettair.h"

#include "test.h"
#include "ioutil.h"

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_WAIT_TRIES 10

/**
 *  Test the atomic_read function.  DAT_SIZE is the total size of
 *  the data to transfer; READ_SIZE is how much will be read
 *  in each atomic_read call; WRITE_SIZE is how much to write
 *  in each write call; and INTERVAL_MS is the number of milliseconds
 *  to sleep between each write.  Note that this function will take
 *  at least (DAT_SIZE / WRITE_SIZE) * INTERVAL_MS milliseconds to
 *  run.  If VERBOSE is set, then debugging messages will be
 *  printed.  If OVERREAD is set, then we will deliberately
 *  not abbreviate the final read request to DAT_SIZE % READ_SIZE,
 *  and test to make sure the read fails.
 */
static int test_atomic_read(unsigned dat_size, unsigned read_size,
  unsigned write_size, unsigned interval_ms, int verbose, int overread) {
    int fd[2];
    pid_t pid;
    if ( (pipe(fd)) != 0) {
        perror("failed to create pipes");
        return 0;
    }
    pid = fork();
    if (pid < 0) {
        perror("failed to fork");
        return 0;
    }
    if (pid != 0) {
        /* parent. */
        int i;
        struct timespec slp_time;
        char * buf;
        unsigned total_written;
        int wait_tries;
        int ret;

        slp_time.tv_sec = interval_ms / 1000;
        slp_time.tv_nsec = (interval_ms % 1000) * 1000 * 1000;
        close(fd[0]);
        buf = malloc(write_size);
        if (buf == NULL) {
            perror("allocating memory");
            return 0;
        }
        for (i = 0; i < write_size; i++) {
            buf[i] = (char) i;
        }
        slp_time.tv_sec = 0;
        slp_time.tv_nsec = interval_ms * 1000 * 1000;
        total_written = 0;
        while (total_written < dat_size) {
            ssize_t w;
            size_t towrite;

            if (write_size > dat_size - total_written)
                towrite = dat_size - total_written;
            else
                towrite = write_size;
            w = write(fd[1], buf, towrite);
            if (w < 0) {
                perror("writing to pipe");
                return 0;
            }
            total_written += w;
            if ( (ret = nanosleep(&slp_time, NULL)) != 0
              && ret != EINTR) {
                perror("nanosleeping");
                return 0;
            }
        }
        close(fd[1]);  /* signal EOF.  Don't forget this! */
        free(buf);
        for (wait_tries = 0; wait_tries < MAX_WAIT_TRIES; wait_tries++) {
            pid_t wpid;
            int status;
            wpid = waitpid(pid, &status, WNOHANG);
            if (wpid < 0) {
                perror("Waiting for child");
            } else if (wpid != 0) {
                if (WIFEXITED(status)) {
                    if (WEXITSTATUS(status) != 0) {
                        if (verbose)
                            fprintf(stderr, "Child exited with status %d\n",
                              WEXITSTATUS(status));
                        return 0;
                    } else {
                        return 1;
                    }
                } else {
                    if (verbose)
                        fprintf(stderr, 
                          "Child did not exit normally!  Status %d\n", status);
                }
            }
            if ( (ret = nanosleep(&slp_time, NULL)) != 0
              && ret != EINTR) {
                perror("nanosleeping");
                return 0;
            }
        }
    } else {
        /* child. */
        char * buf;
        unsigned total_read;

        if (verbose)
            fprintf(stderr, "Child started\n");
        close(fd[1]);
        buf = malloc(read_size);
        if (buf == NULL) {
            perror("allocating memory in child");
            exit(1);
        }
        total_read = 0;
        while (total_read < dat_size) {
            ssize_t r;
            size_t toread;
            if (!overread && read_size > dat_size - total_read)
                toread = dat_size - total_read;
            else
                toread = read_size;
            r = ioutil_atomic_read(fd[0], buf, toread);
            if (overread && toread > dat_size - total_read) {
                if (r >= 0) {
                    exit(1);
                } else {
                    exit(0);
                }
            } else if (r != toread) {
                if (verbose)
                    fprintf(stderr, "Child wrong read length: asked for %u, "
                      "got %d, total so far %u, data size %u\n", read_size,
                      r, total_read, dat_size);
                exit(1);
            }
            if (verbose)
                fprintf(stderr, "Read %d\n", r);
            total_read += r;
        }
        if (ioutil_atomic_read(fd[0], buf, 1) > 0) {
            if (verbose)
                fprintf(stderr, "Extra read did not fail!\n");
            exit(1);
        }
        if (verbose)
            fprintf(stderr, "Child finished\n");
        if (total_read > dat_size) {
            exit(1);
        } else {
            exit(0);
        }
    }
    if (verbose)
        fprintf(stderr, "Gave up waiting for child to finish\n");
    return 0;
}

/**
 *  Test the atomic write function. DAT_SIZE is the total size of
 *  the data to transfer; READ_SIZE is how much will be read in each
 *  read call; and WRITE_SIZE is how much will be written in each call
 *  to ioutil_atomic_write.  If VERBOSE is set, then debugging 
 *  messages will be printed.
 *
 *  XXX NOTE that because the ioutil_atomic_IO functions do not
 *  work properly with non-blocking fds, there is no reliable
 *  way to generate short writes (signals not being a reliable
 *  mechanism).  Therefore we are essentially just testing here
 *  whether io_util_atomic_write calls write(2) correctly.
 */
static int test_atomic_write(unsigned dat_size, unsigned read_size,
  unsigned write_size, int verbose) {
    int fd[2];
    pid_t pid;
    if ( (pipe(fd)) != 0) {
        perror("failed to create pipes");
        return 0;
    }
    pid = fork();
    if (pid < 0) {
        perror("failed to fork");
        return 0;
    }
    if (pid != 0) {
        /* parent. */
        int i;
        char * buf;
        unsigned total_written;
        int wait_tries;
        int ret;
        int retval = 1;

        close(fd[0]);
        buf = malloc(write_size);
        if (buf == NULL) {
            perror("allocating memory");
            return 0;
        }
        for (i = 0; i < write_size; i++) {
            buf[i] = (char) i;
        }
        total_written = 0;
        while (total_written < dat_size) {
            ssize_t w;
            size_t towrite;

            if (write_size > dat_size - total_written)
                towrite = dat_size - total_written;
            else
                towrite = write_size;
            w = ioutil_atomic_write(fd[1], buf, towrite);
            if (w != towrite) {
                retval = 0;
            }
        }
        close(fd[1]);  /* signal EOF.  Don't forget this! */
        free(buf);
        for (wait_tries = 0; wait_tries < MAX_WAIT_TRIES; wait_tries++) {
            pid_t wpid;
            int status;
            struct timespec slp_time;

            slp_time.tv_sec = 0; 
            slp_time.tv_nsec = 10 * 1000 * 1000;
            wpid = waitpid(pid, &status, WNOHANG);
            if (wpid < 0) {
                perror("Waiting for child");
            } else if (wpid != 0) {
                if (WIFEXITED(status)) {
                    if (WEXITSTATUS(status) != 0) {
                        if (verbose)
                            fprintf(stderr, "Child exited with status %d\n",
                              WEXITSTATUS(status));
                        return 0;
                    } else {
                        return retval;
                    }
                } else {
                    if (verbose)
                        fprintf(stderr, 
                          "Child did not exit normally!  Status %d\n", status);
                }
            }
            if ( (ret = nanosleep(&slp_time, NULL)) != 0
              && ret != EINTR) {
                perror("nanosleeping");
                return 0;
            }
        }
    } else {
        /* child. */
        char * buf;
        unsigned total_read;

        if (verbose)
            fprintf(stderr, "Child started\n");
        close(fd[1]);
        buf = malloc(read_size);
        if (buf == NULL) {
            perror("allocating memory in child");
            exit(1);
        }
        total_read = 0;
        while (total_read < dat_size) {
            ssize_t r;
            size_t toread;
            if (read_size > dat_size - total_read)
                toread = dat_size - total_read;
            else
                toread = read_size;
            r = read(fd[0], buf, toread);
            if (r < 0) {
                fprintf(stderr, "Error reading in child!");
                exit(1);
            } else if (r == 0) {
                break;
            } else {
                if (verbose)
                    fprintf(stderr, "Read %d\n", r);
                total_read += r;
            }
        }
        if (verbose)
            fprintf(stderr, "Child finished\n");
        if (total_read != dat_size) {
            exit(1);
        } else {
            exit(0);
        }
    }
    if (verbose)
        fprintf(stderr, "Gave up waiting for child to finish\n");
    return 0;
}

int test_file(FILE *fp, int argc, char **argv) {
    int ret;
    int verbose = 0;

    /* ensure that we aren't testing from a file */
    if ((fp && (fp != stdin)) || (argc > 1)) {
        fprintf(stderr, "I don't accept a file argument\n");
        return 0;
    }

    if ( !(ret = test_atomic_read(4097, 4096, 512, 10, verbose, 0))) {
        return ret; 
    }
    if ( !(ret = test_atomic_read(4097, 4096, 512, 10, verbose, 1))) {
        return ret;
    }
    if ( !(ret = test_atomic_write(4097, 4096, 512, verbose))) {
        return ret; 
    }
    return 1;
}
