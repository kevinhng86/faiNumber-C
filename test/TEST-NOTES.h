/* @NOTE - DO NOT IMPORT. THIS FILE ONLY CONTAIN TEST NOTES.
 *       - NOTES ARE BEING KEPT LIKE THIS SO THAT IT EASIER TO READ
 *       - WHEN DIRECTLY WORKING WITH CODE.
 **/
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

/*
 *
 * @NOTE  Test codes do not need to be written for best performance.
 *
 * @CHECK-LIST  (1) Final inspection.
 *
 * @TODO  (a) Organize, grammar check, and spell check this file.
 *        (b) After v1.0.f, some or all of the tests could be converted
 *            into code path test.
 *
 * Test Scope  Each test should be of its own scope to ensure
 *             correctness between each test unit and to reduce the
 *             chances of mistakenly assigning to the previous test
 *             unit variables. Exception to macro test suit, as macro
 *             test suits are enclosed in their own scopes.
 *
 * Invalid Digits Choosing Rules:
 * Unless the algorithm change:
 * (a) The chosen invalid digit if were valid, should be one value
 *     larger than the max digit of the base that is being tested.
 * (b) If the parsing algorithm for the base that is being tested does
 *     not have a connection of its max digit to the next valid digit
 *     but unavailable for this base then  the ASCII Char Code(58)(:) of
 *     the character that is one value higher than the valid digit with
 *     the maximum value. For example, with the current algorithm of
 *     version v1.*.*, only base 10.
 * (c) With the current algorithm, if the base that is being tested have
 *     its maximum value valid digit as the maximum possible digit then
 *     any invalid digit can be chosen. For example, with the current
 *     algorithm of version v1.*.*, only base 35.
 * (d) If a string of invalid digit, at least one invalid digit must
 *     match the criteria of (a), (b), and (c).
 * (e) For tests that require parsing a valid segment between two
 *     invalid segments where both of the invalid segments could affect
 *     the result value then at least one invalid digit from each
 *     invalid segment must meet the criteria of (a), (b), and (c). The
 *     placement of these invalid digits are depended on the type of
 *     test.
 * *** Comparators cases are exempted from the invalid digits choosing's
 *     rules as their purposes are not to test the accuracy of the
 *     parsers but to test the accuracy of the comparators' algorithms.

 * Overflow Case Definition & Rules:
 * (d.a) When max value and min value's max length are the same, it is
 *       easy to choose overflow cases as test1 and test2 will cover all
 *       possible known bugs. Test 1 will test all the valid digits up
 *       to max length. Where test 2 will test all the invalid digits up
 *       to max length.
 * (d.b) When min value and max value's max length are differences,
 *       there can only be one number that can be parsed at min value's
 *       max length(the longer one). With the current macro test code,
 *       test1 will not be able to cover all the valid digits at min
 *       value's max length. For invalid digits, test2 will be able to
 *       cover that. The important bug to test for here is that all
 *       valid digits, except 0, must produce an overflow result.
 *       When min value and max value's max length are not the same,
 *       the only parsable number at min value's max length start with
 *       a single one and the rest are 0s.
 * (r.a) Bases on the definitions, when testing for overflow, if max
 *       lengths of min value and max value are diffent, a case with
 *       test string at min value's max length. That string start with
 *       a one and except for the last right most digits, all zeros.
 *       The right most digit is the digit with the highest value
 *       for that base. For example, for Octal, the right most digit
 *       is a 7. This test only needed to be added where it matter.
 *       For example, this test does not need to be executed for
 *       functions that return a general code for all errors.
 *
 * Max Length Definition & Rules:
 * (d.a) If there are min value and max value(signed) then there are two
 *       max length, 1 for min and 1 for max value. Otherwise, there is
 *       only 1 max length.
 * (d.b) When min value and max value have diffence lengths, none can
 *       overflow at the lower length.
 * (d.c) When length of max value and min value are not the same, in
 *       true reality, except for one number, all number parse that are
 *       longer than max value's length will overflow.
 * (d.d) Notwithstanding (d.c), with the current design, the behaviour
 *       of the functions of this library is that although the value is
 *       not used when overflow, the digit of min value's max length is
 *       still processed. Thus, function that skip invalid checking,
 *       will not skip invalid checking until the length is beyond min
 *       value's max length.
 * (r.a) Thus(d.d), and because of the amount of macro this library use,
 *       if max value's max length is smaller than min value's max
 *       length, all tests for positive parsing, that require max
 *       length + 1 are required to be tested twice. One for, max
 *       value's max length + 1, and the other for, min value's max
 *       length + 1.
 * (r.b) Rule (r.a) does not apply if:
 *       (1) Naturally the test data is longer than min value's max
 *           length.
 *       (2) The parse on error options.
 *       If rule (r.a) does not apply then max length is min value's
 *       max length.
 *
 * 1st test: Min to max digit check.
 *           Parsing from min digit(0) to max digit of base at every
 *           possible positions to "every possible positions - 1".
 *           For example, in binary, signed, the minimum value of int32
 *           has a length of 32, while it counter part, maximum value
 *           has a length of 31. Thus, parse from min digit to max
 *           digit at 31 possible positions. To do this, after each
 *           loop of min to max digit a 1 is added to the front of the
 *           new loop counter value.
 *
 *           For this example, in base 10, for position 1, the loop
 *           start from digit min to digit max, at every loop 0(preN)
 *           + digit value of that loop. For the next loop,
 *           preN = (preN + 1) * base, for base 10, preN is
 *           (0 + 1) x 10, of which, is 10. Then the same loop at
 *           position 1 is executed, parse from digit min to max with
 *           10 added to the digit value of a loop. For the next loop,
 *           preN is (10 + 1) * 10 = 110, and so on for the remaining
 *           loop.
 *
 *           For this test, position start at 1 because it make
 *           it easier to ensure that the test loop to not create an
 *           overflow result even when the value is discarded. That
 *           is to ensure the portability of the test code.
 *
 *           For bases that are > 10, both, the lower cases and the
 *           upper cases of the digit representation must be tested.
 *
 *           Functions that have multiple parsing engine for different
 *           options, must have each of their engine tested. If possible,
 *           one test one name. If not, A, B, C, ... can suffix test 1
 *           for each engine.
 *
 * 2nd test: Invalid digits check.
 *           It is better to do the unneeded test rather than missing
 *           one test. Thus, test all invalid digits at every possible
 *           position to "every possible positions - 1" and they must
 *           not be parseable. The invalid characters, includes sign
 *           characters, must be tested and they must not be parsable,
 *           even when function that is being tested accept signs
 *           parsing as signs are only valid when they are preceded by
 *           a set of valid digits without being precedeed by non
 *           skipable characters.
 *
 *           The concept of checking result value for this test is
 *           almost similar to test 1. For this test there are two
 *           parts in the each test string, the valid part and the
 *           invalid part. As the position grow, so does the valid part.
 *           For example, for position 1, the test strings will just
 *           contain a single invalid characters, and those test strings
 *           must yielded a parsed result value of zero. For position
 *           2, the test strings, are two characters, a '1' and an
 *           invalid digit, these strings must yield a parsed value of
 *           1. For the 3 positions, the test strings are 3 characters
 *           '11' and an invalid digits, and so on for the rest of the
 *           positions.
 *
 *           For functions that can parse signed values, 3 strings will
 *           always be tested for each invalid character. Thus, for
 *           position 1, for functions that can parse sign, for each
 *           invalid digit, 3 strings, 1 with just an invalid character,
 *           1 with a + sign and an invalid character, and 1 with a -
 *           Sign and an invalid character.
 *
 *           Functions that have multiple parsing engine for different
 *           options, must have each of their engine tested. If possible,
 *           one test one name. If not, A, B, C, ... can suffix test 2
 *           for each engine.
 *
 *           Also, for continuous parsers, ensure that invalid digits
 *           are skips properly. The invalid digits skipper can be
 *           considered as a parsing engine without yielding a value.
 *           Thus, the test naming suffix rule above is suffice.
 *
 * 3rd test: Maximum values parsing and leading zero parsing.
 *           a) Parse max length and trigger overflow check but not max
 *              value or min value. Where not possible, skip.
 *           b) Parse max value and where applicable, min value
 *           (negative). If signed parse both the max value without
 *           sign and with sign(+).
 *           c) Parse one number with leading 0s, a number with only
 *              zeros. If signed, parse one negative number with
 *              leading 0s with more zeroes then the positive counter
 *              part.
 *
 * 4th test  Parsing errors, test both error and return value.
 *           a) Take note that test 2 already covered invalid characters
 *              up to a certain length.
 *
 * True Error functions 3rd test note:
 *
 * Invalid format:
 * a) A string start with one single invalid character.
 * b) Max length + 1 with the last character being the invalid digit.
 *    Instead of following the invalid digit rule, this invalid digit,
 *    is the char code(47) of the character that is one value lower than
 *    the lowest valid digit(0). With the current code path, whether
 *    if min and max value's are the same or different, 1 test of
 *    the longest max length is suffice. But without the invalid digit,
 *    the test string should not overflow. This SKIPPED for bases that
 *    ultilize a digit map, as it is not possible that that digits map
 *    would provide a number for a character that is not a valid digit.
 *    Test 1 and Test 2 already covered all the valid and invalid
 *    digits of bases in the digit map.
 * c) Max length + 1 with the last character being the invalid digit
 *    with the valid digits with a value that does not trigger exact
 *    length overflow check if possible. Preferably (1 - max digit and
 *    cycle again).
 * d) Max value + 1 and where applicable min value - 1, with an additional
 *    invalid digiti on the right side.
 * e) Max value and where applicable, min value, with an additional
 *    invalid digit on the right side.
 * f) Obviously overflow/underflow at the 9th digit plus two more
 *    character to the right, and the right most is the invalid
 *    character.
 * g) At least max length x 2 with all valid digits, EXCEPT for 1 right
 *    most character(Preferably 1 to max digit).
 * h) For unsigned, test +0 and -0. This is to ensure there isn't any
 *    misplaced code during templating.
 * i) Empty string.
 *
 * Flexi functions test note:
 *
 * FP Error Parsing Test (Without Long Check)(Without Error Parsing):
 * Invalid:
 * a) A string that is less than the overflow length and start with one
 *    single invalid character. This should perform the same, without
 *    any option and with all options.
 * b) Max length + 1 with the last character being the invalid digit.
 *    This must yield an under/overflow error with a result value of
 *    zero. If signed, check all, without, +, and - sign.
 * c) For unsigned, test +0 and -0. This is to ensure there isn't any
 *    misplaced code during templating.
 * d) Empty string(Must yield an invalid error)(OPT_NONE and all as
 *    all options should behave the same with this).
 *
 * FP Error Parser Parsing :
 * a) A string that is equal or more than the overflow length and start
 *    with one single invalid character.
 * b) Max length + 1 with the last character being the invalid digit
 *    with the valid digits with a value that does not trigger exact
 *    length overflow check if possible. Preferably (1 - max digit and
 *    cycle again).
 * c) Max value + 1 and where applicable min value - 1, with an additional
 *    invalid digit on the right side.
 * d) Max value and where applicable, min value, with an additional
 *    invalid digit on the right side.
 * e) Obviously overflow/underflow at the 9th digit plus two more
 *    character to the right, and the right most is the invalid
 *    character.
 * f) At least max length x 2 with all valid digits, EXCEPT for 1 right
 *    most character(Preferably 1 to max digit).
 * g) For unsigned, test two strings that are longer than the
 *    overflow length, one start with '-' and one with '+' and the rest
 *    of both strings only contain the one digit. This is to ensure
 *    that there isn't any misplaced code during templating.
 *
 * FP Long Check:
 * a) Without parse on error, max length + 1 and start with one single
 *    invalid character.
 * b) Without parse on error, max length + 1 with the last character.
 *    Instead of following the invalid digit rule, this invalid digit,
 *    is the char code(47) of the character that is one value lower
 *    than the lowest valid digit (0). If min and max value length
 *    differ, use min value. This string, if were without the invalid
 *    digit shouldn't overflow. SKIP, if dmap is ultilized.
 * c) Without the parse on error option, max length + 1 invalid digit +
 *    max length. Preferably (1 - max digit and cycle again). This
 *    string if without the invalid digit and the second max length,
 *    shouldn't overflow. Thus, if min and max value's length differ,
 *    it is min value.
 * d) Same as (c) but with the parse on error option.
 * e) With the parse on error option,
 *    {{CODE PATH OVERFLOW}}{{1 INVALID DIGIT}}{{CODE PATH OVERFLOW}}
 *    and as much as needed and as little as needed.
 * f) All case(s) of (e) but this time the invalid digit is a valid
 *    digit of max value of base. Also with the parse on error option.
 * g) Max value and where applicable, min value, + 1 length. With the
 *    last character being a valid one.
 *
 * FN Long Check:
 * a) Max length + 1 with the last character being the invalid digit.
 *    Instead of following the invalid digit rule, this invalid digit,
 *    is the char code(47) of the character that is one value lower than
 *    the lowest valid digit(0).
 * b) Max length + 1 with the last character being the invalid digit
 *    with the valid digits with a value that does not trigger exact
 *    length overflow check if possible. Preferably (1 - max digit
 *    and cycle again).
 * c) Same as (b) but without any invalid digit in the string.
 * d) At least max length x 2 with all valid digits, EXCEPT for 1 right
 *    most character(Preferably max and if applicable min value).
 * e) Same as string as (d), but this time, all the digits are valid.
 *
 * FN IGNORE_TSPACES:
 * (a) Current test.
 * (b) All possible overflow detection on max length digit plus more
 *     than one whitespace character proceeding the valid digits.
 * (c) All the previous cases of (c) with a valid digit proceeding the
 *     whitespaces. When min value and max value's max length are not
 *     the same, only min value's max length need to be tested.
 *
 ===============START EXAMPLE CASES FOR IGNORE_TSPACES==================
 * ** This is just a reference of the behaviour of the function
 *    real test case may differ. Real test cases are based on code
 *    path of the function. **
 *
 * nopt    = without long check, without IGNORE_TSPACES
 * wlc     = with long check
 * wits    = with IGNORE_TSPACES
 * wlcits  = with long cheeck + IGNORE_TSPACES
 * e(of)   = error overflow. *could be under or over
 * e(if)   = error invalid format
 * e(0)    = error none
 * r(n)    = result with n amount of digit.
 * *** Example overflow at digit 9 ***
 *
 *                     |  nopt         |     wlc      |    wits     |   wlcits
 * "12345678   \0"     | r(8) e(of)    | r(8) e(if)   | r(8) e(0)   | r(8) e(0)
 * "12345678    0\0"   | r(8) e(of)    | r(8) e(if)   | r(8) e(if)  | r(8) e(if)
 * "12345678a\0"       | r(8) e(of)    | r(8) e(if)   | r(8) e(if)  | r(8) e(if)
 * "12345678\0"        | r(8) e(0)     | r(8) e(0)    | r(8) e(0)   | r(8) e(0)     * T1 and T2 tested this unless
 *                                                                                    min and max value's length are
 *                                                                                    different.
 *
 * "123456789   \0"    | r(8) e(of)    | r(8) e(if)   | r(8) e(of)  | r(8) e(of)
 * "123456789    0\0"  | r(8) e(of)    | r(8) e(if)   | r(8) e(if)  | r(8) e(if)
 * "123456789a\0"      | r(8) e(of)    | r(8) e(if)   | r(8) e(if)  | r(8) e(if)
 * "123456789\0"       | r(8) e(of)    | r(8) e(of)   | r(8) e(of)  | r(8) e(of)
 *
 ===============START EXAMPLE CASES FOR IGNORE_TSPACES==================
 *
 *
 * Functions With Options and Manual Cases
 * a) If the behaviour of the individual case should behave the same
 *    across all options, one of it version should be be tested with
 *    no option, and the rest with all options on. If the test cases
 *    are in a similar category(i.e parsing max and min value),
 *    one option none should suffice.
 *
 * Continuous functions test note:
 *
 * Without and with NO_INVALID_SKIP test note:
 *
 * Without - a) A valid number preceed by -+, then the same number
 *              preceed by +-. (Only to signed function)
 *           b) A string that start with 1 invalid digit and end at
 *              an invalid digit. If signed parse 3, without sign, with
 *              + and - sign.
 *           c) A string that is max length + 1 with the last character
 *              being an invalid digit. Instead of following the invalid
 *              digit rule, this invalid digit, is the char code(47) of
 *              the character that is one value lower than the lowest
 *              valid digit(0).
 *           d) A string that is max length length
 *           e) A string that start with >5 invalid digits and end at
 *              > 1 invalid digit. If signed parse 3, without sign, with
 *              + and - sign.
 *           f) A string with only invalid digit.
 *           g) An empty string.
 *
 * With    - a) A string start with one invalid digit.
 *           b) A string start with valid digit and end with invalid
 *              digit. If signed parse 3, without sign, with
 *              + and - sign.
 *           c) A string with only invalid digit.
 *           d) An empty string.
 *
 * Overflow parsing test note:
 * -- Tests are same cases, with just different options
 * Default/ERROR/SKIP     - a) Min/Max value -/+ 1.
 *                          b) Min/Max value -/+ 1, plus 1 additional
 *                             digit.
 *                          c) Min/Max value plus 1 additional digit.
 *                          d) Obvious overflow with what already parse
 *                             at max-th digit with exact max length.
 *                          e) Obvious overflow with what already parse
 *                             but one digit larger than max length.
 *                          f) Max length + 1 with digit from min to max.
 *                          g) At least max length times 2. Digit start
 *                             from min to max and cycle again.
 * -- h is for OVERFLOW_SKIP.
 * (h) All previous cases cycle again but this time, one additional
 *     invalid digit to the right of the string.
 * (i) All cases of (h) but instead of the invalid rules use char code
 *     (47).
 *
 * Invalid format with OVERFLOW_ERROR
 * (a) Max length + 1 with the right most character being an invalid
 *     digit. This string if were without the invalid digit shouldn't
 *     overflow. With the current code path, whether if min and max
 *     value's length are the same or different, it is suffice with 1
 *     test that ultilize the longer length.
 *
 * (b) Same as (a) except instead of following the invalid rule, an
 *     invalid digit with the ASCII value(47) that is less than the
 *     lowest possible digit(0).
 *
 *
 * Continuous parsing test note:
 * All option already been tested by the previous tests. Thus,
 * only two test cases are required. If signed these the numbers should
 * mix well between positive and negative. These numbers does not need
 * to be uniform, this test can be skipped but is executed to test the
 * capability of the functions.
 * a) Five set of numbers that are all not going to overflow.
 * b) Five set of numbers with 2 under/overflow.
 *
 * Comparators test note:
 * Comparator test cases are to test bugs of the comparator functions
 * and not whether if the parsers are working correctly(Other testers
 * already tested that). Thus, besides under/overflow cases, cases
 * that are built to test one comparator function could be reused
 * to test another comparator function even when when the data type are
 * not the same. However, in each category of test, there must a case
 * with the max/min value(and/or close-to) of the data type. Those,
 * if unique, should be the last case for their test category.
 *
 * For comparator errors cases where applicable, if the cases are not
 * in regard to the data value(i.e under/overflow), the same cases can
 * be reused.
 *
 * Binary Test Note:
 * a) For binary parsing, with this algorithm, it is almost suffice with
 * just test 1 and test 2. Nonetheless, the rest of the test still
 * execute and re run just to be standardly uniformly between all
 * bases.
 *
 * b) Although for two's complementing and signed, min value is one
 * length longer than max value, in reality, both negative and positive
 * parsing overflow at the length that is longer than the length of max
 * value. That is because there is only one number that can have that
 * length and it start with 1 and the rest is 0 digits for binary.
 * Thus, for int32_t, overflow length is 31 and not 32. With the
 * algorithm of this library, if length 32, and is valid, it will
 * be parsed differently so that only one number can validly be parsed.
 *
 * Notwithstanding those, for signed FP function's behaviour, the parser
 * will still parse even at length 32 for int32_t and the input string
 * of number is a positive one. However, for test 1 and 2, it is
 * suffice to test the parser at length 31. For OF len it must >32 to
 * test the parse on error parser. Thus, when testing overflow(+)
 * parsing, 2 additional cases is added, 2 original case will produce
 * result (lmax(minl)), while 2 new cases will not produce
 * result(lmax(minl) + 1).
 *
 * c) Certain tests that are too absolutely unneccesary to replicate
 *    are skipped.
 *
 * Skip List:
 * a) Invalid Format - (1) e
 *
 */
