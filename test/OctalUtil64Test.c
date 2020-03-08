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
#include "../h/OctalUtil64.h"
#include "../testlib/testlib.c"
#include "test.h"

int octToInt64Test();
int octToInt64TrueErrorTest();
int octToUInt64Test();
int octToUInt64TrueErrorTest();

int octCompareTest64();
int octInt64OrSmallerTest();
int octCompareUTest64();
int octUInt64OrSmallerTest();

int octToInt64FPTest();
int octToUInt64FPTest();
int octToInt64FNTest();
int octToUInt64FNTest();

int octToInt64C1Test();
int octToUInt64C1Test();

int main(void){
    if ( octToInt64Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToInt64TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt64Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt64TrueErrorTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( octCompareTest64() == 1 ) return 1;
    puts("\n\n\n");
    if ( octInt64OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octCompareUTest64() == 1 ) return 1;
    puts("\n\n\n");
    if ( octUInt64OrSmallerTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( octToInt64FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt64FPTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToInt64FNTest() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt64FNTest() == 1 ) return 1;
    puts("\n\n\n");

    if ( octToInt64C1Test() == 1 ) return 1;
    puts("\n\n\n");
    if ( octToUInt64C1Test() == 1 ) return 1;

    return 0;
}

int octToInt64Test(){
    #define FUNCCALL octToInt64
    const static char * testName = "octToInt64";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int64_t, 7, 21, PRId64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int64_t, 7, 22, FN_ERROR_GENERAL, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64s tCase3[] = {
            (pCase64s){ "777777777777777777775",  9223372036854775805, 0},
            (pCase64s){"+777777777777777777775",  9223372036854775805, 0},
            (pCase64s){"-777777777777777777777", -9223372036854775807, 0},
            (pCase64s){ "777777777777777777777",  9223372036854775807, 0},
            (pCase64s){"+777777777777777777777",  9223372036854775807, 0},
            (pCase64s){"-1000000000000000000000", -9223372036854775807 - 1, 0},
            (pCase64s){"00777777777777777777777", 9223372036854775807, 0},
            (pCase64s){"+000", 0, 0},
            (pCase64s){"-00001000000000000000000000", -9223372036854775807 - 1, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3) , PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64s tCase4[] = {
            /* Underflow */
            (pCase64s){"-1000000000000000000001", -1152921504606846976, 1},
            (pCase64s){"-10000000000000000000000", -9223372036854775807 - 1, 1},
            (pCase64s){"-1234567012345670123450", -1505851632739161317, 1},
            /* Overflow */
            (pCase64s){"1000000000000000000000", 1152921504606846976, 1},
            (pCase64s){"7777777777777777777770", 9223372036854775807, 1},
            (pCase64s){"1234567012345670123450", 1505851632739161317, 1},
            (pCase64s){"10000000000000000000000", 1152921504606846976, 1},
            (pCase64s){"77777777777777777777700", 9223372036854775807, 1},
            (pCase64s){"12345670123456701234500", 1505851632739161317, 1},
            /* Invalid format */
            (pCase64s){"8123", 0, 1},
            (pCase64s){"-1234567012345670123458", -1505851632739161317, 1},
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

int octToInt64TrueErrorTest(){
    #define FUNCCALL octToInt64TrueError
    const static char * testName = "octToInt64TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_S(FUNCCALL, int64_t, 7, 21, PRId64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_S(FUNCCALL, int64_t, 7, 22, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64s tCase3[] = {
            (pCase64s){ "777777777777777777775",  9223372036854775805, 0},
            (pCase64s){"+777777777777777777775",  9223372036854775805, 0},
            (pCase64s){"-777777777777777777777", -9223372036854775807, 0},
            (pCase64s){ "777777777777777777777",  9223372036854775807, 0},
            (pCase64s){"+777777777777777777777",  9223372036854775807, 0},
            (pCase64s){"-1000000000000000000000", -9223372036854775807 - 1, 0},
            (pCase64s){"00777777777777777777777", 9223372036854775807, 0},
            (pCase64s){"+000", 0, 0},
            (pCase64s){"-00001000000000000000000000", -9223372036854775807 - 1, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64s tCase4[] = {
            /* Underflow */
            (pCase64s){"-1000000000000000000001", -1152921504606846976, FN_ERROR_UNDERFLOW},
            (pCase64s){"-10000000000000000000007", -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pCase64s){"-12345670123456701234507", -1505851632739161317, FN_ERROR_UNDERFLOW},
            (pCase64s){"-123456701234567012345071234567012345670123450", -1505851632739161317, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pCase64s){"1000000000000000000000", 1152921504606846976, FN_ERROR_OVERFLOW},
            (pCase64s){"7777777777777777777770", 9223372036854775807, FN_ERROR_OVERFLOW},
            (pCase64s){"1234567012345670123450", 1505851632739161317, FN_ERROR_OVERFLOW},
            (pCase64s){"10000000000000000000007", 1152921504606846976, FN_ERROR_OVERFLOW},
            (pCase64s){"77777777777777777777707", 9223372036854775807, FN_ERROR_OVERFLOW},
            (pCase64s){"12345670123456701234507", 1505851632739161317, FN_ERROR_OVERFLOW},
            (pCase64s){"123456701234567012345071234567012345670123450", 1505851632739161317, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase64s){"8123", 0, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1000000000000000000000/", 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-1000000000000000000001/", -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-1000000000000000000000/", -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"10000000000000000000008", 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-10000000000000000000018", -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-10000000000000000000008", -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1234567012345670123458", 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+1234567012345670123458", 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"12345670123456701234508", 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+12345670123456701234508", 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-12345670123456701234508", -1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"10000000000000000000008", 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+10000000000000000000008", 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-10000000000000000000018", -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"7777777777777777777778", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+7777777777777777777778", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"77777777777777777777708", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+77777777777777777777708", 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-10000000000000000000008", -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"10000000000000000000018", 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+10000000000000000000018", 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-10000000000000000000108", -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"1234567012345670123451234567012345670123458", 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"+1234567012345670123451234567012345670123458", 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pCase64s){"-123456701234567012345012345670123456701234508", -1505851632739161317, FN_ERROR_INVALID_FORMAT},
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

int octToUInt64Test(){
    #define FUNCCALL octToUInt64
    const static char * testName = "octToUInt64";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint64_t, 7, 22, PRIu64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint64_t, 7, 22, FN_ERROR_GENERAL, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64u tCase3[] = {
            (pCase64u){"1777777777777777777775", 18446744073709551613U, 0},
            (pCase64u){"1777777777777777777777", 18446744073709551615U, 0},
            (pCase64u){"001777777777777777777777", 18446744073709551615U, 0},
            (pCase64u){"000", 0, 0},
            (pCase64u){"00001777777777777777777777", 18446744073709551615U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64u tCase4[] = {
            /* Overflow */
            (pCase64u){"2000000000000000000000", 2305843009213693952U, 1},
            (pCase64u){"17777777777777777777770", 18446744073709551615U, 1},
            (pCase64u){"12345670123456701234560", 12046813061913290542U, 1},
            /* Invalid format */
            (pCase64u){"8213", 0, 1},
            (pCase64u){"12345670123456701234568", 12046813061913290542U, 1},
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

int octToUInt64TrueErrorTest(){
    #define FUNCCALL octToUInt64TrueError
    const static char * testName = "octToUInt64TrueError";

    printf("##### Start %s test #####\n", testName);

    /* START Test 1 */
    MAKE_P_CASES_TEST1_U(FUNCCALL, uint64_t, 7, 22, PRIu64);
    /* END Test 1 */

    /* START Test 2 */
    MAKE_P_CASES_TEST2_U(FUNCCALL, uint64_t, 7, 22, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# Test 3: Maximum values parsing and leading zero parsing.");

        pCase64u tCase3[] = {
            (pCase64u){"1777777777777777777775", 18446744073709551613U, 0},
            (pCase64u){"1777777777777777777777", 18446744073709551615U, 0},
            (pCase64u){"001777777777777777777777", 18446744073709551615U, 0},
            (pCase64u){"000", 0, 0},
            (pCase64u){"00001777777777777777777777", 18446744073709551615U, 0}
        };

        MAKE_P_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Parsing errors, test both error and return value.");

        pCase64u tCase4[] = {
            /* Overflow */
            (pCase64u){"2000000000000000000000", 2305843009213693952U, FN_ERROR_OVERFLOW},
            (pCase64u){"17777777777777777777777", 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pCase64u){"12345670123456701234567", 12046813061913290542U, FN_ERROR_OVERFLOW},
            (pCase64u){"123456701234567012345671234567012345670123456", 12046813061913290542U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pCase64u){"8214", 0, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"1234567012345670123456/", 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"2000000000000000000000/", 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"12345670123456701234568", 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"20000000000000000000008", 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"17777777777777777777778", 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"20000000000000000000018", 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pCase64u){"123456701234567012345612345670123456701234568", 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
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

int octCompareTest64(){
    #define FUNCCALL octCompareAsInt64
    const static char * testName = "octCompareAsInt64";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"777777777777777777777", "-1000000000000000000000", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"777777777777777777777", "777777777777777777777", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"-1000000000000000000000", "777777777777777777777", -1, 0}
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
            (cCase){"-1000000000000000000001", "1", 0, 1},
            (cCase){"1", "1000000000000000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octInt64OrSmallerTest(){
    #define FUNCCALL octInt64OrSmaller
    const static char * testName = "octInt64OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "-1234567012345670123450", -1},
            (cCaseNE){"!1", "1234567012345670123450", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "777777777777777777777", -1},
            /* UnderFlow to */
            (cCaseNE){"-1234567012345670123450", "!1", 1},
            (cCaseNE){"-1234567012345670123450", "-1000000000000000000001", 0},
            (cCaseNE){"-1234567012345670123450", "1234567012345670123450", -1},
            (cCaseNE){"-1234567012345670123450", "", -1},
            (cCaseNE){"-1234567012345670123450", "-1000000000000000000000", -1},
            /* OverFlow to */
            (cCaseNE){"1234567012345670123450", "!1", 1},
            (cCaseNE){"1234567012345670123450", "-1234567012345670123450", 1},
            (cCaseNE){"1234567012345670123450", "1000000000000000000000", 0},
            (cCaseNE){"1234567012345670123450", "", -1},
            (cCaseNE){"1234567012345670123450", "777777777777777777777", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "-1234567012345670123450", 1},
            (cCaseNE){"", "1234567012345670123450", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "-1000000000000000000000", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "-1234567012345670123450", 1},
            (cCaseNE){"1", "1234567012345670123450", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"-1000000000000000000000", "777777777777777777777" , -1},
            (cCaseNE){"-1000000000000000000000", "-1000000000000000000000" , 0},
            (cCaseNE){"777777777777777777777", "-1000000000000000000000" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octCompareUTest64(){
    #define FUNCCALL octCompareAsUInt64
    const static char * testName = "octCompareAsUInt64";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Right format comparision.");

        cCase tCase1[] = {
            /* firstString > secondString(1) */
            (cCase){"1777777777777777777777", "1777777777777777777775", 1, 0},
            /* firstString == secondString(0) */
            (cCase){"1777777777777777777777", "1777777777777777777777", 0, 0},
            /* firstString < secondString(-1) */
            (cCase){"1777777777777777777775", "1777777777777777777777", -1, 0}
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
            (cCase){"2000000000000000000000", "1", 0, 1},
            (cCase){"1", "2000000000000000000000", 0, 1}
        };

        MAKE_C_CASES_LOOP("Test 2", FUNCCALL, tCase2, ALEN(tCase2));
        puts ("# Test 2: Passed.");
    } /* END Test 2 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octUInt64OrSmallerTest(){
    #define FUNCCALL octUInt64OrSmaller
    const static char * testName = "octUInt64OrSmaller";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        puts ("# TEST 1: Case to case.");

        cCaseNE tCase1[] = {
            /* Invalid to */
            (cCaseNE){"!1", "1!", 0},
            (cCaseNE){"!1", "12345670123456701234560", -1},
            (cCaseNE){"!1", "", -1},
            (cCaseNE){"!1", "1777777777777777777777", -1},
            /* OverFlow to */
            (cCaseNE){"12345670123456701234560", "!1", 1},
            (cCaseNE){"12345670123456701234560", "2000000000000000000000", 0},
            (cCaseNE){"12345670123456701234560", "", -1},
            (cCaseNE){"12345670123456701234560", "1777777777777777777777", -1},
            /* Empty to */
            (cCaseNE){"", "!1", 1},
            (cCaseNE){"", "12345670123456701234560", 1},
            (cCaseNE){"", "", 0},
            (cCaseNE){"", "1777777777777777777777", -1},
            /* Valid to */
            (cCaseNE){"1", "!1", 1},
            (cCaseNE){"1", "12345670123456701234560", 1},
            (cCaseNE){"1", "", 1},
            (cCaseNE){"1777777777777777777775", "1777777777777777777777" , -1},
            (cCaseNE){"1777777777777777777777", "1777777777777777777777" , 0},
            (cCaseNE){"1777777777777777777777", "1777777777777777777775" , 1}
        };

        MAKE_C_CASESNE_LOOP("Test 1", FUNCCALL, tCase1, ALEN(tCase1));
        puts ("# Test 1: Passed.");
    } /* END Test 1 */

    printf ("##### End %s test #####\n", testName);
    return 0;
    #undef FUNCCALL
}

int octToInt64FPTest(){
    #define FUNCCALL octToInt64FP
    const static char * testName = "octToInt64FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_S(FUNCCALL, int64_t, 7, 21, optArray, ALEN(optArray), PRId64);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_S(FUNCCALL, int64_t, 7, 21, 23, PRId64);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_S(FUNCCALL, int64_t, 7, 22, 23, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        /* (char input, from, to, opt, exp1(result), exp2(error)) */
        pfpCase64s tCase3[] = {
            (pfpCase64s){"777777777777777777775", 0, 20, FN_OPT_NONE, 9223372036854775805, 0},
            (pfpCase64s){"777777777777777777775", 0, 20, FN_OPT_PFP_ALL, 9223372036854775805, 0},
            (pfpCase64s){"+777777777777777777775", 0, 21, FN_OPT_PFP_ALL, 9223372036854775805, 0},
            (pfpCase64s){"-777777777777777777777", 0, 21, FN_OPT_PFP_ALL, -9223372036854775807, 0},
                       /* 0123456789012345678901234 */
            (pfpCase64s){"777777777777777777777", 0, 20, FN_OPT_NONE, 9223372036854775807, 0},
            (pfpCase64s){"777777777777777777777", 0, 20, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"+777777777777777777777", 0, 21, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"-1000000000000000000000", 0, 22, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0},
            (pfpCase64s){"00777777777777777777777", 0, 22, FN_OPT_NONE, 9223372036854775807, 0},
            (pfpCase64s){"00777777777777777777777", 0, 22, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"+000", 0, 3, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase64s){"-000001000000000000000000000", 0, 27, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase64s tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase64s){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase64s){"  14", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase64s){"    -777777777777777777777", 0, 25, FN_PF_IGNORE_LSPACES, -9223372036854775807, 0},
            (pfpCase64s){"   -1000000000000000000000", 0, 25, FN_PF_IGNORE_LSPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"     777777777777777777777", 0, 25, FN_PF_IGNORE_LSPACES, 9223372036854775807, 0},
            (pfpCase64s){"   173  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase64s){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase64s){"14  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase64s){"-777777777777777777777    ", 0, 25, FN_PF_IGNORE_TSPACES, -9223372036854775807, 0},
            (pfpCase64s){"-1000000000000000000000   ", 0, 25, FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"777777777777777777777     ", 0, 25, FN_PF_IGNORE_TSPACES, 9223372036854775807, 0},
            (pfpCase64s){" 30071  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase64s){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase64s){" -1 ", 0, 3, FN_PF_IGNORE_SPACES, -1, 0},
            (pfpCase64s){"   -000  ", 0, 8, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase64s){"   -777777777777777777777   ", 0, 27, FN_PF_IGNORE_SPACES, -9223372036854775807, 0},
            (pfpCase64s){"   -1000000000000000000000  ", 0, 27, FN_PF_IGNORE_SPACES, -9223372036854775807 - 1, 0},
            (pfpCase64s){"   777777777777777777777    ", 0, 27, FN_PF_IGNORE_SPACES, 9223372036854775807, 0},
            (pfpCase64s){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase64s tCase5[] = {
            /* Underflow */
            (pfpCase64s){"-1000000000000000000001", 0, 22, FN_OPT_NONE, -1152921504606846976, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"-10000000000000000000000", 0, 23, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"-12345670123456701234500", 0, 22, FN_OPT_NONE, -1505851632739161317, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfpCase64s){"1000000000000000000000", 0, 21, FN_OPT_NONE, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfpCase64s){"7777777777777777777770", 0, 21, FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"1234567012345670123450", 0, 21, FN_OPT_NONE, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfpCase64s){"10000000000000000000000", 0, 21, FN_OPT_NONE, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfpCase64s){"77777777777777777777700", 0, 21, FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"12345670123456701234500", 0, 22, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase64s){"8123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"8123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1234567012345670123458", 0, 21, FN_OPT_NONE, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+1234567012345670123458", 0, 22, FN_OPT_NONE, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"12345670123456701234508", 0, 22, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+12345670123456701234508", 0, 23, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-12345670123456701234508", 0, 23, FN_OPT_NONE, 0, FN_ERROR_UNDERFLOW},
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
            (pfpCase64s){"81234567012345670123450", 0, 22, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"+81234567012345670123450", 0, 23, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-81234567012345670123450", 0, 23, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"12345670123456701234508", 0, 22, FN_PF_PARSE_ON_ERROR,
                         1505851632739161317, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+12345670123456701234508", 0, 23, FN_PF_PARSE_ON_ERROR,
                         1505851632739161317, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-12345670123456701234508", 0, 23, FN_PF_PARSE_ON_ERROR,
                         -1505851632739161317, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"10000000000000000000008", 0, 22, FN_PF_PARSE_ON_ERROR,
                         1152921504606846976, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+10000000000000000000008", 0, 23, FN_PF_PARSE_ON_ERROR,
                         1152921504606846976, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-10000000000000000000018", 0, 23, FN_PF_PARSE_ON_ERROR,
                         -1152921504606846976, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"77777777777777777777708", 0, 22, FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+77777777777777777777708", 0, 23, FN_PF_PARSE_ON_ERROR,
                         9223372036854775807, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-10000000000000000000008", 0, 23, FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"10000000000000000000108", 0, 22, FN_PF_PARSE_ON_ERROR,
                         1152921504606846977, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+10000000000000000000108", 0, 23, FN_PF_PARSE_ON_ERROR,
                         1152921504606846977, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-10000000000000000000108", 0, 23, FN_PF_PARSE_ON_ERROR,
                         -1152921504606846977, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"123456701234567012345012345670123456701234508", 0, 44, FN_PF_PARSE_ON_ERROR,
                         1505851632739161317, FN_ERROR_OVERFLOW},
            (pfpCase64s){"+123456701234567012345012345670123456701234508", 0, 45, FN_PF_PARSE_ON_ERROR,
                         1505851632739161317, FN_ERROR_OVERFLOW},
            (pfpCase64s){"-123456701234567012345012345670123456701234508", 0, 45, FN_PF_PARSE_ON_ERROR,
                         -1505851632739161317, FN_ERROR_UNDERFLOW},
            /* Long Check */
            (pfpCase64s){":1234567012345670123450", 0, 22, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"1000000000000000000000/", 0, 22, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-100000000000000000000081000000000000000000000", 0, 45, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-100000000000000000000081000000000000000000000", 0, 45, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-100000000000000000000071000000000000000000000", 0, 45, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfpCase64s){"100000000000000000000081000000000000000000000", 0, 44, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-100000000000000000000181000000000000000000001", 0, 45, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-100000000000000000001081000000000000000000010", 0, 45, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfpCase64s){"-10000000000000000000007", 0, 23, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         -9223372036854775807 - 1, FN_ERROR_UNDERFLOW}
        };

        MAKE_PFP_CASES_LOOP("Test 6", FUNCCALL, int64_t, tCase6, ALEN(tCase6), PRId64);
        puts ("# Test 6: Passed.\n");
    } /* END Test 6 */

    { /* START Test 7 */
        puts ("# TEST 7: Positioning test.");

        pfpCase64s tCase7[] = {
            (pfpCase64s){"This number 57060515 is parseable.",
                         12, 19, FN_OPT_NONE, 12345677, 0},
            (pfpCase64s){"Number(726746425) to array.",
                         7, 15, FN_OPT_PFP_ALL, 123456789, 0},
            (pfpCase64s){"At least this one(-11145401322) with sign must pass.",
                         18, 29, FN_OPT_PFP_ALL, -1234567890, 0},
                       /*           10        20        30        40         */
                       /* 01234567890123456789012345678901234567890123456789 */
            (pfpCase64s){"Important number:+777777777777777777777(INT MAX VALUE)",
                         17, 38, FN_OPT_PFP_ALL, 9223372036854775807, 0},
            (pfpCase64s){"Another one:-1000000000000000000000(INT64 MIN VALUE)",
                         12, 34, FN_OPT_PFP_ALL, -9223372036854775807 - 1, 0},
            (pfpCase64s){"Parse after the seven 123456710543563155to before the last five",
                         29, 38, FN_OPT_PFP_ALL, 145874125, 0},
            (pfpCase64s){"From next space   -726746425    (to prior space)",
                         15, 31, FN_OPT_PFP_ALL, -123456789, 0},
            (pfpCase64s){"Without any ingore spaces   -11145401322    with spaces parse will fail."
                         "And the segment considered to be overflow, or contain an invalid format"
                         "depends on FN_PF_LONG_CHECK",
                         25, 43, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int octToUInt64FPTest(){
    #define FUNCCALL octToUInt64FP
    const static char * testName = "octToUInt64FP";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1A */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK, FN_PF_PARSE_ON_ERROR
        };

        MAKE_PFP_CASES_TEST1A_U(FUNCCALL, uint64_t, 7, 22, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1A */

    /* START Test 1B */
    MAKE_PFP_CASES_TEST1B_U(FUNCCALL, uint64_t, 7, 22, 23, PRIu64);
    /* END Test 1B */

    /* START Test 2 */
    MAKE_PFP_CASES_TEST2_U(FUNCCALL, uint64_t, 7, 22, 23, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    { /* START Test 3 */
        puts ("# TEST 3: Main parser test.");

        pfpCase64u tCase3[] = {
            (pfpCase64u){"1777777777777777777775", 0, 21, FN_OPT_NONE, 18446744073709551613U, 0},
            (pfpCase64u){"1777777777777777777775", 0, 21, FN_OPT_PFP_ALL, 18446744073709551613U, 0},
            (pfpCase64u){"1777777777777777777777", 0, 21, FN_OPT_NONE, 18446744073709551615U, 0},
            (pfpCase64u){"1777777777777777777777", 0, 21, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"001777777777777777777777", 0, 23, FN_OPT_NONE, 18446744073709551615U, 0},
            (pfpCase64u){"001777777777777777777777", 0, 23, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"000", 0, 2, FN_OPT_PFP_ALL, 0, 0},
            (pfpCase64u){"00001777777777777777777777", 0, 25, FN_OPT_NONE, 18446744073709551615U, 0}
        };

        MAKE_PFP_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: The ignore spaces options.");

        pfpCase64u tCase4[] = {
            /* Ignore Leading Spaces */
            (pfpCase64u){" 1", 0, 1, FN_PF_IGNORE_LSPACES, 1, 0},
            (pfpCase64u){"  14", 0, 3, FN_PF_IGNORE_LSPACES, 12, 0},
            (pfpCase64u){"   1777777777777777777775", 0, 24, FN_PF_IGNORE_LSPACES, 18446744073709551613U, 0},
            (pfpCase64u){"   1777777777777777777777", 0, 24, FN_PF_IGNORE_LSPACES, 18446744073709551615U, 0},
            (pfpCase64u){"   173  ", 0, 7, FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            (pfpCase64u){"1 ", 0, 1, FN_PF_IGNORE_TSPACES, 1, 0},
            (pfpCase64u){"14  ", 0, 3, FN_PF_IGNORE_TSPACES, 12, 0},
            (pfpCase64u){"1777777777777777777775   ", 0, 24, FN_PF_IGNORE_TSPACES, 18446744073709551613U, 0},
            (pfpCase64u){"1777777777777777777777   ", 0, 24, FN_PF_IGNORE_TSPACES, 18446744073709551615U, 0},
            (pfpCase64u){" 30071  ", 0, 7, FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfpCase64u){" 1 ", 0, 2, FN_PF_IGNORE_SPACES, 1, 0},
            (pfpCase64u){"   000  ", 0, 7, FN_PF_IGNORE_SPACES, 0, 0},
            (pfpCase64u){"   1777777777777777777775   ", 0, 27, FN_PF_IGNORE_SPACES, 18446744073709551613U, 0},
            (pfpCase64u){"   1777777777777777777777   ", 0, 27, FN_PF_IGNORE_SPACES, 18446744073709551615U, 0},
            (pfpCase64u){"   ", 0, 2, FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFP_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Error parsing.");

        pfpCase64u tCase5[] = {
            /* Overflow */
            (pfpCase64u){"2000000000000000000000", 0, 21, FN_OPT_NONE, 2305843009213693952U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"2000000000000000000010", 0, 21, FN_OPT_NONE, 2305843009213693953U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"17777777777777777777770", 0, 22, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            (pfpCase64u){"12345670123456701234567", 0, 22, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfpCase64u){"8123", 0, 3, FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"8123", 0, 3, FN_OPT_PFP_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"123456701234567012345671234567012345670123456708", 0, 47, FN_OPT_NONE, 0, FN_ERROR_OVERFLOW},
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
            (pfpCase64u){"81234567012345670123450", 0, 22, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"12345670123456701234508", 0, 22, FN_PF_PARSE_ON_ERROR, 12046813061913290536U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"20000000000000000000008", 0, 22, FN_PF_PARSE_ON_ERROR, 2305843009213693952U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"17777777777777777777778", 0, 22, FN_PF_PARSE_ON_ERROR, 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"20000000000000000000108", 0, 22, FN_PF_PARSE_ON_ERROR, 2305843009213693953U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"12345670123456701234508", 0, 22, FN_PF_PARSE_ON_ERROR, 12046813061913290536U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"+12345670123456701234501", 0, 23, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"-12345670123456701234501", 0, 23, FN_PF_PARSE_ON_ERROR, 0, FN_ERROR_INVALID_FORMAT},
            /* Long Check */
            (pfpCase64u){"81234567012345670123450", 0, 22, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"1234567012345670123450/", 0, 22, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"123456701234567012345081234567012345670123450", 0, 44, FN_PF_LONG_CHECK,
                         0, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"123456701234567012345081234567012345670123450", 0, 44, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         12046813061913290536U, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"200000000000000000000082000000000000000000000", 0, 44, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfpCase64u){"200000000000000000000072000000000000000000000", 0, 44, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
                         2305843009213693952U, FN_ERROR_OVERFLOW},
            (pfpCase64u){"17777777777777777777777", 0, 22, FN_PF_LONG_CHECK | FN_PF_PARSE_ON_ERROR,
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
            (pfpCase64u){"This number 57060515 is parseable.",
                       12, 19, FN_OPT_NONE, 12345677U, 0},
            (pfpCase64u){"Number(726746425) to array.",
                       7, 15, FN_OPT_PFP_ALL, 123456789U, 0},
                       /*           10        20        30        40        50          */
                       /* 012345678901234567890123456789012345678901234567890123456789  */
            (pfpCase64u){"Important number:+1777777777777777777777(UINT64 MAX VALUE), The + is not parsed.",
                       18, 39, FN_OPT_PFP_ALL, 18446744073709551615U, 0},
            (pfpCase64u){"Parse after the seven 123456771041723035to before the last five",
                       29, 38, FN_OPT_PFP_ALL, 957412547U, 0},
            (pfpCase64u){"From next space   11145401322    (to prior space)",
                       15, 32, FN_OPT_PFP_ALL, 1234567890U, 0},
            (pfpCase64u){"Without any ingore spaces   11145401322    with spaces parse will fail."
                       "And the segment considered to be overflow, or contain an invalid format"
                       "depends on FN_PF_LONG_CHECK",
                       25, 42, FN_PF_LONG_CHECK, 0, FN_ERROR_INVALID_FORMAT}
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

int octToInt64FNTest(){
    #define FUNCCALL octToInt64FN
    const static char * testName = "octToInt64FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_S(FUNCCALL, int64_t, 7, 21, optArray, ALEN(optArray), PRId64);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_S(FUNCCALL, int64_t, 7, 22, FN_ERROR_INVALID_FORMAT, PRId64);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_S(FUNCCALL, int64_t, 7, 21, PRId64);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase64s tCase4[] = {
            (pfnCase64s){"777777777777777777775", FN_OPT_NONE, 9223372036854775805, 0},
            (pfnCase64s){"777777777777777777775", FN_OPT_PFN_ALL, 9223372036854775805, 0},
            (pfnCase64s){"+777777777777777777775", FN_OPT_PFN_ALL, 9223372036854775805, 0},
            (pfnCase64s){"-777777777777777777777", FN_OPT_PFN_ALL, -9223372036854775807, 0},
            (pfnCase64s){"777777777777777777777", FN_OPT_NONE, 9223372036854775807, 0},
            (pfnCase64s){"777777777777777777777", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"+777777777777777777777", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"-1000000000000000000000", FN_OPT_PFN_ALL, -9223372036854775807 - 1, 0},
            (pfnCase64s){"00777777777777777777777", FN_OPT_NONE, 9223372036854775807, 0},
            (pfnCase64s){"00777777777777777777777", FN_OPT_PFN_ALL, 9223372036854775807, 0},
            (pfnCase64s){"+000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase64s){"-00001000000000000000000000", FN_OPT_PFN_ALL, -9223372036854775807 - 1, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, int64_t, tCase4, ALEN(tCase4), PRId64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase64s tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase64s){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase64s){" 14", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase64s){"    -777777777777777777777", FN_PF_IGNORE_LSPACES, -9223372036854775807, 0},
            (pfnCase64s){"   -1000000000000000000000", FN_PF_IGNORE_LSPACES, -9223372036854775807 - 1 , 0},
            (pfnCase64s){"     777777777777777777777", FN_PF_IGNORE_LSPACES, 9223372036854775807, 0},
            (pfnCase64s){"   173  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase64s){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase64s){"14  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase64s){"-777777777777777777777    ", FN_PF_IGNORE_TSPACES, -9223372036854775807, 0},
            (pfnCase64s){"-1000000000000000000000  ", FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, 0},
            (pfnCase64s){"777777777777777777777     ", FN_PF_IGNORE_TSPACES, 9223372036854775807, 0},
            (pfnCase64s){" 30071  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase64s){"1000000000000000000000  ", FN_PF_IGNORE_TSPACES, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+1000000000000000000000  ", FN_PF_IGNORE_TSPACES, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-1000000000000000000010  ", FN_PF_IGNORE_TSPACES, -1152921504606846977, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-1000000000000000000001  ", FN_PF_IGNORE_TSPACES, -1152921504606846976, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-10000000000000000000000  ", FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64s){"10000000000000000000008  ", FN_PF_IGNORE_TSPACES, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+10000000000000000000008  ", FN_PF_IGNORE_TSPACES, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-10000000000000000000108  ", FN_PF_IGNORE_TSPACES, -1152921504606846977, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-10000000000000000000018  ", FN_PF_IGNORE_TSPACES, -1152921504606846976, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-10000000000000000000008  ", FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"123456701234567012345/  ", FN_PF_IGNORE_TSPACES, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567012345670123458  ", FN_PF_IGNORE_TSPACES, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1000000000000000000000  0", FN_PF_IGNORE_TSPACES, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1000000000000000000000  0", FN_PF_IGNORE_TSPACES, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000010  0", FN_PF_IGNORE_TSPACES, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000001  0", FN_PF_IGNORE_TSPACES, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000000  0", FN_PF_IGNORE_TSPACES, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase64s){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase64s){" -1 ", FN_PF_IGNORE_SPACES, -1, 0},
            (pfnCase64s){"   -000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase64s){"   -777777777777777777777      ", FN_PF_IGNORE_SPACES, -9223372036854775807, 0},
            (pfnCase64s){"   -1000000000000000000000     ", FN_PF_IGNORE_SPACES, -9223372036854775807 - 1, 0},
            (pfnCase64s){"   777777777777777777777       ", FN_PF_IGNORE_SPACES, 9223372036854775807, 0},
            (pfnCase64s){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, int64_t, tCase5, ALEN(tCase5), PRId64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase64s tCase6[] = {
            /* Underflow */
            (pfnCase64s){"-1000000000000000000001", FN_OPT_NONE, -1152921504606846976, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-10000000000000000000000", FN_OPT_NONE, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-12345670123456701234500", FN_OPT_NONE, -1505851632739161317, FN_ERROR_UNDERFLOW},
            /* Overflow */
            (pfnCase64s){"1000000000000000000000", FN_OPT_NONE, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"7777777777777777777770", FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"1234567012345670123450", FN_OPT_NONE, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfnCase64s){"10000000000000000000000", FN_OPT_NONE, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"77777777777777777777700", FN_OPT_NONE, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"12345670123456701234500", FN_OPT_NONE, 1505851632739161317, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase64s){"8123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"8123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567012345670123458", FN_OPT_NONE, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567012345670123458", FN_OPT_NONE, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"12345670123456701234508", FN_OPT_NONE, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+12345670123456701234508", FN_OPT_NONE, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-12345670123456701234508", FN_OPT_NONE, -1505851632739161317, FN_ERROR_UNDERFLOW},
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
            (pfnCase64s){"10000000000000000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+10000000000000000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-10000000000000000000107  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-10000000000000000000017  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"-10000000000000000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64s){"10000000000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+10000000000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000100 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000010 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"100000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+100000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-100000000000000000001000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-100000000000000000000100  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-100000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase64s){"1000000000000000000000  ", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1000000000000000000000  ", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000010  ", FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000001  ", FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000000  ", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"10000000000000000000000  ", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+10000000000000000000000  ", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000100  ", FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000010  ", FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000000  ", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"10000000000000000000008  ", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+10000000000000000000008  ", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000108  ", FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000018  ", FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000008  ", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase64s){"1000000000000000000000/", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1000000000000000000000/", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000010/", FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000001/", FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000000/", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"10000000000000000000008", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+10000000000000000000008", FN_PF_LONG_CHECK, 1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000108", FN_PF_LONG_CHECK, -1152921504606846977, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000018", FN_PF_LONG_CHECK, -1152921504606846976, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000008", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"123456701234567012345/", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+123456701234567012345/", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-1000000000000000000000/", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"1234567012345670123458", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+1234567012345670123458", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000008", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"12345670123456701234500", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+12345670123456701234500", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-12345670123456701234500", FN_PF_LONG_CHECK, -1505851632739161317, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"123456701234567012345012345670123456701234508", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+123456701234567012345012345670123456701234508", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-123456701234567012345012345670123456701234508", FN_PF_LONG_CHECK, -1505851632739161317, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"123456701234567012345012345670123456701234500", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+123456701234567012345012345670123456701234500", FN_PF_LONG_CHECK, 1505851632739161317, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-123456701234567012345012345670123456701234500", FN_PF_LONG_CHECK, -1505851632739161317, FN_ERROR_UNDERFLOW},
            (pfnCase64s){"77777777777777777777708", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"+77777777777777777777708", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"-10000000000000000000008", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_INVALID_FORMAT},
            (pfnCase64s){"77777777777777777777700", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"+77777777777777777777700", FN_PF_LONG_CHECK, 9223372036854775807, FN_ERROR_OVERFLOW},
            (pfnCase64s){"-10000000000000000000000", FN_PF_LONG_CHECK, -9223372036854775807 - 1, FN_ERROR_UNDERFLOW}
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

int octToUInt64FNTest(){
    #define FUNCCALL octToUInt64FN
    const static char * testName = "octToUInt64FN";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PF_IGNORE_LSPACES, FN_PF_IGNORE_TSPACES,
            FN_PF_LONG_CHECK
        };

        MAKE_PFN_CASES_TEST1_U(FUNCCALL, uint64_t, 7, 22, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1 */

    /* START Test 2 */
    MAKE_PFN_CASES_TEST2_U(FUNCCALL, uint64_t, 7, 22, FN_ERROR_INVALID_FORMAT, PRIu64);
    /* END Test 2 */

    /* START Test 3 */
    MAKE_PFN_CASES_TEST3_U(FUNCCALL, uint64_t, 7, 21, PRIu64);
    /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: Maximum values parsing and leading zero parsing.");

        pfnCase64u tCase4[] = {
            (pfnCase64u){"1777777777777777777775", FN_OPT_NONE, 18446744073709551613U, 0},
            (pfnCase64u){"1777777777777777777775", FN_OPT_PFN_ALL, 18446744073709551613U, 0},
            (pfnCase64u){"1777777777777777777777", FN_OPT_NONE, 18446744073709551615U, 0},
            (pfnCase64u){"1777777777777777777777", FN_OPT_PFN_ALL, 18446744073709551615U, 0},
            (pfnCase64u){"001777777777777777777777", FN_OPT_NONE, 18446744073709551615U, 0},
            (pfnCase64u){"001777777777777777777777", FN_OPT_PFN_ALL, 18446744073709551615U, 0},
            (pfnCase64u){"000", FN_OPT_PFN_ALL, 0, 0},
            (pfnCase64u){"00001777777777777777777777", FN_OPT_PFN_ALL, 18446744073709551615U, 0}
        };

        MAKE_PFN_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: The ignore spaces options.");

        pfnCase64u tCase5[] = {
            /* Ignore Leading Spaces */
            (pfnCase64u){" 1", FN_PF_IGNORE_LSPACES, 1, 0},
            (pfnCase64u){"  14", FN_PF_IGNORE_LSPACES, 12, 0},
            (pfnCase64u){"   1777777777777777777775", FN_PF_IGNORE_LSPACES, 18446744073709551613U, 0},
            (pfnCase64u){"   1777777777777777777777", FN_PF_IGNORE_LSPACES, 18446744073709551615U, 0},
            (pfnCase64u){"   173  ", FN_PF_IGNORE_LSPACES, 123, FN_ERROR_INVALID_FORMAT},
            /* Ignore Trailing Spaces */
            /* --> Original Cases */
            (pfnCase64u){"1 ", FN_PF_IGNORE_TSPACES, 1, 0},
            (pfnCase64u){"14  ", FN_PF_IGNORE_TSPACES, 12, 0},
            (pfnCase64u){"1777777777777777777775   ", FN_PF_IGNORE_TSPACES, 18446744073709551613U, 0},
            (pfnCase64u){"1777777777777777777777   ", FN_PF_IGNORE_TSPACES, 18446744073709551615U, 0},
            (pfnCase64u){" 30071  ", FN_PF_IGNORE_TSPACES, 0, FN_ERROR_INVALID_FORMAT},
            /* --> Overflow Check*/
            (pfnCase64u){"2000000000000000000000  ", FN_PF_IGNORE_TSPACES, 2305843009213693952U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"12345670123456701234560  ", FN_PF_IGNORE_TSPACES, 12046813061913290542U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64u){"20000000000000000000008  ", FN_PF_IGNORE_TSPACES, 2305843009213693952U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"12345670123456701234568  ", FN_PF_IGNORE_TSPACES, 12046813061913290542U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"2000000000000000000000  0", FN_PF_IGNORE_TSPACES, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567012345670123456  0", FN_PF_IGNORE_TSPACES, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            /* Ignore Both, Leading and Trailing Spaces */
            (pfnCase64u){" 1 ", FN_PF_IGNORE_SPACES, 1, 0},
            (pfnCase64u){"   000  ", FN_PF_IGNORE_SPACES, 0, 0},
            (pfnCase64u){"   1777777777777777777775  ", FN_PF_IGNORE_SPACES, 18446744073709551613U, 0},
            (pfnCase64u){"   1777777777777777777777  ", FN_PF_IGNORE_SPACES, 18446744073709551615U, 0},
            (pfnCase64u){"   ", FN_PF_IGNORE_SPACES, 0, FN_ERROR_EMPTY_STR}
        };

        MAKE_PFN_CASES_LOOP("Test 5", FUNCCALL, uint64_t, tCase5, ALEN(tCase5), PRIu64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Error parsing without long check.");

        pfnCase64u tCase6[] = {
            /* Overflow */
            (pfnCase64u){"2000000000000000000000", FN_OPT_NONE, 2305843009213693952U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"2000000000000000000010", FN_OPT_NONE, 2305843009213693953U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"17777777777777777777770", FN_OPT_NONE, 18446744073709551615U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"12345670123456701234500", FN_OPT_NONE, 12046813061913290536U, FN_ERROR_OVERFLOW},
            /* Invalid format */
            (pfnCase64u){"8123", FN_OPT_NONE, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"8123", FN_OPT_PFN_ALL, 0, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567012345670123450/", FN_OPT_NONE, 12046813061913290536U, FN_ERROR_OVERFLOW},
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
            (pfnCase64u){"20000000000000000000007  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"12345670123456701234567  ", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_OVERFLOW},
            /* --> Invalid Format Check */
            (pfnCase64u){"2000000000000000000000 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567012345670123456 0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"20000000000000000000000  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345670123456701234560  0", FN_PF_IGNORE_TSPACES | FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            /* Without IGNORE_TSPACES */
            /* --> With trailing spaces */
            (pfnCase64u){"2000000000000000000000  ", FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567012345670123456  ", FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"20000000000000000000000  ", FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345670123456701234560  ", FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"20000000000000000000008  ", FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345670123456701234568  ", FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            /* --> Without trailing spaces */
            (pfnCase64u){"2000000000000000000000/", FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"20000000000000000000008", FN_PF_LONG_CHECK, 2305843009213693952U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"1234567012345670123456/", FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345670123456701234568", FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"12345670123456701234567", FN_PF_LONG_CHECK, 12046813061913290542U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"123456701234567012345012345670123456701234508", FN_PF_LONG_CHECK, 12046813061913290536U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"123456701234567012345012345670123456701234500", FN_PF_LONG_CHECK, 12046813061913290536U, FN_ERROR_OVERFLOW},
            (pfnCase64u){"17777777777777777777778", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_INVALID_FORMAT},
            (pfnCase64u){"17777777777777777777770", FN_PF_LONG_CHECK, 18446744073709551615U, FN_ERROR_OVERFLOW}
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

int octToInt64C1Test(){
    #define FUNCCALL octToInt64C1
    const static char * testName = "octToInt64C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_S(FUNCCALL, int64_t, 7, 21, optArray, ALEN(optArray), PRId64);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_S( FUNCCALL, int64_t, 7, 22, PRId64);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_S( FUNCCALL, int64_t, 7, PRId64);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");

        pc1Case64s tCase3[] = {
            /* a */
            (pc1Case64s){"777777777777777777775", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+777777777777777777775", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+777777777777777777775", FN_OPT_PC1_ALL, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"-777777777777777777777", FN_OPT_NONE, {-9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"-777777777777777777777", FN_OPT_PC1_ALL, {-9223372036854775807}, {0}, {-1}, 1},
            /* b */
            (pc1Case64s){"777777777777777777777", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+777777777777777777777", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+777777777777777777777", FN_OPT_PC1_ALL, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"-1000000000000000000000", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-1000000000000000000000", FN_OPT_PC1_ALL, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            /* c */
            (pc1Case64s){"00777777777777777777777", FN_OPT_NONE, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"00777777777777777777777", FN_OPT_PC1_ALL, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"+000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case64s){"+000", FN_OPT_PC1_ALL, {0}, {0}, {-1}, 1},
            (pc1Case64s){"-00001000000000000000000000", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-00001000000000000000000000", FN_OPT_PC1_ALL, {-9223372036854775807 - 1}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, int64_t, tCase3, ALEN(tCase3), PRId64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case64s tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case64s){"-+777777777777777777775", FN_OPT_NONE, {9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"+-777777777777777777775", FN_OPT_NONE, {-9223372036854775805}, {0}, {-1}, 1},
            (pc1Case64s){"87777777777777777777758", FN_OPT_NONE, {9223372036854775805}, {0}, {22}, 1},
            (pc1Case64s){"8+7777777777777777777758", FN_OPT_NONE, {9223372036854775805}, {0}, {23}, 1},
            (pc1Case64s){"8-7777777777777777777758", FN_OPT_NONE, {-9223372036854775805}, {0}, {23}, 1},
            (pc1Case64s){"8@#$%^&7777777777777777777758@", FN_OPT_NONE, {9223372036854775805}, {0}, {28}, 1},
            (pc1Case64s){"8@#$%^&+7777777777777777777758@", FN_OPT_NONE, {9223372036854775805}, {0}, {29}, 1},
            (pc1Case64s){"8@#$%^&-7777777777777777777758@", FN_OPT_NONE, {-9223372036854775805}, {0}, {29}, 1},
            (pc1Case64s){"8@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case64s){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case64s){"8777777777777777777775", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64s){"7777777777777777777758", FN_PC_NO_INVALID_SKIP, {9223372036854775805}, {0}, {21}, 1},
            (pc1Case64s){"+7777777777777777777758", FN_PC_NO_INVALID_SKIP, {9223372036854775805}, {0}, {22}, 1},
            (pc1Case64s){"-7777777777777777777758", FN_PC_NO_INVALID_SKIP, {-9223372036854775805}, {0}, {22}, 1},
            (pc1Case64s){"8%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
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
            (pc1Case64s){"-1000000000000000000001", FN_OPT_NONE, {-1152921504606846976}, {0}, {22}, 1},
            (pc1Case64s){"-10000000000000000000017", FN_OPT_NONE, {-1152921504606846976}, {0}, {22}, 1},
            (pc1Case64s){"-10000000000000000000007", FN_OPT_NONE, {-9223372036854775807 - 1}, {0}, {23}, 1},
            (pc1Case64s){"-1000000000000000000010", FN_OPT_NONE, {-1152921504606846977}, {0}, {22}, 1},
            (pc1Case64s){"-10000000000000000000107", FN_OPT_NONE, {-1152921504606846977}, {0}, {22}, 1},
            (pc1Case64s){"-12345670123456701234507", FN_OPT_NONE, {-1505851632739161317}, {0}, {22}, 1},
            (pc1Case64s){"-123456701234567012345071234567012345670123450", FN_OPT_NONE, {-1505851632739161317}, {0}, {22}, 1},
            /* --> Overflow */
            (pc1Case64s){"1000000000000000000000", FN_OPT_NONE, {1152921504606846976}, {0}, {21}, 1},
            (pc1Case64s){"10000000000000000000007", FN_OPT_NONE, {1152921504606846976}, {0}, {21}, 1},
            (pc1Case64s){"7777777777777777777770", FN_OPT_NONE, {9223372036854775807}, {0}, {21}, 1},
            (pc1Case64s){"77777777777777777777707", FN_OPT_NONE, {9223372036854775807}, {0}, {21}, 1},
            (pc1Case64s){"1000000000000000000010", FN_OPT_NONE, {1152921504606846977}, {0}, {21}, 1},
            (pc1Case64s){"10000000000000000000107", FN_OPT_NONE, {1152921504606846977}, {0}, {21}, 1},
            (pc1Case64s){"1234567012345670123450", FN_OPT_NONE, {1505851632739161317}, {0}, {21}, 1},
            (pc1Case64s){"12345670123456701234507", FN_OPT_NONE, {1505851632739161317}, {0}, {21}, 1},
            (pc1Case64s){"123456701234567012345071234567012345670123450", FN_OPT_NONE, {1505851632739161317}, {0}, {21}, 1},
            /* OVERFLOW_ERROR opt */
            /* --> Underflow */
            (pc1Case64s){"-1000000000000000000001", FN_PC_OVERFLOW_ERROR, {-1152921504606846976}, {FN_ERROR_UNDERFLOW}, {22}, 1},
            (pc1Case64s){"-10000000000000000000017", FN_PC_OVERFLOW_ERROR, {-1152921504606846976}, {FN_ERROR_UNDERFLOW}, {22}, 1},
            (pc1Case64s){"-10000000000000000000007", FN_PC_OVERFLOW_ERROR, {-9223372036854775807 - 1}, {FN_ERROR_UNDERFLOW}, {23}, 1},
            (pc1Case64s){"-1000000000000000000010", FN_PC_OVERFLOW_ERROR, {-1152921504606846977}, {FN_ERROR_UNDERFLOW}, {22}, 1},
            (pc1Case64s){"-10000000000000000000107", FN_PC_OVERFLOW_ERROR, {-1152921504606846977}, {FN_ERROR_UNDERFLOW}, {22}, 1},
            (pc1Case64s){"-12345670123456701234507", FN_PC_OVERFLOW_ERROR, {-1505851632739161317}, {FN_ERROR_UNDERFLOW}, {22}, 1},
            (pc1Case64s){"-123456701234567012345071234567012345670123450", FN_PC_OVERFLOW_ERROR, {-1505851632739161317}, {FN_ERROR_UNDERFLOW}, {22}, 1},
            /* --> Overflow */
            (pc1Case64s){"1000000000000000000000", FN_PC_OVERFLOW_ERROR, {1152921504606846976}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"10000000000000000000007", FN_PC_OVERFLOW_ERROR, {1152921504606846976}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"7777777777777777777770", FN_PC_OVERFLOW_ERROR, {9223372036854775807}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"77777777777777777777707", FN_PC_OVERFLOW_ERROR, {9223372036854775807}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"1000000000000000000010", FN_PC_OVERFLOW_ERROR, {1152921504606846977}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"10000000000000000000107", FN_PC_OVERFLOW_ERROR, {1152921504606846977}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"1234567012345670123450", FN_PC_OVERFLOW_ERROR, {1505851632739161317}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"12345670123456701234507", FN_PC_OVERFLOW_ERROR, {1505851632739161317}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64s){"123456701234567012345071234567012345670123450", FN_PC_OVERFLOW_ERROR, {1505851632739161317}, {FN_ERROR_OVERFLOW}, {21}, 1},
            /* OVERFLOW SKIP opt */
            /* --> Underflow */
            (pc1Case64s){"-1000000000000000000001", FN_PC_OVERFLOW_SKIP, {-1152921504606846976}, {0}, {-1}, 1},
            (pc1Case64s){"-10000000000000000000017", FN_PC_OVERFLOW_SKIP, {-1152921504606846976}, {0}, {-1}, 1},
            (pc1Case64s){"-10000000000000000000007", FN_PC_OVERFLOW_SKIP, {-9223372036854775807 - 1}, {0}, {-1}, 1},
            (pc1Case64s){"-1000000000000000000010", FN_PC_OVERFLOW_SKIP, {-1152921504606846977}, {0}, {-1}, 1},
            (pc1Case64s){"-10000000000000000000107", FN_PC_OVERFLOW_SKIP, {-1152921504606846977}, {0}, {-1}, 1},
            (pc1Case64s){"-12345670123456701234507", FN_PC_OVERFLOW_SKIP, {-1505851632739161317}, {0}, {-1}, 1},
            (pc1Case64s){"-123456701234567012345071234567012345670123450", FN_PC_OVERFLOW_SKIP, {-1505851632739161317}, {0}, {-1}, 1},
            (pc1Case64s){"-10000000000000000000018", FN_PC_OVERFLOW_SKIP, {-1152921504606846976}, {0}, {23}, 1},
            (pc1Case64s){"-100000000000000000000108", FN_PC_OVERFLOW_SKIP, {-1152921504606846976}, {0}, {24}, 1},
            (pc1Case64s){"-100000000000000000000008", FN_PC_OVERFLOW_SKIP, {-9223372036854775807 - 1}, {0}, {24}, 1},
            (pc1Case64s){"-10000000000000000000108", FN_PC_OVERFLOW_SKIP, {-1152921504606846977}, {0}, {23}, 1},
            (pc1Case64s){"-100000000000000000001008", FN_PC_OVERFLOW_SKIP, {-1152921504606846977}, {0}, {24}, 1},
            (pc1Case64s){"-123456701234567012345008", FN_PC_OVERFLOW_SKIP, {-1505851632739161317}, {0}, {24}, 1},
            (pc1Case64s){"-123456701234567012345012345670123456701234508", FN_PC_OVERFLOW_SKIP, {-1505851632739161317}, {0}, {45}, 1},
            /* --> Overflow */
            (pc1Case64s){"1000000000000000000000", FN_PC_OVERFLOW_SKIP, {1152921504606846976}, {0}, {-1}, 1},
            (pc1Case64s){"10000000000000000000007", FN_PC_OVERFLOW_SKIP, {1152921504606846976}, {0}, {-1}, 1},
            (pc1Case64s){"7777777777777777777770", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"77777777777777777777707", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {-1}, 1},
            (pc1Case64s){"1000000000000000000010", FN_PC_OVERFLOW_SKIP, {1152921504606846977}, {0}, {-1}, 1},
            (pc1Case64s){"10000000000000000000107", FN_PC_OVERFLOW_SKIP, {1152921504606846977}, {0}, {-1}, 1},
            (pc1Case64s){"1234567012345670123450", FN_PC_OVERFLOW_SKIP, {1505851632739161317}, {0}, {-1}, 1},
            (pc1Case64s){"12345670123456701234507", FN_PC_OVERFLOW_SKIP, {1505851632739161317}, {0}, {-1}, 1},
            (pc1Case64s){"123456701234567012345071234567012345670123450", FN_PC_OVERFLOW_SKIP, {1505851632739161317}, {0}, {-1}, 1},
            (pc1Case64s){"10000000000000000000008", FN_PC_OVERFLOW_SKIP, {1152921504606846976}, {0}, {22}, 1},
            (pc1Case64s){"100000000000000000000008", FN_PC_OVERFLOW_SKIP, {1152921504606846976}, {0}, {23}, 1},
            (pc1Case64s){"77777777777777777777708", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {22}, 1},
            (pc1Case64s){"777777777777777777777008", FN_PC_OVERFLOW_SKIP, {9223372036854775807}, {0}, {23}, 1},
            (pc1Case64s){"10000000000000000000108", FN_PC_OVERFLOW_SKIP, {1152921504606846977}, {0}, {22}, 1},
            (pc1Case64s){"100000000000000000001008", FN_PC_OVERFLOW_SKIP, {1152921504606846977}, {0}, {23}, 1},
            (pc1Case64s){"12345670123456701234508", FN_PC_OVERFLOW_SKIP, {1505851632739161317}, {0}, {22}, 1},
            (pc1Case64s){"123456701234567012345008", FN_PC_OVERFLOW_SKIP, {1505851632739161317}, {0}, {23}, 1},
            (pc1Case64s){"1234567012345670123450123456701234567012345008", FN_PC_OVERFLOW_SKIP, {1505851632739161317}, {0}, {45}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case64s){"123456701234567012345/", FN_PC_OVERFLOW_ERROR, {1505851632739161317}, {0}, {21}, 1},
            (pc1Case64s){"1234567012345670123458", FN_PC_OVERFLOW_ERROR, {1505851632739161317}, {0}, {21}, 1},
            (pc1Case64s){"-1000000000000000000000/", FN_PC_OVERFLOW_ERROR, {-9223372036854775807 - 1}, {0}, {23}, 1},
            (pc1Case64s){"-10000000000000000000008", FN_PC_OVERFLOW_ERROR, {-9223372036854775807 - 1}, {0}, {23}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, int64_t, tCase5, ALEN(tCase5), PRId64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case64s tCase6[] = {

            (pc1Case64s){"173 +735 -235 $170 $-170", FN_OPT_NONE,
                         {123, 477, -157, 120, -120},
                         {0,0,0,0,0},
                         {3,8,13,18,-1},
                         5},
                       /*           10        20        30        40        50        60        70 */
                       /* 01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
            (pc1Case64s){"073 +12345670123456701234500 -100000000000000000000001 $170 $-11560144",
                         FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {59, 1505851632739161317, -9223372036854775807 - 1, 120, -2547812},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_UNDERFLOW, 0, 0},
                         {3,28,54,59,-1},
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

int octToUInt64C1Test(){
    #define FUNCCALL octToUInt64C1
    const static char * testName = "octToUInt64C1";

    printf("##### Start %s test #####\n", testName);

    { /* START Test 1 */
        unsigned int optArray[] = {
            FN_OPT_NONE, FN_PC_NO_INVALID_SKIP , FN_PC_OVERFLOW_ERROR,
            FN_PC_OVERFLOW_SKIP
        };

        MAKE_PC1_CASES_TEST1_U(FUNCCALL, uint64_t, 7, 22, optArray, ALEN(optArray), PRIu64);
    } /* END Test 1 */

    /* START Test 2A */
    MAKE_PC1_CASES_TEST2A_U( FUNCCALL, uint64_t, 7, 22, PRIu64);
    /* END Test 2A */

    /* START Test 2B */
    MAKE_PC1_CASES_TEST2B_U( FUNCCALL, uint64_t, 7, PRIu64);
    /* END Test 2B */

    { /* START Test 3 */
        puts ("# TEST 3: Maximum values parsing and leading zero parsing.");

        pc1Case64u tCase3[] = {
            /* a */
            (pc1Case64u){"1777777777777777777775", FN_OPT_NONE, {18446744073709551613U}, {0}, {-1}, 1},
            (pc1Case64u){"1777777777777777777775", FN_OPT_PC1_ALL, {18446744073709551613U}, {0}, {-1}, 1},
            /* b */
            (pc1Case64u){"1777777777777777777777", FN_OPT_NONE, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"1777777777777777777777", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1},
            /* c */
            (pc1Case64u){"001777777777777777777777", FN_OPT_NONE, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"001777777777777777777777", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"000", FN_OPT_NONE, {0}, {0}, {-1}, 1},
            (pc1Case64u){"00001777777777777777777777", FN_OPT_PC1_ALL, {18446744073709551615U}, {0}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 3", FUNCCALL, uint64_t, tCase3, ALEN(tCase3), PRIu64);
        puts ("# Test 3: Passed.\n");
    } /* END Test 3 */

    { /* START Test 4 */
        puts ("# TEST 4: With and without NO_INVALID_SKIP parsing.");

        pc1Case64u tCase4[] = {
            /* Without NO_INVALID_SKIP */
            (pc1Case64u){"-1", FN_OPT_NONE, {1}, {0}, {-1}, 1},
            (pc1Case64u){"817777777777777777777758", FN_OPT_NONE, {18446744073709551613U}, {0}, {23}, 1},
            (pc1Case64u){"8@#$%^&17777777777777777777758@", FN_OPT_NONE, {18446744073709551613U}, {0}, {29}, 1},
            (pc1Case64u){"8@#$%^&", FN_OPT_NONE, {0}, {FN_ERROR_NO_VALID_DATA}, {-1}, 1},
            (pc1Case64u){"", FN_OPT_NONE, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1},
            /* With NO_INVALID_SKIP */
            (pc1Case64u){"+0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"-0", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"81777777777777777777775", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"17777777777777777777758", FN_PC_NO_INVALID_SKIP, {18446744073709551613U}, {0}, {22}, 1},
            (pc1Case64u){"8%$%$#", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_INVALID_FORMAT}, {0}, 1},
            (pc1Case64u){"", FN_PC_NO_INVALID_SKIP, {0}, {FN_ERROR_EMPTY_STR}, {-1}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 4", FUNCCALL, uint64_t, tCase4, ALEN(tCase4), PRIu64);
        puts ("# Test 4: Passed.\n");
    } /* END Test 4 */

    { /* START Test 5 */
        puts ("# TEST 5: Overflow parsing.");

        pc1Case64u tCase5[] = {
            /* Overflow default */
            (pc1Case64u){"2000000000000000000000", FN_OPT_NONE, {2305843009213693952U}, {0}, {21}, 1},
            (pc1Case64u){"20000000000000000000007", FN_OPT_NONE, {2305843009213693952U}, {0}, {21}, 1},
            (pc1Case64u){"17777777777777777777777", FN_OPT_NONE, {18446744073709551615U}, {0}, {22}, 1},
            (pc1Case64u){"2000000000000000000010", FN_OPT_NONE, {2305843009213693953U}, {0}, {21}, 1},
            (pc1Case64u){"20000000000000000000107", FN_OPT_NONE, {2305843009213693953U}, {0}, {21}, 1},
            (pc1Case64u){"12345670123456701234507", FN_OPT_NONE, {12046813061913290536U}, {0}, {22}, 1},
            (pc1Case64u){"123456701234567012345071234567012345670123450", FN_OPT_NONE, {12046813061913290536U}, {0}, {22}, 1},
            /* OVERFLOW_ERROR opt */
            (pc1Case64u){"2000000000000000000000", FN_PC_OVERFLOW_ERROR, {2305843009213693952U}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64u){"20000000000000000000007", FN_PC_OVERFLOW_ERROR, {2305843009213693952U}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64u){"17777777777777777777777", FN_PC_OVERFLOW_ERROR, {18446744073709551615U}, {FN_ERROR_OVERFLOW}, {22}, 1},
            (pc1Case64u){"2000000000000000000010", FN_PC_OVERFLOW_ERROR, {2305843009213693953U}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64u){"20000000000000000000107", FN_PC_OVERFLOW_ERROR, {2305843009213693953U}, {FN_ERROR_OVERFLOW}, {21}, 1},
            (pc1Case64u){"12345670123456701234507", FN_PC_OVERFLOW_ERROR, {12046813061913290536U}, {FN_ERROR_OVERFLOW}, {22}, 1},
            (pc1Case64u){"123456701234567012345071234567012345670123450", FN_PC_OVERFLOW_ERROR, {12046813061913290536U}, {FN_ERROR_OVERFLOW}, {22}, 1},
            /* OVERFLOW SKIP opt */
            (pc1Case64u){"2000000000000000000000", FN_PC_OVERFLOW_SKIP, {2305843009213693952U}, {0}, {-1}, 1},
            (pc1Case64u){"20000000000000000000007", FN_PC_OVERFLOW_SKIP, {2305843009213693952U}, {0}, {-1}, 1},
            (pc1Case64u){"17777777777777777777777", FN_PC_OVERFLOW_SKIP, {18446744073709551615U}, {0}, {-1}, 1},
            (pc1Case64u){"2000000000000000000010", FN_PC_OVERFLOW_SKIP, {2305843009213693953U}, {0}, {-1}, 1},
            (pc1Case64u){"20000000000000000000107", FN_PC_OVERFLOW_SKIP, {2305843009213693953U}, {0}, {-1}, 1},
            (pc1Case64u){"12345670123456701234507", FN_PC_OVERFLOW_SKIP, {12046813061913290536U}, {0}, {-1}, 1},
            (pc1Case64u){"123456701234567012345071234567012345670123450", FN_PC_OVERFLOW_SKIP, {12046813061913290536U}, {0}, {-1}, 1},
            (pc1Case64u){"20000000000000000000008", FN_PC_OVERFLOW_SKIP, {2305843009213693952U}, {0}, {22}, 1},
            (pc1Case64u){"200000000000000000000008", FN_PC_OVERFLOW_SKIP, {2305843009213693952U}, {0}, {23}, 1},
            (pc1Case64u){"177777777777777777777708", FN_PC_OVERFLOW_SKIP, {18446744073709551615U}, {0}, {23}, 1},
            (pc1Case64u){"20000000000000000000108", FN_PC_OVERFLOW_SKIP, {2305843009213693953U}, {0}, {22}, 1},
            (pc1Case64u){"200000000000000000001008", FN_PC_OVERFLOW_SKIP, {2305843009213693953U}, {0}, {23}, 1},
            (pc1Case64u){"123456701234567012345008", FN_PC_OVERFLOW_SKIP, {12046813061913290536U}, {0}, {23}, 1},
            (pc1Case64u){"1234567012345670123450123456701234567012345008", FN_PC_OVERFLOW_SKIP, {12046813061913290536U}, {0}, {45}, 1},
            /* Invalid format with OVERFLOW_ERROR */
            (pc1Case64u){"123456701234567012345/", FN_PC_OVERFLOW_ERROR, {1505851632739161317U}, {0}, {21}, 1},
            (pc1Case64u){"1234567012345670123458", FN_PC_OVERFLOW_ERROR, {1505851632739161317U}, {0}, {21}, 1},
            (pc1Case64u){"1234567012345670123456/", FN_PC_OVERFLOW_ERROR, {12046813061913290542U}, {0}, {22}, 1},
            (pc1Case64u){"12345670123456701234568", FN_PC_OVERFLOW_ERROR, {12046813061913290542U}, {0}, {22}, 1}
        };

        MAKE_PC1_CASES_LOOP("Test 5", FUNCCALL, uint64_t, tCase5, ALEN(tCase5), PRIu64);
        puts ("# Test 5: Passed.\n");
    } /* END Test 5 */

    { /* START Test 6 */
        puts ("# TEST 6: Continuous parsing.");

        pc1Case64u tCase6[] = {
            (pc1Case64u){"173 13235 11412 $30431232777 & $3254545", FN_OPT_NONE,
                         {123U, 5789U, 4874U, 3294967295U, 874853U},
                         {0,0,0,0,0},
                         {3,9,15,28,-1},
                         5},
                       /*           10        20        30        40        50        60        70 */
                       /* 01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
            (pc1Case64u){"173 17777777777777777777770 12345670123456701234500       $30431232777 & $3254545", FN_PC_OVERFLOW_SKIP | FN_PC_OVERFLOW_ERROR,
                         {123U, 18446744073709551615U, 12046813061913290536U, 3294967295U, 874853U},
                         {0, FN_ERROR_OVERFLOW, FN_ERROR_OVERFLOW, 0, 0},
                         {3,27,51,70,-1},
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
