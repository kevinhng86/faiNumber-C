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
/* faiNumber - header32Test.c */
/*
 * @NOTE  This test is for testing the joint header file for all 32-bit
 *        functions. This file will not compile if any of the functions
 *        is missing in the header file. This test will need to be
 *        updated if there are any api changes or if any new function is
 *        added to the library. This test only needed to be able to be
 *        compiled without errors. It does not actually needed to be
 *        built and executed.
 *
 *        Although there is a test for the header guards, a visual check
 *        should be carry out prior to any final release.
 *
 **/
#include "../h/faiNumber32.h"

int main(){
    char * str = "1";
    char * str2 = "2";
    int32_t sn32;
    uint32_t un32;
    int e;
    int cr;

    /* START Binary32 Functions */
    e = binToInt32 (str, &sn32);
    e = binToInt32TrueError (str, &sn32);
    e = binToUInt32 (str, &un32);
    e = binToUInt32TrueError (str, &un32);

    e = binToInt32FP (str, 0, 0, &sn32, 0);
    e = binToInt32FN (str, &sn32, 0);
    e = binToUInt32FP (str, 0, 0, &un32, 0);
    e = binToUInt32FN (str, &un32, 0);

    e = binToInt32C1 (str, &sn32, NULL, 0);
    e = binToUInt32C1 (str, &un32, NULL, 0);

    e = binCompareAsInt32 (str, str2, &cr);
    cr = binInt32OrSmaller (str, str2);
    e = binCompareAsUInt32 (str, str2, &cr);
    cr = binUInt32OrSmaller (str, str2);
    /* END Binary32 Functions */

    /* START Octal32 Functions */
    e = octToInt32 (str, &sn32);
    e = octToInt32TrueError (str, &sn32);
    e = octToUInt32 (str, &un32);
    e = octToUInt32TrueError (str, &un32);

    e = octToInt32FP (str, 0, 0, &sn32, 0);
    e = octToInt32FN (str, &sn32, 0);
    e = octToUInt32FP (str, 0, 0, &un32, 0);
    e = octToUInt32FN (str, &un32, 0);

    e = octToInt32C1 (str, &sn32, NULL, 0);
    e = octToUInt32C1 (str, &un32, NULL, 0);

    e = octCompareAsInt32 (str, str2, &cr);
    cr = octInt32OrSmaller (str, str2);
    e = octCompareAsUInt32 (str, str2, &cr);
    cr = octUInt32OrSmaller (str, str2);
    /* END Octal32 Functions */

    /* START Decimal32 Functions */
    e = decToInt32 (str, &sn32);
    e = decToInt32TrueError (str, &sn32);
    e = decToUInt32 (str, &un32);
    e = decToUInt32TrueError (str, &un32);

    e = decToInt32FP (str, 0, 0, &sn32, 0);
    e = decToInt32FN (str, &sn32, 0);
    e = decToUInt32FP (str, 0, 0, &un32, 0);
    e = decToUInt32FN (str, &un32, 0);

    e = decToInt32C1 (str, &sn32, NULL, 0);
    e = decToUInt32C1 (str, &un32, NULL, 0);

    e = decCompareAsInt32 (str, str2, &cr);
    cr = decInt32OrSmaller (str, str2);
    e = decCompareAsUInt32 (str, str2, &cr);
    cr = decUInt32OrSmaller (str, str2);
    /* END Decimal32 Functions */

    /* START Hex32 Functions */
    e = hexToInt32 (str, &sn32);
    e = hexToInt32TrueError (str, &sn32);
    e = hexToUInt32 (str, &un32);
    e = hexToUInt32TrueError (str, &un32);

    e = hexToInt32FP (str, 0, 0, &sn32, 0);
    e = hexToInt32FN (str, &sn32, 0);
    e = hexToUInt32FP (str, 0, 0, &un32, 0);
    e = hexToUInt32FN (str, &un32, 0);

    e = hexToInt32C1 (str, &sn32, NULL, 0);
    e = hexToUInt32C1 (str, &un32, NULL, 0);

    e = hexCompareAsInt32 (str, str2, &cr);
    cr = hexInt32OrSmaller (str, str2);
    e = hexCompareAsUInt32 (str, str2, &cr);
    cr = hexUInt32OrSmaller (str, str2);
    /* END Hex32 Functions */

    if (e){} if (sn32){} if (un32){}
    return 0;
}

/* *********************START HEADER GUARDS TEST********************* */
#ifndef ___faiNumber_faiNumberConsts_H___
  #error "Fail to find the header guard for ___faiNumber_faiNumberConsts_H___"
#endif

#ifndef ___faiNumber_BinaryUtil32_H___
  #error "Fail to find the header guard for ___faiNumber_BinaryUtil32_H___"
#endif

#ifndef ___faiNumber_DecimalUtil32_H___
  #error "Fail to find the header guard for ___faiNumber_DecimalUtil32_H___"
#endif

#ifndef ___faiNumber_HexUtil32_H___
  #error "Fail to find the header guard for ___faiNumber_HexUtil32_H___"
#endif

#ifndef ___faiNumber_OctalUtil32_H___
  #error "Fail to find the header guard for ___faiNumber_OctalUtil32_H___"
#endif
/* **********************END HEADER GUARDS TEST********************** */
