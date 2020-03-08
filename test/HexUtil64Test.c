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
/* @SEE - TEST_NOTES.h */
#include <stdio.h>
#include "../h/HexUtil64.h"
#include "../testlib/testlib.c"
#include "test.h"

int hexToInt64Test();
int hexToInt64TrueErrorTest();
int hexToUInt64Test();
int hexToUInt64TrueErrorTest();

int hexCompareTest64();
int hexInt64OrSmallerTest();
int hexCompareUTest64();
int hexUInt64OrSmallerTest();

int hexToInt64FPTest();
int hexToUInt64FPTest();
int hexToInt64FNTest();
int hexToUInt64FNTest();

int hexToInt64C1Test();
int hexToUInt64C1Test();

int main(void){
    if ( hexToInt64Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToInt64TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt64Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt64TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( hexCompareTest64() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexInt64OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexCompareUTest64() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexUInt64OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( hexToInt64FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt64FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToInt64FNTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt64FNTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( hexToInt64C1Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt64C1Test() == 1 ) return 1;

    return 0;
}

int hexToInt64Test(){
    #define FUNCCALL hexToInt64
    const static char * testName = "hexToInt64";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int64_t, 15, 16, PRId64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int64_t, 15, 16, FN_ERROR_GENERAL, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64s tCase3[] = {
            (pCase64s){ "7FFFFFFFFFFFFFFD",  9223372036854775805, 0},
            (pCase64s){"+7FFFFFFFFFFFFFFD",  9223372036854775805, 0},
            (pCase64s){"-7FFFFFFFFFFFFFFF", -9223372036854775807, 0},
            (pCase64s){ "7FFFFFFFFFFFFFFF",  9223372036854775807, 0},
            (pCase64s){"+7FFFFFFFFFFFFFFF",  9223372036854775807, 0},
            (pCase64s){"-8000000000000000", -9223372036854775807 - 1, 0},
            (pCase64s){"007FFFFFFFFFFFFFFF", 9223372036854775807, 0},
            (pCase64s){"+000", 0, 0},
            (pCase64s){"-00008000000000000000", -9223372036854775807 - 1, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3) , PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64s tCase4[] = {
            /* Underflow */
            (pCase64s){"-8000000000000001", -576460752303423488, 1},
            (pCase64s){"-80000000000000000", -9223372036854775807 - 1, 1},
            (pCase64s){"-1234567890abcdef0", -1311768467294899695, 1},
            (pCase64s){"-1234567890ABCDEF0", -1311768467294899695, 1},
            /* Overflow */
            (pCase64s){"8000000000000000", 576460752303423488, 1},
            (pCase64s){"7FFFFFFFFFFFFFFF0", 9223372036854775807, 1},
            (pCase64s){"1234567890abcdef0", 1311768467294899695, 1},
            (pCase64s){"1234567890ABCDEF0", 1311768467294899695, 1},
            /* Invalid format */
            (pCase64s){"G123", 0, 1},
            (pCase64s){"-1234567890abcdefg", -1311768467294899695, 1},
            /* Empty string */
            (pCase64s){"", 0, 1}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToInt64TrueErrorTest(){
    #define FUNCCALL hexToInt64TrueError
    const static char * testName = "hexToInt64TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int64_t, 15, 16, PRId64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int64_t, 15, 16, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64s tCase3[] = {
            (pCase64s){ "7FFFFFFFFFFFFFFD",  9223372036854775805, 0},
            (pCase64s){"+7FFFFFFFFFFFFFFD",  9223372036854775805, 0},
            (pCase64s){"-7FFFFFFFFFFFFFFF", -9223372036854775807, 0},
            (pCase64s){ "7FFFFFFFFFFFFFFF",  9223372036854775807, 0},
            (pCase64s){"+7FFFFFFFFFFFFFFF",  9223372036854775807, 0},
            (pCase64s){"-8000000000000000", -9223372036854775807 - 1, 0},
            (pCase64s){"007FFFFFFFFFFFFFFF", 9223372036854775807, 0},
            (pCase64s){"+000", 0, 0},
            (pCase64s){"-00008000000000000000", -9223372036854775807 - 1, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64s tCase4[] = {
            /* Underflow */
            (pCase64s){"-8000000000000001", -576460752303423488, FN_ERROR_UNDERFLOW},
            (pCase64s){"-8000000000000000F", -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pCase64s){"-1234567890abcdeff", -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pCase64s){"-1234567890ABCDEFF1234567890ABCDEF", -1311768467294899695, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pCase64s){"8000000000000000", 576460752303423488, FN_ERROR_OVERFLOW},
            (pCase64s){"7FFFFFFFFFFFFFFFF", 9223372036854775807, FN_ERROR_OVERFLOW},
            (pCase64s){"1234567890abcdeff", 1311768467294899695, FN_ERROR_OVERFLOW},
            (pCase64s){"1234567890ABCDEFF1234567890ABCDEF", 1311768467294899695, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase64s){"G123", 0, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1234567890abcdefg", 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+1234567890abcdefg", 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-1234567890abcdefg", -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"8000000000000000G", 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+8000000000000000G", 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-8000000000000001G", -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"7FFFFFFFFFFFFFFFG", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+7FFFFFFFFFFFFFFFG", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-8000000000000000G", -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"8000000000000010G", 576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+8000000000000010G", 576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-8000000000000010G", -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1234567890abcdef1234567890abcdefG", 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+1234567890abcdef1234567890abcdefG", 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-1234567890abcdef1234567890abcdefG", -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pCase64s){"", 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToUInt64Test(){
    #define FUNCCALL hexToUInt64
    const static char * testName = "hexToUInt64";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint64_t, 15, 16, PRIu64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint64_t, 15, 16, FN_ERROR_GENERAL, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64u tCase3[] = {
            (pCase64u){"FFFFFFFFFFFFFFFE", 18446744073709551614U, 0},
            (pCase64u){"FFFFFFFFFFFFFFFF", 18446744073709551615U, 0},
            (pCase64u){"00FFFFFFFFFFFFFFFF", 18446744073709551615U, 0},
            (pCase64u){"000", 0, 0},
            (pCase64u){"0000FFFFFFFFFFFFFFFF", 18446744073709551615U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64u tCase4[] = {
            /* Overflow */
            (pCase64u){"10000000000000000", 1152921504606846976U, 1},
            (pCase64u){"FFFFFFFFFFFFFFFF0", 18446744073709551615U, 1},
            (pCase64u){"1234567890abcdef0", 1311768467294899695, 1},
            (pCase64u){"1234567890ABCDEF0", 1311768467294899695, 1},
            /* Invalid format */
            (pCase64u){"G213", 0, 1},
            (pCase64u){"1234567890abcdefg", 1311768467294899695, 1},
            (pCase64u){"-0", 0, 1},
            (pCase64u){"+0", 0, 1},
            /* Empty string */
            (pCase64u){"", 0, 1}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToUInt64TrueErrorTest(){
    #define FUNCCALL hexToUInt64TrueError
    const static char * testName = "hexToUInt64TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint64_t, 15, 16, PRIu64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint64_t, 15, 16, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64u tCase3[] = {
            (pCase64u){"FFFFFFFFFFFFFFFE", 18446744073709551614U, 0},
            (pCase64u){"FFFFFFFFFFFFFFFF", 18446744073709551615U, 0},
            (pCase64u){"00FFFFFFFFFFFFFFFF", 18446744073709551615U, 0},
            (pCase64u){"000", 0, 0},
            (pCase64u){"0000FFFFFFFFFFFFFFFF", 18446744073709551615U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64u tCase4[] = {
            /* Overflow */
            (pCase64u){"1000000000000000F", 1152921504606846976U, FN_ERROR_OVERFLOW},
            (pCase64u){"FFFFFFFFFFFFFFFFF", 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pCase64u){"1234567890abcdeff", 1311768467294899695U, FN_ERROR_OVERFLOW},
            (pCase64u){"1234567890ABCDEFF1234567890ABCDEF", 1311768467294899695U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase64u){"G214", 0, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"1234567890abcdefg", 1311768467294899695U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"10000000000000000G", 1152921504606846976U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"FFFFFFFFFFFFFFFFG", 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"10000000000000010G", 1152921504606846977U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"1234567890abcdef1234567890abcdefG", 1311768467294899695U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"-0", 0, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"+0", 0, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pCase64u){"", 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexCompareTest64(){
    #define FUNCCALL hexCompareAsInt64
    const static char * testName = "hexCompareAsInt64";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"7FFFFFFFFFFFFFFF", "-8000000000000000", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"7FFFFFFFFFFFFFFF", "7FFFFFFFFFFFFFFF", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"-8000000000000000", "7FFFFFFFFFFFFFFF", -1, 0}
        };

        MAKE_C_CASES_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.\n");
    } /* END Test 1 */

    { /* START Test 2 */
        puts ("# TEST 2: Comparator errors.");

        cCase tCase2[] = {
            /* Empty string */
            (cCase){"1", "", 0, 1},
            (cCase){"", "1", 0, 1},
            /* Invalid format */
            (cCase){"1!", "1", 0, 1},
            (cCase){"1", "1!", 0, 1},
            /* Underflow/Overflow */
            (cCase){"-8000000000000001", "1", 0, 1},
            (cCase){"1", "8000000000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexInt64OrSmallerTest(){
    #define FUNCCALL hexInt64OrSmaller
    const static char * testName = "hexInt64OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "-1234567890abcdef0", -1},
            (cCaseNE){"!1", "1234567890abcdef0", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "7FFFFFFFFFFFFFFF", -1},
            /* UnderFlow to */
            (cCaseNE){"-1234567890abcdef0", "!1", 1},
            (cCaseNE){"-1234567890abcdef0", "-8000000000000001", 0},
            (cCaseNE){"-1234567890abcdef0", "1234567890abcdef0", -1},
            (cCaseNE){"-1234567890abcdef0", "", -1},
            (cCaseNE){"-1234567890abcdef0", "-8000000000000000", -1},
            /* OverFlow to */
            (cCaseNE){"1234567890abcdef0", "!1", 1},
            (cCaseNE){"1234567890abcdef0", "-1234567890abcdef0", 1},
            (cCaseNE){"1234567890abcdef0", "8000000000000000", 0},
            (cCaseNE){"1234567890abcdef0", "", -1},
            (cCaseNE){"1234567890abcdef0", "7FFFFFFFFFFFFFFF", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "-1234567890abcdef0", 1},
            (cCaseNE){"", "1234567890abcdef0", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "-8000000000000000", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "-1234567890abcdef0", 1},
            (cCaseNE){"1", "1234567890abcdef0", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"-8000000000000000", "7FFFFFFFFFFFFFFF" , -1},
            (cCaseNE){"-8000000000000000", "-8000000000000000" , 0},
            (cCaseNE){"7FFFFFFFFFFFFFFF", "-8000000000000000" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexCompareUTest64(){
    #define FUNCCALL hexCompareAsUInt64
    const static char * testName = "hexCompareAsUInt64";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"FFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFE", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"FFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFF", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"FFFFFFFFFFFFFFFE", "FFFFFFFFFFFFFFFF", -1, 0}
        };

        MAKE_C_CASES_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.\n");
    } /* END Test 1 */

    { /* START Test 2 */
        puts ("# TEST 2: Errors(Return suppose to be 1).");

        cCase tCase2[] = {
            /* Empty string */
            (cCase){"", "1", 0, 1},
            (cCase){"1", "", 0, 1},
            /* Invalid format */
            (cCase){"1!", "1", 0, 1},
            (cCase){"1", "1!", 0, 1},
            /* Underflow/Overflow */
            (cCase){"10000000000000000", "1", 0, 1},
            (cCase){"1", "10000000000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexUInt64OrSmallerTest(){
    #define FUNCCALL hexUInt64OrSmaller
    const static char * testName = "hexUInt64OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "1234567890abcdef0", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "FFFFFFFFFFFFFFFF", -1},
            /* OverFlow to */
            (cCaseNE){"1234567890abcdef0", "!1", 1},
            (cCaseNE){"1234567890abcdef0", "10000000000000000", 0},
            (cCaseNE){"1234567890abcdef0", "", -1},
            (cCaseNE){"1234567890abcdef0", "FFFFFFFFFFFFFFFF", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "1234567890abcdef0", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "FFFFFFFFFFFFFFFF", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "1234567890abcdef0", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"FFFFFFFFFFFFFFFE", "FFFFFFFFFFFFFFFF" , -1},
            (cCaseNE){"FFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFF" , 0},
            (cCaseNE){"FFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFE" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToInt64FPTest(){
    #define FUNCCALL hexToInt64FP
    const static char * testName = "hexToInt64FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_S(FUNCCALL, int64_t, 15, 16, optArray, ALEN(optArray), PRId64);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_S(FUNCCALL, int64_t, 15, 16, 17, PRId64);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_S(FUNCCALL, int64_t, 15, 16, 17, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase64s tCase3[] = {
            (pfpCase64s){"7FFFFFFFFFFFFFFD", 0, 15, FN_OPT_NONE, 9223372036854775805, 0},
            (pfpCase64s){"7FFFFFFFFFFFFFFD", 0, 15, FN_OPT_PFP_ALL, 9223372036854775805, 0},
            (pfpCase64s){"+7FFFFFFFFFFFFFFD", 0, 16, FN_OPT_PFP_ALL, 9223372036854775805, 0},
            (pfpCase64s){"-7FFFFFFFFFFFFFFF", 0, 16, FN_OPT_PFP_ALL, -9223372036854775807, 0},
                       /* 0123456789012345678901234 */
            (pfpCase64s){"7FFFFFFFFFFFFFFF", 0, 15, FN_OPT_NONE, 9223372036854775807, 0},
            (pfpCase64s){"7FFFFFFFFFFFFFFF", 0, 15, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"+7FFFFFFFFFFFFFFF", 0, 16, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"-8000000000000000", 0, 16, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0},
            (pfpCase64s){"007FFFFFFFFFFFFFFF", 0, 17, FN_OPT_NONE, 9223372036854775807, 0},
            (pfpCase64s){"007FFFFFFFFFFFFFFF", 0, 17, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"+000", 0, 3, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase64s){"-00008000000000000000", 0, 20, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase64s tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase64s){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase64s){"  25", 0, 3, FN_PF_IGNORE_LSPACES, 37, 0},
            (pfpCase64s){"   -7FFFFFFFFFFFFFFF", 0, 19, FN_PF_IGNORE_LSPACES, -9223372036854775807, 0},
            (pfpCase64s){"   -8000000000000000", 0, 19, FN_PF_IGNORE_LSPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"    7FFFFFFFFFFFFFFF", 0, 19, FN_PF_IGNORE_LSPACES, 9223372036854775807, 0},
            (pfpCase64s){"   512  ", 0, 7, FN_PF_IGNORE_LSPACES, 1298, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase64s){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase64s){"25  ", 0, 3, FN_PF_IGNORE_TSPACES, 37, 0},
            (pfpCase64s){"-7FFFFFFFFFFFFFFF   ", 0, 19, FN_PF_IGNORE_TSPACES, -9223372036854775807, 0},
            (pfpCase64s){"-8000000000000000   ", 0, 19, FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"7FFFFFFFFFFFFFFF    ", 0, 19, FN_PF_IGNORE_TSPACES, 9223372036854775807, 0},
            (pfpCase64s){" 10000  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase64s){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase64s){" -1 ", 0, 3, FN_PF_IGNORE_SPACES, -1, 0},
            (pfpCase64s){"   -000  ", 0, 8, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase64s){"   -7FFFFFFFFFFFFFFF  ", 0, 21, FN_PF_IGNORE_SPACES, -9223372036854775807, 0},
            (pfpCase64s){"   -8000000000000000  ", 0, 21, FN_PF_IGNORE_SPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"   7FFFFFFFFFFFFFFF   ", 0, 21, FN_PF_IGNORE_SPACES, 9223372036854775807, 0},
            (pfpCase64s){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase64s tCase5[] = {
            /* Underflow */
            (pfpCase64s){"-8000000000000001", 0, 16, FN_OPT_NONE, -576460752303423488, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"-80000000000000000", 0, 17, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"-1234567890ABCDEF0", 0, 17, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfpCase64s){"8000000000000000", 0, 15, FN_OPT_NONE, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfpCase64s){"7FFFFFFFFFFFFFFF0", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"1234567890ABCDEF0", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase64s){"G123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"G123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890ABCDEFG", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+1234567890ABCDEFG", 0, 17, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-1234567890ABCDEFG", 0, 17, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Empty string */
            (pfpCase64s){"", 0, 0, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"", 0, 0, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 5", FUNCCALL, int64_t, tCase5, ALEN(tCase5), PRId64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Parse on error test loop and long check.");

        pfpCase64s tCase6[] = {
            /* Parse On Error */
            (pfpCase64s){"G1234567890ABCDEF", 0, 16, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+G1234567890ABCDEF", 0, 17, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-G1234567890ABCDEF", 0, 17, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890abcdefG", 0, 16, FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+1234567890abcdefG", 0, 17, FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-1234567890abcdefG", 0, 17, FN_PF_PARSE_ON_ERROR,
                         -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"1234567890ABCDEFG", 0, 16, FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+1234567890ABCDEFG", 0, 17, FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-1234567890ABCDEFG", 0, 17, FN_PF_PARSE_ON_ERROR,
                         -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"8000000000000000G", 0, 16, FN_PF_PARSE_ON_ERROR,
                         576460752303423488, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+8000000000000000G", 0, 17, FN_PF_PARSE_ON_ERROR,
                         576460752303423488, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-8000000000000001G", 0, 17, FN_PF_PARSE_ON_ERROR,
                         -576460752303423488, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"7FFFFFFFFFFFFFFFG", 0, 16, FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+7FFFFFFFFFFFFFFFG", 0, 17, FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-8000000000000000G", 0, 17, FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"8000000000000010G", 0, 16, FN_PF_PARSE_ON_ERROR,
                         576460752303423489, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+8000000000000010G", 0, 17, FN_PF_PARSE_ON_ERROR,
                         576460752303423489, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-8000000000000010G", 0, 17, FN_PF_PARSE_ON_ERROR,
                         -576460752303423489, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"1234567890ABCDEF1234567890ABCDEFG", 0, 32, FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+1234567890ABCDEF1234567890ABCDEFG", 0, 33, FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-1234567890ABCDEF1234567890ABCDEFG", 0, 33, FN_PF_PARSE_ON_ERROR,
                         -1311768467294899695, FN_ERROR_UNDERFLOW},
            /* Long Check */
            (pfpCase64s){"G1234567890ABCDEF", 0, 16, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890ABCDEFg", 0, 16, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+1234567890ABCDEFg", 0, 17, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-1234567890ABCDEFg", 0, 17, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890ABCDEFG1234567890ABCDEF", 0, 32, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+1234567890ABCDEFG1234567890ABCDEF", 0, 33, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-1234567890ABCDEFG1234567890ABCDEF", 0, 33, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890ABCDEFG1234567890ABCDEF", 0, 32, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+1234567890ABCDEFG1234567890ABCDEF", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-1234567890ABCDEFG1234567890ABCDEF", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"8000000000000000G8000000000000000", 0, 32, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+8000000000000000G8000000000000000", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-8000000000000010G8000000000000010", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-8000000000000001G8000000000000001", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"8000000000000000F8000000000000000", 0, 32, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         576460752303423488, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+8000000000000000F8000000000000000", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         576460752303423488, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-8000000000000010F8000000000000010", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -576460752303423489, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"-8000000000000001F8000000000000001", 0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -576460752303423488, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"+7FFFFFFFFFFFFFFFF", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-8000000000000000F", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, int64_t, tCase6, ALEN(tCase6), PRId64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase64s tCase7[] = {
            (pfpCase64s){"This number BC614E is parseable.",
                         12, 17, FN_OPT_NONE, 12345678, 0},
            (pfpCase64s){"Number(75BCD15) to array.",
                         7, 13, FN_OPT_PFP_ALL, 123456789, 0},
            (pfpCase64s){"At least this one(-499602D) with sign must pass.",
                         18, 25, FN_OPT_PFP_ALL, -77160493, 0},
            (pfpCase64s){"Important number:+7FFFFFFFFFFFFFFF(INT MAX VALUE)",
                         17, 33, FN_OPT_PFP_ALL, 9223372036854775807, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase64s){"Another one:-8000000000000000(INT64 MIN VALUE)",
                         12, 28, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0},
            (pfpCase64s){"Parse after the seven 12345678B1DCCD5to before the last five",
                         29, 35, FN_OPT_PFP_ALL, 145874125, 0},
            (pfpCase64s){"From next space   -75BCD15    (to prior space)",
                         15, 29, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase64s){"Without any ingore spaces   -499602D2    with spaces parse will fail."
                         "And the segment considered to be overflow, or contain an invalid format"
                         "depends on FN_PF_LONG_CHECK",
                         25, 40, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 7", FUNCCALL, int64_t, tCase7, ALEN(tCase7), PRId64);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfpCase64s tCase8[] = {
            (pfpCase64s){"1", 1, 0, FN_OPT_NONE, 0, FN_ERROR_ILLEGAL_ARGS},
            (pfpCase64s){"1", 0, 1, FN_OPT_PFP_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFP_CASES_FATAL("Test 8", FUNCCALL, int64_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToUInt64FPTest(){
    #define FUNCCALL hexToUInt64FP
    const static char * testName = "hexToUInt64FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_U(FUNCCALL, uint64_t, 15, 16, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_U(FUNCCALL, uint64_t, 15, 16, 17, PRIu64);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_U(FUNCCALL, uint64_t, 15, 16, 17, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        pfpCase64u tCase3[] = {
            (pfpCase64u){"FFFFFFFFFFFFFFFE", 0, 15, FN_OPT_NONE, 18446744073709551614U, 0},
            (pfpCase64u){"FFFFFFFFFFFFFFFE", 0, 15, FN_OPT_PFP_ALL, 18446744073709551614U, 0},
            (pfpCase64u){"FFFFFFFFFFFFFFFF", 0, 15, FN_OPT_NONE, 18446744073709551615U, 0},
            (pfpCase64u){"FFFFFFFFFFFFFFFF", 0, 15, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"FFFFFFFFFFFFFFFF", 0, 15, FN_OPT_NONE, 18446744073709551615U, 0},
            (pfpCase64u){"00FFFFFFFFFFFFFFFF", 0, 17, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"000", 0, 2, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase64u){"0000FFFFFFFFFFFFFFFF", 0, 19, FN_OPT_NONE, 18446744073709551615U, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase64u tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase64u){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase64u){"  25", 0, 3, FN_PF_IGNORE_LSPACES, 37, 0},
            (pfpCase64u){"   FFFFFFFFFFFFFFFE", 0, 18, FN_PF_IGNORE_LSPACES, 18446744073709551614U, 0},
            (pfpCase64u){"   FFFFFFFFFFFFFFFF", 0, 18, FN_PF_IGNORE_LSPACES, 18446744073709551615U, 0},
            (pfpCase64u){"   512  ", 0, 7, FN_PF_IGNORE_LSPACES, 1298, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase64u){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase64u){"25  ", 0, 3, FN_PF_IGNORE_TSPACES, 37, 0},
            (pfpCase64u){"FFFFFFFFFFFFFFFE   ", 0, 18, FN_PF_IGNORE_TSPACES, 18446744073709551614U, 0},
            (pfpCase64u){"FFFFFFFFFFFFFFFF   ", 0, 18, FN_PF_IGNORE_TSPACES, 18446744073709551615U, 0},
            (pfpCase64u){" 10000  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase64u){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase64u){"   000  ", 0, 7, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase64u){"   FFFFFFFFFFFFFFFE  ", 0, 20, FN_PF_IGNORE_SPACES, 18446744073709551614U, 0},
            (pfpCase64u){"   FFFFFFFFFFFFFFFF  ", 0, 20, FN_PF_IGNORE_SPACES, 18446744073709551615U, 0},
            (pfpCase64u){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase64u tCase5[] = {
            /* Overflow */
            (pfpCase64u){"10000000000000000", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64u){"10000000000000010", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64u){"FFFFFFFFFFFFFFFF0", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64u){"1234567890ABCDEF0", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase64u){"G123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"G123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"1234567890ABCDEFG", 0, 16, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64u){"+0", 0, 1, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"-0", 0, 1, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pfpCase64u){"", 0, 0, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"", 0, 0, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 5", FUNCCALL, uint64_t, tCase5, ALEN(tCase5), PRIu64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Parse on error test loop and long check.");

        pfpCase64u tCase6[] = {
            /* Parse On Error */
            (pfpCase64u){"G1000000000000000", 0, 16, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"1234567890abcdefG", 0, 16, FN_PF_PARSE_ON_ERROR, 1311768467294899695U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"1234567890ABCDEFG", 0, 16, FN_PF_PARSE_ON_ERROR, 1311768467294899695U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"10000000000000000G", 0, 17, FN_PF_PARSE_ON_ERROR, 1152921504606846976U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"FFFFFFFFFFFFFFFFG", 0, 16, FN_PF_PARSE_ON_ERROR, 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"10000000000000010G", 0, 17, FN_PF_PARSE_ON_ERROR, 1152921504606846977U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"1234567890ABCDEFG", 0, 16, FN_PF_PARSE_ON_ERROR, 1311768467294899695U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"+1234567890ABCDEF0", 0, 17, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"-1234567890ABCDEF0", 0, 17, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            /* Long Check */
            (pfpCase64u){"G1000000000000000", 0, 16, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"1234567890ABCDEFG1234567890ABCDEF", 0, 32, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"1234567890ABCDEFG1234567890ABCDEF", 0, 32, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1311768467294899695U, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"FFFFFFFFFFFFFFFFF", 0, 16, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         18446744073709551615U, FN_ERROR_OVERFLOW}

        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, uint64_t, tCase6, ALEN(tCase6), PRIu64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase64u tCase7[] = {
            (pfpCase64u){"This 1 is parseable.",
                       5, 5, FN_OPT_NONE, 1, 0},
            (pfpCase64u){"This number BC614E is parseable.",
                       12, 17, FN_OPT_NONE, 12345678U, 0},
            (pfpCase64u){"Number(75BCD15) to array.",
                       7, 13, FN_OPT_PFP_ALL, 123456789U, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase64u){"Important number:+FFFFFFFFFFFFFFFF(UINT64 MAX VALUE), The + is not parsed.",
                       18, 33, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"Parse after the seven 1234573910F4C35to before the last five",
                       28, 35, FN_OPT_PFP_ALL, 957412547U, 0},
            (pfpCase64u){"From next space   499602D2    (to prior space)",
                       15, 29, FN_OPT_PFP_ALL, 1234567890U, 0},
            (pfpCase64u){"Without any ingore spaces   499602D2    with spaces parse will fail."
                       "And the segment considered to be overflow, or contain an invalid format"
                       "depends on FN_PF_LONG_CHECK",
                       25, 39, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 7", FUNCCALL, uint64_t, tCase7, ALEN(tCase7), PRIu64);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfpCase64u tCase8[] = {
            (pfpCase64u){"1", 1, 0, FN_OPT_NONE, 0, FN_ERROR_ILLEGAL_ARGS},
            (pfpCase64u){"1", 0, 1, FN_OPT_PFP_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFP_CASES_FATAL("Test 8", FUNCCALL, uint64_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToInt64FNTest(){
    #define FUNCCALL hexToInt64FN
    const static char * testName = "hexToInt64FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_S(FUNCCALL, int64_t, 15, 16, optArray, ALEN(optArray), PRId64);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_S(FUNCCALL, int64_t, 15, 16, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_S(FUNCCALL, int64_t, 15, 15, PRId64);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase64s tCase4[] = {
            (pfnCase64s){"7FFFFFFFFFFFFFFD", FN_OPT_NONE, 9223372036854775805, 0},
            (pfnCase64s){"7FFFFFFFFFFFFFFD", FN_OPT_PFN_ALL, 9223372036854775805, 0},
            (pfnCase64s){"+7FFFFFFFFFFFFFFD", FN_OPT_PFN_ALL, 9223372036854775805, 0},
            (pfnCase64s){"-7FFFFFFFFFFFFFFF", FN_OPT_PFN_ALL, -9223372036854775807, 0},
            (pfnCase64s){"7FFFFFFFFFFFFFFF", FN_OPT_NONE, 9223372036854775807, 0},
            (pfnCase64s){"7FFFFFFFFFFFFFFF", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"+7FFFFFFFFFFFFFFF", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"-8000000000000000", FN_OPT_PFN_ALL, -9223372036854775807 - 1, 0},
            (pfnCase64s){"007FFFFFFFFFFFFFFF", FN_OPT_NONE, 9223372036854775807, 0},
            (pfnCase64s){"007FFFFFFFFFFFFFFF", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"+000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase64s){"-00008000000000000000", FN_OPT_PFN_ALL, -9223372036854775807 - 1, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase64s tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase64s){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase64s){" 25", FN_PF_IGNORE_LSPACES, 37, 0},
            (pfnCase64s){"   -7FFFFFFFFFFFFFFF", FN_PF_IGNORE_LSPACES, -9223372036854775807, 0},
            (pfnCase64s){"   -8000000000000000", FN_PF_IGNORE_LSPACES, -9223372036854775807 - 1 , 0},
            (pfnCase64s){"    7FFFFFFFFFFFFFFF", FN_PF_IGNORE_LSPACES, 9223372036854775807, 0},
            (pfnCase64s){"   512  ", FN_PF_IGNORE_LSPACES, 1298, FN_ERROR_INVALID_FORMAT},
            /* --> Original Cases */
            (pfnCase64s){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase64s){"25  ", FN_PF_IGNORE_TSPACES, 37, 0},
            (pfnCase64s){"-7FFFFFFFFFFFFFFF   ", FN_PF_IGNORE_TSPACES, -9223372036854775807, 0},
            (pfnCase64s){"-8000000000000000   ", FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, 0},
            (pfnCase64s){"7FFFFFFFFFFFFFFF    ", FN_PF_IGNORE_TSPACES, 9223372036854775807, 0},
            (pfnCase64s){" 10000  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase64s){"8000000000000000  ", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+8000000000000000  ", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-8000000000000010  ", FN_PF_IGNORE_TSPACES, -576460752303423489, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-8000000000000001  ", FN_PF_IGNORE_TSPACES, -576460752303423488, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"1234567890ABCDEFF  ", FN_PF_IGNORE_TSPACES, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890ABCDEFF  ", FN_PF_IGNORE_TSPACES, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890ABCDEFF  ", FN_PF_IGNORE_TSPACES, -1311768467294899695, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64s){"8000000000000000G  ", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+8000000000000000G  ", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-8000000000000010G  ", FN_PF_IGNORE_TSPACES, -576460752303423489, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-8000000000000001G  ", FN_PF_IGNORE_TSPACES, -576460752303423488, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"1234567890ABCDEFG  ", FN_PF_IGNORE_TSPACES, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890ABCDEFG  ", FN_PF_IGNORE_TSPACES, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890ABCDEFG  ", FN_PF_IGNORE_TSPACES, -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"800000000000000G  ", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+800000000000000G  ", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-800000000000000G  ", FN_PF_IGNORE_TSPACES, -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"8000000000000000  0", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+8000000000000000  0", FN_PF_IGNORE_TSPACES, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-8000000000000010  0", FN_PF_IGNORE_TSPACES, -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-8000000000000001  0", FN_PF_IGNORE_TSPACES, -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEF  0", FN_PF_IGNORE_TSPACES, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890ABCDEF  0", FN_PF_IGNORE_TSPACES, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890ABCDEF  0", FN_PF_IGNORE_TSPACES, -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase64s){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase64s){" -1 ", FN_PF_IGNORE_SPACES, -1, 0},
            (pfnCase64s){"   -000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase64s){"   -7FFFFFFFFFFFFFFF  ", FN_PF_IGNORE_SPACES, -9223372036854775807, 0},
            (pfnCase64s){"   -8000000000000000  ", FN_PF_IGNORE_SPACES, -9223372036854775807 - 1, 0},
            (pfnCase64s){"   7FFFFFFFFFFFFFFF   ", FN_PF_IGNORE_SPACES, 9223372036854775807, 0},
            (pfnCase64s){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, int64_t, tCase5, ALEN(tCase5), PRId64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase64s tCase6[] = {
            /* Underflow */
            (pfnCase64s){"-8000000000000001", FN_OPT_NONE, -576460752303423488, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-80000000000000000", FN_OPT_NONE, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1234567890abcdef0", FN_OPT_NONE, -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1234567890abcdefG", FN_OPT_NONE, -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1234567890ABCDEF0", FN_OPT_NONE, -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1234567890ABCDEFG", FN_OPT_NONE, -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-8000000000000000G", FN_OPT_NONE, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-8000000000000010G", FN_OPT_NONE, -576460752303423489, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1234567890ABCDEF1234567890ABCDEFG", FN_OPT_NONE, -1311768467294899695, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfnCase64s){"8000000000000000", FN_OPT_NONE, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfnCase64s){"7FFFFFFFFFFFFFFF0", FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567890abcdef0", FN_OPT_NONE, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567890abcdef!", FN_OPT_NONE, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567890ABCDEF0", FN_OPT_NONE, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567890ABCDEF!", FN_OPT_NONE, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"7FFFFFFFFFFFFFFF!", FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"8000000000000010!", FN_OPT_NONE, 576460752303423489, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567890ABCDEF1234567890ABCDEF!", FN_OPT_NONE, 1311768467294899695, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase64s){"G123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"G123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEFG", FN_OPT_NONE, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890ABCDEFG", FN_OPT_NONE, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890ABCDEFG", FN_OPT_NONE, -1311768467294899695, FN_ERROR_UNDERFLOW},
            /* Empty string */
            (pfnCase64s){"", FN_OPT_NONE, 0, FN_ERROR_EMPTY_STR},
            (pfnCase64s){"", FN_OPT_PFN_ALL, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 6", FUNCCALL, int64_t, tCase6, ALEN(tCase6), PRId64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Long check with and without IGNORE_TSPACES.");

        pfnCase64s tCase7[] = {
            /* With IGNORE_TSPACES */
            /* --> Overflow Check */
            (pfnCase64s){"8000000000000000F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+8000000000000000F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-8000000000000010F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -576460752303423489, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-8000000000000001F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -576460752303423488, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"1234567890ABCDEFF  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890ABCDEFF  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890ABCDEFF  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64s){"80000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+80000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-80000000000000100 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-80000000000000010 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEF0 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890ABCDEF0 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890ABCDEF0 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"800000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+800000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-800000000000001000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-800000000000000100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEF00  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890ABCDEF00  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890ABCDEF00  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase64s){"8000000000000000  ", FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+8000000000000000  ", FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-8000000000000010  ", FN_PF_LONG_CHECK, -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-8000000000000001  ", FN_PF_LONG_CHECK, -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEF  ", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890ABCDEF  ", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890ABCDEF  ", FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"80000000000000000  ", FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+80000000000000000  ", FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-80000000000000100  ", FN_PF_LONG_CHECK, -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-80000000000000010  ", FN_PF_LONG_CHECK, -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEF0  ", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890ABCDEF0  ", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890ABCDEF0  ", FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase64s){"1234567890ABCDEFG", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890ABCDEFG", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890ABCDEFG", FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEFF", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890ABCDEFF", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890ABCDEFF", FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"8000000000000000G", FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+8000000000000000G", FN_PF_LONG_CHECK, 576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-8000000000000010G", FN_PF_LONG_CHECK, -576460752303423489, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-8000000000000001G", FN_PF_LONG_CHECK, -576460752303423488, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEF1234567890ABCDEFg", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890ABCDEF1234567890ABCDEFg", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890ABCDEF1234567890ABCDEFg", FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890ABCDEF1234567890ABCDEF0", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890ABCDEF1234567890ABCDEF0", FN_PF_LONG_CHECK, 1311768467294899695, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890ABCDEF1234567890ABCDEF0", FN_PF_LONG_CHECK, -1311768467294899695, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"7FFFFFFFFFFFFFFF7FFFFFFFFFFFFFFFG", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+7FFFFFFFFFFFFFFF7FFFFFFFFFFFFFFFG", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-80000000000000008000000000000000G", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"7FFFFFFFFFFFFFFF7FFFFFFFFFFFFFFF0", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+7FFFFFFFFFFFFFFF7FFFFFFFFFFFFFFF0", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-800000000000000080000000000000000", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFN_CASES_LOOP("Test 7", FUNCCALL, int64_t, tCase7, ALEN(tCase7), PRId64);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfnCase64s tCase8[] = {
            (pfnCase64s){"1", FN_OPT_PFN_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFN_CASES_FATAL("Test 8", FUNCCALL, int64_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToUInt64FNTest(){
    #define FUNCCALL hexToUInt64FN
    const static char * testName = "hexToUInt64FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_U(FUNCCALL, uint64_t, 15, 16, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_U(FUNCCALL, uint64_t, 15, 16, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_U(FUNCCALL, uint64_t, 15, 15, PRIu64);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase64u tCase4[] = {
            (pfnCase64u){"FFFFFFFFFFFFFFFE", FN_OPT_NONE, 18446744073709551614U, 0},
            (pfnCase64u){"FFFFFFFFFFFFFFFE", FN_OPT_PFN_ALL, 18446744073709551614U, 0},
            (pfnCase64u){"FFFFFFFFFFFFFFFF", FN_OPT_NONE, 18446744073709551615U, 0},
            (pfnCase64u){"FFFFFFFFFFFFFFFF", FN_OPT_PFN_ALL, 18446744073709551615U, 0},
            (pfnCase64u){"00FFFFFFFFFFFFFFFF", FN_OPT_NONE, 18446744073709551615U, 0},
            (pfnCase64u){"00FFFFFFFFFFFFFFFF", FN_OPT_PFN_ALL, 18446744073709551615U, 0},
            (pfnCase64u){"000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase64u){"0000FFFFFFFFFFFFFFFF", FN_OPT_PFN_ALL, 18446744073709551615U, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase64u tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase64u){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase64u){"  25", FN_PF_IGNORE_LSPACES, 37, 0},
            (pfnCase64u){"   FFFFFFFFFFFFFFFE", FN_PF_IGNORE_LSPACES, 18446744073709551614U, 0},
            (pfnCase64u){"   FFFFFFFFFFFFFFFF", FN_PF_IGNORE_LSPACES, 18446744073709551615U, 0},
            (pfnCase64u){"   512  ", FN_PF_IGNORE_LSPACES, 1298, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase64u){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase64u){"25  ", FN_PF_IGNORE_TSPACES, 37, 0},
            (pfnCase64u){"FFFFFFFFFFFFFFFE   ", FN_PF_IGNORE_TSPACES, 18446744073709551614U, 0},
            (pfnCase64u){"FFFFFFFFFFFFFFFF   ", FN_PF_IGNORE_TSPACES, 18446744073709551615U, 0},
            (pfnCase64u){" 10000  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase64u){"FFFFFFFFFFFFFFFFF  ", FN_PF_IGNORE_TSPACES, 18446744073709551615U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64u){"FFFFFFFFFFFFFFFFG  ", FN_PF_IGNORE_TSPACES, 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"FFFFFFFFFFFFFFFF  0", FN_PF_IGNORE_TSPACES, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase64u){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase64u){"   000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase64u){"   FFFFFFFFFFFFFFFE  ", FN_PF_IGNORE_SPACES, 18446744073709551614U, 0},
            (pfnCase64u){"   FFFFFFFFFFFFFFFF  ", FN_PF_IGNORE_SPACES, 18446744073709551615U, 0},
            (pfnCase64u){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, uint64_t, tCase5, ALEN(tCase5), PRIu64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase64u tCase6[] = {
            /* Overflow */
            (pfnCase64u){"10000000000000000", FN_OPT_NONE, 1152921504606846976U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"10000000000000010", FN_OPT_NONE, 1152921504606846977U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"FFFFFFFFFFFFFFFF0", FN_OPT_NONE, 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"1234567890abcdef0", FN_OPT_NONE, 1311768467294899695U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"1234567890ABCDEF0", FN_OPT_NONE, 1311768467294899695U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase64u){"G123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"G123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567890ABCDEFG", FN_OPT_NONE, 1311768467294899695U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"+0", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"-0", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pfnCase64u){"", FN_OPT_NONE, 0, FN_ERROR_EMPTY_STR},
            (pfnCase64u){"", FN_OPT_PFN_ALL, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 6", FUNCCALL, uint64_t, tCase6, ALEN(tCase6), PRIu64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Long check with and without IGNORE_TSPACES.");

        pfnCase64u tCase7[] = {
            /* With IGNORE_TSPACES */
            /* --> Overflow Check */
            (pfnCase64u){"FFFFFFFFFFFFFFFFF  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64u){"FFFFFFFFFFFFFFFF 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"FFFFFFFFFFFFFFFF0  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase64u){"FFFFFFFFFFFFFFFF  ", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"FFFFFFFFFFFFFFFFFG  ", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"FFFFFFFFFFFFFFFFFFG  ", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase64u){"1234567890ABCDEFG  ", FN_PF_LONG_CHECK, 1311768467294899695U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567890ABCDEFF  ", FN_PF_LONG_CHECK, 1311768467294899695U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567890ABCDEF1234567890ABCDEFG", FN_PF_LONG_CHECK, 1311768467294899695U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567890ABCDEF1234567890ABCDEF0", FN_PF_LONG_CHECK, 1311768467294899695U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFG", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_OVERFLOW}
        };

        MAKE_PFN_CASES_LOOP("Test 7", FUNCCALL, uint64_t, tCase7, ALEN(tCase7), PRIu64);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfnCase64u tCase8[] = {
            (pfnCase64u){"1", FN_OPT_PFN_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFN_CASES_FATAL("Test 8", FUNCCALL, uint64_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToInt64C1Test(){
    #define FUNCCALL hexToInt64C1
    const static char * testName = "hexToInt64C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_S(FUNCCALL, int64_t, 15, 16, optArray, ALEN(optArray), PRId64);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_S( FUNCCALL, int64_t, 15, 16, PRId64);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_S( FUNCCALL, int64_t, 15, PRId64);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");

        pc1Case64s tCase3[] = {
            /* a */
            (pc1Case64s){"7FFFFFFFFFFFFFFD", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+7FFFFFFFFFFFFFFD", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+7FFFFFFFFFFFFFFD", FN_OPT_PC1_ALL, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"-7FFFFFFFFFFFFFFF", FN_OPT_NONE, {-9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"-7FFFFFFFFFFFFFFF", FN_OPT_PC1_ALL, {-9223372036854775807}, {0}, {-1}, 1},
            /* b */
            (pc1Case64s){"7FFFFFFFFFFFFFFF", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+7FFFFFFFFFFFFFFF", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+7FFFFFFFFFFFFFFF", FN_OPT_PC1_ALL, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"-8000000000000000", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-8000000000000000", FN_OPT_PC1_ALL, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            /* c */
            (pc1Case64s){"007FFFFFFFFFFFFFFF", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"007FFFFFFFFFFFFFFF", FN_OPT_PC1_ALL, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case64s){"+000", FN_OPT_PC1_ALL, {0}, {0}, {-1}, 1},
            (pc1Case64s){"-00008000000000000000", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-00008000000000000000", FN_OPT_PC1_ALL, {-9223372036854775807 - 1}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case64s tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case64s){"-+7FFFFFFFFFFFFFFD", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+-7FFFFFFFFFFFFFFD", FN_OPT_NONE, {-9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"g7FFFFFFFFFFFFFFDg", FN_OPT_NONE, {9223372036854775805}, {0}, {17}, 1},
            (pc1Case64s){"g+7FFFFFFFFFFFFFFDg", FN_OPT_NONE, {9223372036854775805}, {0}, {18}, 1},
            (pc1Case64s){"g-7FFFFFFFFFFFFFFDg", FN_OPT_NONE, {-9223372036854775805}, {0}, {18}, 1},
            (pc1Case64s){"G@#$%^&7FFFFFFFFFFFFFFDG@", FN_OPT_NONE, {9223372036854775805}, {0}, {23}, 1},
            (pc1Case64s){"G@#$%^&+7FFFFFFFFFFFFFFDG@", FN_OPT_NONE, {9223372036854775805}, {0}, {24}, 1},
            (pc1Case64s){"G@#$%^&-7FFFFFFFFFFFFFFDG@", FN_OPT_NONE, {-9223372036854775805}, {0}, {24}, 1},
            (pc1Case64s){"G@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case64s){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case64s){"G7FFFFFFFFFFFFFFD", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64s){"7FFFFFFFFFFFFFFDg", FN_PC_NO_INVALID_SKIP, {9223372036854775805}, {0}, {16}, 1},
            (pc1Case64s){"+7FFFFFFFFFFFFFFDG", FN_PC_NO_INVALID_SKIP, {9223372036854775805}, {0}, {17}, 1},
            (pc1Case64s){"-7FFFFFFFFFFFFFFDG", FN_PC_NO_INVALID_SKIP, {-9223372036854775805}, {0}, {17}, 1},
            (pc1Case64s){"G%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64s){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case64s tCase5[] = {
            /* Overflow default */
            /* --> Underflow */
            (pc1Case64s){"-8000000000000001", FN_OPT_NONE, {-576460752303423488}, {0}, {16}, 1},
            (pc1Case64s){"-8000000000000001F", FN_OPT_NONE, {-576460752303423488}, {0}, {16}, 1},
            (pc1Case64s){"-8000000000000000F", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {17}, 1},
            (pc1Case64s){"-8000000000000010", FN_OPT_NONE, {-576460752303423489}, {0}, {16}, 1},
            (pc1Case64s){"-8000000000000010F", FN_OPT_NONE, {-576460752303423489}, {0}, {16}, 1},
            (pc1Case64s){"-1234567890abcdeff", FN_OPT_NONE, {-1311768467294899695}, {0}, {17}, 1},
            (pc1Case64s){"-1234567890abcdeff1234567890abcdef", FN_OPT_NONE, {-1311768467294899695}, {0}, {17}, 1},
            (pc1Case64s){"-1234567890ABCDEFF", FN_OPT_NONE, {-1311768467294899695}, {0}, {17}, 1},
            (pc1Case64s){"-1234567890ABCDEFF1234567890ABCDEF", FN_OPT_NONE, {-1311768467294899695}, {0}, {17}, 1},
            /* --> Overflow */
            (pc1Case64s){"8000000000000000", FN_OPT_NONE, {576460752303423488}, {0}, {15}, 1},
            (pc1Case64s){"8000000000000000F", FN_OPT_NONE, {576460752303423488}, {0}, {15}, 1},
            (pc1Case64s){"7FFFFFFFFFFFFFFFF", FN_OPT_NONE, {9223372036854775807}, {0}, {16}, 1},
            (pc1Case64s){"8000000000000010", FN_OPT_NONE, {576460752303423489}, {0}, {15}, 1},
            (pc1Case64s){"8000000000000010F", FN_OPT_NONE, {576460752303423489}, {0}, {15}, 1},
            (pc1Case64s){"1234567890abcdeff", FN_OPT_NONE, {1311768467294899695}, {0}, {16}, 1},
            (pc1Case64s){"1234567890abcdeff1234567890abcdef", FN_OPT_NONE, {1311768467294899695}, {0}, {16}, 1},
            (pc1Case64s){"1234567890ABCDEFF", FN_OPT_NONE, {1311768467294899695}, {0}, {16}, 1},
            (pc1Case64s){"1234567890ABCDEFF1234567890ABCDEF", FN_OPT_NONE, {1311768467294899695}, {0}, {16}, 1},
            /* OVERFLOW_ERROR opt */
            /* --> Underflow */
            (pc1Case64s){"-8000000000000001", FN_PC_OVERFLOW_ERROR, {-576460752303423488}, {FN_ERROR_UNDERFLOW}, {16}, 1},
            (pc1Case64s){"-8000000000000001F", FN_PC_OVERFLOW_ERROR, {-576460752303423488}, {FN_ERROR_UNDERFLOW}, {16}, 1},
            (pc1Case64s){"-8000000000000000F", FN_PC_OVERFLOW_ERROR, {-9223372036854775807 - 1}, {FN_ERROR_UNDERFLOW}, {17}, 1},
            (pc1Case64s){"-8000000000000010", FN_PC_OVERFLOW_ERROR, {-576460752303423489}, {FN_ERROR_UNDERFLOW}, {16}, 1},
            (pc1Case64s){"-8000000000000010F", FN_PC_OVERFLOW_ERROR, {-576460752303423489}, {FN_ERROR_UNDERFLOW}, {16}, 1},
            (pc1Case64s){"-1234567890abcdeff", FN_PC_OVERFLOW_ERROR, {-1311768467294899695}, {FN_ERROR_UNDERFLOW}, {17}, 1},
            (pc1Case64s){"-1234567890abcdeff1234567890abcdef", FN_PC_OVERFLOW_ERROR, {-1311768467294899695}, {FN_ERROR_UNDERFLOW}, {17}, 1},
            (pc1Case64s){"-1234567890ABCDEFF", FN_PC_OVERFLOW_ERROR, {-1311768467294899695}, {FN_ERROR_UNDERFLOW}, {17}, 1},
            (pc1Case64s){"-1234567890ABCDEFF1234567890ABCDEF", FN_PC_OVERFLOW_ERROR, {-1311768467294899695}, {FN_ERROR_UNDERFLOW}, {17}, 1},
            /* --> Overflow */
            (pc1Case64s){"8000000000000000", FN_PC_OVERFLOW_ERROR, {576460752303423488}, {FN_ERROR_OVERFLOW}, {15}, 1},
            (pc1Case64s){"8000000000000000F", FN_PC_OVERFLOW_ERROR, {576460752303423488}, {FN_ERROR_OVERFLOW}, {15}, 1},
            (pc1Case64s){"7FFFFFFFFFFFFFFFF", FN_PC_OVERFLOW_ERROR, {9223372036854775807}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64s){"8000000000000010", FN_PC_OVERFLOW_ERROR, {576460752303423489}, {FN_ERROR_OVERFLOW}, {15}, 1},
            (pc1Case64s){"8000000000000010F", FN_PC_OVERFLOW_ERROR, {576460752303423489}, {FN_ERROR_OVERFLOW}, {15}, 1},
            (pc1Case64s){"1234567890abcdeff", FN_PC_OVERFLOW_ERROR, {1311768467294899695}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64s){"1234567890abcdeff1234567890abcdef", FN_PC_OVERFLOW_ERROR, {1311768467294899695}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64s){"1234567890ABCDEFF", FN_PC_OVERFLOW_ERROR, {1311768467294899695}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64s){"1234567890ABCDEFF1234567890ABCDEF", FN_PC_OVERFLOW_ERROR, {1311768467294899695}, {FN_ERROR_OVERFLOW}, {16}, 1},
            /* OVERFLOW SKIP opt */
            /* --> Underflow */
            (pc1Case64s){"-8000000000000001", FN_PC_OVERFLOW_SKIP, {-576460752303423488}, {0}, {-1}, 1},
            (pc1Case64s){"-8000000000000001F", FN_PC_OVERFLOW_SKIP, {-576460752303423488}, {0}, {-1}, 1},
            (pc1Case64s){"-8000000000000000F", FN_PC_OVERFLOW_SKIP, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-8000000000000010", FN_PC_OVERFLOW_SKIP, {-576460752303423489}, {0}, {-1}, 1},
            (pc1Case64s){"-8000000000000010F", FN_PC_OVERFLOW_SKIP, {-576460752303423489}, {0}, {-1}, 1},
            (pc1Case64s){"-1234567890abcdeff", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"-1234567890abcdeff1234567890abcdef", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"-1234567890ABCDEFF", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"-1234567890ABCDEFF1234567890ABCDEF", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"-8000000000000001G", FN_PC_OVERFLOW_SKIP, {-576460752303423488}, {0}, {17}, 1},
            (pc1Case64s){"-80000000000000010G", FN_PC_OVERFLOW_SKIP, {-576460752303423488}, {0}, {18}, 1},
            (pc1Case64s){"-80000000000000000G", FN_PC_OVERFLOW_SKIP, {-9223372036854775807 - 1}, {0}, {18}, 1},
            (pc1Case64s){"-8000000000000010G", FN_PC_OVERFLOW_SKIP, {-576460752303423489}, {0}, {17}, 1},
            (pc1Case64s){"-80000000000000100G", FN_PC_OVERFLOW_SKIP, {-576460752303423489}, {0}, {18}, 1},
            (pc1Case64s){"-1234567890abcdef0G", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {18}, 1},
            (pc1Case64s){"-1234567890abcdef1234567890abcdef0G", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {34}, 1},
            (pc1Case64s){"-1234567890ABCDEF0G", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {18}, 1},
            (pc1Case64s){"-1234567890ABCDEF1234567890ABCDEF0G", FN_PC_OVERFLOW_SKIP, {-1311768467294899695}, {0}, {34}, 1},
            /* --> Overflow */
            (pc1Case64s){"8000000000000000", FN_PC_OVERFLOW_SKIP, {576460752303423488}, {0}, {-1}, 1},
            (pc1Case64s){"8000000000000000F", FN_PC_OVERFLOW_SKIP, {576460752303423488}, {0}, {-1}, 1},
            (pc1Case64s){"7FFFFFFFFFFFFFFFF", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"8000000000000010", FN_PC_OVERFLOW_SKIP, {576460752303423489}, {0}, {-1}, 1},
            (pc1Case64s){"8000000000000010F", FN_PC_OVERFLOW_SKIP, {576460752303423489}, {0}, {-1}, 1},
            (pc1Case64s){"1234567890abcdeff", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"1234567890abcdeff1234567890abcdef", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"1234567890ABCDEFF", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"1234567890ABCDEFF1234567890ABCDEF", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {-1}, 1},
            (pc1Case64s){"8000000000000000G", FN_PC_OVERFLOW_SKIP, {576460752303423488}, {0}, {16}, 1},
            (pc1Case64s){"80000000000000000G", FN_PC_OVERFLOW_SKIP, {576460752303423488}, {0}, {17}, 1},
            (pc1Case64s){"7FFFFFFFFFFFFFFF0G", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {17}, 1},
            (pc1Case64s){"8000000000000010G", FN_PC_OVERFLOW_SKIP, {576460752303423489}, {0}, {16}, 1},
            (pc1Case64s){"80000000000000100G", FN_PC_OVERFLOW_SKIP, {576460752303423489}, {0}, {17}, 1},
            (pc1Case64s){"1234567890abcdef0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {17}, 1},
            (pc1Case64s){"1234567890abcdef1234567890abcdef0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {33}, 1},
            (pc1Case64s){"1234567890ABCDEF0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {17}, 1},
            (pc1Case64s){"1234567890ABCDEF1234567890ABCDEF0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695}, {0}, {33}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case64s){"1234567890ABCDEFG", FN_PC_OVERFLOW_ERROR, {1311768467294899695}, {0}, {16}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, int64_t, tCase5, ALEN(tCase5), PRId64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case64s tCase6[] = {
            (pc1Case64s){"7B +1DE -9D $78 $-78",
                         FN_OPT_NONE,
                         {123, 478, -157, 120, -120},
                         {0,0,0,0,0},
                         {2,7,11,15,-1},
                         5},
                       /* 0         10        20        30        40         */
                       /* 01234567890123456789012345678901234567890123456789 */
            (pc1Case64s){"03B +1234567890ABCDEF012 -8000000000000000012 $78 $-26E064",
                         FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {59, 1311768467294899695, -9223372036854775807 - 1, 120, -2547812},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_UNDERFLOW, 0, 0},
                         {3,24,45,49,-1},
                         5}
        };

        MAKE_PC1_CASES_LOOP("Test 6", FUNCCALL, int64_t, tCase6, ALEN(tCase6), PRId64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Fatal error test.");

        pc1Case64s tCase7[] = {
            (pc1Case64s){"1", ~((unsigned int)FN_OPT_PC1_ALL) , {1}, {0}, {0}, 1}
        };

        MAKE_PC1_CASES_FATAL("Test 7", FUNCCALL, int64_t, tCase7, ALEN(tCase7));
        puts ("# Test 7: Passed.");
    } /* END Test 7 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToUInt64C1Test(){
    #define FUNCCALL hexToUInt64C1
    const static char * testName = "hexToUInt64C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_U(FUNCCALL, uint64_t, 15, 16, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_U( FUNCCALL, uint64_t, 15, 16, PRIu64);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_U( FUNCCALL, uint64_t, 15, PRIu64);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");

        pc1Case64u tCase3[] = {
            /* a */
            (pc1Case64u){"FFFFFFFFFFFFFFFE", FN_OPT_NONE, {18446744073709551614U}, {0}, {-1}, 1},
            (pc1Case64u){"FFFFFFFFFFFFFFFE", FN_OPT_PC1_ALL, {18446744073709551614U}, {0}, {-1}, 1},
            /* b */
            (pc1Case64u){"FFFFFFFFFFFFFFFF", FN_OPT_NONE, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"FFFFFFFFFFFFFFFF", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1},
            /* c */
            (pc1Case64u){"00FFFFFFFFFFFFFFFF", FN_OPT_NONE, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"00FFFFFFFFFFFFFFFF", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case64u){"0000FFFFFFFFFFFFFFFF", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case64u tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case64u){"-1", FN_OPT_NONE, {1}, {0}, {-1}, 1},
            (pc1Case64u){"gFFFFFFFFFFFFFFFEg", FN_OPT_NONE, {18446744073709551614U}, {0}, {17}, 1},
            (pc1Case64u){"G@#$%^&FFFFFFFFFFFFFFFEG@", FN_OPT_NONE, {18446744073709551614U}, {0}, {23}, 1},
            (pc1Case64u){"G@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case64u){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case64u){"+0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"-0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"gFFFFFFFFFFFFFFFE", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"FFFFFFFFFFFFFFFEg", FN_PC_NO_INVALID_SKIP, {18446744073709551614U}, {0}, {16}, 1},
            (pc1Case64u){"G%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case64u tCase5[] = {
            /* Overflow default */
            (pc1Case64u){"1000000000000000F", FN_OPT_NONE, {1152921504606846976U}, {0}, {16}, 1},
            (pc1Case64u){"1000000000000000F0", FN_OPT_NONE, {1152921504606846976U}, {0}, {16}, 1},
            (pc1Case64u){"FFFFFFFFFFFFFFFFF", FN_OPT_NONE, {18446744073709551615U}, {0}, {16}, 1},
            (pc1Case64u){"1000000000000001F", FN_OPT_NONE, {1152921504606846977U}, {0}, {16}, 1},
            (pc1Case64u){"1000000000000001F0", FN_OPT_NONE, {1152921504606846977U}, {0}, {16}, 1},
            (pc1Case64u){"1234567890abcdeff", FN_OPT_NONE, {1311768467294899695U}, {0}, {16}, 1},
            (pc1Case64u){"1234567890abcdeff1234567890abcdef", FN_OPT_NONE, {1311768467294899695U}, {0}, {16}, 1},
            (pc1Case64u){"1234567890ABCDEFF", FN_OPT_NONE, {1311768467294899695U}, {0}, {16}, 1},
            (pc1Case64u){"1234567890ABCDEFF1234567890ABCDEF", FN_OPT_NONE, {1311768467294899695U}, {0}, {16}, 1},
            /* OVERFLOW_ERROR opt */
            (pc1Case64u){"1000000000000000F", FN_PC_OVERFLOW_ERROR, {1152921504606846976U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"1000000000000000F0", FN_PC_OVERFLOW_ERROR, {1152921504606846976U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"FFFFFFFFFFFFFFFFF", FN_PC_OVERFLOW_ERROR, {18446744073709551615U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"1000000000000001F", FN_PC_OVERFLOW_ERROR, {1152921504606846977U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"1000000000000001F0", FN_PC_OVERFLOW_ERROR, {1152921504606846977U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"1234567890abcdeff", FN_PC_OVERFLOW_ERROR, {1311768467294899695U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"1234567890abcdeff1234567890abcdef", FN_PC_OVERFLOW_ERROR, {1311768467294899695U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"1234567890ABCDEFF", FN_PC_OVERFLOW_ERROR, {1311768467294899695U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            (pc1Case64u){"1234567890ABCDEFF1234567890ABCDEF", FN_PC_OVERFLOW_ERROR, {1311768467294899695U}, {FN_ERROR_OVERFLOW}, {16}, 1},
            /* OVERFLOW SKIP opt */
            (pc1Case64u){"1000000000000000F", FN_PC_OVERFLOW_SKIP, {1152921504606846976U}, {0}, {-1}, 1},
            (pc1Case64u){"1000000000000000F0", FN_PC_OVERFLOW_SKIP, {1152921504606846976U}, {0}, {-1}, 1},
            (pc1Case64u){"FFFFFFFFFFFFFFFFF", FN_PC_OVERFLOW_SKIP, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"1000000000000001F", FN_PC_OVERFLOW_SKIP, {1152921504606846977U}, {0}, {-1}, 1},
            (pc1Case64u){"1000000000000001F0", FN_PC_OVERFLOW_SKIP, {1152921504606846977U}, {0}, {-1}, 1},
            (pc1Case64u){"1234567890abcdeff", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {-1}, 1},
            (pc1Case64u){"1234567890abcdeff1234567890abcdef", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {-1}, 1},
            (pc1Case64u){"1234567890ABCDEFF", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {-1}, 1},
            (pc1Case64u){"1234567890ABCDEFF1234567890ABCDEF", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {-1}, 1},
            (pc1Case64u){"10000000000000000G", FN_PC_OVERFLOW_SKIP, {1152921504606846976U}, {0}, {17}, 1},
            (pc1Case64u){"100000000000000000G", FN_PC_OVERFLOW_SKIP, {1152921504606846976U}, {0}, {18}, 1},
            (pc1Case64u){"FFFFFFFFFFFFFFFF0G", FN_PC_OVERFLOW_SKIP, {18446744073709551615U}, {0}, {17}, 1},
            (pc1Case64u){"10000000000000010G", FN_PC_OVERFLOW_SKIP, {1152921504606846977U}, {0}, {17}, 1},
            (pc1Case64u){"100000000000000100G", FN_PC_OVERFLOW_SKIP, {1152921504606846977U}, {0}, {18}, 1},
            (pc1Case64u){"1234567890abcdef0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {17}, 1},
            (pc1Case64u){"1234567890abcdef1234567890abcdef0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {33}, 1},
            (pc1Case64u){"1234567890ABCDEF0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {17}, 1},
            (pc1Case64u){"1234567890ABCDEF1234567890ABCDEF0G", FN_PC_OVERFLOW_SKIP, {1311768467294899695U}, {0}, {33}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case64u){"FFFFFFFFFFFFFFFFG", FN_PC_OVERFLOW_ERROR, {18446744073709551615U}, {0}, {16}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, uint64_t, tCase5, ALEN(tCase5), PRIu64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case64u tCase6[] = {
            (pc1Case64u){"7B 169D 130A $C46535FF & $D5930", FN_OPT_NONE,
                         {123U, 5789U, 4874U, 3294967295U, 874800U},
                         {0,0,0,0,0},
                         {2,7,12,22,-1},
                         5},
                       /*           10        20        30        40        50         */
                       /* 012345678901234567890123456789012345678901234567890123456789 */
            (pc1Case64u){"7B FFFFFFFFFFFFFFFF01 1234567890ABCDEF01 $C46535FF & $D5930", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {123U, 18446744073709551615U, 1311768467294899695U, 3294967295U, 874800U},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_OVERFLOW, 0, 0},
                         {2,21,40,50,-1},
                         5}
        };

        MAKE_PC1_CASES_LOOP("Test 6", FUNCCALL, uint64_t, tCase6, ALEN(tCase6), PRIu64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Fatal error test.");

        pc1Case64u tCase7[] = {
            (pc1Case64u){"1", ~((unsigned int)FN_OPT_PC1_ALL) , {1}, {0}, {0}, 1}
        };

        MAKE_PC1_CASES_FATAL("Test 7", FUNCCALL, uint64_t, tCase7, ALEN(tCase7));
        puts ("# Test 7: Passed.");
    } /* END Test 7 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}
