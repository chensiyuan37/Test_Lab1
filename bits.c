/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>陈思源 3070254799
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x&~y)&~(x&y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask=x>>31;
  return mask&(~x+1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int src_shift = src << 3;
  int dst_shift = dst << 3;
  int byte = (x >> src_shift) & 0xFF;
  int clear_mask = ~(0xFF << dst_shift);
  return (x & clear_mask) | (byte << dst_shift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0F;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y = x | (x + 1);
  int z = ~y;
  return z & (~z + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int n_mod = n & 31;
  int left_shift = (~n_mod + 1) & 31;
  int mask = ~(((1 << 31) >> n_mod) << 1);
  return ((x >> n_mod) & mask) | (x << left_shift);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int d = 1 << n;
  int half = d >> 1;
  int q = x >> n;
  int odd = q & 1;
  int bias = half + ~0 + odd;
  return ((x + bias) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int xor_xy = x ^ y;
  int base = (x & y) + (xor_xy >> 1);
  
  int odd = xor_xy & 1;
  
  int sx = x >> 31;             
  int sy = y >> 31;              
  int same_sign = ~(sx ^ sy);    
  int diff = x + (~y + 1);       
  int diff_sign = diff >> 31;    
  int gt = ((same_sign & ~diff_sign) | (~same_sign & ~sx)) & 1;
  
  return base + (gt & odd);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int xma = x + ~a + 1;
  int x_ge_a = ~((xma ^ ((x ^ a) & (xma ^ x))) >> 31);

  int xmb = x + ~b + 1;
  int x_ge_b = ~((xmb ^ ((x ^ b) & (xmb ^ x))) >> 31);

  int amx = a + ~x + 1;
  int a_ge_x = ~((amx ^ ((a ^ x) & (amx ^ a))) >> 31);

  int bmx = b + ~x + 1;
  int b_ge_x = ~((bmx ^ ((b ^ x) & (bmx ^ b))) >> 31);

  return ((x_ge_a & b_ge_x) | (x_ge_b & a_ge_x)) & 1;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x4 = x << 2;
  int result = x4 + x;
  
  int diff_x4 = (x4 >> 2) ^ x;
  int ovf_x4 = !!diff_x4;
  
  int same_sign = ~((x4 ^ x) >> 31);
  int diff_sign = (result ^ x4) >> 31;
  int ovf_add = !!(same_sign & diff_sign);
  
  int ovf = ovf_x4 | ovf_add;
  
  int mask = (ovf << 31) >> 31;
  
  int sat = (x >> 31) ^ ~(1 << 31);
  
  return (result & ~mask) | (sat & mask);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int hx = x >> 31;
  int hy = y >> 31;
  int hz = z >> 31;

  int s1 = x + y;
  int c1 = (((x & y) | ((x | y) & ~s1)) >> 31) & 1;
  int h1 = hx + hy + c1;

  int s2 = s1 + z;
  int c2 = (((s1 & z) | ((s1 | z) & ~s2)) >> 31) & 1;
  int h2 = h1 + hz + c2;

  int sign_s2 = s2 >> 31;

  int ovf = h2 ^ sign_s2;
  int is_ovf = !!ovf;

  int ret = (h2 >> 31) | 1;

  int mask = is_ovf << 31 >> 31;
  return ret & mask;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned s = uf & 0x80000000;
    unsigned e = (uf >> 23) & 0xFF;
    unsigned m = uf & 0x7FFFFF;

    if (e == 0xFF) {
        return uf;
    }
    if (e == 0 && m == 0) {
        return uf;
    }

    unsigned significand;
    int E; 
    if (e == 0) {
        significand = m;
        E = -149;
    } else {
        significand = (1 << 23) | m;
        E = e - 127;
    }

    unsigned prod = significand * 3;

    int p = 31;
    while (p >= 0 && !(prod & (1u << p))) {
        p--;
    }

    int e_new;
    if (e == 0) {
        e_new = p - 23;
    } else {
        e_new = p + E + 103;
    }

    if (e_new >= 255) {
        return s | 0x7F800000;
    }

    if (e_new <= 0) {
        unsigned m_new = prod >> 1;
        if ((prod & 1) && (m_new & 1)) {
            m_new++;
        }
        if (m_new >= (1 << 23)) {
            return s | (1 << 23); 
        }
        return s | m_new;
    } else {
        int shift = p - 23;
        unsigned sig = prod >> shift;
        unsigned dropped = prod & ((1u << shift) - 1);
        unsigned half = 1u << (shift - 1);
        if (dropped > half || (dropped == half && (sig & 1))) {
            sig++;
            if (sig == (1u << 24)) {
                sig >>= 1;
                e_new++;
                if (e_new >= 255) {
                    return s | 0x7F800000;
                }
            }
        }
        unsigned m_new = sig & 0x7FFFFF;
        return s | (e_new << 23) | m_new;
    }
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned s = uf & 0x80000000;
    unsigned e = (uf >> 23) & 0xFF;
    unsigned m = uf & 0x7FFFFF;

    /* NaN 或无穷大，直接返回 */
    if (e == 0xFF) {
        return uf;
    }
    /* ±0，直接返回，保留符号 */
    if (e == 0 && m == 0) {
        return uf;
    }

    /* 非规格化数：绝对值 < 0.5，舍入到 0 */
    if (e == 0) {
        return s;
    }

    /* e < 126：绝对值 < 0.5，舍入到 0 */
    if (e < 126) {
        return s;
    }

    /* e == 126：值在 [0.5, 1) 之间 */
    if (e == 126) {
        if (m == 0) {
            /* 正好 0.5，舍入到偶数 0 */
            return s;
        } else {
            /* > 0.5，舍入到 1 */
            return s | (127 << 23);  /* 1.0 的浮点表示：阶码 127，尾数 0 */
        }
    }

    /* e >= 150：数值已经是整数，直接返回 */
    if (e >= 150) {
        return uf;
    }

    /* 127 <= e < 150：有小数部分，需要舍入 */
    int shift = 150 - e;               /* 需要右移的位数，1 到 23 */
    unsigned sig = (1 << 23) | m;      /* 包含隐含 1 的有效数字，24 位 */
    unsigned int_part = sig >> shift;  /* 整数部分 */
    unsigned frac = sig & ((1 << shift) - 1); /* 小数部分 */
    unsigned half = 1 << (shift - 1);  /* 中点值 */

    /* round-to-nearest-even */
    if (frac > half || (frac == half && (int_part & 1))) {
        int_part++;
    }

    /* 如果舍入后为 0（理论上不会发生，但保留） */
    if (int_part == 0) {
        return s;
    }

    /* 将整数 int_part 转换回单精度浮点数 */
    int p = 31;
    while (p >= 0 && !(int_part & (1u << p))) {
        p--;
    }
    unsigned e_new = p + 127;          /* 新的阶码 */
    unsigned m_new;
    if (p <= 23) {
        m_new = (int_part & ((1 << p) - 1)) << (23 - p);
    } else {
        /* 理论上不会发生，但为了安全处理 */
        m_new = (int_part >> (p - 23)) & 0x7FFFFF;
    }
    return s | (e_new << 23) | m_new;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  if (x == 0) return 0;

    unsigned s = x & 0x80000000;   // 符号位
    unsigned u;
    if (x < 0) {
        u = ~x + 1;                // 取绝对值，隐式转换为 unsigned
    } else {
        u = x;                     // 隐式转换为 unsigned
    }

    // 找最高位位置 p
    int p = 31;
    while (p >= 0 && !(u & (1u << p))) {
        p--;
    }

    unsigned e = p + 127;
    unsigned m;

    if (p <= 23) {
        m = (u << (23 - p)) & 0x7FFFFF;
    } else {
        int shift = p - 23;
        unsigned sig = u >> shift;
        unsigned dropped = u & ((1u << shift) - 1);
        unsigned half = 1u << (shift - 1);

        // round-to-nearest-even
        if (dropped > half || (dropped == half && (sig & 1))) {
            sig++;
            if (sig == (1u << 24)) {
                sig >>= 1;
                e++;
            }
        }
        m = sig & 0x7FFFFF;
    }

    return s | (e << 23) | m;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 构造掩码 0x55555555：每个 2 位中的低位为 1 */
  int mask1 = 0x55 | (0x55 << 8);
  mask1 = mask1 | (mask1 << 16);

  /* 构造掩码 0x33333333：每个 4 位中的低 2 位为 1 */
  int mask2 = 0x33 | (0x33 << 8);
  mask2 = mask2 | (mask2 << 16);

  /* 构造掩码 0x0F0F0F0F：每个 8 位中的低 4 位为 1 */
  int mask4 = 0x0F | (0x0F << 8);
  mask4 = mask4 | (mask4 << 16);

  /* 构造掩码 0x00FF00FF：每 16 位中的低 8 位为 1 */
  int mask8 = 0xFF | (0xFF << 16);

  /* 构造掩码 0x0000FFFF：低 16 位为 1 */
  int mask16 = 0xFF | (0xFF << 8);

  /* 分治合并 */
  int y = (x & mask1) + ((x >> 1) & mask1);       // 每 2 位一组计数
  y = (y & mask2) + ((y >> 2) & mask2);           // 每 4 位一组计数
  y = (y & mask4) + ((y >> 4) & mask4);           // 每 8 位一组计数
  y = (y & mask8) + ((y >> 8) & mask8);           // 每 16 位一组计数
  y = (y & mask16) + ((y >> 16) & mask16);        // 合并高低 16 位

  return y;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /* 构造掩码 0x55555555：每 2 位中的低位为 1 */
    int m1 = 0x55 | (0x55 << 8);
    m1 = m1 | (m1 << 16);

    /* 构造掩码 0x33333333：每 4 位中的低 2 位为 1 */
    int m2 = 0x33 | (0x33 << 8);
    m2 = m2 | (m2 << 16);

    /* 构造掩码 0x0F0F0F0F：每 8 位中的低 4 位为 1 */
    int m4 = 0x0F | (0x0F << 8);
    m4 = m4 | (m4 << 16);

    /* 构造掩码 0x00FF00FF：每 16 位中的低 8 位为 1 */
    int m8 = 0xFF | (0xFF << 16);

    /* 构造掩码 0x0000FFFF：低 16 位为 1 */
    int m16 = 0xFF | (0xFF << 8);

    /* 交换相邻的 1 位 */
    x = ((x >> 1) & m1) | ((x & m1) << 1);
    /* 交换相邻的 2 位 */
    x = ((x >> 2) & m2) | ((x & m2) << 2);
    /* 交换相邻的 4 位 */
    x = ((x >> 4) & m4) | ((x & m4) << 4);
    /* 交换相邻的 8 位 */
    x = ((x >> 8) & m8) | ((x & m8) << 8);
    /* 交换相邻的 16 位 */
    x = ((x >> 16) & m16) | ((x & m16) << 16);

    return x;
}
