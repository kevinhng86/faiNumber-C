## Benchmark

How fast is the main parsing engine of faiNumber-C comparing to other
numerical parser functions from other libraries?

Below are the benchmark results for the main parser engines of
faiNumber-C(Version 1.0.f) comparing to atoi(), strtol, strtoul,
strtoll, or strtoull.

Benchmark scores are in milliseconds. For each test, all functions of
that test parse the same array of 10,000,000 randomly generated valid
input strings.

For all of the benchmark tests, all of faiNumber-C functions were built
and tested as a dynamic link library. faiNumber-C functions were built
with -O2 optimization.

For the definition of max length, max length is the maximum length of
a valid parsable number that can yield a valid result. When applicable,
if min value and max value's max lengths differ, max length is the max
length of max value(the shorter length).

###### CPU: AMD® A10-7800 radeon r7, 12 compute cores 4c+8g × 4
###### OS: Ubuntu 18.04.3 LTS
###### Compiler: gcc | Version: 7.5.0 | Optimization: -O2
###### C Standard: c99
<br>

#### Vary Length Test Strings With A Length Of At Least 1 To Max Length
| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| decToInt32 | 213 | 213 | 214 |
| atoi       | 415 | 413 | 414 | 
| strtol     | 418 | 424 | 420 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| dectoUInt32 | 161 | 157 | 158 |
| strtoul     | 343 | 341 | 339 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| decToInt64 | 267 | 268 | 272 |
| strtoll    | 558 | 568 | 561 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| binToInt64 |  443 |  443 |  444 |
| strtoll    | 1237 | 1248 | 1244 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| octToInt64 | 260 | 260 | 260 |
| strtoll    | 590 | 597 | 592 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| hexToInt64 | 232 | 232 | 232 |
| strtoll    | 774 | 781 | 775 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| decToUInt64 | 219 | 219 | 219 |
| strtoull    | 474 | 490 | 474 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| binToUInt64 |  421 |  431 |  419 |
| strtoull    | 1194 | 1224 | 1196 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| OctToUInt64 | 214 | 222 | 214 |
| strtoull    | 520 | 531 | 522 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| hextoUInt64 | 186 | 190 | 187 |
| strtoull    | 713 | 739 | 716 |

#### Max Length Test Strings

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| decToInt32 | 213 | 213 | 213 |
| atoi       | 411 | 413 | 411 |
| strtol     | 416 | 420 | 418 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| dectoUInt32 | 156 | 156 | 156 |
| strtoul     | 417 | 421 | 416 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| decToInt64 | 325 | 326 | 323 |
| strtoll    | 853 | 850 | 841 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| binToInt64 |  600 |  616 |  602 |
| strtoll    | 2226 | 2218 | 2213 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| octToInt64 | 276 | 278 | 276 |
| strtoll    | 905 | 903 | 899 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| hexToInt64 |  217 |  214 |  215 |
| strtoll    | 1207 | 1201 | 1201 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| decToUInt64 | 250 | 249 | 250 |
| strtoull    | 768 | 759 | 760 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| binToUInt64 |  594 |  586 |  588 |
| strtoull    | 2197 | 2176 | 2176 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| OctToUInt64 | 223 | 222 | 222 |
| strtoull    | 851 | 853 | 861 |

| | Test 1  | Test 2 | Test 3 |
|---|---|---|---|
| hextoUInt64 |  143 |  144 |  144 |
| strtoull    | 1201 | 1190 | 1191 |

</div>
