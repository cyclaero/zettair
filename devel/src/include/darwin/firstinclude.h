/* darwin/firstinclude.h defines feature macros to allow us to use the
 * functions we want (primarily POSIX, but a few other bits and pieces
 * too) on mac OS X and darwin
 *
 * written nml 2004-07-07
 *
 */

#ifndef FIRSTINCLUDE_H
#define FIRSTINCLUDE_H

/* indicate what the directory separator character is for this OS */
#define OS_SEPARATOR '/'

#include <unistd.h>
#include <sys/types.h>
#include <math.h>

// 
/* declare "don't break me" flag for win32 compatibility */
#define O_BINARY 0

#endif

