// derived from: https://github.com/binsec/rel_bench/blob/main/src/ct/hacl_utility/Hacl_Policies.c
#define NULL ((void*)0)
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

typedef char int8_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

static inline uint8_t FStar_UInt8_eq_mask(uint8_t x, uint8_t y) {
  x = ~(x ^ y);
  x &= x << 4;
  x &= x << 2;
  x &= x << 1;
//Test1: Work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
  return (int8_t)x >> 7;
}

uint8_t Hacl_Policies_cmp_bytes_(uint8_t *b1, uint8_t *b2, uint32_t len, uint8_t *tmp)
{
  uint32_t i;
  for (i = (uint32_t)0U; i < len; i = i + (uint32_t)1U)
  {
    uint8_t bi1 = b1[i];
    uint8_t bi2 = b2[i];
    uint8_t z0 = tmp[0U];
    tmp[0U] = FStar_UInt8_eq_mask(bi1, bi2) & z0;
//Test2: Work
    // int *p = NULL;  // x is a null pointer
    // int blah = *p; 
  }
//Test3: Not Work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
  return tmp[0U];
}

uint8_t Hacl_Policies_cmp_bytes(uint8_t *b1, uint8_t *b2, uint32_t len)
{
  uint8_t tmp[1U];
  tmp[0U] = (uint8_t)255U;
  uint8_t z = Hacl_Policies_cmp_bytes_(b1, b2, len, tmp);
  //Test4: Work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
  return ~z;
}

void main(){
  uint8_t buffer1[16];
  uint8_t buffer2[16];
  uint8_t res = Hacl_Policies_cmp_bytes(buffer1,buffer2,16);
//Test5: Work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
}
