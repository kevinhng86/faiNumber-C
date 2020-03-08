#ifndef ___faiNumber_OctalUtil64_H___
#define ___faiNumber_OctalUtil64_H___
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
/* OctalUtil64 Parsers */
int octToInt64 (const char * restrict str, int64_t * const output);
int octToInt64TrueError (const char * restrict str, int64_t * const output);
int octToUInt64 (const char * restrict str, uint64_t * const output);
int octToUInt64TrueError (const char * restrict str, uint64_t * const output);

/* OctalUtil64 Flexi Parsers */
int octToInt64FP (const char * restrict str, const size_t from, const size_t to,
                  int64_t * const output, const unsigned int options);

int octToInt64FN (const char * restrict str, int64_t * const output,
                  const unsigned int options);

int octToUInt64FP (const char * restrict str, const size_t from, const size_t to,
                   uint64_t * const output, const unsigned int options);

int octToUInt64FN (const char * restrict str, uint64_t * const output,
                   const unsigned int options);

/* OctalUtil64 Continuous Parsers */
int octToInt64C1 (const char * restrict str, int64_t * const output, char ** const nextPTR,
                  const unsigned int options);

int octToUInt64C1 (const char * restrict str, uint64_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* OctalUtil64 Comparators */
int octCompareAsInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int octInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);
int octCompareAsUInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int octUInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - OctalUtil64.h */
