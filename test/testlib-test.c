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
/* faiNumber - testlib-test.c */
/*
 * This file is to test the testlib.c functions
 *
 * This file include testlib.c directly without compiling into
 * multiple object files for fast testing. Just build this file like
 * this. Do not build testlib.c together with file.
 *
 **/
#include "../testlib/testlib.c"
#include <stdio.h>
#include <inttypes.h>

int getRandom32_test();
void getPointInTime_test();
int mkRandomDigitStrings_test();
int abortJMP_test();

int main(){
    if ( getRandom32_test() == 1 ) return 1;

    puts("\n");
    getPointInTime_test();

    puts("\n");
    if ( mkRandomDigitStrings_test() == 1 ) return 1;

    puts("\n");
    if ( abortJMP_test() == 1 ) return 1;

    return 0;
}

int getRandom32_test(){
    puts("***** getRandom32 Test *****");

    int n1;
    /*
     * Pointer testing, test whether if getRandom32 point to the
     * correct function. On first run, getRandom32 always point
     * to _getRandom32. _getRandom32 will then seed the rand() function
     * with srand(). Then _getRandom32 will change getRandom32 to
     * point to the __getRandom32 function. Of which, does not seed
     * the random generator.
     *
     **/
    uintptr_t getRandom32P = (uintptr_t)getRandom32;
    uintptr_t _getRandom32P = (uintptr_t)&_getRandom32;
    uintptr_t __getRandom32P = (uintptr_t)&__getRandom32;

    if ( getRandom32P != _getRandom32P ){
        printf("Test fail, getRandom32 did not initialize to the correct function\n");
        printf("getRandom32(%" PRIxPTR ") - _getRandom32(%" PRIxPTR ")\n", getRandom32P, _getRandom32P);
        return 1;
    }
    n1 = getRandom32(0,1);
    getRandom32P = (unsigned long long)getRandom32;
    if ( getRandom32P != __getRandom32P ){
        printf("Test fail, getRandom32 did not change to the correct function\n");
        printf("getRandom32(%" PRIxPTR ") - __getRandom32(%" PRIxPTR ")\n", getRandom32P, __getRandom32P);
        return 1;
    }

    /*
     * Although, the current algorithm is correct, this test is just to
     * ensure the correctness of output in case of algorithm change.
     *
     * Get 10000 random values and see if any of them is out of
     * range. Also, check in all numbers within range is included.
     * It is very rare or almost impossible, for a 10000 loops run
     * to not get all number of a range of random numbers
     * which only contain 3 values.
     **/
    {
        int i = 0, tCase = 10000;
        int marker[3] = { 0 };
        for ( ; i < tCase; i++ ){
            n1 = getRandom32(-1,1);
            if ( n1 < -1 || n1 > 1 ) {
                puts("getRandom32 failed, out of range.");
                return 1;
            }
            if ( n1 == -1 ) marker[0] = 1;
            else if ( n1 == 0 ) marker[1] = 1;
            else if ( n1 == 1 ) marker[2] = 1;
            if ( marker[0] == 1 && marker[1] == 1 && marker[2] == 1 )
              goto random32Next;

        }
        puts("getRandom32 failed, not all marker is found.");
        return 1;

        random32Next:
        for ( ; i < tCase; i++ ){
            n1 = getRandom32(-1,1);
            if ( n1 < -1 || n1 > 1 ) {
                puts("getRandom32 failed, out of range.");
                return 1;
            }
        }
    }
    puts("...Test Passed");
    puts("***** getRandom32 Test End *****");

    return 0;
}

void getPointInTime_test(){
    puts("***** Checking getPointInTime() Built Version Manually. *****");
    printf("...getPointInTime() version: %d\n", FN_GETPOINTINTIME_V);
    puts("***** Checking getPointInTime() Built Version Manually End. *****");
}

int mkRandomDigitStrings_test(){
    #define THIS_FREE_STRS free(strs[0]); free(strs)
    puts("***** mkRandomDigitStrings Test *****");
    const int digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                          'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                          'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                          'u', 'v', 'w', 'x', 'y', 'z'
                        };
    const size_t tCase = 10000;
    size_t minL = 1,
           maxL = 3;
    const int minD = 1,
              maxD = 3,
          maxFirst = 2;

    const char minDC = minD ^ 48,
               maxDC = maxD ^ 48,
           maxFirstC = maxFirst ^ 48;

    char ** strs;
    size_t i;
    int marker[4], sign;

    /*
     * Although, this first test does not have to be run, it is just to
     * ensure any future editting to the code does not accidently alter
     * any index of the array to make the code give out an errorness result.
     **/
    for ( int i = 0; i < 36; i++ ){
        strs = mkRandomDigitStrings(1, 1, 1, i, i, i, FN_TL_NO_SIGN, FN_TL_WITHL0);
        if ( strs == NULL ){
            puts ("Test fail at checking whether if number generate correctly "
                  " from 0 - 35, couldn't obtain enough memory.");
            return 1;
        }
        if ( strs[0][1] != 0 ) {
            puts ("Test fail at checking whether if number generate correctly "
                  "from 0 - 35, Length is more than 1.");
            return 1;
        }
        if ( strs[0][0] != digit[i] ) {
            printf ("Test fail at checking whether if number generate correctly "
                  "from 0 - 35, Did not generate the correct digit for i[%d] - c[%c].\n"
                  , i, strs[0][0] );
            return 1;
        }

        THIS_FREE_STRS;
    }
    strs = mkRandomDigitStrings(1, 1, 1, 36, 36, 1, FN_TL_NO_SIGN, FN_TL_WITHL0);
    if ( strs != NULL ) {
        puts ("Test fail at checking whether if number generate correctly "
              "from 0 - 35, Larger than 35 was possible(minD && maxD).");
        THIS_FREE_STRS;
        return 1;
    }

    strs = mkRandomDigitStrings(1, 1, 1, 1, 1, 36, FN_TL_NO_SIGN, FN_TL_WITHL0);
    if ( strs != NULL ) {
        puts ("Test fail at checking whether if number generate correctly "
              "from 0 - 35, Larger than 35 was possible(maxFirst).");
        THIS_FREE_STRS;
        return 1;
    }

    /* No sign test.
     *
     * All strings:
     *
     * 1) Must not contain a sign.
     * 2) Length must not be longer than maxL or smaller than minL.
     * 3) Digits must not be larger than digitMax or smaller than digitMin.
     * 4) If length == to maxLength, the first digit must not be larger
     *    than maxFirst.
     * 5) Must contain all digits within the range.(10000 times, it
     *    is almost a for sure that all values of a range 3 values will
     *    be included. It is not impossible but extremely rare to not
     *    have all values.)
     *
     **/
    strs = mkRandomDigitStrings(tCase, minL, maxL, minD, maxD, maxFirst, FN_TL_NO_SIGN, FN_TL_WITHL0);
    if ( strs == NULL ){
        puts ("Test fail at No Sign. Couldn't obtain enough memory.");
        return 1;
    }
    marker[1] = marker[2] = marker[3] = 0;
    for ( i = 0; i < tCase; i++ ){
        size_t len = 0;

        for ( ; strs[i][len] ; len++){
            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at No Sign. Found digit smaller or larger "
                        "than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }

            marker[ strs[i][len] ^ 48 ] = 1;
        }

        if ( len < minL || len > maxL ){
            printf ("Test fail at No Sign. Found length smaller or larger "
                    "than the allowable length range l[%zu].\n", len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][0] > maxFirstC ){
            printf ("Test fail at No Sign. Found first digit larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][0]);
            THIS_FREE_STRS;
            return 1;
        }
        if ( marker[1] == 1 && marker[2] == 1 && marker[3] == 1 )
          goto mkRandomDigitStrings_test_no_sign_next;
    }

    mkRandomDigitStrings_test_no_sign_next:
    for ( ; i < tCase; i++ ){
        size_t len = 0;

        for ( ; strs[i][len] ; len++){
            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at No Sign. Found digit smaller or larger "
                        "than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }
        }

        if ( len < minL || len > maxL ){
            printf ("Test fail at No Sign. Found length smaller or larger "
                    "than the allowable length range l[%zu].\n", len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][0] > maxFirstC ){
            printf ("Test fail at No Sign. Found first digit larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][0]);
            THIS_FREE_STRS;
            return 1;
        }
    }
    /*
     * This block keep here so free needed to be used only one. The loop
     * just right above will not executed anyway if mark[1...3] is not 1.
     * That is because for that to happen, the entire first loop had to
     * finish executing already. Memory can be free first here.
     */
    THIS_FREE_STRS;
    if ( marker[1] != 1 || marker[2] != 1 || marker[3] != 1 ) {
        puts("Test fail at No Sign. mkRandomDigitStrings() did not "
             "generate all the values for the range.");
        return 1;
    }

    /* Random Sign Test.
     *
     * All strings:
     *
     * 1) Can contain or not contain a sign.
     * 2) Length, without sign, must not be longer than maxL or smaller
     *    than minL.
     * 3) Digits must not be larger than digitMax or smaller than digitMin.
     * 4) If length == to maxLength, the first digit must not be larger
     *    than maxFirst.
     * 5) Must contain all digits within the range.(10000 times, it
     *    is almost a for sure that all values of a range 3 values will
     *    be included. It is not impossible but extremely rare to not
     *    have all values.)
     *
     **/
    strs = mkRandomDigitStrings(tCase, minL, maxL, minD, maxD, maxFirst, FN_TL_RAND_SIGN, FN_TL_WITHL0);
    if ( strs == NULL ){
        puts ("Test fail at Random Sign. Couldn't obtain enough memory.");
        return 1;
    }
    marker[1] = marker[2] = marker[3] = 0;
    for ( i = 0; i < tCase; i++ ){
        size_t len = 0;
        if ( (strs[i][0] == 43 || strs[i][0] == 45) && ++len ) sign = 1;
        else sign = 0;

        for ( ; strs[i][len] ; len++){

            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at Random Sign. Found digit smaller "
                        "or larger than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }

            marker[ strs[i][len] ^ 48 ] = 1;
        }
        len = len - sign;

        if ( len < minL || len > maxL ){
            printf ("Test fail at Random Sign. Found length smaller or larger "
                    "than the allowable length range l[%zu].\n", len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][sign] > maxFirstC ){
            printf ("Test fail at Random Sign. Found first digit larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][sign]);
            THIS_FREE_STRS;
            return 1;
        }
        if ( marker[1] == 1 && marker[2] == 1 && marker[3] == 1 )
          goto mkRandomDigitStrings_test_rand_sign_next;
    }

    mkRandomDigitStrings_test_rand_sign_next:
    for ( ; i < tCase; i++ ){
        size_t len = 0;
        if ( (strs[i][0] == 43 || strs[i][0] == 45) && ++len ) sign = 1;
        else sign = 0;

        for ( ; strs[i][len] ; len++){
            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at Random Sign. Found digit smaller "
                        "or larger than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }
        }
        len = len - sign;

        if ( len < minL || len > maxL ){
            printf ("Test fail at Random Sign. Found length smaller or larger "
                    "than the allowable length range l[%zu].\n", len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][sign] > maxFirstC ){
            printf ("Test fail at Random Sign. Found first digit larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][sign]);
            THIS_FREE_STRS;
            return 1;
        }
    }
    /*
     * This block keep here so free needed to be used only one. The loop
     * just right above will not executed anyway if mark[1...3] is not 1.
     * That is because for that to happen, the entire first loop had to
     * finish executing already. Memory can be free first here.
     */
    THIS_FREE_STRS;
    if ( marker[1] != 1 || marker[2] != 1 || marker[3] != 1 ) {
        puts("Test fail at Random Sign. mkRandomDigitStrings() did not "
             "generate all the values for the range.");
        return 1;
    }

    /*
     * For the next two tests, there must be a sign on all strings,
     * if compare "len - 1" in every loop to maxL would consume more
     * time than prior reduction of minL and maxL. Thus, after obtaining
     * the array, minL++ and maxL++. After, the test loop is done,
     * minL-- and maxL--.
     *
     **/

    /* Neg Only Test.
     *
     * All strings:
     *
     * 1) Must contain a negative sign.
     * 2) Length, without sign, must not be longer than maxL or smaller
     *    than minL.
     * 3) Digits must not be larger than digitMax or smaller than digitMin.
     * 4) If length == to maxLength, the first digit must not be larger
     *    than maxFirst.
     * 5) Must contain all digits within the range.(10000 times, it
     *    is almost a for sure that all values of a range 3 values will
     *    be included. It is not impossible but extremely rare to not
     *    have all values.)
     **/
    strs = mkRandomDigitStrings(tCase, minL, maxL, minD, maxD, maxFirst, FN_TL_NEG_ONLY, FN_TL_WITHL0);
    minL++;
    maxL++;
    if ( strs == NULL ){
        puts ("Test fail at Neg Only. Couldn't obtain enough memory.");
        return 1;
    }
    marker[1] = marker[2] = marker[3] = 0;
    for ( i = 0; i < tCase; i++ ){
        size_t len = 1;
        if ( strs[i][0] != 45 ) {
            printf ("Test fail at Neg Only. A number without a negative "
                    "sign was found n[%s].\n", strs[i]);
            THIS_FREE_STRS;
            return 1;
        }

        for ( ; strs[i][len] ; len++){
            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at Neg Only. Found digit smaller "
                        "or larger than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }

            marker[ strs[i][len] ^ 48 ] = 1;
        }

        if ( len < minL || len > maxL ){
            printf ("Test fail at Neg Only. Found length smaller or larger "
                    "than the allowable length range l[%zu](without sign).\n"
                    , --len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][1] > maxFirstC ){
            printf ("Test fail at Neg Only. Found first digit larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][1]);
            THIS_FREE_STRS;
            return 1;
        }
        if ( marker[1] == 1 && marker[2] == 1 && marker[3] == 1 )
          goto mkRandomDigitStrings_test_neg_only_next;
    }

    mkRandomDigitStrings_test_neg_only_next:
        for ( ; i < tCase; i++ ){
        size_t len = 1;
        if ( strs[i][0] != 45 ) {
            printf ("Test fail at Neg Only. A number without a negative "
                    "sign was found n[%s].\n", strs[i]);
            THIS_FREE_STRS;
            return 1;
        }

        for ( ; strs[i][len] ; len++){
            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at Neg Only. Found digit smaller "
                        "or larger than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }
        }

        if ( len < minL || len > maxL ){
            printf ("Test fail at Neg Only. Found length smaller or larger "
                    "than the allowable length range l[%zu](without sign).\n"
                    , --len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][1] > maxFirstC ){
            printf ("Test fail at Neg Only. Found first digit larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][1]);
            THIS_FREE_STRS;
            return 1;
        }
    }

    /*
     * This block keep here so free needed to be used only one. The loop
     * just right above will not executed anyway if mark[1...3] is not 1.
     * That is because for that to happen, the entire first loop had to
     * finish executing already. Memory can be free first here.
     */
    THIS_FREE_STRS;
    if ( marker[1] != 1 || marker[2] != 1 || marker[3] != 1 ) {
        puts("Test fail at Neg Only. mkRandomDigitStrings() did not "
             "generate all the values for the range.");
        return 1;
    }
    minL--;
    maxL--;

    /* Pos Only Test.
     *
     * All strings:
     *
     * 1) Must contain a positive sign.
     * 2) Length, without sign, must not be longer than maxL or smaller
     *    than minL.
     * 3) Digits must not be larger than digitMax or smaller than digitMin.
     * 4) If length == to maxLength, the first digit must not be larger
     *    than maxFirst.
     * 5) Must contain all digits within the range.(10000 times, it
     *    is almost a for sure that all values of a range 3 values will
     *    be included. It is not impossible but extremely rare to not
     *    have all values.)
     **/
    strs = mkRandomDigitStrings(tCase, minL, maxL, minD, maxD, maxFirst, FN_TL_POS_ONLY, FN_TL_WITHL0);
    minL++;
    maxL++;
    if ( strs == NULL ){
        puts ("Test fail at Pos Only. Couldn't obtain enough memory.");
        return 1;
    }
    marker[1] = marker[2] = marker[3] = 0;
    for ( i = 0; i < tCase; i++ ){
        size_t len = 1;
        if ( strs[i][0] != 43 ) {
            printf ("Test fail at Pos Only. A number without a positve "
                    "sign was founded n[%s].\n", strs[i]);
            THIS_FREE_STRS;
            return 1;
        }

        for ( ; strs[i][len] ; len++){
            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at Pos Only. Founded a digit that is "
                        "smaller or larger than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }

            marker[ strs[i][len] ^ 48 ] = 1;
        }

        if ( len < minL || len > maxL ){
            printf ("Test fail at Pos Only. Founded a length that is "
                    "smaller or larger than the allowable length "
                    "range l[%zu](without sign).\n", --len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][1] > maxFirstC ){
            printf ("Test fail at Pos Only. First digit is larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][1]);
            THIS_FREE_STRS;
            return 1;
        }
        if ( marker[1] == 1 && marker[2] == 1 && marker[3] == 1 )
          goto mkRandomDigitStrings_test_pos_only_next;
    }

    mkRandomDigitStrings_test_pos_only_next:
        for ( i = 0; i < tCase; i++ ){
        size_t len = 1;
        if ( strs[i][0] != 43 ) {
            printf ("Test fail at Pos Only. A number without a positve "
                    "sign was founded n[%s].\n", strs[i]);
            THIS_FREE_STRS;
            return 1;
        }

        for ( ; strs[i][len] ; len++){
            if ( strs[i][len] < minDC || strs[i][len] > maxDC ){
                printf ("Test fail at Pos Only. Founded a digit that is "
                        "smaller or larger than range c[%c].\n", strs[i][len]);
                THIS_FREE_STRS;
                return 1;
            }

            marker[ strs[i][len] ^ 48 ] = 1;
        }

        if ( len < minL || len > maxL ){
            printf ("Test fail at Pos Only. Founded a length that is "
                    "smaller or larger than the allowable length "
                    "range l[%zu](without sign).\n", --len);
            THIS_FREE_STRS;
            return 1;
        }

        if ( len == maxL && strs[i][1] > maxFirstC ){
            printf ("Test fail at Pos Only. First digit is larger than "
                    "the largest allowable first digit c[%c].\n", strs[i][1]);
            THIS_FREE_STRS;
            return 1;
        }
    }

    /*
     * This block keep here so free needed to be used only one. The loop
     * just right above will not executed anyway if mark[1...3] is not 1.
     * That is because for that to happen, the entire first loop had to
     * finish executing already. Memory can be free first here.
     */
    THIS_FREE_STRS;
    if ( marker[1] != 1 || marker[2] != 1 || marker[3] != 1 ) {
        puts("Test fail at Pos Only. mkRandomDigitStrings() did not "
             "generate all the values for the range.");
        return 1;
    }
    minL--;
    maxL--;

    /* No leading zero test.
     *
     * All strings:
     *
     * 1) Must not contain a leading zero.
     * 2) If have sign, after the sign, must contain a leading zero.
     *
     * Although, this check block is not performance efficient, it
     * was written like this for easy readability and easy maintaince.
     **/
    for ( unsigned int ui = 0; ui <= FN_TL_SIGN_OPTION_MAX; ui++ ){
        strs = mkRandomDigitStrings(tCase, minL, maxL, 0, maxD, maxFirst, ui, FN_TL_NOL0);
        if ( strs == NULL ) {
            puts ("Test fail at checking the noL0 options. Couldn't obtain enough memory");
            return 1;
        }

        for ( i = 0; i < tCase; i++ ){
            sign = strs[i][0] == 45 || strs[i][0] == 43? 1 : 0;
            if ( strs[i][sign] == digit[0] ){
                puts ("Test fail at checking the noL0 options. Found a leading zero.");
                THIS_FREE_STRS;
                return 1;
            }
        }

        THIS_FREE_STRS;
    }

    puts("...Test Passed");
    puts("***** mkRandomDigitStrings End *****");
    #undef THIS_FREE_STRS
    return 0;
}

int abortJMP_test(){
    puts("***** abortJMP Test *****");

    volatile int i = 0;
    volatile int flag = 0;
    int reloop = 5;

    flag = setjmp(FN_TL_JMP_BUFF);

    signal(SIGABRT, abortJMP);
    i++;

    if (flag != FN_TL_JMP_CODE || i < reloop) abort();

    if (i != reloop || flag != FN_TL_JMP_CODE){
        printf ("Test fail mismatch counter or flag.\n"
                "i[%d]    | flag[%d]", i, flag);
        return 1;
    }

    puts("...Test Passed");
    puts("***** abortJMP Test End *****");

    return 0;
}
