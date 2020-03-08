#ifndef ___faiNumber_uniMacro_H___
#define ___faiNumber_uniMacro_H___
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

/*
 * These file is included here so that if build as a Dynamic Library.
 * code that link to this library does not need to include these header
 * to use this library.
 *
 **/
#include <stdlib.h>         /* <- abort() */
#include <stdio.h>          /* <- puts() */

/* ************************ START XOR Macro ************************* */
/* Both values will be promoted to int and will give a value of int */
#define fn_bwxor_ucptr_48(strPTR) (*(unsigned char *)(strPTR) ^ (unsigned char)48)
/* ************************* END XOR Macro ************************** */

/* ************************ START MISC Macro ************************* */
#define fn_ptr_deConst(ptr, type)          ( (type) ((uintptr_t)(ptr)) )
#define fn_ptr_deConst_cp(ptr)           ( (char *) ((uintptr_t)(ptr)) )
#define fn_ptr_deConst_cpp(ptr)         ( (char **) ((uintptr_t)(ptr)) )

#define fn_ptr_safe_add_ceil_uptrt(ptr, v) \
((uintptr_t)(ptr) < UINTPTR_MAX - (v)? (uintptr_t)((ptr) + (v)) : UINTPTR_MAX)

#define fn_bwnot_u(v)                                   ((unsigned)~(v))
#define fn_bwnot_s(v)                                     ((signed)~(v))

#define fn_getv_dmap(strPTR, dmap)    dmap[(*(unsigned char *)(strPTR))]
/* ************************* END MISC Macro ************************** */

/*
 * @NOTE  Unless stated otherwise, macro below here were not built with
 *        pointer arithmatic in mind. Check before usage.
 *
 **/
/* ****************** START Parsers Return Macros ******************* */
/* @NOTE: Parsers Error Return Macros were designed to aid readability
 *        in code.
 *
 *        Except for "code" or "codeN", everything else that pass to
 *        these macros should only be actual variables.
 *
 *        These are not value substitution macros but are reusable blocks
 *        of code.
 *
 *        These macro may or may not be used in the code.
 */
#define fn_parser_ret_s(output, result, isNeg) do { \
    *output = isNeg? -result : result; \
    return 0; \
} while(0)

#define fn_parser_ret_u(output, result) do { \
    *output = result; \
    return 0; \
} while(0)

#define fn_parser_err_ret_0(output, code) do { \
    *output = 0; \
    return code; \
} while(0)

#define fn_parser_err_ret_s(output, result, isNeg, code) do { \
    *output = isNeg? -result : result; \
    return code; \
} while(0)

#define fn_parser_err_ret_s_n(output, result, code) do { \
    *output = -result; \
    return code; \
} while(0)

#define fn_parser_err_ret_u(output, result, code) do {\
    *output = result; \
    return code; \
} while(0)

#define fn_parser_err_goto_0(output, label) do { \
    *output = 0; \
    goto label; \
} while(0)

#define fn_parser_err_goto_s(output, result, isNeg, label) do { \
    *output = isNeg? -result : result; \
    goto label; \
} while(0)

#define fn_parser_err_goto_s_n(output, result, label) do { \
    *output = -result; \
    goto label; \
} while(0)

#define fn_parser_err_goto_u(output, result, label) do { \
    *output = result; \
    goto label; \
} while(0)

#define fn_parser_err_of_ret_s(output, result, isNeg) do { \
    if ( isNeg ) { \
        *output = -result; \
        return FN_ERROR_UNDERFLOW; \
    } \
    *output = result; \
    return FN_ERROR_OVERFLOW; \
} while(0)

#define fn_parser_err_of_ret_s_n(output, result) do { \
    *output = -result; \
    return FN_ERROR_UNDERFLOW; \
} while(0)

#define fn_parser_err_of_ret_u(output, result) do { \
    *output = result; \
    return FN_ERROR_OVERFLOW; \
} while(0)
/* ******************* END Parsers Return Macros ******************** */

/* ************ START Flexi No Pos Parsers Return Macros ************ */
/* eov(error or valid):
 *     The final return statement will evaluate for 0 char. If zero
 *     char, it was a valid parsing.
 *
 * voe(valid or error):
 *     The final return statement will always return error. This is
 *     used when an evaluation of whether if the character that is
 *     going to be parsed is the end(null char) of the string is carried
 *     out prior to actually parsing that character. Since it is known
 *     that that character can't be a null char, without the ignore
 *     trailing spaces option and that character is a space, it is an
 *     invalid digit. Therefore, the return error code without the
 *     ignore trailing spaces option code block will always return an
 *     INVALID_FORMAT error code.
 *
 * xor:
 *     strPTR need to be xor to 48 before checking for spaces.
 *
 * raw(if available):
 *     strPTR does not need to be xor to 48 before checking for spaces.
 *
 * s: signed output assignment.
 * u: unsigned output assignment.
 * 0: 0 is assigned to output.
 *
 */
/* xor */
#define fn_fnparser_ret_xor_eov_0(output, options, strPTR) do { \
    *output = 0; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_bwxor_ucptr_48(strPTR) == 16 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return fn_bwxor_ucptr_48(strPTR) == 48? 0 : FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_xor_eov_s(output, result, isNeg, options, strPTR) do { \
    *output = isNeg? -result : result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_bwxor_ucptr_48(strPTR) == 16 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return fn_bwxor_ucptr_48(strPTR) == 48? 0 : FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_xor_eov_u(output, result, options, strPTR) do { \
    *output = result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_bwxor_ucptr_48(strPTR) == 16 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return fn_bwxor_ucptr_48(strPTR) == 48? 0 : FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_xor_voe_s(output, result, isNeg, options, strPTR) do { \
    *output = isNeg? -result : result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_bwxor_ucptr_48(strPTR) == 16 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_xor_voe_s_n(output, result, options, strPTR) do { \
    *output = -result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_bwxor_ucptr_48(strPTR) == 16 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_xor_voe_u(output, result, options, strPTR) do { \
    *output = result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_bwxor_ucptr_48(strPTR) == 16 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_INVALID_FORMAT; \
} while(0)
/* dmap */
#define fn_fnparser_ret_dmap_eov_0(output, options, dmap, strPTR) do { \
    *output = 0; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_getv_dmap(strPTR, dmap) == 252 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return fn_getv_dmap(strPTR, dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_dmap_eov_s(output, result, isNeg, options, dmap, strPTR) do { \
    *output = isNeg? -result : result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_getv_dmap(strPTR, dmap) == 252 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return fn_getv_dmap(strPTR, dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_dmap_eov_u(output, result, options, dmap, strPTR) do { \
    *output = result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_getv_dmap(strPTR, dmap) == 252 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return fn_getv_dmap(strPTR, dmap) == 200? 0 : FN_ERROR_INVALID_FORMAT; \
} while(0)

#define fn_fnparser_ret_dmap_voe_s(output, result, isNeg, options, dmap, strPTR) do { \
    *output = isNeg? -result : result; \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( fn_getv_dmap(strPTR, dmap) == 252 ) { \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? 0 : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_INVALID_FORMAT; \
} while(0)

/*
 * Use ret_d_** for bases with only digit as value representation, use
 * ret_a_** for bases with both alpha and digits as value representation.
 *
 **/
#define fn_fnparser_err_of_ret_d_s(output, result, isNeg, maxDigitI, options, strPTR) do { \
    int retCode; \
    if ( isNeg ){ \
        *output = -result; \
        retCode = FN_ERROR_UNDERFLOW; \
    } else { \
        *output = result; \
        retCode = FN_ERROR_OVERFLOW; \
    } \
    if ( options & FN_PF_LONG_CHECK ){ \
        while ( fn_bwxor_ucptr_48(strPTR) <= maxDigitI ) strPTR++; \
        if ( fn_bwxor_ucptr_48(strPTR) != 16 ) { \
            return fn_bwxor_ucptr_48(strPTR) == 48? retCode : FN_ERROR_INVALID_FORMAT; \
        } \
        if ( options & FN_PF_IGNORE_TSPACES ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? retCode : FN_ERROR_INVALID_FORMAT; \
        } \
        return FN_ERROR_INVALID_FORMAT; \
    } \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( *strPTR == 32 ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? retCode : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return retCode; \
} while(0)

#define fn_fnparser_err_of_ret_d_s_n(output, result, maxDigitI, options, strPTR) do { \
    *output = -result; \
    if ( options & FN_PF_LONG_CHECK ){ \
        while ( fn_bwxor_ucptr_48(strPTR) <= maxDigitI ) strPTR++; \
        if ( fn_bwxor_ucptr_48(strPTR) != 16 ) { \
            return fn_bwxor_ucptr_48(strPTR) == 48? FN_ERROR_UNDERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        if ( options & FN_PF_IGNORE_TSPACES ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_UNDERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        return FN_ERROR_INVALID_FORMAT; \
    } \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( *strPTR == 32 ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_UNDERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_UNDERFLOW; \
} while(0)

#define fn_fnparser_err_of_ret_d_u(output, result, maxDigitI, options, strPTR) do { \
    *output = result; \
    if ( options & FN_PF_LONG_CHECK ){ \
        while ( fn_bwxor_ucptr_48(strPTR) <= maxDigitI ) strPTR++; \
        if ( fn_bwxor_ucptr_48(strPTR) != 16 ) { \
            return fn_bwxor_ucptr_48(strPTR) == 48? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        if ( options & FN_PF_IGNORE_TSPACES ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        return FN_ERROR_INVALID_FORMAT; \
    } \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( *strPTR == 32 ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_OVERFLOW; \
} while(0)

#define fn_fnparser_err_of_ret_a_s(output, result, isNeg, maxDigitI, options, dmap, strPTR) do { \
    int retCode; \
    if ( isNeg ){ \
        *output = -result; \
        retCode = FN_ERROR_UNDERFLOW; \
    } else { \
        *output = result; \
        retCode = FN_ERROR_OVERFLOW; \
    } \
    if ( options & FN_PF_LONG_CHECK ){ \
        while ( fn_getv_dmap(strPTR, dmap) <= maxDigitI ) strPTR++; \
        if ( fn_getv_dmap(strPTR, dmap) != 252 ) { \
            return fn_getv_dmap(strPTR, dmap) == 200? retCode : FN_ERROR_INVALID_FORMAT; \
        } \
        if ( options & FN_PF_IGNORE_TSPACES ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? retCode : FN_ERROR_INVALID_FORMAT; \
        } \
        return FN_ERROR_INVALID_FORMAT; \
    } \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( *strPTR == 32 ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? retCode : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return retCode; \
} while(0)

#define fn_fnparser_err_of_ret_a_s_n(output, result, maxDigitI, options, dmap, strPTR) do { \
    *output = -result; \
    if ( options & FN_PF_LONG_CHECK ){ \
        while ( fn_getv_dmap(strPTR, dmap) <= maxDigitI ) strPTR++; \
        if ( fn_getv_dmap(strPTR, dmap) != 252 ) { \
            return fn_getv_dmap(strPTR, dmap) == 200? FN_ERROR_UNDERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        if ( options & FN_PF_IGNORE_TSPACES ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_UNDERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        return FN_ERROR_INVALID_FORMAT; \
    } \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( *strPTR == 32 ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_UNDERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_UNDERFLOW; \
} while(0)

#define fn_fnparser_err_of_ret_a_u(output, result, maxDigitI, options, dmap, strPTR) do { \
    *output = result; \
    if ( options & FN_PF_LONG_CHECK ){ \
        while ( fn_getv_dmap(strPTR, dmap) <= maxDigitI ) strPTR++; \
        if ( fn_getv_dmap(strPTR, dmap) != 252 ) { \
            return fn_getv_dmap(strPTR, dmap) == 200? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        if ( options & FN_PF_IGNORE_TSPACES ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
        return FN_ERROR_INVALID_FORMAT; \
    } \
    if ( options & FN_PF_IGNORE_TSPACES ){ \
        if ( *strPTR == 32 ){ \
            strPTR++; \
            while ( *strPTR == 32 ) strPTR++; \
            return !*strPTR? FN_ERROR_OVERFLOW : FN_ERROR_INVALID_FORMAT; \
        } \
    } \
    return FN_ERROR_OVERFLOW; \
} while(0)
/* ************* END Flexi No Pos Parsers Return Macros ************* */

/* ************* START Continuous Parsers Return Macros ************* */
/* Err Ret 0 */
#define fn_cparser_err_ret_0_nptr_null(output, nextPTR, code) do { \
    *output = 0; \
    if ( nextPTR != NULL ) *nextPTR = NULL; \
    return code; \
} while(0)

#define fn_cparser_err_ret_0_nptr_raw(output, nextPTR, retPTR, code) do { \
    *output = 0; \
    if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(retPTR); \
    return code; \
} while(0)

/* Err OF Ret d */
/*
 * Use ret_d_** for bases with only digit as value representation, use
 * ret_a_** for bases with both alpha and digits as value representation.
 *
 **/
#define fn_cparser_err_of_ret_d_s(output, result, isNeg, maxDigitI, nextPTR, retPTR) do { \
    if ( options & FN_PC_OVERFLOW_SKIP ){ \
        while (1) { \
            if ( fn_bwxor_ucptr_48(retPTR) > maxDigitI ) break; \
            retPTR++; \
        } \
        if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(retPTR) == 48? NULL : fn_ptr_deConst_cp(retPTR); \
    } else { \
        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(retPTR); \
    } \
    if ( isNeg ){ \
        *output = -result; \
        return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_UNDERFLOW : 0; \
    } \
    *output = result; \
    return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_OVERFLOW : 0; \
} while(0)

#define fn_cparser_err_of_ret_d_s_n(output, result, maxDigitI, nextPTR, retPTR) do { \
    if ( options & FN_PC_OVERFLOW_SKIP ){ \
        while (1) { \
            if ( fn_bwxor_ucptr_48(retPTR) > maxDigitI ) break; \
            retPTR++; \
        } \
        if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(retPTR) == 48? NULL : fn_ptr_deConst_cp(retPTR); \
    } else { \
        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(retPTR); \
    } \
    *output = -result; \
    return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_UNDERFLOW : 0; \
} while(0)

#define fn_cparser_err_of_ret_d_u(output, result, maxDigitI, nextPTR, retPTR) do { \
    if ( options & FN_PC_OVERFLOW_SKIP ){ \
        while (1) { \
            if ( fn_bwxor_ucptr_48(retPTR) > maxDigitI ) break; \
            retPTR++; \
        } \
        if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(retPTR) == 48? NULL : fn_ptr_deConst_cp(retPTR); \
    } else { \
        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(retPTR); \
    } \
    *output = result; \
    return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_OVERFLOW : 0; \
} while(0)

/* Err OF Ret a */
#define fn_cparser_err_of_ret_a_s(output, result, isNeg, maxDigitI, dmap, nextPTR, retPTR) do { \
    if ( options & FN_PC_OVERFLOW_SKIP ){ \
        while (1) { \
            if ( fn_getv_dmap(retPTR, dmap) > maxDigitI ) break; \
            retPTR++; \
        } \
        if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(retPTR, dmap) == 200? NULL : fn_ptr_deConst_cp(retPTR); \
    } else { \
        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(retPTR); \
    } \
    if ( isNeg ){ \
        *output = -result; \
        return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_UNDERFLOW : 0; \
    } \
    *output = result; \
    return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_OVERFLOW : 0; \
} while(0)

#define fn_cparser_err_of_ret_a_s_n(output, result, maxDigitI, dmap, nextPTR, retPTR) do { \
    if ( options & FN_PC_OVERFLOW_SKIP ){ \
        while (1) { \
            if ( fn_getv_dmap(retPTR, dmap) > maxDigitI ) break; \
            retPTR++; \
        } \
        if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(retPTR, dmap) == 200? NULL : fn_ptr_deConst_cp(retPTR); \
    } else { \
        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(retPTR); \
    } \
    *output = -result; \
    return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_UNDERFLOW : 0; \
} while(0)

#define fn_cparser_err_of_ret_a_u(output, result, maxDigitI, dmap, nextPTR, retPTR) do { \
    if ( options & FN_PC_OVERFLOW_SKIP ){ \
        while (1) { \
            if ( fn_getv_dmap(retPTR, dmap) > maxDigitI ) break; \
            retPTR++; \
        } \
        if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(retPTR, dmap) == 200? NULL : fn_ptr_deConst_cp(retPTR); \
    } else { \
        if ( nextPTR != NULL ) *nextPTR = fn_ptr_deConst_cp(retPTR); \
    } \
    *output = result; \
    return (options & FN_PC_OVERFLOW_ERROR)? FN_ERROR_OVERFLOW : 0; \
} while(0)

/* Ret xor */
#define fn_cparser_ret_0_xor(output, result, nextPTR, retPTR) do { \
    *output = 0; \
    if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(retPTR) == 48? NULL : fn_ptr_deConst_cp(retPTR); \
    return 0; \
} while(0)

#define fn_cparser_ret_s_xor(output, result, isNeg, nextPTR, retPTR) do { \
    *output = isNeg? -result : result; \
    if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(retPTR) == 48? NULL : fn_ptr_deConst_cp(retPTR); \
    return 0; \
} while(0)

#define fn_cparser_ret_s_n_xor(output, result, nextPTR, retPTR) do { \
    *output = -result; \
    if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(retPTR) == 48? NULL : fn_ptr_deConst_cp(retPTR); \
    return 0; \
} while(0)

#define fn_cparser_ret_u_xor(output, result, nextPTR, retPTR) do { \
    *output = result; \
    if ( nextPTR != NULL ) *nextPTR = fn_bwxor_ucptr_48(retPTR) == 48? NULL : fn_ptr_deConst_cp(retPTR); \
    return 0; \
} while(0)

/* Ret dmap */
#define fn_cparser_ret_0_dmap(output, result, dmap, nextPTR, retPTR) do { \
    *output = 0; \
    if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(retPTR, dmap) == 200? NULL : fn_ptr_deConst_cp(retPTR); \
    return 0; \
} while(0)

#define fn_cparser_ret_s_dmap(output, result, isNeg, dmap, nextPTR, retPTR) do { \
    *output = isNeg? -result : result; \
    if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(retPTR, dmap) == 200? NULL : fn_ptr_deConst_cp(retPTR); \
    return 0; \
} while(0)

#define fn_cparser_ret_u_dmap(output, result, dmap, nextPTR, retPTR) do { \
    *output = result; \
    if ( nextPTR != NULL ) *nextPTR = fn_getv_dmap(retPTR, dmap) == 200? NULL : fn_ptr_deConst_cp(retPTR); \
    return 0; \
} while(0)
/* ************** END Continuous Parsers Return Macros ************** */

/* ****************** START Error Aborting Macros ******************* */
/*
 * Abort macro was written like this for easy alter of features if
 * needed and also flexibility.
 **/
#define fn_err_terminate(funcName, err, msg) do { \
    fprintf(stderr, \
            "faiNumber Error Termination.\n" \
            "Function: %s.\n" \
            "Error: %s.\n" \
            "Message: %s.\n", \
            funcName, err, msg); \
    abort(); \
} while(0)
/* ******************* END Error Aborting Macros ******************** */

#endif    /* faiNumber - uniMacro.h */
