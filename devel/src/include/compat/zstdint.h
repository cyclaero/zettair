#ifndef ZSTDINT_H
#define ZSTDINT_H

#include "config.h"

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif 

#include <limits.h>

#ifndef UINT32_MAX
#define UINT32_MAX UINT_MAX
#endif

#ifndef UINT16_MAX
#define UINT16_MAX USHRT_MAX
#endif

#endif

