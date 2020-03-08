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
/* faiNumber - testlib.c */
#include "testlib.h"

jmp_buf FN_TL_JMP_BUFF;

/*
 * For fast processing getRandom32 functions does not check for
 * wheather min > max or maximum > RAND_MAX. Use with care.
 **/
int (*getRandom32)(const int minimum, const int maximum) = &_getRandom32;

int _getRandom32 ( const int minimum, const int maximum ){
    getRandom32 = &__getRandom32;
    srand( (unsigned)getPointInTime() );
    return (rand() % (maximum + 1 - minimum)) + minimum;
}

int __getRandom32 ( const int minimum, const int maximum ){
    return (rand() % (maximum + 1 - minimum)) + minimum;
}

/*
 * It is an assumption that if CLOCK_REALTIME is available
 * then clock_gettime() must be available.
 *
 * @NOTE: getPointInTime()'s purpose is to get two points in time to
 *        measure execution time. Thus, depend on the build enviroment.
 *        this function may return a clock tick time, or an actual
 *        timestamp, both are in milliseconds.
 *
 *        The FN_GETPOINTINTIME_V is for debugging purpose. It its
 *        value equal to 1 then that mean getPointInTime()'s
 *        return value is an actual timestamp. If its value is equal
 *        to 2 then getPointInTime()'s may or may not return an
 *        actual timestamp but a clock tick time. May or may not is
 *        because version 2 of getPointInTime() may get update.
 *
 *        The return value will be type long long.
 **/
#ifdef CLOCK_REALTIME
const int FN_GETPOINTINTIME_V = 1;
long long getPointInTime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ((long long)ts.tv_sec * 1000) + (ts.tv_nsec/1000000L);
}
/* If clock_gettime() is not available, fall back to c standard clock() */
#else
const int FN_GETPOINTINTIME_V = 2;
long long getPointInTime() {
    return (long long)(clock() / (CLOCKS_PER_SEC / 1000));
}
#endif

char ** mkRandomDigitStrings
        (const size_t arraySize, size_t nMinLen, size_t nMaxLen,
         const unsigned int digitMin, const unsigned int digitMax,
         const unsigned int maxFirstDigit, const unsigned int signOption,
         const unsigned int noL0
        ){
    const static char digits[] = {'0','1','2','3','4','5','6','7','8','9',
                                  'a','b','c','d','e','f','g','h','i','j',
                                  'k','l','m','n','o','p','q','r','s','t',
                                  'u','v','w','x','y','z'
                                 };
    if ( digitMin > 35 || digitMax > 35 || maxFirstDigit > 35 || digitMin > digitMax ) return NULL;

    char ** output = (char **)malloc(arraySize * sizeof(char*));
    if ( output == NULL ) return NULL;
    /*
     * Although, this waste some memory, it is the fastest to do.
     *
     * It is possible to freed the unused memory with realloc(),
     * and if the return pointer is not the same as the original. It
     * index is re-calculate to match the pointer.
     *
     * char * base = base str;
     * char * str = str;
     * char * temp = new base;
     *
     * if ( temp != base ) array[i] = temp + (array[i] - base);
     *
     * That will cost execution time but reduce memory footprint and memory leak.
     * Due to randomness, probably half of the memory reserved for * str
     * won't be used.
     **/

    char * str = (char *)malloc((arraySize * nMaxLen) + (arraySize << 2));
    if ( str == NULL){
        free(output);
        return NULL;
    }
    size_t strLen;

    switch (signOption){
        case FN_TL_NO_SIGN: goto no_sign;
        case FN_TL_RAND_SIGN: goto rand_sign;
        case FN_TL_NEG_ONLY: goto neg_only;
        case FN_TL_POS_ONLY: goto pos_only;
        default: goto no_sign;
    }

    /*  No Sign */
    no_sign:
    for (size_t i = 0 ; i < arraySize; i++){
        output[i] = str;
        strLen = getRandom32(nMinLen, nMaxLen);
        if ( strLen == nMaxLen ) {
            *(str++) = digits[getRandom32(digitMin, maxFirstDigit)];
            strLen--;
        }
        while( strLen-- ) *(str++) = digits[getRandom32(digitMin, digitMax)];
        *(str++) = 0;
        if ( noL0 ){
            if ( output[i][0] == digits[0] ) output[i][0] = digits[1];
        }
    }
    goto end;

    /*  Random Sign */
    rand_sign:
    for (size_t i = 0 ; i < arraySize; i++){
        unsigned int sign;
        output[i] = str;
        strLen = getRandom32(nMinLen, nMaxLen);
        if ( (sign = getRandom32(0, 1)) )
          *(str++) = getRandom32(0, 1)? 45 : 43;
        if ( strLen == nMaxLen ){
            *(str++) = digits[getRandom32(digitMin, maxFirstDigit)];
            strLen--;
        }
        while ( strLen-- ) *(str++) = digits[getRandom32(digitMin, digitMax)];
        *(str++) = 0;
        if ( noL0 ){
            if ( output[i][sign] == digits[0] ) output[i][sign] = digits[1];
        }
    }
    goto end;

    /*  Negative Sign Only */
    neg_only:
    for (size_t i = 0; i < arraySize; i++){
        output[i] = str;
        strLen = getRandom32(nMinLen, nMaxLen);
        *(str++) = 45;
        if ( strLen == nMaxLen ) {
            *(str++) = digits[getRandom32(digitMin, maxFirstDigit)];
            strLen--;
        }
        while( strLen-- ) *(str++) = digits[getRandom32(digitMin, digitMax)];
        *(str++) = 0;
        if ( noL0 ){
            if ( output[i][1] == digits[0] ) output[i][1] = digits[1];
        }
    }
    goto end;

    /*  Positive Sign Only */
    pos_only:
    for (size_t i = 0; i < arraySize; i++){
        output[i] = str;
        strLen = getRandom32(nMinLen, nMaxLen);
        *(str++) = 43;
        if ( strLen == nMaxLen ) {
            *(str++) = digits[getRandom32(digitMin, maxFirstDigit)];
            strLen--;
        }
        while( strLen-- ) *(str++) = digits[getRandom32(digitMin, digitMax)];
        *(str++) = 0;
        if ( noL0 ){
            if ( output[i][1] == digits[0] ) output[i][1] = digits[1];
        }
    }

    end:
    return output;
}

void abortJMP(int signum){
    longjmp(FN_TL_JMP_BUFF, FN_TL_JMP_CODE);
}
