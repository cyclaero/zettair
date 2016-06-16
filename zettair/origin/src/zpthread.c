/* zpthread.c implements dummy pthread operations, for when
 * multi-threaded access is not desired 
 *
 * written nml 2006-11-24
 *
 */

#include "firstinclude.h"

#include "zpthread.h"

#if defined(HAVE_PTHREAD_H) && defined(ZET_MT)

int zpthread_concurrent(void) {
    return 1;
}

#else

int zpthread_concurrent(void) {
    return 0;
}

/* define dummy functions */

int zpthread_create(zpthread_t *thread, zpthread_attr_t *attr, 
  void *(*start_routine)(void *), void *arg) {
    *thread = start_routine(arg);
    return ZPTHREAD_OK;
}

int zpthread_join(zpthread_t thread, void **thread_return) {
    *thread_return = thread;
    return ZPTHREAD_OK;
}

zpthread_t pthread_self(void) {
    return NULL;
}

int zpthread_cond_init(zpthread_cond_t *cond, const zpthread_condattr_t *attr) {
    return ZPTHREAD_OK;
}

int zpthread_cond_signal(zpthread_cond_t *cond) {
    return ZPTHREAD_OK;
}

int zpthread_cond_broadcast(zpthread_cond_t *cond) {
    return ZPTHREAD_OK;
}

int zpthread_cond_wait(zpthread_cond_t *cond, zpthread_mutex_t *mutex) {
    return ZPTHREAD_OK;
}

int zpthread_cond_destroy(zpthread_cond_t *cond) {
    return ZPTHREAD_OK;
}

int zpthread_mutex_init(zpthread_mutex_t *mutex, 
  const zpthread_mutexattr_t *mutexattr) {
    return ZPTHREAD_OK;
}

int zpthread_mutex_lock(zpthread_mutex_t *mutex) {
    return ZPTHREAD_OK;
}

int zpthread_mutex_trylock(zpthread_mutex_t *mutex) {
    return ZPTHREAD_OK;
}

int zpthread_mutex_unlock(zpthread_mutex_t *mutex) {
    return ZPTHREAD_OK;
}

int zpthread_mutex_destroy(zpthread_mutex_t *mutex) {
    return ZPTHREAD_OK;
}

#endif

