#ifndef ___faiNumber_uniComparator_H___
#define ___faiNumber_uniComparator_H___
/* @NOTE - THIS IS FAINUMBER-C PRIVATE INCLUDE FILE
 *       - DO NOT DIRECTLY INCLUDE THIS HEADER FILE
 */
/*
 * Copyright 2020 Khang Hoang Nguyen
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

/* ***************START UNI COMPARATOR FUNCTION MAKER**************** */
/* Function Maker: ***CompareAs*** */
#define fn_make_func_comparator_parser_as(funcName, funcToCall, intType) \
int funcName (const char * restrict firstString, const char * restrict secondString, int * const output){ \
    intType n1, n2; \
\
    if ( funcToCall(firstString, &n1) || funcToCall(secondString, &n2) ) { \
        *output = 0; \
        return 1; \
    } \
\
    if ( n1 > n2 ) *output = 1; \
    else if ( n1 < n2 ) *output = -1; \
    else *output = 0; \
\
    return 0; \
}

/* Function Maker: ***OrSmaller*** */
#define fn_make_func_comparator_parser_orsmaller(funcName, funcToCall, intType) \
int funcName (const char * restrict firstString, const char * restrict secondString){ \
    intType n1, n2; \
    int e1 = funcToCall(firstString, &n1), \
        e2 = funcToCall(secondString, &n2); \
\
    if ( !e1 ) { \
        if ( e1 == e2 ) { \
            if ( n1 > n2 ) return 1; \
            else if ( n1 < n2 ) return -1; \
            return 0; \
        } \
\
        return 1; \
    } else if ( !e2 ) return -1; \
\
    e1 = e1 == FN_ERROR_INVALID_FORMAT? 0 : e1; \
    e2 = e2 == FN_ERROR_INVALID_FORMAT? 0 : e2; \
\
    if ( e1 > e2 ) return 1; \
    else if ( e1 < e2 ) return -1; \
    return 0; \
}
/* ****************END UNI COMPARATOR FUNCTION MAKER***************** */

#endif    /* faiNumber - uniComparator.h */
