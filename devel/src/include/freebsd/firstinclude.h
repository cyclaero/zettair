/* freebsd/firstinclude.h defines feature macros to allow us to use the
 * functions we want (primarily POSIX, but a few other bits and pieces
 * too) on freebsd
 *
 * written nml 2003-04-24
 *
 */

#ifndef FIRSTINCLUDE_H
#define FIRSTINCLUDE_H

#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64           /* large file support */
#endif

/* indicate what the directory separator character is for this OS */
#define OS_SEPARATOR '/'

#include <unistd.h>
#include <sys/types.h>

#include "config.h"

/* declare "don't break me" flag for win32 compatibility */
#define O_BINARY 0

#endif

