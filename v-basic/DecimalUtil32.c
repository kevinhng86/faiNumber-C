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
/* faiNumber - DecimalUtil32.c */
#include "../h/DecimalUtil32.h"

/* START INTERNAL MACRO INCLUSION */
#include "../uni/uniMacro.h"
/* END INTERNAL MACRO INCLUSION */
/*
 * @NOTE  Alternative methods is saved to this __int32 files for
 *        reference. Loop may not be manually unroll when parsing int64
 *        or when the digits is more than 20 digits. Alternative codes
 *        may need to be edited prior to usage.
 *
 * / ** comment blocks are meant for future document generator when
 * released.
 *
 * Also see DEV-NOTE.txt.
 *
 * Important values: 48: 0, 43: +, 45: -
 *
 **/
int decToInt32 (const char * restrict str, int32_t * const output){
    int32_t result;
    unsigned int isNeg;
    /*
     * 0: Empty string.
     * 45(-): Negative.
     * 43(+): Positive
     * Have a sign, but next is 0, that is an invalid string.
     *
     * Case 45 and 43 can be fall through, but doing it like this allow
     * setting the isNeg value when needed and when not. Thus, saving
     * one execution cost of when setting the isNeg value to 0 and then
     * assign to it again with a value of 1 when there is a minus sign.
     *
     **/
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

    /*
     * Parse the first digit outside of loop.
     *
     * 0 xor 48 will become 48. Thus, null char after xor is 48.
     *
     * Casting char pointer to unsigned char pointer so that the
     * dereference value is represent as 0 - 255 naturally, and safely.
     * Otherwise, that value can be -128 - 127, and its negative value
     * will be converted to a negative int equivelent during the xor
     * process. Negative values xor to 48 will yield negative values.
     * Thus, without using char values as unsigned the the comparison
     * operation would yield incorrect results.
     *
     * Doing it like the below is to prevent any negative conversation
     * before the xor process. Nonetheless, to make it easy for future
     * code maintenance of the xor process, the xor process is done
     * through a macro.
     *
     * Alternative: (v: 214 - 216 | 203 - 205)
     *
     * result = fn_bwxor_ucptr_48(str);
     * if ( result > 9 ){
     *     *output = 0;
     *     return result == 48? 0 : FN_ERROR_GENERAL;
     * }
     * str++;
     *
     */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 9 ){
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* End First Char Parse */

    /*
     * Parse the next 8 digits.
     *
     * Unrolling the loop like below offer greater performance.
     * Nonetheless, these two alternative loops is saved here as
     * reference. They seemed to operate as the same speed when
     * optimized with -O2. The top alternative code may need to be
     * added with an overflow check for pointer arithmetic.
     *
     * for ( const char * const maxM1 = str + 8; str < maxM1; str++ ){
     *     if ( fn_bwxor_ucptr_48(str) > 9 ){
     *         *output = isNeg? -result : result;
     *         return !*str? 0 : 1;
     *     }
     *     result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
     * }
     *
     * for ( int i = 0; i < 8; i++, str++ ){
     *     if ( fn_bwxor_ucptr_48(str) > 9 ){
     *         *output = isNeg? -result : result;
     *         return !*str? 0 : 1;
     *     }
     *     result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
     * }
     *
     **/
    /* START Parse Until Max Number Length - 1 */
/* START decToInt32 UNROLL MACRO */
#define decToInt32_loop_unroll  \
    if ( fn_bwxor_ucptr_48(str) > 9 ){ \
        *output = isNeg? -result : result; \
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToInt32_loop_unroll;
    decToInt32_loop_unroll;
    decToInt32_loop_unroll;
    decToInt32_loop_unroll;
    decToInt32_loop_unroll;
    decToInt32_loop_unroll;
    decToInt32_loop_unroll;
    decToInt32_loop_unroll;

#undef decToInt32_loop_unroll
/* END decToInt32 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /*
     * If parsing 8 digits + 1(first digit) and there are still more to
     * the string, parse one more character. If there is more than 10
     * digits that is more than int32 max and min. Hence, if all the
     * characters were valid digits, an overflow string of number
     * for this data type.
     *
     * When parsing the 10th digit, check if adding this 10th digit(if
     * a valid digit) value to the parsed value will make the parsed
     * value become overflow.
     *
     * 2147483647 is int32 max and -2147483648 is int min. Thus, if
     * after parsing the 9th digit and the parsed value is greater than
     * 214748364, it will surely overflow just with the multiplication
     * by 10. If it is below that value, every valid digits can be
     * added to the parsed value without making it overflow. If it is
     * exactly 214748364 then for positive, the maximum value that the
     * 10th digits can be is 8 for negative, and for positive it is 7.
     *
     * It possible to use this formula for dynamic byte size data type
     * and the variable can be setup not only at compile time but
     * also at run time.
     *
     * For dynamic byte size data type, this example demonstrate how
     * to calculate the needed value at run time. First, calculate
     * max length for the data type. To do so, parse the data type max
     * value for the base into an ascii string on first run. If signed,
     * parse both max and min value into 2 strings. Those/that length,
     * is/are max length(s). Of which, when subtract to 1, can be used
     * to know when the overflow check need to be executed. To calculate
     * the max last digit, use "data max % base". To get the value that
     * the parsed have to be compared to when the overflow check is
     * carry out use "(data max - (data max % base)) / base".
     *
     * Take note that, with two's complement system and for signed
     * parsing, not all bases will have the same max length for
     * min value and max value. If the length of min value and max value
     * are not the same, they will only be different by one, with min
     * value being the longer number. Although it is that, their common
     * max length is max value's max length as there only can be one
     * number that have min value's max length and that number is min
     * value. When min value and max value's max length are not the
     * same, there is no value that can overflow at max value's max
     * length.
     *
     * For signed parsing, the code for parsing the last digit for each
     * base can vary, but ultimately, there are only two variety of
     * code:
     *
     * 1. Min and Max value have the same length.
     * 2. Min and Max value do not have the same length.
     *
     * For signed parsing, a big major safety issue when it come to
     * last digit parsing is whether the final bitshift of a negative
     * value conform with the standard as the last shift may resulted
     * in shifting the MSB into the sign bit. In the event where
     * needed to be conformed with the standard, the value can be
     * calculated using "(result * -base) - LastChar". Since the code
     * itself already been micro optimized to be as maximum extend
     * as possible before the last digit, not using bitshifting for the
     * last digit for only negative values would not reduce perfomance
     * noticeably if it does. That calculation in the end, without
     * shifting, have a high change of being optimized by the compiler
     * as one of the value of the calculation is a statical one(-base).
     *
     **/
    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_GENERAL);

         /*
          * If this library were to support Ones' complement a macro can
          * be defined like this alternative. But currentlly, this
          * library chose to only support Two's Complement.
          *
          * This was written like the below for reference as INT**_T
          * only support Two's Complement. But if this function
          * were to write for int. Basically the TRIGGER MACRO is issue
          * when ((INT_MIN + 1) * -1) != INT_MAX. For the formula, if
          * INT_MIN + 1 then turn into positive does not equal to
          * INT_MAX then that is not the Two's Complement system, and
          * bases on the standard, for negative values, the system
          * should support at least 2n - 1. Where n is without the sign
          * bit and 2 is powered to n.
          *
          * Most unlikely but in an environement where it is absolutely
          * that there isn't any macro definition of evaluation that
          * can be used for comparison at compile time, manual change
          * of the TRIGGER MACRO is possible. Another method is to
          * compile and executing a small and portable program prior to
          * compilation of main library on the targeted system to get
          * all the needed environmental value of the targeted system
          * and save those values as macros definitions in a linked
          * header file. Then build the main library. That linked
          * header file, if available, can be blank, but if the
          * pre-evaluator is executed, macros can be generated and save
          * to that file. That can help obtain environmental values
          * that are not available at compile time. Take note
          * that this is saved as references, this library does
          * not yet have code that require the evaluator prior to
          * compiling the main library.
          *
          * #ifdef TRIGGER_MACRO
          * {{ CODE FOR ONES' COMPLEMENT SYSTEM }}
          * #else
          * {{ CODE FOR TWO'S COMPLEMENT SYSTEM }}
          * #endif
          *
          */
        if ( isNeg ) {
            if ( result > 214748363 ){
                if ( result > 214748364 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_GENERAL);
                if ( fn_bwxor_ucptr_48(str) > 8 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_GENERAL);
            }

            *output = -((result << 3) + (result << 1)) - fn_bwxor_ucptr_48(str);
        } else {
            if ( result > 214748363 ){
                if ( result > 214748364 ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);
                if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);
            }

            *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
        }

        return !*(str + 1)? 0 : FN_ERROR_GENERAL;
    }
    /* END Last Digit Parsing */

    *output = isNeg? -result : result;
    return 0;
}

/**
    !| author: Khang Hoang Nguyen
    !
    !  <p>Parse the `input` string as a signed decimal integer string
    !  to an int32_t value.
    !
    !  <p>Possible Error Yields:<br>
    !  Underflow<br>
    !  Overflow<br>
    !  Empty strings<br>
    !  Invalid format<br>
    !  </p>

*/
int decToInt32TrueError (const char * restrict str, int32_t * const output){
    int32_t result;
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
    if ( fn_bwxor_ucptr_48(str) > 9 ){
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* End First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START decToInt32TrueError UNROLL MACRO  */
#define decToInt32TrueError_loop_unroll \
    if ( fn_bwxor_ucptr_48(str) > 9 ){ \
        *output = isNeg? -result : result; \
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToInt32TrueError_loop_unroll;
    decToInt32TrueError_loop_unroll;
    decToInt32TrueError_loop_unroll;
    decToInt32TrueError_loop_unroll;
    decToInt32TrueError_loop_unroll;
    decToInt32TrueError_loop_unroll;
    decToInt32TrueError_loop_unroll;
    decToInt32TrueError_loop_unroll;

#undef decToInt32TrueError_loop_unroll
/* END decToInt32TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

        if ( isNeg ) {
            if ( result > 214748363 ){
                if ( result > 214748364 ) fn_parser_err_goto_s_n(output, result, decToInt32TrueError_error_check);
                if ( fn_bwxor_ucptr_48(str) > 8 ) fn_parser_err_goto_s_n(output, result, decToInt32TrueError_error_check);
            }

            *output = -((result << 3) + (result << 1)) - fn_bwxor_ucptr_48(str);
        } else {
            if ( result > 214748363 ){
                if ( result > 214748364 ) fn_parser_err_goto_u(output, result, decToInt32TrueError_error_check);
                if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_goto_u(output, result, decToInt32TrueError_error_check);
            }

            *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
        }

        /* START Error Check Block */
        if ( *(str + 1) ){
            decToInt32TrueError_error_check:    /* LABEL */
            str++;
            for ( ; *str; str++ ) {
                if ( *str < '0' || *str > '9' ) return FN_ERROR_INVALID_FORMAT;
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

int decToUInt32 (const char * restrict str, uint32_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_GENERAL);
    /* END Check Empty String */

    uint32_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /*
     * Alternative: (164 - 165 | s: 166 - 167)
     *
     * result = fn_bwxor_ucptr_48(str);
     * if ( result > 9 ) {
     *     *output = 0;
     *     return result == 48? 0 : FN_ERROR_GENERAL;
     * }
     * str++;
     *
     **/
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 9 ) {
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START decToUInt32 UNROLL MACRO  */
#define decToUInt32_loop_unroll \
    if ( fn_bwxor_ucptr_48(str) > 9 ){ \
        *output = result; \
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_GENERAL; \
    } \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToUInt32_loop_unroll;
    decToUInt32_loop_unroll;
    decToUInt32_loop_unroll;
    decToUInt32_loop_unroll;
    decToUInt32_loop_unroll;
    decToUInt32_loop_unroll;
    decToUInt32_loop_unroll;
    decToUInt32_loop_unroll;

#undef decToUInt32_loop_unroll
/* END decToUInt32 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);

        if ( result > 429496728U ){
            if ( result > 429496729U ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);
            if ( fn_bwxor_ucptr_48(str) > 5 ) fn_parser_err_ret_u(output, result, FN_ERROR_GENERAL);
        }

        *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
        return !*(str + 1)? 0 : FN_ERROR_GENERAL;
    }
    /* END Last Digit Parsing */

    *output = result;
    return 0;
}

int decToUInt32TrueError (const char * restrict str, uint32_t * const output){
    /* START Check Empty String */
    if ( !*str ) fn_parser_err_ret_0(output, FN_ERROR_EMPTY_STR);
    /* END Check Empty String */

    uint32_t result;

    /* START Skip Leading 0s */
    while( *str == 48 ) str++;
    /* END Skip Leading 0s */

    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 9 ) {
        *output = 0;
        return fn_bwxor_ucptr_48(str) == 48? 0 : FN_ERROR_INVALID_FORMAT;
    }
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START decToUInt32TrueError UNROLL MACRO  */
#define decToUInt32TrueError_loop_unroll \
    if ( fn_bwxor_ucptr_48(str) > 9 ){ \
        *output = result; \
        return fn_bwxor_ucptr_48(str) == 48 ? 0 : FN_ERROR_INVALID_FORMAT; \
    } \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToUInt32TrueError_loop_unroll;
    decToUInt32TrueError_loop_unroll;
    decToUInt32TrueError_loop_unroll;
    decToUInt32TrueError_loop_unroll;
    decToUInt32TrueError_loop_unroll;
    decToUInt32TrueError_loop_unroll;
    decToUInt32TrueError_loop_unroll;
    decToUInt32TrueError_loop_unroll;

#undef decToUInt32TrueError_loop_unroll
/* END decToUInt32TrueError UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT);

        if ( result > 429496728U ){
            if ( result > 429496729U ) fn_parser_err_goto_u(output, result, decToUInt32TrueError_error_check);
            if ( fn_bwxor_ucptr_48(str) > 5 ) fn_parser_err_goto_u(output, result, decToUInt32TrueError_error_check);
        }

        *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);

        /* START Error Check Block */
        if ( *(str + 1)  ) {
            decToUInt32TrueError_error_check:    /* LABEL */
            str++;
            for ( ; *str; str++ ){
                if ( *str < '0' || *str > '9' ) return FN_ERROR_INVALID_FORMAT;
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

/*
 * Flexi Parser Naming Context:
 *
 * Suffix:
 * **FP = Flexi Parser with positioning and "from" and "to" are size_t.
 * **FN = Flexi Parser without positioning.
 *
 * @NOTE: The suffix **F alone is reserved for future macro creation
 *        for composing the function to call bases on the amount of
 *        argument. That is for when the Flexi Parsers part of the
 *        library become mature and the design for their future
 *        functionality expansion is final.
 *
 *        For Flexi Parsers with positioning. Although "from" and "to"
 *        can both be pointers. Of which, "from" is the input str,
 *        and "to" can be another pointer. Nonetheless, since there is
 *        an available version of the Flexi Parser where "from" and "to"
 *        are not ultilized, taking positions as size_t ensure that the
 *        users do not send a null pointer for the "to" position. But
 *        instead use the appropriate function for their usage cases.
 *
 *        However, in the event where this library of expanding the
 *        Flexi Parsers to create more flexibility for the users, a
 *        version that can take the "from" and "to" positions can just
 *        be a mirror or an exact copy of **FP with its parameter
 *        change and with an undetermined name. Nonetheless, with that
 *        not yet existence function, if a NULL pointer is encoutered
 *        for the "to" position, it will just call and return a value
 *        from it counter part **FN.
 *
 *        Since "from" and "to" are not optional arguments and are
 *        associated to the input string, their placements in the
 *        functions' parameter are right next to the input string.
 *
 **/
/*
 * @NOTE  This function will not check whether if the position "from"
 *        and "to" are valid positions. It will parse base on the input
 *        value of the "from" and "to" positions. The only check that
 *        this function does is that "from" can't be larger than "to".
 *        Both, "from" and "to" are inclusive positions.
 *
 *        ***FP functions DO NOT expect the segment from 'from' to 'to',
 *        inclusively, to contain a NULL CHAR. Even the 'to' position
 *        shouldn't be the temination part of the string.
 *
 **/
int decToInt32FP (const char * restrict str, const size_t from, const size_t to,
                  int32_t * const output, const unsigned int options ){
    /* START Arguments Check */
    /*
     * Since Invalid Arguments are associated with programming errors
     * and can be fixed by the programmer prior to run time. Thus,
     * instead of returning an error, abort() is called.
     *
     * "Bitwise And" to "Bitwise Complement" is to ensure the
     * unnecessary code change in the event where the next version of
     * the function support more options.
     *
     * This check is most likely take the same computational time as
     * compare larger as compare larger will most likely need to
     * subtract options to OPT_***_ALL and check > 0. With this,
     * after anding options, zero(ZF) flag is most likely be checked
     * and the calculation of complementing of the value of macro
     * OPT_***_ALL is probably done at compile time.
     *
     **/
    if ( from > to ) fn_err_terminate(__func__, "Invalid Arguments", "From > To");
    if ( options & fn_bwnot_u(FN_OPT_PFP_ALL) ) fn_err_terminate(__func__, "Invalid Arguments", "Invalid options flag");
    /* END Arguments Check */

    int32_t result;
    unsigned int isNeg;

    const char * end = str + to;
    str += from;

    /* START Ignore Leading And Trailing Spaces */
    if ( options & FN_PF_IGNORE_SPACES ){
        /*
         * There is no way to not have to do an extra unneccessary loop
         * that is not efficient for when both of the ignore spaces
         * options are turned on as str will check until it is <= end
         * and end will also do something similar until it is >= str.
         * Of which if the string only contained spaces, str would
         * be larger than end. The inefficiency will only occur if the
         * string contains one single character with trailing and
         * leading spaces or only a single character.
         *
         * But if the second condition check is just end > str, it will
         * not be enough if only the ignore trailling spaces options is
         * turned on and the string contained only spaces.
         *
         * Although the IGNORE_SPACES option is the IGNORE_LSPACES and
         * IGNORE_TSPACES together, it is still check. That is because
         * doing so help reduce the amount of evaluation needed to jump
         * to right code path if the option is not used. It will take
         * one evaluation to skip this code block if neither of the
         * options is ultilized. On the other hand, it will take an
         * additional evaluation if either of the options is turned on.
         * However, with branch prediction in the image, and if parsing
         * consistently with or without the option without mixing them
         * up, after a few executions, it will cost nothing without
         * the options on. For with the options on, it does not cost
         * any additional evalution.
         *
         **/
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
    /*
     * 0 is not expected within the "from" and "to" segment. Thus,
     * there isn't a case for a NULL character.
     *
     **/
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
    /*
     * When done if *str > *end then the segment only contained 0s.
     *
     * On the other hand, if *str == *end, the segment contained
     * exactly one character for parsing.
     *
     **/
    while( str <= end && *str == 48 ) str++;
    if ( str > end ) {
        *output = 0;
        return 0;
    } else if ( str == end ){
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = isNeg? -fn_bwxor_ucptr_48(str) : fn_bwxor_ucptr_48(str);
        return 0;
    }
    /* END Skip Leading 0s */

    /* START Error Check Block */
    /*
     * Max length is equal to 10. Thus, when end - str, inclusively,
     * there should only be, at max, 9 positions as 0 is a position.
     *
     **/
    if ( (uintptr_t)(end - str) > 9 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto decToInt32FP_error_parse;
        else *output = 0;

        decToInt32FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end; str++ ){
                if ( *str < '0' || *str > '9' ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /*
     * Technically when unrolling this loop below it shouldn't
     * offer any additional benefit as the loop below is a variable
     * length one, and str would always have to be compared to end.
     * Nonetheless, this loop below seemed to operate faster when
     * unroll. Probably due to the save on jump instructions.
     *
     * @NOTE  With the current design, when the code get to here, the
     *        segment must have at least a length of 2 or more as
     *        length ones are parsed right below skip leading zeroes.
     **/
    /* START Parse Until Max Number Length - 1 */
/* decToInt32FP UNROLL MACRO START */
#define decToInt32FP_unroll_loop \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++; \
    if ( str > end ) fn_parser_ret_s(output, result, isNeg)

    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;

#undef decToInt32FP_unroll_loop
/* END decToInt32FP UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    /* *str == *end */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

    if ( isNeg ) {
        if ( result > 214748363 ){
            if ( result > 214748364 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_UNDERFLOW);
            if ( fn_bwxor_ucptr_48(str) > 8 ) fn_parser_err_ret_s_n(output, result, FN_ERROR_UNDERFLOW);
        }

        *output = -((result << 3) + (result << 1)) - fn_bwxor_ucptr_48(str);
    } else {
        if ( result > 214748363 ){
            if ( result > 214748364 ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);
            if ( fn_bwxor_ucptr_48(str) > 7 ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);
        }

        *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
    }
    /* END Last Digit Parsing */

    return 0;
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    decToInt32FP_error_parse:    /* LABEL */
    /*
     * For this part of the code, goto statement is used for code
     * readability. This is because of if combining parsing when it is
     * obvious that parsing from "from" to "to" will produce an
     * overflow with successful parse cases, it will cost additional
     * checks for sucessful parse cases. It will also cost additional
     * checks for usage cases where the result is unneeded for when
     * there is an obvious overflow error.
     *
     * On the other hand, if writing the code block of "error parsing"
     * into the if statement that evaluate the length between "from" and
     * "to" then it will reduce code readability.
     *
     **/
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START decToInt32FP UNROLL MACRO 2 */
#define decToInt32FP_unroll_loop \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;
    decToInt32FP_unroll_loop;

#undef decToInt32FP_unroll_loop
/* END decToInt32FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_s(output, result, isNeg, FN_ERROR_INVALID_FORMAT);

    if ( isNeg ) {
        if ( result > 214748363 ){
            if ( result > 214748364 ){
                str++;
                fn_parser_err_goto_s_n(output, result, decToInt32FP_error_check);
            }
            if ( fn_bwxor_ucptr_48(str) > 8 ){
                str++;
                fn_parser_err_goto_s_n(output, result, decToInt32FP_error_check);
            }
        }

        *output = -((result << 3) + (result << 1)) - fn_bwxor_ucptr_48(str);
    } else {
        if ( result > 214748363 ){
            if ( result > 214748364 ) {
                str++;
                fn_parser_err_goto_u(output, result, decToInt32FP_error_check);
            }
            if ( fn_bwxor_ucptr_48(str) > 7 ){
                str++;
                fn_parser_err_goto_u(output, result, decToInt32FP_error_check);
            }
        }

        *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
    }

    str++;
    goto decToInt32FP_error_check;
    /* END Last Digit Parsing */
    /* **************************END INVALID PARSING************************** */
}

/*
 * FN_PF_PARSE_ON_ERROR is not a valid flag for **FN functions.
 **/
int decToInt32FN (const char * restrict str, int32_t * const output,
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
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_fnparser_ret_xor_eov_0(output, options, str);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START decToInt32FN UNROLL MACRO */
#define decToInt32FN_loop_unroll \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_fnparser_ret_xor_eov_s(output, result, isNeg, options, str); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToInt32FN_loop_unroll;
    decToInt32FN_loop_unroll;
    decToInt32FN_loop_unroll;
    decToInt32FN_loop_unroll;
    decToInt32FN_loop_unroll;
    decToInt32FN_loop_unroll;
    decToInt32FN_loop_unroll;
    decToInt32FN_loop_unroll;

#undef decToInt32FN_loop_unroll
/* END decToInt32FN UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_fnparser_ret_xor_voe_s(output, result, isNeg, options, str);

        if ( isNeg ) {
            if ( result > 214748363 ){
                if ( result > 214748364 ){
                    str++;
                    fn_fnparser_err_of_ret_d_s_n(output, result, 9, options, str);
                }
                if ( fn_bwxor_ucptr_48(str) > 8 ){
                    str++;
                    fn_fnparser_err_of_ret_d_s_n(output, result, 9, options, str);
                }
            }

            *output = -((result << 3) + (result << 1)) - fn_bwxor_ucptr_48(str);
        } else {
            if ( result > 214748363 ){
                if ( result > 214748364 ){
                    str++;
                    fn_fnparser_err_of_ret_d_u(output, result, 9, options, str);
                }
                if ( fn_bwxor_ucptr_48(str) > 7 ){
                    str++;
                    fn_fnparser_err_of_ret_d_u(output, result, 9, options, str);
                }
            }

            *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
        }

        /* START Error Check Block */
        if ( *(str + 1) ){
            str++;

            if ( options & FN_PF_LONG_CHECK ){
                int retCode = isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;

                /* @TODO: Benchmark this vs without xor. */
                /*
                 * If LONG_CHECK is on, Any valid digit is skipped until
                 * the loop found a none valid digit(including the null
                 * char).
                 *
                 * If the first invalid digit that was founded was not
                 * a whitespace then the function will return bases on
                 * that invalid digit. If that invalid digit is a null
                 * char then an under/overflow error is returned. Else,
                 * an INVALID_FORMAT error is returned.
                 *
                 **/
                while ( fn_bwxor_ucptr_48(str) <= 9 ) str++;

                if ( fn_bwxor_ucptr_48(str) != 16 ) {
                    return fn_bwxor_ucptr_48(str) == 48? retCode : FN_ERROR_INVALID_FORMAT;
                }

                /*
                 * If the IGNORE_TSPACES option is on, the current
                 * position of str is move up by one(The only character
                 * that can reach here is a whitespace). A loop will
                 * then skip all the whitespace characters until it
                 * reach a none whitespace character. The function will
                 * then return an error code bases on the the last
                 * character that the loop processed. If that character
                 * is a null char, an under/overflow error is returned.
                 * Otherwise, for any other character, whether valid
                 * or invalid digits, an INVALID_FORMAT error is
                 * returned. For example, "123  1" is not a valid
                 * string of number.
                 *
                 **/
                if ( options & FN_PF_IGNORE_TSPACES ){
                    str++;
                    while ( *str == 32 ) str++;
                    return !*str? retCode : FN_ERROR_INVALID_FORMAT;
                }

                /*
                 * The only time the code can reach this return
                 * statement is if the IGNORE_TSPACES option is not
                 * on and the first loop ended at a whitespace
                 * character. Thus, with the LONG_CHECK option on but
                 * without the IGNORE_TSPACES option, any strings of
                 * numbers that have whitespaces proceeding the valid
                 * digits would be considered invalid strings of
                 * numbers by Parser FN functions.
                 *
                 */
                return FN_ERROR_INVALID_FORMAT;
            }


            /*
             * Without LONG_CHECK and with the IGNORE_TSPACES option,
             * the first character is evaluated for whether if that
             * character is a whitespace. If that character is a
             * whitespace, the character thereafter is skipped until
             * a none whitespace is reached. The return error code is
             * based on that none whitespace character. If that none
             * whitespace character is a null char then the function
             * return without error. Otherwise, an INVALID_FORMAT error
             * is yielded.
             *
             **/
            if ( options & FN_PF_IGNORE_TSPACES ){
                if ( *str == 32 ){
                    str++;
                    while ( *str == 32 ) str++;
                    return !*str? 0 : FN_ERROR_INVALID_FORMAT;
                }
            }

            /*
             * Without the LONG_CHECk option, and without the IGNORE
             * TSPACES option or if the IGNORE_TSPACES option is on but
             * the first character after the max length digit is not
             * a whitespace then an under/overflow error is returned.
             *
             **/
            return isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
        }
        /* END Error Check Block */

        return 0;
    }
    /* END Last Digit Parsing */

    *output = isNeg? -result : result;
    return 0;
}

int decToUInt32FP (const char * restrict str, const size_t from, const size_t to,
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
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
        *output = fn_bwxor_ucptr_48(str);
        return 0;
    }
    /* END Skip Leading 0s */

    /* START Error Check Block */
    if ( (uintptr_t)(end - str) > 9 ) {
        if ( options & FN_PF_PARSE_ON_ERROR ) goto decToUInt32FP_error_parse;
        else *output = 0;

        decToUInt32FP_error_check:    /* LABEL */
        if ( options & FN_PF_LONG_CHECK ) {
            for ( ; str <= end ; str++ ){
                if ( *str < '0' || *str > '9' ) return FN_ERROR_INVALID_FORMAT;
            }
        }

        return FN_ERROR_OVERFLOW;
    }
    /* END Error Check Block */

    /* *************************START VALID PARSING************************* */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START decToUInt32FP UNROLL MACRO */
#define decToUInt32FP_unroll_loop \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++; \
    if ( str > end ) fn_parser_ret_u(output, result)

    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;

#undef decToUInt32FP_unroll_loop
/* END decToUInt32FP UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT);

    if ( result > 429496728U ){
        if ( result > 429496729U ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);
        if ( fn_bwxor_ucptr_48(str) > 5 ) fn_parser_err_ret_u(output, result, FN_ERROR_OVERFLOW);
    }

    *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
    /* END Last Digit Parsing */

    return 0;
    /* **************************END VALID PARSING************************** */

    /* *************************START INVALID PARSING************************* */
    decToUInt32FP_error_parse:    /* LABEL */
    /* START First Char Parse */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_0(output, FN_ERROR_INVALID_FORMAT);
    result = fn_bwxor_ucptr_48(str);
    str++;
    /* END First Char Parse */

    /* START Parse Until Max Number Length - 1 */
/* START decToUInt32FP UNROLL MACRO 2 */
#define decToUInt32FP_unroll_loop \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;
    decToUInt32FP_unroll_loop;

#undef decToUInt32FP_unroll_loop
/* END decToUInt32FP UNROLL MACRO 2 */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_parser_err_ret_u(output, result, FN_ERROR_INVALID_FORMAT);

    if ( result > 429496728U ){
        if ( result > 429496729U ){
            str++;
            fn_parser_err_goto_u(output, result, decToUInt32FP_error_check);
        }
        if ( fn_bwxor_ucptr_48(str) > 5 ){
            str++;
            fn_parser_err_goto_u(output, result, decToUInt32FP_error_check);
        }
    }

    *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
    str++;
    /* END Last Digit Parsing */

    goto decToUInt32FP_error_check;
    /* **************************END INVALID PARSING************************** */
}

int decToUInt32FN (const char * restrict str, uint32_t * const output,
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
    if ( fn_bwxor_ucptr_48(str) > 9 ) {
        *output = 0;
        /*
         * @NOTE  This code and its comment is kept here as reference.
         *        as except to the error check block, the rest of
         *        the code is going to use macro. This is same
         *        for parsing signed **FP.
         *
         * If options is check first it will help the branch predictor
         * for cases where IGNORE_TSPACES is not utilize.
         *
         * When parsing a string of digit, within the function, this
         * option(the IGNORE_TSPACES) will only be checked one, it just
         * come down to where. For now, there are a few varieties of
         * this evaluation. But it shouldn't be that many. Thus, if this
         * option is not on and branch predictor recognized it, it
         * will cost little to no additional computational time to
         * evaluate whether if the IGNORE_TSPACES option is on. With
         * branch predictor, the worst computational time cost is when
         * parse one with this option on and the next one without this
         * option on.
         *
         * If with the IGNORE_TSPACES option, the first character to
         * check is the unparsable character. Of which, that character
         * value had been xor to 48. Therefore, to check for whether
         * if that character is a space or not efficiently, its value
         * must be compared to the value of "a whitespace character xor
         * to 48". Of which, that value is 16(32 xor 48). If that
         * unparsable character is a whitespace then the remaining of
         * the string is checked in a normal fashion of skipping
         * whitespaces by comparing characters to the whitespace
         * character. After skipping the whitespaces, if the first
         * none whitespace character is not a null character, that is
         * an invalid format string of number. Note that the code was
         * written with ASCII values but besides the 16 ' ' can also be
         * used.
         *
         * Without the IGNORE_TSPACES option, the value of the
         * unparsable character is used to determine the error. If
         * that unparsable character is not a null character, that is
         * an invalid format string of number.
         *
         **/
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
/* START decToUInt32FN UNROLL MACRO */
#define decToUInt32FN_loop_unroll \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_fnparser_ret_xor_eov_u(output, result, options, str); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToUInt32FN_loop_unroll;
    decToUInt32FN_loop_unroll;
    decToUInt32FN_loop_unroll;
    decToUInt32FN_loop_unroll;
    decToUInt32FN_loop_unroll;
    decToUInt32FN_loop_unroll;
    decToUInt32FN_loop_unroll;
    decToUInt32FN_loop_unroll;

#undef decToUInt32FN_loop_unroll
/* END decToUInt32FN UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( *str ){
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_fnparser_ret_xor_voe_u(output, result, options, str);

        if ( result > 429496728U ){
            if ( result > 429496729U ){
                str++;
                fn_fnparser_err_of_ret_d_u(output, result, 9, options, str);
            }
            if ( fn_bwxor_ucptr_48(str) > 5 ){
                str++;
                fn_fnparser_err_of_ret_d_u(output, result, 9, options, str);
            }
        }

        *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);

        /* START Error Check Block */
        if ( *(str + 1) ) {
            str++;

            if ( options & FN_PF_LONG_CHECK ){
                while ( fn_bwxor_ucptr_48(str) <= 9 ) str++;

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

/*
 *
 * @NOTE  nextPTR is optional, nextPTR can be NULL or a valid address.
 *        ***C1 function aborts if they receive any option flag that
 *        they do not support.
 *
 * Next Pointer Assignment:
 * nextPTR will never be equal to NULL unless a NULL character is
 * founded.
 *
 * *Output assign.: a) A valid result without error.
 *                  b) 0 if EMPTY_STR, NO_VALID_DATA, and
 *                     INVALID_FORMAT error.
 *                  c) A none overflow parsed value right just before
 *                     the first valid digit that can make the parsed
 *                     result become overflow when overflow parsing is
 *                     encountered. That is whether if any of the
 *                     options related to overflow parsing is on or not.
 *
 * Default Behaviour
 * a) This function will skip any invalid digits that it first
 *    encounter.
 * b) It will parse the from the first valid digit that it founded until
 *    one of the following condition occur:
 *      (1) it encounters a NULL character;
 *      (2) it encounters an invalid digit; or
 *      (3) if parsing the value of a valid digit make the value that it
 *          already parsed become under/overflow;
 * c) When this function stop, even if an error is yielded, it will
 * assign the location of the position of where it stopped but not
 * already parsed to "nextPTR" if "nextPTR" is not NULL. Nonetheless,
 * if a null character is founded, if nextPTR is not a NULL pointer then
 * nextPTR will be assigned with a NULL value. If the NO_VALID_DATA
 * error is encountered, it is a guarantee that if nextPTR is available,
 * a NULL value will be assigned to nextPTR.
 *
 * To treat sign as invalid, if parsing one long number into an array.
 * parse first as sign then the rest parse as unsigned using
 * decToUInt32C (i.e +2147478979874121321987979713213797979131313).
 * In that case, the entire number could be made invalid if a sign is
 * encountered elsewhere that is not the beginning of a parsable valid
 * segment within the first segment. Whether that long number is a
 * positive or negative number is decided by the first segment. Note
 * that, it is just an example usage, splitting a number like the
 * example above may not be fit for calculation.
 *
 * Options:
 * OVERFLOW_ERROR  With this option on, an under/overflow error is
 *                 yielded, when the function parses a a continuous
 *                 segment of valid digits that contained a value that
 *                 is smaller/larger than the min/max value of the data
 *                 type. Without this option, this function will never
 *                 return an under/overflow error.
 *
 * OVERFLOW_SKIP   With this option on, if an under/overflow occur, all
 *                 the valid digit will be skipped until an invalid
 *                 digit or a null char is founded. Thus, with this
 *                 option on, and if the function parsed an
 *                 under/overflow segment, nextPTR will either be NULL
 *                 or pointing to an invalid digit. Without this option
 *                 on, when an under/overflow occur, nextPTR, if
 *                 available, will be assigned with the location of
 *                 the first digits that if added to the parsed value
 *                 will make the parsed value become under/overflow.
 *
 * NO_INVALID_SKIP  With this option on, the function will not skip
 *                  any invalid digits when it first started to parse.
 *                  If it encounters an invalid part first, it will
 *                  return and INVALID_FORMAT error. However, if a valid
 *                  segment is founded first, the function will not
 *                  returned an error if it encounter an invalid digit
 *                  after parsing that valid segment. Instead, without
 *                  overflow, nextPTR, if available, will be assigned
 *                  with the first invalid digit that the function
 *                  encountered after it parsed a valid segment.
 *
 * C1 = First Design
 *
 **/
int decToInt32C1 (const char * restrict str, int32_t * const output, char ** const nextPTR,
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
                if ( fn_bwxor_ucptr_48(str + 1) > 9 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
                isNeg = 1;
                str++;
                break;
            }
            case 43:{
                if ( fn_bwxor_ucptr_48(str + 1) > 9 ) fn_cparser_err_ret_0_nptr_raw(output, nextPTR, str, FN_ERROR_INVALID_FORMAT);
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
        if ( fn_bwxor_ucptr_48(str) > 9 ) {
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
            /*
             * Based on ASCII codes, except whitespaces there are more
             * common use characters that are above 57('9') then there
             * are below (48)'0'. Thus, > '9'(57) is compared first.
             * That is also true for both signed and unsigned char. If
             * for some reason there are more characters that needed to
             * be skipped that in ASCII code, are below the value of
             * 48 then if branch prediction is available, and if they
             * (the characters) are continuous, branch prediction will
             * most likely choose the correct evaluation for those
             * continuous segment.
             *
             **/
            if ( *str > '9' ) str++;
            else if ( *str < '0' ){
                switch ( *str ){
                    case 0: fn_cparser_err_ret_0_nptr_null(output, nextPTR, FN_ERROR_NO_VALID_DATA);
                    case 45: {
                        if ( fn_bwxor_ucptr_48(str + 1) > 9 ) break;
                        isNeg = 1;
                        str++;
                        goto decToInt32C1_invalid_skip_done;
                    }
                    case 43:{
                        if ( fn_bwxor_ucptr_48(str + 1) > 9 ) break;
                        isNeg = 0;
                        str++;
                        goto decToInt32C1_invalid_skip_done;
                    }
                    default: break;
                }
                str++;
            } else {
                isNeg = 0;
                decToInt32C1_invalid_skip_done:    /* LABEL */
                break;
            }
        }
        /* END Skipping Invalid And Sign Evaluation */

        /* START Skip Leading 0s */
        while ( *str == 48 ) str++;
        /* END Skip Leading 0s */

        /* START First Char Parse */
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_cparser_ret_0_xor(output, result, nextPTR, str);
        result = fn_bwxor_ucptr_48(str);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length - 1 */
/* START decToInt32C1 UNROLL MACRO */
#define decToInt32C1_loop_unroll \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_cparser_ret_s_xor(output, result, isNeg, nextPTR, str); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToInt32C1_loop_unroll;
    decToInt32C1_loop_unroll;
    decToInt32C1_loop_unroll;
    decToInt32C1_loop_unroll;
    decToInt32C1_loop_unroll;
    decToInt32C1_loop_unroll;
    decToInt32C1_loop_unroll;
    decToInt32C1_loop_unroll;

#undef decToInt32C1_loop_unroll
/* END decToInt32C1 UNROLL MACRO */
    /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_cparser_ret_s_xor(output, result, isNeg, nextPTR, str);

    if ( isNeg ) {
        if ( result > 214748363 ){
            if ( result > 214748364 ) fn_cparser_err_of_ret_d_s_n(output, result, 9, nextPTR, str);
            if ( fn_bwxor_ucptr_48(str) > 8 ) fn_cparser_err_of_ret_d_s_n(output, result, 9, nextPTR, str);
        }

        *output = -((result << 3) + (result << 1)) - fn_bwxor_ucptr_48(str);
    } else {
        if ( result > 214748363 ){
            if ( result > 214748364 ) fn_cparser_err_of_ret_d_u(output, result, 9, nextPTR, str);
            if ( fn_bwxor_ucptr_48(str) > 7 ) fn_cparser_err_of_ret_d_u(output, result, 9, nextPTR, str);
        }

        *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
    }
    /* END Last Digit Parsing */

    /* START Overflow Check */
    if ( *(str + 1) ){
        str++;
        int retCode;

        if ( options & FN_PC_OVERFLOW_ERROR && fn_bwxor_ucptr_48(str) <= 9 ){
            retCode = isNeg? FN_ERROR_UNDERFLOW : FN_ERROR_OVERFLOW;
        } else retCode = 0;

        if ( options & FN_PC_OVERFLOW_SKIP ){
            /*
             * @TODO  Benchmark this and added (N) characters
             *        evaluation per loop execution. Where (N) depend
             *        on code size, performance, and if possible,
             *        cache size.
             *
             **/
            while (1) {
                if ( fn_bwxor_ucptr_48(str) > 9 ) break;
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

int decToUInt32C1 (const char * restrict str, uint32_t * const output, char ** const nextPTR,
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
        if ( fn_bwxor_ucptr_48(str) > 9 ) {
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
            if ( *str > '9' ) str++;
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
        if ( fn_bwxor_ucptr_48(str) > 9 ) fn_cparser_ret_0_xor(output, result, nextPTR, str);
        result = fn_bwxor_ucptr_48(str);
        str++;
        /* END First Char Parse */
    /* ***********************END INVALID SKIP*********************** */
    }

    /* START Parse Until Max Number Length - 1 */
/* START decToUInt32C1 UNROLL MACRO */
#define decToUInt32C1_loop_unroll \
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_cparser_ret_u_xor(output, result, nextPTR, str); \
    result = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str); \
    str++

    decToUInt32C1_loop_unroll;
    decToUInt32C1_loop_unroll;
    decToUInt32C1_loop_unroll;
    decToUInt32C1_loop_unroll;
    decToUInt32C1_loop_unroll;
    decToUInt32C1_loop_unroll;
    decToUInt32C1_loop_unroll;
    decToUInt32C1_loop_unroll;

#undef decToUInt32C1_loop_unroll
/* END decToUInt32C1 UNROLL MACRO */
   /* END Parse Until Max Number Length - 1 */

    /* START Last Digit Parsing */
    if ( fn_bwxor_ucptr_48(str) > 9 ) fn_cparser_ret_u_xor(output, result, nextPTR, str);

    if ( result > 429496728U ){
        if ( result > 429496729U ) fn_cparser_err_of_ret_d_u(output, result, 9, nextPTR, str);
        if ( fn_bwxor_ucptr_48(str) > 5 ) fn_cparser_err_of_ret_d_u(output, result, 9, nextPTR, str);
    }

    *output = (result << 3) + (result << 1) + fn_bwxor_ucptr_48(str);
    /* END Last Digit Parsing */

    /* START Overflow Check */
    if ( *(str + 1) ){
        str++;
        int retCode;

        if ( options & FN_PC_OVERFLOW_ERROR && fn_bwxor_ucptr_48(str) <= 9 ){
            retCode = FN_ERROR_OVERFLOW;
        } else retCode = 0;

        if ( options & FN_PC_OVERFLOW_SKIP ){
            while (1) {
                if ( fn_bwxor_ucptr_48(str) > 9 ) break;
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
fn_make_func_comparator_parser_as(decCompareAsInt32, decToInt32, int32_t)
fn_make_func_comparator_parser_orsmaller(decInt32OrSmaller, decToInt32TrueError, int32_t)

fn_make_func_comparator_parser_as(decCompareAsUInt32, decToUInt32, uint32_t)
fn_make_func_comparator_parser_orsmaller(decUInt32OrSmaller, decToUInt32TrueError, uint32_t)
/* END UNI FUNCTIONS MAKER */
