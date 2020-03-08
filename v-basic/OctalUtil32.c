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
/* faiNumber - OctalUtil32.c */
#include "../h/OctalUtil32.h"

/* START INTERNAL MACRO INCLUSION */
#include "../uni/uniMacro.h"
/* END INTERNAL MACRO INCLUSION */

int octToInt32 (const char * restrict str, int32_t * const output){
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
    if ( fn_bwxor_ucptr_48(str) > 7 ){
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* End First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START octToInt32 UNROLL MACRO */
#define octToInt32_loop_unroll(N)  \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ){ \
        *output = isNeg? -result : result; \
        return fn_bwxor_ucptr_48(str + N) == 48? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToInt32_loop_unroll(0);
        octToInt32_loop_unroll(1);
        octToInt32_loop_unroll(2);
        octToInt32_loop_unroll(3);
    }

    octToInt32_loop_unroll(0);

#undef octToInt32_loop_unroll
/* END octToInt32 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 1) ){
        str++;
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_GENERAL);

        if ( isNeg ) {
            if ( result > 268435455 ){
                if ( result > 268435456 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_GENERAL);
                if ( fn_bwxor_ucptr_48(str) > 0 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_GENERAL);
            }

            *output = (result * -8) - fn_bwxor_ucptr_48(str);
        } else {
            if ( result > 268435455 ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);

            *output = (result << 3) + fn_bwxor_ucptr_48(str);
        }

        return !*(str + 1)? 0 : FN_ERROR_GENERAL;
    }
    /* END Last Digit Parsing */

    *output = isNeg? -result : result;
    return 0;
}

int octToInt32TrueError (const char * restrict str, int32_t * const output){
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
    if ( fn_bwxor_ucptr_48(str) > 7 ){
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* End First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START octToInt32TrueError UNROLL MACRO  */
#define octToInt32TrueError_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ){ \
        *output = isNeg? -result : result; \
        return fn_bwxor_ucptr_48(str + N) == 48? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToInt32TrueError_loop_unroll(0);
        octToInt32TrueError_loop_unroll(1);
        octToInt32TrueError_loop_unroll(2);
        octToInt32TrueError_loop_unroll(3);
    }

    octToInt32TrueError_loop_unroll(0);

#undef octToInt32TrueError_loop_unroll
/* END octToInt32TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 1) ){
        str++;
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

        if ( isNeg ) {
            if ( result > 268435455 ){
                if ( result > 268435456 ) fn_parser_err_goto_s_n(output, result, octToInt32TrueError_error_check);
                if ( fn_bwxor_ucptr_48(str) > 0 ) fn_parser_err_goto_s_n(output, result, octToInt32TrueError_error_check);
            }

            *output = (result * -8) - fn_bwxor_ucptr_48(str);
        } else {
            if ( result > 268435455 ) fn_parser_err_goto_u(output, result, octToInt32TrueError_error_check);

            *output = (result << 3) + fn_bwxor_ucptr_48(str);
        }

        /* START Error Check Block */
        if ( *(str + 1) ){
            octToInt32TrueError_error_check:    /* LABEL */
            str++;
            for ( ; *str; str++ ) {
                if ( *str < '0' || *str > '7' ) return FN_ERROR_INVALID_FORMAT;
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

int octToUInt32 (const char * restrict str, uint32_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_GENERAL);
    /* END Check Empty String */

    uint32_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 7 ) {
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /*
     * The performance that can be achived by unrolling the loop below
     * into individual 9 executions is not unnoticable(test to be around
     * 10ms gain for 10 million strings). But, doing it like the below
     * save on code size and make it easy for converting the code to
     * parse for different data types. But in the future, depend on
     * the architecture that this code target and the performance gain,
     * code that specifically target a system may unroll the below loop
     * and similars into individual execution.
     *
     **/
    /* START Parse Until Max Number Length - 1 */
/* START octToUInt32 UNROLL MACRO  */
#define octToUInt32_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ){ \
        *output = result; \
        return fn_bwxor_ucptr_48(str + N) == 48? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToUInt32_loop_unroll(0);
        octToUInt32_loop_unroll(1);
        octToUInt32_loop_unroll(2);
        octToUInt32_loop_unroll(3);
    }

    octToUInt32_loop_unroll(0);

#undef octToUInt32_loop_unroll
/* END octToUInt32 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 1) ){
        str++;
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);
        if ( result > 536870911U ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);

        *output = (result << 3) + fn_bwxor_ucptr_48(str);
        return !*(str + 1)? 0 : FN_ERROR_GENERAL;
    }
    /* END Last Digit Parsing */

    *output = result;
    return 0;
}

int octToUInt32TrueError (const char * restrict str, uint32_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
    /* END Check Empty String */

    uint32_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 7 ) {
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START octToUInt32TrueError UNROLL MACRO  */
#define octToUInt32TrueError_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ){ \
        *output = result; \
        return fn_bwxor_ucptr_48(str + N) == 48 ? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToUInt32TrueError_loop_unroll(0);
        octToUInt32TrueError_loop_unroll(1);
        octToUInt32TrueError_loop_unroll(2);
        octToUInt32TrueError_loop_unroll(3);
    }

    octToUInt32TrueError_loop_unroll(0);

#undef octToUInt32TrueError_loop_unroll
/* END octToUInt32TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 1) ){
        str++;
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT);
        if ( result > 536870911U ) fn_parser_err_goto_u(output, result, octToUInt32TrueError_error_check);

        *output = (result << 3) + fn_bwxor_ucptr_48(str);

        /* START Error Check Block */
        if ( *(str + 1)  ) {
            octToUInt32TrueError_error_check:    /* LABEL */
            str++;
            for ( ; *str; str++ ){
                if ( *str < '0' || *str > '7' ) return FN_ERROR_INVALID_FORMAT;
            }
            return FN_ERROR_OVERFLOW;
        }
        /* END Error Check Block */

        return 0;
    }
    /* END Last Digit Parsing */

    *output = result;
    return 0;
}

int octToInt32FP (const char * restrict str, const size_t from, const size_t to,
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
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = isNeg? -fn_bwxor_ucptr_48(str) : fn_bwxor_ucptr_48(str);
        return 0;
    }
    /* END Skip Leading 0s */

    const uintptr_t positions = (uintptr_t)end - (uintptr_t)str;

    /* START Error Check Block */
    if ( positions > 10 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto octToInt32FP_error_parse;
        else *output = 0;

        octToInt32FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end; str++ ){
                if ( *str < '0' || *str > '7' ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* octToInt32FP UNROLL MACRO START */
#define octToInt32FP_unroll_loop(N) \
    if ( (str + N) == end ) { \
        str = str + N; \
        goto octToInt32FP_last_digit; \
    } \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( ;; str = str + 4 ){
        octToInt32FP_unroll_loop(0);
        octToInt32FP_unroll_loop(1);
        octToInt32FP_unroll_loop(2);
        octToInt32FP_unroll_loop(3);
    }

#undef octToInt32FP_unroll_loop
/* END octToInt32FP UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    octToInt32FP_last_digit:    /* LABEL */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

    if ( positions < 10 ){
        *output = isNeg? -(result << 3) - fn_bwxor_ucptr_48(str)
                       : (result << 3) + fn_bwxor_ucptr_48(str);
        return 0;
    }

    if ( isNeg ) {
        if ( result > 268435455 ){
            if ( result > 268435456 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_UNDERFLOW);
            if ( fn_bwxor_ucptr_48(str) > 0 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_UNDERFLOW);
        }

        *output = (result * -8) - fn_bwxor_ucptr_48(str);
    } else {
        if ( result > 268435455 ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);

        *output = (result << 3) + fn_bwxor_ucptr_48(str);
    }
    /* END Last Digit Parsing */

    return 0;
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    octToInt32FP_error_parse:    /* LABEL */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START octToInt32FP UNROLL MACRO 2 */
#define octToInt32FP_unroll_loop(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const char * const maxM1 = str + 8; str < maxM1; str = str + 4 ){
        octToInt32FP_unroll_loop(0);
        octToInt32FP_unroll_loop(1);
        octToInt32FP_unroll_loop(2);
        octToInt32FP_unroll_loop(3);
    }

    octToInt32FP_unroll_loop(0);
    str++;

#undef octToInt32FP_unroll_loop
/* END octToInt32FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

    if ( isNeg ) {
        if ( result > 268435455 ){
            if ( result > 268435456 ){
                str++;
                fn_parser_err_goto_s_n(output, result, octToInt32FP_error_check);
            }
            if ( fn_bwxor_ucptr_48(str) > 0 ){
                str++;
                fn_parser_err_goto_s_n(output, result, octToInt32FP_error_check);
            }
        }

        *output = (result * -8) - fn_bwxor_ucptr_48(str);
    } else {
        if ( result > 268435455 ){
            str++;
            fn_parser_err_goto_u(output, result, octToInt32FP_error_check);
        }

        *output = (result << 3) + fn_bwxor_ucptr_48(str);
    }

    str++;
    /* END Last Digit Parsing */

    goto octToInt32FP_error_check;
    /* **************************END INVALID PARSING************************** */
}

int octToInt32FN (const char * restrict str, int32_t * const output,
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
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_fnparser_ret_xor_eov_0(output, options, str);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START octToInt32FN UNROLL MACRO */
#define octToInt32FN_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) { \
        str = str + N; \
        fn_fnparser_ret_xor_eov_s(output, result, isNeg, options, str); \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToInt32FN_loop_unroll(0);
        octToInt32FN_loop_unroll(1);
        octToInt32FN_loop_unroll(2);
        octToInt32FN_loop_unroll(3);
    }

    octToInt32FN_loop_unroll(0);

#undef octToInt32FN_loop_unroll
/* END octToInt32FN UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 1) ){
        str++;
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_fnparser_ret_xor_voe_s(output, result, isNeg, options, str);

        if ( isNeg ) {
            if ( result > 268435455 ){
                if ( result > 268435456 ){
                    str++;
                    fn_fnparser_err_of_ret_d_s_n(output, result, 7, options, str);
                }
                if ( fn_bwxor_ucptr_48(str) > 0 ){
                    str++;
                    fn_fnparser_err_of_ret_d_s_n(output, result, 7, options, str);
                }
            }

            *output = (result * -8) - fn_bwxor_ucptr_48(str);
        } else {
            if ( result > 268435455 ){
                str++;
                fn_fnparser_err_of_ret_d_u(output, result, 7, options, str);
            }

            *output = (result << 3) + fn_bwxor_ucptr_48(str);
        }

        /* START Error Check Block */
        if ( *(str + 1) ){
            str++;

            if ( options & FN_PF_LONG_CHECK ){
                int retCode = isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;

                while ( fn_bwxor_ucptr_48(str) <= 7 ) str++;

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

int octToUInt32FP (const char * restrict str, const size_t from, const size_t to,
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
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = fn_bwxor_ucptr_48(str);
        return 0;
    }
    /* END Skip Leading 0s */

    const uintptr_t positions = (uintptr_t)end - (uintptr_t)str;

    /* START Error Check Block */
    if ( positions > 10 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto octToUInt32FP_error_parse;
        else *output = 0;

        octToUInt32FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end ; str++ ){
                if ( *str < '0' || *str > '7' ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START octToUInt32FP UNROLL MACRO */
#define octToUInt32FP_unroll_loop(N) \
    if ( (str + N) == end ) { \
        str = str + N; \
        goto octToUInt32FP_last_digit; \
    } \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( ;; str = str + 4 ){
        octToUInt32FP_unroll_loop(0);
        octToUInt32FP_unroll_loop(1);
        octToUInt32FP_unroll_loop(2);
        octToUInt32FP_unroll_loop(3);
    }

#undef octToUInt32FP_unroll_loop
/* END octToUInt32FP UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    octToUInt32FP_last_digit:    /* LABEL */

    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT);

    if ( positions < 10 ) {
        *output = (result << 3) + fn_bwxor_ucptr_48(str);
        return 0;
    }

    if ( result > 536870911U ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);

    *output = (result << 3) + fn_bwxor_ucptr_48(str);
    /* END Last Digit Parsing */

    return 0;
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    octToUInt32FP_error_parse:    /* LABEL */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START octToUInt32FP UNROLL MACRO 2 */
#define octToUInt32FP_unroll_loop(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const char * const maxM1 = str + 8; str < maxM1; str = str + 4 ){
        octToUInt32FP_unroll_loop(0);
        octToUInt32FP_unroll_loop(1);
        octToUInt32FP_unroll_loop(2);
        octToUInt32FP_unroll_loop(3);
    }

    octToUInt32FP_unroll_loop(0);
    str++;

#undef octToUInt32FP_unroll_loop
/* END octToUInt32FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT);

    if ( result > 536870911U ){
        str++;
        fn_parser_err_goto_u(output, result, octToUInt32FP_error_check);
    }

    *output = (result << 3) + fn_bwxor_ucptr_48(str);
    str++;
    /* END Last Digit Parsing */

    goto octToUInt32FP_error_check;
    /* **************************END INVALID PARSING************************** */
}

int octToUInt32FN (const char * restrict str, uint32_t * const output,
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
    if ( fn_bwxor_ucptr_48(str) > 7 ) {
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

    /* START Parse Until Max Number Length - 1 */
/* START octToUInt32FN UNROLL MACRO */
#define octToUInt32FN_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) { \
        str = str + N; \
        fn_fnparser_ret_xor_eov_u(output, result, options, str); \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToUInt32FN_loop_unroll(0);
        octToUInt32FN_loop_unroll(1);
        octToUInt32FN_loop_unroll(2);
        octToUInt32FN_loop_unroll(3);
    }

    octToUInt32FN_loop_unroll(0);

#undef octToUInt32FN_loop_unroll
/* END octToUInt32FN UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *(str + 1) ){
        str++;
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_fnparser_ret_xor_voe_u(output, result, options, str);
        if ( result > 536870911U ){
            str++;
            fn_fnparser_err_of_ret_d_u(output, result, 7, options, str);
        }

        *output = (result << 3) + fn_bwxor_ucptr_48(str);

        /* START Error Check Block */
        if ( *(str + 1) ) {
            str++;

            if ( options & FN_PF_LONG_CHECK ){
                while ( fn_bwxor_ucptr_48(str) <= 7 ) str++;

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
    /* END Last Digit Parsing */

    *output = result;
    return 0;
}

int octToInt32C1 (const char * restrict str, int32_t * const output, char ** const nextPTR,
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
                if ( fn_bwxor_ucptr_48(str + 1) > 7 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
                isNeg = 1;
                str++;
                break;
            }
            case 43:{
                if ( fn_bwxor_ucptr_48(str + 1) > 7 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
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
        if ( fn_bwxor_ucptr_48(str) > 7 ) {
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
            if ( *str > '7' ) str++;
            else if ( *str < '0' ){
                switch ( *str ){
                    case 0: fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_NO_VALID_DATA);
                    case 45: {
                        if ( fn_bwxor_ucptr_48(str + 1) > 7 ) break;
                        isNeg = 1;
                        str++;
                        goto octToInt32C1_invalid_skip_done;
                    }
                    case 43:{
                        if ( fn_bwxor_ucptr_48(str + 1) > 7 ) break;
                        isNeg = 0;
                        str++;
                        goto octToInt32C1_invalid_skip_done;
                    }
                    default: break;
                }
                str++;
            } else {
                isNeg = 0;
                octToInt32C1_invalid_skip_done:    /* LABEL */
                break;
            }
        }
        /* END Skipping Invalid And Sign Evaluation */

        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_cparser_ret_0_xor(output, result, nextPTR, str);
        result = fn_bwxor_ucptr_48(str);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length - 1 */
/* START octToInt32C1 UNROLL MACRO */
#define octToInt32C1_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) { \
        str = str + N; \
        fn_cparser_ret_s_xor(output, result, isNeg, nextPTR, str); \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToInt32C1_loop_unroll(0);
        octToInt32C1_loop_unroll(1);
        octToInt32C1_loop_unroll(2);
        octToInt32C1_loop_unroll(3);
    }

    octToInt32C1_loop_unroll(0);
    str++;

#undef octToInt32C1_loop_unroll
/* END octToInt32C1 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_cparser_ret_s_xor(output, result, isNeg, nextPTR, str);

    if ( isNeg ) {
        if ( result > 268435455 ){
            if ( result > 268435456 ) fn_cparser_err_of_ret_d_s_n(output, result, 7, nextPTR, str);
            if ( fn_bwxor_ucptr_48(str) > 0 ) fn_cparser_err_of_ret_d_s_n(output, result, 7, nextPTR, str);
        }

        *output = (result * -8) - fn_bwxor_ucptr_48(str);
    } else {
        if ( result > 268435455 ) fn_cparser_err_of_ret_d_u(output, result, 7, nextPTR, str);

        *output = (result << 3) + fn_bwxor_ucptr_48(str);
    }
    /* END Last Digit Parsing */

    /* START Overflow Check */
    if ( *(str + 1) ){
        str++;
        int retCode;

        if ( options & FN_PC_OVERFLOW_ERROR && fn_bwxor_ucptr_48(str) <= 7 ){
            retCode = isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
        } else retCode = 0;

        if ( options & FN_PC_OVERFLOW_SKIP ){
            while (1) {
                if ( fn_bwxor_ucptr_48(str) > 7 ) break;
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

int octToUInt32C1 (const char * restrict str, uint32_t * const output, char ** const nextPTR,
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
        if ( fn_bwxor_ucptr_48(str) > 7 ) {
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
            if ( *str > '7' ) str++;
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
        if ( fn_bwxor_ucptr_48(str) > 7 ) fn_cparser_ret_0_xor(output, result, nextPTR, str);
        result = fn_bwxor_ucptr_48(str);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length - 1 */
/* START octToUInt32C1 UNROLL MACRO */
#define octToUInt32C1_loop_unroll(N) \
    if ( fn_bwxor_ucptr_48(str + N) > 7 ) { \
        str = str + N; \
        fn_cparser_ret_u_xor(output, result, nextPTR, str); \
    } \
    result = (result << 3) + fn_bwxor_ucptr_48(str + N)

    for ( const uintptr_t maxM1 = fn_ptr_safe_add_ceil_uptrt(str, 8)
          ; (uintptr_t)str < maxM1; str = str + 4 ){
        octToUInt32C1_loop_unroll(0);
        octToUInt32C1_loop_unroll(1);
        octToUInt32C1_loop_unroll(2);
        octToUInt32C1_loop_unroll(3);
    }

    octToUInt32C1_loop_unroll(0);
    str++;

#undef octToUInt32C1_loop_unroll
/* END octToUInt32C1 UNROLL MACRO */
   /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 7 ) fn_cparser_ret_u_xor(output, result, nextPTR, str);
    if ( result > 536870911U ) fn_cparser_err_of_ret_d_u(output, result, 7, nextPTR, str);

    *output = (result << 3) + fn_bwxor_ucptr_48(str);
    /* END Last Digit Parsing */

    /* START Overflow Check */
    if ( *(str + 1) ){
        str++;
        int retCode;

        if ( options & FN_PC_OVERFLOW_ERROR && fn_bwxor_ucptr_48(str) <= 7 ){
            retCode = FN_ERROR_OVERFLOW;
        } else retCode = 0;

        if ( options & FN_PC_OVERFLOW_SKIP ){
            while (1) {
                if ( fn_bwxor_ucptr_48(str) > 7 ) break;
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
fn_make_func_comparator_parser_as(octCompareAsInt32, octToInt32, int32_t)
fn_make_func_comparator_parser_orsmaller(octInt32OrSmaller, octToInt32TrueError, int32_t)

fn_make_func_comparator_parser_as(octCompareAsUInt32, octToUInt32, uint32_t)
fn_make_func_comparator_parser_orsmaller(octUInt32OrSmaller, octToUInt32TrueError, uint32_t)
/* END UNI FUNCTIONS MAKER */
