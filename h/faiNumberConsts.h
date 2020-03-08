#ifndef ___faiNumber_faiNumberConsts_H___
#define ___faiNumber_faiNumberConsts_H___
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
#include <inttypes.h>    /* For int32_t and such */
#include <stddef.h>      /* For size_t */

/* ************************START OPTION FLAGS************************ */
/*
 * @DEV-NOTE: If a new option flag is added and their order is changed.
 *            OPT_***_ALL can be calculate using
 *            "VALID OPT FLAG | NEXT OPT FLAG | ... and so on".
 *            To validate if the correct option flag was send to a
 *            function and if the option value not in order, use bitwise
 *            not. ( OPTs & ( ~OPT_***_ALL ) ). That must yield a zero
 *            value, if only valid options was included.
 *
 * FN_OPT_NONE  A value that can be sent to any functions where options
 *              is available to use the functions with default behaviour
 *              and without any option on. It is a guarantee that
 *              FN_OPT_NONE will always be a value of zero.
 *
 * @NOTE  Unless stated otherwise, functions of this library will abort
 *        by calling the abort() function if they receive any option
 *        flag that they don't support including invalid one. For
 *        example, calling the function decToInt32FN with the option
 *        flag FN_PF_PARSE_ON_ERROR will make the function call
 *        the abort() function. decToInt32FN will also call the abort()
 *        function when it receive any option flag that are not
 *        the values of those flags that it support.
 *
 **/
#define FN_OPT_NONE 0
/*
 * Options Flags for flexi parsers (i.e decToInt32FP, decToInt32FN )
 *
 * The OPT part of the name is removed for the option flag because it
 * make it easier for typing and because of the length of these flag
 * names it is a low risk that these option macro flag will have a
 * name clash with another const or macro. Also, without the OPT
 * part, it is still easy to identify that these are option flags.
 *
 **/
#define FN_PF_IGNORE_LSPACES 1
#define FN_PF_IGNORE_TSPACES 2
#define FN_PF_IGNORE_SPACES 3     /* = FN_FP_IGNORE_LSPACES | FN_FP_IGNORE_TSPACES */
#define FN_PF_LONG_CHECK 4
#define FN_PF_PARSE_ON_ERROR 8    /* NA to **FN parsers */

/*
 * FN_OPT_PFP_ALL is used to turn on all options for flexi parser
 * functions with suffix FP(i.e decToInt32FP) where FN_OPT_PFN_ALL
 * for those flexi functions with suffix FN(i.e decToInt32FN.
 *
 * PFP stand for Parser FP, where PFN stand for Parser FN.
 *
 * The OPT is added to the all option on macros for easy identification,
 * and also that the name get longer to reduce the chances of name
 * conflicts.
 **/
#define FN_OPT_PFP_ALL 15
#define FN_OPT_PFN_ALL 7

/*
 * Options Flag for continuous parsers (i.e decToInt32C1 )
 * C1 suffix stand for Continuous Design 1.
 *
 **/
#define FN_PC_NO_INVALID_SKIP 1
#define FN_PC_OVERFLOW_ERROR 2
#define FN_PC_OVERFLOW_SKIP 4

/*
 * FN_OPT_PC1_ALL is used to turn on all options for continuous parser
 * functions end with the suffix C1(i.*/
#define FN_OPT_PC1_ALL 7
/* *************************END OPTION FLAGS************************* */

/* *************************START Error Codes************************ */
/*
 * 1) FN_ERROR_NONE value is returned when there is no error.
 *    For future releases, it is a guarantee that FN_ERROR_NONE will
 *    always be a zero value.
 * 2) FN_ERROR_GENERAL value is returned by functions that does not
 *    return true error but only returned a general error value
 *    when it has encountered an error.
 *    For future releases, it is almost a guarantee that
 *    FN_ERROR_GENERAL will always be a value of 1.
 * 3) FN_ERROR_GENERAL shouldn't be use as a compare error code value
 *    when using a function that returning an actual error code
 *    for the type errors that it has encountered.
 * 4) ERROR_NULL_PTR and ERROR_ILLEGAL_ARGS are not being used but
 *    are just reserved.
 *
 **/
#define FN_ERROR_NONE 0
/*
 * Error 1 - 99: Numbering Error(with 1 & 2 reserved for underflow &
 *               overflow).
 **/
#define FN_ERROR_UNDERFLOW 1
#define FN_ERROR_OVERFLOW 2
/*
 * Error 100 - 199: Invalid Formatting Error.
 **/
#define FN_ERROR_EMPTY_STR 100
#define FN_ERROR_INVALID_FORMAT 101
#define FN_ERROR_NO_VALID_DATA 102
/*
 * Error 200 - 899: Reserved For Future Usage.
 **/
/*
 * Error 900 - 999: Invalid Arguments, Invalid Addresses.
 **/
#define FN_ERROR_NULL_PTR 900
#define FN_ERROR_ILLEGAL_ARGS 901
/*
 * General Error Code.
 **/
#define FN_ERROR_GENERAL 1
/* *************************END Error Codes************************** */

/* ***********************START VERSION NUMBER*********************** */
/* This will be define with the correct version when release */
/* Version = Hexadecimal.
 * Major: 4 left most digits.
 * Minor: Next 3 digits.
 * Build: The last digit.(Final is always f).
 *
 * Major releases: Features changes or additional of new features and
 *                 or APIs.
 * Minor releases: Bug fix patches, or patches to improve performance
 *                 without any changes to any features and/or APIs.
 * Built: (0) Alpha.
 *      : (1 - 7)  Beta 1 to Beta 7.
 *      : (8 - 14) RC 1 to RC 7.
 *      : (15) Final.
 *
 * If there are more than 7 Beta or 7 Release Candidate versions then
 * the minor release version get move up by one without actually
 * releasing the final build to the pre move up version.
 *
 * A version can go from Beta to RC but can't go from RC to Beta.
 *
 * Version Alpha is use only for development mode.
 *
 * It is possible for any major version to receive a minor release.
 * For example, if the current major version is 3, although the APIs
 * will not change nor will there be any additional features, it is
 * still possible for version 1 or 2 to receive patches that are
 * available for that version.
 *
 **/
#define FAINUMBER_C_MAJOR 0x0001
#define FAINUMBER_C_MINOR 0x000
#define FAINUMBER_C_BUILD 0xf
#define FAINUMBER_C_VERSION 0x0001000f
/* ************************END VERSION NUMBER************************ */

#endif    /* faiNumber - faiNumberConsts.h */
