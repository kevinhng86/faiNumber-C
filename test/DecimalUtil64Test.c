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
#include "../h/DecimalUtil64.h"
#include "../testlib/testlib.c"
#include "test.h"

int decToInt64Test();
int decToInt64TrueErrorTest();
int decToUInt64Test();
int decToUInt64TrueErrorTest();

int decCompareTest64();
int decInt64OrSmallerTest();
int decCompareUTest64();
int decUInt64OrSmallerTest();

int decToInt64FPTest();
int decToUInt64FPTest();
int decToInt64FNTest();
int decToUInt64FNTest();

int decToInt64C1Test();
int decToUInt64C1Test();

int main(void){
    if ( decToInt64Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToInt64TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt64Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt64TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( decCompareTest64() == 1 ) return 1;
    puts("\n\n\n");
    if ( decInt64OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decCompareUTest64() == 1 ) return 1;
    puts("\n\n\n");
    if ( decUInt64OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( decToInt64FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt64FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToInt64FNTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt64FNTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( decToInt64C1Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt64C1Test() == 1 ) return 1;

    return 0;
}

int decToInt64Test(){
    #define FUNCCALL decToInt64
    const static char * testName = "decToInt64";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int64_t, 9, 19, PRId64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int64_t, 9, 19, FN_ERROR_GENERAL, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64s tCase3[] = {
            (pCase64s){ "9223372036854775805",  9223372036854775805, 0},
            (pCase64s){"+9223372036854775805",  9223372036854775805, 0},
            (pCase64s){"-9223372036854775807", -9223372036854775807, 0},
            (pCase64s){ "9223372036854775807",  9223372036854775807, 0},
            (pCase64s){"+9223372036854775807",  9223372036854775807, 0},
            (pCase64s){"-9223372036854775808", -9223372036854775807 - 1, 0},
            (pCase64s){"009223372036854775807", 9223372036854775807, 0},
            (pCase64s){"+000", 0, 0},
            (pCase64s){"-00009223372036854775808", -9223372036854775807 - 1, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3) , PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64s tCase4[] = {
            /* Underflow */
            (pCase64s){"-9223372036854775809", -922337203685477580, 1},
            (pCase64s){"-92233720368547758080", -9223372036854775807 - 1, 1},
            (pCase64s){"-12345678901234567890", -1234567890123456789, 1},
            /* Overflow */
            (pCase64s){"9223372036854775808", 922337203685477580, 1},
            (pCase64s){"92233720368547758070", 9223372036854775807, 1},
            (pCase64s){"12345678901234567890", 1234567890123456789, 1},
            /* Invalid format */
            (pCase64s){":123", 0, 1},
            (pCase64s){"-1234567890123456789:", -1234567890123456789, 1},
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

int decToInt64TrueErrorTest(){
    #define FUNCCALL decToInt64TrueError
    const static char * testName = "decToInt64TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int64_t, 9, 19, PRId64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int64_t, 9, 19, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64s tCase3[] = {
            (pCase64s){ "9223372036854775805",  9223372036854775805, 0},
            (pCase64s){"+9223372036854775805",  9223372036854775805, 0},
            (pCase64s){"-9223372036854775807", -9223372036854775807, 0},
            (pCase64s){ "9223372036854775807",  9223372036854775807, 0},
            (pCase64s){"+9223372036854775807",  9223372036854775807, 0},
            (pCase64s){"-9223372036854775808", -9223372036854775807 - 1, 0},
            (pCase64s){"009223372036854775807", 9223372036854775807, 0},
            (pCase64s){"+000", 0, 0},
            (pCase64s){"-00009223372036854775808", -9223372036854775807 - 1, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64s tCase4[] = {
            /* Underflow */
            (pCase64s){"-9223372036854775809", -922337203685477580, FN_ERROR_UNDERFLOW},
            (pCase64s){"-92233720368547758089", -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pCase64s){"-12345678901234567899", -1234567890123456789, FN_ERROR_UNDERFLOW},
            (pCase64s){"-123456789012345678991234567890123456789", -1234567890123456789, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pCase64s){"9223372036854775808", 922337203685477580, FN_ERROR_OVERFLOW},
            (pCase64s){"92233720368547758079", 9223372036854775807, FN_ERROR_OVERFLOW},
            (pCase64s){"12345678901234567899", 1234567890123456789, FN_ERROR_OVERFLOW},
            (pCase64s){"123456789012345678991234567890123456789", 1234567890123456789, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase64s){":123", 0, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1234567890123456789/", 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+1234567890123456789/", 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-1234567890123456789/", -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1234567890123456789:", 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+1234567890123456789:", 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-1234567890123456789:", -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"9223372036854775808/", 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+9223372036854775808/", 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-9223372036854775809/", -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"9223372036854775807/", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+9223372036854775807/", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-9223372036854775808/", -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"9223372036854775810/", 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+9223372036854775810/", 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-9223372036854775810/", -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1234567890123456789012345678901234567890:", 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+1234567890123456789012345678901234567890:", 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-1234567890123456789012345678901234567890:", -1234567890123456789, FN_ERROR_INVALID_FORMAT},
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

int decToUInt64Test(){
    #define FUNCCALL decToUInt64
    const static char * testName = "decToUInt64";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint64_t, 9, 20, PRIu64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint64_t, 9, 20, FN_ERROR_GENERAL, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64u tCase3[] = {
            (pCase64u){"18446744073709551614", 18446744073709551614U, 0},
            (pCase64u){"18446744073709551615", 18446744073709551615U, 0},
            (pCase64u){"0018446744073709551615", 18446744073709551615U, 0},
            (pCase64u){"000", 0, 0},
            (pCase64u){"000018446744073709551615", 18446744073709551615U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64u tCase4[] = {
            /* Overflow */
            (pCase64u){"18446744073709551616", 1844674407370955161U, 1},
            (pCase64u){"184467440737095516159", 18446744073709551615U, 1},
            (pCase64u){"123456789012345678909", 12345678901234567890U, 1},
            /* Invalid format */
            (pCase64u){":213", 0, 1},
            (pCase64u){"12345678901234567890:", 12345678901234567890U, 1},
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

int decToUInt64TrueErrorTest(){
    #define FUNCCALL decToUInt64TrueError
    const static char * testName = "decToUInt64TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint64_t, 9, 20, PRIu64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint64_t, 9, 20, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64u tCase3[] = {
            (pCase64u){"18446744073709551614", 18446744073709551614U, 0},
            (pCase64u){"18446744073709551615", 18446744073709551615U, 0},
            (pCase64u){"0018446744073709551615", 18446744073709551615U, 0},
            (pCase64u){"000", 0, 0},
            (pCase64u){"000018446744073709551615", 18446744073709551615U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64u tCase4[] = {
            /* Overflow */
            (pCase64u){"18446744073709551616", 1844674407370955161U, FN_ERROR_OVERFLOW},
            (pCase64u){"184467440737095516159", 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pCase64u){"123456789012345678909", 12345678901234567890U, FN_ERROR_OVERFLOW},
            (pCase64u){"1234567890123456789091234567890123456789", 12345678901234567890U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase64u){":214", 0, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"12345678901234567890/", 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"12345678901234567890:", 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"18446744073709551616/", 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"18446744073709551615:", 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"18446744073709551620:", 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"1234567890123456789012345678901234567890:", 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
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

int decCompareTest64(){
    #define FUNCCALL decCompareAsInt64
    const static char * testName = "decCompareAsInt64";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"9223372036854775807", "-9223372036854775808", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"9223372036854775807", "9223372036854775807", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"-9223372036854775808", "9223372036854775807", -1, 0}
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
            (cCase){"-9223372036854775809", "1", 0, 1},
            (cCase){"1", "9223372036854775808", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decInt64OrSmallerTest(){
    #define FUNCCALL decInt64OrSmaller
    const static char * testName = "decInt64OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "-12345678901234567890", -1},
            (cCaseNE){"!1", "12345678901234567890", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "9223372036854775807", -1},
            /* UnderFlow to */
            (cCaseNE){"-12345678901234567890", "!1", 1},
            (cCaseNE){"-12345678901234567890", "-9223372036854775809", 0},
            (cCaseNE){"-12345678901234567890", "12345678901234567890", -1},
            (cCaseNE){"-12345678901234567890", "", -1},
            (cCaseNE){"-12345678901234567890", "-9223372036854775808", -1},
            /* OverFlow to */
            (cCaseNE){"12345678901234567890", "!1", 1},
            (cCaseNE){"12345678901234567890", "-12345678901234567890", 1},
            (cCaseNE){"12345678901234567890", "9223372036854775808", 0},
            (cCaseNE){"12345678901234567890", "", -1},
            (cCaseNE){"12345678901234567890", "9223372036854775807", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "-12345678901234567890", 1},
            (cCaseNE){"", "12345678901234567890", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "-9223372036854775808", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "-12345678901234567890", 1},
            (cCaseNE){"1", "12345678901234567890", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"-9223372036854775808", "9223372036854775807" , -1},
            (cCaseNE){"-9223372036854775808", "-9223372036854775808" , 0},
            (cCaseNE){"9223372036854775807", "-9223372036854775808" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decCompareUTest64(){
    #define FUNCCALL decCompareAsUInt64
    const static char * testName = "decCompareAsUInt64";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"18446744073709551615", "18446744073709551614", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"18446744073709551615", "18446744073709551615", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"18446744073709551614", "18446744073709551615", -1, 0}
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
            (cCase){"18446744073709551616", "1", 0, 1},
            (cCase){"1", "18446744073709551616", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decUInt64OrSmallerTest(){
    #define FUNCCALL decUInt64OrSmaller
    const static char * testName = "decUInt64OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "123456789012345678901", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "18446744073709551615", -1},
            /* OverFlow to */
            (cCaseNE){"123456789012345678901", "!1", 1},
            (cCaseNE){"123456789012345678901", "18446744073709551616", 0},
            (cCaseNE){"123456789012345678901", "", -1},
            (cCaseNE){"123456789012345678901", "18446744073709551615", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "123456789012345678901", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "18446744073709551615", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "123456789012345678901", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"18446744073709551614", "18446744073709551615" , -1},
            (cCaseNE){"18446744073709551615", "18446744073709551615" , 0},
            (cCaseNE){"18446744073709551615", "18446744073709551614" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToInt64FPTest(){
    #define FUNCCALL decToInt64FP
    const static char * testName = "decToInt64FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_S(FUNCCALL, int64_t, 9, 19, optArray, ALEN(optArray), PRId64);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_S(FUNCCALL, int64_t, 9, 19, 20, PRId64);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_S(FUNCCALL, int64_t, 9, 19, 20, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase64s tCase3[] = {
            (pfpCase64s){"9223372036854775805", 0, 18, FN_OPT_NONE, 9223372036854775805, 0},
            (pfpCase64s){"9223372036854775805", 0, 18, FN_OPT_PFP_ALL, 9223372036854775805, 0},
            (pfpCase64s){"+9223372036854775805", 0, 19, FN_OPT_PFP_ALL, 9223372036854775805, 0},
            (pfpCase64s){"-9223372036854775807", 0, 19, FN_OPT_PFP_ALL, -9223372036854775807, 0},
                       /* 0123456789012345678901234 */
            (pfpCase64s){"9223372036854775807", 0, 18, FN_OPT_NONE, 9223372036854775807, 0},
            (pfpCase64s){"9223372036854775807", 0, 18, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"+9223372036854775807", 0, 19, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"-9223372036854775808", 0, 19, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0},
            (pfpCase64s){"009223372036854775807", 0, 20, FN_OPT_NONE, 9223372036854775807, 0},
            (pfpCase64s){"009223372036854775807", 0, 20, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"+000", 0, 3, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase64s){"-00009223372036854775808", 0, 23, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase64s tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase64s){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase64s){"  12", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase64s){"   -9223372036854775807", 0, 22, FN_PF_IGNORE_LSPACES, -9223372036854775807, 0},
            (pfpCase64s){"   -9223372036854775808", 0, 22, FN_PF_IGNORE_LSPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"    9223372036854775807", 0, 22, FN_PF_IGNORE_LSPACES, 9223372036854775807, 0},
            (pfpCase64s){"   123  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase64s){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase64s){"12  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase64s){"-9223372036854775807   ", 0, 22, FN_PF_IGNORE_TSPACES, -9223372036854775807, 0},
            (pfpCase64s){"-9223372036854775808   ", 0, 22, FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"9223372036854775807    ", 0, 22, FN_PF_IGNORE_TSPACES, 9223372036854775807, 0},
            (pfpCase64s){" 12345  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase64s){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase64s){" -1 ", 0, 3, FN_PF_IGNORE_SPACES, -1, 0},
            (pfpCase64s){"   -000  ", 0, 8, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase64s){"   -9223372036854775807  ", 0, 24, FN_PF_IGNORE_SPACES, -9223372036854775807, 0},
            (pfpCase64s){"   -9223372036854775808  ", 0, 24, FN_PF_IGNORE_SPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"   9223372036854775807   ", 0, 24, FN_PF_IGNORE_SPACES, 9223372036854775807, 0},
            (pfpCase64s){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase64s tCase5[] = {
            /* Underflow */
            (pfpCase64s){"-9223372036854775809", 0, 19, FN_OPT_NONE, -922337203685477580, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"-92233720368547758080", 0, 20, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"-12345678901234567890", 0, 20, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfpCase64s){"9223372036854775808", 0, 18, FN_OPT_NONE, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfpCase64s){"92233720368547758070", 0, 19, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"12345678901234567890", 0, 19, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase64s){":123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){":123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890123456789/", 0, 19, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+1234567890123456789/", 0, 20, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-1234567890123456789/", 0, 20, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
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
            (pfpCase64s){"/1234567890123456789", 0, 19, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+/1234567890123456789", 0, 20, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-/1234567890123456789", 0, 20, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890123456789/", 0, 19, FN_PF_PARSE_ON_ERROR,
                         1234567890123456789, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+1234567890123456789/", 0, 20, FN_PF_PARSE_ON_ERROR,
                         1234567890123456789, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-1234567890123456789/", 0, 20, FN_PF_PARSE_ON_ERROR,
                         -1234567890123456789, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"9223372036854775808:", 0, 19, FN_PF_PARSE_ON_ERROR,
                         922337203685477580, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+9223372036854775808:", 0, 20, FN_PF_PARSE_ON_ERROR,
                         922337203685477580, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-9223372036854775809:", 0, 20, FN_PF_PARSE_ON_ERROR,
                         -922337203685477580, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"9223372036854775807/", 0, 19, FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+9223372036854775807/", 0, 20, FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-9223372036854775808/", 0, 20, FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"9223372036854775810:", 0, 19, FN_PF_PARSE_ON_ERROR,
                         922337203685477581, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+9223372036854775810:", 0, 20, FN_PF_PARSE_ON_ERROR,
                         922337203685477581, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-9223372036854775810:", 0, 20, FN_PF_PARSE_ON_ERROR,
                         -922337203685477581, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"1234567890123456789012345678901234567890/", 0, 40, FN_PF_PARSE_ON_ERROR,
                         1234567890123456789, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+1234567890123456789012345678901234567890/", 0, 41, FN_PF_PARSE_ON_ERROR,
                         1234567890123456789, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-1234567890123456789012345678901234567890/", 0, 41, FN_PF_PARSE_ON_ERROR,
                         -1234567890123456789, FN_ERROR_UNDERFLOW},
            /* Long Check */
            (pfpCase64s){":1234567890123456789", 0, 19, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890123456789/", 0, 19, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+1234567890123456789/", 0, 20, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-1234567890123456789/", 0, 20, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890123456789:1234567890123456789", 0, 38, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+1234567890123456789:1234567890123456789", 0, 39, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-1234567890123456789:1234567890123456789", 0, 39, FN_PF_LONG_CHECK,
                         -0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567890123456789:1234567890123456789", 0, 38, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+1234567890123456789:1234567890123456789", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-1234567890123456789:1234567890123456789", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"9223372036854775810:9223372036854775810", 0, 38, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+9223372036854775810:9223372036854775810", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-9223372036854775810:9223372036854775810", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"9223372036854775808:9223372036854775808", 0, 38, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+9223372036854775808:9223372036854775808", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-9223372036854775809:9223372036854775809", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"922337203685477581099223372036854775810", 0, 38, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477581, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+922337203685477581099223372036854775810", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477581, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-922337203685477581099223372036854775810", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -922337203685477581, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"922337203685477580899223372036854775808", 0, 38, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477580, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+922337203685477580899223372036854775808", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         922337203685477580, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-922337203685477580999223372036854775809", 0, 39, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -922337203685477580, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"92233720368547758079", 0, 19, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+92233720368547758079", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-92233720368547758089", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, int64_t, tCase6, ALEN(tCase6), PRId64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase64s tCase7[] = {
            (pfpCase64s){"This number 12345678 is parseable.",
                         12, 19, FN_OPT_NONE, 12345678, 0},
            (pfpCase64s){"Number(123456789) to array.",
                         7, 15, FN_OPT_PFP_ALL, 123456789, 0},
            (pfpCase64s){"At least this one(-1234567890) with sign must pass.",
                         18, 28, FN_OPT_PFP_ALL, -1234567890, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase64s){"Important number:+9223372036854775807(INT MAX VALUE)",
                         17, 36, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"Another one:-9223372036854775808(INT64 MIN VALUE)",
                         12, 31, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0},
            (pfpCase64s){"Parse after the seven 1234567145874125to last five",
                         29, 37, FN_OPT_PFP_ALL, 145874125, 0},
            (pfpCase64s){"From next space   -123456789    (to prior space)",
                         15, 31, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase64s){"Without any ingore spaces   -1234567890    with spaces parse will fail."
                         "And the segment considered to be overflow, or contain an invalid format"
                         "depends on FN_PF_LONG_CHECK",
                         25, 42, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int decToUInt64FPTest(){
    #define FUNCCALL decToUInt64FP
    const static char * testName = "decToUInt64FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_U(FUNCCALL, uint64_t, 9, 20, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_U(FUNCCALL, uint64_t, 9, 20, 21, PRIu64);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_U(FUNCCALL, uint64_t, 9, 20, 21, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        pfpCase64u tCase3[] = {
            (pfpCase64u){"18446744073709551614", 0, 19, FN_OPT_NONE, 18446744073709551614U, 0},
            (pfpCase64u){"18446744073709551614", 0, 19, FN_OPT_PFP_ALL, 18446744073709551614U, 0},
            (pfpCase64u){"18446744073709551615", 0, 19, FN_OPT_NONE, 18446744073709551615U, 0},
            (pfpCase64u){"18446744073709551615", 0, 19, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"0018446744073709551615", 0, 21, FN_OPT_NONE, 18446744073709551615U, 0},
            (pfpCase64u){"0018446744073709551615", 0, 21, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"000", 0, 2, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase64u){"000018446744073709551615", 0, 23, FN_OPT_NONE, 18446744073709551615U, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase64u tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase64u){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase64u){"  12", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase64u){"   18446744073709551614", 0, 22, FN_PF_IGNORE_LSPACES, 18446744073709551614U, 0},
            (pfpCase64u){"   18446744073709551615", 0, 22, FN_PF_IGNORE_LSPACES, 18446744073709551615U, 0},
            (pfpCase64u){"   123  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase64u){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase64u){"12  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase64u){"18446744073709551614   ", 0, 22, FN_PF_IGNORE_TSPACES, 18446744073709551614U, 0},
            (pfpCase64u){"18446744073709551615   ", 0, 22, FN_PF_IGNORE_TSPACES, 18446744073709551615U, 0},
            (pfpCase64u){" 12345  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase64u){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase64u){"   000  ", 0, 7, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase64u){"   18446744073709551614  ", 0, 24, FN_PF_IGNORE_SPACES, 18446744073709551614U, 0},
            (pfpCase64u){"   18446744073709551615  ", 0, 24, FN_PF_IGNORE_SPACES, 18446744073709551615U, 0},
            (pfpCase64u){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase64u tCase5[] = {
            /* Overflow */
            (pfpCase64u){"18446744073709551616", 0, 19, FN_OPT_NONE, 1844674407370955161U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"18446744073709551620", 0, 19, FN_OPT_NONE, 1844674407370955162U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"184467440737095516150", 0, 20, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64u){"123456789012345678901", 0, 20, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase64u){":123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){":123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"12345678901234567890/", 0, 20, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
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
            (pfpCase64u){"/12345678901234567890", 0, 20, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"12345678901234567890:", 0, 20, FN_PF_PARSE_ON_ERROR, 12345678901234567890U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"18446744073709551616:", 0, 20, FN_PF_PARSE_ON_ERROR, 1844674407370955161U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"18446744073709551615/", 0, 20, FN_PF_PARSE_ON_ERROR, 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"18446744073709551620:", 0, 20, FN_PF_PARSE_ON_ERROR, 1844674407370955162U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"12345678901234567890:", 0, 20, FN_PF_PARSE_ON_ERROR, 12345678901234567890U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"+123456789012345678901", 0, 21, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"-123456789012345678901", 0, 21, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            /* Long Check */
            (pfpCase64u){":12345678901234567890", 0, 20, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"12345678901234567890/", 0, 20, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"12345678901234567890:12345678901234567890", 0, 40, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"12345678901234567890:12345678901234567890", 0, 40, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"18446744073709551620:18446744073709551620", 0, 40, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"18446744073709551616:18446744073709551616", 0, 40, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"18446744073709551620918446744073709551620", 0, 40, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1844674407370955162U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"18446744073709551616918446744073709551616", 0, 40, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1844674407370955161U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"184467440737095516159", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
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
            (pfpCase64u){"This number 12345678 is parseable.",
                       12, 19, FN_OPT_NONE, 12345678U, 0},
            (pfpCase64u){"Number(123456789) to array.",
                       7, 15, FN_OPT_PFP_ALL, 123456789U, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase64u){"Important number:+18446744073709551615(UINT64 MAX VALUE), The + is not parsed.",
                       18, 37, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"Parse after the seven 1234567957412547to last five",
                       29, 37, FN_OPT_PFP_ALL, 957412547U, 0},
            (pfpCase64u){"From next space   1234567890    (to prior space)",
                       15, 31, FN_OPT_PFP_ALL, 1234567890U, 0},
            (pfpCase64u){"Without any ingore spaces   1234567890    with spaces parse will fail."
                       "And the segment considered to be overflow, or contain an invalid format"
                       "depends on FN_PF_LONG_CHECK",
                       25, 41, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int decToInt64FNTest(){
    #define FUNCCALL decToInt64FN
    const static char * testName = "decToInt64FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_S(FUNCCALL, int64_t, 9, 19, optArray, ALEN(optArray), PRId64);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_S(FUNCCALL, int64_t, 9, 19, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_S(FUNCCALL, int64_t, 9, 18, PRId64);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase64s tCase4[] = {
            (pfnCase64s){"9223372036854775805", FN_OPT_NONE, 9223372036854775805, 0},
            (pfnCase64s){"9223372036854775805", FN_OPT_PFN_ALL, 9223372036854775805, 0},
            (pfnCase64s){"+9223372036854775805", FN_OPT_PFN_ALL, 9223372036854775805, 0},
            (pfnCase64s){"-9223372036854775807", FN_OPT_PFN_ALL, -9223372036854775807, 0},
            (pfnCase64s){"9223372036854775807", FN_OPT_NONE, 9223372036854775807, 0},
            (pfnCase64s){"9223372036854775807", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"+9223372036854775807", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"-9223372036854775808", FN_OPT_PFN_ALL, -9223372036854775807 - 1, 0},
            (pfnCase64s){"009223372036854775807", FN_OPT_NONE, 9223372036854775807, 0},
            (pfnCase64s){"009223372036854775807", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"+000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase64s){"-00009223372036854775808", FN_OPT_PFN_ALL, -9223372036854775807 - 1, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase64s tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase64s){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase64s){" 12", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase64s){"   -9223372036854775807", FN_PF_IGNORE_LSPACES, -9223372036854775807, 0},
            (pfnCase64s){"   -9223372036854775808", FN_PF_IGNORE_LSPACES, -9223372036854775807 - 1 , 0},
            (pfnCase64s){"    9223372036854775807", FN_PF_IGNORE_LSPACES, 9223372036854775807, 0},
            (pfnCase64s){"   123  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfnCase64s){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase64s){"12  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase64s){"-9223372036854775807   ", FN_PF_IGNORE_TSPACES, -9223372036854775807, 0},
            (pfnCase64s){"-9223372036854775808   ", FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, 0},
            (pfnCase64s){"9223372036854775807    ", FN_PF_IGNORE_TSPACES, 9223372036854775807, 0},
            (pfnCase64s){" 12345  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase64s){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase64s){" -1 ", FN_PF_IGNORE_SPACES, -1, 0},
            (pfnCase64s){"   -000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase64s){"   -9223372036854775807  ", FN_PF_IGNORE_SPACES, -9223372036854775807, 0},
            (pfnCase64s){"   -9223372036854775808  ", FN_PF_IGNORE_SPACES, -9223372036854775807 - 1, 0},
            (pfnCase64s){"   9223372036854775807       ", FN_PF_IGNORE_SPACES, 9223372036854775807, 0},
            (pfnCase64s){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, int64_t, tCase5, ALEN(tCase5), PRId64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase64s tCase6[] = {
            /* Underflow */
            (pfnCase64s){"-9223372036854775809", FN_OPT_NONE, -922337203685477580, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-92233720368547758080", FN_OPT_NONE, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-12345678901234567890", FN_OPT_NONE, -1234567890123456789, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1234567890123456789:", FN_OPT_NONE, -1234567890123456789, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-9223372036854775808:", FN_OPT_NONE, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-9223372036854775810:", FN_OPT_NONE, -922337203685477581, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1234567890123456789012345678901234567890:", FN_OPT_NONE, -1234567890123456789, FN_ERROR_UNDERFLOW},
            /* Overflow */
            /* --> Original Cases */
            (pfnCase64s){"9223372036854775808", FN_OPT_NONE, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfnCase64s){"92233720368547758070", FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"12345678901234567890", FN_OPT_NONE, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567890123456789:", FN_OPT_NONE, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"9223372036854775807:", FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"9223372036854775810:", FN_OPT_NONE, 922337203685477581, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567890123456789012345678901234567890:", FN_OPT_NONE, 1234567890123456789, FN_ERROR_OVERFLOW},
            /* --> Overflow Check*/
            (pfnCase64s){"9223372036854775810  ", FN_PF_IGNORE_TSPACES, 922337203685477581, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+9223372036854775810  ", FN_PF_IGNORE_TSPACES, 922337203685477581, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-9223372036854775810  ", FN_PF_IGNORE_TSPACES, -922337203685477581, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"9223372036854775808  ", FN_PF_IGNORE_TSPACES, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+9223372036854775808  ", FN_PF_IGNORE_TSPACES, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-9223372036854775809  ", FN_PF_IGNORE_TSPACES, -922337203685477580, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"12345678901234567899  ", FN_PF_IGNORE_TSPACES, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+12345678901234567899  ", FN_PF_IGNORE_TSPACES, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-12345678901234567899  ", FN_PF_IGNORE_TSPACES, -1234567890123456789, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64s){"9223372036854775810:  ", FN_PF_IGNORE_TSPACES, 922337203685477581, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+9223372036854775810:  ", FN_PF_IGNORE_TSPACES, 922337203685477581, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-9223372036854775810:  ", FN_PF_IGNORE_TSPACES, -922337203685477581, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"9223372036854775808:  ", FN_PF_IGNORE_TSPACES, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+9223372036854775808:  ", FN_PF_IGNORE_TSPACES, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-9223372036854775809:  ", FN_PF_IGNORE_TSPACES, -922337203685477580, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"1234567890123456789:  ", FN_PF_IGNORE_TSPACES, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890123456789:  ", FN_PF_IGNORE_TSPACES, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890123456789:  ", FN_PF_IGNORE_TSPACES, -1234567890123456789, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"+123456789012345678/  ", FN_PF_IGNORE_TSPACES, 123456789012345678, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-123456789012345678:  ", FN_PF_IGNORE_TSPACES, -123456789012345678, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775810  0", FN_PF_IGNORE_TSPACES, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775810  0", FN_PF_IGNORE_TSPACES, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775810  0", FN_PF_IGNORE_TSPACES, -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775808  0", FN_PF_IGNORE_TSPACES, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775808  0", FN_PF_IGNORE_TSPACES, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775809  0", FN_PF_IGNORE_TSPACES, -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890123456789  0", FN_PF_IGNORE_TSPACES, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890123456789  0", FN_PF_IGNORE_TSPACES, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890123456789  0", FN_PF_IGNORE_TSPACES, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            /* Invalid format */
            (pfnCase64s){":123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){":123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890123456789:", FN_OPT_NONE, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890123456789:", FN_OPT_NONE, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890123456789:", FN_OPT_NONE, -1234567890123456789, FN_ERROR_UNDERFLOW},
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
            (pfnCase64s){"92233720368547758109  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+92233720368547758109  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-92233720368547758109  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -922337203685477581, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"92233720368547758089  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+92233720368547758089  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-92233720368547758099  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -922337203685477580, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"12345678901234567899  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+12345678901234567899  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-12345678901234567899  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64s){"92233720368547758100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+92233720368547758100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-92233720368547758100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"92233720368547758080  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+92233720368547758080  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-92233720368547758090  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"12345678901234567890  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+12345678901234567890  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-12345678901234567890  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase64s){"9223372036854775810  ", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775810  ", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775810  ", FN_PF_LONG_CHECK, -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775808  ", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775808  ", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775809  ", FN_PF_LONG_CHECK, -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"12345678901234567890  ", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+12345678901234567890  ", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-12345678901234567890  ", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775810/  ", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775810/  ", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775810/  ", FN_PF_LONG_CHECK, -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775808/  ", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775808/  ", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775809/  ", FN_PF_LONG_CHECK, -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"12345678901234567890/  ", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+12345678901234567890/  ", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-12345678901234567890/  ", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775810:  ", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775810:  ", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775810:  ", FN_PF_LONG_CHECK, -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775808:  ", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775808:  ", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775809:  ", FN_PF_LONG_CHECK, -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"12345678901234567890:  ", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+12345678901234567890:  ", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-12345678901234567890:  ", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase64s){"9223372036854775810:", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775810:", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775810:", FN_PF_LONG_CHECK, -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775808:", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775808:", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775809:", FN_PF_LONG_CHECK, -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890123456789:", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890123456789:", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890123456789:", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775810/", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775810/", FN_PF_LONG_CHECK, 922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775810/", FN_PF_LONG_CHECK, -922337203685477581, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"9223372036854775808/", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775808/", FN_PF_LONG_CHECK, 922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775809/", FN_PF_LONG_CHECK, -922337203685477580, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890123456789/", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567890123456789/", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1234567890123456789/", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"12345678901234567899", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+12345678901234567899", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-12345678901234567899", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"123456789012345678901234567890123456789:", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+123456789012345678901234567890123456789:", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-123456789012345678901234567890123456789:", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567890123456789012345678901234567899", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1234567890123456789012345678901234567899", FN_PF_LONG_CHECK, 1234567890123456789, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1234567890123456789012345678901234567899", FN_PF_LONG_CHECK, -1234567890123456789, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"9223372036854775807:", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+9223372036854775807:", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-9223372036854775808:", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"92233720368547758079", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+92233720368547758079", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-92233720368547758089", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW}
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

int decToUInt64FNTest(){
    #define FUNCCALL decToUInt64FN
    const static char * testName = "decToUInt64FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_U(FUNCCALL, uint64_t, 9, 20, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_U(FUNCCALL, uint64_t, 9, 20, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_U(FUNCCALL, uint64_t, 9, 19, PRIu64);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase64u tCase4[] = {
            (pfnCase64u){"18446744073709551614", FN_OPT_NONE, 18446744073709551614U, 0},
            (pfnCase64u){"18446744073709551614", FN_OPT_PFN_ALL, 18446744073709551614U, 0},
            (pfnCase64u){"18446744073709551615", FN_OPT_NONE, 18446744073709551615U, 0},
            (pfnCase64u){"18446744073709551615", FN_OPT_PFN_ALL, 18446744073709551615U, 0},
            (pfnCase64u){"0018446744073709551615", FN_OPT_NONE, 18446744073709551615U, 0},
            (pfnCase64u){"0018446744073709551615", FN_OPT_PFN_ALL, 18446744073709551615U, 0},
            (pfnCase64u){"000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase64u){"000018446744073709551615", FN_OPT_PFN_ALL, 18446744073709551615U, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase64u tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase64u){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase64u){"  12", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase64u){"   18446744073709551614", FN_PF_IGNORE_LSPACES, 18446744073709551614U, 0},
            (pfnCase64u){"   18446744073709551615", FN_PF_IGNORE_LSPACES, 18446744073709551615U, 0},
            (pfnCase64u){"   123  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase64u){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase64u){"12  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase64u){"18446744073709551614   ", FN_PF_IGNORE_TSPACES, 18446744073709551614U, 0},
            (pfnCase64u){"18446744073709551615   ", FN_PF_IGNORE_TSPACES, 18446744073709551615U, 0},
            (pfnCase64u){" 12345  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase64u){"18446744073709551620  ", FN_PF_IGNORE_TSPACES, 1844674407370955162U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"18446744073709551616  ", FN_PF_IGNORE_TSPACES, 1844674407370955161U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"123456789012345678909  ", FN_PF_IGNORE_TSPACES, 12345678901234567890U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64u){"18446744073709551620:  ", FN_PF_IGNORE_TSPACES, 1844674407370955162U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"18446744073709551616:  ", FN_PF_IGNORE_TSPACES, 1844674407370955161U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"12345678901234567890:  ", FN_PF_IGNORE_TSPACES, 12345678901234567890U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"18446744073709551620  0", FN_PF_IGNORE_TSPACES, 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"18446744073709551616  0", FN_PF_IGNORE_TSPACES, 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345678901234567890  0", FN_PF_IGNORE_TSPACES, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase64u){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase64u){"   000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase64u){"   18446744073709551614  ", FN_PF_IGNORE_SPACES, 18446744073709551614U, 0},
            (pfnCase64u){"   18446744073709551615  ", FN_PF_IGNORE_SPACES, 18446744073709551615U, 0},
            (pfnCase64u){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, uint64_t, tCase5, ALEN(tCase5), PRIu64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase64u tCase6[] = {
            /* Overflow */
            (pfnCase64u){"18446744073709551616", FN_OPT_NONE, 1844674407370955161U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"18446744073709551620", FN_OPT_NONE, 1844674407370955162U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"184467440737095516150", FN_OPT_NONE, 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"123456789012345678901", FN_OPT_NONE, 12345678901234567890U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase64u){":123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){":123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345678901234567890/", FN_OPT_NONE, 12345678901234567890U, FN_ERROR_OVERFLOW},
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
            (pfnCase64u){"184467440737095516209  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1844674407370955162U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"184467440737095516169  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1844674407370955161U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"123456789012345678909  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64u){"184467440737095516200  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"184467440737095516160  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"123456789012345678900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase64u){"18446744073709551620  ", FN_PF_LONG_CHECK, 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"18446744073709551616  ", FN_PF_LONG_CHECK, 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345678901234567890  ", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"18446744073709551620/  ", FN_PF_LONG_CHECK, 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"18446744073709551616/  ", FN_PF_LONG_CHECK, 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345678901234567890/  ", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"184467440737095516200:  ", FN_PF_LONG_CHECK, 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"184467440737095516160:  ", FN_PF_LONG_CHECK, 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"123456789012345678900:  ", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase64u){"18446744073709551620/", FN_PF_LONG_CHECK, 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"18446744073709551616/", FN_PF_LONG_CHECK, 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345678901234567890/", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"18446744073709551620:", FN_PF_LONG_CHECK, 1844674407370955162U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"18446744073709551616:", FN_PF_LONG_CHECK, 1844674407370955161U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345678901234567890:", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"123456789012345678909", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"1234567890123456789012345678901234567890:", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345678901234567890123456789012345678909", FN_PF_LONG_CHECK, 12345678901234567890U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"18446744073709551615:", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"184467440737095516159", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_OVERFLOW}
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

int decToInt64C1Test(){
    #define FUNCCALL decToInt64C1
    const static char * testName = "decToInt64C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_S(FUNCCALL, int64_t, 9, 19, optArray, ALEN(optArray), PRId64);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_S( FUNCCALL, int64_t, 9, 19, PRId64);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_S( FUNCCALL, int64_t, 9, PRId64);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");

        pc1Case64s tCase3[] = {
            /* a */
            (pc1Case64s){"9223372036854775805", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+9223372036854775805", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+9223372036854775805", FN_OPT_PC1_ALL, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"-9223372036854775807", FN_OPT_NONE, {-9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"-9223372036854775807", FN_OPT_PC1_ALL, {-9223372036854775807}, {0}, {-1}, 1},
            /* b */
            (pc1Case64s){"9223372036854775807", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+9223372036854775807", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+9223372036854775807", FN_OPT_PC1_ALL, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"-9223372036854775808", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-9223372036854775808", FN_OPT_PC1_ALL, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            /* c */
            (pc1Case64s){"009223372036854775807", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"009223372036854775807", FN_OPT_PC1_ALL, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case64s){"+000", FN_OPT_PC1_ALL, {0}, {0}, {-1}, 1},
            (pc1Case64s){"-00009223372036854775808", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-00009223372036854775808", FN_OPT_PC1_ALL, {-9223372036854775807 - 1}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case64s tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case64s){"-+9223372036854775805", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+-9223372036854775805", FN_OPT_NONE, {-9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){":9223372036854775805:", FN_OPT_NONE, {9223372036854775805}, {0}, {20}, 1},
            (pc1Case64s){":+9223372036854775805:", FN_OPT_NONE, {9223372036854775805}, {0}, {21}, 1},
            (pc1Case64s){":-9223372036854775805:", FN_OPT_NONE, {-9223372036854775805}, {0}, {21}, 1},
            (pc1Case64s){":@#$%^&9223372036854775805:@", FN_OPT_NONE, {9223372036854775805}, {0}, {26}, 1},
            (pc1Case64s){":@#$%^&+9223372036854775805:@", FN_OPT_NONE, {9223372036854775805}, {0}, {27}, 1},
            (pc1Case64s){":@#$%^&-9223372036854775805:@", FN_OPT_NONE, {-9223372036854775805}, {0}, {27}, 1},
            (pc1Case64s){":@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case64s){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case64s){":9223372036854775805", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64s){"9223372036854775805:", FN_PC_NO_INVALID_SKIP, {9223372036854775805}, {0}, {19}, 1},
            (pc1Case64s){"+9223372036854775805:", FN_PC_NO_INVALID_SKIP, {9223372036854775805}, {0}, {20}, 1},
            (pc1Case64s){"-9223372036854775805:", FN_PC_NO_INVALID_SKIP, {-9223372036854775805}, {0}, {20}, 1},
            (pc1Case64s){"^%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
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
            (pc1Case64s){"-9223372036854775809", FN_OPT_NONE, {-922337203685477580}, {0}, {19}, 1},
            (pc1Case64s){"-92233720368547758099", FN_OPT_NONE, {-922337203685477580}, {0}, {19}, 1},
            (pc1Case64s){"-92233720368547758089", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {20}, 1},
            (pc1Case64s){"-9223372036854775810", FN_OPT_NONE, {-922337203685477581}, {0}, {19}, 1},
            (pc1Case64s){"-92233720368547758109", FN_OPT_NONE, {-922337203685477581}, {0}, {19}, 1},
            (pc1Case64s){"-12345678901234567899", FN_OPT_NONE, {-1234567890123456789}, {0}, {20}, 1},
            (pc1Case64s){"-1234567890123456789912345678901234567890", FN_OPT_NONE, {-1234567890123456789}, {0}, {20}, 1},
            /* --> Overflow */
            (pc1Case64s){"9223372036854775808", FN_OPT_NONE, {922337203685477580}, {0}, {18}, 1},
            (pc1Case64s){"92233720368547758089", FN_OPT_NONE, {922337203685477580}, {0}, {18}, 1},
            (pc1Case64s){"92233720368547758079", FN_OPT_NONE, {9223372036854775807}, {0}, {19}, 1},
            (pc1Case64s){"9223372036854775810", FN_OPT_NONE, {922337203685477581}, {0}, {18}, 1},
            (pc1Case64s){"92233720368547758109", FN_OPT_NONE, {922337203685477581}, {0}, {18}, 1},
            (pc1Case64s){"12345678901234567899", FN_OPT_NONE, {1234567890123456789}, {0}, {19}, 1},
            (pc1Case64s){"1234567890123456789912345678901234567890", FN_OPT_NONE, {1234567890123456789}, {0}, {19}, 1},
            /* OVERFLOW_ERROR opt */
            /* --> Underflow */
            (pc1Case64s){"-9223372036854775809", FN_PC_OVERFLOW_ERROR, {-922337203685477580}, {FN_ERROR_UNDERFLOW}, {19}, 1},
            (pc1Case64s){"-92233720368547758099", FN_PC_OVERFLOW_ERROR, {-922337203685477580}, {FN_ERROR_UNDERFLOW}, {19}, 1},
            (pc1Case64s){"-92233720368547758089", FN_PC_OVERFLOW_ERROR, {-9223372036854775807 - 1}, {FN_ERROR_UNDERFLOW}, {20}, 1},
            (pc1Case64s){"-9223372036854775810", FN_PC_OVERFLOW_ERROR, {-922337203685477581}, {FN_ERROR_UNDERFLOW}, {19}, 1},
            (pc1Case64s){"-92233720368547758109", FN_PC_OVERFLOW_ERROR, {-922337203685477581}, {FN_ERROR_UNDERFLOW}, {19}, 1},
            (pc1Case64s){"-12345678901234567899", FN_PC_OVERFLOW_ERROR, {-1234567890123456789}, {FN_ERROR_UNDERFLOW}, {20}, 1},
            (pc1Case64s){"-1234567890123456789912345678901234567890", FN_PC_OVERFLOW_ERROR, {-1234567890123456789}, {FN_ERROR_UNDERFLOW}, {20}, 1},
            /* --> Overflow */
            (pc1Case64s){"9223372036854775808", FN_PC_OVERFLOW_ERROR, {922337203685477580}, {FN_ERROR_OVERFLOW}, {18}, 1},
            (pc1Case64s){"92233720368547758089", FN_PC_OVERFLOW_ERROR, {922337203685477580}, {FN_ERROR_OVERFLOW}, {18}, 1},
            (pc1Case64s){"92233720368547758079", FN_PC_OVERFLOW_ERROR, {9223372036854775807}, {FN_ERROR_OVERFLOW}, {19}, 1},
            (pc1Case64s){"9223372036854775810", FN_PC_OVERFLOW_ERROR, {922337203685477581}, {FN_ERROR_OVERFLOW}, {18}, 1},
            (pc1Case64s){"92233720368547758109", FN_PC_OVERFLOW_ERROR, {922337203685477581}, {FN_ERROR_OVERFLOW}, {18}, 1},
            (pc1Case64s){"12345678901234567899", FN_PC_OVERFLOW_ERROR, {1234567890123456789}, {FN_ERROR_OVERFLOW}, {19}, 1},
            (pc1Case64s){"1234567890123456789912345678901234567890", FN_PC_OVERFLOW_ERROR, {1234567890123456789}, {FN_ERROR_OVERFLOW}, {19}, 1},
            /* OVERFLOW SKIP opt */
            /* --> Underflow */
            (pc1Case64s){"-9223372036854775809", FN_PC_OVERFLOW_SKIP, {-922337203685477580}, {0}, {-1}, 1},
            (pc1Case64s){"-92233720368547758099", FN_PC_OVERFLOW_SKIP, {-922337203685477580}, {0}, {-1}, 1},
            (pc1Case64s){"-92233720368547758089", FN_PC_OVERFLOW_SKIP, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-9223372036854775810", FN_PC_OVERFLOW_SKIP, {-922337203685477581}, {0}, {-1}, 1},
            (pc1Case64s){"-92233720368547758109", FN_PC_OVERFLOW_SKIP, {-922337203685477581}, {0}, {-1}, 1},
            (pc1Case64s){"-12345678901234567899", FN_PC_OVERFLOW_SKIP, {-1234567890123456789}, {0}, {-1}, 1},
            (pc1Case64s){"-1234567890123456789912345678901234567890", FN_PC_OVERFLOW_SKIP, {-1234567890123456789}, {0}, {-1}, 1},
            (pc1Case64s){"-9223372036854775809:", FN_PC_OVERFLOW_SKIP, {-922337203685477580}, {0}, {20}, 1},
            (pc1Case64s){"-92233720368547758099:", FN_PC_OVERFLOW_SKIP, {-922337203685477580}, {0}, {21}, 1},
            (pc1Case64s){"-92233720368547758089:", FN_PC_OVERFLOW_SKIP, {-9223372036854775807 - 1}, {0}, {21}, 1},
            (pc1Case64s){"-9223372036854775810:", FN_PC_OVERFLOW_SKIP, {-922337203685477581}, {0}, {20}, 1},
            (pc1Case64s){"-92233720368547758109:", FN_PC_OVERFLOW_SKIP, {-922337203685477581}, {0}, {21}, 1},
            (pc1Case64s){"-12345678901234567899:", FN_PC_OVERFLOW_SKIP, {-1234567890123456789}, {0}, {21}, 1},
            (pc1Case64s){"-1234567890123456789912345678901234567890:", FN_PC_OVERFLOW_SKIP, {-1234567890123456789}, {0}, {41}, 1},
            /* --> Overflow */
            (pc1Case64s){"9223372036854775808", FN_PC_OVERFLOW_SKIP, {922337203685477580}, {0}, {-1}, 1},
            (pc1Case64s){"92233720368547758089", FN_PC_OVERFLOW_SKIP, {922337203685477580}, {0}, {-1}, 1},
            (pc1Case64s){"92233720368547758079", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"9223372036854775810", FN_PC_OVERFLOW_SKIP, {922337203685477581}, {0}, {-1}, 1},
            (pc1Case64s){"92233720368547758109", FN_PC_OVERFLOW_SKIP, {922337203685477581}, {0}, {-1}, 1},
            (pc1Case64s){"12345678901234567899", FN_PC_OVERFLOW_SKIP, {1234567890123456789}, {0}, {-1}, 1},
            (pc1Case64s){"1234567890123456789912345678901234567890", FN_PC_OVERFLOW_SKIP, {1234567890123456789}, {0}, {-1}, 1},
            (pc1Case64s){"9223372036854775808:", FN_PC_OVERFLOW_SKIP, {922337203685477580}, {0}, {19}, 1},
            (pc1Case64s){"92233720368547758089:", FN_PC_OVERFLOW_SKIP, {922337203685477580}, {0}, {20}, 1},
            (pc1Case64s){"92233720368547758079:", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {20}, 1},
            (pc1Case64s){"9223372036854775810:", FN_PC_OVERFLOW_SKIP, {922337203685477581}, {0}, {19}, 1},
            (pc1Case64s){"92233720368547758109:", FN_PC_OVERFLOW_SKIP, {922337203685477581}, {0}, {20}, 1},
            (pc1Case64s){"12345678901234567899:", FN_PC_OVERFLOW_SKIP, {1234567890123456789}, {0}, {20}, 1},
            (pc1Case64s){"1234567890123456789912345678901234567890:", FN_PC_OVERFLOW_SKIP, {1234567890123456789}, {0}, {40}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case64s){"1234567890123456789/", FN_PC_OVERFLOW_ERROR, {1234567890123456789}, {0}, {19}, 1},
            (pc1Case64s){"1234567890123456789:", FN_PC_OVERFLOW_ERROR, {1234567890123456789}, {0}, {19}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, int64_t, tCase5, ALEN(tCase5), PRId64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case64s tCase6[] = {
            (pc1Case64s){"123 +478 -157 $120 $-120", FN_OPT_NONE,
                         {123, 478, -157, 120, -120},
                         {0,0,0,0,0},
                         {3,8,13,18,-1},
                         5},
            (pc1Case64s){"059 +12345678901234567890 -9223372036854775808012 $120 $-2547812", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {59, 1234567890123456789, -9223372036854775807 - 1, 120, -2547812},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_UNDERFLOW, 0, 0},
                         {3,25,49,54,-1},
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

int decToUInt64C1Test(){
    #define FUNCCALL decToUInt64C1
    const static char * testName = "decToUInt64C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_U(FUNCCALL, uint64_t, 9, 20, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_U( FUNCCALL, uint64_t, 9, 20, PRIu64);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_U( FUNCCALL, uint64_t, 9, PRIu64);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");

        pc1Case64u tCase3[] = {
            /* a */
            (pc1Case64u){"18446744073709551614", FN_OPT_NONE, {18446744073709551614U}, {0}, {-1}, 1},
            (pc1Case64u){"18446744073709551614", FN_OPT_PC1_ALL, {18446744073709551614U}, {0}, {-1}, 1},
            /* b */
            (pc1Case64u){"18446744073709551615", FN_OPT_NONE, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"18446744073709551615", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1},
            /* c */
            (pc1Case64u){"0018446744073709551615", FN_OPT_NONE, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"0018446744073709551615", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case64u){"000018446744073709551615", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case64u tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case64u){"-1", FN_OPT_NONE, {1}, {0}, {-1}, 1},
            (pc1Case64u){":18446744073709551614:", FN_OPT_NONE, {18446744073709551614U}, {0}, {21}, 1},
            (pc1Case64u){":@#$%^&18446744073709551614:@", FN_OPT_NONE, {18446744073709551614U}, {0}, {27}, 1},
            (pc1Case64u){":@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case64u){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case64u){"+0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"-0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){":18446744073709551614", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"18446744073709551614:", FN_PC_NO_INVALID_SKIP, {18446744073709551614U}, {0}, {20}, 1},
            (pc1Case64u){"^%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case64u tCase5[] = {
            /* Overflow default */
            (pc1Case64u){"18446744073709551616", FN_OPT_NONE, {1844674407370955161U}, {0}, {19}, 1},
            (pc1Case64u){"184467440737095516169", FN_OPT_NONE, {1844674407370955161U}, {0}, {19}, 1},
            (pc1Case64u){"184467440737095516159", FN_OPT_NONE, {18446744073709551615U}, {0}, {20}, 1},
            (pc1Case64u){"18446744073709551620", FN_OPT_NONE, {1844674407370955162U}, {0}, {19}, 1},
            (pc1Case64u){"184467440737095516209", FN_OPT_NONE, {1844674407370955162U}, {0}, {19}, 1},
            (pc1Case64u){"123456789012345678909", FN_OPT_NONE, {12345678901234567890U}, {0}, {20}, 1},
            (pc1Case64u){"1234567890123456789091234567890123456789", FN_OPT_NONE, {12345678901234567890U}, {0}, {20}, 1},
            /* OVERFLOW_ERROR opt */
            (pc1Case64u){"18446744073709551616", FN_PC_OVERFLOW_ERROR, {1844674407370955161U}, {FN_ERROR_OVERFLOW}, {19}, 1},
            (pc1Case64u){"184467440737095516169", FN_PC_OVERFLOW_ERROR, {1844674407370955161U}, {FN_ERROR_OVERFLOW}, {19}, 1},
            (pc1Case64u){"184467440737095516159", FN_PC_OVERFLOW_ERROR, {18446744073709551615U}, {FN_ERROR_OVERFLOW}, {20}, 1},
            (pc1Case64u){"18446744073709551620", FN_PC_OVERFLOW_ERROR, {1844674407370955162U}, {FN_ERROR_OVERFLOW}, {19}, 1},
            (pc1Case64u){"184467440737095516209", FN_PC_OVERFLOW_ERROR, {1844674407370955162U}, {FN_ERROR_OVERFLOW}, {19}, 1},
            (pc1Case64u){"123456789012345678909", FN_PC_OVERFLOW_ERROR, {12345678901234567890U}, {FN_ERROR_OVERFLOW}, {20}, 1},
            (pc1Case64u){"1234567890123456789091234567890123456789", FN_PC_OVERFLOW_ERROR, {12345678901234567890U}, {FN_ERROR_OVERFLOW}, {20}, 1},
            /* OVERFLOW SKIP opt */
            (pc1Case64u){"18446744073709551616", FN_PC_OVERFLOW_SKIP, {1844674407370955161U}, {0}, {-1}, 1},
            (pc1Case64u){"184467440737095516169", FN_PC_OVERFLOW_SKIP, {1844674407370955161U}, {0}, {-1}, 1},
            (pc1Case64u){"184467440737095516159", FN_PC_OVERFLOW_SKIP, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"18446744073709551620", FN_PC_OVERFLOW_SKIP, {1844674407370955162U}, {0}, {-1}, 1},
            (pc1Case64u){"184467440737095516209", FN_PC_OVERFLOW_SKIP, {1844674407370955162U}, {0}, {-1}, 1},
            (pc1Case64u){"123456789012345678909", FN_PC_OVERFLOW_SKIP, {12345678901234567890U}, {0}, {-1}, 1},
            (pc1Case64u){"1234567890123456789091234567890123456789", FN_PC_OVERFLOW_SKIP, {12345678901234567890U}, {0}, {-1}, 1},
            (pc1Case64u){"18446744073709551616:", FN_PC_OVERFLOW_SKIP, {1844674407370955161U}, {0}, {20}, 1},
            (pc1Case64u){"184467440737095516169:", FN_PC_OVERFLOW_SKIP, {1844674407370955161U}, {0}, {21}, 1},
            (pc1Case64u){"184467440737095516159:", FN_PC_OVERFLOW_SKIP, {18446744073709551615U}, {0}, {21}, 1},
            (pc1Case64u){"18446744073709551620:", FN_PC_OVERFLOW_SKIP, {1844674407370955162U}, {0}, {20}, 1},
            (pc1Case64u){"184467440737095516209:", FN_PC_OVERFLOW_SKIP, {1844674407370955162U}, {0}, {21}, 1},
            (pc1Case64u){"123456789012345678909:", FN_PC_OVERFLOW_SKIP, {12345678901234567890U}, {0}, {21}, 1},
            (pc1Case64u){"1234567890123456789091234567890123456789:", FN_PC_OVERFLOW_SKIP, {12345678901234567890U}, {0}, {40}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case64u){"12345678901234567890/", FN_PC_OVERFLOW_ERROR, {12345678901234567890U}, {0}, {20}, 1},
            (pc1Case64u){"12345678901234567890:", FN_PC_OVERFLOW_ERROR, {12345678901234567890U}, {0}, {20}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, uint64_t, tCase5, ALEN(tCase5), PRIu64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case64u tCase6[] = {
            (pc1Case64u){"123 5789 4874 $3294967295 & $874854", FN_OPT_NONE,
                         {123U, 5789U, 4874U, 3294967295U, 874854U},
                         {0,0,0,0,0},
                         {3,8,13,25,-1},
                         5},
            (pc1Case64u){"123 184467440737095516150 123456789012345678901 $3294967295 & $874854", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {123U, 18446744073709551615U, 12345678901234567890U, 3294967295U, 874854U},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_OVERFLOW, 0, 0},
                         {3,25,47,59,-1},
                         5}
        };

        MAKE_PC1_CASES_LOOP("Test 6", FUNCCALL, uint64_t, tCase6, ALEN(tCase6), PRIu64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Fatal error test.");

        pc1Case64u tCase7[] = {
            (pc1Case64u){"1", ~((unsigned int)FN_OPT_PC1_ALL), {1}, {0}, {0}, 1}
        };

        MAKE_PC1_CASES_FATAL("Test 7", FUNCCALL, uint64_t, tCase7, ALEN(tCase7));
        puts ("# Test 7: Passed.");
    } /* END Test 7 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}
