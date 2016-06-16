/* mrwlock.c implements a multiple-read/write lock, as described by mrwlock.h.
 * 
 * Naturally, being seriously multi-threaded, this code is incredibly difficult
 * to read/write/debug.  Consider yourself warned.
 *
 * The purpose of this lock is to limit the number of active readers and 
 * writers to a resource.  Optionally, reading and writing can be made mutually
 * exclusive, in which case we also want to interleave reads and writes, while
 * allowing operations of the same type to proceed in parallel.
 * This is the more difficult case, so the following text discusses it alone.
 * Assuming we get a stream of requests for locks, something like the following:
 *
 *  W W R W W W R R R R W R R W W W W R R R R R R R R 
 *
 * what we want is to interleave the operations with maximum parallelisation
 * allowed.  So, we want the grouped operations below to proceed in parallel.
 * 
 *  W W R W W W R R R R W R R W W W W R R R R R R R R 
 *  \-/ | \---/ \-----/ | \_/ \-----/ \-------------/
 *
 * This is achieved by having a switching state, which allows only reads or 
 * only writes to proceed.  However, switching without deadlock or livelock is
 * difficult.  Say we receive a request for a write when we are currently
 * allowing reads to proceed.  Since the write is blocked, the state starts to
 * switch and new reads are forced to wait.  However, we need to wait until the
 * reads that have already started to finish before we allow the write to start.
 * During this time, both read and write requests are queued.
 * Once the last active read request has finished, the state can switch to
 * writing, and queued writes can proceed.  However, read requests may have
 * piled up during this period of time, suggesting the need to switch back.
 * We allow a period of hysteresis, where all of the writes queued at the time
 * of the switch may proceed, but not necessarily more.
 * After the period of hysteresis, the switch back to reading may begin if 
 * there are queued read requests.  This process protects the invariant that
 * there are active threads of only one type at a time (of course, none of this
 * applies if reads and writes can proceed simultaneously). 
 *
 * Interleaving reads and writes is the tricky part.  Once that is done, a
 * second stage monitors the number of active threads of each type at a time.
 * If a thread wants to start, but exceeds the active limit, then it is passed
 * through the switching stage, but deemed passive.  Passive threads run
 * immediately after active threads of the same type finish.  
 *
 * written nml 2006-09-11
 *
 */

#include "firstinclude.h"

#include "mrwlock.h"

#include "def.h"
#include "zpthread.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>

enum lockstate {
    LOCKSTATE_EITHER = 0,           /* both reads and writes can proceed */
    LOCKSTATE_NEITHER = 1,          /* neither reads nor writes can proceed */
    LOCKSTATE_READ = 2,             /* reads may proceed */
    LOCKSTATE_WRITE = 3,            /* writes may proceed */
    LOCKSTATE_NEVER = 4             /* can't get a lock, go home (shutting 
                                     * down) */
};

const char *mwrlock_lockstates(enum lockstate ls) {
    switch (ls) {
    case LOCKSTATE_EITHER: return "either";
    case LOCKSTATE_NEITHER: return "neither";
    case LOCKSTATE_READ: return "read";
    case LOCKSTATE_WRITE: return "write";
    case LOCKSTATE_NEVER: return "never";
    default: return "!not recognised!";
    }
}

struct lockset {
    unsigned int active;            /* number active */
    unsigned int passive;           /* number accepted but not active */
    unsigned int waiting;           /* number waiting */
    unsigned int max_active;        /* maximum active number */
    zpthread_cond_t passive_cond;    /* condition variable waited on by 
                                     * passive threads */
    zpthread_cond_t waiting_cond;    /* condition variable waited on by 
                                     * waiting threads */
};

struct mrwlock {
    zpthread_mutex_t mutex;          /* mutex controls access to the lock */
    enum lockstate state;           /* state governing when and if reads 
                                     * and writes can proceed */
    unsigned int hysteresis;        /* number of threads that can pass in the 
                                     * current state (only applies to READ 
                                     * and WRITE states) */
    struct lockset reader;          /* condition variables and counters for 
                                     * reading */
    struct lockset writer;          /* condition variables and counters for 
                                     * writing */
};

struct mrwlock *mrwlock_new(unsigned int readers, unsigned int writers, 
  int wrexcl) {
    struct mrwlock *lock = malloc(sizeof(*lock));
    int pret;

    if (lock) {
        if (wrexcl) {
            lock->state = LOCKSTATE_READ;
        } else {
            lock->state = LOCKSTATE_EITHER;
        }
        lock->hysteresis = 0;
        lock->reader.active = lock->reader.passive = lock->reader.waiting = 0;
        lock->writer.active = lock->writer.passive = lock->writer.waiting = 0;
        lock->reader.max_active = readers;
        lock->writer.max_active = writers;
        pret = zpthread_cond_init(&lock->reader.passive_cond, NULL); 
        assert(pret == 0);
        pret = zpthread_cond_init(&lock->reader.waiting_cond, NULL); 
        assert(pret == 0);
        pret = zpthread_cond_init(&lock->writer.passive_cond, NULL); 
        assert(pret == 0);
        pret = zpthread_cond_init(&lock->writer.waiting_cond, NULL); 
        assert(pret == 0);
        pret = zpthread_mutex_init(&lock->mutex, NULL); assert(pret == 0);
    }

    return lock;
}

#define PFAIL(ret)                                                            \
    switch (ret) {                                                            \
    default:                                                                  \
    case EINVAL: return MRWLOCK_EINVAL;                                       \
    case EDEADLK: assert("deadlock" && 0); return MRWLOCK_EINVAL;             \
    }

enum mrwlock_ret mrwlock_delete(struct mrwlock *lock) {
    int pret;

    if ((pret = zpthread_mutex_lock(&lock->mutex)) == ZPTHREAD_OK) {
        /* prevent anything else from waiting for locks */
        lock->state = LOCKSTATE_NEVER;

        /* get rid of waiting threads of both types (they should exit
         * immediately) */
        pret = zpthread_cond_broadcast(&lock->reader.waiting_cond);
        assert(pret == ZPTHREAD_OK);
        pret = zpthread_cond_broadcast(&lock->writer.waiting_cond);
        assert(pret == ZPTHREAD_OK);

        /* pretend to be a passive reader thread, to wait until the queue 
         * is empty */
        lock->reader.passive++;
        while (lock->reader.active || (lock->reader.passive > 1)) {
            assert(lock->reader.max_active);

            if ((pret 
              = zpthread_cond_wait(&lock->reader.passive_cond, &lock->mutex)) 
                == ZPTHREAD_OK) {

                /* propagate signal to other waiters, if any */
                pret = zpthread_cond_signal(&lock->reader.passive_cond);
                assert(pret == ZPTHREAD_OK);
            } else {
                PFAIL(pret);
            }
        }
        lock->reader.passive--;
        assert(lock->reader.passive == 0);
        assert(lock->reader.active == 0);

        /* pretend to be a passive writer thread, to wait until the queue 
         * is empty */
        lock->writer.passive++;
        while (lock->writer.active || (lock->writer.passive > 1)) {
            assert(lock->writer.max_active);

            if ((pret 
              = zpthread_cond_wait(&lock->writer.passive_cond, &lock->mutex)) 
                == 0) {

                /* propagate signal to other waiters, if any */
                pret = zpthread_cond_signal(&lock->writer.passive_cond);
                assert(pret == ZPTHREAD_OK);
            } else {
                PFAIL(pret);
            }
        }
        lock->writer.passive--;
        assert(lock->writer.passive == 0);
        assert(lock->writer.active == 0);

        pret = zpthread_cond_destroy(&lock->reader.waiting_cond);
        assert(pret == ZPTHREAD_OK);
        pret = zpthread_cond_destroy(&lock->reader.passive_cond);
        assert(pret == ZPTHREAD_OK);
        pret = zpthread_cond_destroy(&lock->writer.waiting_cond);
        assert(pret == ZPTHREAD_OK);
        pret = zpthread_cond_destroy(&lock->writer.passive_cond);
        assert(pret == ZPTHREAD_OK);
        pret = zpthread_mutex_unlock(&lock->mutex);
        assert(pret == ZPTHREAD_OK);
        pret = zpthread_mutex_destroy(&lock->mutex);
        assert(pret == ZPTHREAD_OK);
        free(lock);
        return MRWLOCK_OK;
    } else {
        PFAIL(pret);
    }
}

/* internal function to handle the symmetrical cases for reading and writing
 * lock */
static enum mrwlock_ret mrwlock_lock(struct mrwlock *lock, 
  struct lockset *wanted, struct lockset *other, int read) {
    int pret;

    if ((pret = zpthread_mutex_lock(&lock->mutex)) == ZPTHREAD_OK) {
        /* check that we can eventually acquire a lock */
        if (lock->state == LOCKSTATE_NEVER || wanted->max_active == 0) {
            return MRWLOCK_NOLOCK;
        }

        if ((lock->hysteresis == 0) 
          && ((read && (lock->state == LOCKSTATE_WRITE))
            || (!read && (lock->state == LOCKSTATE_READ)))) {

            /* this thread wants a lock of the non-activated type, and 
             * hysteresis is inactive. start switch by blocking all new 
             * threads of the activated type. */
            assert(wanted->active == 0);
            assert(wanted->passive == 0);
            if (other->active || other->passive) {
                /* threads of the other type are active, wait until 
                 * they finish */
                lock->state = LOCKSTATE_NEITHER;
            } else {
                /* no threads of the other type are active or passive, switch 
                 * all of the way */
                lock->state = read ? LOCKSTATE_READ : LOCKSTATE_WRITE;
                lock->hysteresis = wanted->waiting;
            }
        }

        /* wait until this type of transaction has been activiated */
        wanted->waiting++;
        while (lock->state != LOCKSTATE_EITHER 
          && ((read && (lock->state != LOCKSTATE_READ))
            || (!read && (lock->state != LOCKSTATE_WRITE)))) {

            if ((pret = zpthread_cond_wait(&wanted->waiting_cond, &lock->mutex)) 
              != ZPTHREAD_OK) {
                wanted->waiting--;
                PFAIL(pret);
            }

            /* check whether we can obtain a lock (may change, as _delete
             * function utilises this) */
            if (lock->state == LOCKSTATE_NEVER || wanted->max_active == 0) {
                return MRWLOCK_NOLOCK;
            } 
        }
        wanted->waiting--;
        if (lock->hysteresis > 0) {
            lock->hysteresis--;
        }

        /* this type of thread *must* be currently active */
        if (lock->state != LOCKSTATE_EITHER) {
            assert(!read || lock->state == LOCKSTATE_READ);
            assert(read || lock->state == LOCKSTATE_WRITE);
        }

        /* avoid starving waiting threads of the other type, by starting to 
         * switch if nothing remains waiting from this type */
        if (lock->state != LOCKSTATE_EITHER 
          && !lock->hysteresis && other->waiting) {
            /* note that this thread will always have a chance to complete the
             * switch in _unlock, so we never switch all of the way, unlike
             * similar code above */
            assert(other->active == 0 && other->passive == 0);
            lock->state = LOCKSTATE_NEITHER;
        }

        /* Now wait until a free 'activity' slot opens up.  Note that we don't
         * fuse this loop with the previous so that threads, once accepted, can
         * proceed to activity regardless of whether we stop accepting further
         * threads of that type, but still limit the number of active threads of
         * that type at one time. */
        wanted->passive++;
        while (wanted->active >= wanted->max_active) {
            if (lock->state == LOCKSTATE_NEVER || wanted->max_active == 0) {
                wanted->passive--;
                return MRWLOCK_NOLOCK;
            }

            if ((pret = zpthread_cond_wait(&wanted->passive_cond, &lock->mutex)) 
              != ZPTHREAD_OK) {
                wanted->passive--;
                PFAIL(pret);
            }
        }
        wanted->passive--;

        /* lock acquired */
        assert(wanted->active < wanted->max_active);
        wanted->active++;
        pret = zpthread_mutex_unlock(&lock->mutex);
        assert(pret == ZPTHREAD_OK);
        return MRWLOCK_OK;
    } else {
        PFAIL(pret);
    }
}

enum mrwlock_ret mrwlock_rlock(struct mrwlock *lock) {
    return mrwlock_lock(lock, &lock->reader, &lock->writer, 1);
}

enum mrwlock_ret mrwlock_wlock(struct mrwlock *lock) {
    return mrwlock_lock(lock, &lock->writer, &lock->reader, 0);
}

/* internal function to handle the symmetrical cases for reading and writing
 * unlock */
static enum mrwlock_ret mrwlock_unlock(struct mrwlock *lock, 
  struct lockset *wanted, struct lockset *other, int read) {
    int pret;
    unsigned int signal = 0;   /* number of signals sent */

    if ((pret = zpthread_mutex_lock(&lock->mutex)) == ZPTHREAD_OK) {
        assert(wanted->active > 0);
        wanted->active--;

        /* if both are able to proceed, nothing should be waiting */
        assert((lock->state != LOCKSTATE_EITHER)
          || (wanted->waiting == 0 && other->waiting == 0));

        /* unless both are able to proceed, there should be no active or 
         * passive threads waiting for locks of the other type */
        assert((lock->state == LOCKSTATE_EITHER) || other->passive == 0);
        assert((lock->state == LOCKSTATE_EITHER) || other->active == 0);

        /* signal passive threads of this type to start */
        for (signal = 0; signal < wanted->passive 
          && wanted->active + signal < wanted->max_active; signal++) {
            pret = zpthread_cond_signal(&wanted->passive_cond);
            assert(pret == ZPTHREAD_OK);
        }

        /* if we are the last active or passive thread, and the state is
         * changing to the other type, complete change */
        if (!wanted->active && !wanted->passive 
          && lock->state == LOCKSTATE_NEITHER) {
            assert(other->waiting);
            assert(!other->passive);
            assert(!other->active);
            lock->state = read ? LOCKSTATE_WRITE : LOCKSTATE_READ;
            lock->hysteresis = other->waiting;

            /* signal waiting threads of other type to proceed */
            zpthread_cond_broadcast(&other->waiting_cond);

        /* if threads of the other type are waiting, prevent starvation by 
         * starting switch */
        } else if (other->waiting && (lock->hysteresis == 0)
          && ((read && (lock->state == LOCKSTATE_READ))
            || (!read && (lock->state == LOCKSTATE_WRITE)))) {

            lock->state = LOCKSTATE_NEITHER;
        }

        pret = zpthread_mutex_unlock(&lock->mutex);
        assert(pret == ZPTHREAD_OK);
        return MRWLOCK_OK;
    } else {
        PFAIL(pret);
    }
}

enum mrwlock_ret mrwlock_runlock(struct mrwlock *lock) {
    return mrwlock_unlock(lock, &lock->reader, &lock->writer, 1);
}

enum mrwlock_ret mrwlock_wunlock(struct mrwlock *lock) {
    return mrwlock_unlock(lock, &lock->writer, &lock->reader, 0);
}

#ifdef MRWLOCK_TEST

#include <stdio.h>

#define LIM 100000000

void *writer(void *ptr) {
    enum mrwlock_ret mret;
    unsigned int i,
                 sum = 0;

    printf("writer %u seeking lock\n", (unsigned int) zpthread_self());
    if ((mret = mrwlock_wlock(ptr)) == MRWLOCK_OK) {
        printf("writer %u got lock\n", (unsigned int) zpthread_self());

        /* delay for a bit */
        for (i = 0; i < LIM; i++) {
            sum *= i;
        }

        printf("writer %u releasing lock\n", (unsigned int) zpthread_self());
        mrwlock_wunlock(ptr);
    } else {
        printf("failed, with ret value %d\n", mret);
    }

    return NULL;
}

void *reader(void *ptr) {
    enum mrwlock_ret mret;
    unsigned int i,
                 sum = 0;

    printf("reader %u seeking lock\n", (unsigned int) zpthread_self());
    if ((mret = mrwlock_rlock(ptr)) == MRWLOCK_OK) {
        printf("reader %u got lock\n", (unsigned int) zpthread_self());

        /* delay for a bit */
        for (i = 0; i < LIM; i++) {
            sum *= i;
        }

        printf("reader %u releasing lock\n", (unsigned int) zpthread_self());
        mrwlock_runlock(ptr);
    } else {
        printf("failed, with ret value %d\n", mret);
    }

    return NULL;
}

#define THREADS 100

int main(int argc, char **argv) {
    unsigned int i,
                 readers = 0,
                 writers = 0,
                 joined = 0;
    zpthread_t thread[THREADS];
    int pret;
    struct mrwlock *lock = mrwlock_new(5, 4, 1);
    unsigned long int seed = time(NULL);
    assert(lock);

    if (argc >= 2) {
        seed = atoi(argv[1]);
    }
   
    printf("seed is %lu\n", seed);
    srand(seed);

    for (i = 0; i < THREADS; i++) {
        unsigned int r = rand() & 1;

        if (((pret = zpthread_create(&thread[i], NULL, 
            r ? reader : writer, lock)) == 0)) {

            if (r) {
                readers++;
            } else {
                writers++;
            }
            usleep(300000);
        } else {
            fprintf(stderr, "thread create failed with %d\n", pret);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < THREADS; i++) {
        void *status;
        if ((pret = zpthread_join(thread[i], &status)) == 0) {
            /* do nothing */
            joined++;
        } else {
            fprintf(stderr, "thread join failed with %d\n", pret);
            return EXIT_FAILURE;
        }
    }

    mrwlock_delete(lock);
    printf("%u readers, %u writers, %u joined\n", readers, writers, joined);
    return EXIT_SUCCESS;
}

#endif

