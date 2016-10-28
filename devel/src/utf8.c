//  utf8.c
//  searchd
//
//  Created by Dr. Rolf Jansen on 2016-06-18.
//  Copyright © 2016 projectworld.net. All rights reserved.

#include "utf8.h"


utf32 u_foldCase(utf32 u, uint32_t options);

static const uchar trailingBytesForUTF8[256] =
{
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

static const utf32 offsetsFromUTF8[6] = { 0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080 };
static const uchar firstByteMark[7]   = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
static const utf32 byteMask = 0xBF;
static const utf32 byteMark = 0x80; 

utf32 utf8to32(uchar **v)
{
   utf32 u32 = 0;
   uchar tl, *u = (*v)++;

   if (*u < 0x80)
      return *u;

   else switch (tl = trailingBytesForUTF8[*u])
   {
      default:
         return 0xFFFD;

      case 3: u32 += *u++; u32 <<= 6;
      case 2: u32 += *u++; u32 <<= 6;
      case 1: u32 += *u++; u32 <<= 6;
      case 0: u32 += *u++;
   }
   *v = u;

   return u32 - offsetsFromUTF8[tl];
}


utf8 utf32to8(utf32 u32)
{
   utf8  u8 = 0;
   uchar l;

   if      (u32 < 0x80)     l = 1;
   else if (u32 < 0x800)    l = 2;
   else if (u32 < 0x10000)  l = 3;
   else if (u32 < 0x110000) l = 4;
   else   { u32 = 0xFFFD;   l = 3; }

   uchar *u =(uchar *)&u8 + l;
   switch (l)
   {
      case 4: *--u = (uchar)((u32 | byteMark) & byteMask); u32 >>= 6;
      case 3: *--u = (uchar)((u32 | byteMark) & byteMask); u32 >>= 6;
      case 2: *--u = (uchar)((u32 | byteMark) & byteMask); u32 >>= 6;
      case 1: *--u = (uchar) (u32 | firstByteMark[l]);
   }

   return u8;
}


char *casefold(char *p)
{
   utf32  u, v;
   uchar  c, tl;
   uchar *s = (uchar *)p;
   uchar *w = (uchar *)&v;

   if (s)
      while (c = *s)
         if ('A' <= c && c <= 'Z')
            *s++ = c + 0x20;

         else if (c < 0x80)
            s++;

         else
         {
            uchar *t = s;
            if ((u = utf8to32(&t)) != 0xFFFD)
            {
               v = u_foldCase(u, 0);
               if (v != u)
                  switch (tl = trailingBytesForUTF8[c])
                  {
                     case 1:
                        *(uint16_t *)s = (uint16_t)utf32to8(v);
                        break;

                     case 2:
                        v = utf32to8(v);
                        s[0] = w[0];
                        s[1] = w[1];
                        s[2] = w[2];
                        break;

                     case 3:
                        *(uint32_t *)s = utf32to8(v);
                        break;
                  }
            }
            s = t;
         }

   return p;
}
