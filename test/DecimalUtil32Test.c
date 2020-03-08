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
#include "../h/DecimalUtil32.h"
#include "../testlib/testlib.c"
#include "test.h"

int decToInt32Test();
int decToInt32TrueErrorTest();
int decToUInt32Test();
int decToUInt32TrueErrorTest();

int decCompareTest32();
int decInt32OrSmallerTest();
int decCompareUTest32();
int decUInt32OrSmallerTest();

int decToInt32FPTest();
int decToUInt32FPTest();
int decToInt32FNTest();
int decToUInt32FNTest();

int decToInt32C1Test();
int decToUInt32C1Test();

int main(void){
    if ( decToInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( decCompareTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( decInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decCompareUTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( decUInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( decToInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( decToInt32C1Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( decToUInt32C1Test() == 1 ) return 1;

    return 0;
}

int decToInt32Test(){
    #define FUNCCALL decToInt32
    const static char * testName = "decToInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 9, 10, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 9, 10, FN_ERROR_GENERAL, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "2147483645",  2147483645, 0},
            (pCase32s){"+2147483645",  2147483645, 0},
            (pCase32s){"-2147483647", -2147483647, 0},
            (pCase32s){ "2147483647",  2147483647, 0},
            (pCase32s){"+2147483647",  2147483647, 0},
            (pCase32s){"-2147483648", -2147483648, 0},
            (pCase32s){"002147483647", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-00002147483648", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3) , PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-2147483649", -214748364, 1},
            (pCase32s){"-21474836480", -2147483648, 1},
            (pCase32s){"-12345678900", -1234567890, 1},
            /* Overflow */
            (pCase32s){"2147483648", 214748364, 1},
            (pCase32s){"21474836470", 2147483647, 1},
            (pCase32s){"12345678900", 1234567890, 1},
            /* Invalid format */
            (pCase32s){":123", 0, 1},
            (pCase32s){"-1234567890:", -1234567890, 1},
            /* Empty string */
            (pCase32s){"", 0, 1}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToInt32TrueErrorTest(){
    #define FUNCCALL decToInt32TrueError
    const static char * testName = "decToInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 9, 10, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 9, 10, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "2147483645",  2147483645, 0},
            (pCase32s){"+2147483645",  2147483645, 0},
            (pCase32s){"-2147483647", -2147483647, 0},
            (pCase32s){ "2147483647",  2147483647, 0},
            (pCase32s){"+2147483647",  2147483647, 0},
            (pCase32s){"-2147483648", -2147483648, 0},
            (pCase32s){"002147483647", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-00002147483648", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-2147483649", -214748364, FN_ERROR_UNDERFLOW},
            (pCase32s){"-21474836489", -2147483648, FN_ERROR_UNDERFLOW},
            (pCase32s){"-12345678909", -1234567890, FN_ERROR_UNDERFLOW},
            (pCase32s){"-123456789091234567890", -1234567890, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pCase32s){"2147483648", 214748364, FN_ERROR_OVERFLOW},
            (pCase32s){"21474836479", 2147483647, FN_ERROR_OVERFLOW},
            (pCase32s){"12345678909", 1234567890, FN_ERROR_OVERFLOW},
            (pCase32s){"123456789091234567890", 1234567890, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32s){":123", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"1234567890/", 1234567890, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"1234567890:", 1234567890, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+1234567890:", 1234567890, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-1234567890:", -1234567890, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"2147483648/", 214748364, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+2147483648/", 214748364, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-2147483649/", -214748364, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"2147483647/", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+2147483647/", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-2147483648/", -2147483648, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"2147483650/", 214748365, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+2147483650/", 214748365, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-2147483650/", -214748365, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"12345678901234567890:", 1234567890, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+12345678901234567890:", 1234567890, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-12345678901234567890:", -1234567890, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pCase32s){"", 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToUInt32Test(){
    #define FUNCCALL decToUInt32
    const static char * testName = "decToUInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 9, 10, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 9, 10, FN_ERROR_GENERAL, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"4294967294", 4294967294U, 0},
            (pCase32u){"4294967295", 4294967295U, 0},
            (pCase32u){"004294967295", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"00004294967295", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"4294967296", 429496729U, 1},
            (pCase32u){"42949672950", 4294967295U, 1},
            (pCase32u){"12345678900", 1234567890U, 1},
            /* Invalid format */
            (pCase32u){":213", 0, 1},
            (pCase32u){"1234567890:", 1234567890U, 1},
            (pCase32u){"-0", 0, 1},
            (pCase32u){"+0", 0, 1},
            /* Empty string */
            (pCase32u){"", 0, 1}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToUInt32TrueErrorTest(){
    #define FUNCCALL decToUInt32TrueError
    const static char * testName = "decToUInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 9, 10, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 9, 10, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"4294967294", 4294967294U, 0},
            (pCase32u){"4294967295", 4294967295U, 0},
            (pCase32u){"004294967295", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"00004294967295", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"4294967296", 429496729U, FN_ERROR_OVERFLOW},
            (pCase32u){"42949672959", 4294967295U, FN_ERROR_OVERFLOW},
            (pCase32u){"12345678909", 1234567890U, FN_ERROR_OVERFLOW},
            (pCase32u){"123456789091234567890", 1234567890U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32u){":214", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"1234567890/", 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"1234567890:", 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"4294967296/", 429496729U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"4294967295:", 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"4294967305:", 429496730U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"12345678901234567890:", 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"-0", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"+0", 0, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pCase32u){"", 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_P_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# TEST 4: Passed.");
    } /* END Test 4 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decCompareTest32(){
    #define FUNCCALL decCompareAsInt32
    const static char * testName = "decCompareAsInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"2147483647", "-2147483648", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"2147483647", "2147483647", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"-2147483648", "2147483647", -1, 0}
        };

        MAKE_C_CASES_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.\n");
    } /* END Test 1 */

    { /* START Test 2 */
        puts ("# TEST 2: Comparator errors.");

        cCase tCase2[] = {
            /* Empty string */
            (cCase){"", "1", 0, 1},
            (cCase){"1", "", 0, 1},
            /* Invalid format */
            (cCase){"1!", "1", 0, 1},
            (cCase){"1", "1!", 0, 1},
            /* Underflow/Overflow */
            (cCase){"-2147483649", "1", 0, 1},
            (cCase){"1", "2147483648", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decInt32OrSmallerTest(){
    #define FUNCCALL decInt32OrSmaller
    const static char * testName = "decInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "-12345678901", -1},
            (cCaseNE){"!1", "12345678901", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "2147483647", -1},
            /* UnderFlow to */
            (cCaseNE){"-12345678901", "!1", 1},
            (cCaseNE){"-12345678901", "-2147483649", 0},
            (cCaseNE){"-12345678901", "12345678901", -1},
            (cCaseNE){"-12345678901", "", -1},
            (cCaseNE){"-12345678901", "-2147483648", -1},
            /* OverFlow to */
            (cCaseNE){"12345678901", "!1", 1},
            (cCaseNE){"12345678901", "-12345678901", 1},
            (cCaseNE){"12345678901", "2147483648", 0},
            (cCaseNE){"12345678901", "", -1},
            (cCaseNE){"12345678901", "2147483647", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "-12345678901", 1},
            (cCaseNE){"", "12345678901", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "-2147483648", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "-12345678901", 1},
            (cCaseNE){"1", "12345678901", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"-2147483648", "2147483647" , -1},
            (cCaseNE){"-2147483648", "-2147483648" , 0},
            (cCaseNE){"2147483647", "-2147483648" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decCompareUTest32(){
    #define FUNCCALL decCompareAsUInt32
    const static char * testName = "decCompareAsUInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"4294967295", "4294967294", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"4294967295", "4294967295", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"4294967294", "4294967295", -1, 0}
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
            (cCase){"4294967296", "1", 0, 1},
            (cCase){"1", "4294967296", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decUInt32OrSmallerTest(){
    #define FUNCCALL decUInt32OrSmaller
    const static char * testName = "decUInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "12345678901", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "4294967295", -1},
            /* OverFlow to */
            (cCaseNE){"12345678901", "!1", 1},
            (cCaseNE){"12345678901", "4294967296", 0},
            (cCaseNE){"12345678901", "", -1},
            (cCaseNE){"12345678901", "4294967295", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "12345678901", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "4294967295", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "12345678901", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"4294967294", "4294967295" , -1},
            (cCaseNE){"4294967295", "4294967295" , 0},
            (cCaseNE){"4294967295", "4294967294" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToInt32FPTest(){
    #define FUNCCALL decToInt32FP
    const static char * testName = "decToInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_S(FUNCCALL, int32_t, 9, 10, optArray, ALEN(optArray), PRId32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_S(FUNCCALL, int32_t, 9, 10, 11, PRId32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_S(FUNCCALL, int32_t, 9, 10, 11, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32s tCase3[] = {
            (pfpCase32s){"2147483645", 0, 9, FN_OPT_NONE, 2147483645, 0},
            (pfpCase32s){"2147483645", 0, 9, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"+2147483645", 0, 10, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"-2147483647", 0, 10, FN_OPT_PFP_ALL, -2147483647, 0},
                       /* 0123456789012345678901234 */
            (pfpCase32s){"2147483647", 0, 9, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"2147483647", 0, 9, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+2147483647", 0, 10, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"-2147483648", 0, 10, FN_OPT_PFP_ALL, -2147483648, 0},
            (pfpCase32s){"002147483647", 0, 11, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"002147483647", 0, 11, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+000", 0, 3, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase32s){"-00002147483648", 0, 14, FN_OPT_PFP_ALL, -2147483648, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32s tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32s){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32s){"  12", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase32s){"   -2147483647", 0, 13, FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfpCase32s){"   -2147483648", 0, 13, FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfpCase32s){"    2147483647", 0, 13, FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfpCase32s){"   123  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32s){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32s){"12  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase32s){"-2147483647   ", 0, 13, FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfpCase32s){"-2147483648   ", 0, 13, FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfpCase32s){"2147483647    ", 0, 13, FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfpCase32s){" 12345  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32s){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32s){" -1 ", 0, 3, FN_PF_IGNORE_SPACES, -1, 0},
            (pfpCase32s){"   -000  ", 0, 8, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32s){"   -2147483647  ", 0, 15, FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfpCase32s){"   -2147483648  ", 0, 15, FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfpCase32s){"   2147483647   ", 0, 15, FN_PF_IGNORE_SPACES, 2147483647, 0},
            (pfpCase32s){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32s tCase5[] = {
            /* Underflow */
            (pfpCase32s){"-2147483649", 0, 10, FN_OPT_NONE, -214748364, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-21474836480", 0, 11, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-12345678901", 0, 11, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfpCase32s){"2147483648", 0, 9, FN_OPT_NONE, 214748364, FN_ERROR_OVERFLOW},
            (pfpCase32s){"21474836470", 0, 10, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"12345678901", 0, 10, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32s){":123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){":123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"1234567890/", 0, 10, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+1234567890/", 0, 11, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-1234567890/", 0, 11, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /*
             * Empty string: For Flexi FPs, any NULL character within
             * the segment will yield an FN_ERROR_INVALID_FORMAT error.
             * The only time an empty string error can be generate is
             * with "   " and with any of the skip spaces option turned
             * on, of which already tested.
             **/
            (pfpCase32s){"", 0, 0, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"", 0, 0, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 5", FUNCCALL, int32_t, tCase5, ALEN(tCase5), PRId32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Parse on error test loop and long check.");

        pfpCase32s tCase6[] = {
            /* Parse On Error */
            (pfpCase32s){"/1000000000", 0, 10, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+/1000000000", 0, 11, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-/1000000000", 0, 11, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"1234567890/", 0, 10, FN_PF_PARSE_ON_ERROR, 1234567890, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+1234567890/", 0, 11, FN_PF_PARSE_ON_ERROR, 1234567890, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-1234567890/", 0, 11, FN_PF_PARSE_ON_ERROR, -1234567890, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"2147483648:", 0, 10, FN_PF_PARSE_ON_ERROR, 214748364, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+2147483648:", 0, 11, FN_PF_PARSE_ON_ERROR, 214748364, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-2147483649:", 0, 11, FN_PF_PARSE_ON_ERROR, -214748364, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"2147483647/", 0, 10, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+2147483647/", 0, 11, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-2147483648/", 0, 11, FN_PF_PARSE_ON_ERROR, -2147483648, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"2147483650:", 0, 10, FN_PF_PARSE_ON_ERROR, 214748365, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+2147483650:", 0, 11, FN_PF_PARSE_ON_ERROR, 214748365, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-2147483650:", 0, 11, FN_PF_PARSE_ON_ERROR, -214748365, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"12345678901234567890/", 0, 20, FN_PF_PARSE_ON_ERROR, 1234567890, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+12345678901234567890/", 0, 21, FN_PF_PARSE_ON_ERROR, 1234567890, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-12345678901234567890/", 0, 21, FN_PF_PARSE_ON_ERROR, -1234567890, FN_ERROR_UNDERFLOW},
            /* Long Check */
            (pfpCase32s){":1234567890", 0, 10, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"1234567890/", 0, 10, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+1234567890/", 0, 11, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-1234567890/", 0, 11, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"1234567890:1234567890", 0, 20, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+1234567890:1234567890", 0, 21, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-1234567890:1234567890", 0, 21, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"1234567890:1234567890", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1234567890, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+1234567890:1234567890", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1234567890, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-1234567890:1234567890", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -1234567890, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"2147483650:2147483650", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748365, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+2147483650:2147483650", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748365, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-2147483650:2147483650", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -214748365, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"2147483648:2147483648", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748364, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+2147483648:2147483648", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748364, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-2147483649:2147483649", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -214748364, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"214748365092147483650", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748365, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+214748365092147483650", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748365, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-214748365092147483650", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -214748365, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"214748364892147483648", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748364, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+214748364892147483648", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         214748364, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-214748364992147483649", 0, 21, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -214748364, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"21474836479", 0, 10, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+21474836479", 0, 11, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-21474836489", 0, 11, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -2147483648, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, int32_t, tCase6, ALEN(tCase6), PRId32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase32s tCase7[] = {
            (pfpCase32s){"This number 12345678 is parseable.",
                         12, 19, FN_OPT_NONE, 12345678, 0},
            (pfpCase32s){"Number(123456789) to array.",
                         7, 15, FN_OPT_PFP_ALL, 123456789, 0},
            (pfpCase32s){"At least this one(-1234567890) with sign must pass.",
                         18, 28, FN_OPT_PFP_ALL, -1234567890, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase32s){"Important number:+2147483647(INT MAX VALUE)",
                         17, 27, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"Another one:-2147483648(INT32 MIN VALUE)",
                         12, 22, FN_OPT_PFP_ALL, -2147483648, 0},
            (pfpCase32s){"Parse after the seven 1234567145874125to last five",
                         29, 37, FN_OPT_PFP_ALL, 145874125, 0},
            (pfpCase32s){"From next space   -123456789    (to prior space)",
                         15, 31, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase32s){"Without any ingore spaces   -1234567890    with spaces parse will fail."
                         "And the segment considered to be overflow, or contain an invalid format"
                         "depends on FN_PF_LONG_CHECK",
                         25, 42, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 7", FUNCCALL, int32_t, tCase7, ALEN(tCase7), PRId32);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfpCase32s tCase8[] = {
            (pfpCase32s){"1", 1, 0, FN_OPT_NONE, 0, FN_ERROR_ILLEGAL_ARGS},
            (pfpCase32s){"1", 0, 1, FN_OPT_PFP_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFP_CASES_FATAL("Test 8", FUNCCALL, int32_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToUInt32FPTest(){
    #define FUNCCALL decToUInt32FP
    const static char * testName = "decToUInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_U(FUNCCALL, uint32_t, 9, 10, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_U(FUNCCALL, uint32_t, 9, 10, 11, PRIu32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_U(FUNCCALL, uint32_t, 9, 10, 11, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32u tCase3[] = {
            (pfpCase32u){"4294967294", 0, 9, FN_OPT_NONE, 4294967294U, 0},
            (pfpCase32u){"4294967294", 0, 9, FN_OPT_PFP_ALL, 4294967294U, 0},
            (pfpCase32u){"4294967295", 0, 9, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"4294967295", 0, 9, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"004294967295", 0, 11, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"004294967295", 0, 11, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"000", 0, 2, FN_OPT_PFP_ALL, 0, 0},
                       /* 012345678901234567890 */
            (pfpCase32u){"00004294967295", 0, 13, FN_OPT_NONE, 4294967295U, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32u tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32u){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32u){"  12", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase32u){"   4294967294", 0, 12, FN_PF_IGNORE_LSPACES, 4294967294U, 0},
            (pfpCase32u){"   4294967295", 0, 12, FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfpCase32u){"   123  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32u){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32u){"12  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase32u){"4294967294   ", 0, 12, FN_PF_IGNORE_TSPACES, 4294967294U, 0},
            (pfpCase32u){"4294967295   ", 0, 12, FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfpCase32u){" 12345  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32u){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32u){"   000  ", 0, 7, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32u){"   4294967294  ", 0, 14, FN_PF_IGNORE_SPACES, 4294967294U, 0},
            (pfpCase32u){"   4294967295  ", 0, 14, FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfpCase32u){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32u tCase5[] = {
            /* Overflow */
            (pfpCase32u){"4294967296", 0, 9, FN_OPT_NONE, 429496729U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"4294967300", 0, 9, FN_OPT_NONE, 429496730U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"42949672950", 0, 10, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"12345678901", 0, 15, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32u){":123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){":123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"1234567890/", 0, 10, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"+0", 0, 1, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"-0", 0, 1, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pfpCase32u){"", 0, 0, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"", 0, 0, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Parse on error test loop and long check.");

        pfpCase32u tCase6[] = {
            /* Parse On Error */
            (pfpCase32u){"/1000000000", 0, 10, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"1234567890:", 0, 10, FN_PF_PARSE_ON_ERROR, 1234567890U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"4294967296:", 0, 10, FN_PF_PARSE_ON_ERROR, 429496729U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"4294967295/", 0, 10, FN_PF_PARSE_ON_ERROR, 4294967295U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"4294967300:", 0, 10, FN_PF_PARSE_ON_ERROR, 429496730U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"12345678901234567890:", 0, 20, FN_PF_PARSE_ON_ERROR, 1234567890U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"+12345678901", 0, 11, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"-12345678901", 0, 11, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            /* Long Check */
            (pfpCase32u){":1234567890", 0, 10, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"1234567890/", 0, 10, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"1234567890:1234567890", 0, 20, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"1234567890:1234567890", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1234567890, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"4294967300:4294967300", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         429496730U, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"4294967296:4294967296", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         429496729U, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"429496730094294967300", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         429496730U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"429496729694294967296", 0, 20, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         429496729U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"42949672959", 0, 10, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         4294967295U, FN_ERROR_OVERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, uint32_t, tCase6, ALEN(tCase6), PRIu32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase32u tCase7[] = {
            (pfpCase32u){"This 1 is parseable.",
                       5, 5, FN_OPT_NONE, 1, 0},
            (pfpCase32u){"This number 12345678 is parseable.",
                       12, 19, FN_OPT_NONE, 12345678U, 0},
            (pfpCase32u){"Number(123456789) to array.",
                       7, 15, FN_OPT_PFP_ALL, 123456789U, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase32u){"Important number:+4294967295(UINT32 MAX VALUE), The + is not parsed.",
                       18, 27, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"Parse after the seven 1234567957412547to before first t",
                       29, 37, FN_OPT_PFP_ALL, 957412547U, 0},
            (pfpCase32u){"From next space   1234567890    (to prior space)",
                       15, 31, FN_OPT_PFP_ALL, 1234567890U, 0},
            (pfpCase32u){"Without any ingore spaces   1234567890    with spaces parse will fail."
                       "And the segment considered to be overflow, or contain an invalid format"
                       "depends on FN_PF_LONG_CHECK",
                       25, 41, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
        };

        MAKE_PFP_CASES_LOOP("Test 7", FUNCCALL, uint32_t, tCase7, ALEN(tCase7), PRIu32);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfpCase32u tCase8[] = {
            (pfpCase32u){"1", 1, 0, FN_OPT_NONE, 0, FN_ERROR_ILLEGAL_ARGS},
            (pfpCase32u){"1", 0, 1, FN_OPT_PFP_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFP_CASES_FATAL("Test 8", FUNCCALL, uint32_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToInt32FNTest(){
    #define FUNCCALL decToInt32FN
    const static char * testName = "decToInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_S(FUNCCALL, int32_t, 9, 10, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_S(FUNCCALL, int32_t, 9, 10, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_S(FUNCCALL, int32_t, 9, 9, PRId32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32s tCase4[] = {
            (pfnCase32s){"2147483645", FN_OPT_NONE, 2147483645, 0},
            (pfnCase32s){"2147483645", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"+2147483645", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"-2147483647", FN_OPT_PFN_ALL, -2147483647, 0},
            (pfnCase32s){"2147483647", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"2147483647", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+2147483647", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"-2147483648", FN_OPT_PFN_ALL, -2147483648, 0},
            (pfnCase32s){"002147483647", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"002147483647", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32s){"-00002147483648", FN_OPT_PFN_ALL, -2147483648, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32s tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32s){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32s){" 12", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase32s){"   -2147483647", FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfnCase32s){"   -2147483648", FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfnCase32s){"    2147483647", FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfnCase32s){"   123  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32s){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32s){"12  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase32s){"-2147483647   ", FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfnCase32s){"-2147483648   ", FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfnCase32s){"2147483647    ", FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfnCase32s){" 12345  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32s){"2147483650  ", FN_PF_IGNORE_TSPACES, 214748365, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+2147483650  ", FN_PF_IGNORE_TSPACES, 214748365, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-2147483650  ", FN_PF_IGNORE_TSPACES, -214748365, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"2147483648  ", FN_PF_IGNORE_TSPACES, 214748364, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+2147483648  ", FN_PF_IGNORE_TSPACES, 214748364, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-2147483649  ", FN_PF_IGNORE_TSPACES, -214748364, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"12345678909  ", FN_PF_IGNORE_TSPACES, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345678909  ", FN_PF_IGNORE_TSPACES, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345678909  ", FN_PF_IGNORE_TSPACES, -1234567890, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"2147483650:  ", FN_PF_IGNORE_TSPACES, 214748365, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+2147483650:  ", FN_PF_IGNORE_TSPACES, 214748365, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-2147483650:  ", FN_PF_IGNORE_TSPACES, -214748365, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"2147483648:  ", FN_PF_IGNORE_TSPACES, 214748364, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+2147483648:  ", FN_PF_IGNORE_TSPACES, 214748364, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-2147483649:  ", FN_PF_IGNORE_TSPACES, -214748364, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"12345678909:  ", FN_PF_IGNORE_TSPACES, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345678909:  ", FN_PF_IGNORE_TSPACES, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345678909:  ", FN_PF_IGNORE_TSPACES, -1234567890, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"123456789/  ", FN_PF_IGNORE_TSPACES, 123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"123456789:  ", FN_PF_IGNORE_TSPACES, 123456789, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483650  0", FN_PF_IGNORE_TSPACES, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483650  0", FN_PF_IGNORE_TSPACES, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483650  0", FN_PF_IGNORE_TSPACES, -214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483648  0", FN_PF_IGNORE_TSPACES, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483648  0", FN_PF_IGNORE_TSPACES, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483649  0", FN_PF_IGNORE_TSPACES, -214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1234567890  0", FN_PF_IGNORE_TSPACES, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+1234567890  0", FN_PF_IGNORE_TSPACES, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1234567890  0", FN_PF_IGNORE_TSPACES, -1234567890, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32s){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32s){" -1 ", FN_PF_IGNORE_SPACES, -1, 0},
            (pfnCase32s){"   -000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32s){"   -2147483647  ", FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfnCase32s){"   -2147483648  ", FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfnCase32s){"   2147483647       ", FN_PF_IGNORE_SPACES, 2147483647, 0},
            (pfnCase32s){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, int32_t, tCase5, ALEN(tCase5), PRId32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase32s tCase6[] = {
            /* @NOTE  Without option LONG_CHECK, after the maximum length an
             *        underflow or overflow error will alway be yielded if
             *        there are invalid digits and the invalid digits is not
             *        within the maximum length.
             **/
            /* Underflow */
            (pfnCase32s){"-2147483649", FN_OPT_NONE, -214748364, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-21474836489", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-12345678909", FN_OPT_NONE, -1234567890, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-1234567890:", FN_OPT_NONE, -1234567890, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-2147483648:", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-2147483650:", FN_OPT_NONE, -214748365, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-12345678909123456789:", FN_OPT_NONE, -1234567890, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfnCase32s){"2147483648", FN_OPT_NONE, 214748364, FN_ERROR_OVERFLOW},
            (pfnCase32s){"21474836479", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"12345678909", FN_OPT_NONE, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"1234567890:", FN_OPT_NONE, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"2147483647:", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"2147483650:", FN_OPT_NONE, 214748365, FN_ERROR_OVERFLOW},
            (pfnCase32s){"12345678909123456789:", FN_OPT_NONE, 1234567890, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32s){":123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){":123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1234567890:", FN_OPT_NONE, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+1234567890:", FN_OPT_NONE, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-1234567890:", FN_OPT_NONE, -1234567890, FN_ERROR_UNDERFLOW},
            /* Empty string */
            (pfnCase32s){"", FN_OPT_NONE, 0, FN_ERROR_EMPTY_STR},
            (pfnCase32s){"", FN_OPT_PFN_ALL, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 6", FUNCCALL, int32_t, tCase6, ALEN(tCase6), PRId32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Long check with and without IGNORE_TSPACES.");

        pfnCase32s tCase7[] = {
            /* With IGNORE_TSPACES */
            /* --> Overflow Check */
            (pfnCase32s){"21474836509  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748365, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+21474836509  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748365, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-21474836509  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -214748365, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"21474836489  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748364, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+21474836489  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748364, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-21474836499  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -214748364, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"12345678909  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345678909  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345678909  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1234567890, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"21474836500  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+21474836500  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-21474836500  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"21474836480  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+21474836480  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-21474836490  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345678900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345678900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345678900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1234567890, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32s){"2147483650  ", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483650  ", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483650  ", FN_PF_LONG_CHECK, -214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483648  ", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483648  ", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483649  ", FN_PF_LONG_CHECK, -214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345678900  ", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345678900  ", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345678900  ", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483650/  ", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483650/  ", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483650/  ", FN_PF_LONG_CHECK, -214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483648/  ", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483648/  ", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483649/  ", FN_PF_LONG_CHECK, -214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345678900/  ", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345678900/  ", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345678900/  ", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"21474836500:  ", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+21474836500:  ", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-21474836500:  ", FN_PF_LONG_CHECK, -214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"21474836480:  ", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+21474836480:  ", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-21474836490:  ", FN_PF_LONG_CHECK, -214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"123456789000:  ", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+123456789000:  ", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-123456789000:  ", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32s){"2147483650:", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483650:", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483650:", FN_PF_LONG_CHECK, -214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483648:", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483648:", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483649:", FN_PF_LONG_CHECK, -214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1234567890:", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+1234567890:", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1234567890:", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483650/", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483650/", FN_PF_LONG_CHECK, 214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483650/", FN_PF_LONG_CHECK, -214748365, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2147483648/", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2147483648/", FN_PF_LONG_CHECK, 214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2147483649/", FN_PF_LONG_CHECK, -214748364, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1234567890/", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+1234567890/", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1234567890/", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345678909", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345678909", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345678909", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"12345678901234567890:", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345678901234567890:", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345678901234567890:", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"123456789012345678909", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+123456789012345678909", FN_PF_LONG_CHECK, 1234567890, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-123456789012345678909", FN_PF_LONG_CHECK, -1234567890, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"21474836472147483647:", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+21474836472147483647:", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-21474836482147483648:", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"214748364721474836479", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+214748364721474836479", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-214748364821474836489", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFN_CASES_LOOP("Test 7", FUNCCALL, int32_t, tCase7, ALEN(tCase7), PRId32);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfnCase32s tCase8[] = {
            (pfnCase32s){"1", FN_OPT_PFN_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFN_CASES_FATAL("Test 8", FUNCCALL, int32_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToUInt32FNTest(){
    #define FUNCCALL decToUInt32FN
    const static char * testName = "decToUInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_U(FUNCCALL, uint32_t, 9, 10, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_U(FUNCCALL, uint32_t, 9, 10, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_U(FUNCCALL, uint32_t, 9, 9, PRIu32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32u tCase4[] = {
            (pfnCase32u){"4294967294", FN_OPT_NONE, 4294967294U, 0},
            (pfnCase32u){"4294967294", FN_OPT_PFN_ALL, 4294967294U, 0},
            (pfnCase32u){"4294967295", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"4294967295", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"004294967295", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"004294967295", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32u){"00004294967295", FN_OPT_PFN_ALL, 4294967295U, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32u tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32u){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32u){"  12", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase32u){"   4294967294", FN_PF_IGNORE_LSPACES, 4294967294U, 0},
            (pfnCase32u){"   4294967295", FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfnCase32u){"   123  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32u){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32u){"12  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase32u){"4294967294   ", FN_PF_IGNORE_TSPACES, 4294967294U, 0},
            (pfnCase32u){"4294967295   ", FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfnCase32u){" 12345  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32u){"4294967300  ", FN_PF_IGNORE_TSPACES, 429496730U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"4294967296  ", FN_PF_IGNORE_TSPACES, 429496729U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"12345678900  ", FN_PF_IGNORE_TSPACES, 1234567890U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"4294967300:  ", FN_PF_IGNORE_TSPACES, 429496730U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"4294967296:  ", FN_PF_IGNORE_TSPACES, 429496729U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"1234567890:  ", FN_PF_IGNORE_TSPACES, 1234567890U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"4294967300  0", FN_PF_IGNORE_TSPACES, 429496730U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4294967296  0", FN_PF_IGNORE_TSPACES, 429496729U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567890  0", FN_PF_IGNORE_TSPACES, 1234567890U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32u){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32u){"   000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32u){"   4294967294  ", FN_PF_IGNORE_SPACES, 4294967294U, 0},
            (pfnCase32u){"   4294967295  ", FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfnCase32u){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase32u tCase6[] = {
            /* Overflow */
            (pfnCase32u){"4294967296", FN_OPT_NONE, 429496729U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"4294967300", FN_OPT_NONE, 429496730U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"42949672950", FN_OPT_NONE, 4294967295U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"12345678901", FN_OPT_NONE, 1234567890U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32u){":123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){":123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567890/", FN_OPT_NONE, 1234567890U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"+0", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"-0", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            /* Empty string */
            (pfnCase32u){"", FN_OPT_NONE, 0, FN_ERROR_EMPTY_STR},
            (pfnCase32u){"", FN_OPT_PFN_ALL, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 6", FUNCCALL, uint32_t, tCase6, ALEN(tCase6), PRIu32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Long check with and without IGNORE_TSPACES.");

        pfnCase32u tCase7[] = {
            /* With IGNORE_TSPACES */
            /* --> Overflow Check */
            (pfnCase32u){"42949673009  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 429496730U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"42949672969  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 429496729U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"12345678909  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"42949673000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 429496730U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"42949672960  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 429496729U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345678900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32u){"4294967300  ", FN_PF_LONG_CHECK, 429496730U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4294967296  ", FN_PF_LONG_CHECK, 429496729U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567890  ", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4294967300/  ", FN_PF_LONG_CHECK, 429496730U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4294967296/  ", FN_PF_LONG_CHECK, 429496729U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567890/  ", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"42949673000:  ", FN_PF_LONG_CHECK, 429496730U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"42949672960:  ", FN_PF_LONG_CHECK, 429496729U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345678900:  ", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32u){"4294967300/", FN_PF_LONG_CHECK, 429496730U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4294967296/", FN_PF_LONG_CHECK, 429496729U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567890/", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4294967300:", FN_PF_LONG_CHECK, 429496730U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4294967296:", FN_PF_LONG_CHECK, 429496729U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567890:", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345678909", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"12345678901234567890:", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"123456789012345678909", FN_PF_LONG_CHECK, 1234567890U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"42949672954294967295:", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"429496729542949672959", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_OVERFLOW}
        };

        MAKE_PFN_CASES_LOOP("Test 7", FUNCCALL, uint32_t, tCase7, ALEN(tCase7), PRIu32);
        puts ("# Test 7: Passed.\n");
    } /* END Test 7 */

    { /* START Test 8 */
        puts ("# TEST 8: Fatal error test.");

        pfnCase32u tCase8[] = {
            (pfnCase32u){"1", FN_OPT_PFN_ALL + 1, 0, FN_ERROR_ILLEGAL_ARGS}
        };

        MAKE_PFN_CASES_FATAL("Test 8", FUNCCALL, uint32_t, tCase8, ALEN(tCase8));
        puts ("# Test 8: Passed.");
    } /* END Test 8 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToInt32C1Test(){
    #define FUNCCALL decToInt32C1
    const static char * testName = "decToInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_S(FUNCCALL, int32_t, 9, 10, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_S(FUNCCALL, int32_t, 9, 10, PRId32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_S(FUNCCALL, int32_t, 9, PRId32);
    /* END Test 2B */

    /*
     * e pointer = -1 = NULL.
     * {input str, opt, array e result, array e error, array e pointer, expected len}
     * {"1234 1234", opt, {1234, 1234}, {err, err}, {4,-1}, 2}
     *
     */
    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");

        pc1Case32s tCase3[] = {
            /* a */
            (pc1Case32s){"2147483645", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+2147483645", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+2147483645", FN_OPT_PC1_ALL, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"-2147483647", FN_OPT_NONE, {-2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-2147483647", FN_OPT_PC1_ALL, {-2147483647}, {0}, {-1}, 1},
            /* b */
            (pc1Case32s){"2147483647", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+2147483647", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+2147483647", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-2147483648", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-2147483648", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1},
            /* c */
            (pc1Case32s){"002147483647", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"002147483647", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_PC1_ALL, {0}, {0}, {-1}, 1},
            (pc1Case32s){"-00002147483648", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-00002147483648", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32s tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32s){"-+2147483645", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+-2147483645", FN_OPT_NONE, {-2147483645}, {0}, {-1}, 1},
            (pc1Case32s){":2147483645:", FN_OPT_NONE, {2147483645}, {0}, {11}, 1},
            (pc1Case32s){":+2147483645:", FN_OPT_NONE, {2147483645}, {0}, {12}, 1},
            (pc1Case32s){":-2147483645:", FN_OPT_NONE, {-2147483645}, {0}, {12}, 1},
            (pc1Case32s){":@#$%^&2147483645:@", FN_OPT_NONE, {2147483645}, {0}, {17}, 1},
            (pc1Case32s){":@#$%^&+2147483645:@", FN_OPT_NONE, {2147483645}, {0}, {18}, 1},
            (pc1Case32s){":@#$%^&-2147483645:@", FN_OPT_NONE, {-2147483645}, {0}, {18}, 1},
            (pc1Case32s){":@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32s){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32s){":2147483645", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32s){"2147483645:", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {10}, 1},
            (pc1Case32s){"+2147483645:", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {11}, 1},
            (pc1Case32s){"-2147483645:", FN_PC_NO_INVALID_SKIP, {-2147483645}, {0}, {11}, 1},
            (pc1Case32s){"^%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32s){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case32s tCase5[] = {
            /* Overflow default */
            /* --> Underflow */
            (pc1Case32s){"-2147483649", FN_OPT_NONE, {-214748364}, {0}, {10}, 1},
            (pc1Case32s){"-21474836499", FN_OPT_NONE, {-214748364}, {0}, {10}, 1},
            (pc1Case32s){"-21474836489", FN_OPT_NONE, {-2147483648}, {0}, {11}, 1},
            (pc1Case32s){"-2147483650", FN_OPT_NONE, {-214748365}, {0}, {10}, 1},
            (pc1Case32s){"-21474836509", FN_OPT_NONE, {-214748365}, {0}, {10}, 1},
            (pc1Case32s){"-12345678909", FN_OPT_NONE, {-1234567890}, {0}, {11}, 1},
            (pc1Case32s){"-123456789091234567890", FN_OPT_NONE, {-1234567890}, {0}, {11}, 1},
            /* --> Overflow */
            (pc1Case32s){"2147483648", FN_OPT_NONE, {214748364}, {0}, {9}, 1},
            (pc1Case32s){"21474836489", FN_OPT_NONE, {214748364}, {0}, {9}, 1},
            (pc1Case32s){"21474836479", FN_OPT_NONE, {2147483647}, {0}, {10}, 1},
            (pc1Case32s){"2147483650", FN_OPT_NONE, {214748365}, {0}, {9}, 1},
            (pc1Case32s){"21474836509", FN_OPT_NONE, {214748365}, {0}, {9}, 1},
            (pc1Case32s){"12345678909", FN_OPT_NONE, {1234567890}, {0}, {10}, 1},
            (pc1Case32s){"123456789091234567890", FN_OPT_NONE, {1234567890}, {0}, {10}, 1},
            /* OVERFLOW_ERROR opt */
            /* --> Underflow */
            (pc1Case32s){"-2147483649", FN_PC_OVERFLOW_ERROR, {-214748364}, {FN_ERROR_UNDERFLOW}, {10}, 1},
            (pc1Case32s){"-21474836499", FN_PC_OVERFLOW_ERROR, {-214748364}, {FN_ERROR_UNDERFLOW}, {10}, 1},
            (pc1Case32s){"-21474836489", FN_PC_OVERFLOW_ERROR, {-2147483648}, {FN_ERROR_UNDERFLOW}, {11}, 1},
            (pc1Case32s){"-2147483650", FN_PC_OVERFLOW_ERROR, {-214748365}, {FN_ERROR_UNDERFLOW}, {10}, 1},
            (pc1Case32s){"-21474836509", FN_PC_OVERFLOW_ERROR, {-214748365}, {FN_ERROR_UNDERFLOW}, {10}, 1},
            (pc1Case32s){"-12345678909", FN_PC_OVERFLOW_ERROR, {-1234567890}, {FN_ERROR_UNDERFLOW}, {11}, 1},
            (pc1Case32s){"-123456789091234567890", FN_PC_OVERFLOW_ERROR, {-1234567890}, {FN_ERROR_UNDERFLOW}, {11}, 1},
            /* --> Overflow */
            (pc1Case32s){"2147483648", FN_PC_OVERFLOW_ERROR, {214748364}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32s){"21474836489", FN_PC_OVERFLOW_ERROR, {214748364}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32s){"21474836479", FN_PC_OVERFLOW_ERROR, {2147483647}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32s){"2147483650", FN_PC_OVERFLOW_ERROR, {214748365}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32s){"21474836509", FN_PC_OVERFLOW_ERROR, {214748365}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32s){"12345678909", FN_PC_OVERFLOW_ERROR, {1234567890}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32s){"123456789091234567890", FN_PC_OVERFLOW_ERROR, {1234567890}, {FN_ERROR_OVERFLOW}, {10}, 1},
            /* OVERFLOW SKIP opt */
            /* --> Underflow */
            (pc1Case32s){"-2147483649", FN_PC_OVERFLOW_SKIP, {-214748364}, {0}, {-1}, 1},
            (pc1Case32s){"-21474836499", FN_PC_OVERFLOW_SKIP, {-214748364}, {0}, {-1}, 1},
            (pc1Case32s){"-21474836489", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-2147483650", FN_PC_OVERFLOW_SKIP, {-214748365}, {0}, {-1}, 1},
            (pc1Case32s){"-21474836509", FN_PC_OVERFLOW_SKIP, {-214748365}, {0}, {-1}, 1},
            (pc1Case32s){"-12345678909", FN_PC_OVERFLOW_SKIP, {-1234567890}, {0}, {-1}, 1},
            (pc1Case32s){"-123456789091234567890", FN_PC_OVERFLOW_SKIP, {-1234567890}, {0}, {-1}, 1},
            (pc1Case32s){"-2147483649:", FN_PC_OVERFLOW_SKIP, {-214748364}, {0}, {11}, 1},
            (pc1Case32s){"-21474836499:", FN_PC_OVERFLOW_SKIP, {-214748364}, {0}, {12}, 1},
            (pc1Case32s){"-21474836489:", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {12}, 1},
            (pc1Case32s){"-2147483650:", FN_PC_OVERFLOW_SKIP, {-214748365}, {0}, {11}, 1},
            (pc1Case32s){"-21474836509:", FN_PC_OVERFLOW_SKIP, {-214748365}, {0}, {12}, 1},
            (pc1Case32s){"-12345678909:", FN_PC_OVERFLOW_SKIP, {-1234567890}, {0}, {12}, 1},
            (pc1Case32s){"-123456789091234567890:", FN_PC_OVERFLOW_SKIP, {-1234567890}, {0}, {22}, 1},
            /* --> Overflow */
            (pc1Case32s){"2147483648", FN_PC_OVERFLOW_SKIP, {214748364}, {0}, {-1}, 1},
            (pc1Case32s){"21474836489", FN_PC_OVERFLOW_SKIP, {214748364}, {0}, {-1}, 1},
            (pc1Case32s){"21474836479", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"2147483650", FN_PC_OVERFLOW_SKIP, {214748365}, {0}, {-1}, 1},
            (pc1Case32s){"21474836509", FN_PC_OVERFLOW_SKIP, {214748365}, {0}, {-1}, 1},
            (pc1Case32s){"12345678909", FN_PC_OVERFLOW_SKIP, {1234567890}, {0}, {-1}, 1},
            (pc1Case32s){"123456789091234567890", FN_PC_OVERFLOW_SKIP, {1234567890}, {0}, {-1}, 1},
            (pc1Case32s){"2147483648:", FN_PC_OVERFLOW_SKIP, {214748364}, {0}, {10}, 1},
            (pc1Case32s){"21474836489:", FN_PC_OVERFLOW_SKIP, {214748364}, {0}, {11}, 1},
            (pc1Case32s){"21474836479:", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {11}, 1},
            (pc1Case32s){"2147483650:", FN_PC_OVERFLOW_SKIP, {214748365}, {0}, {10}, 1},
            (pc1Case32s){"21474836509:", FN_PC_OVERFLOW_SKIP, {214748365}, {0}, {11}, 1},
            (pc1Case32s){"12345678909:", FN_PC_OVERFLOW_SKIP, {1234567890}, {0}, {11}, 1},
            (pc1Case32s){"123456789091234567890:", FN_PC_OVERFLOW_SKIP, {1234567890}, {0}, {21}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32s){"1234567890/", FN_PC_OVERFLOW_ERROR, {1234567890}, {0}, {10}, 1},
            (pc1Case32s){"1234567890:", FN_PC_OVERFLOW_ERROR, {1234567890}, {0}, {10}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, int32_t, tCase5, ALEN(tCase5), PRId32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32s tCase6[] = {
            (pc1Case32s){"123 +478 -157 $120 $-120", FN_OPT_NONE,
                         {123, 478, -157, 120, -120},
                         {0,0,0,0,0},
                         {3,8,13,18,-1},
                         5},
            (pc1Case32s){"059 +012345678901234 -2147483648012 $120 $-2547812", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {59, 1234567890, -2147483648, 120, -2547812},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_UNDERFLOW, 0, 0},
                         {3,20,35,40,-1},
                         5}
        };

        MAKE_PC1_CASES_LOOP("Test 6", FUNCCALL, int32_t, tCase6, ALEN(tCase6), PRId32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Fatal error test.");

        pc1Case32s tCase7[] = {
            (pc1Case32s){"1", ~((unsigned int)FN_OPT_PC1_ALL) , {1}, {0}, {0}, 1}
        };

        MAKE_PC1_CASES_FATAL("Test 7", FUNCCALL, int32_t, tCase7, ALEN(tCase7));
        puts ("# Test 7: Passed.");
    } /* END Test 7 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int decToUInt32C1Test(){
    #define FUNCCALL decToUInt32C1
    const static char * testName = "decToUInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_U(FUNCCALL, uint32_t, 9, 10, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_U(FUNCCALL, uint32_t, 9, 10, PRIu32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_U(FUNCCALL, uint32_t, 9, PRIu32);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");
        /* -1 Check nextPTR pointer is NULL */
        pc1Case32u tCase3[] = {
            /* a */
            (pc1Case32u){"4294967294", FN_OPT_NONE, {4294967294U}, {0}, {-1}, 1},
            (pc1Case32u){"4294967294", FN_OPT_PC1_ALL, {4294967294U}, {0}, {-1}, 1},
            /* b */
            (pc1Case32u){"4294967295", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"4294967295", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            /* c */
            (pc1Case32u){"004294967295", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"004294967295", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32u){"00004294967295", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32u tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32u){"-1", FN_OPT_NONE, {1}, {0}, {-1}, 1},
            (pc1Case32u){":4294967294:", FN_OPT_NONE, {4294967294U}, {0}, {11}, 1},
            (pc1Case32u){":@#$%^&4294967294:@", FN_OPT_NONE, {4294967294U}, {0}, {17}, 1},
            (pc1Case32u){":@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32u){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32u){"+0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"-0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){":4294967294", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"4294967294:", FN_PC_NO_INVALID_SKIP, {4294967294U}, {0}, {10}, 1},
            (pc1Case32u){":%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case32u tCase5[] = {
            /* Overflow default */
            (pc1Case32u){"4294967296", FN_OPT_NONE, {429496729U}, {0}, {9}, 1},
            (pc1Case32u){"42949672969", FN_OPT_NONE, {429496729U}, {0}, {9}, 1},
            (pc1Case32u){"42949672959", FN_OPT_NONE, {4294967295U}, {0}, {10}, 1},
            (pc1Case32u){"4294967300", FN_OPT_NONE, {429496730U}, {0}, {9}, 1},
            (pc1Case32u){"42949673009", FN_OPT_NONE, {429496730U}, {0}, {9}, 1},
            (pc1Case32u){"12345678909", FN_OPT_NONE, {1234567890U}, {0}, {10}, 1},
            (pc1Case32u){"123456789091234567890", FN_OPT_NONE, {1234567890U}, {0}, {10}, 1},
            /* OVERFLOW_ERROR opt */
            (pc1Case32u){"4294967296", FN_PC_OVERFLOW_ERROR, {429496729U}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32u){"42949672969", FN_PC_OVERFLOW_ERROR, {429496729U}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32u){"42949672959", FN_PC_OVERFLOW_ERROR, {4294967295U}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32u){"4294967300", FN_PC_OVERFLOW_ERROR, {429496730U}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32u){"42949673009", FN_PC_OVERFLOW_ERROR, {429496730U}, {FN_ERROR_OVERFLOW}, {9}, 1},
            (pc1Case32u){"12345678909", FN_PC_OVERFLOW_ERROR, {1234567890U}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32u){"123456789091234567890", FN_PC_OVERFLOW_ERROR, {1234567890U}, {FN_ERROR_OVERFLOW}, {10}, 1},
            /* OVERFLOW SKIP opt */
            (pc1Case32u){"4294967296", FN_PC_OVERFLOW_SKIP, {429496729U}, {0}, {-1}, 1},
            (pc1Case32u){"42949672969", FN_PC_OVERFLOW_SKIP, {429496729U}, {0}, {-1}, 1},
            (pc1Case32u){"42949672959", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"4294967300", FN_PC_OVERFLOW_SKIP, {429496730U}, {0}, {-1}, 1},
            (pc1Case32u){"42949673009", FN_PC_OVERFLOW_SKIP, {429496730U}, {0}, {-1}, 1},
            (pc1Case32u){"12345678909", FN_PC_OVERFLOW_SKIP, {1234567890U}, {0}, {-1}, 1},
            (pc1Case32u){"123456789091234567890", FN_PC_OVERFLOW_SKIP, {1234567890U}, {0}, {-1}, 1},
            (pc1Case32u){"4294967296:", FN_PC_OVERFLOW_SKIP, {429496729U}, {0}, {10}, 1},
            (pc1Case32u){"42949672969:", FN_PC_OVERFLOW_SKIP, {429496729U}, {0}, {11}, 1},
            (pc1Case32u){"42949672959:", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {11}, 1},
            (pc1Case32u){"4294967300:", FN_PC_OVERFLOW_SKIP, {429496730U}, {0}, {10}, 1},
            (pc1Case32u){"42949673009:", FN_PC_OVERFLOW_SKIP, {429496730U}, {0}, {11}, 1},
            (pc1Case32u){"12345678909:", FN_PC_OVERFLOW_SKIP, {1234567890U}, {0}, {11}, 1},
            (pc1Case32u){"123456789091234567890:", FN_PC_OVERFLOW_SKIP, {1234567890U}, {0}, {21}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32u){"1234567890/", FN_PC_OVERFLOW_ERROR, {1234567890U}, {0}, {10}, 1},
            (pc1Case32u){"1234567890:", FN_PC_OVERFLOW_ERROR, {1234567890U}, {0}, {10}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32u tCase6[] = {
            (pc1Case32u){"123 5789 4874 $3294967295 & $874854", FN_OPT_NONE,
                         {123U, 5789U, 4874U, 3294967295U, 874854U},
                         {0,0,0,0,0},
                         {3,8,13,25,-1},
                         5},
            (pc1Case32u){"123 42949672950 12345678901234567890 $3294967295 & $874854", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {123U, 4294967295U, 1234567890U, 3294967295U, 874854U},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_OVERFLOW, 0, 0},
                         {3,15,36,48,-1},
                         5}
        };

        MAKE_PC1_CASES_LOOP("Test 6", FUNCCALL, uint32_t, tCase6, ALEN(tCase6), PRIu32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Fatal error test.");

        pc1Case32u tCase7[] = {
            (pc1Case32u){"1", ~((unsigned int)FN_OPT_PC1_ALL) , {1}, {0}, {0}, 1}
        };

        MAKE_PC1_CASES_FATAL("Test 7", FUNCCALL, uint32_t, tCase7, ALEN(tCase7));
        puts ("# Test 7: Passed.");
    } /* END Test 7 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}
