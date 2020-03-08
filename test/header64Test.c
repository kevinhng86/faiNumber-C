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
/* faiNumber - header64Test.c */
/*
 * @NOTE  This test is for testing the joint header file for all 64-bit
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
#include "../h/faiNumber64.h"

int main(){
    char * str = "1";
    char * str2 = "2";
    int64_t sn64;
    uint64_t un64;
    int e;
    int cr;

    /* START Binary64 Functions */
    e = binToInt64 (str, &sn64);
    e = binToInt64TrueError (str, &sn64);
    e = binToUInt64 (str, &un64);
    e = binToUInt64TrueError (str, &un64);

    e = binToInt64FP (str, 0, 0, &sn64, 0);
    e = binToInt64FN (str, &sn64, 0);
    e = binToUInt64FP (str, 0, 0, &un64, 0);
    e = binToUInt64FN (str, &un64, 0);

    e = binToInt64C1 (str, &sn64, NULL, 0);
    e = binToUInt64C1 (str, &un64, NULL, 0);

    e = binCompareAsInt64 (str, str2, &cr);
    cr = binInt64OrSmaller (str, str2);
    e = binCompareAsUInt64 (str, str2, &cr);
    cr = binUInt64OrSmaller (str, str2);
    /* END Binary64 Functions */

    /* START Octal64 Functions */
    e = octToInt64 (str, &sn64);
    e = octToInt64TrueError (str, &sn64);
    e = octToUInt64 (str, &un64);
    e = octToUInt64TrueError (str, &un64);

    e = octToInt64FP (str, 0, 0, &sn64, 0);
    e = octToInt64FN (str, &sn64, 0);
    e = octToUInt64FP (str, 0, 0, &un64, 0);
    e = octToUInt64FN (str, &un64, 0);

    e = octToInt64C1 (str, &sn64, NULL, 0);
    e = octToUInt64C1 (str, &un64, NULL, 0);

    e = octCompareAsInt64 (str, str2, &cr);
    cr = octInt64OrSmaller (str, str2);
    e = octCompareAsUInt64 (str, str2, &cr);
    cr = octUInt64OrSmaller (str, str2);
    /* END Octal64 Functions */

    /* START Decimal64 Functions */
    e = decToInt64 (str, &sn64);
    e = decToInt64TrueError (str, &sn64);
    e = decToUInt64 (str, &un64);
    e = decToUInt64TrueError (str, &un64);

    e = decToInt64FP (str, 0, 0, &sn64, 0);
    e = decToInt64FN (str, &sn64, 0);
    e = decToUInt64FP (str, 0, 0, &un64, 0);
    e = decToUInt64FN (str, &un64, 0);

    e = decToInt64C1 (str, &sn64, NULL, 0);
    e = decToUInt64C1 (str, &un64, NULL, 0);

    e = decCompareAsInt64 (str, str2, &cr);
    cr = decInt64OrSmaller (str, str2);
    e = decCompareAsUInt64 (str, str2, &cr);
    cr = decUInt64OrSmaller (str, str2);
    /* END Decimal64 Functions */

    /* START Hex64 Functions */
    e = hexToInt64 (str, &sn64);
    e = hexToInt64TrueError (str, &sn64);
    e = hexToUInt64 (str, &un64);
    e = hexToUInt64TrueError (str, &un64);

    e = hexToInt64FP (str, 0, 0, &sn64, 0);
    e = hexToInt64FN (str, &sn64, 0);
    e = hexToUInt64FP (str, 0, 0, &un64, 0);
    e = hexToUInt64FN (str, &un64, 0);

    e = hexToInt64C1 (str, &sn64, NULL, 0);
    e = hexToUInt64C1 (str, &un64, NULL, 0);

    e = hexCompareAsInt64 (str, str2, &cr);
    cr = hexInt64OrSmaller (str, str2);
    e = hexCompareAsUInt64 (str, str2, &cr);
    cr = hexUInt64OrSmaller (str, str2);
    /* END Hex64 Functions */

    if (e){} if (sn64){} if (un64){}
    return 0;
}

/* *********************START HEADER GUARDS TEST********************* */
#ifndef ___faiNumber_faiNumberConsts_H___
  #error "Fail to find the header guard for ___faiNumber_faiNumberConsts_H___"
#endif

#ifndef ___faiNumber_BinaryUtil64_H___
  #error "Fail to find the header guard for ___faiNumber_BinaryUtil64_H___"
#endif

#ifndef ___faiNumber_DecimalUtil64_H___
  #error "Fail to find the header guard for ___faiNumber_DecimalUtil64_H___"
#endif

#ifndef ___faiNumber_HexUtil64_H___
  #error "Fail to find the header guard for ___faiNumber_HexUtil64_H___"
#endif

#ifndef ___faiNumber_OctalUtil64_H___
  #error "Fail to find the header guard for ___faiNumber_OctalUtil64_H___"
#endif
/* **********************END HEADER GUARDS TEST********************** */
