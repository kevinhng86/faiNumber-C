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
#include "../h/OctalUtil32.h"
#include "../testlib/testlib.c"
#include "test.h"

int octToInt32Test();
int octToInt32TrueErrorTest();
int octToUInt32Test();
int octToUInt32TrueErrorTest();

int octCompareTest32();
int octInt32OrSmallerTest();
int octCompareUTest32();
int octUInt32OrSmallerTest();

int octToInt32FPTest();
int octToUInt32FPTest();
int octToInt32FNTest();
int octToUInt32FNTest();

int octToInt32C1Test();
int octToUInt32C1Test();

int main(void){
    if ( octToInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( octCompareTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( octInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octCompareUTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( octUInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( octToInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( octToInt32C1Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt32C1Test() == 1 ) return 1;

    return 0;
}

int octToInt32Test(){
    #define FUNCCALL octToInt32
    const static char * testName = "octToInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 7, 11, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 7, 11, FN_ERROR_GENERAL, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "17777777775",  2147483645, 0},
            (pCase32s){"+17777777775",  2147483645, 0},
            (pCase32s){"-17777777777", -2147483647, 0},
            (pCase32s){ "17777777777",  2147483647, 0},
            (pCase32s){"+17777777777",  2147483647, 0},
            (pCase32s){"-20000000000", -2147483648, 0},
            (pCase32s){"0017777777777", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-000020000000000", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3) , PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-20000000001", -268435456, 1},
            (pCase32s){"-200000000000", -2147483648, 1},
            (pCase32s){"-123456701230", -1402433619, 1},
            /* Overflow */
            (pCase32s){"20000000000", 268435456, 1},
            (pCase32s){"177777777770", 2147483647, 1},
            (pCase32s){"123456701230", 1402433619, 1},
            /* Invalid format */
            (pCase32s){"8123", 0, 1},
            (pCase32s){"-123456701238", -1402433619, 1},
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

int octToInt32TrueErrorTest(){
    #define FUNCCALL octToInt32TrueError
    const static char * testName = "octToInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 7, 11, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 7, 11, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "17777777775",  2147483645, 0},
            (pCase32s){"+17777777775",  2147483645, 0},
            (pCase32s){"-17777777777", -2147483647, 0},
            (pCase32s){ "17777777777",  2147483647, 0},
            (pCase32s){"+17777777777",  2147483647, 0},
            (pCase32s){"-20000000000", -2147483648, 0},
            (pCase32s){"0017777777777", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-000020000000000", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-20000000001", -268435456, FN_ERROR_UNDERFLOW},
            (pCase32s){"-200000000007", -2147483648, FN_ERROR_UNDERFLOW},
            (pCase32s){"-123456701237", -1402433619, FN_ERROR_UNDERFLOW},
            (pCase32s){"-12345670123712345670123", -1402433619, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pCase32s){"20000000000", 268435456, FN_ERROR_OVERFLOW},
            (pCase32s){"177777777777", 2147483647, FN_ERROR_OVERFLOW},
            (pCase32s){"123456701237", 1402433619, FN_ERROR_OVERFLOW},
            (pCase32s){"12345670123712345670123", 1402433619, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32s){"8123", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"12345670123/", 1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+12345670123/", 1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-12345670123/", -1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"123456701238", 1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+123456701238", 1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-123456701238", -1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"200000000008", 268435456, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+200000000008", 268435456, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-200000000018", -268435456, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"177777777778", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+177777777778", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-200000000008", -2147483648, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"200000000008", 268435456, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+200000000008", 268435456, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-200000000108", -268435457, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"12345670123123456701238", 1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+12345670123123456701238", 1402433619, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-12345670123123456701238", -1402433619, FN_ERROR_INVALID_FORMAT},
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

int octToUInt32Test(){
    #define FUNCCALL octToUInt32
    const static char * testName = "octToUInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 7, 11, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 7, 11, FN_ERROR_GENERAL, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"37777777775", 4294967293U, 0},
            (pCase32u){"37777777777", 4294967295U, 0},
            (pCase32u){"0037777777777", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"000037777777777", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"40000000000", 536870912U, 1},
            (pCase32u){"377777777770", 4294967295U, 1},
            (pCase32u){"123456701230", 1402433619U, 1},
            /* Invalid format */
            (pCase32u){"8213", 0, 1},
            (pCase32u){"123456701238", 1402433619U, 1},
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

int octToUInt32TrueErrorTest(){
    #define FUNCCALL octToUInt32TrueError
    const static char * testName = "octToUInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 7, 11, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 7, 11, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"37777777775", 4294967293U, 0},
            (pCase32u){"37777777777", 4294967295U, 0},
            (pCase32u){"0037777777777", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"000037777777777", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"40000000000", 536870912U, FN_ERROR_OVERFLOW},
            (pCase32u){"377777777777", 4294967295U, FN_ERROR_OVERFLOW},
            (pCase32u){"123456701237", 1402433619U, FN_ERROR_OVERFLOW},
            (pCase32u){"12345670123712345670123", 1402433619U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32u){"8214", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"12345670123/", 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"123456701238", 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"400000000008", 536870912U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"377777777778", 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"400000000018", 536870912U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"123456701238", 1402433619U, FN_ERROR_INVALID_FORMAT},
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

int octCompareTest32(){
    #define FUNCCALL octCompareAsInt32
    const static char * testName = "octCompareAsInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"17777777777", "-20000000000", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"17777777777", "17777777777", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"-20000000000", "17777777777", -1, 0}
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
            (cCase){"-20000000001", "1", 0, 1},
            (cCase){"1", "20000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octInt32OrSmallerTest(){
    #define FUNCCALL octInt32OrSmaller
    const static char * testName = "octInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "-123456701230", -1},
            (cCaseNE){"!1", "123456701230", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "17777777777", -1},
            /* UnderFlow to */
            (cCaseNE){"-123456701230", "!1", 1},
            (cCaseNE){"-123456701230", "-20000000001", 0},
            (cCaseNE){"-123456701230", "123456701230", -1},
            (cCaseNE){"-123456701230", "", -1},
            (cCaseNE){"-123456701230", "-20000000000", -1},
            /* OverFlow to */
            (cCaseNE){"123456701230", "!1", 1},
            (cCaseNE){"123456701230", "-123456701230", 1},
            (cCaseNE){"123456701230", "20000000000", 0},
            (cCaseNE){"123456701230", "", -1},
            (cCaseNE){"123456701230", "17777777777", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "-123456701230", 1},
            (cCaseNE){"", "123456701230", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "-20000000000", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "-123456701230", 1},
            (cCaseNE){"1", "123456701230", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"-20000000000", "17777777777" , -1},
            (cCaseNE){"-20000000000", "-20000000000" , 0},
            (cCaseNE){"17777777777", "-20000000000" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octCompareUTest32(){
    #define FUNCCALL octCompareAsUInt32
    const static char * testName = "octCompareAsUInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"37777777777", "37777777775", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"37777777777", "37777777777", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"37777777775", "37777777777", -1, 0}
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
            (cCase){"40000000000", "1", 0, 1},
            (cCase){"1", "40000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octUInt32OrSmallerTest(){
    #define FUNCCALL octUInt32OrSmaller
    const static char * testName = "octUInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "123456701230", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "37777777777", -1},
            /* OverFlow to */
            (cCaseNE){"123456701230", "!1", 1},
            (cCaseNE){"123456701230", "40000000000", 0},
            (cCaseNE){"123456701230", "", -1},
            (cCaseNE){"123456701230", "37777777777", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "123456701230", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "37777777777", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "123456701230", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"37777777775", "37777777777" , -1},
            (cCaseNE){"37777777777", "37777777777" , 0},
            (cCaseNE){"37777777777", "37777777775" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octToInt32FPTest(){
    #define FUNCCALL octToInt32FP
    const static char * testName = "octToInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_S(FUNCCALL, int32_t, 7, 11, optArray, ALEN(optArray), PRId32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_S(FUNCCALL, int32_t, 7, 11, 12, PRId32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_S(FUNCCALL, int32_t, 7, 11, 12, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32s tCase3[] = {
            (pfpCase32s){"17777777775", 0, 10, FN_OPT_NONE, 2147483645, 0},
            (pfpCase32s){"17777777775", 0, 10, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"+17777777775", 0, 11, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"-17777777777", 0, 11, FN_OPT_PFP_ALL, -2147483647, 0},
            (pfpCase32s){"17777777777", 0, 10, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"17777777777", 0, 10, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+17777777777", 0, 11, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"-20000000000", 0, 11, FN_OPT_PFP_ALL, -2147483648, 0},
                       /* 0123456789012345678901234 */
            (pfpCase32s){"0017777777777", 0, 12, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"0017777777777", 0, 12, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+000", 0, 3, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase32s){"-000020000000000", 0, 15, FN_OPT_PFP_ALL, -2147483648, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32s tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32s){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32s){"  14", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase32s){"   -17777777777", 0, 14, FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfpCase32s){"   -20000000000", 0, 14, FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfpCase32s){"    17777777777", 0, 14, FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfpCase32s){"   173  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32s){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32s){"14  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase32s){"-17777777777   ", 0, 14, FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfpCase32s){"-20000000000   ", 0, 14, FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfpCase32s){"17777777777    ", 0, 14, FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfpCase32s){" 30071  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32s){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32s){" -1 ", 0, 3, FN_PF_IGNORE_SPACES, -1, 0},
            (pfpCase32s){"   -000  ", 0, 8, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32s){"  -17777777777  ", 0, 15, FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfpCase32s){"  -20000000000  ", 0, 15, FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfpCase32s){"  17777777777   ", 0, 15, FN_PF_IGNORE_SPACES, 2147483647, 0},
            (pfpCase32s){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32s tCase5[] = {
            /* Underflow */
            (pfpCase32s){"-20000000001", 0, 11, FN_OPT_NONE, -268435456, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-200000000000", 0, 12, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-123456701230", 0, 12, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfpCase32s){"20000000000", 0, 10, FN_OPT_NONE, 268435456, FN_ERROR_OVERFLOW},
            (pfpCase32s){"177777777770", 0, 11, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"123456701230", 0, 11, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32s){"8123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"8123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"123456701238", 0, 11, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+123456701238", 0, 12, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-123456701238", 0, 12, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Empty string */
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
            (pfpCase32s){"810000000000", 0, 11, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+810000000000", 0, 12, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-810000000000", 0, 12, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"123456701238", 0, 11, FN_PF_PARSE_ON_ERROR, 1402433619, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+123456701238", 0, 12, FN_PF_PARSE_ON_ERROR, 1402433619, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-123456701238", 0, 12, FN_PF_PARSE_ON_ERROR, -1402433619, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"200000000008", 0, 11, FN_PF_PARSE_ON_ERROR, 268435456, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+200000000008", 0, 12, FN_PF_PARSE_ON_ERROR, 268435456, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-200000000018", 0, 12, FN_PF_PARSE_ON_ERROR, -268435456, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"177777777778", 0, 11, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+177777777778", 0, 12, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-200000000008", 0, 12, FN_PF_PARSE_ON_ERROR, -2147483648, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"200000000018", 0, 11, FN_PF_PARSE_ON_ERROR, 268435456, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+200000000008", 0, 12, FN_PF_PARSE_ON_ERROR, 268435456, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-200000000108", 0, 12, FN_PF_PARSE_ON_ERROR, -268435457, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"12345670123123456701238", 0, 22, FN_PF_PARSE_ON_ERROR, 1402433619, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+12345670123123456701238", 0, 23, FN_PF_PARSE_ON_ERROR, 1402433619, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-12345670123123456701238", 0, 23, FN_PF_PARSE_ON_ERROR, -1402433619, FN_ERROR_UNDERFLOW},
            /* Long Check */
            (pfpCase32s){"812345670123", 0, 11, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"12345670123/", 0, 11, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"12345670123812345670123", 0, 22, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+12345670123812345670123", 0, 23, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-12345670123812345670123", 0, 23, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"12345670123812345670123", 0, 22, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1402433619, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+12345670123812345670123", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1402433619, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-12345670123812345670123", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -1402433619, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"20000000000820000000000", 0, 22, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         268435456, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+20000000000820000000000", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         268435456, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-20000000010820000000010", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -268435457, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-20000000001820000000001", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -268435456, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"20000000000720000000000", 0, 22, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         268435456, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+20000000000720000000000", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         268435456, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-20000000010720000000010", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -268435457, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-20000000001720000000001", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -268435456, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"+177777777777", 0, 12, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-200000000007", 0, 12, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -2147483648, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, int32_t, tCase6, ALEN(tCase6), PRId32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase32s tCase7[] = {
            (pfpCase32s){"This number 57060515 is parseable.",
                         12, 19, FN_OPT_NONE, 12345677, 0},
            (pfpCase32s){"Number(726746425) to array.",
                         7, 15, FN_OPT_PFP_ALL, 123456789, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase32s){"At least this one(-11145401322) with sign must pass.",
                         18, 29, FN_OPT_PFP_ALL, -1234567890, 0},
            (pfpCase32s){"Important number:+17777777777(INT MAX VALUE)",
                         17, 28, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"Another one:-20000000000(INT32 MIN VALUE)",
                         12, 23, FN_OPT_PFP_ALL, -2147483648, 0},
            (pfpCase32s){"Parse after the seven 123456710543563155to last five",
                         29, 38, FN_OPT_PFP_ALL, 145874125, 0},
            (pfpCase32s){"From next space   -726746425    (to prior space)",
                         15, 31, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase32s){"Without any ingore spaces   -11145401322    with spaces parse will fail."
                         "And the segment considered to be overflow, or contain an invalid format"
                         "depends on FN_PF_LONG_CHECK",
                         25, 43, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int octToUInt32FPTest(){
    #define FUNCCALL octToUInt32FP
    const static char * testName = "octToUInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_U(FUNCCALL, uint32_t, 7, 11, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_U(FUNCCALL, uint32_t, 7, 11, 12, PRIu32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_U(FUNCCALL, uint32_t, 7, 11, 12, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32u tCase3[] = {
            (pfpCase32u){"37777777775", 0, 10, FN_OPT_NONE, 4294967293U, 0},
            (pfpCase32u){"37777777775", 0, 10, FN_OPT_PFP_ALL, 4294967293U, 0},
            (pfpCase32u){"37777777777", 0, 10, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"37777777777", 0, 10, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"0037777777777", 0, 12, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"0037777777777", 0, 12, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"000", 0, 2, FN_OPT_PFP_ALL, 0, 0},
                       /* 012345678901234567890 */
            (pfpCase32u){"000037777777777", 0, 14, FN_OPT_NONE, 4294967295U, 0}

        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32u tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32u){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32u){"  14", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase32u){"   37777777775", 0, 13, FN_PF_IGNORE_LSPACES, 4294967293U, 0},
            (pfpCase32u){"   37777777777", 0, 13, FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfpCase32u){"   173  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32u){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32u){"14  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase32u){"37777777775   ", 0, 13, FN_PF_IGNORE_TSPACES, 4294967293U, 0},
            (pfpCase32u){"37777777777   ", 0, 13, FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfpCase32u){" 30071  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32u){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32u){"   000  ", 0, 7, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32u){"   37777777775  ", 0, 15, FN_PF_IGNORE_SPACES, 4294967293U, 0},
            (pfpCase32u){"   37777777777  ", 0, 15, FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfpCase32u){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32u tCase5[] = {
            /* Overflow */
            (pfpCase32u){"40000000000", 0, 10, FN_OPT_NONE, 536870912U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"40000000010", 0, 10, FN_OPT_NONE, 536870913U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"377777777770", 0, 11, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"12345670123123456701230", 0, 22, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32u){"8123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"8123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"123456701238", 0, 11, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
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
            (pfpCase32u){"810000000000", 0, 11, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"123456701238", 0, 11, FN_PF_PARSE_ON_ERROR, 1402433619U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"400000000018", 0, 11, FN_PF_PARSE_ON_ERROR, 536870912U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"377777777778", 0, 11, FN_PF_PARSE_ON_ERROR, 4294967295U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"400000000108", 0, 11, FN_PF_PARSE_ON_ERROR, 536870913U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"12345670123123456701238", 0, 22, FN_PF_PARSE_ON_ERROR, 1402433619U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"+123456701230", 0, 12, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"-123456701230", 0, 12, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            /* Long Check */
            (pfpCase32u){"812345670123", 0, 11, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"12345670123/", 0, 11, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"12345670123812345670123", 0, 22, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"12345670123812345670123", 0, 22, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1402433619U, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"40000000000840000000000", 0, 22, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         536870912U, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"40000000000740000000000", 0, 22, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         536870912U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"377777777777", 0, 11, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
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
            (pfpCase32u){"This number 57060515 is parseable.",
                       12, 19, FN_OPT_NONE, 12345677U, 0},
            (pfpCase32u){"Number(726746425) to array.",
                       7, 15, FN_OPT_PFP_ALL, 123456789U, 0},
                       /* 012345678901234567890123456789012345678901234567890 */
            (pfpCase32u){"Important number:+37777777777(UINT32 MAX VALUE), The + is not parsed.",
                       18, 28, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"Parse after the seven 12345677104172303to before first t",
                       29, 38, FN_OPT_PFP_ALL, 957412547U, 0},
            (pfpCase32u){"From next space   11145401322    (to prior space)",
                       15, 32, FN_OPT_PFP_ALL, 1234567890U, 0},
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

int octToInt32FNTest(){
    #define FUNCCALL octToInt32FN
    const static char * testName = "octToInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_S(FUNCCALL, int32_t, 7, 11, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_S(FUNCCALL, int32_t, 7, 11, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_S(FUNCCALL, int32_t, 7, 10, PRId32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32s tCase4[] = {
            (pfnCase32s){"17777777775", FN_OPT_NONE, 2147483645, 0},
            (pfnCase32s){"17777777775", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"+17777777775", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"-17777777777", FN_OPT_PFN_ALL, -2147483647, 0},
            (pfnCase32s){"17777777777", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"17777777777", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+17777777777", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"-20000000000", FN_OPT_PFN_ALL, -2147483648, 0},
            (pfnCase32s){"0017777777777", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"0017777777777", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32s){"-000020000000000", FN_OPT_PFN_ALL, -2147483648, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32s tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32s){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32s){" 14", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase32s){"   -17777777777", FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfnCase32s){"   -20000000000", FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfnCase32s){"    17777777777", FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfnCase32s){"   173  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32s){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32s){"14  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase32s){"-17777777777   ", FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfnCase32s){"-20000000000   ", FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfnCase32s){"17777777777    ", FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfnCase32s){" 30071  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32s){"20000000000  ", FN_PF_IGNORE_TSPACES, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+20000000000  ", FN_PF_IGNORE_TSPACES, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-20000000010  ", FN_PF_IGNORE_TSPACES, -268435457, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-20000000001  ", FN_PF_IGNORE_TSPACES, -268435456, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"200000000008  ", FN_PF_IGNORE_TSPACES, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+200000000008  ", FN_PF_IGNORE_TSPACES, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-200000000108  ", FN_PF_IGNORE_TSPACES, -268435457, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-200000000018  ", FN_PF_IGNORE_TSPACES, -268435456, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"1234567012/  ", FN_PF_IGNORE_TSPACES, 175304202, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345670128  ", FN_PF_IGNORE_TSPACES, 175304202, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"20000000000  0", FN_PF_IGNORE_TSPACES, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+20000000000  0", FN_PF_IGNORE_TSPACES, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000010  0", FN_PF_IGNORE_TSPACES, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000001  0", FN_PF_IGNORE_TSPACES, -268435456, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32s){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32s){" -1 ", FN_PF_IGNORE_SPACES, -1, 0},
            (pfnCase32s){"   -000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32s){"   -17777777777  ", FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfnCase32s){"   -20000000000  ", FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfnCase32s){"   17777777777       ", FN_PF_IGNORE_SPACES, 2147483647, 0},
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
            (pfnCase32s){"-20000000001", FN_OPT_NONE, -268435456, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-200000000000", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-123456701230", FN_OPT_NONE, -1402433619, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-123456701238", FN_OPT_NONE, -1402433619, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-200000000008", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-200000000108", FN_OPT_NONE, -268435457, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-12345670123123456701238", FN_OPT_NONE, -1402433619, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfnCase32s){"20000000000", FN_OPT_NONE, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"177777777770", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"123456701238", FN_OPT_NONE, 1402433619, FN_ERROR_OVERFLOW},
            (pfnCase32s){"123456701238", FN_OPT_NONE, 1402433619, FN_ERROR_OVERFLOW},
            (pfnCase32s){"177777777778", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"200000000018", FN_OPT_NONE, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"12345670123123456701238", FN_OPT_NONE, 1402433619, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32s){"8123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"8123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"123456701238", FN_OPT_NONE, 1402433619, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+123456701238", FN_OPT_NONE, 1402433619, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-123456701238", FN_OPT_NONE, -1402433619, FN_ERROR_UNDERFLOW},
            /* Empty string */
            (pfnCase32s){"", FN_OPT_NONE, 0, FN_ERROR_EMPTY_STR},
            (pfnCase32s){"", FN_OPT_PFN_ALL, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 6", FUNCCALL, int32_t, tCase6, ALEN(tCase6), PRId32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 7 */

    { /* START Test 7 */
        puts ("# TEST 7: Long check with and without IGNORE_TSPACES.");

        pfnCase32s tCase7[] = {
            /* With IGNORE_TSPACES */
            /* --> Overflow Check */
            (pfnCase32s){"200000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+200000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 268435456, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-200000000107  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -268435457, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-200000000017  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -268435456, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-200000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -2147483648, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"200000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+200000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000100 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000010 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2000000001000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2000000000100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32s){"20000000000  ", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+20000000000  ", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000010  ", FN_PF_LONG_CHECK, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000001  ", FN_PF_LONG_CHECK, -268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000000  ", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"200000000002  ", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+200000000002  ", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000102  ", FN_PF_LONG_CHECK, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000012  ", FN_PF_LONG_CHECK, -268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000002  ", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2000000000002  ", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+2000000000002  ", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2000000001002  ", FN_PF_LONG_CHECK, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2000000000102  ", FN_PF_LONG_CHECK, -268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-2000000000002  ", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32s){"20000000000/", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+20000000000/", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000010/", FN_PF_LONG_CHECK, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000001/", FN_PF_LONG_CHECK, -268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"200000000008", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+200000000008", FN_PF_LONG_CHECK, 268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000108", FN_PF_LONG_CHECK, -268435457, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-200000000018", FN_PF_LONG_CHECK, -268435456, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345670123/", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345670123/", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345670123/", FN_PF_LONG_CHECK, -1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"123456701238", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+123456701238", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-123456701238", FN_PF_LONG_CHECK, -1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345670123123456701238", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+12345670123123456701238", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-12345670123123456701238", FN_PF_LONG_CHECK, -1402433619, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"12345670123123456701237", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+12345670123123456701237", FN_PF_LONG_CHECK, 1402433619, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-12345670123123456701237", FN_PF_LONG_CHECK, -1402433619, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"17777777777177777777778", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+17777777777177777777778", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-20000000000200000000008", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"17777777777177777777777", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+17777777777177777777777", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-20000000000200000000007", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_UNDERFLOW}
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

int octToUInt32FNTest(){
    #define FUNCCALL octToUInt32FN
    const static char * testName = "octToUInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_U(FUNCCALL, uint32_t, 7, 11, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_U(FUNCCALL, uint32_t, 7, 11, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_U(FUNCCALL, uint32_t, 7, 10, PRIu32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32u tCase4[] = {
            (pfnCase32u){"37777777775", FN_OPT_NONE, 4294967293U, 0},
            (pfnCase32u){"37777777775", FN_OPT_PFN_ALL, 4294967293U, 0},
            (pfnCase32u){"37777777777", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"37777777777", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"0037777777777", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"0037777777777", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32u){"000037777777777", FN_OPT_PFN_ALL, 4294967295U, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32u tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32u){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32u){"  14", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase32u){"   37777777775", FN_PF_IGNORE_LSPACES, 4294967293U, 0},
            (pfnCase32u){"   37777777777", FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfnCase32u){"   173  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32u){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32u){"14  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase32u){"37777777775   ", FN_PF_IGNORE_TSPACES, 4294967293U, 0},
            (pfnCase32u){"37777777777   ", FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfnCase32u){" 30071  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32u){"40000000000  ", FN_PF_IGNORE_TSPACES, 536870912U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"400000000008  ", FN_PF_IGNORE_TSPACES, 536870912U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"40000000000  0", FN_PF_IGNORE_TSPACES, 536870912U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32u){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32u){"   000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32u){"   37777777775  ", FN_PF_IGNORE_SPACES, 4294967293U, 0},
            (pfnCase32u){"   37777777777  ", FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfnCase32u){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase32u tCase6[] = {
            /* Overflow */
            (pfnCase32u){"40000000000", FN_OPT_NONE, 536870912U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"40000000010", FN_OPT_NONE, 536870913U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"377777777770", FN_OPT_NONE, 4294967295U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"123456701230", FN_OPT_NONE, 1402433619U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32u){"8123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"8123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"123456701238", FN_OPT_NONE, 1402433619U, FN_ERROR_OVERFLOW},
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
            (pfnCase32u){"400000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 536870912U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"123456701237  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"40000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 536870912U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345670123 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"400000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 536870912U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"123456701230  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32u){"40000000000  ", FN_PF_LONG_CHECK, 536870912U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345670123  ", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"400000000007  ", FN_PF_LONG_CHECK, 536870912U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"123456701237  ", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"4000000000077  ", FN_PF_LONG_CHECK, 536870912U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1234567012377  ", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32u){"400000000008", FN_PF_LONG_CHECK, 536870912U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345670123/", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"123456701238", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"123456701237", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"12345670123123456701238", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"12345670123123456701237", FN_PF_LONG_CHECK, 1402433619U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"37777777777377777777778", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"37777777777377777777777", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_OVERFLOW}
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

int octToInt32C1Test(){
    #define FUNCCALL octToInt32C1
    const static char * testName = "octToInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_S(FUNCCALL, int32_t, 7, 11, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_S(FUNCCALL, int32_t, 7, 11, PRId32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_S(FUNCCALL, int32_t, 7, PRId32);
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
            (pc1Case32s){"17777777775", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+17777777775", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+17777777775", FN_OPT_PC1_ALL, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"-17777777777", FN_OPT_NONE, {-2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-17777777777", FN_OPT_PC1_ALL, {-2147483647}, {0}, {-1}, 1},
            /* b */
            (pc1Case32s){"17777777777", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+17777777777", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+17777777777", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-20000000000", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-20000000000", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1},
            /* c */
            (pc1Case32s){"0017777777777", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"0017777777777", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_PC1_ALL, {0}, {0}, {-1}, 1},
            (pc1Case32s){"-000020000000000", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-000020000000000", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32s tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32s){"-+17777777775", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+-17777777775", FN_OPT_NONE, {-2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"8177777777758", FN_OPT_NONE, {2147483645}, {0}, {12}, 1},
            (pc1Case32s){"8+177777777758", FN_OPT_NONE, {2147483645}, {0}, {13}, 1},
            (pc1Case32s){"8-177777777758", FN_OPT_NONE, {-2147483645}, {0}, {13}, 1},
            (pc1Case32s){"8@#$%^&177777777758@", FN_OPT_NONE, {2147483645}, {0}, {18}, 1},
            (pc1Case32s){"8@#$%^&+177777777758@", FN_OPT_NONE, {2147483645}, {0}, {19}, 1},
            (pc1Case32s){"8@#$%^&-177777777758@", FN_OPT_NONE, {-2147483645}, {0}, {19}, 1},
            (pc1Case32s){"8@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32s){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32s){"817777777775", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32s){"177777777758", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {11}, 1},
            (pc1Case32s){"+177777777758", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {12}, 1},
            (pc1Case32s){"-177777777758", FN_PC_NO_INVALID_SKIP, {-2147483645}, {0}, {12}, 1},
            (pc1Case32s){"8%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
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
            (pc1Case32s){"-20000000001", FN_OPT_NONE, {-268435456}, {0}, {11}, 1},
            (pc1Case32s){"-200000000017", FN_OPT_NONE, {-268435456}, {0}, {11}, 1},
            (pc1Case32s){"-200000000007", FN_OPT_NONE, {-2147483648}, {0}, {12}, 1},
            (pc1Case32s){"-20000000010", FN_OPT_NONE, {-268435457}, {0}, {11}, 1},
            (pc1Case32s){"-200000000107", FN_OPT_NONE, {-268435457}, {0}, {11}, 1},
            (pc1Case32s){"-123456701237", FN_OPT_NONE, {-1402433619}, {0}, {12}, 1},
            (pc1Case32s){"-12345670123712345670123", FN_OPT_NONE, {-1402433619}, {0}, {12}, 1},
            /* --> Overflow */
            (pc1Case32s){"20000000000", FN_OPT_NONE, {268435456}, {0}, {10}, 1},
            (pc1Case32s){"200000000007", FN_OPT_NONE, {268435456}, {0}, {10}, 1},
            (pc1Case32s){"177777777777", FN_OPT_NONE, {2147483647}, {0}, {11}, 1},
            (pc1Case32s){"20000000001", FN_OPT_NONE, {268435456}, {0}, {10}, 1},
            (pc1Case32s){"200000000017", FN_OPT_NONE, {268435456}, {0}, {10}, 1},
            (pc1Case32s){"123456701237", FN_OPT_NONE, {1402433619}, {0}, {11}, 1},
            (pc1Case32s){"12345670123712345670123", FN_OPT_NONE, {1402433619}, {0}, {11}, 1},
            /* OVERFLOW_ERROR opt */
            /* --> Underflow */
            (pc1Case32s){"-20000000001", FN_PC_OVERFLOW_ERROR, {-268435456}, {FN_ERROR_UNDERFLOW}, {11}, 1},
            (pc1Case32s){"-200000000017", FN_PC_OVERFLOW_ERROR, {-268435456}, {FN_ERROR_UNDERFLOW}, {11}, 1},
            (pc1Case32s){"-200000000007", FN_PC_OVERFLOW_ERROR, {-2147483648}, {FN_ERROR_UNDERFLOW}, {12}, 1},
            (pc1Case32s){"-20000000010", FN_PC_OVERFLOW_ERROR, {-268435457}, {FN_ERROR_UNDERFLOW}, {11}, 1},
            (pc1Case32s){"-200000000107", FN_PC_OVERFLOW_ERROR, {-268435457}, {FN_ERROR_UNDERFLOW}, {11}, 1},
            (pc1Case32s){"-123456701237", FN_PC_OVERFLOW_ERROR, {-1402433619}, {FN_ERROR_UNDERFLOW}, {12}, 1},
            (pc1Case32s){"-12345670123712345670123", FN_PC_OVERFLOW_ERROR, {-1402433619}, {FN_ERROR_UNDERFLOW}, {12}, 1},
            /* --> Overflow */
            (pc1Case32s){"20000000000", FN_PC_OVERFLOW_ERROR, {268435456}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32s){"200000000007", FN_PC_OVERFLOW_ERROR, {268435456}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32s){"177777777777", FN_PC_OVERFLOW_ERROR, {2147483647}, {FN_ERROR_OVERFLOW}, {11}, 1},
            (pc1Case32s){"20000000001", FN_PC_OVERFLOW_ERROR, {268435456}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32s){"200000000017", FN_PC_OVERFLOW_ERROR, {268435456}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32s){"123456701237", FN_PC_OVERFLOW_ERROR, {1402433619}, {FN_ERROR_OVERFLOW}, {11}, 1},
            (pc1Case32s){"12345670123712345670123", FN_PC_OVERFLOW_ERROR, {1402433619}, {FN_ERROR_OVERFLOW}, {11}, 1},
            /* OVERFLOW SKIP opt */
            /* --> Underflow */
            (pc1Case32s){"-20000000001", FN_PC_OVERFLOW_SKIP, {-268435456}, {0}, {-1}, 1},
            (pc1Case32s){"-200000000017", FN_PC_OVERFLOW_SKIP, {-268435456}, {0}, {-1}, 1},
            (pc1Case32s){"-200000000007", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-20000000010", FN_PC_OVERFLOW_SKIP, {-268435457}, {0}, {-1}, 1},
            (pc1Case32s){"-200000000107", FN_PC_OVERFLOW_SKIP, {-268435457}, {0}, {-1}, 1},
            (pc1Case32s){"-123456701237", FN_PC_OVERFLOW_SKIP, {-1402433619}, {0}, {-1}, 1},
            (pc1Case32s){"-12345670123712345670123", FN_PC_OVERFLOW_SKIP, {-1402433619}, {0}, {-1}, 1},
            (pc1Case32s){"-200000000018", FN_PC_OVERFLOW_SKIP, {-268435456}, {0}, {12}, 1},
            (pc1Case32s){"-2000000000108", FN_PC_OVERFLOW_SKIP, {-268435456}, {0}, {13}, 1},
            (pc1Case32s){"-2000000000008", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {13}, 1},
            (pc1Case32s){"-200000000108", FN_PC_OVERFLOW_SKIP, {-268435457}, {0}, {12}, 1},
            (pc1Case32s){"-2000000001008", FN_PC_OVERFLOW_SKIP, {-268435457}, {0}, {13}, 1},
            (pc1Case32s){"-1234567012308", FN_PC_OVERFLOW_SKIP, {-1402433619}, {0}, {13}, 1},
            (pc1Case32s){"-123456701231234567012308", FN_PC_OVERFLOW_SKIP, {-1402433619}, {0}, {24}, 1},
            /* --> Overflow */
            (pc1Case32s){"20000000000", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {-1}, 1},
            (pc1Case32s){"200000000007", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {-1}, 1},
            (pc1Case32s){"177777777777", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"20000000001", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {-1}, 1},
            (pc1Case32s){"200000000017", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {-1}, 1},
            (pc1Case32s){"123456701237", FN_PC_OVERFLOW_SKIP, {1402433619}, {0}, {-1}, 1},
            (pc1Case32s){"12345670123712345670123", FN_PC_OVERFLOW_SKIP, {1402433619}, {0}, {-1}, 1},
            (pc1Case32s){"200000000008", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {11}, 1},
            (pc1Case32s){"2000000000008", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {12}, 1},
            (pc1Case32s){"1777777777708", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {12}, 1},
            (pc1Case32s){"200000000018", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {11}, 1},
            (pc1Case32s){"2000000000108", FN_PC_OVERFLOW_SKIP, {268435456}, {0}, {12}, 1},
            (pc1Case32s){"1234567012318", FN_PC_OVERFLOW_SKIP, {1402433619}, {0}, {12}, 1},
            (pc1Case32s){"123456701231234567012308", FN_PC_OVERFLOW_SKIP, {1402433619}, {0}, {23}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32s){"12345670123/", FN_PC_OVERFLOW_ERROR, {1402433619}, {0}, {11}, 1},
            (pc1Case32s){"123456701238", FN_PC_OVERFLOW_ERROR, {1402433619}, {0}, {11}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, int32_t, tCase5, ALEN(tCase5), PRId32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32s tCase6[] = {
            (pc1Case32s){"173 +735 -235 $170 $-170", FN_OPT_NONE,
                         {123, 477, -157, 120, -120},
                         {0,0,0,0,0},
                         {3,8,13,18,-1},
                         5},
            (pc1Case32s){"073 +1234567012301234 -20000000000012 $170 $-11560144", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {59, 1402433619, -2147483648, 120, -2547812},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_UNDERFLOW, 0, 0},
                         {3,21,37,42,-1},
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

int octToUInt32C1Test(){
    #define FUNCCALL octToUInt32C1
    const static char * testName = "octToUInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_U(FUNCCALL, uint32_t, 7, 11, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_U(FUNCCALL, uint32_t, 7, 11, PRIu32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_U(FUNCCALL, uint32_t, 7, PRIu32);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");
        /* -1 Check nextPTR pointer is NULL */
        pc1Case32u tCase3[] = {
            /* a */
            (pc1Case32u){"37777777775", FN_OPT_NONE, {4294967293U}, {0}, {-1}, 1},
            (pc1Case32u){"37777777775", FN_OPT_PC1_ALL, {4294967293U}, {0}, {-1}, 1},
            /* b */
            (pc1Case32u){"37777777777", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"37777777777", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            /* c */
            (pc1Case32u){"0037777777777", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"0037777777777", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32u){"000037777777777", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32u tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32u){"-1", FN_OPT_NONE, {1}, {0}, {-1}, 1},
            (pc1Case32u){"8377777777758", FN_OPT_NONE, {4294967293U}, {0}, {12}, 1},
            (pc1Case32u){"8@#$%^&377777777758@", FN_OPT_NONE, {4294967293U}, {0}, {18}, 1},
            (pc1Case32u){"8@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32u){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32u){"+0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"-0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"837777777775", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"377777777758", FN_PC_NO_INVALID_SKIP, {4294967293U}, {0}, {11}, 1},
            (pc1Case32u){"^%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case32u tCase5[] = {
            /* Overflow default */
            (pc1Case32u){"40000000000", FN_OPT_NONE, {536870912U}, {0}, {10}, 1},
            (pc1Case32u){"400000000007", FN_OPT_NONE, {536870912U}, {0}, {10}, 1},
            (pc1Case32u){"377777777777", FN_OPT_NONE, {4294967295U}, {0}, {11}, 1},
            (pc1Case32u){"40000000010", FN_OPT_NONE, {536870913U}, {0}, {10}, 1},
            (pc1Case32u){"400000000107", FN_OPT_NONE, {536870913U}, {0}, {10}, 1},
            (pc1Case32u){"123456701237", FN_OPT_NONE, {1402433619U}, {0}, {11}, 1},
            (pc1Case32u){"12345670123712345670123", FN_OPT_NONE, {1402433619U}, {0}, {11}, 1},
            /* OVERFLOW_ERROR opt */
            (pc1Case32u){"40000000000", FN_PC_OVERFLOW_ERROR, {536870912U}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32u){"400000000007", FN_PC_OVERFLOW_ERROR, {536870912U}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32u){"377777777777", FN_PC_OVERFLOW_ERROR, {4294967295U}, {FN_ERROR_OVERFLOW}, {11}, 1},
            (pc1Case32u){"40000000010", FN_PC_OVERFLOW_ERROR, {536870913U}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32u){"400000000107", FN_PC_OVERFLOW_ERROR, {536870913U}, {FN_ERROR_OVERFLOW}, {10}, 1},
            (pc1Case32u){"123456701237", FN_PC_OVERFLOW_ERROR, {1402433619U}, {FN_ERROR_OVERFLOW}, {11}, 1},
            (pc1Case32u){"12345670123712345670123", FN_PC_OVERFLOW_ERROR, {1402433619U}, {FN_ERROR_OVERFLOW}, {11}, 1},
            /* OVERFLOW SKIP opt */
            (pc1Case32u){"40000000000", FN_PC_OVERFLOW_SKIP, {536870912U}, {0}, {-1}, 1},
            (pc1Case32u){"400000000007", FN_PC_OVERFLOW_SKIP, {536870912U}, {0}, {-1}, 1},
            (pc1Case32u){"377777777777", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"40000000010", FN_PC_OVERFLOW_SKIP, {536870913U}, {0}, {-1}, 1},
            (pc1Case32u){"400000000107", FN_PC_OVERFLOW_SKIP, {536870913U}, {0}, {-1}, 1},
            (pc1Case32u){"123456701237", FN_PC_OVERFLOW_SKIP, {1402433619U}, {0}, {-1}, 1},
            (pc1Case32u){"12345670123712345670123", FN_PC_OVERFLOW_SKIP, {1402433619U}, {0}, {-1}, 1},
            (pc1Case32u){"400000000008", FN_PC_OVERFLOW_SKIP, {536870912U}, {0}, {11}, 1},
            (pc1Case32u){"4000000000008", FN_PC_OVERFLOW_SKIP, {536870912U}, {0}, {12}, 1},
            (pc1Case32u){"3777777777708", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {12}, 1},
            (pc1Case32u){"400000000108", FN_PC_OVERFLOW_SKIP, {536870913U}, {0}, {11}, 1},
            (pc1Case32u){"4000000001008", FN_PC_OVERFLOW_SKIP, {536870913U}, {0}, {12}, 1},
            (pc1Case32u){"1234567012308", FN_PC_OVERFLOW_SKIP, {1402433619U}, {0}, {12}, 1},
            (pc1Case32u){"123456701231234567012308", FN_PC_OVERFLOW_SKIP, {1402433619U}, {0}, {23}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32u){"12345670123/", FN_PC_OVERFLOW_ERROR, {1402433619U}, {0}, {11}, 1},
            (pc1Case32u){"123456701238", FN_PC_OVERFLOW_ERROR, {1402433619U}, {0}, {11}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32u tCase6[] = {
            (pc1Case32u){"173 13235 11412 $30431232777 & $3254545", FN_OPT_NONE,
                         {123U, 5789U, 4874U, 3294967295U, 874853U},
                         {0,0,0,0,0},
                         {3,9,15,28,-1},
                         5},
                       /* 0         10        20        30        40        50 */
                       /* 012345678901234567890123456789012345678901234567890123456789 */
            (pc1Case32u){"173 37777777777012 12345670123123456701230 $30431232777 & $3254545", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {123U, 4294967295U, 1402433619U, 3294967295U, 874853U},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_OVERFLOW, 0, 0},
                         {3,18,42,55,-1},
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
