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

#ifndef ___faiNumber_BinaryUtil32_H___
#define ___faiNumber_BinaryUtil32_H___

/* BinaryUtil32 Parsers */
int binToInt32 (const char * restrict str, int32_t * const output);
int binToInt32TrueError (const char * restrict str, int32_t * const output);
int binToUInt32 (const char * restrict str, uint32_t * const output);
int binToUInt32TrueError (const char * restrict str, uint32_t * const output);

/* BinaryUtil32 Flexi Parsers */
int binToInt32FP (const char * restrict str, const size_t from, const size_t to,
                  int32_t * const output, const unsigned int options);

int binToInt32FN (const char * restrict str, int32_t * const output,
                  const unsigned int options);

int binToUInt32FP (const char * restrict str, const size_t from, const size_t to,
                   uint32_t * const output, const unsigned int options);

int binToUInt32FN (const char * restrict str, uint32_t * const output,
                   const unsigned int options);

/* BinaryUtil32 Continuous Parsers */
int binToInt32C1 (const char * restrict str, int32_t * const output, char ** const nextPTR,
                  const unsigned int options);

int binToUInt32C1 (const char * restrict str, uint32_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* BinaryUtil32 Comparators */
int binCompareAsInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int binInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);
int binCompareAsUInt32 (const char * restrict firstString, const char * restrict secondString, int * const output);
int binUInt32OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - BinaryUtil32.h */


#ifndef ___faiNumber_DecimalUtil32_H___
#define ___faiNumber_DecimalUtil32_H___

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


#ifndef ___faiNumber_HexUtil32_H___
#define ___faiNumber_HexUtil32_H___

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


#ifndef ___faiNumber_OctalUtil32_H___
#define ___faiNumber_OctalUtil32_H___

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



#ifndef ___faiNumber_BinaryUtil64_H___
#define ___faiNumber_BinaryUtil64_H___

/* BinaryUtil64 Parsers */
int binToInt64 (const char * restrict str, int64_t * const output);
int binToInt64TrueError (const char * restrict str, int64_t * const output);
int binToUInt64 (const char * restrict str, uint64_t * const output);
int binToUInt64TrueError (const char * restrict str, uint64_t * const output);

/* BinaryUtil64 Flexi Parsers */
int binToInt64FP (const char * restrict str, const size_t from, const size_t to,
                  int64_t * const output, const unsigned int options);

int binToInt64FN (const char * restrict str, int64_t * const output,
                  const unsigned int options);

int binToUInt64FP (const char * restrict str, const size_t from, const size_t to,
                   uint64_t * const output, const unsigned int options);

int binToUInt64FN (const char * restrict str, uint64_t * const output,
                   const unsigned int options);

/* BinaryUtil64 Continuous Parsers */
int binToInt64C1 (const char * restrict str, int64_t * const output, char ** const nextPTR,
                  const unsigned int options);

int binToUInt64C1 (const char * restrict str, uint64_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* BinaryUtil64 Comparators */
int binCompareAsInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int binInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);
int binCompareAsUInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int binUInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - BinaryUtil64.h */


#ifndef ___faiNumber_DecimalUtil64_H___
#define ___faiNumber_DecimalUtil64_H___

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


#ifndef ___faiNumber_HexUtil64_H___
#define ___faiNumber_HexUtil64_H___

/* HexUtil64 Parsers */
int hexToInt64 (const char * restrict str, int64_t * const output);
int hexToInt64TrueError (const char * restrict str, int64_t * const output);
int hexToUInt64 (const char * restrict str, uint64_t * const output);
int hexToUInt64TrueError (const char * restrict str, uint64_t * const output);

/* HexUtil64 Flexi Parsers */
int hexToInt64FP (const char * restrict str, const size_t from, const size_t to,
                  int64_t * const output, const unsigned int options);

int hexToInt64FN (const char * restrict str, int64_t * const output,
                  const unsigned int options);

int hexToUInt64FP (const char * restrict str, const size_t from, const size_t to,
                   uint64_t * const output, const unsigned int options);

int hexToUInt64FN (const char * restrict str, uint64_t * const output,
                   const unsigned int options);

/* HexUtil64 Continuous Parsers */
int hexToInt64C1 (const char * restrict str, int64_t * const output, char ** const nextPTR,
                  const unsigned int options);

int hexToUInt64C1 (const char * restrict str, uint64_t * const output, char ** const nextPTR,
                   const unsigned int options);

/* HexUtil64 Comparators */
int hexCompareAsInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int hexInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);
int hexCompareAsUInt64 (const char * restrict firstString, const char * restrict secondString, int * const output);
int hexUInt64OrSmaller (const char * restrict firstString, const char * restrict secondString);

#endif    /* faiNumber - HexUtil64.h */


#ifndef ___faiNumber_OctalUtil64_H___
#define ___faiNumber_OctalUtil64_H___

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
