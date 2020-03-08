#ifndef ___faiNumber_HexUtil32_H___
#define ___faiNumber_HexUtil32_H___
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
/* HexUtil32 Parsers */
int hexToInt32 (const char * restrict str, int32_t * const output);
int hexToInt32TrueError (const char * restrict str, int32_t * const output);
int hexToUInt32 (const char * restrict str, uint32_t * const output);
int hexToUInt32TrueError (const char * restrict str, uint32_t * const output);

/* HexUtil32 Flexi Parsers */
int hexToInt32FP (const char * restrict str, const size_t from, const size_t to,
                  int32_t * const output, const unsigned int options);

int hexToInt32FN (const char * restrict str, int32_t * const output,
                  const unsigned int options);

int hexToUInt32FP (const char * restrict str, const size_t from, const size_t to,
                   uint32_t * const output, const unsigned int options);

int hexToUInt32FN (const char * restrict str, uint32_t * const output,
                   const unsigned int options);

/* HexUtil32 Continuous Parsers */
int hexToInt32C1 (const char * restrict str, int32_t * const output, char ** const nextPTR,
                  const unsigned int options);

int hexToUInt32C1 (const char * restrict str, uint32_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* HexUtil32 Comparators */
int hexCompareAsInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int hexInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);
int hexCompareAsUInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int hexUInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - HexUtil32.h */
