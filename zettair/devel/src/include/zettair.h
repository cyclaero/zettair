/* zettair.h defines feature macros to allow us to use the
 * functions we want (primarily POSIX, but a few other bits and pieces
 * too) on Mac OS X and FreeBSD
 *
 * written nml 2004-07-07
 *
 */

#ifndef ZETTAIR_H
#define ZETTAIR_H

/* indicate what the directory separator character is for this OS */
#define OS_SEPARATOR '/'

#include <unistd.h>
#include <sys/types.h>
#include <math.h>

#define ZET_MT

#define PACKAGE "zettair"
#define PACKAGE_VERSION "0.9.4 - projectstore.net"

#endif

