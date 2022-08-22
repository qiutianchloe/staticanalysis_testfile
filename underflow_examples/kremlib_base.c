// derived from: https://github.com/binsec/rel_bench/blob/main/src/ct/hacl_utility/kremlib_base.h

/* MIT License
 *
 * Copyright (c) 2016-2017 INRIA and Microsoft Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/******************************************************************************/
/* Implementation of machine integers (possibly of 128-bit integers)          */
/******************************************************************************/

typedef unsigned long uint64_t;
typedef long int64_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;


/* static */ /* inline */ uint32_t rotate32_left(uint32_t x, uint32_t n) {
  /*  assert (n<32); */
  return (x << n) | (x >> (32 - n));
}
/* static */ /* inline */ uint32_t rotate32_right(uint32_t x, uint32_t n) {
  /*  assert (n<32); */
  return (x >> n) | (x << (32 - n));
}

/* Constant time comparisons */
/* static */ /* inline */ uint8_t FStar_UInt8_eq_mask(uint8_t x, uint8_t y) {
  x = ~(x ^ y);
  x &= x << 4;
  x &= x << 2;
  x &= x << 1;
  return (int8_t)x >> 7;
}

/* static */ /* inline */ uint8_t FStar_UInt8_gte_mask(uint8_t x, uint8_t y) {
  return ~(uint8_t)(((int32_t)x - y) >> 31);
}

/* static */ /* inline */ uint16_t FStar_UInt16_eq_mask(uint16_t x, uint16_t y) {
  x = ~(x ^ y);
  x &= x << 8;
  x &= x << 4;
  x &= x << 2;
  x &= x << 1;
  return (int16_t)x >> 15;
}

/* static */ /* inline */ uint16_t FStar_UInt16_gte_mask(uint16_t x, uint16_t y) {
  return ~(uint16_t)(((int32_t)x - y) >> 31);
}

/* static */ /* inline */ uint32_t FStar_UInt32_eq_mask(uint32_t x, uint32_t y) {
  x = ~(x ^ y);
  x &= x << 16;
  x &= x << 8;
  x &= x << 4;
  x &= x << 2;
  x &= x << 1;
  return ((int32_t)x) >> 31;
}

/* static */ /* inline */ uint32_t FStar_UInt32_gte_mask(uint32_t x, uint32_t y) {
  return ~((uint32_t)(((int64_t)x - y) >> 63));
}

/* static */ /* inline */ uint64_t FStar_UInt64_eq_mask(uint64_t x, uint64_t y) {
  x = ~(x ^ y);
  x &= x << 32;
  x &= x << 16;
  x &= x << 8;
  x &= x << 4;
  x &= x << 2;
  x &= x << 1;
  return ((int64_t)x) >> 63;
}


// XXX: workaround that we currently cannot parse 64-bit literals
uint64_t UINT64_C(uint32_t high, uint32_t low){
  uint64_t result = 0;
  result |= (((uint64_t)high) << 32);
  result |= (uint64_t)low;
  return result;
}

/* static */ /* inline */ uint64_t FStar_UInt64_gte_mask(uint64_t x, uint64_t y) {
  uint64_t low63 =
    ~((uint64_t)((int64_t)((int64_t)(x & UINT64_C(0x7fffffff,0xffffffff)) -
                           (int64_t)(y & UINT64_C(0x7fffffff,0xffffffff))) >>
                   63));
  uint64_t high_bit =
    ~((uint64_t)((int64_t)((int64_t)(x & UINT64_C(0x80000000,0x00000000)) -
                           (int64_t)(y & UINT64_C(0x80000000,0x00000000))) >>
                   63));
  return low63 & high_bit;
}


