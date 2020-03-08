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
/* faiNumber - HexUtil32.c */
#include "../h/HexUtil32.h"

/* START INTERNAL MACRO INCLUSION */
#include "../uni/uniMacro.h"
/* END INTERNAL MACRO INCLUSION */

/*
 * null = 200 | 32( ) = 252 | 43(+) = 253 | 45(-) = 254 | inv = 255
 *
 * For future, if expand to support more bases, for each base, it is
 * better to have this digit map array as a file scope variable. There
 * are only 256 indexes in this array. Without alignment, that is only
 * 256 bytes.
 *
 **/
static const unsigned char fnv_local_dmap[] = { 200,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,252,255,255,255,255,255,255,255,255,255,255,253,255,254,
    255,255,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,255,255,255,
    255,255,255,255, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
     21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    255,255,255,255,255,255, 10, 11, 12, 13, 14, 15, 16, 17, 18,
     19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
     34, 35,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
};

int hexToInt32 (const char * restrict str, int32_t * const output){
    int32_t result;
    unsigned int isNeg;

    /* START Sign Check */
    switch ( *str ){
        case 0: fn_parser_err_ret_0(output, FN_ERROR_GENERAL);
        case 45: {
            if ( !*(++str) ) fn_parser_err_ret_0(output, FN_ERROR_GENERAL);
            isNeg = 1;
            break;
        }
        case 43: {
            if ( !*(++str) ) fn_parser_err_ret_0(output, FN_ERROR_GENERAL);
            isNeg = 0;
            break;
        }
        default: {
            isNeg = 0;
            break;
        }
    }
    /* END Sign Check */

    /* START Skip Leading 0s */
    while ( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ){
        *output = 0;
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_GENERAL;
    }
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* End First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START hexToInt32 UNROLL MACRO */
#define hexToInt32_loop_unroll  \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ){ \
        *output = isNeg? -result : result; \
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToInt32_loop_unroll;
    hexToInt32_loop_unroll;
    hexToInt32_loop_unroll;
    hexToInt32_loop_unroll;
    hexToInt32_loop_unroll;
    hexToInt32_loop_unroll;

#undef hexToInt32_loop_unroll
/* END hexToInt32 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_GENERAL);

        if ( isNeg ) {
            if ( result > 134217727 ) {
                if ( result > 134217728 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_GENERAL);
                if ( fn_getv_dmap(str, fnv_local_dmap) > 0 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_GENERAL);
            }
            /*
             * Bitshifting here is unsafe and divide the code into two
             * branches will make it harder for maintainance. It would
             * be easy for the compiler to optimize this multiplication
             * as one of the multiplicator is a static one.
             **/
            *output = (result * -16) - fn_getv_dmap(str, fnv_local_dmap);
        } else {
            if ( result > 134217727 ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);

            *output = (result << 4) | fn_getv_dmap(str, fnv_local_dmap);
        }

        return !*(str + 1)? 0 : FN_ERROR_GENERAL;
    }
    /* END Last Digit Parsing */

    *output = isNeg? -result : result;
    return 0;
}

int hexToInt32TrueError (const char * restrict str, int32_t * const output){
    int32_t result;
    unsigned int isNeg;

    /* START Sign Check */
    switch (*str){
        case 0: fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
        case 45: {
            if ( !*(++str) ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
            isNeg = 1;
            break;
        }
        case 43: {
            if ( !*(++str) ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
            isNeg = 0;
            break;
        }
        default: {
            isNeg = 0;
            break;
        }
    }
    /* END Sign Check */

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ){
        *output = 0;
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* End First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START hexToInt32TrueError UNROLL MACRO  */
#define hexToInt32TrueError_loop_unroll \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ){ \
        *output = isNeg? -result : result; \
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToInt32TrueError_loop_unroll;
    hexToInt32TrueError_loop_unroll;
    hexToInt32TrueError_loop_unroll;
    hexToInt32TrueError_loop_unroll;
    hexToInt32TrueError_loop_unroll;
    hexToInt32TrueError_loop_unroll;

#undef hexToInt32TrueError_loop_unroll
/* END hexToInt32TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

        if ( isNeg ) {
            if ( result > 134217727 ) {
                if ( result > 134217728 ) fn_parser_err_goto_s_n(output, result, hexToInt32TrueError_error_check);
                if ( fn_getv_dmap(str, fnv_local_dmap) > 0 ) fn_parser_err_goto_s_n(output, result, hexToInt32TrueError_error_check);
            }

            *output = (result * -16) - fn_getv_dmap(str, fnv_local_dmap);
        } else {
            if ( result > 134217727 ) fn_parser_err_goto_u(output, result, hexToInt32TrueError_error_check);

            *output = (result << 4) | fn_getv_dmap(str, fnv_local_dmap);
        }

        /* START Error Check Block */
        if ( *(str + 1) ){
            hexToInt32TrueError_error_check:    /* LABEL */
            str++;
            for ( ; fn_getv_dmap(str, fnv_local_dmap) != 200; str++ ) {
                if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) return FN_ERROR_INVALID_FORMAT;
            }
            return isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
        }
        /* END Error Check Block */

        return 0;
    }
    /* END Last Digit Parsing */

    *output = isNeg? -result : result;
    return 0;
}

int hexToUInt32 (const char * restrict str, uint32_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_GENERAL);
    /* END Check Empty String */

    uint32_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) {
        *output = 0;
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_GENERAL;
    }
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START hexToUInt32 UNROLL MACRO  */
#define hexToUInt32_loop_unroll \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ){ \
        *output = result; \
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToUInt32_loop_unroll;
    hexToUInt32_loop_unroll;
    hexToUInt32_loop_unroll;
    hexToUInt32_loop_unroll;
    hexToUInt32_loop_unroll;
    hexToUInt32_loop_unroll;
    hexToUInt32_loop_unroll;

#undef hexToUInt32_loop_unroll
/* END hexToUInt32 UNROLL MACRO */
    /* END Parse Until Max Number Length */

    *output = result;
    return !*str? 0 : FN_ERROR_GENERAL;
}

int hexToUInt32TrueError (const char * restrict str, uint32_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
    /* END Check Empty String */

    uint32_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) {
        *output = 0;
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START hexToUInt32TrueError UNROLL MACRO  */
#define hexToUInt32TrueError_loop_unroll \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ){ \
        *output = result; \
        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToUInt32TrueError_loop_unroll;
    hexToUInt32TrueError_loop_unroll;
    hexToUInt32TrueError_loop_unroll;
    hexToUInt32TrueError_loop_unroll;
    hexToUInt32TrueError_loop_unroll;
    hexToUInt32TrueError_loop_unroll;
    hexToUInt32TrueError_loop_unroll;

#undef hexToUInt32TrueError_loop_unroll
/* END hexToUInt32TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length */

    *output = result;

    /* START Error Check Block */
    if ( *str ){
        for ( ; fn_getv_dmap(str, fnv_local_dmap) != 200; str++ ){
            if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) return FN_ERROR_INVALID_FORMAT;
        }
        return FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    return 0;
}

int hexToInt32FP (const char * restrict str, const size_t from, const size_t to,
                  int32_t * const output, const unsigned int options ){
    /* START Arguments Check */
    if ( from > to ) fn_err_terminate(__func__, "Invalid Arguments", "From > To");
    if ( options & fn_bwnot_u(FN_OPT_PFP_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    int32_t result;
    unsigned int isNeg;

    const char * end = str + to;
    str += from;

    /* START Ignore Leading And Trailing Spaces */
    if ( options & FN_PF_IGNORE_SPACES ){
        if ( options & FN_PF_IGNORE_LSPACES ){
            while ( str <= end ){
                if ( *str != 32 ) break;
                str++;
            }
        }

        if ( options & FN_PF_IGNORE_TSPACES ){
            while ( end >= str ){
                if ( *end != 32 ) break;
                end--;
            }
        }

        if ( str > end ) fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
    }
    /* END Ignore Leading And Trailing Spaces */

    /* START Sign Check */
    switch (*str){
        case 45: {
            if ( str == end ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
            isNeg = 1;
            str++;
            break;
        }
        case 43: {
            if ( str == end ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
            isNeg = 0;
            str++;
            break;
        }
        default: {
            isNeg = 0;
            break;
        }
    }
    /* END Sign Check */

    /* START Skip Leading 0s */
    while( str <= end && *str == 48 ) str++;
    if ( str > end ) {
        *output = 0;
        return 0;
    } else if ( str == end ){
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = isNeg? -fn_getv_dmap(str, fnv_local_dmap) : fn_getv_dmap(str, fnv_local_dmap);
        return 0;
    }
    /* END Skip Leading 0s */

    /* START Error Check Block */
    if ( (uintptr_t)(end - str) > 7 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto hexToInt32FP_error_parse;
        else *output = 0;

        hexToInt32FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end; str++ ){
                if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* hexToInt32FP UNROLL MACRO START */
#define hexToInt32FP_unroll_loop \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++; \
    if ( str > end ) fn_parser_ret_s(output, result, isNeg)

    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;

#undef hexToInt32FP_unroll_loop
/* END hexToInt32FP UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    /* *str == *end */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

    if ( isNeg ) {
        if ( result > 134217727 ) {
            if ( result > 134217728 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_UNDERFLOW);
            if ( fn_getv_dmap(str, fnv_local_dmap) > 0 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_UNDERFLOW);
        }

        *output = (result * -16) - fn_getv_dmap(str, fnv_local_dmap);
    } else {
        if ( result > 134217727 ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);

        *output = (result << 4) | fn_getv_dmap(str, fnv_local_dmap);
    }
    /* END Last Digit Parsing */

    return 0;
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    hexToInt32FP_error_parse:    /* LABEL */

    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START hexToInt32FP UNROLL MACRO 2 */
#define hexToInt32FP_unroll_loop \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;
    hexToInt32FP_unroll_loop;

#undef hexToInt32FP_unroll_loop
/* END hexToInt32FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

    if ( isNeg ) {
        if ( result > 134217727 ) {
            if ( result > 134217728 ){
                str++;
                fn_parser_err_goto_s_n(output, result, hexToInt32FP_error_check);
            }
            if ( fn_getv_dmap(str, fnv_local_dmap) > 0 ){
                str++;
                fn_parser_err_goto_s_n(output, result, hexToInt32FP_error_check);
            }
        }

        *output = (result * -16) - fn_getv_dmap(str, fnv_local_dmap);
    } else {
        if ( result > 134217727 ) {
            str++;
            fn_parser_err_goto_u(output, result, hexToInt32FP_error_check);
        }

        *output = (result << 4) | fn_getv_dmap(str, fnv_local_dmap);
    }

    str++;
    goto hexToInt32FP_error_check;
    /* END Last Digit Parsing */
    /* **************************END INVALID PARSING************************** */
}

int hexToInt32FN (const char * restrict str, int32_t * const output,
                  const unsigned int options){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PFN_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    int32_t result;
    unsigned int isNeg;

    /* START Ignore Leading Spaces */
    if ( options & FN_PF_IGNORE_LSPACES ){
        while ( *str == 32 ) str++;
    }
    /* END Ignore Leading Spaces */

    /* START Sign Check */
    switch (*str){
        case 0: fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
        case 45: {
            if ( !*(++str) ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
            isNeg = 1;
            break;
        }
        case 43: {
            if ( !*(++str) ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
            isNeg = 0;
            break;
        }
        default: {
            isNeg = 0;
            break;
        }
    }
    /* END Sign Check */

    /* START Skip Leading 0s */
    while ( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_fnparser_ret_dmap_eov_0(output, options, fnv_local_dmap, str);
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START hexToInt32FN UNROLL MACRO */
#define hexToInt32FN_loop_unroll \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_fnparser_ret_dmap_eov_s(output, result, isNeg, options, fnv_local_dmap, str); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToInt32FN_loop_unroll;
    hexToInt32FN_loop_unroll;
    hexToInt32FN_loop_unroll;
    hexToInt32FN_loop_unroll;
    hexToInt32FN_loop_unroll;
    hexToInt32FN_loop_unroll;

#undef hexToInt32FN_loop_unroll
/* END hexToInt32FN UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_fnparser_ret_dmap_voe_s(output, result, isNeg, options, fnv_local_dmap, str);

        if ( isNeg ) {
            if ( result > 134217727 ) {
                if ( result > 134217728 ){
                    str++;
                    fn_fnparser_err_of_ret_a_s_n(output, result, 15, options, fnv_local_dmap, str);
                }
                if ( fn_getv_dmap(str, fnv_local_dmap) > 0 ){
                    str++;
                    fn_fnparser_err_of_ret_a_s_n(output, result, 15, options, fnv_local_dmap, str);
                }
            }

            *output = (result * -16) - fn_getv_dmap(str, fnv_local_dmap);
        } else {
            if ( result > 134217727 ){
                str++;
                fn_fnparser_err_of_ret_a_u(output, result, 15, options, fnv_local_dmap, str);
            }

            *output = (result << 4) | fn_getv_dmap(str, fnv_local_dmap);
        }

        /* START Error Check Block */
        if ( *(str + 1) ){
            str++;

            if ( options & FN_PF_LONG_CHECK ){
                int retCode = isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;

                while ( fn_getv_dmap(str, fnv_local_dmap) <= 15 ) str++;

                if ( fn_getv_dmap(str, fnv_local_dmap) != 252 ) {
                    return fn_getv_dmap(str, fnv_local_dmap) == 200? retCode : FN_ERROR_INVALID_FORMAT;
                }

                if ( options & FN_PF_IGNORE_TSPACES ){
                    str++;
                    while ( *str == 32 ) str++;
                    return !*str? retCode : FN_ERROR_INVALID_FORMAT;
                }

                return FN_ERROR_INVALID_FORMAT;
            }

            if ( options & FN_PF_IGNORE_TSPACES ){
                if ( *str == 32 ){
                    str++;
                    while ( *str == 32 ) str++;
                    return !*str? 0 : FN_ERROR_INVALID_FORMAT;
                }
            }

            return isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
        }
        /* END Error Check Block */

        return 0;
    }
    /* END Last Digit Parsing */

    *output = isNeg? -result : result;
    return 0;
}

int hexToUInt32FP (const char * restrict str, const size_t from, const size_t to,
                   uint32_t * const output, const unsigned int options){
    /* START Arguments Check */
    if ( from > to ) fn_err_terminate(__func__, "Invalid Arguments", "From > To");
    if ( options & fn_bwnot_u(FN_OPT_PFP_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    uint32_t result;

    const char * end = str + to;
    str += from;

    /* START Ignore Leading And Trailing Spaces */
    if ( options & FN_PF_IGNORE_SPACES ) {
        if ( options & FN_PF_IGNORE_LSPACES ){
            while ( str <= end ){
                if ( *str != 32 ) break;
                str++;
            }
        }

        if ( options & FN_PF_IGNORE_TSPACES ){
            while ( end >= str ){
                if ( *end != 32 ) break;
                end--;
            }
        }

        if ( str > end ) fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
    }
    /* END Ignore Leading And Trailing Spaces */

    /* START Skip Leading 0s */
    while( str <= end && *str == 48 ) str++;
    if ( str > end ) {
        *output = 0;
        return 0;
    } else if ( str == end ) {
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = fn_getv_dmap(str, fnv_local_dmap);
        return 0;
    }
    /* END Skip Leading 0s */

    /* START Error Check Block */
    if ( (uintptr_t)(end - str) > 7 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto hexToUInt32FP_error_parse;
        else *output = 0;

        hexToUInt32FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end ; str++ ){
                if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START hexToUInt32FP UNROLL MACRO */
#define hexToUInt32FP_unroll_loop \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++; \
    if ( str > end ) fn_parser_ret_u(output, result)

    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;

#undef hexToUInt32FP_unroll_loop
/* END hexToUInt32FP UNROLL MACRO */
    /* END Parse Until Max Number Length */
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    hexToUInt32FP_error_parse:    /* LABEL */
    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START hexToUInt32FP UNROLL MACRO 2 */
#define hexToUInt32FP_unroll_loop \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;
    hexToUInt32FP_unroll_loop;

#undef hexToUInt32FP_unroll_loop
/* END hexToUInt32FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length */

    *output = result;
    goto hexToUInt32FP_error_check;
    /* **************************END INVALID PARSING************************** */
}

int hexToUInt32FN (const char * restrict str, uint32_t * const output,
                   const unsigned int options ){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PFN_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    uint32_t result;

    /* START Ignore Leading Spaces */
    if ( options & FN_PF_IGNORE_LSPACES ){
        while ( *str == 32 ) str++;
    }
    /* END Ignore Leading Spaces */

    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
    /* END Check Empty String */

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) {
        *output = 0;

        if ( options & FN_PF_IGNORE_TSPACES ){
            if ( fn_getv_dmap(str, fnv_local_dmap) == 252 ) {
                str++;
                while ( *str == 32 ) str++;
                return !*str? 0 : FN_ERROR_INVALID_FORMAT;
            }
        }

        return fn_getv_dmap(str, fnv_local_dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_getv_dmap(str, fnv_local_dmap);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START hexToUInt32FN UNROLL MACRO */
#define hexToUInt32FN_loop_unroll \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_fnparser_ret_dmap_eov_u(output, result, options, fnv_local_dmap, str); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToUInt32FN_loop_unroll;
    hexToUInt32FN_loop_unroll;
    hexToUInt32FN_loop_unroll;
    hexToUInt32FN_loop_unroll;
    hexToUInt32FN_loop_unroll;
    hexToUInt32FN_loop_unroll;
    hexToUInt32FN_loop_unroll;

#undef hexToUInt32FN_loop_unroll
/* END hexToUInt32FN UNROLL MACRO */
    /* END Parse Until Max Number Length */

    *output = result;

    /* START Error Check Block */
    if ( *str ) {
        if ( options & FN_PF_LONG_CHECK ){
            while ( fn_getv_dmap(str, fnv_local_dmap) <= 15 ) str++;

            if ( fn_getv_dmap(str, fnv_local_dmap) != 252 ) {
                return fn_getv_dmap(str, fnv_local_dmap) == 200? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT;
            }

            if ( options & FN_PF_IGNORE_TSPACES ){
                str++;
                while ( *str == 32 ) str++;
                return !*str? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT;
            }

            return FN_ERROR_INVALID_FORMAT;
        }

        if ( options & FN_PF_IGNORE_TSPACES ){
            if ( *str == 32 ){
                str++;
                while ( *str == 32 ) str++;
                return !*str? 0 : FN_ERROR_INVALID_FORMAT;
            }
        }

        return FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    return 0;
}

int hexToInt32C1 (const char * restrict str, int32_t * const output, char ** const nextPTR,
                  const unsigned int options){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PC1_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    int32_t result;
    unsigned int isNeg;

    if ( options & FN_PC_NO_INVALID_SKIP ){
    /* *********************START NO INVALID SKIP******************** */
        /* START Sign Check */
        switch ( *str ){
            case 0: fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_EMPTY_STR);
            case 45:{
                if ( fn_getv_dmap(str + 1, fnv_local_dmap) > 15 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
                isNeg = 1;
                str++;
                break;
            }
            case 43:{
                if ( fn_getv_dmap(str + 1, fnv_local_dmap) > 15 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
                isNeg = 0;
                str++;
                break;
            }
            default:{
                isNeg = 0;
                break;
            }
        }
        /* END Sign Check */

        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) {
            *output = 0;
            if ( fn_getv_dmap(str, fnv_local_dmap) == 200 ){
                if ( nextPTR != NULL ) *nextPTR = NULL;
                return 0;
            }

            if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(str);
            return FN_ERROR_INVALID_FORMAT;
        }
        result = fn_getv_dmap(str, fnv_local_dmap);
        str++;
        /* END First Char Parse */
    /* **********************END NO INVALID SKIP********************* */
    } else {
    /* **********************START INVALID SKIP********************** */
        /* START Check Empty String */
        if ( !*str ) fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_EMPTY_STR);
        /* END Check Empty String */

        /* START Skipping Invalid And Sign Evaluation */
        while(1){
            if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) {
               switch ( fn_getv_dmap(str, fnv_local_dmap) ){
                    case 200: fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_NO_VALID_DATA);
                    case 254: {
                        if ( fn_getv_dmap(str + 1, fnv_local_dmap) > 15 ) break;
                        isNeg = 1;
                        str++;
                        goto hexToInt32C1_invalid_skip_done;
                    }
                    case 253:{
                        if ( fn_getv_dmap(str + 1, fnv_local_dmap) > 15 ) break;
                        isNeg = 0;
                        str++;
                        goto hexToInt32C1_invalid_skip_done;
                    }
                    default: break;
                }
                str++;
            } else {
                isNeg = 0;
                hexToInt32C1_invalid_skip_done:    /* LABEL */
                break;
            }
        }
        /* END Skipping Invalid And Sign Evaluation */

        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_cparser_ret_0_dmap(output, result, fnv_local_dmap, nextPTR, str);
        result = fn_getv_dmap(str, fnv_local_dmap);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length - 1 */
/* START hexToInt32C1 UNROLL MACRO */
#define hexToInt32C1_loop_unroll \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_cparser_ret_s_dmap(output, result, isNeg, fnv_local_dmap, nextPTR, str); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToInt32C1_loop_unroll;
    hexToInt32C1_loop_unroll;
    hexToInt32C1_loop_unroll;
    hexToInt32C1_loop_unroll;
    hexToInt32C1_loop_unroll;
    hexToInt32C1_loop_unroll;

#undef hexToInt32C1_loop_unroll
/* END hexToInt32C1 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_cparser_ret_s_dmap(output, result, isNeg, fnv_local_dmap, nextPTR, str);

    if ( isNeg ) {
        if ( result > 134217727 ) {
            if ( result > 134217728 ) fn_cparser_err_of_ret_a_s_n(output, result, 15, fnv_local_dmap, nextPTR, str);
            if ( fn_getv_dmap(str, fnv_local_dmap) > 0 ) fn_cparser_err_of_ret_a_s_n(output, result, 15, fnv_local_dmap, nextPTR, str);
        }

        *output = (result * -16) - fn_getv_dmap(str, fnv_local_dmap);
    } else {
        if ( result > 134217727 ) fn_cparser_err_of_ret_a_u(output, result, 15, fnv_local_dmap, nextPTR, str);

        *output = (result << 4) | fn_getv_dmap(str, fnv_local_dmap);
    }
    /* END Last Digit Parsing */

    /* START Overflow Check */
    if ( *(str + 1) ){
        str++;
        int retCode;

        if ( options & FN_PC_OVERFLOW_ERROR && fn_getv_dmap(str, fnv_local_dmap) <= 15 ){
            retCode = isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
        } else retCode = 0;

        if ( options & FN_PC_OVERFLOW_SKIP ){
            while (1) {
                if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) break;
                str++;
            }

            if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(str, fnv_local_dmap) == 200? NULL : fn_ptr_deConst_cp(str);
            return retCode;
        }

        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(str);
        return retCode;
    }
    /* END Overflow Check */

    if ( nextPTR != NULL ) *nextPTR = NULL;
    return 0;
}

int hexToUInt32C1 (const char * restrict str, uint32_t * const output, char ** const nextPTR,
                   const unsigned int options){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PC1_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    /* START Check Empty String */
    if ( !*str ) fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_EMPTY_STR);
    /* END Check Empty String */

    uint32_t result;

    if ( options & FN_PC_NO_INVALID_SKIP ){
    /* *********************START NO INVALID SKIP******************** */
        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) {
            *output = 0;
            if ( fn_getv_dmap(str, fnv_local_dmap) == 200 ){
                if ( nextPTR != NULL ) *nextPTR = NULL;
                return 0;
            }
            if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(str);
            return FN_ERROR_INVALID_FORMAT;
        }
        result = fn_getv_dmap(str, fnv_local_dmap);
        str++;
        /* END First Char Parse */
    /* **********************END NO INVALID SKIP********************* */
    } else {
    /* **********************START INVALID SKIP********************** */
        /* START Skipping Invalid */
        while(1){
            if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ){
                if ( fn_getv_dmap(str, fnv_local_dmap) == 200 ) fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_NO_VALID_DATA);
                str++;
            } else break;
        }
        /* END Skipping Invalid */

        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_cparser_ret_0_dmap(output, result, fnv_local_dmap, nextPTR, str);
        result = fn_getv_dmap(str, fnv_local_dmap);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length */
/* START hexToUInt32C1 UNROLL MACRO */
#define hexToUInt32C1_loop_unroll \
    if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) fn_cparser_ret_u_dmap(output, result, fnv_local_dmap, nextPTR, str); \
    result = (result << 4) | fn_getv_dmap(str, fnv_local_dmap); \
    str++

    hexToUInt32C1_loop_unroll;
    hexToUInt32C1_loop_unroll;
    hexToUInt32C1_loop_unroll;
    hexToUInt32C1_loop_unroll;
    hexToUInt32C1_loop_unroll;
    hexToUInt32C1_loop_unroll;
    hexToUInt32C1_loop_unroll;

#undef hexToUInt32C1_loop_unroll
/* END hexToUInt32C1 UNROLL MACRO */
   /* END Parse Until Max Number Length */

    *output = result;

    /* START Overflow Check */
    if ( *str ){
        int retCode;

        if ( options & FN_PC_OVERFLOW_ERROR && fn_getv_dmap(str, fnv_local_dmap) <= 15 ){
            retCode = FN_ERROR_OVERFLOW;
        } else retCode = 0;

        if ( options & FN_PC_OVERFLOW_SKIP ){
            while (1) {
                if ( fn_getv_dmap(str, fnv_local_dmap) > 15 ) break;
                str++;
            }

            if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(str, fnv_local_dmap) == 200? NULL : fn_ptr_deConst_cp(str);
            return retCode;
        }

        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(str);
        return retCode;
    }
    /* END Overflow Check */

    if ( nextPTR != NULL ) *nextPTR = NULL;
    return 0;
}

/* START UNI FUNCTIONS MAKER */
#include "../uni/uniComparator.h"
fn_make_func_comparator_parser_as(hexCompareAsInt32, hexToInt32, int32_t)
fn_make_func_comparator_parser_orsmaller(hexInt32OrSmaller, hexToInt32TrueError, int32_t)

fn_make_func_comparator_parser_as(hexCompareAsUInt32, hexToUInt32, uint32_t)
fn_make_func_comparator_parser_orsmaller(hexUInt32OrSmaller, hexToUInt32TrueError, uint32_t)
/* END UNI FUNCTIONS MAKER */
