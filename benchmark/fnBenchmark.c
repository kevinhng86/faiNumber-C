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
/* faiNumber - fnBenchmark.c */
/*
 * @NOTE  Parser functions from this library were written in a way
 *        that they benefit greatly with branch prediction. Thus,
 *        when testing input strings that are the same length, even if
 *        they are at max length, depend on the base, parser of this
 *        library may parse them faster than if the strings were uneven
 *        in length. Thus, the benchmark unit were setup to test the
 *        functions with test strings that are vary in length. Their
 *        length could be any where from at least a length of 1 to max
 *        number length. But if needed to test the functions benchmark
 *        score when all strings are the same in length use something
 *        similar like "../testlib/benchmark/def_b2s_max_i64.h". In
 *        that example, max will ensure all test strings are at max
 *        number length for the defined base. If there are two max
 *        number length due to length differences between positive and
 *        negative values, the lower max number length is the defined
 *        one.
 *
 */
#include <stdio.h>
#include "../h/DecimalUtil32.h"
#include "../h/DecimalUtil64.h"
#include "../h/BinaryUtil64.h"
#include "../h/OctalUtil64.h"
#include "../h/HexUtil64.h"

/*
 * Since benchmarking can be run and easily alter in this file,
 * currently, there isn't a need to compile testlib.c separately,
 * and since the benchmarker will not be included into any other
 * code, testlib.c is directly included into this file. To match
 * the build of other library, this library must be build with -O2
 * optimization and is a dynamic link library. Build together as
 * one package will always be faster with -O2 optimization.
 *
 **/
#include "../testlib/testlib.c"

#define GETSTR(value) # value
#define GETFSTR(name) " "GETSTR(name)

#define TCASE (size_t)10000000
#define SIGNOPT FN_TL_RAND_SIGN
#define BASE 10
#define MIND 0
#define MAXD 9
#define MINL 1
#define MAXL 10
#define MAXFIRST 1

/* The second line to get rid of compiler unused warning */
#define DECL int32_t n = 0; int error = 0; int ni = 0; unsigned long nl = 0; \
                     if(n); if(error); if(ni); if(nl);

#define TARRAY tArray[i]

#define GETFBLOCK(FSTR, FCODE) \
    starttime = getPointInTime(); \
    for ( size_t i = 0; i < TCASE; i++ ) FCODE; \
    endtime = getPointInTime(); \
    result = endtime - starttime; \
    printf ("#"FSTR" benchmark = %lld milliseconds.\n", result);\
    puts("#")

/* If any F1 to F3 is not used, set it _STR and _BLOCK to empty */
#define F1NAME decToInt32
#define F1STR GETFSTR(F1NAME)
#define GETF1 error = F1NAME(TARRAY, &n)
#define F1BLOCK GETFBLOCK(F1STR, GETF1)

#define F2NAME atoi
#define F2STR GETFSTR(F2NAME)
#define GETF2 ni = F2NAME(TARRAY)
#define F2BLOCK GETFBLOCK(F2STR, GETF2)

#define F3NAME strtol
#define F3STR GETFSTR(F3NAME)
#define GETF3 nl = F3NAME(TARRAY, NULL, BASE)
#define F3BLOCK GETFBLOCK(F3STR, GETF3)

#define BENCHMARK do { \
    long long starttime, endtime, result; \
    DECL \
    char ** tArray; \
\
    tArray = (char **) mkRandomDigitStrings(TCASE, MINL, MAXL, MIND, MAXD, MAXFIRST, SIGNOPT, FN_TL_NOL0); \
    if ( tArray == NULL ) { \
        puts("Error allocating memory for random data."); \
        return 1; \
    } \
\
    puts ("#### START"F1STR F2STR F3STR " benchmark. ####"); \
\
    printf ("# Parse the same number array consist of %zu random strings.\n", TCASE); \
    puts ("# All functions will parse the same random array."); \
    puts ("#"); \
\
F1BLOCK; \
F2BLOCK; \
F3BLOCK; \
\
    /* Remove the comment marker from the line below to test print debug. */ \
    /* for ( size_t i = 0; i < 100; i++ ) printf ("%s\n", tArray[i]); */\
    puts("##### END"F1STR F2STR F3STR " benchmark. #####"); \
\
    /* Freemem. */ \
\
    free(tArray[0]); \
    free(tArray); \
} while(0)

int32_t benchmark();

int main() {

    puts("\n\n**********************TEST 1**********************\n\n");

    BENCHMARK;

    /*
     * Example below to use the same macro for differnt functions.
     *
     **/
    puts("\n\n**********************TEST 2**********************\n\n");

    /*
     * The file undef_all_f.h will undef all the F1___ to F3___
     * This is to make the code shorter and easy to manage.
     * To undef individual f, use ../testlib/benchmark/undef_f*.h
     *
     **/
    #include "../testlib/benchmark/undef_all_f.h"

    #define F1NAME decToUInt32
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #define F2NAME strtoul
    #define F2STR GETFSTR(F2NAME)
    #define GETF2 nl = F2NAME(tArray[i], NULL, BASE)
    #define F2BLOCK GETFBLOCK(F2STR, GETF2)

    /*
     * atoi is not being used for the second conversion
     * If it isn't used, it isn't needed to define anything except
     * for __STR and __BLOCK.
     **/
    #define F3STR
    #define F3BLOCK

    /* Redefining variable */
    #undef DECL
    #define DECL uint32_t n = 0; int error = 0; unsigned long nl; \
                 if (n); if(error); if(nl);

    /*
     * Here, since there is still a definition for unsigned parsing
     * it is possible to just change the SIGNOPT macro value. However,
     * this method below to show how flexible the benchmark macro
     * library is. If a base setup for the macro is available, it can
     * be used instead. The file naming context is def_bNS_L_iW.h,
     * where:
     *   (N) is the base number;
     *   (L) is either min or max, where min is where the input strings
     *       will have a random length of at least 1 to max length.
     *       max is where all input strings will have max length;
     *   (S) is either u or s for unsigned and sign respectively; and
     *   (W) is for the width of the integer.
     **/
    #include "../testlib/benchmark/def_b10u_min_i32.h"

    BENCHMARK;

    /* START Decimal i64 Signed */
    puts("\n\n**********************TEST 3**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"
    #include "../testlib/benchmark/undef_f2.h"

    #define F1NAME decToInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #define F2NAME strtoll
    #define F2STR GETFSTR(F2NAME)
    #define GETF2 nll = F2NAME(tArray[i], NULL, BASE)
    #define F2BLOCK GETFBLOCK(F2STR, GETF2)

    #undef DECL
    #define DECL int64_t n = 0; int error = 0; long long nll; \
                 if (n); if(error); if(nll);

    #include "../testlib/benchmark/def_b10s_min_i64.h"

    BENCHMARK;
    /* END Decimal i64 Signed */

    /* START Binary i64 Signed */
    puts("\n\n**********************TEST 4**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"

    #define F1NAME binToInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #include "../testlib/benchmark/def_b2s_min_i64.h"

    BENCHMARK;
    /* END Binary i64 Signed */

    /* START Octal i64 Signed */
    puts("\n\n**********************TEST 5**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"

    #define F1NAME octToInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #include "../testlib/benchmark/def_b8s_min_i64.h"

    BENCHMARK;
    /* END Octal i64 Signed */

    /* START Hexadecimal i64 Signed */
    puts("\n\n**********************TEST 6**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"

    #define F1NAME hexToInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #include "../testlib/benchmark/def_b16s_min_i64.h"

    BENCHMARK;
    /* END Hexadecimal i64 Signed */

    /* START Decimal i64 Unsigned */
    puts("\n\n**********************TEST 7**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"
    #include "../testlib/benchmark/undef_f2.h"

    #define F1NAME decToUInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #define F2NAME strtoull
    #define F2STR GETFSTR(F2NAME)
    #define GETF2 nll = F2NAME(tArray[i], NULL, BASE)
    #define F2BLOCK GETFBLOCK(F2STR, GETF2)

    #undef DECL
    #define DECL uint64_t n = 0; int error = 0; unsigned long long nll; \
                 if (n); if(error); if(nll);

    #include "../testlib/benchmark/def_b10u_min_i64.h"

    BENCHMARK;
    /* END Decimal i64 Unsigned */

    /* START Binary i64 Unsigned */
    puts("\n\n**********************TEST 8**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"

    #define F1NAME binToUInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #include "../testlib/benchmark/def_b2u_min_i64.h"

    BENCHMARK;
    /* END Binary i64 Unsigned */

    /* START Octal i64 Unsigned */
    puts("\n\n**********************TEST 9**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"

    #define F1NAME octToUInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #include "../testlib/benchmark/def_b8u_min_i64.h"

    BENCHMARK;
    /* END Octal i64 Unsigned */

    /* START Hexadecimal i64 Unsigned */
    puts("\n\n**********************TEST 10**********************\n\n");
    #include "../testlib/benchmark/undef_f1.h"

    #define F1NAME hexToUInt64
    #define F1STR GETFSTR(F1NAME)
    #define GETF1 error = F1NAME(tArray[i], &n)
    #define F1BLOCK GETFBLOCK(F1STR, GETF1)

    #include "../testlib/benchmark/def_b16u_min_i64.h"

    BENCHMARK;
    /* END Hexadecimal i64 Unsigned */


    /* START Hexadecimal i64 Unsigned Max Length */
    puts("\n\n**********************TEST 11**********************");
    puts("*** This test is to show the speed gain when all string are the same in length(max length). ");
    puts("*** The test above this test, all strings are vary in length with a length of 1 to max.\n\n");

    #include "../testlib/benchmark/def_b16u_max_i64.h"

    BENCHMARK;
    /* END Hexadecimal i64 Unsigned Max Length */

    puts("\n");
    return 0;
}
