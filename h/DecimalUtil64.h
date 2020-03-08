#ifndef ___faiNumber_DecimalUtil64_H___
#define ___faiNumber_DecimalUtil64_H___
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
/* DecimalUtil64 Parsers */
int decToInt64 (const char * restrict str, int64_t * const output);
int decToInt64TrueError (const char * restrict str, int64_t * const output);
int decToUInt64 (const char * restrict str, uint64_t * const output);
int decToUInt64TrueError (const char * restrict str, uint64_t * const output);

/* DecimalUtil64 Flexi Parsers */
int decToInt64FP (const char * restrict str, const size_t from, const size_t to,
                  int64_t * const output, const unsigned int options);

int decToInt64FN (const char * restrict str, int64_t * const output,
                  const unsigned int options);

int decToUInt64FP (const char * restrict str, const size_t from, const size_t to,
                   uint64_t * const output, const unsigned int options);

int decToUInt64FN (const char * restrict str, uint64_t * const output,
                   const unsigned int options);

/* DecimalUtil64 Continuous Parsers */
int decToInt64C1 (const char * restrict str, int64_t * const output, char ** const nextPTR,
                  const unsigned int options);

int decToUInt64C1 (const char * restrict str, uint64_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* DecimalUtil64 Comparators */
int decCompareAsInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int decInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);
int decCompareAsUInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int decUInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - DecimalUtil64.h */
