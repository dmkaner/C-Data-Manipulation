/* 
 * CS:APP Data Lab 
 * 
 * Dylan Kane dqk5384
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */


/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

  /*
   * This function achieves the xor operator
   * by first using x and y as a mask for 
   * eachother and then reversion all the bits,
   * then doing this again but with x and y
   * having reversed bits. When these two 
   * values are "anded" it works because
   * it simulates exaclty what xor is doing,
   * return a 1 only if the two bits are
   * different
   */

  int reversedBits = ~(x&y);
  int doubleReversedBits = ~((~x) & (~y));

  int xor = doubleReversedBits & reversedBits;  
   
  return xor;
}




/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {

  /*
   * The function is able to figure out if
   * there are any 1s in the odd bit places
   * by first masking all the 1s in a group of
   * 8 bits which is only necessary because
   * we cannot hold large constants. Basiclly
   * 170 is the largest constant that consists
   * of alternating ones, being in the odd 
   * position. After using the alternating ones
   * as a mask, if there are still any values
   * left just double bang that value to 
   * turn it into a 1 or 0
   */

  //shifting all 1s in 8 bits
  int group1 = x;
  int group2 = x >> 8;
  int group3 = x >> 16;
  int group4 = x >> 24;
  int collectedOnes = group1 | group2 | group3 | group4;
  
  //masking odd places ones
  int alternatingOnes = 170;
  int allOddBitsIncluded = collectedOnes & alternatingOnes;

  //double bang to convert to corrent number
  int convertVal = !!allOddBitsIncluded; 

  return convertVal;

}





/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {

  /*
   * This function works by taking the x value
   * and converting it to a 1 or 0 with the
   * double bang, the using this to create two 
   * masks. Each mask will correnspond to y or z
   * and they will either let all the bits
   * through or none of the bits through depending
   * on which mask it is. If !!x is 1 then
   * y's mask will be all ones and z's mask
   * will be the opposite, all zeros. After this
   * the two values are simply or'd which
   * works because one will always be zero.
   */

  //create first mask for y
  int filter1 = ~(!!x) + 1;

  //create mask for z that is just the opposite of y's
  int filter2 = ~filter1;

  //use the masks and then just return the added results
  int val = (filter1 & y) | (filter2 & z);

  return val;
}





/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  
  /* 
   * Piazza was really helpful for this one.
   * Advice was given to create a pattern to do
   * the counting of bits in parralel, so the first
   * section of this code is creating that pattern
   * of a 1 bit every 4 bits, and then the number is
   * shifted on top of the pattern to have each
   * section of 4 bits count the ones. These values 
   * are then extracted by shifting 
   * the appropriate amount of spaces.
   *
   */ 
  
  //instantiate total
  int total;

  //creates first layer, 17 is 10001
  int baseLayer = 17 | (17 << 8);

  //pattern is made by shifting and adding 
  int pattern = baseLayer | (baseLayer << 16);
  
  //this section shifts number along the bits
  int sum = x & pattern;
  sum += x >> 1 & pattern;
  sum += x >> 2 & pattern;
  sum += x >> 3 & pattern;
  
  //totals up the 1s by getting each section of 4
  total = sum << 28 >> 28; 
  total += sum << 24 >> 28;
  total += sum << 20 >> 28;
  total += sum << 16 >> 28;
  total += sum << 12 >> 28;
  total += sum << 8 >> 28;
  total += sum << 4 >> 28;
  total += sum >> 28;
   
  return total;

}






/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
 
  /*
   * This solution reverses all the bits then
   * adds one because x's minimum value is the
   * only value that will become itself with
   * this operation. There is one special case
   * where zero will actually become itself
   * aswell though, this is checked with the
   * special case checker, making sure the
   * value actually has a 1 in the LSB position 
   *
   */

  //operation that turns the minimum value into itself
  int minChecker = !(x ^ ((~x) + 1));

  //checks for special case of 0
  int specialCaseChecker = !!x;
  
  return minChecker & specialCaseChecker;

}






/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
 
  /*
   * This one was a doozy for me. First here
   * I calculate if the operation will overflow
   * because this helps with special cases
   * later on. I then simulate subtraction by
   * reversing all the bits then add one, then
   * adding this to y which is essetially adding
   * the negative. I then check if this value is
   * positive or negative which will determine if
   * the operation was less than or equal to or
   * greater than. This is then used with the
   * overflow checker, x's sign, and y's sign
   * to determine all the special cases. I figured
   * this out by creating a kmap and deriving
   * a sum of products function  
   *
   */

  // checking for overflow and storing x and y's signs
  int xySum = x + y;
  int xSign = x >> 31;
  int ySign = y >> 31;
  int xySign = xySum >> 31;
  int oFlow = !(ySign ^ xSign) & (ySign ^ xySign);

  //simulates subtraction
  int simSubtract = y + ((~x)+1);

  //checks if positive or negative
  int regAnswer = !(simSubtract & (1<<31));
  
  //inverts y to save signs
  int invertedY = !ySign;

  //kmap sum of products representation
  int part1 = regAnswer & oFlow;
  int part2 = regAnswer & invertedY;
  int part3 = regAnswer & xSign;
  int part4 = !oFlow & xSign & invertedY;

  return part1 | part2 | part3 | part4;
}





/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
 
  /*
   * This function is mainly working with the mag
   * variable, where the number is converted 
   * to its positive value. The rest of the code
   * is for determining if this should be done to
   * x, if x is already positive it should not be
   * converted. This is descided by acutally just
   * using the code from the conditional function
   * above. 
   *
   */

  //extract sign for conditional
  int signBit = x >> 31; 
  int filter1 = ~(!!signBit) + 1;
  int filter2 = ~filter1;

  //converting the negative value to positive
  int mag = (1<<31) + (~x + 1);
 
  //conditional statement 
  return (filter1 & mag) | (filter2 & x);
}





/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  
  /*
   * This function is very simple, it just
   * uses an if statement to change the sign
   * to be 0 (least significant bit) so it is 
   * always positive, and also just returns 
   * the argument for the NAN 
   *
   */
  
  //extract sign bit
  unsigned sign = uf >> 31;
  
  //take care of NAN
  if (uf == 0x7fc00000) {
    return uf; 
  } else if (uf == 0xffc00000) {
    return uf;
  }
  
  //if Sign bit is negative, change it to 0
  if (sign == 0) {
    return uf;
  } else {
    return uf & ~(1<<31);
  }

}





/* 
 * floatScale4 - Return bit-level equivalent of expression 4*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale4(unsigned uf) { 
  /*
   * This function can mentally be split up into
   * three different senarios that need to be dealt
   * with, being normalized values, denormalized
   * values, and outlying cases. For normalized
   * values you just need to add two to the exponent,
   * for denormalized values you need to add two to
   * the exponent and shift the fraction two places
   * if this will not result in overflow, and for that
   * and the other cases return infinity or the 
   * argument given.  
   *
   */
  
  //instantiate variables
  unsigned nan;
  unsigned sign;
  unsigned exp;
  unsigned frac; 

  //Checks for zero and negative zero
  if (uf == 0) {
    return uf;
  } else if (uf == 0x80000000) {
    return uf;
  } 

  //Checks for NAN
  nan = ( (uf >> 23) & 255);
  if (nan == 255) {
    return uf;
  }

  //Extracting the three parts of a floating point
  sign = uf >> 31;
  exp = uf << 1 >> 24;
  frac = uf & 0x7FFFFF;

  //Check for overflow of the exponent
  if (exp + 2 >= 255) {
    return (sign << 31) | (255 << 23) | (0);
  }

  //If statment to handle denormalized and normalized
  if (exp == 0) {  
    
    //Determine if exp still needs added 
    unsigned bitTracker = frac >> 21;
    if (!!bitTracker == 1) {
      frac = frac << 1 & 0x7FFFFF;
      exp += 2;
    } else {
      frac = frac << 2 & 0x7FFFFF;
    }

  } else {
    exp += 2;
  }
  return (sign << 31) | (exp << 23) | (frac);

}
