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
#include "../h/HexUtil32.h"
#include "../testlib/testlib.c"
#include "test.h"

int hexToInt32Test();
int hexToInt32TrueErrorTest();
int hexToUInt32Test();
int hexToUInt32TrueErrorTest();

int hexCompareTest32();
int hexInt32OrSmallerTest();
int hexCompareUTest32();
int hexUInt32OrSmallerTest();

int hexToInt32FPTest();
int hexToUInt32FPTest();
int hexToInt32FNTest();
int hexToUInt32FNTest();

int hexToInt32C1Test();
int hexToUInt32C1Test();

int main(void){
    if ( hexToInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( hexCompareTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexCompareUTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexUInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( hexToInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( hexToInt32C1Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( hexToUInt32C1Test() == 1 ) return 1;

    return 0;
}

int hexToInt32Test(){
    #define FUNCCALL hexToInt32
    const static char * testName = "hexToInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 15, 8, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 15, 8, FN_ERROR_GENERAL, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "7FFFFFFD",  2147483645, 0},
            (pCase32s){"+7FFFFFFD",  2147483645, 0},
            (pCase32s){"-7FFFFFFF", -2147483647, 0},
            (pCase32s){ "7FFFFFFF",  2147483647, 0},
            (pCase32s){"+7FFFFFFF",  2147483647, 0},
            (pCase32s){"-80000000", -2147483648, 0},
            (pCase32s){"007FFFFFFF", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-000080000000", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3) , PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-80000001", -134217728, 1},
            (pCase32s){"-800000000", -2147483648, 1},
            (pCase32s){"-1abcdeff0", -448585471, 1},
            (pCase32s){"-1ABCDEFF0", -448585471, 1},
            /* Overflow */
            (pCase32s){"80000000", 134217728, 1},
            (pCase32s){"7FFFFFFF0", 2147483647, 1},
            (pCase32s){"-1abcdeff0", -448585471, 1},
            (pCase32s){"-1ABCDEFF0", -448585471, 1},
            /* Invalid format */
            (pCase32s){"G123", 0, 1},
            (pCase32s){"-12345679g", -305419897, 1},
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

int hexToInt32TrueErrorTest(){
    #define FUNCCALL hexToInt32TrueError
    const static char * testName = "hexToInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 15, 8, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 15, 8, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "7FFFFFFD",  2147483645, 0},
            (pCase32s){"+7FFFFFFD",  2147483645, 0},
            (pCase32s){"-7FFFFFFF", -2147483647, 0},
            (pCase32s){ "7FFFFFFF",  2147483647, 0},
            (pCase32s){"+7FFFFFFF",  2147483647, 0},
            (pCase32s){"-80000000", -2147483648, 0},
            (pCase32s){"007FFFFFFF", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-000080000000", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-80000001", -134217728, FN_ERROR_UNDERFLOW},
            (pCase32s){"-80000000F", -2147483648, FN_ERROR_UNDERFLOW},
            (pCase32s){"-1abcdefff", -448585471, FN_ERROR_UNDERFLOW},
            (pCase32s){"-1ABCDEFFFABCDEFF0", -448585471, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pCase32s){"80000000", 134217728, FN_ERROR_OVERFLOW},
            (pCase32s){"7FFFFFFFF", 2147483647, FN_ERROR_OVERFLOW},
            (pCase32s){"1abcdefff", 448585471, FN_ERROR_OVERFLOW},
            (pCase32s){"1ABCDEFFFABCDEFF0", 448585471, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32s){"G123", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"12345679g", 305419897, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+12345679g", 305419897, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-12345679g", -305419897, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"80000000G", 134217728, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+80000000G", 134217728, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-80000001G", -134217728, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"7FFFFFFFG", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+7FFFFFFFG", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-80000000G", -2147483648, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"80000010G", 134217729, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+80000010G", 134217729, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-80000010G", -134217729, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"1234567912345679G", 305419897, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+1234567912345679G", 305419897, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-1234567912345679G", -305419897, FN_ERROR_INVALID_FORMAT},
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

int hexToUInt32Test(){
    #define FUNCCALL hexToUInt32
    const static char * testName = "hexToUInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 15, 8, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 15, 8, FN_ERROR_GENERAL, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"FFFFFFFE", 4294967294U, 0},
            (pCase32u){"FFFFFFFF", 4294967295U, 0},
            (pCase32u){"00FFFFFFFF", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"0000FFFFFFFF", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"100000000", 268435456U, 1},
            (pCase32u){"FFFFFFFF0", 4294967295U, 1},
            (pCase32u){"1abcdeff0", 448585471U, 1},
            (pCase32u){"1ABCDEFF0", 448585471U, 1},
            /* Invalid format */
            (pCase32u){"G213", 0, 1},
            (pCase32u){"12345679g", 305419897U, 1},
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

int hexToUInt32TrueErrorTest(){
    #define FUNCCALL hexToUInt32TrueError
    const static char * testName = "hexToUInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 15, 8, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 15, 8, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"FFFFFFFE", 4294967294U, 0},
            (pCase32u){"FFFFFFFF", 4294967295U, 0},
            (pCase32u){"00FFFFFFFF", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"0000FFFFFFFF", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"10000000F", 268435456U, FN_ERROR_OVERFLOW},
            (pCase32u){"FFFFFFFFF", 4294967295U, FN_ERROR_OVERFLOW},
            (pCase32u){"1abcdefff", 448585471U, FN_ERROR_OVERFLOW},
            (pCase32u){"1ABCDEFFF", 448585471U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32u){"G214", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"12345679g", 305419897U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"100000000G", 268435456U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"FFFFFFFFG", 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"100000010G", 268435457U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"1234567912345679G", 305419897U, FN_ERROR_INVALID_FORMAT},
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

int hexCompareTest32(){
    #define FUNCCALL hexCompareAsInt32
    const static char * testName = "hexCompareAsInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"7FFFFFFF", "-80000000", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"7FFFFFFF", "7FFFFFFF", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"-80000000", "7FFFFFFF", -1, 0}
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
            (cCase){"-80000001", "1", 0, 1},
            (cCase){"1", "80000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexInt32OrSmallerTest(){
    #define FUNCCALL hexInt32OrSmaller
    const static char * testName = "hexInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "-123456790", -1},
            (cCaseNE){"!1", "123456790", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "7FFFFFFF", -1},
            /* UnderFlow to */
            (cCaseNE){"-123456790", "!1", 1},
            (cCaseNE){"-123456790", "-80000001", 0},
            (cCaseNE){"-123456790", "123456790", -1},
            (cCaseNE){"-123456790", "", -1},
            (cCaseNE){"-123456790", "-80000000", -1},
            /* OverFlow to */
            (cCaseNE){"123456790", "!1", 1},
            (cCaseNE){"123456790", "-123456790", 1},
            (cCaseNE){"123456790", "80000000", 0},
            (cCaseNE){"123456790", "", -1},
            (cCaseNE){"123456790", "7FFFFFFF", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "-123456790", 1},
            (cCaseNE){"", "123456790", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "-80000000", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "-123456790", 1},
            (cCaseNE){"1", "123456790", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"-80000000", "7FFFFFFF" , -1},
            (cCaseNE){"-80000000", "-80000000" , 0},
            (cCaseNE){"7FFFFFFF", "-80000000" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexCompareUTest32(){
    #define FUNCCALL hexCompareAsUInt32
    const static char * testName = "hexCompareAsUInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"FFFFFFFF", "FFFFFFFE", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"FFFFFFFF", "FFFFFFFF", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"FFFFFFFE", "FFFFFFFF", -1, 0}
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
            (cCase){"100000000", "1", 0, 1},
            (cCase){"1", "100000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexUInt32OrSmallerTest(){
    #define FUNCCALL hexUInt32OrSmaller
    const static char * testName = "hexUInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "123456790", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "FFFFFFFF", -1},
            /* OverFlow to */
            (cCaseNE){"123456790", "!1", 1},
            (cCaseNE){"123456790", "100000000", 0},
            (cCaseNE){"123456790", "", -1},
            (cCaseNE){"123456790", "FFFFFFFF", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "123456790", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "FFFFFFFF", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "123456790", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"FFFFFFFE", "FFFFFFFF" , -1},
            (cCaseNE){"FFFFFFFF", "FFFFFFFF" , 0},
            (cCaseNE){"FFFFFFFF", "FFFFFFFE" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int hexToInt32FPTest(){
    #define FUNCCALL hexToInt32FP
    const static char * testName = "hexToInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_S(FUNCCALL, int32_t, 15, 8, optArray, ALEN(optArray), PRId32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_S(FUNCCALL, int32_t, 15, 8, 9, PRId32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_S(FUNCCALL, int32_t, 15, 8, 9, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32s tCase3[] = {
            (pfpCase32s){"7FFFFFFD", 0, 7, FN_OPT_NONE, 2147483645, 0},
            (pfpCase32s){"7FFFFFFD", 0, 7, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"+7FFFFFFD", 0, 8, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"-7FFFFFFF", 0, 8, FN_OPT_PFP_ALL, -2147483647, 0},
                       /* 0123456789012345678901234 */
            (pfpCase32s){"7FFFFFFF", 0, 7, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"7FFFFFFF", 0, 7, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+7FFFFFFF", 0, 8, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"-80000000", 0, 8, FN_OPT_PFP_ALL, -2147483648, 0},
            (pfpCase32s){"007FFFFFFF", 0, 9, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"007FFFFFFF", 0, 9, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+000", 0, 3, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase32s){"-000080000000", 0, 12, FN_OPT_PFP_ALL, -2147483648, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32s tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32s){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32s){"  25", 0, 3, FN_PF_IGNORE_LSPACES, 37, 0},
            (pfpCase32s){"   -7FFFFFFF", 0, 11, FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfpCase32s){"   -80000000", 0, 11, FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfpCase32s){"    7FFFFFFF", 0, 11, FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfpCase32s){"   512  ", 0, 7, FN_PF_IGNORE_LSPACES, 1298, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32s){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32s){"25  ", 0, 3, FN_PF_IGNORE_TSPACES, 37, 0},
            (pfpCase32s){"-7FFFFFFF   ", 0, 11, FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfpCase32s){"-80000000   ", 0, 11, FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfpCase32s){"7FFFFFFF    ", 0, 11, FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfpCase32s){" 10000  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32s){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32s){" -1 ", 0, 3, FN_PF_IGNORE_SPACES, -1, 0},
            (pfpCase32s){"   -000  ", 0, 8, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32s){"   -7FFFFFFF  ", 0, 13, FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfpCase32s){"   -80000000  ", 0, 13, FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfpCase32s){"   7FFFFFFF   ", 0, 13, FN_PF_IGNORE_SPACES, 2147483647, 0},
            (pfpCase32s){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32s tCase5[] = {
            /* Underflow */
            (pfpCase32s){"-80000001", 0, 8, FN_OPT_NONE, -134217728, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-800000000", 0, 9, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-123456790", 0, 9, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfpCase32s){"80000000", 0, 7, FN_OPT_NONE, 134217728, FN_ERROR_OVERFLOW},
            (pfpCase32s){"800000000", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"123456790", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32s){"G123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"G123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"12345679G", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+12345679G", 0, 9, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-12345679G", 0, 9, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
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
            (pfpCase32s){"G1abcdeff", 0, 8, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+G1abcdeff", 0, 9, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-G1abcdeff", 0, 9, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"1abcdeffG", 0, 8, FN_PF_PARSE_ON_ERROR, 448585471, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+1abcdeffG", 0, 9, FN_PF_PARSE_ON_ERROR, 448585471, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-1abcdeffG", 0, 9, FN_PF_PARSE_ON_ERROR, -448585471, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"1ABCDEFFG", 0, 8, FN_PF_PARSE_ON_ERROR, 448585471, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+1ABCDEFFG", 0, 9, FN_PF_PARSE_ON_ERROR, 448585471, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-1ABCDEFFG", 0, 9, FN_PF_PARSE_ON_ERROR, -448585471, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"80000000G", 0, 8, FN_PF_PARSE_ON_ERROR, 134217728, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+80000000G", 0, 9, FN_PF_PARSE_ON_ERROR, 134217728, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-80000001G", 0, 9, FN_PF_PARSE_ON_ERROR, -134217728, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"7FFFFFFFG", 0, 8, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+7FFFFFFFG", 0, 9, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-80000000G", 0, 9, FN_PF_PARSE_ON_ERROR, -2147483648, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"80000010G", 0, 8, FN_PF_PARSE_ON_ERROR, 134217729, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+80000010G", 0, 9, FN_PF_PARSE_ON_ERROR, 134217729, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-80000010G", 0, 9, FN_PF_PARSE_ON_ERROR, -134217729, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"12345679123456790G", 0, 17, FN_PF_PARSE_ON_ERROR, 305419897, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+12345679123456790G", 0, 18, FN_PF_PARSE_ON_ERROR, 305419897, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-12345679123456790G", 0, 18, FN_PF_PARSE_ON_ERROR, -305419897, FN_ERROR_UNDERFLOW},
            /* Long Check */
            (pfpCase32s){"g12345679", 0, 8, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"12345679G12345679", 0, 8, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+12345679G12345679", 0, 9, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-12345679G12345679", 0, 9, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"12345679G12345679", 0, 8, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         305419897, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+12345679G12345679", 0, 9, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         305419897, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-12345679G12345679", 0, 9, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -305419897, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"80000000G80000000", 0, 16, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         134217728, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+80000000G80000000", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         134217728, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-80000010G80000010", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -134217729, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-80000001G80000001", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -134217728, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"80000000F80000000", 0, 16, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         134217728, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+80000000F80000000", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         134217728, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-80000010F80000010", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -134217729, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-80000001F80000001", 0, 17, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -134217728, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"7FFFFFFFF", 0, 8, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+7FFFFFFFF", 0, 9, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-80000000F", 0, 9, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -2147483648, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, int32_t, tCase6, ALEN(tCase6), PRId32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase32s tCase7[] = {
            (pfpCase32s){"This number BC614E is parseable.",
                         12, 17, FN_OPT_NONE, 12345678, 0},
            (pfpCase32s){"Number(75BCD15) to array.",
                         7, 13, FN_OPT_PFP_ALL, 123456789, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase32s){"At least this one(-75BCD15) with sign must pass.",
                         18, 25, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase32s){"Important number:+7FFFFFFF(INT MAX VALUE)",
                         17, 25, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"Another one:-80000000(INT32 MIN VALUE)",
                         12, 20, FN_OPT_PFP_ALL, -2147483648, 0},
            (pfpCase32s){"Parse after the seven 12345678B1DCCD5to before the last five",
                         29, 35, FN_OPT_PFP_ALL, 145874125, 0},
            (pfpCase32s){"From next space   -75BCD15    (to prior space)",
                         15, 29, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase32s){"Without any ingore spaces   -499602D2    with spaces parse will fail."
                         "And the segment considered to be overflow, or contain an invalid format"
                         "depends on FN_PF_LONG_CHECK",
                         25, 40, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int hexToUInt32FPTest(){
    #define FUNCCALL hexToUInt32FP
    const static char * testName = "hexToUInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_U(FUNCCALL, uint32_t, 15, 8, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_U(FUNCCALL, uint32_t, 15, 8, 9, PRIu32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_U(FUNCCALL, uint32_t, 15, 8, 9, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32u tCase3[] = {
            (pfpCase32u){"FFFFFFFE", 0, 7, FN_OPT_NONE, 4294967294U, 0},
            (pfpCase32u){"FFFFFFFE", 0, 7, FN_OPT_PFP_ALL, 4294967294U, 0},
            (pfpCase32u){"FFFFFFFF", 0, 7, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"FFFFFFFF", 0, 7, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"00FFFFFFFF", 0, 9, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"00FFFFFFFF", 0, 9, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"000", 0, 2, FN_OPT_PFP_ALL, 0, 0},
                       /* 012345678901234567890 */
            (pfpCase32u){"0000FFFFFFFF", 0, 11, FN_OPT_NONE, 4294967295U, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32u tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32u){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32u){"  25", 0, 3, FN_PF_IGNORE_LSPACES, 37, 0},
            (pfpCase32u){"   FFFFFFFE", 0, 10, FN_PF_IGNORE_LSPACES, 4294967294U, 0},
            (pfpCase32u){"   FFFFFFFF", 0, 10, FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfpCase32u){"   512  ", 0, 7, FN_PF_IGNORE_LSPACES, 1298U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32u){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32u){"25  ", 0, 3, FN_PF_IGNORE_TSPACES, 37, 0},
            (pfpCase32u){"FFFFFFFE   ", 0, 10, FN_PF_IGNORE_TSPACES, 4294967294U, 0},
            (pfpCase32u){"FFFFFFFF   ", 0, 10, FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfpCase32u){" 10000  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32u){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32u){"   000  ", 0, 7, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32u){"   FFFFFFFE  ", 0, 12, FN_PF_IGNORE_SPACES, 4294967294U, 0},
            (pfpCase32u){"   FFFFFFFF  ", 0, 12, FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfpCase32u){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32u tCase5[] = {
            /* Overflow */
            (pfpCase32u){"100000000", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"100000010", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"FFFFFFFF0", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"123456790", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32u){"G123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"G123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"12345679G", 0, 8, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
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
             (pfpCase32u){"G10000000", 0, 8, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
             (pfpCase32u){"1abcdeffG", 0, 8, FN_PF_PARSE_ON_ERROR, 448585471U, FN_ERROR_OVERFLOW},
             (pfpCase32u){"1ABCDEFFG", 0, 8, FN_PF_PARSE_ON_ERROR, 448585471U, FN_ERROR_OVERFLOW},
             (pfpCase32u){"10000000G", 0, 8, FN_PF_PARSE_ON_ERROR, 268435456U, FN_ERROR_OVERFLOW},
             (pfpCase32u){"FFFFFFFFG", 0, 8, FN_PF_PARSE_ON_ERROR, 4294967295U, FN_ERROR_OVERFLOW},
             (pfpCase32u){"10000001G", 0, 8, FN_PF_PARSE_ON_ERROR, 268435457U, FN_ERROR_OVERFLOW},
             (pfpCase32u){"12345679123456790G", 0, 27, FN_PF_PARSE_ON_ERROR, 305419897U, FN_ERROR_OVERFLOW},
             (pfpCase32u){"+12345679", 0, 8, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
             (pfpCase32u){"-12345679", 0, 8, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
             /* Long Check */
             (pfpCase32u){"g12345679", 0, 8, FN_PF_LONG_CHECK,
                          0, FN_ERROR_INVALID_FORMAT},
             (pfpCase32u){"12345679G12345679", 0, 16, FN_PF_LONG_CHECK,
                          0, FN_ERROR_INVALID_FORMAT},
             (pfpCase32u){"12345679G12345679", 0, 16, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                          305419897U, FN_ERROR_INVALID_FORMAT},
             (pfpCase32u){"FFFFFFFFF", 0, 8, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
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
            (pfpCase32u){"This number BC614E is parseable.",
                       12, 17, FN_OPT_NONE, 12345678U, 0},
            (pfpCase32u){"Number(75BCD15) to array.",
                       7, 13, FN_OPT_PFP_ALL, 123456789U, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase32u){"Important number:+FFFFFFFF(UINT32 MAX VALUE), The + is not parsed.",
                       18, 25, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"Parse after the seven 1234573910F4C3to before first t",
                       28, 35, FN_OPT_PFP_ALL, 957412547U, 0},
            (pfpCase32u){"From next space   499602D2    (to prior space)",
                       15, 29, FN_OPT_PFP_ALL, 1234567890U, 0},
            (pfpCase32u){"Without any ingore spaces   499602D2    with spaces parse will fail."
                       "And the segment considered to be overflow, or contain an invalid format"
                       "depends on FN_PF_LONG_CHECK",
                       25, 39, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int hexToInt32FNTest(){
    #define FUNCCALL hexToInt32FN
    const static char * testName = "hexToInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_S(FUNCCALL, int32_t, 15, 8, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_S(FUNCCALL, int32_t, 15, 8, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_S(FUNCCALL, int32_t, 15, 7, PRId32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32s tCase4[] = {
            (pfnCase32s){"7FFFFFFD", FN_OPT_NONE, 2147483645, 0},
            (pfnCase32s){"7FFFFFFD", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"+7FFFFFFD", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"-7FFFFFFF", FN_OPT_PFN_ALL, -2147483647, 0},
            (pfnCase32s){"7FFFFFFF", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"7FFFFFFF", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+7FFFFFFF", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"-80000000", FN_OPT_PFN_ALL, -2147483648, 0},
            (pfnCase32s){"007FFFFFFF", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"007FFFFFFF", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32s){"-000080000000", FN_OPT_PFN_ALL, -2147483648, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32s tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32s){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32s){" 25", FN_PF_IGNORE_LSPACES, 37, 0},
            (pfnCase32s){"   -7FFFFFFF", FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfnCase32s){"   -80000000", FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfnCase32s){"    7FFFFFFF", FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfnCase32s){"   512  ", FN_PF_IGNORE_LSPACES, 1298, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32s){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32s){"25  ", FN_PF_IGNORE_TSPACES, 37, 0},
            (pfnCase32s){"-7FFFFFFF   ", FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfnCase32s){"-80000000   ", FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfnCase32s){"7FFFFFFF    ", FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfnCase32s){" 10000  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32s){"80000000  ", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+80000000  ", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-80000010  ", FN_PF_IGNORE_TSPACES, -134217729, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-80000001  ", FN_PF_IGNORE_TSPACES, -134217728, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"12345679F  ", FN_PF_IGNORE_TSPACES, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345679F  ", FN_PF_IGNORE_TSPACES, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345679F  ", FN_PF_IGNORE_TSPACES, -305419897, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"80000000G  ", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+80000000G  ", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-80000010G  ", FN_PF_IGNORE_TSPACES, -134217729, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-80000001G  ", FN_PF_IGNORE_TSPACES, -134217728, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"12345679G  ", FN_PF_IGNORE_TSPACES, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345679G  ", FN_PF_IGNORE_TSPACES, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345679G  ", FN_PF_IGNORE_TSPACES, -305419897, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"8000000G  ", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+8000000G  ", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-8000000G  ", FN_PF_IGNORE_TSPACES, -134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"80000000  0", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+80000000  0", FN_PF_IGNORE_TSPACES, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-80000010  0", FN_PF_IGNORE_TSPACES, -134217729, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-80000001  0", FN_PF_IGNORE_TSPACES, -134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345679F  0", FN_PF_IGNORE_TSPACES, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345679F  0", FN_PF_IGNORE_TSPACES, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345679F  0", FN_PF_IGNORE_TSPACES, -305419897, FN_ERROR_UNDERFLOW},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32s){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32s){" -1 ", FN_PF_IGNORE_SPACES, -1, 0},
            (pfnCase32s){"   -000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32s){"   -7FFFFFFF  ", FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfnCase32s){"   -80000000  ", FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfnCase32s){"   7FFFFFFF   ", FN_PF_IGNORE_SPACES, 2147483647, 0},
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
            (pfnCase32s){"-80000001", FN_OPT_NONE, -134217728, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-800000000", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-1abcdeff0", FN_OPT_NONE, -448585471, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-1abcdeffG", FN_OPT_NONE, -448585471, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-1ABCDEFF0", FN_OPT_NONE, -448585471, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-1ABCDEFFG", FN_OPT_NONE, -448585471, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-80000000G", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-80000010G", FN_OPT_NONE, -134217729, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-1234567912345679G", FN_OPT_NONE, -305419897, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfnCase32s){"80000000", FN_OPT_NONE, 134217728, FN_ERROR_OVERFLOW},
            (pfnCase32s){"7FFFFFFF0", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"1abcdeff0", FN_OPT_NONE, 448585471, FN_ERROR_OVERFLOW},
            (pfnCase32s){"1abcdeffG", FN_OPT_NONE, 448585471, FN_ERROR_OVERFLOW},
            (pfnCase32s){"1ABCDEFF0", FN_OPT_NONE, 448585471, FN_ERROR_OVERFLOW},
            (pfnCase32s){"1ABCDEFFG", FN_OPT_NONE, 448585471, FN_ERROR_OVERFLOW},
            (pfnCase32s){"7FFFFFFFG", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"80000010G", FN_OPT_NONE, 134217729, FN_ERROR_OVERFLOW},
            (pfnCase32s){"1234567912345679G", FN_OPT_NONE, 305419897, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32s){"G123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"G123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345679G", FN_OPT_NONE, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345679G", FN_OPT_NONE, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345679G", FN_OPT_NONE, -305419897, FN_ERROR_UNDERFLOW},
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
            (pfnCase32s){"80000000F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 134217728, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+80000000F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 134217728, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-80000010F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -134217729, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-80000001F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -134217728, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"12345679F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345679F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345679F  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -305419897, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"800000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+800000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-800000100 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -134217729, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-800000010 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"123456790 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+123456790 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-123456790 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"8000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+8000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-8000001000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -134217729, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-8000000100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1234567900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+1234567900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1234567900  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -305419897, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32s){"80000000  ", FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+80000000  ", FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-80000010  ", FN_PF_LONG_CHECK, -134217729, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-80000001  ", FN_PF_LONG_CHECK, -134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345679  ", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345679  ", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345679  ", FN_PF_LONG_CHECK, -305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"800000000  ", FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+800000000  ", FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-800000100  ", FN_PF_LONG_CHECK, -134217729, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-800000010  ", FN_PF_LONG_CHECK, -134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"123456790  ", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+123456790  ", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-123456790  ", FN_PF_LONG_CHECK, -305419897, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32s){"12345679G", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345679G", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345679G", FN_PF_LONG_CHECK, -305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345679F", FN_PF_LONG_CHECK, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345679F", FN_PF_LONG_CHECK, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345679F", FN_PF_LONG_CHECK, -305419897, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"80000000G", FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+80000000G", FN_PF_LONG_CHECK, 134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-80000010G", FN_PF_LONG_CHECK, -134217729, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-80000001G", FN_PF_LONG_CHECK, -134217728, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1234567912345679g", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+1234567912345679g", FN_PF_LONG_CHECK, 305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1234567912345679g", FN_PF_LONG_CHECK, -305419897, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345679123456790", FN_PF_LONG_CHECK, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345679123456790", FN_PF_LONG_CHECK, 305419897, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345679123456790", FN_PF_LONG_CHECK, -305419897, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"7FFFFFFF7FFFFFFFG", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+7FFFFFFF7FFFFFFFG", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-8000000080000000G", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"7FFFFFFF7FFFFFFF0", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+7FFFFFFF7FFFFFFF0", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-80000000800000000", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_UNDERFLOW}
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

int hexToUInt32FNTest(){
    #define FUNCCALL hexToUInt32FN
    const static char * testName = "hexToUInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_U(FUNCCALL, uint32_t, 15, 8, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_U(FUNCCALL, uint32_t, 15, 8, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_U(FUNCCALL, uint32_t, 15, 7, PRIu32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32u tCase4[] = {
            (pfnCase32u){"FFFFFFFE", FN_OPT_NONE, 4294967294U, 0},
            (pfnCase32u){"FFFFFFFE", FN_OPT_PFN_ALL, 4294967294U, 0},
            (pfnCase32u){"FFFFFFFF", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"FFFFFFFF", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"00FFFFFFFF", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"00FFFFFFFF", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32u){"0000FFFFFFFF", FN_OPT_PFN_ALL, 4294967295U, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32u tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32u){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32u){"  25", FN_PF_IGNORE_LSPACES, 37, 0},
            (pfnCase32u){"   FFFFFFFE", FN_PF_IGNORE_LSPACES, 4294967294U, 0},
            (pfnCase32u){"   FFFFFFFF", FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfnCase32u){"   512  ", FN_PF_IGNORE_LSPACES, 1298, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32u){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32u){"25  ", FN_PF_IGNORE_TSPACES, 37, 0},
            (pfnCase32u){"FFFFFFFE   ", FN_PF_IGNORE_TSPACES, 4294967294U, 0},
            (pfnCase32u){"FFFFFFFF   ", FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfnCase32u){" 12345  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32u){"FFFFFFFFF  ", FN_PF_IGNORE_TSPACES, 4294967295U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"FFFFFFFFG  ", FN_PF_IGNORE_TSPACES, 4294967295U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"FFFFFFFF  0", FN_PF_IGNORE_TSPACES, 4294967295U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32u){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32u){"   000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32u){"   FFFFFFFE  ", FN_PF_IGNORE_SPACES, 4294967294U, 0},
            (pfnCase32u){"   FFFFFFFF  ", FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfnCase32u){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase32u tCase6[] = {
            /* Overflow */
            (pfnCase32u){"100000000", FN_OPT_NONE, 268435456U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"100000010", FN_OPT_NONE, 268435457U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"FFFFFFFF0", FN_OPT_NONE, 4294967295U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"1abcdeff0", FN_OPT_NONE, 448585471U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"1ABCDEFF0", FN_OPT_NONE, 448585471U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32u){"G123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"G123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345679G", FN_OPT_NONE, 305419897U, FN_ERROR_OVERFLOW},
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
            (pfnCase32u){"FFFFFFFFF  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"FFFFFFFF 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"FFFFFFFF0  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32u){"FFFFFFFF  ", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"FFFFFFFFFG  ", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"FFFFFFFFFFG  ", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32u){"12345679G", FN_PF_LONG_CHECK, 305419897U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345679F", FN_PF_LONG_CHECK, 305419897U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"1234567912345679g", FN_PF_LONG_CHECK, 305419897U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567912345679F", FN_PF_LONG_CHECK, 305419897U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"FFFFFFFFFFFFFFFFG", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"FFFFFFFFFFFFFFFFF", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_OVERFLOW}
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

int hexToInt32C1Test(){
    #define FUNCCALL hexToInt32C1
    const static char * testName = "hexToInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_S(FUNCCALL, int32_t, 15, 8, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_S(FUNCCALL, int32_t, 15, 8, PRId32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_S(FUNCCALL, int32_t, 15, PRId32);
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
            (pc1Case32s){"7FFFFFFD", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+7FFFFFFD", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+7FFFFFFD", FN_OPT_PC1_ALL, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"-7FFFFFFF", FN_OPT_NONE, {-2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-7FFFFFFF", FN_OPT_PC1_ALL, {-2147483647}, {0}, {-1}, 1},
            /* b */
            (pc1Case32s){"7FFFFFFF", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+7FFFFFFF", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+7FFFFFFF", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-80000000", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-80000000", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1},
            /* c */
            (pc1Case32s){"007FFFFFFF", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"007FFFFFFF", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_PC1_ALL, {0}, {0}, {-1}, 1},
            (pc1Case32s){"-000080000000", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-000080000000", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32s tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32s){"-+7FFFFFFD", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+-7FFFFFFD", FN_OPT_NONE, {-2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"g7FFFFFFDg", FN_OPT_NONE, {2147483645}, {0}, {9}, 1},
            (pc1Case32s){"g+7FFFFFFDg", FN_OPT_NONE, {2147483645}, {0}, {10}, 1},
            (pc1Case32s){"g-7FFFFFFDg", FN_OPT_NONE, {-2147483645}, {0}, {10}, 1},
            (pc1Case32s){"G#$%^&7FFFFFFDG@", FN_OPT_NONE, {2147483645}, {0}, {14}, 1},
            (pc1Case32s){"G#$%^&+7FFFFFFDG@", FN_OPT_NONE, {2147483645}, {0}, {15}, 1},
            (pc1Case32s){"G#$%^&-7FFFFFFDG@", FN_OPT_NONE, {-2147483645}, {0}, {15}, 1},
            (pc1Case32s){"G#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32s){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32s){"g7FFFFFFD", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32s){"7FFFFFFDg", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {8}, 1},
            (pc1Case32s){"+7FFFFFFDG", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {9}, 1},
            (pc1Case32s){"-7FFFFFFDG", FN_PC_NO_INVALID_SKIP, {-2147483645}, {0}, {9}, 1},
            (pc1Case32s){"G%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
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
            (pc1Case32s){"-80000001", FN_OPT_NONE, {-134217728}, {0}, {8}, 1},
            (pc1Case32s){"-80000001F", FN_OPT_NONE, {-134217728}, {0}, {8}, 1},
            (pc1Case32s){"-80000000F", FN_OPT_NONE, {-2147483648}, {0}, {9}, 1},
            (pc1Case32s){"-80000010", FN_OPT_NONE, {-134217729}, {0}, {8}, 1},
            (pc1Case32s){"-80000010F", FN_OPT_NONE, {-134217729}, {0}, {8}, 1},
            (pc1Case32s){"-1abcdefff", FN_OPT_NONE, {-448585471}, {0}, {9}, 1},
            (pc1Case32s){"-1ABCDEFFF", FN_OPT_NONE, {-448585471}, {0}, {9}, 1},
            (pc1Case32s){"-12345679F", FN_OPT_NONE, {-305419897}, {0}, {9}, 1},
            (pc1Case32s){"-12345679F12345679", FN_OPT_NONE, {-305419897}, {0}, {9}, 1},
            /* --> Overflow */
            (pc1Case32s){"80000000", FN_OPT_NONE, {134217728}, {0}, {7}, 1},
            (pc1Case32s){"80000000F", FN_OPT_NONE, {134217728}, {0}, {7}, 1},
            (pc1Case32s){"7FFFFFFFF", FN_OPT_NONE, {2147483647}, {0}, {8}, 1},
            (pc1Case32s){"80000010", FN_OPT_NONE, {134217729}, {0}, {7}, 1},
            (pc1Case32s){"80000010F", FN_OPT_NONE, {134217729}, {0}, {7}, 1},
            (pc1Case32s){"1abcdefff", FN_OPT_NONE, {448585471}, {0}, {8}, 1},
            (pc1Case32s){"1ABCDEFFF", FN_OPT_NONE, {448585471}, {0}, {8}, 1},
            (pc1Case32s){"12345679F", FN_OPT_NONE, {305419897}, {0}, {8}, 1},
            (pc1Case32s){"12345679F12345679", FN_OPT_NONE, {305419897}, {0}, {8}, 1},
            /* OVERFLOW_ERROR opt */
            /* --> Underflow */
            (pc1Case32s){"-80000001", FN_PC_OVERFLOW_ERROR, {-134217728}, {FN_ERROR_UNDERFLOW}, {8}, 1},
            (pc1Case32s){"-80000001F", FN_PC_OVERFLOW_ERROR, {-134217728}, {FN_ERROR_UNDERFLOW}, {8}, 1},
            (pc1Case32s){"-80000000F", FN_PC_OVERFLOW_ERROR, {-2147483648}, {FN_ERROR_UNDERFLOW}, {9}, 1},
            (pc1Case32s){"-80000010", FN_PC_OVERFLOW_ERROR, {-134217729}, {FN_ERROR_UNDERFLOW}, {8}, 1},
            (pc1Case32s){"-80000010F", FN_PC_OVERFLOW_ERROR, {-134217729}, {FN_ERROR_UNDERFLOW}, {8}, 1},
            (pc1Case32s){"-1abcdefff", FN_PC_OVERFLOW_ERROR, {-448585471}, {FN_ERROR_UNDERFLOW}, {9}, 1},
            (pc1Case32s){"-1ABCDEFFF", FN_PC_OVERFLOW_ERROR, {-448585471}, {FN_ERROR_UNDERFLOW}, {9}, 1},
            (pc1Case32s){"-12345679F", FN_PC_OVERFLOW_ERROR, {-305419897}, {FN_ERROR_UNDERFLOW}, {9}, 1},
            (pc1Case32s){"-12345679F12345679", FN_PC_OVERFLOW_ERROR, {-305419897}, {FN_ERROR_UNDERFLOW}, {9}, 1},
            /* --> Overflow */
            (pc1Case32s){"80000000", FN_PC_OVERFLOW_ERROR, {134217728}, {FN_ERROR_OVERFLOW}, {7}, 1},
            (pc1Case32s){"80000000F", FN_PC_OVERFLOW_ERROR, {134217728}, {FN_ERROR_OVERFLOW}, {7}, 1},
            (pc1Case32s){"7FFFFFFFF", FN_PC_OVERFLOW_ERROR, {2147483647}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32s){"80000010", FN_PC_OVERFLOW_ERROR, {134217729}, {FN_ERROR_OVERFLOW}, {7}, 1},
            (pc1Case32s){"80000010F", FN_PC_OVERFLOW_ERROR, {134217729}, {FN_ERROR_OVERFLOW}, {7}, 1},
            (pc1Case32s){"1abcdefff", FN_PC_OVERFLOW_ERROR, {448585471}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32s){"1ABCDEFFF", FN_PC_OVERFLOW_ERROR, {448585471}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32s){"12345679F", FN_PC_OVERFLOW_ERROR, {305419897}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32s){"12345679F12345679", FN_PC_OVERFLOW_ERROR, {305419897}, {FN_ERROR_OVERFLOW}, {8}, 1},
            /* OVERFLOW SKIP opt */
            /* --> Underflow */
            (pc1Case32s){"-80000001", FN_PC_OVERFLOW_SKIP, {-134217728}, {0}, {-1}, 1},
            (pc1Case32s){"-80000001F", FN_PC_OVERFLOW_SKIP, {-134217728}, {0}, {-1}, 1},
            (pc1Case32s){"-80000000F", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-80000010", FN_PC_OVERFLOW_SKIP, {-134217729}, {0}, {-1}, 1},
            (pc1Case32s){"-80000010F", FN_PC_OVERFLOW_SKIP, {-134217729}, {0}, {-1}, 1},
            (pc1Case32s){"-1abcdefff", FN_PC_OVERFLOW_SKIP, {-448585471}, {0}, {-1}, 1},
            (pc1Case32s){"-1ABCDEFFF", FN_PC_OVERFLOW_SKIP, {-448585471}, {0}, {-1}, 1},
            (pc1Case32s){"-12345679F", FN_PC_OVERFLOW_SKIP, {-305419897}, {0}, {-1}, 1},
            (pc1Case32s){"-12345679F12345679", FN_PC_OVERFLOW_SKIP, {-305419897}, {0}, {-1}, 1},
            (pc1Case32s){"-80000001g", FN_PC_OVERFLOW_SKIP, {-134217728}, {0}, {9}, 1},
            (pc1Case32s){"-800000010G", FN_PC_OVERFLOW_SKIP, {-134217728}, {0}, {10}, 1},
            (pc1Case32s){"-800000000G", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {10}, 1},
            (pc1Case32s){"-80000010G", FN_PC_OVERFLOW_SKIP, {-134217729}, {0}, {9}, 1},
            (pc1Case32s){"-800000100G", FN_PC_OVERFLOW_SKIP, {-134217729}, {0}, {10}, 1},
            (pc1Case32s){"-1abcdeff0G", FN_PC_OVERFLOW_SKIP, {-448585471}, {0}, {10}, 1},
            (pc1Case32s){"-1ABCDEFF0G", FN_PC_OVERFLOW_SKIP, {-448585471}, {0}, {10}, 1},
            (pc1Case32s){"-123456790G", FN_PC_OVERFLOW_SKIP, {-305419897}, {0}, {10}, 1},
            (pc1Case32s){"-12345679123456790G", FN_PC_OVERFLOW_SKIP, {-305419897}, {0}, {18}, 1},
            /* --> Overflow */
            (pc1Case32s){"80000000", FN_PC_OVERFLOW_SKIP, {134217728}, {0}, {-1}, 1},
            (pc1Case32s){"80000000F", FN_PC_OVERFLOW_SKIP, {134217728}, {0}, {-1}, 1},
            (pc1Case32s){"7FFFFFFFF", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"80000010", FN_PC_OVERFLOW_SKIP, {134217729}, {0}, {-1}, 1},
            (pc1Case32s){"80000010F", FN_PC_OVERFLOW_SKIP, {134217729}, {0}, {-1}, 1},
            (pc1Case32s){"1abcdefff", FN_PC_OVERFLOW_SKIP, {448585471}, {0}, {-1}, 1},
            (pc1Case32s){"1ABCDEFFF", FN_PC_OVERFLOW_SKIP, {448585471}, {0}, {-1}, 1},
            (pc1Case32s){"12345679F", FN_PC_OVERFLOW_SKIP, {305419897}, {0}, {-1}, 1},
            (pc1Case32s){"12345679F12345679", FN_PC_OVERFLOW_SKIP, {305419897}, {0}, {-1}, 1},
            (pc1Case32s){"80000000g", FN_PC_OVERFLOW_SKIP, {134217728}, {0}, {8}, 1},
            (pc1Case32s){"800000000G", FN_PC_OVERFLOW_SKIP, {134217728}, {0}, {9}, 1},
            (pc1Case32s){"7FFFFFFF0G", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {9}, 1},
            (pc1Case32s){"80000010G", FN_PC_OVERFLOW_SKIP, {134217729}, {0}, {8}, 1},
            (pc1Case32s){"800000100G", FN_PC_OVERFLOW_SKIP, {134217729}, {0}, {9}, 1},
            (pc1Case32s){"1abcdeff0G", FN_PC_OVERFLOW_SKIP, {448585471}, {0}, {9}, 1},
            (pc1Case32s){"1ABCDEFF0G", FN_PC_OVERFLOW_SKIP, {448585471}, {0}, {9}, 1},
            (pc1Case32s){"123456790G", FN_PC_OVERFLOW_SKIP, {305419897}, {0}, {9}, 1},
            (pc1Case32s){"12345679123456790G", FN_PC_OVERFLOW_SKIP, {305419897}, {0}, {17}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32s){"12345679G", FN_PC_OVERFLOW_ERROR, {305419897}, {0}, {8}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, int32_t, tCase5, ALEN(tCase5), PRId32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32s tCase6[] = {
            (pc1Case32s){"7B +1DE -9D $78 $-78", FN_OPT_NONE,
                         {123, 478, -157, 120, -120},
                         {0,0,0,0,0},
                         {2,7,11,15,-1},
                         5},
            (pc1Case32s){"3B +1234567901 -80000000123 $78 $-26E064", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {59, 305419897, -2147483648, 120, -2547812},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_UNDERFLOW, 0, 0},
                         {2,14,27,31,-1},
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

int hexToUInt32C1Test(){
    #define FUNCCALL hexToUInt32C1
    const static char * testName = "hexToUInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_U(FUNCCALL, uint32_t, 15, 8, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_U(FUNCCALL, uint32_t, 15, 8, PRIu32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_U(FUNCCALL, uint32_t, 15, PRIu32);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");
        /* -1 Check nextPTR pointer is NULL */
        pc1Case32u tCase3[] = {
            /* a */
            (pc1Case32u){"FFFFFFFE", FN_OPT_NONE, {4294967294U}, {0}, {-1}, 1},
            (pc1Case32u){"FFFFFFFE", FN_OPT_PC1_ALL, {4294967294U}, {0}, {-1}, 1},
            /* b */
            (pc1Case32u){"FFFFFFFF", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"FFFFFFFF", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            /* c */
            (pc1Case32u){"00FFFFFFFF", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"00FFFFFFFF", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32u){"0000FFFFFFFF", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32u tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32u){"-1", FN_OPT_NONE, {1}, {0}, {-1}, 1},
            (pc1Case32u){"gFFFFFFFEg", FN_OPT_NONE, {4294967294U}, {0}, {9}, 1},
            (pc1Case32u){"G@#$%^&FFFFFFFEG@", FN_OPT_NONE, {4294967294U}, {0}, {15}, 1},
            (pc1Case32u){"G@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32u){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32u){"+0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"-0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"gFFFFFFFE", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"FFFFFFFEg", FN_PC_NO_INVALID_SKIP, {4294967294U}, {0}, {8}, 1},
            (pc1Case32u){"G%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case32u tCase5[] = {
            /* Overflow default */
            (pc1Case32u){"10000000F", FN_OPT_NONE, {268435456U}, {0}, {8}, 1},
            (pc1Case32u){"10000000F0", FN_OPT_NONE, {268435456U}, {0}, {8}, 1},
            (pc1Case32u){"FFFFFFFFF", FN_OPT_NONE, {4294967295U}, {0}, {8}, 1},
            (pc1Case32u){"10000001F", FN_OPT_NONE, {268435457U}, {0}, {8}, 1},
            (pc1Case32u){"10000001F0", FN_OPT_NONE, {268435457U}, {0}, {8}, 1},
            (pc1Case32u){"1abcdefff", FN_OPT_NONE, {448585471U}, {0}, {8}, 1},
            (pc1Case32u){"1ABCDEFFF", FN_OPT_NONE, {448585471U}, {0}, {8}, 1},
            (pc1Case32u){"12345679F", FN_OPT_NONE, {305419897U}, {0}, {8}, 1},
            (pc1Case32u){"12345679F12345679", FN_OPT_NONE, {305419897U}, {0}, {8}, 1},
            /* OVERFLOW_ERROR opt */
            (pc1Case32u){"10000000F", FN_PC_OVERFLOW_ERROR, {268435456U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"10000000F0", FN_PC_OVERFLOW_ERROR, {268435456U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"FFFFFFFFF", FN_PC_OVERFLOW_ERROR, {4294967295U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"10000001F", FN_PC_OVERFLOW_ERROR, {268435457U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"10000001F0", FN_PC_OVERFLOW_ERROR, {268435457U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"1abcdefff", FN_PC_OVERFLOW_ERROR, {448585471U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"1ABCDEFFF", FN_PC_OVERFLOW_ERROR, {448585471U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"12345679F", FN_PC_OVERFLOW_ERROR, {305419897U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            (pc1Case32u){"12345679F12345679", FN_PC_OVERFLOW_ERROR, {305419897U}, {FN_ERROR_OVERFLOW}, {8}, 1},
            /* OVERFLOW SKIP opt */
            (pc1Case32u){"10000000F", FN_PC_OVERFLOW_SKIP, {268435456U}, {0}, {-1}, 1},
            (pc1Case32u){"10000000F0", FN_PC_OVERFLOW_SKIP, {268435456U}, {0}, {-1}, 1},
            (pc1Case32u){"FFFFFFFFF", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"10000001F", FN_PC_OVERFLOW_SKIP, {268435457U}, {0}, {-1}, 1},
            (pc1Case32u){"10000001F0", FN_PC_OVERFLOW_SKIP, {268435457U}, {0}, {-1}, 1},
            (pc1Case32u){"1abcdefff", FN_PC_OVERFLOW_SKIP, {448585471U}, {0}, {-1}, 1},
            (pc1Case32u){"1ABCDEFFF", FN_PC_OVERFLOW_SKIP, {448585471U}, {0}, {-1}, 1},
            (pc1Case32u){"12345679F", FN_PC_OVERFLOW_SKIP, {305419897U}, {0}, {-1}, 1},
            (pc1Case32u){"12345679F12345679", FN_PC_OVERFLOW_SKIP, {305419897U}, {0}, {-1}, 1},
            (pc1Case32u){"100000000g", FN_PC_OVERFLOW_SKIP, {268435456U}, {0}, {9}, 1},
            (pc1Case32u){"1000000000G", FN_PC_OVERFLOW_SKIP, {268435456U}, {0}, {10}, 1},
            (pc1Case32u){"FFFFFFFF0G", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {9}, 1},
            (pc1Case32u){"100000010G", FN_PC_OVERFLOW_SKIP, {268435457U}, {0}, {9}, 1},
            (pc1Case32u){"1000000100G", FN_PC_OVERFLOW_SKIP, {268435457U}, {0}, {10}, 1},
            (pc1Case32u){"1abcdeff0G", FN_PC_OVERFLOW_SKIP, {448585471U}, {0}, {9}, 1},
            (pc1Case32u){"1ABCDEFF0G", FN_PC_OVERFLOW_SKIP, {448585471U}, {0}, {9}, 1},
            (pc1Case32u){"123456790G", FN_PC_OVERFLOW_SKIP, {305419897U}, {0}, {9}, 1},
            (pc1Case32u){"12345679123456790G", FN_PC_OVERFLOW_SKIP, {305419897U}, {0}, {17}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32u){"FFFFFFFFG", FN_PC_OVERFLOW_ERROR, {4294967295U}, {0}, {8}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32u tCase6[] = {
            (pc1Case32u){"7B 169D 130A $C46535FF & $D5930", FN_OPT_NONE,
                         {123U, 5789U, 4874U, 3294967295U, 874800U},
                         {0,0,0,0,0},
                         {2,7,12,22,-1},
                         5},
            (pc1Case32u){"7B FFFFFFFF0123 123456790123 $C46535FF & $D5930", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {123U, 4294967295U, 305419897U, 3294967295U, 874800U},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_OVERFLOW, 0, 0},
                         {2,15,28,38,-1},
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
