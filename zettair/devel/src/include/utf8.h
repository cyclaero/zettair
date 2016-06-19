//  utf8.h
//  searchd
//
//  Created by Dr. Rolf Jansen on 2016-06-18.
//  Copyright © 2016 projectworld.net. All rights reserved.


#include <tmmintrin.h>

typedef unsigned char uchar;
typedef unsigned int  utf8;
typedef unsigned int  utf32;


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

// PickXXX-Routine are for picking data out of or
// the PostgreSQL database that tranfers binary data
// in Network Byte Order, that is big endian.
// i386 machines operate on data in little endian
// byte order, therefore byte swapping is necessary.
   #define PickInt(x)    SwapInt32(*(int32_t *)(x))
   #define PickInt64(x)  SwapInt64(*(int64_t *)(x))
   #define PickDouble(x) SwapDouble(*(double *)(x))

   #define MapShort(x)   SwapInt16(x)
   #define MapInt(x)     SwapInt32(x)
   #define MapInt64(x)   SwapInt64(x)
   #define MapDouble(x)  SwapDouble(x)
   #define MapPixel(x)   SwapLittlePixel(x)

   #define TwoChars(x)   (uint16_t)SwapInt16(*(uint16_t *)(x))
   #define ThreeChars(x) (uint32_t)SwapTri24(*(uint32_t *)(x))
   #define FourChars(x)  (uint32_t)SwapInt32(*(uint32_t *)(x))

   static inline uint16_t SwapInt16(uint16_t x)
   {
      __asm__("rolw $8,%0" : "+q" (x));
      return x;
   }

   static inline uint32_t SwapInt32(uint32_t x)
   {
      __asm__("bswapl %0" : "+q" (x));
      return x;
   }

   static inline uint32_t SwapTri24(uint32_t x)
   {
      uint32_t z;
      char *p = (char *)&x;
      char *q = (char *)&z;

      q[0] = p[2];
      q[1] = p[1];
      q[2] = p[0];
      q[3] = 0;

      return z;
   }


#if defined(__x86_64__)

   static inline uint64_t SwapInt64(uint64_t x)
   {
      __asm__("bswapq %0" : "+q" (x));
      return x;
   }

#else

   static inline uint64_t SwapInt64(uint64_t x)
   {
      uint64_t z;
      char *p = (char *)&x;
      char *q = (char *)&z;

      q[0] = p[7];
      q[1] = p[6];
      q[2] = p[5];
      q[3] = p[4];
      q[4] = p[3];
      q[5] = p[2];
      q[6] = p[1];
      q[7] = p[0];

      return z;
   }

#endif

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

// ppc machines operate on data in big endian
// byte order, therefore NO byte swapping is necessary. 
   #define PickInt(x)    *(int32_t *)(x)
   #define PickInt64(x)  *(int64_t *)(x)
   #define PickDouble(x) *(double *)(x)

   #define MapShort(x)   x
   #define MapInt(x)     x
   #define MapInt64(x)   x
   #define MapDouble(x)  x
   #define MapPixel(x)   SwapBigPixel(x)

   #define TwoChars(x)   *(uint16_t *)(x)
   #define ThreeChars(x) *(uint32_t *)(x) >> 8
   #define FourChars(x)  *(uint32_t *)(x)

#if defined(__ppc__) && defined(__GNUC__)

   static inline uint16_t SwapInt16(uint16_t x)
   {
      uint16_t z;
      __asm__("lhbrx %0,0,%1" : "=r" (z) : "r" (&x), "m" (x));
      return z;
   }

#else

   static inline uint16_t SwapInt16(uint16_t x)
   {
      uint16_t z;
      char *p = (char *)&x;
      char *q = (char *)&z;

      q[0] = p[1];
      q[1] = p[0];

      return z;
   }

#endif

   static inline uint32_t SwapInt32(uint32_t x)
   {
      uint32_t z;
      char *p = (char *)&x;
      char *q = (char *)&z;

      q[0] = p[3];
      q[1] = p[2];
      q[2] = p[1];
      q[3] = p[0];

      return z;
   }

   static inline uint64_t SwapInt64(uint64_t x)
   {
      uint64_t z;
      char *p = (char *)&x;
      char *q = (char *)&z;

      q[0] = p[7];
      q[1] = p[6];
      q[2] = p[5];
      q[3] = p[4];
      q[4] = p[3];
      q[5] = p[2];
      q[6] = p[1];
      q[7] = p[0];

      return z;
   }

#endif


#if defined(__x86_64__)

   static const __m128i nul16 = {0x0000000000000000ULL, 0x0000000000000000ULL};  // 16 bytes with nul
   static const __m128i lfd16 = {0x0A0A0A0A0A0A0A0AULL, 0x0A0A0A0A0A0A0A0AULL};  // 16 bytes with line feed
   static const __m128i vtl16 = {0x7C7C7C7C7C7C7C7CULL, 0x7C7C7C7C7C7C7C7CULL};  // 16 bytes with vertical line '|' limit
   static const __m128i obl16 = {0x2121212121212121ULL, 0x2121212121212121ULL};  // 16 bytes with outer blank limit

   // Drop-in replacement for strlen(), utilizing some builtin SSSE3 instructions
   static inline int strvlen(const char *str)
   {
      if (!*str)
         return 0;

      unsigned bmask;

      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_lddqu_si128((__m128i *)str), nul16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)str%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&str[len]), nul16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int linelen(const char *line)
   {
      if (!*line)
         return 0;

      unsigned bmask;

      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_lddqu_si128((__m128i *)line), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_lddqu_si128((__m128i *)line), lfd16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)line%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&line[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&line[len]), lfd16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int fieldlen(const char *field)
   {
      if (!*field)
         return 0;

      unsigned bmask;

      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_lddqu_si128((__m128i *)field), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_lddqu_si128((__m128i *)field), vtl16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)field%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&field[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&field[len]), vtl16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int wordlen(const char *word)
   {
      if (!*word)
         return 0;

      unsigned bmask;

      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmplt_epi8(_mm_abs_epi8(_mm_lddqu_si128((__m128i *)word)), obl16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)word%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmplt_epi8(_mm_abs_epi8(_mm_load_si128((__m128i *)&word[len])), obl16)))
            return len + __builtin_ctz(bmask);
   }

#else

   #define strvlen(s) strlen(s)

   static inline int linelen(const char *line)
   {
      if (!*line)
         return 0;

      int l;
      for (l = 0; line[l] && line[l] != '\n'; l++)
         ;
      return l;
   }

   static inline int fieldlen(const char *field)
   {
      if (!*field)
         return 0;

      int l;
      for (l = 0; field[l] && field[l] != '|'; l++)
         ;
      return l;
   }

   static inline int wordlen(const char *word)
   {
      if (!*word)
         return 0;

      int l;
      for (l = 0; word[l] > ' '; l++)
         ;
      return l;
   }

#endif


// String copying from src to dst.
// m: Max. capacity of dst, including the final nul.
//    A value of 0 would indicate that the capacity of dst matches the size of src (including nul)
// l: On entry, src length or 0, on exit, the length of src, maybe NULL
// Returns the length of the resulting string in dst.
static inline int strmlcpy(char *dst, const char *src, int m, int *l)
{
   int k, n;

   if (l)
   {
      if (!*l)
         *l = strvlen(src);
      k = *l;
   }
   else
      k = strvlen(src);

   if (!m)
      n = k;
   else
      n = (k < m) ? k : m-1;

   switch (n)
   {
      default:
         if ((intptr_t)dst&0xF || (intptr_t)src&0xF)
            for (k = 0; k  < n>>4<<1; k += 2)
               ((uint64_t *)dst)[k] = ((uint64_t *)src)[k], ((uint64_t *)dst)[k+1] = ((uint64_t *)src)[k+1];
         else
            for (k = 0; k  < n>>4; k++)
               _mm_store_si128(&((__m128i *)dst)[k], _mm_load_si128(&((__m128i *)src)[k]));
      case 8 ... 15:
         if ((k = n>>4<<1) < n>>3)
            ((uint64_t *)dst)[k] = ((uint64_t *)src)[k];
      case 4 ... 7:
         if ((k = n>>3<<1) < n>>2)
            ((uint32_t *)dst)[k] = ((uint32_t *)src)[k];
      case 2 ... 3:
         if ((k = n>>2<<1) < n>>1)
            ((uint16_t *)dst)[k] = ((uint16_t *)src)[k];
      case 1:
         if ((k = n>>1<<1) < n)
            dst[k] = src[k];
      case 0:
         ;
   }

   dst[n] = '\0';
   return n;
}

// String concat to dst with variable number of src/len pairs, whereby each len
// serves as the l parameter in strmlcpy(), i.e. strmlcpy(dst, src, ml, &len)
// m: Max. capacity of dst, including the final nul.
//    If m == 0, then the sum of the length of all src strings is returned in l - nothing is copied though.
// l: On entry, offset into dst or -1, when -1, the offset is the end of the initial string in dst
//    On exit, the length of the total concat, even if it would not fit into dst, maybe NULL.
// Returns the length of the resulting string in dst.
int strmlcat(char *dst, int m, int *l, ...);


static inline utf8 getu(char **s)
{
   utf8 u = 0;
   char c = **s;

   if (c >= 0)
      u = c;

   else if ((*s)[1] != '\0')
      if ((c & 0xE0) == 0xC0)
         u = TwoChars(*s), *s += 1;

      else if ((*s)[2] != '\0')
         if ((c & 0xF0) == 0xE0)
            u = ThreeChars(*s), *s += 2;

         else if ((*s)[3] != '\0')
            if ((c & 0xF8) == 0xF0)
               u = FourChars(*s), *s += 3;

   *s += 1;
   return u;
}

static inline utf8 putu(utf8 u, char **t)
{
   if (u <= 0x7F)
      **t = (char)u,                           *t += 1;

   else if (u <= 0xFFFF)
      *(uint16_t *)*t = MapShort((uint16_t)u), *t += 2;

   else if (u <= 0xFFFFFF)
   {
      char v[4];
      *(uint32_t *)v = MapInt(u);
      (*t)[0] = v[1];
      (*t)[1] = v[2];
      (*t)[2] = v[3],                          *t += 3;
   }

   else
      *(uint32_t *)*t = MapInt(u),             *t += 4;

   return u;
}

char *casefold(char *p);

#if defined __APPLE__

   #define pathfold(p) casefold(p)

#elif defined __FreeBSD__

   #define pathfold(p) (p)

#endif
