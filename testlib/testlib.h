#ifndef ___faiNumber_testlib_H___
#define ___faiNumber_testlib_H___
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
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <setjmp.h>

#define FN_TL_JMP_BUFF jumpBuffer
#define FN_TL_JMP_CODE 1
/*
 * @NOTE: FN_TL_**** Macros are important, and is being used across
 *        the bechmark units macros. Any future change have to give
 *        consideration to the benchmark units.
 **/
#define FN_TL_NO_SIGN 0
#define FN_TL_RAND_SIGN 1
#define FN_TL_NEG_ONLY 2
#define FN_TL_POS_ONLY 3
#define FN_TL_SIGN_OPTION_MAX 3

/* These macro below is used incase the expansion options */
#define FN_TL_WITHL0 0
#define FN_TL_NOL0 1

extern jmp_buf FN_TL_JMP_BUFF;
extern const int FN_GETPOINTINTIME_V;

char ** mkRandomDigitStrings
        (const size_t arraySize, size_t nMinLen, size_t nMaxLen,
         const unsigned int digitMin, const unsigned int digitMax,
         const unsigned int maxFirstDigit, const unsigned int signOption,
         const unsigned int noL0
        );

long long getPointInTime();

int _getRandom32 (const int minimum, const int maximum);
int __getRandom32 (const int minimum, const int maximum);
int (*getRandom32)(const int minimum, const int maximum);

void abortJMP(int signum);

#endif    /* faiNumber - testlib.h */
