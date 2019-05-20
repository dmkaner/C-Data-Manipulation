#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {





  {"bitXor", (funct_t) bitXor, (funct_t) test_bitXor, 2, "& ~", 14, 1,
    {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"anyOddBit", (funct_t) anyOddBit, (funct_t) test_anyOddBit, 1,
    "! ~ & ^ | + << >>", 12, 2,
    {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"conditional", (funct_t) conditional, (funct_t) test_conditional, 3, "! ~ & ^ | << >>", 16, 3,
    {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"bitCount", (funct_t) bitCount, (funct_t) test_bitCount, 1, "! ~ & ^ | + << >>", 40, 4,
    {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"isTmin", (funct_t) isTmin, (funct_t) test_isTmin, 1, "! ~ & ^ | +", 10, 1,
    {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"isLessOrEqual", (funct_t) isLessOrEqual, (funct_t) test_isLessOrEqual, 2,
    "! ~ & ^ | + << >>", 24, 3,
    {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"twosComp2SignMag", (funct_t) twosComp2SignMag, (funct_t) test_twosComp2SignMag, 1, "! ~ & ^ | + << >>", 15, 4,
    {{TMin+1, TMax},{TMin+1,TMax},{TMin+1,TMax}}},
  {"floatAbsVal", (funct_t) floatAbsVal, (funct_t) test_floatAbsVal, 1,
    "$", 10, 2,
    {{1, 1},{1,1},{1,1}}},
  {"floatScale4", (funct_t) floatScale4, (funct_t) test_floatScale4, 1,
    "$", 30, 4,
    {{1, 1},{1,1},{1,1}}},
  {"", NULL, NULL, 0, "", 0, 0,
    {{0, 0},{0,0},{0,0}}}
};
