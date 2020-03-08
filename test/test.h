#ifndef ___faiNumber_test_H___
#define ___faiNumber_test_H___
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
#include <inttypes.h>

/* *********************START VARIABLE DEFINITION******************** */
const static char digits[] = {'0','1','2','3','4','5','6','7','8','9',
                              'a','b','c','d','e','f','g','h','i','j',
                              'k','l','m','n','o','p','q','r','s','t',
                              'u','v','w','x','y','z'
                             };
const static char digitsA[] = {'0','1','2','3','4','5','6','7','8','9',
                               'A','B','C','D','E','F','G','H','I','J',
                               'K','L','M','N','O','P','Q','R','S','T',
                               'U','V','W','X','Y','Z'
                              };
/* **********************END VARIABLE DEFINITION********************* */

/* *************************START MISC MACRO************************* */
#define ALEN(ARRAY) sizeof(ARRAY) / sizeof(ARRAY[0])
#define CONCAT_SRC_TEXT(v1, v2) v1##v2
/* **************************END MISC MACRO************************** */

/* *******************START TEST STRUCT DEFINITION******************* */
/*
 * These struct are strictly build for faiNumber parsers test cases.
 * Currently struct are made like this so that it uniformly and
 * less error prone.
 **/
#define MAKE_P_CASE_STRUCT(pre, su, w) \
    typedef struct pCase##w##su {\
        char * input; \
        pre##int##w##_t exp1;\
        int exp2; \
    } pCase##w##su

#define MAKE_PFP_CASE_STRUCT(pre, su, w) \
    typedef struct pfpCase##w##su { \
        char * input; \
        size_t from; \
        size_t to; \
        unsigned int opt; \
        pre##int##w##_t exp1; \
        int exp2; \
    } pfpCase##w##su

#define MAKE_PFN_CASE_STRUCT(pre, su, w) \
    typedef struct pfnCase##w##su { \
        char * input; \
        unsigned int opt; \
        pre##int##w##_t exp1; \
        int exp2; \
    } pfnCase##w##su

/* @NOTE: PC1 test case stuct was not built for testing string that is
 *        longer than int32_t max value. Length of expected maximum
 *        is 10.
 **/
#define MAKE_PC1_CASE_STRUCT(pre,su,w) \
    typedef struct pc1Case##w##su{ \
        char * input; \
        unsigned int opt; \
        pre##int##w##_t exp1[10]; \
        int exp2[10]; \
        int32_t exp3[10]; \
        size_t elen; \
    } pc1Case##w##su

/* Parser test struct for 32 */
MAKE_P_CASE_STRUCT(,s, 32);
MAKE_P_CASE_STRUCT(u,u, 32);
/* Parser test struct for 64 */
MAKE_P_CASE_STRUCT(,s, 64);
MAKE_P_CASE_STRUCT(u,u, 64);

typedef struct cCase {
    char * input1;
    char * input2;
    int exp1;
    int exp2;
} cCase;

typedef struct cCaseNE {
    char * input1;
    char * input2;
    int exp1;
} cCaseNE;

/* Flexi test struct for 32 */
MAKE_PFP_CASE_STRUCT(,s,32);
MAKE_PFP_CASE_STRUCT(u,u,32);

/* Flexi test struct for 64 */
MAKE_PFP_CASE_STRUCT(,s,64);
MAKE_PFP_CASE_STRUCT(u,u,64);

/* Parser FN test struct for 32 */
MAKE_PFN_CASE_STRUCT(,s,32);
MAKE_PFN_CASE_STRUCT(u,u,32);
/* Parser FN test struct for 64 */
MAKE_PFN_CASE_STRUCT(,s,64);
MAKE_PFN_CASE_STRUCT(u,u,64);

/* Parser C1 test struct for 32 */
MAKE_PC1_CASE_STRUCT(,s,32);
MAKE_PC1_CASE_STRUCT(u,u,32);
/* Parser C1 test struct for 64 */
MAKE_PC1_CASE_STRUCT(,s,64);
MAKE_PC1_CASE_STRUCT(u,u,64);

#undef MAKE_P_CASE_STRUCT
#undef MAKE_PFP_CASE_STRUCT
#undef MAKE_PFN_CASE_STRUCT
#undef MAKE_PC1_CASE_STRUCT
/* ********************END TEST STRUCT DEFINITION******************** */

/* ******************START NORMAL PARSER TEST MACRO****************** */
/* Parse Case Test Loop*/
#define MAKE_P_CASES_LOOP(TNAME, FUNC, INTTYPE, ARRAY, LEN, PRINTER) do { \
    INTTYPE result; \
    int err; \
    for ( int i = 0; i < LEN; i++ ){ \
        err = FUNC(ARRAY[i].input, &result); \
        if ( err != ARRAY[i].exp2 ) { \
            printf("Test failed. " TNAME  ". Unexpected error code.\n" \
                   "Case: %d\n" \
                   "Input: '%s'\n" \
                   "Expected Result: %" PRINTER "    | Expected Error Code: %d\n" \
                   "Returned Result: %" PRINTER "    | Returned Error Code: %d\n", \
                   i, \
                   ARRAY[i].input, ARRAY[i].exp1, ARRAY[i].exp2, \
                   result, err); \
            return 1; \
        } \
        if ( result != ARRAY[i].exp1 ){ \
            printf("Test failed. " TNAME ". Unexpected result value.\n" \
                   "Case: %d\n" \
                   "Input: '%s'\n" \
                   "Expected Result: %" PRINTER "    | Expected Error Code: %d\n" \
                   "Returned Result: %" PRINTER "    | Returned Error Code: %d\n", \
                   i, \
                   ARRAY[i].input, ARRAY[i].exp1, ARRAY[i].exp2, \
                   result, err); \
            return 1; \
        } \
    } \
} while(0)

/* Parse Cases Test 1 Signed */
#define MAKE_P_CASES_TEST1_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, PRINTER) do { \
    puts ("# Test 1(Signed): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            err = FUNC(&cbuffer[1], &result); \
            /* 0 - Max Digit */ \
            if ( err ){ \
                printf("Test failed. Unexpected error returned at parse without sign.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse without sign.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], result, err); \
                return 1; \
            } \
            /* +0 - +Max Digit */ \
            cbuffer[0] = '+'; \
            err = FUNC(cbuffer, &result); \
            if ( err ){ \
                printf("Test failed. Unexpected error returned at parse with sign (+).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse with sign (+).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, result, err); \
                return 1; \
            } \
            /* -0 - -Max Digit */ \
            cbuffer[0] = '-'; \
            err = FUNC(cbuffer, &result); \
            if ( err ){ \
                printf("Test failed. Unexpected error returned at parse with sign (-).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, result, err); \
                return 1; \
            } \
            if ( result != -expR ){ \
                printf("Test failed. Wrong result value at parse with sign (-).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, result, err); \
                return 1; \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1: Passed.\n"); \
} while(0)

/* Parse Cases Test 1 Unsigned */
#define MAKE_P_CASES_TEST1_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, PRINTER) do { \
    puts ("# Test 1(Unsigned): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            err = FUNC(&cbuffer[1], &result); \
            if ( err ){ \
                printf("Test failed. Unexpected error returned.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], result, err); \
                return 1; \
            } \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1: Passed.\n"); \
} while(0)

/* Parse Cases Test 2 Signed */
#define MAKE_P_CASES_TEST2_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, ERREXP, PRINTER) do { \
    puts ("# TEST 2(Signed): Invalid digits check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    signed char i; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE expR = 0; \
    INTTYPE result; \
    int err; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            err = FUNC(&cbuffer[1], &result); \
            /* NS */ \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse without sign.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse without sign.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
                return 1; \
            } \
            /* + */ \
            cbuffer[0] = '+'; \
            err = FUNC(cbuffer, &result); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse with sign (+).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse with sign (+).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            /* - */ \
            cbuffer[0] = '-'; \
            err = FUNC(cbuffer, &result); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse with sign (-).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            if ( result != -expR ){ \
                printf("Test failed. Wrong result value at parse with sign (-).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2: Passed.\n"); \
} while(0)

/* Parse Cases Test 2 Unsigned */
#define MAKE_P_CASES_TEST2_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, ERREXP, PRINTER) do { \
    puts ("# TEST 2(Unsigned): Invalid digits check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    signed char i; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE expR = 0; \
    INTTYPE result; \
    int err; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            err = FUNC(&cbuffer[1], &result); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
                return 1; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2: Passed.\n"); \
} while(0)
/* *******************END NORMAL PARSER TEST MACRO******************* */

/* *******************START COMPARATOR TEST MACRO******************** */
/* Comparator Case Test Loop*/
#define MAKE_C_CASES_LOOP(TNAME, FUNC, ARRAY, LEN) do { \
    int result, err; \
    for ( int i = 0; i < LEN; i++ ){ \
        err = FUNC(ARRAY[i].input1, ARRAY[i].input2, &result); \
        if ( err != ARRAY[i].exp2 ) { \
            printf ("Test failed. " TNAME ". Unexpected error code.\n" \
                    "Case: %d.\n" \
                    "Input 1: '%s'    | Input 2: '%s'\n" \
                    "Expected Result: %d    | Expected Error Code: %d\n" \
                    "Returned Result: %d    | Returned Error Code: %d\n", \
                    i, \
                    ARRAY[i].input1, ARRAY[i].input2, \
                    ARRAY[i].exp1, ARRAY[i].exp2, \
                    result, err); \
            return 1; \
        } \
        if ( result != ARRAY[i].exp1 ) { \
            printf("Test failed. " TNAME ". Unexpected result value.\n" \
                   "Case: %d.\n" \
                   "Input 1: '%s'    | Input 2: '%s'\n" \
                   "Expected Result: %d    | Expected Error Code: %d\n" \
                   "Returned Result: %d    | Returned Error Code: %d\n", \
                   i, \
                   ARRAY[i].input1, ARRAY[i].input2, \
                   ARRAY[i].exp1, ARRAY[i].exp2, \
                   result, err); \
            return 1; \
        } \
    } \
} while(0)

/* NE = No Error */
#define MAKE_C_CASESNE_LOOP(TNAME, FUNC, ARRAY, LEN) do { \
    int result; \
    for ( int i = 0; i < LEN; i++ ){ \
        result = FUNC(ARRAY[i].input1, ARRAY[i].input2); \
        if ( result != ARRAY[i].exp1 ) { \
            printf("Test failed. " TNAME ". Unexpected result value.\n" \
                   "Case: %d.\n" \
                   "Input 1: '%s'    | Input 2: '%s'\n" \
                   "Expected Result: %d\n" \
                   "Returned Result: %d\n", \
                   i, \
                   ARRAY[i].input1, ARRAY[i].input2, \
                   ARRAY[i].exp1, \
                   result); \
            return 1; \
        } \
    } \
} while(0)
/* ********************END COMPARATOR TEST MACRO********************* */

/* *******************START FP PARSER TEST MACRO********************* */
/* Parser FP Test Loop*/
#define MAKE_PFP_CASES_LOOP(TNAME, FUNC, INTTYPE, ARRAY, LEN, PRINTER) do { \
    INTTYPE result; \
    int err; \
    for ( int i = 0; i < LEN; i++ ){ \
        err = FUNC(ARRAY[i].input, ARRAY[i].from, ARRAY[i].to, &result, ARRAY[i].opt ); \
        if ( err != ARRAY[i].exp2 ) { \
            printf ("Test failed. " TNAME ". Unexpected error code.\n" \
                    "Case: %d\n" \
                    "Input: '%s'    | From: %zu    | To: %zu    | Opt: %u\n" \
                    "Expected Result: %" PRINTER "    | Expected Error Code: %d\n" \
                    "Returned Result: %" PRINTER "    | Returned Error Code: %d\n", \
                    i, \
                    ARRAY[i].input, ARRAY[i].from, ARRAY[i].to, ARRAY[i].opt, \
                    ARRAY[i].exp1, ARRAY[i].exp2, \
                    result, err); \
            return 1; \
        } \
        if ( result != ARRAY[i].exp1 ) { \
            printf("Test failed. " TNAME ". Unexpected result value.\n" \
                   "Case: %d\n" \
                   "Input: '%s'    | From: %zu    | To: %zu    | Opt: %u\n" \
                   "Expected Result: %" PRINTER "    | Expected Error Code: %d\n" \
                   "Returned Result: %" PRINTER "    | Returned Error Code: %d\n", \
                   i, \
                   ARRAY[i].input, ARRAY[i].from, ARRAY[i].to, ARRAY[i].opt, \
                   ARRAY[i].exp1, ARRAY[i].exp2, \
                   result, err); \
            return 1; \
        } \
    } \
} while(0)

/* Parser FP Fatal Test Loop*/
#define MAKE_PFP_CASES_FATAL(TNAME, FUNC, INTTYPE, ARRAY, LEN) do { \
    INTTYPE result; \
    int err = 0; \
    volatile size_t i = 0; \
    volatile int flag; \
    puts ("\nTake note, for portability error printer is not supressed."); \
    fflush(stdout); \
    puts ("-----------------START Error Printers------------------------"); \
    for ( ; i < LEN; i++ ){ \
        flag = setjmp(FN_TL_JMP_BUFF); \
        signal(SIGABRT, abortJMP); \
        if ( flag != FN_TL_JMP_CODE ) err = FUNC(ARRAY[i].input, ARRAY[i].from, ARRAY[i].to, &result, ARRAY[i].opt ); \
        if ( i + 1 < LEN) puts(""); \
    } \
    puts ("------------------END Error Printers-------------------------\n"); \
    if ( i != LEN ) { \
        printf("Test failed. " TNAME ". Not all signal is raised.\n" \
               "Length: %zu\n" \
               "Counter: %zu\n", \
               LEN, \
               i); \
       return 1; \
    } \
    signal(SIGABRT, SIG_DFL); \
    if ( err ) {} \
} while(0)

/* Parser FP Test 1A Signed */
#define MAKE_PFP_CASES_TEST1A_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OPTARR, OPTARRLEN, PRINTER) do { \
    puts ("# Test 1A(Signed): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            for ( size_t optP = 0; optP < OPTARRLEN; optP++ ) { \
                err = FUNC(cbuffer, 1, pos, &result, OPTARR[optP] ); \
                /* 0 - Max Digit */ \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned at parse without sign.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != expR ){ \
                    printf("Test failed. Wrong result value at parse without sign.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                /* +0 - +Max Digit */ \
                cbuffer[0] = '+'; \
                err = FUNC(cbuffer, 0, pos, &result, OPTARR[optP] ); \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned at parse with sign (+).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != expR ){ \
                    printf("Test failed. Wrong result value at parse with sign (+).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                /* -0 - -Max Digit */ \
                cbuffer[0] = '-'; \
                err = FUNC(cbuffer, 0, pos, &result, OPTARR[optP] ); \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned at parse with sign (-).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != -expR ){ \
                    printf("Test failed. Wrong result value at parse with sign (-).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1A: Passed.\n"); \
} while(0)

/* Parser FP Cases Test 1A Unsigned */
#define MAKE_PFP_CASES_TEST1A_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OPTARR, OPTARRLEN, PRINTER) do { \
    puts ("# Test 1A(Unsigned): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            for ( size_t optP = 0; optP < OPTARRLEN; optP++ ) { \
                err = FUNC(cbuffer, 1, pos, &result, OPTARR[optP] ); \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != expR ){ \
                    printf("Test failed. Wrong result value.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1A: Passed.\n"); \
} while(0)

/* Parser FP Cases Test 1B Signed */
/* Test 1B is the same as test 1A but for the error parser */
#define MAKE_PFP_CASES_TEST1B_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OFLEN, PRINTER) do { \
    puts ("# Test 1B(Signed): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            err = FUNC(cbuffer, 1, OFLEN + 1, &result, FN_PF_PARSE_ON_ERROR | FN_PF_LONG_CHECK ); \
            /* 0 - Max Digit */ \
            if ( err != FN_ERROR_INVALID_FORMAT ){ \
                printf("Test failed. Unexpected error code at parse without sign.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        &cbuffer[1], result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse without sign.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        &cbuffer[1], result, err); \
                return 1; \
            } \
            /* +0 - +Max Digit */ \
            cbuffer[0] = '+'; \
            err = FUNC(cbuffer, 0, OFLEN, &result, FN_PF_PARSE_ON_ERROR | FN_PF_LONG_CHECK); \
            if ( err != FN_ERROR_INVALID_FORMAT ){ \
                printf("Test failed. Unexpected error code at parse with sign (+).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        cbuffer, result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse with sign (+).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        cbuffer, result, err); \
                return 1; \
            } \
            /* -0 - -Max Digit */ \
            cbuffer[0] = '-'; \
            err = FUNC(cbuffer, 0, OFLEN, &result, FN_PF_PARSE_ON_ERROR | FN_PF_LONG_CHECK); \
            if ( err != FN_ERROR_INVALID_FORMAT ){ \
                printf("Test failed. Unexpected error code at parse with sign (-).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        cbuffer, result, err); \
                return 1; \
            } \
            if ( result != -expR ){ \
                printf("Test failed. Wrong result value at parse with sign (-).\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        cbuffer, result, err); \
                return 1; \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1B: Passed.\n"); \
} while(0)

/* Parser FP Cases Test 1B Unsigned */
#define MAKE_PFP_CASES_TEST1B_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OFLEN, PRINTER) do { \
    puts ("# Test 1B(Unsigned): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            err = FUNC(cbuffer, 1, OFLEN + 1, &result, FN_PF_PARSE_ON_ERROR | FN_PF_LONG_CHECK ); \
            if ( err != FN_ERROR_INVALID_FORMAT ){ \
                printf("Test failed. Unexpected error code.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        &cbuffer[1], result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value.\n" \
                       "String: '%s'    | Result: %" PRINTER "    | Error Code: %d\n", \
                        &cbuffer[1], result, err); \
                return 1; \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1B: Passed.\n"); \
} while(0)

/* Parser FP Test 2 Signed */
#define MAKE_PFP_CASES_TEST2_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OFLEN, ERREXP, PRINTER) do { \
    puts ("# TEST 2(Signed): Invalid digits check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    signed char i; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE expR = 0; \
    INTTYPE result; \
    int err; \
    unsigned int opt = 0; \
    size_t to; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            CONCAT_SRC_TEXT(FUNC, _pfp_cases_test2_s_start_parse):    /* LABEL */ \
            to = !opt? pos : OFLEN; \
            err = FUNC(cbuffer, 1, to, &result, opt); \
            /* NS */ \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse without sign.\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, opt, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse without sign.\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, opt, \
                       result, err); \
                return 1; \
            } \
            /* + */ \
            cbuffer[0] = '+'; \
            err = FUNC(cbuffer, 0, to, &result, opt); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse with sign (+).\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, opt, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse with sign (+).\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, opt, \
                       result, err); \
                return 1; \
            } \
            /* - */ \
            cbuffer[0] = '-'; \
            err = FUNC(cbuffer, 0, to, &result, opt); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse with sign (-).\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, opt, \
                       result, err); \
                return 1; \
            } \
            if ( result != -expR ){ \
                printf("Test failed. Wrong result value at parse with sign (-).\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, opt, \
                       result, err); \
                return 1; \
            } \
            if ( !opt ){ \
                opt = FN_PF_PARSE_ON_ERROR | FN_PF_LONG_CHECK; \
                goto CONCAT_SRC_TEXT(FUNC, _pfp_cases_test2_s_start_parse); \
            } else { \
                opt = 0; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2: Passed.\n"); \
} while(0)

/* Parser FP Test 2 Unsigned */
#define MAKE_PFP_CASES_TEST2_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OFLEN, ERREXP, PRINTER) do { \
    puts ("# TEST 2(Unsigned): Invalid digits check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    signed char i; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE expR = 0; \
    INTTYPE result; \
    int err; \
    unsigned int opt = 0; \
    size_t to; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            CONCAT_SRC_TEXT(FUNC, _pfp_cases_test2_u_start_parse):    /* LABEL */ \
            to = !opt? pos : OFLEN; \
            err = FUNC(cbuffer, 1, to, &result, opt); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code.\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, opt, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value.\n" \
                       "String: '%s'    | Current Char Code: %d    | Opt: %u\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, opt, \
                       result, err); \
                return 1; \
            } \
            if ( !opt ){ \
                opt = FN_PF_PARSE_ON_ERROR | FN_PF_LONG_CHECK; \
                goto CONCAT_SRC_TEXT(FUNC, _pfp_cases_test2_u_start_parse); \
            } else { \
                opt = 0; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2: Passed.\n"); \
} while(0)
/* ********************END FP PARSER TEST MACRO********************** */

/* *******************START FN PARSER TEST MACRO********************* */
/* Parser FN Test Loop*/
#define MAKE_PFN_CASES_LOOP(TNAME, FUNC, INTTYPE, ARRAY, LEN, PRINTER) do { \
    INTTYPE result; \
    int err; \
    for ( int i = 0; i < LEN; i++ ){ \
        err = FUNC(ARRAY[i].input, &result, ARRAY[i].opt); \
        if ( err != ARRAY[i].exp2 ) { \
            printf ("Test failed. " TNAME ". Unexpected error code.\n" \
                    "Case: %d\n" \
                    "Input: '%s'    | Opt: %u\n" \
                    "Expected Result: %" PRINTER "    | Expected Error Code: %d\n" \
                    "Returned Result: %" PRINTER "    | Returned Error Code: %d\n", \
                    i, \
                    ARRAY[i].input, ARRAY[i].opt, \
                    ARRAY[i].exp1, ARRAY[i].exp2, \
                    result, err); \
            return 1; \
        } \
        if ( result != ARRAY[i].exp1 ) { \
            printf("Test failed. " TNAME ". Unexpected result value.\n" \
                   "Case: %d\n" \
                   "Input: '%s'    | Opt: %u\n" \
                   "Expected Result: %" PRINTER "    | Expected Error Code: %d\n" \
                   "Returned Result: %" PRINTER "    | Returned Error Code: %d\n", \
                   i, \
                   ARRAY[i].input, ARRAY[i].opt, \
                   ARRAY[i].exp1, ARRAY[i].exp2, \
                   result, err); \
            return 1; \
        } \
    } \
} while(0)

/* Parser FN Fatal Test Loop*/
#define MAKE_PFN_CASES_FATAL(TNAME, FUNC, INTTYPE, ARRAY, LEN) do { \
    INTTYPE result; \
    int err = 0; \
    volatile size_t i = 0; \
    volatile int flag; \
    puts ("\nTake note, for portability error printer is not supressed."); \
    fflush(stdout); \
    puts ("-----------------START Error Printers------------------------"); \
    for ( ; i < LEN; i++ ){ \
        flag = setjmp(FN_TL_JMP_BUFF); \
        signal(SIGABRT, abortJMP); \
        if ( flag != FN_TL_JMP_CODE ) err = FUNC(ARRAY[i].input, &result, ARRAY[i].opt ); \
        if ( i + 1 < LEN) puts(""); \
    } \
    puts ("------------------END Error Printers-------------------------\n"); \
    if ( i != LEN ) { \
        printf("Test failed. " TNAME ". Not all signal is raised.\n" \
               "Length: %zu\n" \
               "Counter: %zu\n", \
               LEN, \
               i); \
        return 1; \
    } \
    signal(SIGABRT, SIG_DFL); \
    if ( err ) {} \
} while(0)

/* Parser FN Test 1 Signed */
#define MAKE_PFN_CASES_TEST1_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OPTARR, OPTARRLEN, PRINTER) do { \
    puts ("# Test 1(Signed): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            for ( size_t optP = 0; optP < OPTARRLEN; optP++ ) { \
                err = FUNC(&cbuffer[1], &result, OPTARR[optP]); \
                /* 0 - Max Digit */ \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned at parse without sign.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != expR ){ \
                    printf("Test failed. Wrong result value at parse without sign.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                /* +0 - +Max Digit */ \
                cbuffer[0] = '+'; \
                err = FUNC(cbuffer, &result, OPTARR[optP]); \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned at parse with sign (+).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != expR ){ \
                    printf("Test failed. Wrong result value at parse with sign (+).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                /* -0 - -Max Digit */ \
                cbuffer[0] = '-'; \
                err = FUNC(cbuffer, &result, OPTARR[optP]); \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned at parse with sign (-).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != -expR ){ \
                    printf("Test failed. Wrong result value at parse with sign (-).\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            cbuffer, OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1: Passed.\n"); \
} while(0)

/* Parser FN Cases Test 1 Unsigned */
#define MAKE_PFN_CASES_TEST1_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OPTARR, OPTARRLEN, PRINTER) do { \
    puts ("# Test 1(Unsigned): Min to max digit check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            for ( size_t optP = 0; optP < OPTARRLEN; optP++ ) { \
                err = FUNC(&cbuffer[1], &result, OPTARR[optP]); \
                if ( err ){ \
                    printf("Test failed. Unexpected error returned.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
                if ( result != expR ){ \
                    printf("Test failed. Wrong result value.\n" \
                           "String: '%s'    | Opt: %u\n" \
                           "Result: %" PRINTER "    | Error Code: %d\n", \
                            &cbuffer[1], OPTARR[optP], \
                            result, err); \
                    return 1; \
                } \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1: Passed.\n"); \
} while(0)

/* Parser FN Cases Test 2 Signed */
#define MAKE_PFN_CASES_TEST2_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, ERREXP, PRINTER) do { \
    puts ("# TEST 2(Signed): Invalid digits check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    signed char i; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE expR = 0; \
    INTTYPE result; \
    int err; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            err = FUNC(&cbuffer[1], &result, FN_OPT_NONE); \
            /* NS */ \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse without sign.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse without sign.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
               return 1; \
            } \
            /* + */ \
            cbuffer[0] = '+'; \
            err = FUNC(cbuffer, &result, FN_OPT_NONE); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse with sign (+).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value at parse with sign (+).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            /* - */ \
            cbuffer[0] = '-'; \
            err = FUNC(cbuffer, &result, FN_OPT_NONE); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code at parse with sign (-).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            if ( result != -expR ){ \
                printf("Test failed. Wrong result value at parse with sign (-).\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       cbuffer, i, \
                       result, err); \
                return 1; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2: Passed.\n"); \
} while(0)

/* Parser FN Cases Test 2 Unsigned */
#define MAKE_PFN_CASES_TEST2_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, ERREXP, PRINTER) do { \
    puts ("# TEST 2(Unsigned): Invalid digits check."); \
    char cbuffer[MAXLEN + 2] = {0}; \
    signed char i; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE expR = 0; \
    INTTYPE result; \
    int err; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            err = FUNC(&cbuffer[1], &result, FN_OPT_NONE); \
            if ( err != ERREXP ){ \
                printf("Test failed. Unexpected error code.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
                return 1; \
            } \
            if ( result != expR ){ \
                printf("Test failed. Wrong result value.\n" \
                       "String: '%s'    | Current Char Code: %d\n" \
                       "Result: %" PRINTER "    | Error Code: %d\n", \
                       &cbuffer[1], i, \
                       result, err); \
                return 1; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2: Passed.\n"); \
} while(0)

/* Parser FN Cases Test 3 Signed */
#define MAKE_PFN_CASES_TEST3_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, PRINTER) do { \
    puts ("# Test 3(Signed): IGNORE_TSPACES auto test."); \
    size_t buffStart = 0; \
    char * failMsg; \
    char cbuffer[MAXLEN + 8] = {0}; \
    char iChar; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err, expErr, spCount, spPOS, capChar = 0; \
    int invAdd = 0, invChange = 0; \
    unsigned int opt = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            /* Intialize starting position for spaces */ \
            CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_ini_opt):    /* LABEL */ \
            spCount = 0; \
            spPOS = pos + 1; \
            /* Add space to string */ \
            CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_sp_add):    /* LABEL */ \
            cbuffer[spPOS] = ' '; \
            cbuffer[spPOS + 1] = 0; \
            /* Initialize expected error code */ \
            if ( opt ) { \
                if ( opt == FN_PF_LONG_CHECK ){ \
                    expErr = FN_ERROR_INVALID_FORMAT; \
                } else { \
                    expErr = 0; \
                } \
            } else { \
                expErr = FN_ERROR_INVALID_FORMAT; \
            } \
            /*
             * Add a digit after the space(s).
             * Although, it is call invalid character, the character
             * that is being added is actually a valid character.
             **/ \
            if ( 0 ){ \
                CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_inv_add):    /* LABEL */ \
                cbuffer[spPOS + 1] = '0'; \
                cbuffer[spPOS + 2] = 0; \
                expErr = FN_ERROR_INVALID_FORMAT; \
            } \
            /* Change all the spaces to 1 invalid digit */ \
            if ( 0 ){ \
                CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_inv_change):    /* LABEL */ \
                cbuffer[pos + 1] = iChar; \
                cbuffer[pos + 2] = 0; \
                expErr = FN_ERROR_INVALID_FORMAT; \
            } \
            err = FUNC(&cbuffer[1], &result, opt); \
            /* 0 - Max Digit */ \
            if ( err != expErr ){ \
                 failMsg = "Test failed. Wrong error code at parse without sign."; \
                 buffStart = 1; \
                 goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_fail_case); \
            } \
            if ( result != expR ){ \
                failMsg = "Test failed. Wrong result value at parse without sign."; \
                buffStart = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_fail_case); \
            } \
            /* +0 - +Max Digit */ \
            cbuffer[0] = '+'; \
            err = FUNC(cbuffer, &result, opt); \
            if ( err != expErr ){ \
                failMsg = "Test failed. Wrong error code at parse with sign (+)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_fail_case); \
            } \
            if ( result != expR ){ \
                failMsg = "Test failed. Wrong result value at parse with sign (+)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_fail_case); \
            } \
            /* -0 - -Max Digit */ \
            cbuffer[0] = '-'; \
            err = FUNC(cbuffer, &result, opt); \
            if ( err != expErr ){ \
                failMsg = "Test failed. Wrong error code at parse with sign (-)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_fail_case); \
            } \
            if ( result != -expR ){ \
                expR = -expR; \
                failMsg = "Test failed. Wrong result value at parse with sign (-).\n"; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_fail_case); \
            } \
            /*
             * Fail printer.
             * Here, for debugging purpose.
             *
             **/ \
            if ( 0 ){ \
                CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_fail_case):    /* LABEL */ \
                printf("===============================================\n" \
                       "%s\n" \
                       "String: '%s'    | Opt: %u\n\n" \
                       "Expected Result: %" PRINTER "\n" \
                       "Result: %" PRINTER "\n\n" \
                       "Expected Error Code: %d\n" \
                       "Error Code: %d\n" \
                       "===============================================\n", \
                       failMsg, \
                       &cbuffer[buffStart], opt, \
                       expR, result, \
                       expErr, err); \
                return 1; \
            } \
            /* Invalid character add jump condition */ \
            if ( !invAdd && !invChange ){ \
                invAdd = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_inv_add); \
            } else { \
                invAdd = 0; \
            } \
            /* Adding space jump condition */ \
            if ( spCount < 3 ){ \
                spCount++; \
                spPOS++; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_sp_add); \
            } \
            /* Invalid character change jump condition */ \
            if ( !invChange ){ \
                iChar = '/'; \
                invChange = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_inv_change); \
            } else { \
                if ( invChange == 1 ){ \
                    if ( MAXDIGIT < 35 ) { \
                        iChar = digits[MAXDIGIT + 1]; \
                    } else { \
                        iChar = 123; \
                    } \
                    invChange = 2; \
                    goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_inv_change); \
                } \
                invChange = 0; \
            } \
            /* opt jump condition */ \
            if ( !opt ){ \
                opt = FN_PF_IGNORE_TSPACES; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_ini_opt); \
            } else { \
                if ( opt == FN_PF_IGNORE_TSPACES ) { \
                    opt = FN_PF_LONG_CHECK; \
                    goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_ini_opt); \
                } else if ( opt == FN_PF_LONG_CHECK ) { \
                    opt = FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK; \
                    goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_s_ini_opt); \
                } \
                opt = 0; \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 3: Passed.\n"); \
} while(0)

/* Parser FN Cases Test 3 Unsigned */
#define MAKE_PFN_CASES_TEST3_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, PRINTER) do { \
    puts ("# Test 3(Unsigned): IGNORE_TSPACES auto test."); \
    char * failMsg; \
    char cbuffer[MAXLEN + 8] = {0}; \
    char iChar; \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    INTTYPE preN = 0; \
    INTTYPE result, expR; \
    int err, expErr, spCount, spPOS, capChar = 0; \
    int invAdd = 0, invChange = 0; \
    unsigned int opt = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( INTTYPE i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            /* Intialize starting position for spaces */ \
            CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_ini_opt):    /* LABEL */ \
            spCount = 0; \
            spPOS = pos + 1; \
            /* Add space to string */ \
            CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_sp_add):    /* LABEL */ \
            cbuffer[spPOS] = ' '; \
            cbuffer[spPOS + 1] = 0; \
            /* Initialize expected error code */ \
            if ( opt ) { \
                if ( opt == FN_PF_LONG_CHECK ){ \
                    expErr = FN_ERROR_INVALID_FORMAT; \
                } else { \
                    expErr = 0; \
                } \
            } else { \
                expErr = FN_ERROR_INVALID_FORMAT; \
            } \
            /*
             * Add a digit after the space(s).
             * Although, it is call invalid character, the character
             * that is being added is actually a valid character.
             **/ \
            if ( 0 ){ \
                CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_inv_add):    /* LABEL */ \
                cbuffer[spPOS + 1] = '0'; \
                cbuffer[spPOS + 2] = 0; \
                expErr = FN_ERROR_INVALID_FORMAT; \
            } \
            /* Change all the spaces to 1 invalid digit */ \
            if ( 0 ){ \
                CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_inv_change):    /* LABEL */ \
                cbuffer[pos + 1] = iChar; \
                cbuffer[pos + 2] = 0; \
                expErr = FN_ERROR_INVALID_FORMAT; \
            } \
            err = FUNC(&cbuffer[1], &result, opt); \
            /* 0 - Max Digit */ \
            if ( err != expErr ){ \
                 failMsg = "Test failed. Wrong error code."; \
                 goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_fail_case); \
            } \
            if ( result != expR ){ \
                failMsg = "Test failed. Wrong result value."; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_fail_case); \
            } \
            /*
             * Fail printer.
             * Here, for debugging purpose.
             *
             **/ \
            if ( 0 ){ \
                CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_fail_case):    /* LABEL */ \
                printf("===============================================\n" \
                       "%s\n" \
                       "String: '%s'    | Opt: %u\n\n" \
                       "Expected Result: %" PRINTER "\n" \
                       "Result: %" PRINTER "\n\n" \
                       "Expected Error Code: %d\n" \
                       "Error Code: %d\n" \
                       "===============================================\n", \
                       failMsg, \
                       &cbuffer[1], opt, \
                       expR, result, \
                       expErr, err); \
                return 1; \
            } \
            /* Invalid character add jump condition */ \
            if ( !invAdd && !invChange ){ \
                invAdd = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_inv_add); \
            } else { \
                invAdd = 0; \
            } \
            /* Adding space jump condition */ \
            if ( spCount < 3 ){ \
                spCount++; \
                spPOS++; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_sp_add); \
            } \
            /* Invalid character change jump condition */ \
            if ( !invChange ){ \
                iChar = '/'; \
                invChange = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_inv_change); \
            } else { \
                if ( invChange == 1 ){ \
                    if ( MAXDIGIT < 35 ) { \
                        iChar = digits[MAXDIGIT + 1]; \
                    } else { \
                        iChar = 123; \
                    } \
                    invChange = 2; \
                    goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_inv_change); \
                } \
                invChange = 0; \
            } \
            /* opt jump condition */ \
            if ( !opt ){ \
                opt = FN_PF_IGNORE_TSPACES; \
                goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_ini_opt); \
            } else { \
                if ( opt == FN_PF_IGNORE_TSPACES ) { \
                    opt = FN_PF_LONG_CHECK; \
                    goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_ini_opt); \
                } else if ( opt == FN_PF_LONG_CHECK ) { \
                    opt = FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK; \
                    goto CONCAT_SRC_TEXT(FUNC, _pfn_cases_test3_u_ini_opt); \
                } \
                opt = 0; \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 3: Passed.\n"); \
} while(0)
/* ********************END FN PARSER TEST MACRO********************** */

/* *******************START C1 PARSER TEST MACRO********************* */
/* Parser C1 Test Loop*/
#define MAKE_PC1_CASES_LOOP(TNAME, FUNC, INTTYPE, ARRAY, LEN, PRINTER) do { \
    INTTYPE result; \
    char * failMsg; \
    char *ePTR, *nPTR, *startAddr; \
    int err; \
    int failRet = 0; \
    for ( int i = 0; i < LEN; i++ ){ \
        nPTR = ARRAY[i].input; \
        for ( size_t c = 0; c < ARRAY[i].elen; c++ ){ \
            /* The code was made like this, but -1 is future proof */ \
            if ( ARRAY[i].exp3[c] < 0 ) ePTR = NULL; \
            else ePTR = (char *)((uintptr_t)ARRAY[i].input + (uintptr_t)ARRAY[i].exp3[c]); \
            /*
             * All cases are test with NULL as parameter for nextPTR.
             *
             * If the function produces an erroneous result and the
             * pointer is NULL before hand then the test code would
             * already returned before getting to here again. Thus, if
             * nPTR is NULL prior to loop execution, one or more of the
             * parameters for the test case must be setup incorrectly.
             *
             **/ \
            if ( nPTR == NULL ) { \
                fprintf(stderr, \
                        "Invalid test case parameters.\n" \
                        "Case: %d\n", \
                        i); \
                abort(); \
            } \
            startAddr = nPTR; \
            err = FUNC(nPTR, &result, NULL, ARRAY[i].opt); \
            err = FUNC(nPTR, &result, &nPTR, ARRAY[i].opt); \
            if ( ARRAY[i].exp3[c] == -2 ) nPTR = NULL; \
            if ( err != ARRAY[i].exp2[c] ) { \
                failMsg = "Test failed. " TNAME ". Unexpected error code."; \
                failRet = 1; \
            } \
            if ( result != ARRAY[i].exp1[c] && !failRet ) { \
                failMsg = "Test failed. " TNAME ". Unexpected result value."; \
                failRet = 1; \
            } \
            if ( nPTR != ePTR && !failRet ) { \
                failMsg = "Test failed. " TNAME ". Unexpected pointer value."; \
                failRet = 1; \
            } \
            if ( failRet ) { \
                printf ("%s\n" \
                        "Case: %d    | Expected Case: %zu\n" \
                        "Opt: %u\n" \
                        "Input: '%s'\n" \
                        "Input Addr: %" PRIuPTR "\n" \
                        "Start Addr: %" PRIuPTR "\n\n" \
                        "Expected Result: %" PRINTER "\n" \
                        "Returned Result: %" PRINTER "\n\n" \
                        "Expected Pointer: %" PRIuPTR "\n"  \
                        "Returned Pointer: %" PRIuPTR "\n\n" \
                        "Expected Error Code: %d\n" \
                        "Returned Error Code: %d\n", \
                        failMsg, \
                        i, c, \
                        ARRAY[i].opt, \
                        ARRAY[i].input, (uintptr_t)ARRAY[i].input, (uintptr_t)startAddr, \
                        ARRAY[i].exp1[c], result, \
                        (uintptr_t)ePTR, (uintptr_t)nPTR, \
                        ARRAY[i].exp2[c], err); \
                return 1; \
            } \
        } \
    } \
} while(0)

/* Parser C1 Fatal Test Loop*/
#define MAKE_PC1_CASES_FATAL(TNAME, FUNC, INTTYPE, ARRAY, LEN) do { \
    INTTYPE result; \
    char * voidstr; \
    int err = 0; \
    volatile size_t i = 0; \
    volatile int flag; \
    puts ("\nTake note, for portability error printer is not supressed."); \
    fflush(stdout); \
    puts ("-----------------START Error Printers------------------------"); \
    for ( ; i < LEN; i++ ){ \
        flag = setjmp(FN_TL_JMP_BUFF); \
        signal(SIGABRT, abortJMP); \
        if ( flag != FN_TL_JMP_CODE ) err = FUNC(ARRAY[i].input, &result, &voidstr, ARRAY[i].opt ); \
        if ( i + 1 < LEN) puts(""); \
    } \
    puts ("------------------END Error Printers-------------------------\n"); \
    if ( i != LEN ) { \
        printf("Test failed. " TNAME ". Not all signals are raised.\n" \
               "Length: %zu\n" \
               "Counter: %zu\n", \
               LEN, \
               i); \
        return 1; \
    } \
    signal(SIGABRT, SIG_DFL); \
    if ( err ) {} \
} while(0)

/* Parser C1 Test 1 Signed */
#define MAKE_PC1_CASES_TEST1_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OPTARR, OPTARRLEN, PRINTER) do { \
    puts ("# Test 1(Signed): Min to max digit check."); \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    char * failMsg; \
    size_t buffStart; \
    int negExpR; \
    char cbuffer[MAXLEN + 2] = {0}; \
    char * nPTR; \
    INTTYPE result, expR, preN = 0; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( unsigned char i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            for ( size_t optP = 0; optP < OPTARRLEN; optP++ ) { \
                /* 0 - Max Digit */ \
                err = FUNC(&cbuffer[1], &result, NULL, OPTARR[optP]);    /* NULL Optional Check */ \
                err = FUNC(&cbuffer[1], &result, &nPTR, OPTARR[optP]); \
                if ( err ){ \
                    failMsg = "Test failed. Unexpected error returned at parse without sign."; \
                    buffStart = 1; \
                    negExpR = 0; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                if ( result != expR ){ \
                    failMsg = "Test failed. Wrong result value at parse without sign."; \
                    buffStart = 1; \
                    negExpR = 0; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                if ( nPTR != NULL ){ \
                    failMsg = "Test failed. Unexpected pointer returned at parse without sign."; \
                    buffStart = 1; \
                    negExpR = 0; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                /* +0 - +Max Digit */ \
                cbuffer[0] = '+'; \
                err = FUNC(cbuffer, &result, NULL, OPTARR[optP]);    /* NULL Optional Check */ \
                err = FUNC(cbuffer, &result, &nPTR, OPTARR[optP]); \
                if ( err ){ \
                    failMsg = "Test failed. Unexpected error returned at parse with sign (+)."; \
                    buffStart = 0; \
                    negExpR = 0; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                if ( result != expR ){ \
                    failMsg = "Test failed. Wrong result value at parse with sign (+)."; \
                    buffStart = 0; \
                    negExpR = 0; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                if ( nPTR != NULL ){ \
                    failMsg = "Test failed. Unexpected pointer returned at parse without sign."; \
                    buffStart = 0; \
                    negExpR = 0; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                /* -0 - -Max Digit */ \
                cbuffer[0] = '-'; \
                err = FUNC(cbuffer, &result, NULL, OPTARR[optP]);    /* NULL Optional Check */ \
                err = FUNC(cbuffer, &result, &nPTR, OPTARR[optP]); \
                if ( err ){ \
                    failMsg = "Test failed. Unexpected error returned at parse with sign (-)."; \
                    buffStart = 0; \
                    negExpR = 1; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                if ( result != -expR ){ \
                    failMsg = "Test failed. Wrong result value at parse with sign (-)."; \
                    buffStart = 0; \
                    negExpR = 1; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                if ( nPTR != NULL ){ \
                    failMsg = "Test failed. Unexpected pointer returned at parse without sign."; \
                    buffStart = 0; \
                    negExpR = 1; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case); \
                } \
                if (0){ \
                    CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_s_fail_case):    /* LABEL */ \
                    printf("===============================================\n" \
                           "%s\n" \
                           "Current Digit Value(Base 10): %u    | Char Code: %d\n" \
                           "Opt: %u\n" \
                           "Input: '%s'\n" \
                           "Input Addr: %" PRIuPTR "\n\n" \
                           "Expected Result: %" PRINTER "\n"\
                           "Returned Result: %" PRINTER "\n\n"\
                           "Expected Pointer: %" PRIuPTR "\n" \
                           "Returned Pointer: %" PRIuPTR "\n\n" \
                           "Expected Error Code: %d\n" \
                           "Returned Error Code: %d\n" \
                           "===============================================\n", \
                           failMsg, \
                           i, *(signed char *)(&cbuffer[pos]), OPTARR[optP], \
                           &cbuffer[buffStart], (uintptr_t)&cbuffer[buffStart], \
                           (negExpR? -expR: expR), result, \
                           (uintptr_t)NULL, (uintptr_t)nPTR, \
                           0, err); \
                    return 1; \
                } \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1: Passed.\n"); \
} while(0)

/* Parser C1 Test 1 Unsigned */
#define MAKE_PC1_CASES_TEST1_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, OPTARR, OPTARRLEN, PRINTER) do { \
    puts ("# Test 1(Unsigned): Min to max digit check."); \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    char * failMsg; \
    char cbuffer[MAXLEN + 2] = {0}; \
    char * nPTR; \
    INTTYPE result, expR, preN = 0; \
    int err; \
    int capChar = 0; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for ( unsigned char i = 0; i <= MAXDIGIT; i++ ){ \
            expR = preN + i; \
            if ( !capChar ) cbuffer[pos] = digits[i]; \
            else cbuffer[pos] = digitsA[i]; \
            for ( size_t optP = 0; optP < OPTARRLEN; optP++ ) { \
                err = FUNC(&cbuffer[1], &result, NULL, OPTARR[optP]);    /* NULL Optional Check */ \
                err = FUNC(&cbuffer[1], &result, &nPTR, OPTARR[optP]); \
                if ( err ){ \
                    failMsg = "Test failed. Unexpected error returned."; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_u_fail_case); \
                } \
                if ( result != expR ){ \
                    failMsg = "Test failed. Wrong result value."; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_u_fail_case); \
                } \
                if ( nPTR != NULL ){ \
                    failMsg = "Test failed. Unexpected pointer returned."; \
                    goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_u_fail_case); \
                } \
                if (0){ \
                    CONCAT_SRC_TEXT(FUNC, _pc1_cases_test1_u_fail_case):    /* LABEL */ \
                    printf("===============================================\n" \
                           "%s\n" \
                           "Current Digit Value(Base 10): %u    | Char Code: %d\n" \
                           "Opt: %u\n" \
                           "Input: '%s'\n" \
                           "Input Addr: %" PRIuPTR "\n\n" \
                           "Expected Result: %" PRINTER "\n"\
                           "Returned Result: %" PRINTER "\n\n"\
                           "Expected Pointer: %" PRIuPTR "\n" \
                           "Returned Pointer: %" PRIuPTR "\n\n" \
                           "Expected Error Code: %d\n" \
                           "Returned Error Code: %d\n" \
                           "===============================================\n", \
                           failMsg, \
                           i, *(signed char *)(&cbuffer[pos]), OPTARR[optP], \
                           &cbuffer[1], (uintptr_t)&cbuffer[1], \
                           expR, result, \
                           (uintptr_t)NULL, (uintptr_t)nPTR, \
                           0, err); \
                    return 1; \
                } \
            } \
            /* If max digit > 9, ensure parsing both, the lower case and upper case of i */ \
            if ( i > 9 ){ \
                if ( capChar ){ \
                    capChar = 0; \
                } else { \
                    capChar = 1; \
                    i--; \
                } \
            } \
        } \
        if ( pos < MAXLEN ) { \
            preN = (preN + 1) * base; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 1: Passed.\n"); \
} while(0)

/* Parser C1 Test 2A Signed */
#define MAKE_PC1_CASES_TEST2A_S(FUNC, INTTYPE, MAXDIGIT, MAXLEN, PRINTER) do { \
    puts ("# TEST 2A(Signed): Invalid digits check."); \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    char * failMsg; \
    size_t buffStart; \
    signed char i; \
    unsigned int opt = 0; \
    char cbuffer[MAXLEN + 2] = {0}; \
    char * nPTR, * expPTR; \
    INTTYPE result, expR = 0; \
    int err, expERR; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_start_parse):    /* LABEL */ \
            if ( pos == 1 ) { \
                if ( !opt ) { \
                    expPTR = NULL; \
                    expERR = FN_ERROR_NO_VALID_DATA; \
                } else { \
                    expPTR = &cbuffer[pos]; \
                    expERR = FN_ERROR_INVALID_FORMAT; \
                } \
            } else { \
                expPTR = &cbuffer[pos]; \
                expERR = 0; \
            } \
            /* NS */ \
            err = FUNC(&cbuffer[1], &result, NULL, opt);    /* NULL Optional Check */ \
            err = FUNC(&cbuffer[1], &result, &nPTR, opt); \
            if ( err != expERR ){ \
                failMsg = "Test failed. Unexpected error code at parse without sign."; \
                buffStart = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            if ( result != expR ){ \
                failMsg = "Test failed. Wrong result value at parse without sign."; \
                buffStart = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            if ( nPTR != expPTR ){ \
                failMsg = "Test failed. Wrong pointer value ret at parse without sign."; \
                buffStart = 1; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            /* + */ \
            if ( pos == 1 && opt ) expPTR = cbuffer; \
            cbuffer[0] = '+'; \
            err = FUNC(cbuffer, &result, NULL, opt);    /* NULL Optional Check */ \
            err = FUNC(cbuffer, &result, &nPTR, opt); \
            if ( err != expERR ){ \
                failMsg = "Test failed. Unexpected error code at parse with sign (+)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            if ( result != expR ){ \
                failMsg = "Test failed. Wrong result value at parse with sign (+)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            if ( nPTR != expPTR ){ \
                failMsg = "Test failed. Wrong pointer value ret at parse with sign (+)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            /* - */ \
            cbuffer[0] = '-'; \
            err = FUNC(cbuffer, &result, NULL, opt);    /* NULL Optional Check */ \
            err = FUNC(cbuffer, &result, &nPTR, opt); \
            if ( err != expERR ){ \
                failMsg = "Test failed. Unexpected error code at parse with sign (-)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            if ( result != -expR ){ \
                failMsg = "Test failed. Wrong result value at parse with sign (-)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            if ( nPTR != expPTR ){ \
                failMsg = "Test failed. Wrong pointer value ret at parse with sign (-)."; \
                buffStart = 0; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case); \
            } \
            if (0) { \
                CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_fail_case):    /* LABEL */ \
                printf("===============================================\n" \
                       "%s\n" \
                       "Current Char Code: %d    | Opt: %u\n" \
                       "Input: '%s'\n" \
                       "Input Addr: %" PRIuPTR "\n\n" \
                       "Expected Result: %" PRINTER "\n"\
                       "Returned Result: %" PRINTER "\n\n"\
                       "Expected Pointer: %" PRIuPTR "\n" \
                       "Returned Pointer: %" PRIuPTR "\n\n" \
                       "Expected Error Code: %d\n" \
                       "Returned Error Code: %d\n" \
                       "===============================================\n", \
                       failMsg, \
                       i, opt, \
                       &cbuffer[buffStart], (uintptr_t)&cbuffer[buffStart], \
                       expR, result, \
                       (uintptr_t)expPTR, (uintptr_t)nPTR, \
                       expERR, err); \
                return 1; \
            } \
            if ( !opt ){ \
                opt = FN_PC_NO_INVALID_SKIP; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_s_start_parse); \
            } else { \
                opt = 0; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2A: Passed.\n"); \
} while(0)

/* Parser C1 Test 2A Signed */
#define MAKE_PC1_CASES_TEST2A_U(FUNC, INTTYPE, MAXDIGIT, MAXLEN, PRINTER) do { \
    puts ("# TEST 2A(Unigned): Invalid digits check."); \
    const INTTYPE base = (INTTYPE)(MAXDIGIT + 1); \
    char * failMsg; \
    signed char i; \
    unsigned int opt = 0; \
    char cbuffer[MAXLEN + 2] = {0}; \
    char * nPTR, * expPTR; \
    INTTYPE result, expR = 0; \
    int err, expERR; \
    for ( size_t pos = 1; pos <= MAXLEN; pos++ ){ \
        for( i = -128 ;; i++ ){ \
            if ( MAXDIGIT < 10 ){ \
                if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
            } else { \
                if ( i >= 48 && i <= digits[9] ) continue; \
                else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
                else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
            } \
            if ( i == 0 ) continue; \
            cbuffer[pos] = *(char *)(&i); \
            CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_u_start_parse):    /* LABEL */ \
            if ( pos == 1 ) { \
                if ( !opt ) { \
                    expPTR = NULL; \
                    expERR = FN_ERROR_NO_VALID_DATA; \
                } else { \
                    expPTR = &cbuffer[pos]; \
                    expERR = FN_ERROR_INVALID_FORMAT; \
                } \
            } else { \
                expPTR = &cbuffer[pos]; \
                expERR = 0; \
            } \
            err = FUNC(&cbuffer[1], &result, NULL, opt);    /* NULL Optional Check */ \
            err = FUNC(&cbuffer[1], &result, &nPTR, opt); \
            if ( err != expERR ){ \
                failMsg = "Test failed. Unexpected error code."; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_u_fail_case); \
            } \
            if ( result != expR ){ \
                failMsg = "Test failed. Wrong result value."; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_u_fail_case); \
            } \
            if ( nPTR != expPTR ){ \
                failMsg = "Test failed. Wrong pointer value."; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_u_fail_case); \
            } \
            if (0) { \
                CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_u_fail_case):    /* LABEL */ \
                printf("===============================================\n" \
                       "%s\n" \
                       "Current Char Code: %d    | Opt: %u\n" \
                       "Input: '%s'\n" \
                       "Input Addr: %" PRIuPTR "\n\n" \
                       "Expected Result: %" PRINTER "\n"\
                       "Returned Result: %" PRINTER "\n\n"\
                       "Expected Pointer: %" PRIuPTR "\n" \
                       "Returned Pointer: %" PRIuPTR "\n\n" \
                       "Expected Error Code: %d\n" \
                       "Returned Error Code: %d\n" \
                       "===============================================\n", \
                       failMsg, \
                       i, opt, \
                       &cbuffer[1], (uintptr_t)&cbuffer[1], \
                       expR, result, \
                       (uintptr_t)expPTR, (uintptr_t)nPTR, \
                       expERR, err); \
                return 1; \
            } \
            if ( !opt ){ \
                opt = FN_PC_NO_INVALID_SKIP; \
                goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2a_u_start_parse); \
            } else { \
                opt = 0; \
            } \
            if ( i == 127 ) break; \
        } \
        if ( pos < MAXLEN ) { \
            expR = (expR * base) + 1; \
            cbuffer[pos] = digits[1]; \
        } \
    } \
    puts ("# Test 2A: Passed.\n"); \
} while(0)

/* Parser C1 Test 2B Signed */
#define MAKE_PC1_CASES_TEST2B_S(FUNC, INTTYPE, MAXDIGIT, PRINTER) do { \
    puts ("# TEST 2B(Signed): Ensure invalid digits are skip properly."); \
    char * failMsg; \
    signed char i; \
    unsigned int opt = 0; \
    char cbuffer[5] = {0}; cbuffer[1] = '!'; \
    char * nPTR, * expPTR; \
    INTTYPE result, expR; \
    int err, expERR; \
    for( i = -128 ;; i++ ){ \
        if ( MAXDIGIT < 10 ){ \
            if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
        } else { \
            if ( i >= 48 && i <= digits[9] ) continue; \
            else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
            else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
        } \
        if ( i == 0 ) continue; \
        cbuffer[0] = *(char *)(&i); \
        CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_start_parse):    /* LABEL */ \
        if ( !opt ) { \
            expPTR = NULL; \
            expERR = 0; \
            expR = 1; \
        } else { \
            expPTR = cbuffer; \
            expERR = FN_ERROR_INVALID_FORMAT; \
            expR = 0; \
        } \
        /* NS */ \
        cbuffer[2] = '1'; cbuffer[3] = 0; \
        err = FUNC(cbuffer, &result, NULL, opt);    /* NULL Optional Check */ \
        err = FUNC(cbuffer, &result, &nPTR, opt); \
        if ( err != expERR ){ \
            failMsg = "Test failed. Unexpected error code at parse without sign."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        if ( result != expR ){ \
            failMsg = "Test failed. Wrong result value at parse without sign."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        if ( nPTR != expPTR ){ \
            failMsg = "Test failed. Wrong pointer value ret at parse without sign."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        /* + */ \
        cbuffer[2] = '+'; cbuffer[3] = '1'; cbuffer[4] = 0; \
        err = FUNC(cbuffer, &result, NULL, opt);    /* NULL Optional Check */ \
        err = FUNC(cbuffer, &result, &nPTR, opt); \
        if ( err != expERR ){ \
            failMsg = "Test failed. Unexpected error code at parse with sign (+)."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        if ( result != expR ){ \
            failMsg = "Test failed. Wrong result value at parse with sign (+)."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        if ( nPTR != expPTR ){ \
            failMsg = "Test failed. Wrong pointer value ret at parse with sign (+)."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        /* - */ \
        cbuffer[2] = '-'; cbuffer[3] = '1'; cbuffer[4] = 0; \
        err = FUNC(cbuffer, &result, NULL, opt);    /* NULL Optional Check */ \
        err = FUNC(cbuffer, &result, &nPTR, opt); \
        if ( err != expERR ){ \
            failMsg = "Test failed. Unexpected error code at parse with sign (-)."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        if ( result != -expR ){ \
            expR = -expR; \
            failMsg = "Test failed. Wrong result value at parse with sign (-)."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        if ( nPTR != expPTR ){ \
            failMsg = "Test failed. Wrong pointer value ret at parse with sign (-)."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case); \
        } \
        if (0) { \
            CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_fail_case):    /* LABEL */ \
            printf("===============================================\n" \
                   "%s\n" \
                   "Current Char Code: %d    | Opt: %u\n" \
                   "Input: '%s'\n" \
                   "Input Addr: %" PRIuPTR "\n\n" \
                   "Expected Result: %" PRINTER "\n"\
                   "Returned Result: %" PRINTER "\n\n"\
                   "Expected Pointer: %" PRIuPTR "\n" \
                   "Returned Pointer: %" PRIuPTR "\n\n" \
                   "Expected Error Code: %d\n" \
                   "Returned Error Code: %d\n" \
                   "===============================================\n", \
                   failMsg, \
                   i, opt, \
                   cbuffer, (uintptr_t)cbuffer, \
                   expR, result, \
                   (uintptr_t)expPTR, (uintptr_t)nPTR, \
                   expERR, err); \
            return 1; \
        } \
        if ( !opt ){ \
            opt = FN_PC_NO_INVALID_SKIP; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_s_start_parse); \
        } else { \
            opt = 0; \
        } \
        if ( i == 127 ) break; \
    } \
    puts ("# Test 2B: Passed.\n"); \
} while(0)

/* Parser C1 Test 2B Unsigned */
#define MAKE_PC1_CASES_TEST2B_U(FUNC, INTTYPE, MAXDIGIT, PRINTER) do { \
    puts ("# TEST 2B(Unsigned): Ensure invalid digits are skip properly."); \
    char * failMsg; \
    signed char i; \
    unsigned int opt = 0; \
    char cbuffer[3] = {0}; cbuffer[1] = '1'; \
    char * nPTR, * expPTR; \
    INTTYPE result, expR; \
    int err, expERR; \
    for( i = -128 ;; i++ ){ \
        if ( MAXDIGIT < 10 ){ \
            if ( i >= 48 && i <= digits[MAXDIGIT] ) continue; \
        } else { \
            if ( i >= 48 && i <= digits[9] ) continue; \
            else if ( i >= digits[10] && i <= digits[MAXDIGIT] ) continue; \
            else if ( i >= digitsA[10] && i <= digitsA[MAXDIGIT] ) continue; \
        } \
        if ( i == 0 ) continue; \
        cbuffer[0] = *(char *)(&i); \
        CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_u_start_parse):    /* LABEL */ \
        if ( !opt ) { \
            expPTR = NULL; \
            expERR = 0; \
            expR = 1; \
        } else { \
            expPTR = cbuffer; \
            expERR = FN_ERROR_INVALID_FORMAT; \
            expR = 0; \
        } \
        err = FUNC(cbuffer, &result, NULL, opt);    /* NULL Optional Check */ \
        err = FUNC(cbuffer, &result, &nPTR, opt); \
        if ( err != expERR ){ \
            failMsg = "Test failed. Unexpected error code."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_u_fail_case); \
        } \
        if ( result != expR ){ \
            failMsg = "Test failed. Wrong result value."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_u_fail_case); \
        } \
        if ( nPTR != expPTR ){ \
            failMsg = "Test failed. Wrong pointer value."; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_u_fail_case); \
        } \
        if (0) { \
            CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_u_fail_case):    /* LABEL */ \
            printf("===============================================\n" \
                   "%s\n" \
                   "Current Char Code: %d    | Opt: %u\n" \
                   "Input: '%s'\n" \
                   "Input Addr: %" PRIuPTR "\n\n" \
                   "Expected Result: %" PRINTER "\n"\
                   "Returned Result: %" PRINTER "\n\n"\
                   "Expected Pointer: %" PRIuPTR "\n" \
                   "Returned Pointer: %" PRIuPTR "\n\n" \
                   "Expected Error Code: %d\n" \
                   "Returned Error Code: %d\n" \
                   "===============================================\n", \
                   failMsg, \
                   i, opt, \
                   cbuffer, (uintptr_t)cbuffer, \
                   expR, result, \
                   (uintptr_t)expPTR, (uintptr_t)nPTR, \
                   expERR, err); \
            return 1; \
        } \
        if ( !opt ){ \
            opt = FN_PC_NO_INVALID_SKIP; \
            goto CONCAT_SRC_TEXT(FUNC, _pc1_cases_test2b_u_start_parse); \
        } else { \
            opt = 0; \
        } \
        if ( i == 127 ) break; \
    } \
    puts ("# Test 2B: Passed.\n"); \
} while(0)
/* ********************END C1 PARSER TEST MACRO********************** */

#endif    /* test.h */
