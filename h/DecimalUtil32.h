#ifndef ___faiNumber_DecimalUtil32_H___
#define ___faiNumber_DecimalUtil32_H___
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
/* DecimalUtil32 Parsers */
int decToInt32 (const char * restrict str, int32_t * const output);
int decToInt32TrueError (const char * restrict str, int32_t * const output);
int decToUInt32 (const char * restrict str, uint32_t * const output);
int decToUInt32TrueError (const char * restrict str, uint32_t * const output);

/* DecimalUtil32 Flexi Parsers */
int decToInt32FP (const char * restrict str, const size_t from, const size_t to,
                  int32_t * const output, const unsigned int options);

int decToInt32FN (const char * restrict str, int32_t * const output,
                  const unsigned int options);

int decToUInt32FP (const char * restrict str, const size_t from, const size_t to,
                   uint32_t * const output, const unsigned int options);

int decToUInt32FN (const char * restrict str, uint32_t * const output,
                   const unsigned int options);

/* DecimalUtil32 Continuous Parsers */
int decToInt32C1 (const char * restrict str, int32_t * const output, char ** const nextPTR,
                  const unsigned int options);

int decToUInt32C1 (const char * restrict str, uint32_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* DecimalUtil32 Comparators */
int decCompareAsInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int decInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);
int decCompareAsUInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int decUInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - DecimalUtil32.h */
