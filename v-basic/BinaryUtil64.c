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
/* faiNumber - BinaryUtil64.c */
#include "../h/BinaryUtil64.h"

/* START INTERNAL MACRO INCLUSION */
#include "../uni/uniMacro.h"
/* END INTERNAL MACRO INCLUSION */

int binToInt64 (const char * restrict str, int64_t * const output){
    int64_t result;
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
    if ( fn_bwxor_ucptr_48(str) > 1 ){
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* End First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START binToInt64 UNROLL MACRO */
#define binToInt64_loop_unroll(N)  \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ){ \
        *output = isNeg? -result : result; \
        return fn_bwxor_ucptr_48(str + N) == 48? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToInt64_loop_unroll(0);
        binToInt64_loop_unroll(1);
        binToInt64_loop_unroll(2);
        binToInt64_loop_unroll(3);
    }

    binToInt64_loop_unroll(0);
    binToInt64_loop_unroll(1);

#undef binToInt64_loop_unroll
/* END binToInt64 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 2) ){
        str = str + 2;
        if ( fn_bwxor_ucptr_48(str) > 0 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_GENERAL);
        if ( !isNeg ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);
        if ( result > 4611686018427387904 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_GENERAL);

        *output = -4611686018427387904 - 4611686018427387904;

        return !*(str + 1)? 0 : FN_ERROR_GENERAL;
    }
    /* END Last Digit Parsing */

    *output = isNeg? -result : result;
    return 0;
}

int binToInt64TrueError (const char * restrict str, int64_t * const output){
    int64_t result;
    unsigned int isNeg;

    /* START Sign Check */
    switch (*str){
        /* Empty String */
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
    if ( fn_bwxor_ucptr_48(str) > 1 ){
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* End First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START binToInt64TrueError UNROLL MACRO  */
#define binToInt64TrueError_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ){ \
        *output = isNeg? -result : result; \
        return fn_bwxor_ucptr_48(str + N) == 48? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToInt64TrueError_loop_unroll(0);
        binToInt64TrueError_loop_unroll(1);
        binToInt64TrueError_loop_unroll(2);
        binToInt64TrueError_loop_unroll(3);
    }

    binToInt64TrueError_loop_unroll(0);
    binToInt64TrueError_loop_unroll(1);

#undef binToInt64TrueError_loop_unroll
/* END binToInt64TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 2) ){
        str = str + 2;
        if ( fn_bwxor_ucptr_48(str) > 0 ) {
            if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);
            fn_parser_err_goto_s(output, result, isNeg, binToInt64TrueError_error_check);
        }
        if ( !isNeg ) fn_parser_err_goto_u(output, result, binToInt64TrueError_error_check);
        if ( result > 4611686018427387904 ) fn_parser_err_goto_s(output, result, isNeg, binToInt64TrueError_error_check);

        *output = -4611686018427387904 - 4611686018427387904;

        /* START Error Check Block */
        if ( *(str + 1) ){
            binToInt64TrueError_error_check:    /* LABEL */
            str++;
            for ( ; *str; str++ ) {
                if ( *str < '0' || *str > '1' ) return FN_ERROR_INVALID_FORMAT;
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

int binToUInt64 (const char * restrict str, uint64_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_GENERAL);
    /* END Check Empty String */

    uint64_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 1 ) {
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START binToUInt64 UNROLL MACRO  */
#define binToUInt64_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ){ \
        *output = result; \
        return fn_bwxor_ucptr_48(str + N) == 48? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToUInt64_loop_unroll(0);
        binToUInt64_loop_unroll(1);
        binToUInt64_loop_unroll(2);
        binToUInt64_loop_unroll(3);
    }

    binToUInt64_loop_unroll(0);
    binToUInt64_loop_unroll(1);
    binToUInt64_loop_unroll(2);

#undef binToUInt64_loop_unroll
/* END binToUInt64 UNROLL MACRO */
    /* END Parse Until Max Number Length */

    *output = result;
    return !*(str + 3)? 0 : FN_ERROR_GENERAL;
}

int binToUInt64TrueError (const char * restrict str, uint64_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
    /* END Check Empty String */

    uint64_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 1 ) {
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START binToUInt64TrueError UNROLL MACRO  */
#define binToUInt64TrueError_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ){ \
        *output = result; \
        return fn_bwxor_ucptr_48(str + N) == 48? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToUInt64TrueError_loop_unroll(0);
        binToUInt64TrueError_loop_unroll(1);
        binToUInt64TrueError_loop_unroll(2);
        binToUInt64TrueError_loop_unroll(3);
    }

    binToUInt64TrueError_loop_unroll(0);
    binToUInt64TrueError_loop_unroll(1);
    binToUInt64TrueError_loop_unroll(2);

#undef binToUInt64TrueError_loop_unroll
/* END binToUInt64TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length */

    *output = result;

    /* START Error Check Block */
    if ( *(str + 3) ) {
        str = str + 3;
        for ( ; *str; str++ ){
            if ( *str < '0' || *str > '1' ) return FN_ERROR_INVALID_FORMAT;
        }
        return FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    return 0;
}

int binToInt64FP (const char * restrict str, const size_t from, const size_t to,
                  int64_t * const output, const unsigned int options ){
    /* START Arguments Check */
    if ( from > to ) fn_err_terminate(__func__, "Invalid Arguments", "From > To");
    if ( options & fn_bwnot_u(FN_OPT_PFP_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    int64_t result;
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
        if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = isNeg? -fn_bwxor_ucptr_48(str) : fn_bwxor_ucptr_48(str);
        return 0;
    }
    /* END Skip Leading 0s */

    const uintptr_t positions = (uintptr_t)end - (uintptr_t)str;

    /* START Error Check Block */
    if ( positions > 63 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto binToInt64FP_error_parse;
        else *output = 0;

        binToInt64FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end; str++ ){
                if ( *str < '0' || *str > '1' ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* binToInt64FP UNROLL MACRO START */
#define binToInt64FP_unroll_loop(N) \
    if ( (str + N) == end ) { \
        str = str + N; \
        goto binToInt64FP_last_digit; \
    } \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( ;; str = str + 4 ){
        binToInt64FP_unroll_loop(0);
        binToInt64FP_unroll_loop(1);
        binToInt64FP_unroll_loop(2);
        binToInt64FP_unroll_loop(3);
    }

#undef binToInt64FP_unroll_loop
/* END binToInt64FP UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    binToInt64FP_last_digit:    /* LABEL */
    /* *str == *end */
    if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

    if ( positions < 63 ) {
        *output = isNeg? -(result << 1) - fn_bwxor_ucptr_48(str)
                       : (result << 1) + fn_bwxor_ucptr_48(str);
        return 0;
    }

    if ( !isNeg ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);
    if ( fn_bwxor_ucptr_48(str) > 0 || result > 4611686018427387904 ) {
        *output = -result;
        return FN_ERROR_UNDERFLOW;
    }

    *output = -4611686018427387904 - 4611686018427387904;
    /* END Last Digit Parsing */

    return 0;
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    binToInt64FP_error_parse:    /* LABEL */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START binToInt64FP UNROLL MACRO 2 */
#define binToInt64FP_unroll_loop(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToInt64FP_unroll_loop(0);
        binToInt64FP_unroll_loop(1);
        binToInt64FP_unroll_loop(2);
        binToInt64FP_unroll_loop(3);
    }

    binToInt64FP_unroll_loop(0);
    binToInt64FP_unroll_loop(1);
    str = str + 2;

#undef binToInt64FP_unroll_loop
/* END binToInt64FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 0 ) {
        if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);
        str++;
        fn_parser_err_goto_s(output, result, isNeg, binToInt64FP_error_check);
    }
    if ( !isNeg ){
        str++;
        fn_parser_err_goto_u(output, result, binToInt64FP_error_check);
    }
    if ( result > 4611686018427387904 ){
        str++;
        fn_parser_err_goto_s(output, result, isNeg, binToInt64FP_error_check);
    }

    *output = -4611686018427387904 - 4611686018427387904;
    str++;
    /* END Last Digit Parsing */

    goto binToInt64FP_error_check;
    /* **************************END INVALID PARSING************************** */
}

int binToInt64FN (const char * restrict str, int64_t * const output,
                  const unsigned int options){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PFN_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    int64_t result;
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
    if ( fn_bwxor_ucptr_48(str) > 1 ) fn_fnparser_ret_xor_eov_0(output, options, str);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START binToInt64FN UNROLL MACRO */
#define binToInt64FN_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) { \
        str = str + N; \
        fn_fnparser_ret_xor_eov_s(output, result, isNeg, options, str); \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToInt64FN_loop_unroll(0);
        binToInt64FN_loop_unroll(1);
        binToInt64FN_loop_unroll(2);
        binToInt64FN_loop_unroll(3);
    }

    binToInt64FN_loop_unroll(0);
    binToInt64FN_loop_unroll(1);

#undef binToInt64FN_loop_unroll
/* END binToInt64FN UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 2) ){
        str = str + 2;
        if ( fn_bwxor_ucptr_48(str) > 0 ) {
            if ( fn_bwxor_ucptr_48(str) > 1 ) fn_fnparser_ret_xor_voe_s(output, result, isNeg, options, str);
            str++;
            fn_fnparser_err_of_ret_d_s(output, result, isNeg, 1, options, str);
        }
        if ( !isNeg ){
            str++;
            fn_fnparser_err_of_ret_d_u(output, result, 1, options, str);
        }
        if ( result > 4611686018427387904 ){
            str++;
            fn_fnparser_err_of_ret_d_s(output, result, isNeg, 1, options, str);
        }

        *output = -4611686018427387904 - 4611686018427387904;

        /* START Error Check Block */
        if ( *(str + 1) ){
            str++;

            if ( options & FN_PF_LONG_CHECK ){
                int retCode = isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;

                while ( fn_bwxor_ucptr_48(str) <= 1 ) str++;

                if ( fn_bwxor_ucptr_48(str) != 16 ) {
                    return fn_bwxor_ucptr_48(str) == 48? retCode : FN_ERROR_INVALID_FORMAT;
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

int binToUInt64FP (const char * restrict str, const size_t from, const size_t to,
                   uint64_t * const output, const unsigned int options){
    /* START Arguments Check */
    if ( from > to ) fn_err_terminate(__func__, "Invalid Arguments", "From > To");
    if ( options & fn_bwnot_u(FN_OPT_PFP_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    uint64_t result;

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
        if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = fn_bwxor_ucptr_48(str);
        return 0;
    }
    /* END Skip Leading 0s */

    /* START Error Check Block */
    if ( (uintptr_t)(end - str) > 63 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto binToUInt64FP_error_parse;
        else *output = 0;

        binToUInt64FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end ; str++ ){
                if ( *str < '0' || *str > '1' ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START binToUInt64FP UNROLL MACRO */
#define binToUInt64FP_unroll_loop(N) \
    if ( (str + N) > end ) fn_parser_ret_u(output, result); \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( ;; str = str + 4 ){
        binToUInt64FP_unroll_loop(0);
        binToUInt64FP_unroll_loop(1);
        binToUInt64FP_unroll_loop(2);
        binToUInt64FP_unroll_loop(3);
    }

#undef binToUInt64FP_unroll_loop
/* END binToUInt64FP UNROLL MACRO */
    /* END Parse Until Max Number Length */
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    binToUInt64FP_error_parse:    /* LABEL */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 1 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START binToUInt64FP UNROLL MACRO 2 */
#define binToUInt64FP_unroll_loop(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToUInt64FP_unroll_loop(0);
        binToUInt64FP_unroll_loop(1);
        binToUInt64FP_unroll_loop(2);
        binToUInt64FP_unroll_loop(3);
    }

    binToUInt64FP_unroll_loop(0);
    binToUInt64FP_unroll_loop(1);
    binToUInt64FP_unroll_loop(2);

#undef binToUInt64FP_unroll_loop
/* END binToUInt64FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length */

    *output = result;
    str = str + 3;
    /* END Last Digit Parsing */

    goto binToUInt64FP_error_check;
    /* **************************END INVALID PARSING************************** */
}

int binToUInt64FN (const char * restrict str, uint64_t * const output,
                   const unsigned int options ){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PFN_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    uint64_t result;

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
    if ( fn_bwxor_ucptr_48(str) > 1 ) {
        *output = 0;
        if ( options & FN_PF_IGNORE_TSPACES ){
            if ( fn_bwxor_ucptr_48(str) == 16 ) {
                str++;
                while ( *str == 32 ) str++;
                return !*str? 0 : FN_ERROR_INVALID_FORMAT;
            }
        }

        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length */
/* START binToUInt64FN UNROLL MACRO */
#define binToUInt64FN_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) { \
        str = str + N; \
        fn_fnparser_ret_xor_eov_u(output, result, options, str); \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToUInt64FN_loop_unroll(0);
        binToUInt64FN_loop_unroll(1);
        binToUInt64FN_loop_unroll(2);
        binToUInt64FN_loop_unroll(3);
    }

    binToUInt64FN_loop_unroll(0);
    binToUInt64FN_loop_unroll(1);
    binToUInt64FN_loop_unroll(2);

#undef binToUInt64FN_loop_unroll
/* END binToUInt64FN UNROLL MACRO */
    /* END Parse Until Max Number Length */

    *output = result;

    /* START Error Check Block */
    if ( *(str + 3) ) {
        str = str + 3;

        if ( options & FN_PF_LONG_CHECK ){
            while ( fn_bwxor_ucptr_48(str) <= 1 ) str++;

            if ( fn_bwxor_ucptr_48(str) != 16 ) {
                return fn_bwxor_ucptr_48(str) == 48? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT;
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

int binToInt64C1 (const char * restrict str, int64_t * const output, char ** const nextPTR,
                  const unsigned int options){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PC1_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    int64_t result;
    unsigned int isNeg;

    if ( options & FN_PC_NO_INVALID_SKIP ){
    /* *********************START NO INVALID SKIP******************** */
        /* START Sign Check */
        switch ( *str ){
            case 0: fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_EMPTY_STR);
            case 45:{
                if ( fn_bwxor_ucptr_48(str + 1) > 1 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
                isNeg = 1;
                str++;
                break;
            }
            case 43:{
                if ( fn_bwxor_ucptr_48(str + 1) > 1 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
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
        if ( fn_bwxor_ucptr_48(str) > 1 ) {
            *output = 0;
            if ( fn_bwxor_ucptr_48(str) == 48 ){
                if ( nextPTR != NULL ) *nextPTR = NULL;
                return 0;
            }

            if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(str);
            return FN_ERROR_INVALID_FORMAT;
        }
        result = fn_bwxor_ucptr_48(str);
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
            if ( *str > '1' ) str++;
            else if ( *str < '0' ){
                switch ( *str ){
                    case 0: fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_NO_VALID_DATA);
                    case 45: {
                        if ( fn_bwxor_ucptr_48(str + 1) > 1 ) break;
                        isNeg = 1;
                        str++;
                        goto binToInt64C1_invalid_skip_done;
                    }
                    case 43:{
                        if ( fn_bwxor_ucptr_48(str + 1) > 1 ) break;
                        isNeg = 0;
                        str++;
                        goto binToInt64C1_invalid_skip_done;
                    }
                    default: break;
                }
                str++;
            } else {
                isNeg = 0;
                binToInt64C1_invalid_skip_done:    /* LABEL */
                break;
            }
        }
        /* END Skipping Invalid And Sign Evaluation */

        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_bwxor_ucptr_48(str) > 1 ) fn_cparser_ret_0_xor(output, result, nextPTR, str);
        result = fn_bwxor_ucptr_48(str);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length - 1 */
/* START binToInt64C1 UNROLL MACRO */
#define binToInt64C1_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) { \
        str = str + N; \
        fn_cparser_ret_s_xor(output, result, isNeg, nextPTR, str); \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToInt64C1_loop_unroll(0);
        binToInt64C1_loop_unroll(1);
        binToInt64C1_loop_unroll(2);
        binToInt64C1_loop_unroll(3);
    }

    binToInt64C1_loop_unroll(0);
    binToInt64C1_loop_unroll(1);

#undef binToInt64C1_loop_unroll
/* END binToInt64C1 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 2) ){
        str = str + 2;
        if ( fn_bwxor_ucptr_48(str) > 0 ) {
            if ( fn_bwxor_ucptr_48(str) > 1 ) fn_cparser_ret_s_xor(output, result, isNeg, nextPTR, str);
            fn_cparser_err_of_ret_d_s(output, result, isNeg, 1, nextPTR, str);
        }
        if ( !isNeg ) fn_cparser_err_of_ret_d_u(output, result, 1, nextPTR, str);
        if ( result > 4611686018427387904 ) fn_cparser_err_of_ret_d_s_n(output, result, 1, nextPTR, str);

        *output = -4611686018427387904 - 4611686018427387904;

        /* START Overflow Check */
        if ( *(str + 1) ){
            str++;
            int retCode;

            if ( options & FN_PC_OVERFLOW_ERROR && fn_bwxor_ucptr_48(str) <= 1 ){
                retCode = FN_ERROR_UNDERFLOW;
            } else retCode = 0;

            if ( options & FN_PC_OVERFLOW_SKIP ){
                while (1) {
                    if ( fn_bwxor_ucptr_48(str) > 1 ) break;
                    str++;
                }

                if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(str) == 48? NULL : fn_ptr_deConst_cp(str);
                return retCode;
            }

            if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(str);
            return retCode;
        }
        /* END Overflow Check */
    /* END Last Digit Parsing */
    } else {
        *output = isNeg? -result : result;
    }

    if ( nextPTR != NULL ) *nextPTR = NULL;
    return 0;
}

int binToUInt64C1 (const char * restrict str, uint64_t * const output, char ** const nextPTR,
                  const unsigned int options){
    /* START Arguments Check */
    if ( options & fn_bwnot_u(FN_OPT_PC1_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    /* START Check Empty String */
    if ( !*str ) fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_EMPTY_STR);
    /* END Check Empty String */

    uint64_t result;

    if ( options & FN_PC_NO_INVALID_SKIP ){
    /* *********************START NO INVALID SKIP******************** */
        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_bwxor_ucptr_48(str) > 1 ) {
            *output = 0;
            if ( fn_bwxor_ucptr_48(str) == 48 ){
                if ( nextPTR != NULL ) *nextPTR = NULL;
                return 0;
            }
            if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(str);
            return FN_ERROR_INVALID_FORMAT;
        }
        result = fn_bwxor_ucptr_48(str);
        str++;
        /* END First Char Parse */
    /* **********************END NO INVALID SKIP********************* */
    } else {
    /* **********************START INVALID SKIP********************** */
        /* START Skipping Invalid */
        while(1){
            if ( *str > '1' ) str++;
            else if ( *str < '0' ){
                if ( !*str ) fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_NO_VALID_DATA);
                str++;
            } else break;
        }
        /* END Skipping Invalid */

        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_bwxor_ucptr_48(str) > 1 ) fn_cparser_ret_0_xor(output, result, nextPTR, str);
        result = fn_bwxor_ucptr_48(str);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length */
/* START binToUInt64C1 UNROLL MACRO */
#define binToUInt64C1_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 1 ) { \
        str = str + N; \
        fn_cparser_ret_u_xor(output, result, nextPTR, str); \
    } \
    result = (result << 1) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 60)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        binToUInt64C1_loop_unroll(0);
        binToUInt64C1_loop_unroll(1);
        binToUInt64C1_loop_unroll(2);
        binToUInt64C1_loop_unroll(3);
    }

    binToUInt64C1_loop_unroll(0);
    binToUInt64C1_loop_unroll(1);
    binToUInt64C1_loop_unroll(2);

#undef binToUInt64C1_loop_unroll
/* END binToUInt64C1 UNROLL MACRO */
   /* END Parse Until Max Number Length */

    *output = result;

    /* START Overflow Check */
    if ( *(str + 3) ){
        str = str + 3;
        int retCode;

        if ( options & FN_PC_OVERFLOW_ERROR && fn_bwxor_ucptr_48(str) <= 1 ){
            retCode = FN_ERROR_OVERFLOW;
        } else retCode = 0;

        if ( options & FN_PC_OVERFLOW_SKIP ){
            while (1) {
                if ( fn_bwxor_ucptr_48(str) > 1 ) break;
                str++;
            }

            if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(str) == 48? NULL : fn_ptr_deConst_cp(str);
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
fn_make_func_comparator_parser_as(binCompareAsInt64, binToInt64, int64_t)
fn_make_func_comparator_parser_orsmaller(binInt64OrSmaller, binToInt64TrueError, int64_t)

fn_make_func_comparator_parser_as(binCompareAsUInt64, binToUInt64, uint64_t)
fn_make_func_comparator_parser_orsmaller(binUInt64OrSmaller, binToUInt64TrueError, uint64_t)
/* END UNI FUNCTIONS MAKER */
