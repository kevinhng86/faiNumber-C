#ifndef ___faiNumber_OctalUtil32_H___
#define ___faiNumber_OctalUtil32_H___
/* Copyright 2020 Khang Hoang Nguyen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "faiNumberConsts.h"
/* OctalUtil32 Parsers */
int octToInt32 (const char * restrict str, int32_t * const output);
int octToInt32TrueError (const char * restrict str, int32_t * const output);
int octToUInt32 (const char * restrict str, uint32_t * const output);
int octToUInt32TrueError (const char * restrict str, uint32_t * const output);

/* OctalUtil32 Flexi Parsers */
int octToInt32FP (const char * restrict str, const size_t from, const size_t to,
                  int32_t * const output, const unsigned int options);

int octToInt32FN (const char * restrict str, int32_t * const output,
                  const unsigned int options);

int octToUInt32FP (const char * restrict str, const size_t from, const size_t to,
                   uint32_t * const output, const unsigned int options);

int octToUInt32FN (const char * restrict str, uint32_t * const output,
                   const unsigned int options);

/* OctalUtil32 Continuous Parsers */
int octToInt32C1 (const char * restrict str, int32_t * const output, char ** const nextPTR,
                  const unsigned int options);

int octToUInt32C1 (const char * restrict str, uint32_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* OctalUtil32 Comparators */
int octCompareAsInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int octInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);
int octCompareAsUInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int octUInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - OctalUtil32.h */
