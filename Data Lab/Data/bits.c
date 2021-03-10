/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
         
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
    //uses Demorgans law, ~(x|y) is the same as (~x & ~y)
    return (~x & ~y);
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
    //in order to check if it is a number that can be stored in 32 bits, we first shift left 16 times to get rid of the right 16 bits, and fill the leftmost 16 with 0s, then we shift right to return the original first 16 bits to their origional place, and leaving the rightmost 16 bits as 0s. This gets rid of the scenario that the number could be negative. By XORing the newly shifted number to the origional int x we will either get 0 if it is an exact match and therefore can be stored in 16 bits, or some other number indicating it cannot be stored in 16 bits.
    x = ((x << 16) >> 16) ^ x;
    //the ! changes x to 1 for a number that can be stored in 16 bits, or x to 0 if it cannot.
    return !x;
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
    //create new int filled with 0s and a single 1 in the LSB
    int x = 0x1;
    //shift 3 first, then double each following shift otherwise the binary number will be incremented improperly, this also decreases the amount of operations performed
    //00000000000000000000000000000001
    x = (x << 3) + x;
    //00000000000000000000000000001001
    x = (x << 6) + x;
    //00000000000000000000001001001001
    x = (x << 12) + x;
    //00000000001001001001001001001001
    x = (x << 24) + x;
    //01001001001001001001001001001001
    return x;
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
    //first create a number that alternates in a way such that every even-numbered bit holds a 1 value, and every odd-numbered bit holds a 0 value. 
    int y = 0x5;
    //00000000000000000000000000000101
    y = (y << 4) + y;
    //00000000000000000000000001010101
    y = (y << 8) + y;
    //00000000000000000101010101010101
    y = (y << 16) + y;
    //01010101010101010101010101010101
    //compare the newly created number using the bitwise & operator, which will check to see if there are any stray bits in odd-numbered places. If they are, the result after comparing will be 0x0, and then turns into a 1 with the first !, then inverted to 0 with the second !. The opposite of course occurs when there are bits in even-numbered places.
    return !!(y & x);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    //shifting the int x left 31 times, puts the LSB in the right-most place, then shifting right 31 times fills the rest of the binary places with whatever the LSB was. 
    x = x << 31;
    return (x >> 31);
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    //flip int x using the logical not (!), then use bitwise or (|) to compare to int y. By flipping x instead of y you isolate the test case: (1,0), which results in 0 being returned, if y was flipped the opposite would occur. Flipping either of them would account for both test cases in which x==y.
    return ((!x) | y);
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
    int x;
    int y;
    int z;
    //generates 32 bit mask filled with 1s
    //11111111111111111111111111111111
    x = ~0;
    //left shift x lowbit number of times
    //11111111111111111111111111111000
    y = (x << lowbit);
    //left shift x highbit + 1 number of times
    //11111111111111111111111111000000
    z = (x << highbit) << 1;
    //compare the y and bitwise not z masks with bitwise & operator to return the final mask of 1s
    //00000000000000000000000000111111 & 
    //11111111111111111111111111111000 returns:
    //00000000000000000000000000111000 
    return ~z & y;
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
    int sign;
    //multiply x by 3
    x = x + x + x;
    //if triple x is positive, after comparing to mask 3 sign will be 0, else if negative then sign will be 3, this accounts for rounding, since we divide by 4 in the next step
    sign = (x >> 31) & 3;
    //add sign to x to provide rounding effect, then divide by 4 by shifting right twice
    return (x + sign) >> 2;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    //initialize variable
    int sign;
    int dbl_x;
    int sign_dbl_x;
    int tpl_x;
    int sign_tpl_x;
    int overflow_check;
    int check_neg_overflow;
    //get the sign mask of x
    sign = (x >> 31);
    //doubles x
    dbl_x = (x + x);
    //gets the sign mask for the first stage of multiplication after doubling x
    sign_dbl_x = (dbl_x >> 31);
    //triples x
    tpl_x = (x + dbl_x);
    //gets the sign mask for the second stage of multiplication after tripling x
    sign_tpl_x = (tpl_x >> 31);
    //compares the sign masks of the original int x, double int x, and triple int x. If all of the sign masks are consisistent with one-another, then there was no overflow that needs to be accounted for. Creates a mask of 1s if there is overflow, otherwise 0s
    overflow_check = (sign ^ sign_dbl_x) | (sign_dbl_x ^ sign_tpl_x);
    //if x was negative to begin with, then a mask of 1 at the sign bit is created
    check_neg_overflow = (~(sign) ^ (0x1 << 31));
    //sets sign output to 0x80000000 if negative overflow occurs, if there was no overflow then tpl_x will be returned, otherwise if there is positive overflow returns 0x7FFFFFFF
    //if positive overflow: ((all 1s) & (0 followed by all 1s)) | ((all 0s) & (triple the value of x)) = 0x7FFFFFFF
    //if negative overflow: ((all 1s) & (1 followed by all 0s)) | ((all 0s) & (triple the value of x)) = 0x80000000
    //if no overflow:       ((all 0s) & (depends on x, irrelevant)) | ((all 1s) & triple the value of x))h = triple the value of x
    return (overflow_check & check_neg_overflow) | ((~overflow_check) & tpl_x);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    x = x ^ x << 16;
    //00000000000000000000000000000111 ^ 00000000000001110000000000000000
    //00000000000001110000000000000111
    x = x ^ x << 8;
    //00000000000001110000000000000111 ^ 00000111000000000000011100000000
    //00000111000001110000011100000111
    x = x ^ x << 4;
    //00000111000001110000011100000111 ^ 01110000011100000111000001110000
    //01110111011101110111011101110111
    x = x ^ x << 2;
    //01110111011101110111011101110111 ^ 11011101110111011101110111011100
    //10101010101010101010101010101011
    x = x ^ x << 1;
    //10101010101010101010101010101011 ^ 01010101010101010101010101010110
    //01010101010101010101010101010110
    //11111111111111111111111111111101
    return (x >> 31) & 1;
    //11111111111111111111111111111101 & 00000000000000000000000000000001
    //00000000000000000000000000000001
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    //ilog2(x) = n is equal to 2^n = x
    //max value that will ever need to be returned is 30.9999999999, therefore only 5 bits are needed
    //initialize y, final value to be returned
    int y = 0x00;
    //if there is a value in the most significant 16 bits of int x, then return 1 in the 5th LSB
    //this continues increasing from the 16th most significant bit if 10000 was returned for y, or decreasing from the 16th significant bit if 0 was returned for y
    //this is effectivley a binary search for the most significant bit, inserting bits in y that correspond to the number of shifts needed to get to that bit
    y = (!!(x >> 16)) << 4;
    y = (!!(x >> (y + 8)) << 3) + y;
    y = (!!(x >> (y + 4)) << 2) + y;
    y = (!!(x >> (y + 2)) << 1) + y;
    y = !!(x >> (y + 1)) + y;
    return y;
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x) {
    int sign;
    int round;
    //if x is positive, after comparing to mask 3 sign will be 0, else if negative then sign will be 3, this accounts for the difference in rounding with negatives
    sign = (x >> 31) & 3;
    //get the remainder after dividing by 4
    round = x & 3;
    //multiply round by 3, then add sign to account for if x is a negative number, since otherwise the result after 3/4 will be off by 1-3 in the negative direction
    //divide by 4 in order to correct the larger number recieved throuhg adding the remainders. This adjusts the remainder so that x can be correctly shifted
    //this is used to add 3/4s of the remainder back which would otherwise be lost in dividing x by 4
    round = ((round + round + round) + sign) >> 2;
    //divide x by 4 by shifting right twice first, this avoids potential overflow
    x = x >> 2;
    //now triple the value of x in order to complete the equivilate of multiplying the origional x by 3/4
    x = x + x + x;
    //add the remainder to x to provide rounding effect (towards 0)
    return x + round;
}
/*
 * Extra credit
 */
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    int neg_uf;
    //to account for NaN, initialize both the min and max of negative NaN (-infinity) floating point values as ints
    int max_negNaN = (1 << 31) >> 8;
    //1 11111111 00000000000000000000000
    //the most negative NaN would be:
    //1 11111111 11111111111111111111111
    //create variable to switch sign, 1 followed by 31 0s
    //1 00000000 00000000000000000000000
    int sign = 1 << 31;
    //get the negative absolute value of uf by sign OR uf, this also converts +infinity NaN to -infinity NaN, so that both may be checked with the same boundry in the if statment
    int neg_abs_uf = sign | uf;
    //check to see if neg_abs_uf is in the negative NaN region (-infinity), if it is, then the initial argument is returned
    if (max_negNaN < neg_abs_uf) {
        //return argument uf
        return uf;
    }
    //otherwise, the negative of the initial argument is returned, since it is not a NaN
    //switch sign of uf with XOR
    neg_uf = uf ^ sign;
    //else return the negative of arument uf
    return neg_uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    return 2;
}
