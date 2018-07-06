//  utf8.h
//  searchd
//
//  Created by Dr. Rolf Jansen on 2016-06-18.
//  Copyright © 2016 projectworld.net. All rights reserved.


#include <stdint.h>

#ifndef false
#define false ((boolean)0)
#endif

#ifndef true
#define true  ((boolean)1)
#endif

typedef unsigned int  boolean;
typedef unsigned int  utf8;
typedef unsigned int  utf32;
typedef unsigned char uchar;


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

   #define TwoChars(x)   (uint16_t)SwapInt16(*(uint16_t *)(x))
   #define ThreeChars(x) (uint32_t)SwapTri24(*(uint32_t *)(x))
   #define FourChars(x)  (uint32_t)SwapInt32(*(uint32_t *)(x))

   #if (defined(__i386__) || defined(__x86_64__)) && defined(__GNUC__)

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

   #endif

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

   #if defined(__x86_64__) && defined(__GNUC__)

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

   #define MapShort(x)   (x)
   #define MapInt(x)     (x)
   #define MapInt64(x)   (x)
   #define MapDouble(x)  (x)

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

static inline double SwapDouble(double x)
{
   double z;
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


static inline char LowChar(char c)
{
   return ('A' <= c && c <= 'Z') ? c + 0x20 : c;
}

static inline char UpChar(char c)
{
   return ('a' <= c && c <= 'z') ? c - 0x20 : c;
}

static inline uint16_t TwoLowChars(char *s)
{
   uint16_t z = TwoChars(s);
   char *p = (char *)&z;
   p[0] = LowChar(p[0]);
   p[1] = LowChar(p[1]);
   return z;
}

static inline uint32_t FourLowChars(char *s)
{
   uint32_t z = FourChars(s);
   char *p = (char *)&z;
   p[0] = LowChar(p[0]);
   p[1] = LowChar(p[1]);
   p[2] = LowChar(p[2]);
   p[3] = LowChar(p[3]);
   return z;
}

static inline char *lowercase(char *s)
{
   if (s)
   {
      char c, *p = s;
      while (c = *p)
         if ('A' <= c && c <= 'Z')
            *p++ = c + 0x20;
         else
            p++;
   }
   return s;
}

static inline char *uppercase(char *s)
{
   if (s)
   {
      char c, *p = s;
      while (c = *p)
         if ('a' <= c && c <= 'z')
            *p++ = c - 0x20;
         else
            p++;
   }
   return s;
}


#if defined(__x86_64__)

   #include <x86intrin.h>

   static const __m128i nul16 = {0x0000000000000000ULL, 0x0000000000000000ULL};  // 16 bytes with nul
   static const __m128i lfd16 = {0x0A0A0A0A0A0A0A0AULL, 0x0A0A0A0A0A0A0A0AULL};  // 16 bytes with line feed '\n'
   static const __m128i vtt16 = {0x0B0B0B0B0B0B0B0BULL, 0x0B0B0B0B0B0B0B0BULL};  // 16 bytes with vertical tabs '\v'
   static const __m128i col16 = {0x3A3A3A3A3A3A3A3AULL, 0x3A3A3A3A3A3A3A3AULL};  // 16 bytes with colon ':'
   static const __m128i grt16 = {0x3E3E3E3E3E3E3E3EULL, 0x3E3E3E3E3E3E3E3EULL};  // 16 bytes with greater sign '>'
   static const __m128i vtl16 = {0x7C7C7C7C7C7C7C7CULL, 0x7C7C7C7C7C7C7C7CULL};  // 16 bytes with vertical line '|'
   static const __m128i dot16 = {0x2E2E2E2E2E2E2E2EULL, 0x2E2E2E2E2E2E2E2EULL};  // 16 bytes with dots '.'
   static const __m128i sls16 = {0x2F2F2F2F2F2F2F2FULL, 0x2F2F2F2F2F2F2F2FULL};  // 16 bytes with slashes '/'
   static const __m128i amp16 = {0x2626262626262626ULL, 0x2626262626262626ULL};  // 16 bytes with ampersand '&'
   static const __m128i equ16 = {0x3D3D3D3D3D3D3D3DULL, 0x3D3D3D3D3D3D3D3DULL};  // 16 bytes with equal signs '='
   static const __m128i blk16 = {0x2020202020202020ULL, 0x2020202020202020ULL};  // 16 bytes with inner blank limit
   static const __m128i obl16 = {0x2121212121212121ULL, 0x2121212121212121ULL};  // 16 bytes with outer blank limit

   // Drop-in replacement for strlen() and memvcpy(), utilizing some builtin SSSE3 instructions
   static inline int strvlen(const char *str)
   {
      if (!str || !*str)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)str), nul16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)str%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&str[len]), nul16)))
            return len + __builtin_ctz(bmask);
   }

   static inline void memvcpy(void *dst, const void *src, size_t n)
   {
      size_t k;

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
               (( uint8_t *)dst)[k] = (( uint8_t *)src)[k];
         case 0:
            ;
      }
   }


   static inline int linelen(const char *line)
   {
      if (!line || !*line)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)line), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)line), lfd16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)line%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&line[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&line[len]), lfd16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int sectlen(const char *sect)
   {
      if (!sect || !*sect)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)sect), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)sect), vtt16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)sect%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&sect[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&sect[len]), vtt16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int collen(const char *col)
   {
      if (!col || !*col)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)col), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)col), col16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)col%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&col[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&col[len]), col16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int taglen(const char *tag)
   {
      if (!tag || !*tag)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)tag), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)tag), grt16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)tag%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&tag[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&tag[len]), grt16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int fieldlen(const char *field)
   {
      if (!field || !*field)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)field), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)field), vtl16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)field%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&field[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&field[len]), vtl16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int domlen(const char *domain)
   {
      if (!domain || !*domain)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)domain), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)domain), dot16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)domain%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&domain[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&domain[len]), dot16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int segmlen(const char *segm)
   {
      if (!segm || !*segm)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)segm), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)segm), sls16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)segm%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&segm[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&segm[len]), sls16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int vdeflen(const char *vardef)
   {
      if (!vardef || !*vardef)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)vardef), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)vardef), amp16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)vardef%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&vardef[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&vardef[len]), amp16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int vnamlen(const char *varname)
   {
      if (!varname || !*varname)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)varname), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)varname), equ16)))
         return __builtin_ctz(bmask);

      for (int len = 16 - (intptr_t)varname%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&varname[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&varname[len]), equ16)))
            return len + __builtin_ctz(bmask);
   }

   static inline int wordlen(const char *word)
   {
      if (!word || !*word)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(blk16, _mm_max_epu8(blk16, _mm_loadu_si128((__m128i *)word)))))
         return __builtin_ctz(bmask);      // ^^^^^^^ unsigned comparison (a >= b) is identical to a == maxu(a, b) ^^^^^^^

      for (int len = 16 - (intptr_t)word%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(blk16, _mm_max_epu8(blk16, _mm_load_si128((__m128i *)&word[len])))))
            return len + __builtin_ctz(bmask);
   }

   static inline int blanklen(const char *blank)
   {
      if (!blank || !*blank)
         return 0;

      unsigned bmask;
      if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i *)blank), nul16))
                | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(obl16, _mm_min_epu8(obl16, _mm_loadu_si128((__m128i *)blank)))))
         return __builtin_ctz(bmask);      // ^^^^^^^ unsigned comparison (a <= b) is identical to a == minu(a, b) ^^^^^^^

      for (int len = 16 - (intptr_t)blank%16;; len += 16)
         if (bmask = (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_load_si128((__m128i *)&blank[len]), nul16))
                   | (unsigned)_mm_movemask_epi8(_mm_cmpeq_epi8(obl16, _mm_min_epu8(obl16, _mm_load_si128((__m128i *)&blank[len])))))
            return len + __builtin_ctz(bmask);
   }


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

#else

   #define strvlen(s) (int)strlen(s)
   #define memvcpy(d,s,n)  memcpy(d,s,n)

   static inline int linelen(const char *line)
   {
      if (!line || !*line)
         return 0;

      int l;
      for (l = 0; line[l] && line[l] != '\n'; l++)
         ;
      return l;
   }

   static inline int sectlen(const char *sect)
   {
      if (!sect || !*sect)
         return 0;

      int l;
      for (l = 0; sect[l] && sect[l] != '\v'; l++)
         ;
      return l;
   }

   static inline int collen(const char *col)
   {
      if (!col || !*col)
         return 0;

      int l;
      for (l = 0; col[l] && col[l] != ':'; l++)
         ;
      return l;
   }

   static inline int taglen(const char *tag)
   {
      if (!tag || !*tag)
         return 0;

      int l;
      for (l = 0; tag[l] && tag[l] != '>'; l++)
         ;
      return l;
   }

   static inline int fieldlen(const char *field)
   {
      if (!field || !*field)
         return 0;

      int l;
      for (l = 0; field[l] && field[l] != '|'; l++)
         ;
      return l;
   }

   static inline int domlen(const char *domain)
   {
      if (!domain || !*domain)
         return 0;

      int l;
      for (l = 0; domain[l] && domain[l] != '.'; l++)
         ;
      return l;
   }

   static inline int segmlen(const char *segm)
   {
      if (!segm || !*segm)
         return 0;

      int l;
      for (l = 0; segm[l] && segm[l] != '/'; l++)
         ;
      return l;
   }

   static inline int vdeflen(const char *vardef)
   {
      if (!vardef || !*vardef)
         return 0;

      int l;
      for (l = 0; vardef[l] && vardef[l] != '&'; l++)
         ;
      return l;
   }

   static inline int vnamlen(const char *varname)
   {
      if (!varname || !*varname)
         return 0;

      int l;
      for (l = 0; varname[l] && varname[l] != '='; l++)
         ;
      return l;
   }

   static inline int wordlen(const char *word)
   {
      if (!word || !*word)
         return 0;

      int l;
      for (l = 0; (uint8_t)word[l] > ' '; l++)
         ;
      return l;
   }

   static inline int blanklen(const char *blank)
   {
      if (!blank || !*blank)
         return 0;

      int l;
      for (l = 0; blank[l] && (uint8_t)blank[l] <= ' '; l++)
         ;
      return l;
   }


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
            *l = (int)strlen(src);
         k = *l;
      }
      else
         k = (int)strlen(src);

      if (!m)
         n = k;
      else
         n = (k < m) ? k : m-1;

      strlcpy(dst, src, n+1);
      return n;
   }

#endif


// String concat to dst with variable number of src/len pairs, whereby each len
// serves as the l parameter in strmlcpy(), i.e. strmlcpy(dst, src, ml, &len)
// m: Max. capacity of dst, including the final nul.
//    If m == 0, then the sum of the length of all src strings is returned in l - nothing is copied though.
// l: On entry, offset into dst or -1, when -1, the offset is the end of the initial string in dst
//    On exit, the length of the total concat, even if it would not fit into dst, maybe NULL.
// Returns the length of the resulting string in dst.
int strmlcat(char *dst, int m, int *l, ...);


static inline boolean cmp2(void *a, void *b)
{
   return *(uint16_t *)a == *(uint16_t *)b;
}

static inline boolean cmp3(void *a, void *b)
{
   return *(uint8_t *)a == *(uint8_t *)b && cmp2((uint8_t *)a+1, (uint8_t *)b+1);
}

static inline boolean cmp4(void *a, void *b)
{
   return *(uint32_t *)a == *(uint32_t *)b;
}

static inline boolean cmp5(void *a, void *b)
{
   return *(uint8_t *)a == *(uint8_t *)b && cmp4((uint8_t *)a+1, (uint8_t *)b+1);
}

static inline boolean cmp6(void *a, void *b)
{
   return cmp2(a, b) && cmp4((uint8_t *)a+2, (uint8_t *)b+2);
}

static inline boolean cmp7(void *a, void *b)
{
   return cmp3(a, b) && cmp4((uint8_t *)a+3, (uint8_t *)b+3);
}

static inline boolean cmp8(void *a, void *b)
{
#if !defined(__arm__)
   return *(uint64_t *)a == *(uint64_t *)b;
#else
   return cmp4(a, b) && cmp4((uint8_t *)a+4, (uint8_t *)b+4);
#endif
}

static inline boolean cmp9(void *a, void *b)
{
   return *(uint8_t *)a == *(uint8_t *)b && cmp8((uint8_t *)a+1, (uint8_t *)b+1);
}

static inline boolean cmp10(void *a, void *b)
{
   return cmp2(a, b) && cmp8((uint8_t *)a+2, (uint8_t *)b+2);
}

static inline boolean cmp11(void *a, void *b)
{
   return cmp3(a, b) && cmp8((uint8_t *)a+3, (uint8_t *)b+3);
}

static inline boolean cmp12(void *a, void *b)
{
   return cmp4(a, b) && cmp8((uint8_t *)a+4, (uint8_t *)b+4);
}

static inline boolean cmp13(void *a, void *b)
{
   return cmp5(a, b) && cmp8((uint8_t *)a+5, (uint8_t *)b+5);
}

static inline boolean cmp16(void *a, void *b)
{
   return cmp8(a, b) && cmp8((uint8_t *)a+8, (uint8_t *)b+8);
}


static inline void cpy2(void *a, void *b)
{
  *(uint16_t *)a = *(uint16_t *)b;
}

static inline void cpy3(void *a, void *b)
{
   cpy2(a, b), *(uint8_t *)((uint8_t *)a+2) = *(uint8_t *)((uint8_t *)b+2);
}

static inline void cpy4(void *a, void *b)
{
   *(uint32_t *)a = *(uint32_t *)b;
}

static inline void cpy5(void *a, void *b)
{
   cpy4(a, b), *(uint8_t *)((uint8_t *)a+4) = *(uint8_t *)((uint8_t *)b+4);
}

static inline void cpy6(void *a, void *b)
{
   cpy4(a, b), cpy2((uint8_t *)a+4, (uint8_t *)b+4);
}

static inline void cpy7(void *a, void *b)
{
   cpy4(a, b), cpy3((uint8_t *)a+4, (uint8_t *)b+4);
}

static inline void cpy8(void *a, void *b)
{
#if !defined(__arm__)
   *(uint64_t *)a = *(uint64_t *)b;
#else
   cpy4(a, b), cpy4((uint8_t *)a+4, (uint8_t *)b+4);
#endif
}

static inline void cpy9(void *a, void *b)
{
   cpy8(a, b), *(uint8_t *)((uint8_t *)a+8) = *(uint8_t *)((uint8_t *)b+8);
}

static inline void cpy10(void *a, void *b)
{
   cpy8(a, b), cpy2((uint8_t *)a+8, (uint8_t *)b+8);
}

static inline void cpy11(void *a, void *b)
{
   cpy8(a, b), cpy3((uint8_t *)a+8, (uint8_t *)b+8);
}

static inline void cpy12(void *a, void *b)
{
   cpy8(a, b), cpy4((uint8_t *)a+8, (uint8_t *)b+8);
}

static inline void cpy13(void *a, void *b)
{
   cpy8(a, b), cpy5((uint8_t *)a+8, (uint8_t *)b+8);
}

static inline void cpy16(void *a, void *b)
{
   cpy8(a, b), cpy8((uint8_t *)a+8, (uint8_t *)b+8);
}


// forward skip white space  !!! s MUST NOT be NULL !!!
static inline char *skip(char *s)
{
   for (;;)
      switch (*s)
      {
         case '\t'...'\r':
         case ' ':
            s++;
            break;

         default:
            return s;
      }
}

// backward skip white space  !!! s MUST NOT be NULL !!!
static inline char *bskip(char *s)
{
   for (;;)
      switch (*--s)
      {
         case '\t'...'\r':
         case ' ':
            break;

         default:
            return s+1;
      }
}

static inline char *trim(char *s)
{
   *bskip(s+strvlen(s)) = '\0';
   return skip(s);
}


// jump to the stop mark  !!! s MUST NOT be NULL !!!
static inline char *jump(char *s, char stop)
{
   boolean q, sq, dq;
   char    c;

   for (q = sq = dq = false; (c = *s) && (c != stop || q); s++)
      if (c == '\'' && !dq)
         q = sq = !sq;
      else if (c == '"' && !sq)
         q = dq = !dq;

   return s;
}


static inline utf8 getu(char **s)
{
   utf8 u = 0;
   char c = **s;

   if ((uint8_t)c < 0x80)
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

static inline int putu(utf8 u, char *t)
{
   int l;

   if (u <= 0x7F)
      *t = (char)u,                           l = 1;

   else if (u <= 0xFFFF)
      *(uint16_t *)t = MapShort((uint16_t)u), l = 2;

   else if (u <= 0xFFFFFF)
   {
      char v[4] = {};
      *(uint32_t *)v = MapInt(u);
      t[0] = v[1];
      t[1] = v[2];
      t[2] = v[3],                            l = 3;
   }

   else
      *(uint32_t *)t = MapInt(u),             l = 4;

   return l;
}

char *casefold(char *p);

#if defined __APPLE__

   #define pathfold(p) casefold(p)

#elif defined __FreeBSD__

   #define pathfold(p) (p)

#endif
