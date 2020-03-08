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
#include "../h/BinaryUtil32.h"
#include "../testlib/testlib.c"
#include "test.h"

int binToInt32Test();
int binToInt32TrueErrorTest();
int binToUInt32Test();
int binToUInt32TrueErrorTest();

int binCompareTest32();
int binInt32OrSmallerTest();
int binCompareUTest32();
int binUInt32OrSmallerTest();

int binToInt32FPTest();
int binToUInt32FPTest();
int binToInt32FNTest();
int binToUInt32FNTest();

int binToInt32C1Test();
int binToUInt32C1Test();

int main(void){
    if ( binToInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( binToInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( binToUInt32Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( binToUInt32TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( binCompareTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( binInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( binCompareUTest32() == 1 ) return 1;
    puts("\n\n\n");
    if ( binUInt32OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( binToInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( binToUInt32FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( binToInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( binToUInt32FNTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( binToInt32C1Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( binToUInt32C1Test() == 1 ) return 1;

    return 0;
}

int binToInt32Test(){
    #define FUNCCALL binToInt32
    const static char * testName = "binToInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 1, 31, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 1, 32, FN_ERROR_GENERAL, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "1111111111111111111111111111101",  2147483645, 0},
            (pCase32s){"+1111111111111111111111111111101",  2147483645, 0},
            (pCase32s){"-1111111111111111111111111111111", -2147483647, 0},
            (pCase32s){ "1111111111111111111111111111111",  2147483647, 0},
            (pCase32s){"+1111111111111111111111111111111",  2147483647, 0},
            (pCase32s){"-10000000000000000000000000000000", -2147483648, 0},
            (pCase32s){"001111111111111111111111111111111", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-000010000000000000000000000000000000", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3) , PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-10000000000000000000000000000001", -1073741824, 1},
            (pCase32s){"-100000000000000000000000000000000", -2147483648, 1},
            (pCase32s){"-101010101010101010101010101010101", -1431655765, 1},
            /* Overflow */
            (pCase32s){"10000000000000000000000000000000", 1073741824, 1},
            (pCase32s){"11111111111111111111111111111110", 2147483647, 1},
            (pCase32s){"10101010101010101010101010101010", 1431655765, 1},
            (pCase32s){"100000000000000000000000000000000", 1073741824, 1},
            (pCase32s){"111111111111111111111111111111100", 2147483647, 1},
            (pCase32s){"101010101010101010101010101010100", 1431655765, 1},
            /* Invalid format */
            (pCase32s){"2101", 0, 1},
            (pCase32s){"-10101010101010101010101010101012", -1431655765, 1},
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

int binToInt32TrueErrorTest(){
    #define FUNCCALL binToInt32TrueError
    const static char * testName = "binToInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int32_t, 1, 31, PRId32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int32_t, 1, 32, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32s tCase3[] = {
            (pCase32s){ "1111111111111111111111111111101",  2147483645, 0},
            (pCase32s){"+1111111111111111111111111111101",  2147483645, 0},
            (pCase32s){"-1111111111111111111111111111111", -2147483647, 0},
            (pCase32s){ "1111111111111111111111111111111",  2147483647, 0},
            (pCase32s){"+1111111111111111111111111111111",  2147483647, 0},
            (pCase32s){"-10000000000000000000000000000000", -2147483648, 0},
            (pCase32s){"001111111111111111111111111111111", 2147483647, 0},
            (pCase32s){"+000", 0, 0},
            (pCase32s){"-000010000000000000000000000000000000", -2147483648, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32s tCase4[] = {
            /* Underflow */
            (pCase32s){"-10000000000000000000000000000001", -1073741824, FN_ERROR_UNDERFLOW},
            (pCase32s){"-10000000000000000000000000000010", -1073741825, FN_ERROR_UNDERFLOW},
            (pCase32s){"-100000000000000000000000000000001", -2147483648, FN_ERROR_UNDERFLOW},
            (pCase32s){"-101010101010101010101010101010101", -1431655765, FN_ERROR_UNDERFLOW},
            (pCase32s){"-1010101010101010101010101010101010101010101010101010101010101010", -1431655765, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pCase32s){"10000000000000000000000000000000", 1073741824, FN_ERROR_OVERFLOW},
            (pCase32s){"11111111111111111111111111111110", 2147483647, FN_ERROR_OVERFLOW},
            (pCase32s){"10101010101010101010101010101010", 1431655765, FN_ERROR_OVERFLOW},
            (pCase32s){"1010101010101010101010101010101010101010101010101010101010101010", 1431655765, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32s){"2101", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-10000000000000000000000000000000/", 2147483648, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"10101010101010101010101010101012", 1431655765, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+10101010101010101010101010101012", 1431655765, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"101010101010101010101010101010102", 1431655765, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+101010101010101010101010101010102", 1431655765, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-101010101010101010101010101010102", -1431655765, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"100000000000000000000000000000002", 1073741824, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+100000000000000000000000000000002", 1073741824, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-100000000000000000000000000000012", -1073741824, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"11111111111111111111111111111112", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+11111111111111111111111111111112", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"111111111111111111111111111111102", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+111111111111111111111111111111102", 2147483647, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-100000000000000000000000000000002", -2147483648, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"101010101010101010101010101010101010101010101010101010101010102", 1431655765, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"+101010101010101010101010101010101010101010101010101010101010102", 1431655765, FN_ERROR_INVALID_FORMAT},
            (pCase32s){"-101010101010101010101010101010101010101010101010101010101010102", -1431655765, FN_ERROR_INVALID_FORMAT},
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

int binToUInt32Test(){
    #define FUNCCALL binToUInt32
    const static char * testName = "binToUInt32";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 1, 32, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 1, 32, FN_ERROR_GENERAL, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"11111111111111111111111111111110", 4294967294U, 0},
            (pCase32u){"11111111111111111111111111111111", 4294967295U, 0},
            (pCase32u){"0011111111111111111111111111111111", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"000011111111111111111111111111111111", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"100000000000000000000000000000000", 2147483648U, 1},
            (pCase32u){"101010101010101010101010101010100", 2863311530U, 1},
            /* Invalid format */
            (pCase32u){"2101", 0, 1},
            (pCase32u){"101010101010101010101010101010102", 2863311530U, 1},
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

int binToUInt32TrueErrorTest(){
    #define FUNCCALL binToUInt32TrueError
    const static char * testName = "binToUInt32TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint32_t, 1, 32, PRIu32);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint32_t, 1, 32, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase32u tCase3[] = {
            (pCase32u){"11111111111111111111111111111110", 4294967294U, 0},
            (pCase32u){"11111111111111111111111111111111", 4294967295U, 0},
            (pCase32u){"0011111111111111111111111111111111", 4294967295U, 0},
            (pCase32u){"000", 0, 0},
            (pCase32u){"000011111111111111111111111111111111", 4294967295U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase32u tCase4[] = {
            /* Overflow */
            (pCase32u){"100000000000000000000000000000001", 2147483648U, FN_ERROR_OVERFLOW},
            (pCase32u){"111111111111111111111111111111111", 4294967295U, FN_ERROR_OVERFLOW},
            (pCase32u){"101010101010101010101010101010101", 2863311530U, FN_ERROR_OVERFLOW},
            (pCase32u){"1010101010101010101010101010101010101010101010101010101010101010", 2863311530U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase32u){"2101", 0, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"10101010101010101010101010101010/", 2863311530U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"101010101010101010101010101010102", 2863311530U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"100000000000000000000000000000002", 2147483648U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"111111111111111111111111111111112", 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pCase32u){"10101010101010101010101010101010101010101010101010101010101010102", 2863311530U, FN_ERROR_INVALID_FORMAT},
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

int binCompareTest32(){
    #define FUNCCALL binCompareAsInt32
    const static char * testName = "binCompareAsInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"1111111111111111111111111111111", "-10000000000000000000000000000000", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"1111111111111111111111111111111", "1111111111111111111111111111111", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"-10000000000000000000000000000000", "1111111111111111111111111111111", -1, 0}
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
            (cCase){"1!", "101", 0, 1},
            (cCase){"101", "1!", 0, 1},
            /* Underflow/Overflow */
            (cCase){"-10000000000000000000000000000001", "-1", 0, 1},
            (cCase){"1", "10000000000000000000000000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int binInt32OrSmallerTest(){
    #define FUNCCALL binInt32OrSmaller
    const static char * testName = "binInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "-10101010101010101010101010101010", -1},
            (cCaseNE){"!1", "10101010101010101010101010101010", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "1111111111111111111111111111111", -1},
            /* UnderFlow to */
            (cCaseNE){"-10101010101010101010101010101010", "!1", 1},
            (cCaseNE){"-10101010101010101010101010101010", "-10000000000000000000000000000001", 0},
            (cCaseNE){"-10101010101010101010101010101010", "10101010101010101010101010101010", -1},
            (cCaseNE){"-10101010101010101010101010101010", "", -1},
            (cCaseNE){"-10101010101010101010101010101010", "-10000000000000000000000000000000", -1},
            /* OverFlow to */
            (cCaseNE){"10101010101010101010101010101010", "!1", 1},
            (cCaseNE){"10101010101010101010101010101010", "-10101010101010101010101010101010", 1},
            (cCaseNE){"10101010101010101010101010101010", "10000000000000000000000000000000", 0},
            (cCaseNE){"10101010101010101010101010101010", "", -1},
            (cCaseNE){"10101010101010101010101010101010", "1111111111111111111111111111111", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "-10101010101010101010101010101010", 1},
            (cCaseNE){"", "10101010101010101010101010101010", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "-10000000000000000000000000000000", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "-10101010101010101010101010101010", 1},
            (cCaseNE){"1", "10101010101010101010101010101010", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"-10000000000000000000000000000000", "1111111111111111111111111111111" , -1},
            (cCaseNE){"-10000000000000000000000000000000", "-10000000000000000000000000000000" , 0},
            (cCaseNE){"1111111111111111111111111111111", "-10000000000000000000000000000000" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int binCompareUTest32(){
    #define FUNCCALL binCompareAsUInt32
    const static char * testName = "binCompareAsUInt32";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"11111111111111111111111111111111", "11111111111111111111111111111110", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"11111111111111111111111111111111", "11111111111111111111111111111111", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"11111111111111111111111111111110", "11111111111111111111111111111111", -1, 0}
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
            (cCase){"100000000000000000000000000000000", "1", 0, 1},
            (cCase){"1", "100000000000000000000000000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int binUInt32OrSmallerTest(){
    #define FUNCCALL binUInt32OrSmaller
    const static char * testName = "binUInt32OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "101010101010101010101010101010101", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "11111111111111111111111111111111", -1},
            /* OverFlow to */
            (cCaseNE){"101010101010101010101010101010101", "!1", 1},
            (cCaseNE){"101010101010101010101010101010101", "100000000000000000000000000000000", 0},
            (cCaseNE){"101010101010101010101010101010101", "", -1},
            (cCaseNE){"101010101010101010101010101010101", "11111111111111111111111111111111", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "101010101010101010101010101010101", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "11111111111111111111111111111111", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "101010101010101010101010101010101", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"11111111111111111111111111111110", "11111111111111111111111111111111" , -1},
            (cCaseNE){"11111111111111111111111111111111", "11111111111111111111111111111111" , 0},
            (cCaseNE){"11111111111111111111111111111111", "11111111111111111111111111111110" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int binToInt32FPTest(){
    #define FUNCCALL binToInt32FP
    const static char * testName = "binToInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_S(FUNCCALL, int32_t, 1, 31, optArray, ALEN(optArray), PRId32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_S(FUNCCALL, int32_t, 1, 31, 33, PRId32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_S(FUNCCALL, int32_t, 1, 32, 33, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32s tCase3[] = {
            (pfpCase32s){"1111111111111111111111111111101", 0, 30, FN_OPT_NONE, 2147483645, 0},
            (pfpCase32s){"1111111111111111111111111111101", 0, 30, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"+1111111111111111111111111111101", 0, 31, FN_OPT_PFP_ALL, 2147483645, 0},
            (pfpCase32s){"-1111111111111111111111111111111", 0, 31, FN_OPT_PFP_ALL, -2147483647, 0},
                       /* 0123456789012345678901234567890123456789 */
            (pfpCase32s){"1111111111111111111111111111111", 0, 30, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"1111111111111111111111111111111", 0, 30, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+1111111111111111111111111111111", 0, 31, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"-10000000000000000000000000000000", 0, 32, FN_OPT_PFP_ALL, -2147483648, 0},
            (pfpCase32s){"001111111111111111111111111111111", 0, 32, FN_OPT_NONE, 2147483647, 0},
            (pfpCase32s){"001111111111111111111111111111111", 0, 32, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"+000", 0, 3, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase32s){"-0000010000000000000000000000000000000", 0, 37, FN_OPT_PFP_ALL, -2147483648, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32s tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32s){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32s){"  1100", 0, 5, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase32s){"   -1111111111111111111111111111111", 0, 34, FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfpCase32s){"  -10000000000000000000000000000000", 0, 34, FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfpCase32s){"    1111111111111111111111111111111", 0, 34, FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfpCase32s){"   1111011  ", 0, 11, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32s){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32s){"1100  ", 0, 5, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase32s){"-1111111111111111111111111111111   ", 0, 34, FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfpCase32s){"-10000000000000000000000000000000  ", 0, 34, FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfpCase32s){"1111111111111111111111111111111    ", 0, 34, FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfpCase32s){" 1111011  ", 0, 9, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32s){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32s){" -1 ", 0, 3, FN_PF_IGNORE_SPACES, -1, 0},
            (pfpCase32s){"   -000  ", 0, 8, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32s){"   -1111111111111111111111111111111   ", 0, 37, FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfpCase32s){"   -10000000000000000000000000000000  ", 0, 37, FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfpCase32s){"   1111111111111111111111111111111    ", 0, 37, FN_PF_IGNORE_SPACES, 2147483647, 0},
            (pfpCase32s){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32s tCase5[] = {
            /* Underflow */
            (pfpCase32s){"-10000000000000000000000000000001", 0, 32, FN_OPT_NONE, -1073741824, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-100000000000000000000000000000000", 0, 33, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-101010101010101010101010101010100", 0, 33, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfpCase32s){"10000000000000000000000000000000", 0, 31, FN_OPT_NONE, 1073741824, FN_ERROR_OVERFLOW},
            (pfpCase32s){"11111111111111111111111111111110", 0, 31, FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"10101010101010101010101010101010", 0, 31, FN_OPT_NONE, 1431655765, FN_ERROR_OVERFLOW},
            (pfpCase32s){"100000000000000000000000000000000", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"111111111111111111111111111111100", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"101010101010101010101010101010100", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32s){"2101", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"2101", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"10101010101010101010101010101012", 0, 31, FN_OPT_NONE, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+10101010101010101010101010101012", 0, 32, FN_OPT_NONE, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"101010101010101010101010101010102", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+101010101010101010101010101010102", 0, 33, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-101010101010101010101010101010102", 0, 33, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
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
            (pfpCase32s){"210101010101010101010101010101010", 0, 32, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+210101010101010101010101010101010", 0, 33, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-210101010101010101010101010101010", 0, 33, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-100000000000000000000000000000020", 0, 33, FN_PF_PARSE_ON_ERROR, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"101010101010101010101010101010102", 0, 32, FN_PF_PARSE_ON_ERROR, 1431655765, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+101010101010101010101010101010102", 0, 33, FN_PF_PARSE_ON_ERROR, 1431655765, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-101010101010101010101010101010102", 0, 33, FN_PF_PARSE_ON_ERROR, -1431655765, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"100000000000000000000000000000002", 0, 32, FN_PF_PARSE_ON_ERROR, 1073741824, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+100000000000000000000000000000002", 0, 33, FN_PF_PARSE_ON_ERROR, 1073741824, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-100000000000000000000000000000012", 0, 33, FN_PF_PARSE_ON_ERROR, -1073741824, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"111111111111111111111111111111102", 0, 32, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+111111111111111111111111111111102", 0, 33, FN_PF_PARSE_ON_ERROR, 2147483647, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-100000000000000000000000000000002", 0, 33, FN_PF_PARSE_ON_ERROR, -2147483648, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"10101010101010101010101010101010101010101010101010101010101010101010102", 0, 70, FN_PF_PARSE_ON_ERROR, 1431655765, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+10101010101010101010101010101010101010101010101010101010101010101010102", 0, 71, FN_PF_PARSE_ON_ERROR, 1431655765, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-10101010101010101010101010101010101010101010101010101010101010101010102", 0, 71, FN_PF_PARSE_ON_ERROR, -1431655765, FN_ERROR_UNDERFLOW},
            /* Long Check */
            (pfpCase32s){"210101010101010101010101010101010",
                         0, 32, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-10000000000000000000000000000000/",
                         0, 33, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-10000000000000000000000000000000210000000000000000000000000000000",
                         0, 65, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-10000000000000000000000000000000210000000000000000000000000000000",
                         0, 65, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-10000000000000000000000000000001210000000000000000000000000000001",
                         0, 65, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"10000000000000000000000000000000210000000000000000000000000000000",
                         0, 64, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"+10000000000000000000000000000000210000000000000000000000000000000",
                         0, 65, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-10000000000000000000000000000010210000000000000000000000000000010",
                         0, 65, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, -1073741825, FN_ERROR_INVALID_FORMAT},
            (pfpCase32s){"-10000000000000000000000000000001110000000000000000000000000000001",
                         0, 65, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, -1073741824, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"10000000000000000000000000000000110000000000000000000000000000000",
                         0, 64, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, 1073741824, FN_ERROR_OVERFLOW},
            (pfpCase32s){"+10000000000000000000000000000000110000000000000000000000000000000",
                         0, 65, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, 1073741824, FN_ERROR_OVERFLOW},
            (pfpCase32s){"-10000000000000000000000000000010110000000000000000000000000000010",
                         0, 65, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, -1073741825, FN_ERROR_UNDERFLOW},
            (pfpCase32s){"-100000000000000000000000000000001",
                         0, 33, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, -2147483648, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, int32_t, tCase6, ALEN(tCase6), PRId32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase32s tCase7[] = {
            (pfpCase32s){"This number 101111000110000101001110 is parseable.",
                         12, 35, FN_OPT_NONE, 12345678, 0},
            (pfpCase32s){"Number(111010110111100110100010101) to array.",
                         7, 33, FN_OPT_PFP_ALL, 123456789, 0},
            (pfpCase32s){"At least this one(-1001001100101100000001011010010) with sign must pass.",
                         18, 49, FN_OPT_PFP_ALL, -1234567890, 0},
            (pfpCase32s){"Important number:+1111111111111111111111111111111(INT MAX VALUE)",
                         17, 48, FN_OPT_PFP_ALL, 2147483647, 0},
            (pfpCase32s){"Another one:-10000000000000000000000000000000(INT32 MIN VALUE)",
                         12, 44, FN_OPT_PFP_ALL, -2147483648, 0},
            (pfpCase32s){"Parse after the seven 23456710001011000111011100110011015to before the last five",
                         28, 55, FN_OPT_PFP_ALL, 145874125, 0},
            (pfpCase32s){"From next space   -111010110111100110100010101    (to prior space)",
                         15, 49, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase32s){"Without any ingore spaces   -100100110010110000000101100    with spaces parse will fail."
                         "And the segment considered to be overflow, or contain an invalid format"
                         "depends on FN_PF_LONG_CHECK",
                         25, 59, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int binToUInt32FPTest(){
    #define FUNCCALL binToUInt32FP
    const static char * testName = "binToUInt32FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_U(FUNCCALL, uint32_t, 1, 32, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_U(FUNCCALL, uint32_t, 1, 32, 33, PRIu32);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_U(FUNCCALL, uint32_t, 1, 32, 33, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase32u tCase3[] = {
            (pfpCase32u){"11111111111111111111111111111110", 0, 31, FN_OPT_NONE, 4294967294U, 0},
            (pfpCase32u){"11111111111111111111111111111110", 0, 31, FN_OPT_PFP_ALL, 4294967294U, 0},
            (pfpCase32u){"11111111111111111111111111111111", 0, 31, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"11111111111111111111111111111111", 0, 31, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"0011111111111111111111111111111111", 0, 33, FN_OPT_NONE, 4294967295U, 0},
            (pfpCase32u){"0011111111111111111111111111111111", 0, 33, FN_OPT_PFP_ALL, 4294967295U, 0},
            (pfpCase32u){"000", 0, 2, FN_OPT_PFP_ALL, 0, 0},
                       /* 0123456789012345678901234567890123456789 */
            (pfpCase32u){"000011111111111111111111111111111111", 0, 35, FN_OPT_NONE, 4294967295U, 0}

        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase32u tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase32u){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase32u){"  1100", 0, 5, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase32u){"   11111111111111111111111111111110", 0, 34, FN_PF_IGNORE_LSPACES, 4294967294U, 0},
            (pfpCase32u){"   11111111111111111111111111111111", 0, 34, FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfpCase32u){"   1111011  ", 0, 11, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase32u){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase32u){"1100  ", 0, 5, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase32u){"11111111111111111111111111111110   ", 0, 34, FN_PF_IGNORE_TSPACES, 4294967294U, 0},
            (pfpCase32u){"11111111111111111111111111111111   ", 0, 34, FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfpCase32u){"   11000000111001   ", 0, 19, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase32u){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase32u){"   000  ", 0, 7, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase32u){"   11111111111111111111111111111110   ", 0, 37, FN_PF_IGNORE_SPACES, 4294967294U, 0},
            (pfpCase32u){"   11111111111111111111111111111111   ", 0, 37, FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfpCase32u){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase32u tCase5[] = {
            /* Overflow */
            (pfpCase32u){"100000000000000000000000000000001", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"111111111111111111111111111111110", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase32u){"101010101010101010101010101010100", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase32u){"2101", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"2101", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"101010101010101010101010101010102", 0, 32, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
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
            (pfpCase32u){"210000000000000000000000000000000", 0, 32, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"101010101010101010101010101010102", 0, 32, FN_PF_PARSE_ON_ERROR, 2863311530U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"1000000000000000000000000000000012", 0, 33, FN_PF_PARSE_ON_ERROR, 2147483648U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"111111111111111111111111111111112", 0, 32, FN_PF_PARSE_ON_ERROR, 4294967295U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"10101010101010101010101010101010101010101010101010101010101010101010102", 0, 70, FN_PF_PARSE_ON_ERROR, 2863311530U, FN_ERROR_OVERFLOW},
            (pfpCase32u){"+101010101010101010101010101010100", 0, 33, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"-101010101010101010101010101010100", 0, 33, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            /* Long Check */
            (pfpCase32u){"210101010101010101010101010101010", 0, 32, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"10101010101010101010101010101010/", 0, 32, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"10101010101010101010101010101010210101010101010101010101010101010",
                         0, 64, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"10101010101010101010101010101010210101010101010101010101010101010",
                         0, 64, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, 2863311530U, FN_ERROR_INVALID_FORMAT},
            (pfpCase32u){"111111111111111111111111111111111",
                         0, 32, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR, 4294967295U, FN_ERROR_OVERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, uint32_t, tCase6, ALEN(tCase6), PRIu32);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase32u tCase7[] = {
            (pfpCase32u){"This 1 is parseable.",
                       5, 5, FN_OPT_NONE, 1, 0},
            (pfpCase32u){"This number 101111000110000101001110 is parseable.",
                       12, 35, FN_OPT_NONE, 12345678U, 0},
            (pfpCase32u){"Number(111010110111100110100010101) to array.",
                       7, 33, FN_OPT_PFP_ALL, 123456789U, 0},
            (pfpCase32u){"Important number:+11111111111111111111111111111111(UINT32 MAX VALUE), The + is not parsed.",
                       18, 49, FN_OPT_PFP_ALL, 4294967295U, 0},
                       /* 0         10        20        30        40        50        60        70 */
                       /* 01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
            (pfpCase32u){"Parse after the seven 1234567111001000100001111010011000011to to before first t",
                       29, 58, FN_OPT_PFP_ALL, 957412547U, 0},
            (pfpCase32u){"From next space   1001001100101100000001011010010    (to prior space)",
                       15, 52, FN_OPT_PFP_ALL, 1234567890U, 0},
            (pfpCase32u){"Without any ingore spaces   1001001100101100000001011010    with spaces parse will fail."
                       "And the segment considered to be overflow, or contain an invalid format"
                       "depends on FN_PF_LONG_CHECK",
                       25, 59, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int binToInt32FNTest(){
    #define FUNCCALL binToInt32FN
    const static char * testName = "binToInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_S(FUNCCALL, int32_t, 1, 31, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_S(FUNCCALL, int32_t, 1, 32, FN_ERROR_INVALID_FORMAT, PRId32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_S(FUNCCALL, int32_t, 1, 31, PRId32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32s tCase4[] = {
            (pfnCase32s){"1111111111111111111111111111101", FN_OPT_NONE, 2147483645, 0},
            (pfnCase32s){"1111111111111111111111111111101", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"+1111111111111111111111111111101", FN_OPT_PFN_ALL, 2147483645, 0},
            (pfnCase32s){"-1111111111111111111111111111111", FN_OPT_PFN_ALL, -2147483647, 0},
            (pfnCase32s){"1111111111111111111111111111111", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"1111111111111111111111111111111", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+1111111111111111111111111111111", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"-10000000000000000000000000000000", FN_OPT_PFN_ALL, -2147483648, 0},
            (pfnCase32s){"001111111111111111111111111111111", FN_OPT_NONE, 2147483647, 0},
            (pfnCase32s){"001111111111111111111111111111111", FN_OPT_PFN_ALL, 2147483647, 0},
            (pfnCase32s){"+000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32s){"-000010000000000000000000000000000000", FN_OPT_PFN_ALL, -2147483648, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, int32_t, tCase4, ALEN(tCase4), PRId32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32s tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32s){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32s){" 1100", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase32s){"   -1111111111111111111111111111111", FN_PF_IGNORE_LSPACES, -2147483647, 0},
            (pfnCase32s){"   -10000000000000000000000000000000", FN_PF_IGNORE_LSPACES, -2147483648, 0},
            (pfnCase32s){"    1111111111111111111111111111111", FN_PF_IGNORE_LSPACES, 2147483647, 0},
            (pfnCase32s){"   1111011  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32s){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32s){"1100  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase32s){"-1111111111111111111111111111111   ", FN_PF_IGNORE_TSPACES, -2147483647, 0},
            (pfnCase32s){"-10000000000000000000000000000000   ", FN_PF_IGNORE_TSPACES, -2147483648, 0},
            (pfnCase32s){"1111111111111111111111111111111    ", FN_PF_IGNORE_TSPACES, 2147483647, 0},
            (pfnCase32s){" 11000000111001  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32s){"10000000000000000000000000000000  ", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+10000000000000000000000000000000  ", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-10000000000000000000000000000001  ", FN_PF_IGNORE_TSPACES, -1073741824, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-10000000000000000000000000000010  ", FN_PF_IGNORE_TSPACES, -1073741825, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"100000000000000000000000000000002  ", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+100000000000000000000000000000002  ", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-100000000000000000000000000000012  ", FN_PF_IGNORE_TSPACES, -1073741824, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-100000000000000000000000000000102  ", FN_PF_IGNORE_TSPACES, -1073741825, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"1000000000000000000000000000000/  ", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"10000000000000000000000000000002  ", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"10000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+10000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10000000000000000000000000000001  0", FN_PF_IGNORE_TSPACES, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10000000000000000000000000000010  0", FN_PF_IGNORE_TSPACES, -1073741825, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32s){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32s){" -1 ", FN_PF_IGNORE_SPACES, -1, 0},
            (pfnCase32s){"   -000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32s){"   -1111111111111111111111111111111  ", FN_PF_IGNORE_SPACES, -2147483647, 0},
            (pfnCase32s){"   -10000000000000000000000000000000  ", FN_PF_IGNORE_SPACES, -2147483648, 0},
            (pfnCase32s){"   1111111111111111111111111111111       ", FN_PF_IGNORE_SPACES, 2147483647, 0},
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
            (pfnCase32s){"-10000000000000000000000000000001", FN_OPT_NONE, -1073741824, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-100000000000000000000000000000000", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-10101010101010101010101010101011", FN_OPT_NONE, -1431655765, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-101010101010101010101010101010102", FN_OPT_NONE, -1431655765, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-100000000000000000000000000000002", FN_OPT_NONE, -2147483648, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-1010101010101010101010101010101010101010101010101010101010102", FN_OPT_NONE, -1431655765, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfnCase32s){"10000000000000000000000000000000", FN_OPT_NONE, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"11111111111111111111111111111110", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"10101010101010101010101010101010", FN_OPT_NONE, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"100000000000000000000000000000000", FN_OPT_NONE, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"111111111111111111111111111111100", FN_OPT_NONE, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"101010101010101010101010101010100", FN_OPT_NONE, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"1010101010101010101010101010101010101010101010101010101010102", FN_OPT_NONE, 1431655765, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32s){"2101", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"2101", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"10101010101010101010101010101012", FN_OPT_NONE, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+10101010101010101010101010101012", FN_OPT_NONE, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"101010101010101010101010101010102", FN_OPT_NONE, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+101010101010101010101010101010102", FN_OPT_NONE, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-101010101010101010101010101010102", FN_OPT_NONE, -1431655765, FN_ERROR_UNDERFLOW},
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
            (pfnCase32s){"100000000000000000000000000000001  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+100000000000000000000000000000001  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1073741824, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-100000000000000000000000000000011  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1073741824, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-100000000000000000000000000000101  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1073741825, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"-100000000000000000000000000000001  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -2147483648, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32s){"100000000000000000000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+100000000000000000000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-100000000000000000000000000000010 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-100000000000000000000000000000100 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1073741825, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-100000000000000000000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1000000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+1000000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1000000000000000000000000000000100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1000000000000000000000000000001000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1073741825, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1000000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32s){"10000000000000000000000000000000  ", FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+10000000000000000000000000000000  ", FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10000000000000000000000000000001  ", FN_PF_LONG_CHECK, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10000000000000000000000000000010  ", FN_PF_LONG_CHECK, -1073741825, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"100000000000000000000000000000002  ", FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+100000000000000000000000000000002  ", FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-100000000000000000000000000000012  ", FN_PF_LONG_CHECK, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-100000000000000000000000000000102  ", FN_PF_LONG_CHECK, -1073741825, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"1000000000000000000000000000000002  ", FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+1000000000000000000000000000000002  ",FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1000000000000000000000000000000102  ", FN_PF_LONG_CHECK, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-1000000000000000000000000000001002  ", FN_PF_LONG_CHECK, -1073741825, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32s){"10000000000000000000000000000000/", FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+10000000000000000000000000000000/", FN_PF_LONG_CHECK, 1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10000000000000000000000000000001/", FN_PF_LONG_CHECK, -1073741824, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10000000000000000000000000000010/", FN_PF_LONG_CHECK, -1073741825, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"101010101010101010101010101010102", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+101010101010101010101010101010102", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-101010101010101010101010101010102", FN_PF_LONG_CHECK, -1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"101010101010101010101010101010100", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+101010101010101010101010101010100", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-101010101010101010101010101010100", FN_PF_LONG_CHECK, -1431655765, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"10101010101010101010101010101010101010101010101010101010101010102", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+10101010101010101010101010101010101010101010101010101010101010102", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10101010101010101010101010101010101010101010101010101010101010102", FN_PF_LONG_CHECK, -1431655765, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"10101010101010101010101010101010101010101010101010101010101010100", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+10101010101010101010101010101010101010101010101010101010101010100", FN_PF_LONG_CHECK, 1431655765, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-10101010101010101010101010101010101010101010101010101010101010100", FN_PF_LONG_CHECK, -1431655765, FN_ERROR_UNDERFLOW},
            (pfnCase32s){"11111111111111111111111111111111111111111111111111111111111111112", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"+11111111111111111111111111111111111111111111111111111111111111112", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"-10000000000000000000000000000000000000000000000000000000000000002", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_INVALID_FORMAT},
            (pfnCase32s){"11111111111111111111111111111111111111111111111111111111111111110", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"+11111111111111111111111111111111111111111111111111111111111111110", FN_PF_LONG_CHECK, 2147483647, FN_ERROR_OVERFLOW},
            (pfnCase32s){"-10000000000000000000000000000000000000000000000000000000000000001", FN_PF_LONG_CHECK, -2147483648, FN_ERROR_UNDERFLOW}
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

int binToUInt32FNTest(){
    #define FUNCCALL binToUInt32FN
    const static char * testName = "binToUInt32FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_U(FUNCCALL, uint32_t, 1, 32, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_U(FUNCCALL, uint32_t, 1, 32, FN_ERROR_INVALID_FORMAT, PRIu32);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_U(FUNCCALL, uint32_t, 1, 31, PRIu32);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase32u tCase4[] = {
            (pfnCase32u){"11111111111111111111111111111110", FN_OPT_NONE, 4294967294U, 0},
            (pfnCase32u){"11111111111111111111111111111110", FN_OPT_PFN_ALL, 4294967294U, 0},
            (pfnCase32u){"11111111111111111111111111111111", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"11111111111111111111111111111111", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"0011111111111111111111111111111111", FN_OPT_NONE, 4294967295U, 0},
            (pfnCase32u){"0011111111111111111111111111111111", FN_OPT_PFN_ALL, 4294967295U, 0},
            (pfnCase32u){"000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase32u){"000011111111111111111111111111111111", FN_OPT_PFN_ALL, 4294967295U, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase32u tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase32u){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase32u){"  1100", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase32u){"   11111111111111111111111111111110", FN_PF_IGNORE_LSPACES, 4294967294U, 0},
            (pfnCase32u){"   11111111111111111111111111111111", FN_PF_IGNORE_LSPACES, 4294967295U, 0},
            (pfnCase32u){"   1111011  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase32u){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase32u){"1100  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase32u){"11111111111111111111111111111110   ", FN_PF_IGNORE_TSPACES, 4294967294U, 0},
            (pfnCase32u){"11111111111111111111111111111111   ", FN_PF_IGNORE_TSPACES, 4294967295U, 0},
            (pfnCase32u){" 11000000111001  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase32u){"100000000000000000000000000000000  ", FN_PF_IGNORE_TSPACES, 2147483648U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"100000000000000000000000000000002  ", FN_PF_IGNORE_TSPACES, 2147483648U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"10000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES, 2147483648U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase32u){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase32u){"   000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase32u){"   11111111111111111111111111111110  ", FN_PF_IGNORE_SPACES, 4294967294U, 0},
            (pfnCase32u){"   11111111111111111111111111111111  ", FN_PF_IGNORE_SPACES, 4294967295U, 0},
            (pfnCase32u){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase32u tCase6[] = {
            /* Overflow */
            (pfnCase32u){"100000000000000000000000000000001", FN_OPT_NONE, 2147483648U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"111111111111111111111111111111110", FN_OPT_NONE, 4294967295U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"101010101010101010101010101010100", FN_OPT_NONE, 2863311530U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase32u){"2101", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"2101", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"101010101010101010101010101010102", FN_OPT_NONE, 2863311530U, FN_ERROR_OVERFLOW},
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
            (pfnCase32u){"100000000000000000000000000000001  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 2147483648U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase32u){"10000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 2147483648U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"100000000000000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 2147483648U, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase32u){"10000000000000000000000000000000  ", FN_PF_LONG_CHECK, 2147483648U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"100000000000000000000000000000002  ", FN_PF_LONG_CHECK, 2147483648U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"1000000000000000000000000000000002  ", FN_PF_LONG_CHECK, 2147483648U, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase32u){"10000000000000000000000000000000/", FN_PF_LONG_CHECK, 2147483648U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"101010101010101010101010101010102", FN_PF_LONG_CHECK, 2863311530U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"101010101010101010101010101010100", FN_PF_LONG_CHECK, 2863311530U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"10101010101010101010101010101010101010101010101010101010101010102", FN_PF_LONG_CHECK, 2863311530U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"10101010101010101010101010101010101010101010101010101010101010100", FN_PF_LONG_CHECK, 2863311530U, FN_ERROR_OVERFLOW},
            (pfnCase32u){"11111111111111111111111111111111111111111111111111111111111111112", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_INVALID_FORMAT},
            (pfnCase32u){"11111111111111111111111111111111111111111111111111111111111111110", FN_PF_LONG_CHECK, 4294967295U, FN_ERROR_OVERFLOW}
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

int binToInt32C1Test(){
    #define FUNCCALL binToInt32C1
    const static char * testName = "binToInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_S(FUNCCALL, int32_t, 1, 31, optArray, ALEN(optArray), PRId32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_S(FUNCCALL, int32_t, 1, 32, PRId32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_S(FUNCCALL, int32_t, 1, PRId32);
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
            (pc1Case32s){"1111111111111111111111111111101", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+1111111111111111111111111111101", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+1111111111111111111111111111101", FN_OPT_PC1_ALL, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"-1111111111111111111111111111111", FN_OPT_NONE, {-2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-1111111111111111111111111111111", FN_OPT_PC1_ALL, {-2147483647}, {0}, {-1}, 1},
            /* b */
            (pc1Case32s){"1111111111111111111111111111111", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+1111111111111111111111111111111", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+1111111111111111111111111111111", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"-10000000000000000000000000000000", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-10000000000000000000000000000000", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1},
            /* c */
            (pc1Case32s){"001111111111111111111111111111111", FN_OPT_NONE, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"001111111111111111111111111111111", FN_OPT_PC1_ALL, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32s){"+000", FN_OPT_PC1_ALL, {0}, {0}, {-1}, 1},
            (pc1Case32s){"-000010000000000000000000000000000000", FN_OPT_NONE, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-000010000000000000000000000000000000", FN_OPT_PC1_ALL, {-2147483648}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, int32_t, tCase3, ALEN(tCase3), PRId32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32s tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32s){"-+1111111111111111111111111111101", FN_OPT_NONE, {2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"+-1111111111111111111111111111101", FN_OPT_NONE, {-2147483645}, {0}, {-1}, 1},
            (pc1Case32s){"211111111111111111111111111111012", FN_OPT_NONE, {2147483645}, {0}, {32}, 1},
            (pc1Case32s){"2+11111111111111111111111111111012", FN_OPT_NONE, {2147483645}, {0}, {33}, 1},
            (pc1Case32s){"2-11111111111111111111111111111012", FN_OPT_NONE, {-2147483645}, {0}, {33}, 1},
            (pc1Case32s){"2@#$%^&11111111111111111111111111111012@", FN_OPT_NONE, {2147483645}, {0}, {38}, 1},
            (pc1Case32s){"2@#$%^&+11111111111111111111111111111012@", FN_OPT_NONE, {2147483645}, {0}, {39}, 1},
            (pc1Case32s){"2@#$%^&-11111111111111111111111111111012@", FN_OPT_NONE, {-2147483645}, {0}, {39}, 1},
            (pc1Case32s){"2@#$%^#", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32s){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32s){"21111111111111111111111111111101", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32s){"11111111111111111111111111111012", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {31}, 1},
            (pc1Case32s){"+11111111111111111111111111111012", FN_PC_NO_INVALID_SKIP, {2147483645}, {0}, {32}, 1},
            (pc1Case32s){"-11111111111111111111111111111012", FN_PC_NO_INVALID_SKIP, {-2147483645}, {0}, {32}, 1},
            (pc1Case32s){"2%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
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
            (pc1Case32s){"-10000000000000000000000000000001", FN_OPT_NONE, {-1073741824}, {0}, {32}, 1},
            (pc1Case32s){"-100000000000000000000000000000010", FN_OPT_NONE, {-1073741824}, {0}, {32}, 1},
            (pc1Case32s){"-100000000000000000000000000000000", FN_OPT_NONE, {-2147483648}, {0}, {33}, 1},
            (pc1Case32s){"-101010101010101010101010101010100", FN_OPT_NONE, {-1431655765}, {0}, {32}, 1},
            (pc1Case32s){"-1010101010101010101010101010101010101010101010101010101010101010101011", FN_OPT_NONE, {-1431655765}, {0}, {32}, 1},
            /* --> Overflow */
            (pc1Case32s){"10000000000000000000000000000000", FN_OPT_NONE, {1073741824}, {0}, {31}, 1},
            (pc1Case32s){"100000000000000000000000000000000", FN_OPT_NONE, {1073741824}, {0}, {31}, 1},
            (pc1Case32s){"11111111111111111111111111111110", FN_OPT_NONE, {2147483647}, {0}, {31}, 1},
            (pc1Case32s){"111111111111111111111111111111100", FN_OPT_NONE, {2147483647}, {0}, {31}, 1},
            (pc1Case32s){"10101010101010101010101010101010", FN_OPT_NONE, {1431655765}, {0}, {31}, 1},
            (pc1Case32s){"101010101010101010101010101010100", FN_OPT_NONE, {1431655765}, {0}, {31}, 1},
            (pc1Case32s){"1010101010101010101010101010101010101010101010101010101010101010101011", FN_OPT_NONE, {1431655765}, {0}, {31}, 1},
            /* OVERFLOW_ERROR opt */
            /* --> Underflow */
            (pc1Case32s){"-10000000000000000000000000000001", FN_PC_OVERFLOW_ERROR, {-1073741824}, {FN_ERROR_UNDERFLOW}, {32}, 1},
            (pc1Case32s){"-100000000000000000000000000000010", FN_PC_OVERFLOW_ERROR, {-1073741824}, {FN_ERROR_UNDERFLOW}, {32}, 1},
            (pc1Case32s){"-100000000000000000000000000000001", FN_PC_OVERFLOW_ERROR, {-2147483648}, {FN_ERROR_UNDERFLOW}, {33}, 1},
            (pc1Case32s){"-101010101010101010101010101010100", FN_PC_OVERFLOW_ERROR, {-1431655765}, {FN_ERROR_UNDERFLOW}, {32}, 1},
            (pc1Case32s){"-1010101010101010101010101010101010101010101010101010101010101010101011", FN_PC_OVERFLOW_ERROR, {-1431655765}, {FN_ERROR_UNDERFLOW}, {32}, 1},
            /* --> Overflow */
            (pc1Case32s){"10000000000000000000000000000000", FN_PC_OVERFLOW_ERROR, {1073741824}, {FN_ERROR_OVERFLOW}, {31}, 1},
            (pc1Case32s){"100000000000000000000000000000000", FN_PC_OVERFLOW_ERROR, {1073741824}, {FN_ERROR_OVERFLOW}, {31}, 1},
            (pc1Case32s){"11111111111111111111111111111110", FN_PC_OVERFLOW_ERROR, {2147483647}, {FN_ERROR_OVERFLOW}, {31}, 1},
            (pc1Case32s){"111111111111111111111111111111100", FN_PC_OVERFLOW_ERROR, {2147483647}, {FN_ERROR_OVERFLOW}, {31}, 1},
            (pc1Case32s){"10101010101010101010101010101010", FN_PC_OVERFLOW_ERROR, {1431655765}, {FN_ERROR_OVERFLOW}, {31}, 1},
            (pc1Case32s){"101010101010101010101010101010100", FN_PC_OVERFLOW_ERROR, {1431655765}, {FN_ERROR_OVERFLOW}, {31}, 1},
            (pc1Case32s){"1010101010101010101010101010101010101010101010101010101010101010101011", FN_PC_OVERFLOW_ERROR, {1431655765}, {FN_ERROR_OVERFLOW}, {31}, 1},
            /* OVERFLOW SKIP opt */
            /* --> Underflow */
            (pc1Case32s){"-10000000000000000000000000000001", FN_PC_OVERFLOW_SKIP, {-1073741824}, {0}, {-1}, 1},
            (pc1Case32s){"-100000000000000000000000000000010", FN_PC_OVERFLOW_SKIP, {-1073741824}, {0}, {-1}, 1},
            (pc1Case32s){"-100000000000000000000000000000001", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {-1}, 1},
            (pc1Case32s){"-101010101010101010101010101010100", FN_PC_OVERFLOW_SKIP, {-1431655765}, {0}, {-1}, 1},
            (pc1Case32s){"-1010101010101010101010101010101010101010101010101010101010101010101011", FN_PC_OVERFLOW_SKIP, {-1431655765}, {0}, {-1}, 1},
            (pc1Case32s){"-100000000000000000000000000000012", FN_PC_OVERFLOW_SKIP, {-1073741824}, {0}, {33}, 1},
            (pc1Case32s){"-1000000000000000000000000000000102", FN_PC_OVERFLOW_SKIP, {-1073741824}, {0}, {34}, 1},
            (pc1Case32s){"-1000000000000000000000000000000012", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {34}, 1},
            (pc1Case32s){"-1010101010101010101010101010101002", FN_PC_OVERFLOW_SKIP, {-1431655765}, {0}, {34}, 1},
            (pc1Case32s){"-10101010101010101010101010101010101010101010101010101010101010101010112", FN_PC_OVERFLOW_SKIP, {-1431655765}, {0}, {71}, 1},
            (pc1Case32s){"-10000000000000000000000000000001/", FN_PC_OVERFLOW_SKIP, {-1073741824}, {0}, {33}, 1},
            (pc1Case32s){"-100000000000000000000000000000010/", FN_PC_OVERFLOW_SKIP, {-1073741824}, {0}, {34}, 1},
            (pc1Case32s){"-100000000000000000000000000000001/", FN_PC_OVERFLOW_SKIP, {-2147483648}, {0}, {34}, 1},
            (pc1Case32s){"-101010101010101010101010101010100/", FN_PC_OVERFLOW_SKIP, {-1431655765}, {0}, {34}, 1},
            (pc1Case32s){"-1010101010101010101010101010101010101010101010101010101010101010101011/", FN_PC_OVERFLOW_SKIP, {-1431655765}, {0}, {71}, 1},
            /* --> Overflow */
            (pc1Case32s){"10000000000000000000000000000000", FN_PC_OVERFLOW_SKIP, {1073741824}, {0}, {-1}, 1},
            (pc1Case32s){"100000000000000000000000000000000", FN_PC_OVERFLOW_SKIP, {1073741824}, {0}, {-1}, 1},
            (pc1Case32s){"11111111111111111111111111111110", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"111111111111111111111111111111100", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {-1}, 1},
            (pc1Case32s){"10101010101010101010101010101010", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {-1}, 1},
            (pc1Case32s){"101010101010101010101010101010100", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {-1}, 1},
            (pc1Case32s){"1010101010101010101010101010101010101010101010101010101010101010101011", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {-1}, 1},
            (pc1Case32s){"100000000000000000000000000000002", FN_PC_OVERFLOW_SKIP, {1073741824}, {0}, {32}, 1},
            (pc1Case32s){"1000000000000000000000000000000002", FN_PC_OVERFLOW_SKIP, {1073741824}, {0}, {33}, 1},
            (pc1Case32s){"111111111111111111111111111111102", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {32}, 1},
            (pc1Case32s){"1111111111111111111111111111111002", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {33}, 1},
            (pc1Case32s){"101010101010101010101010101010102", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {32}, 1},
            (pc1Case32s){"1010101010101010101010101010101002", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {33}, 1},
            (pc1Case32s){"10101010101010101010101010101010101010101010101010101010101010101010112", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {70}, 1},
            (pc1Case32s){"10000000000000000000000000000000/", FN_PC_OVERFLOW_SKIP, {1073741824}, {0}, {32}, 1},
            (pc1Case32s){"100000000000000000000000000000000/", FN_PC_OVERFLOW_SKIP, {1073741824}, {0}, {33}, 1},
            (pc1Case32s){"11111111111111111111111111111110/", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {32}, 1},
            (pc1Case32s){"111111111111111111111111111111100/", FN_PC_OVERFLOW_SKIP, {2147483647}, {0}, {33}, 1},
            (pc1Case32s){"10101010101010101010101010101010/", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {32}, 1},
            (pc1Case32s){"101010101010101010101010101010100/", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {33}, 1},
            (pc1Case32s){"1010101010101010101010101010101010101010101010101010101010101010101011/", FN_PC_OVERFLOW_SKIP, {1431655765}, {0}, {70}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32s){"-10000000000000000000000000000002", FN_PC_OVERFLOW_ERROR, {-1073741824}, {0}, {32}, 1},
            (pc1Case32s){"-1000000000000000000000000000000/", FN_PC_OVERFLOW_ERROR, {-1073741824}, {0}, {32}, 1},
            (pc1Case32s){"-100000000000000000000000000000002", FN_PC_OVERFLOW_ERROR, {-2147483648}, {0}, {33}, 1},
            (pc1Case32s){"-10000000000000000000000000000000/", FN_PC_OVERFLOW_ERROR, {-2147483648}, {0}, {33}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, int32_t, tCase5, ALEN(tCase5), PRId32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32s tCase6[] = {
            (pc1Case32s){"1111011 +111011110 -10011101 $1111000 $-1111000", FN_OPT_NONE,
                         {123, 478, -157, 120, -120},
                         {0,0,0,0,0},
                         {7,18,28,37,-1},
                         5},
            (pc1Case32s){"0111011 +10101010101010101010101010101011111111 -100000000000000000000000000000001111 $1111000 $-1001101110000001100100", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {59, 1431655765, -2147483648, 120, -2547812},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_UNDERFLOW, 0, 0},
                         {7,47,85,94,-1},
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

int binToUInt32C1Test(){
    #define FUNCCALL binToUInt32C1
    const static char * testName = "binToUInt32C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_U(FUNCCALL, uint32_t, 1, 32, optArray, ALEN(optArray), PRIu32);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_U(FUNCCALL, uint32_t, 1, 32, PRIu32);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_U(FUNCCALL, uint32_t, 1, PRIu32);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");
        /* -1 Check nextPTR pointer is NULL */
        pc1Case32u tCase3[] = {
            /* a */
            (pc1Case32u){"11111111111111111111111111111110", FN_OPT_NONE, {4294967294U}, {0}, {-1}, 1},
            (pc1Case32u){"11111111111111111111111111111110", FN_OPT_PC1_ALL, {4294967294U}, {0}, {-1}, 1},
            /* b */
            (pc1Case32u){"11111111111111111111111111111111", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"11111111111111111111111111111111", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            /* c */
            (pc1Case32u){"0011111111111111111111111111111111", FN_OPT_NONE, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"0011111111111111111111111111111111", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case32u){"000011111111111111111111111111111111", FN_OPT_PC1_ALL, {4294967295U}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, uint32_t, tCase3, ALEN(tCase3), PRIu32);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case32u tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case32u){"-1", FN_OPT_NONE, {1}, {0}, {-1}, 1},
            (pc1Case32u){"2111111111111111111111111111111102", FN_OPT_NONE, {4294967294U}, {0}, {33}, 1},
            (pc1Case32u){"2@#$%^&111111111111111111111111111111102@", FN_OPT_NONE, {4294967294U}, {0}, {39}, 1},
            (pc1Case32u){"2@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case32u){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case32u){"+0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"-0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"211111111111111111111111111111110", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"111111111111111111111111111111102", FN_PC_NO_INVALID_SKIP, {4294967294U}, {0}, {32}, 1},
            (pc1Case32u){"2%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case32u){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, uint32_t, tCase4, ALEN(tCase4), PRIu32);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case32u tCase5[] = {
            /* Overflow default */
            (pc1Case32u){"100000000000000000000000000000001", FN_OPT_NONE, {2147483648U}, {0}, {32}, 1},
            (pc1Case32u){"1000000000000000000000000000000011", FN_OPT_NONE, {2147483648U}, {0}, {32}, 1},
            (pc1Case32u){"111111111111111111111111111111110", FN_OPT_NONE, {4294967295U}, {0}, {32}, 1},
            (pc1Case32u){"101010101010101010101010101010100", FN_OPT_NONE, {2863311530U}, {0}, {32}, 1},
            (pc1Case32u){"10101010101010101010101010101010010101010101010101010101010101010101010", FN_OPT_NONE, {2863311530U}, {0}, {32}, 1},
            /* OVERFLOW_ERROR opt */
            (pc1Case32u){"100000000000000000000000000000001", FN_PC_OVERFLOW_ERROR, {2147483648U}, {FN_ERROR_OVERFLOW}, {32}, 1},
            (pc1Case32u){"1000000000000000000000000000000011", FN_PC_OVERFLOW_ERROR, {2147483648U}, {FN_ERROR_OVERFLOW}, {32}, 1},
            (pc1Case32u){"111111111111111111111111111111110", FN_PC_OVERFLOW_ERROR, {4294967295U}, {FN_ERROR_OVERFLOW}, {32}, 1},
            (pc1Case32u){"101010101010101010101010101010100", FN_PC_OVERFLOW_ERROR, {2863311530U}, {FN_ERROR_OVERFLOW}, {32}, 1},
            (pc1Case32u){"10101010101010101010101010101010010101010101010101010101010101010101010", FN_PC_OVERFLOW_ERROR, {2863311530U}, {FN_ERROR_OVERFLOW}, {32}, 1},
            /* OVERFLOW SKIP opt */
            (pc1Case32u){"100000000000000000000000000000001", FN_PC_OVERFLOW_SKIP, {2147483648U}, {0}, {-1}, 1},
            (pc1Case32u){"1000000000000000000000000000000011", FN_PC_OVERFLOW_SKIP, {2147483648U}, {0}, {-1}, 1},
            (pc1Case32u){"111111111111111111111111111111110", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {-1}, 1},
            (pc1Case32u){"101010101010101010101010101010100", FN_PC_OVERFLOW_SKIP, {2863311530U}, {0}, {-1}, 1},
            (pc1Case32u){"10101010101010101010101010101010010101010101010101010101010101010101010", FN_PC_OVERFLOW_SKIP, {2863311530U}, {0}, {-1}, 1},
            (pc1Case32u){"1000000000000000000000000000000012", FN_PC_OVERFLOW_SKIP, {2147483648U}, {0}, {33}, 1},
            (pc1Case32u){"10000000000000000000000000000000112", FN_PC_OVERFLOW_SKIP, {2147483648U}, {0}, {34}, 1},
            (pc1Case32u){"1111111111111111111111111111111102", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {33}, 1},
            (pc1Case32u){"1010101010101010101010101010101002", FN_PC_OVERFLOW_SKIP, {2863311530U}, {0}, {33}, 1},
            (pc1Case32u){"101010101010101010101010101010100101010101010101010101010101010101010102", FN_PC_OVERFLOW_SKIP, {2863311530U}, {0}, {71}, 1},
            (pc1Case32u){"100000000000000000000000000000001/", FN_PC_OVERFLOW_SKIP, {2147483648U}, {0}, {33}, 1},
            (pc1Case32u){"1000000000000000000000000000000011/", FN_PC_OVERFLOW_SKIP, {2147483648U}, {0}, {34}, 1},
            (pc1Case32u){"111111111111111111111111111111110/", FN_PC_OVERFLOW_SKIP, {4294967295U}, {0}, {33}, 1},
            (pc1Case32u){"101010101010101010101010101010100/", FN_PC_OVERFLOW_SKIP, {2863311530U}, {0}, {33}, 1},
            (pc1Case32u){"10101010101010101010101010101010010101010101010101010101010101010101010/", FN_PC_OVERFLOW_SKIP, {2863311530U}, {0}, {71}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case32u){"111111111111111111111111111111112", FN_PC_OVERFLOW_ERROR, {4294967295U}, {0}, {32}, 1},
            (pc1Case32u){"11111111111111111111111111111111/", FN_PC_OVERFLOW_ERROR, {4294967295U}, {0}, {32}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, uint32_t, tCase5, ALEN(tCase5), PRIu32);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case32u tCase6[] = {
            (pc1Case32u){"1111011 1011010011101 100110000101011 $11000100011001010011010111111111 & $11010101100101100110", FN_OPT_NONE,
                         {123U, 5789U, 19499U, 3294967295U, 874854U},
                         {0,0,0,0,0},
                         {7,21,37,71,-1},
                         5},
                       /* 0         10        20        30        40        50       60         70        80        90        100       110*/
                       /* 012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789 */
            (pc1Case32u){"1111011 111111111111111111111111111111110000 10101010101010101010101010101010000000 $11000100011001010011010111111111 & $11010101100101100110", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {123U, 4294967295U, 2863311530U, 3294967295U, 874854U},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_OVERFLOW, 0, 0},
                         {7,44,83,117,-1},
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
