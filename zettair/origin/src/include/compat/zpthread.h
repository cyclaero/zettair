/* zpthread.h includes the pthread primitives, and also declares
 * dummies in case multi-threaded access is not desired.
 *
 * written nml 2006-11-24
 *
 */

#ifndef ZPTHREAD_H
#define ZPTHREAD_H

#include "def.h"
#include "config.h"

enum {
    ZPTHREAD_OK = 0
};

/* ZPTHREAD_CONCURRENT, which is specific to zpthread, indicates whether 
 * threads actually run concurrently, or whether the dummy, serial versions 
 * are used. */

#if defined(HAVE_PTHREAD_H) && defined(ZET_MT)

/* include real pthread operations */
#include <pthread.h>

#define ZPTHREAD_CONCURRENT 1

/* alias dummy operations to them */

typedef pthread_t zpthread_t;
typedef pthread_attr_t zpthread_attr_t;
typedef pthread_mutex_t zpthread_mutex_t;
typedef pthread_mutexattr_t zpthread_mutexattr_t;
typedef pthread_cond_t zpthread_cond_t;
typedef pthread_condattr_t zpthread_condattr_t;

#define zpthread_cond_init pthread_cond_init
#define zpthread_cond_signal pthread_cond_signal
#define zpthread_cond_broadcast pthread_cond_broadcast
#define zpthread_cond_wait pthread_cond_wait
#define zpthread_cond_destroy pthread_cond_destroy
#define zpthread_mutex_init pthread_mutex_init
#define zpthread_mutex_lock pthread_mutex_lock
#define zpthread_mutex_trylock pthread_mutex_trylock
#define zpthread_mutex_unlock pthread_mutex_unlock
#define zpthread_mutex_destroy pthread_mutex_destroy
#define zpthread_self pthread_self
#define zpthread_create pthread_create
#define zpthread_join pthread_join

#define ZPTHREAD_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
#define ZPTHREAD_COND_INITIALIZER PTHREAD_COND_INITIALIZER

#else  /* don't use real pthread operations, declare dummies */

#define ZPTHREAD_CONCURRENT 0

/* declare dummy pthread data-types and operations.  This list is not
 * complete, but you can add to it as necessary (including dummy
 * definition in zpthread.c). */

typedef void *zpthread_t; 
typedef int zpthread_attr_t; 
typedef int zpthread_mutex_t;
typedef int zpthread_mutexattr_t;
typedef int zpthread_cond_t;
typedef int zpthread_condattr_t;

#define ZPTHREAD_MUTEX_INITIALIZER 0

int zpthread_cond_init(zpthread_cond_t *cond, const zpthread_condattr_t *attr);
int zpthread_cond_signal(zpthread_cond_t *cond);
int zpthread_cond_broadcast(zpthread_cond_t *cond);
int zpthread_cond_wait(zpthread_cond_t *cond, zpthread_mutex_t *mutex);
int zpthread_cond_destroy(zpthread_cond_t *cond);

int zpthread_mutex_init(zpthread_mutex_t *mutex, 
  const zpthread_mutexattr_t *mutexattr);
int zpthread_mutex_lock(zpthread_mutex_t *mutex);
int zpthread_mutex_trylock(zpthread_mutex_t *mutex);
int zpthread_mutex_unlock(zpthread_mutex_t *mutex);
int zpthread_mutex_destroy(zpthread_mutex_t *mutex);

zpthread_t zpthread_self(void);

int zpthread_create(zpthread_t *thread, zpthread_attr_t *attr, 
  void *(*start_routine)(void *), void *arg);
int zpthread_join(zpthread_t th, void **thread_return);

#endif

#endif

