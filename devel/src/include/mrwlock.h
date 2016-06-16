/* mrwlock.h declares an interface to a multiple-reader, multiple-writer lock.
 * This lock was designed to control access to an index, and should be modified
 * as access policies change.
 *
 * Essentially, the lock allows multiple-readers to be active,
 * or multiple-writers, but not both.  In addition, starvation is avoided by
 * preventing new operations starting when operations of the opposing type are
 * pending.  Constraints can be imposed on the number of simultaneous readers 
 * and/or writers.
 *
 * written nml 2006-09-11
 *
 */

#ifndef MRWLOCK_H
#define MRWLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

enum mrwlock_ret {
    MRWLOCK_OK = 0,

    MRWLOCK_EINVAL = -1,
    MRWLOCK_NOLOCK = -2
};

struct mrwlock;

/* create a new multiple-read/write lock.  readers is the number of
 * simultaneous readers, writers is the number of simultaneous writers, wrexcl
 * is whether reading and writing are mutually exclusive. */
struct mrwlock *mrwlock_new(unsigned int readers, unsigned int writers, 
  int wrexcl);

/* delete a lock, waiting for readers and writes that are active if necessary */
enum mrwlock_ret mrwlock_delete(struct mrwlock *lock);

/* obtain a read lock, waiting if necessary */
enum mrwlock_ret mrwlock_rlock(struct mrwlock *lock);

/* obtain a write lock, waiting if necessary */
enum mrwlock_ret mrwlock_wlock(struct mrwlock *lock);

/* return a write lock */
enum mrwlock_ret mrwlock_wunlock(struct mrwlock *lock);

/* return a read lock */
enum mrwlock_ret mrwlock_runlock(struct mrwlock *lock);

#ifdef __cplusplus
}
#endif

#endif

