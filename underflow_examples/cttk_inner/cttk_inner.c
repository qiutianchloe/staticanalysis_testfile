// from: https://github.com/pornin/CTTK/blob/master/src/inner.h
// run with -loop 64 to see unfolding of all of these functions


/*
 * Copyright (c) 2018 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
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

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned long uint64_t;
typedef long int64_t;

/* static */ /* inline */ uint32_t
mulu32(uint32_t x, uint32_t y)
{
  _(loop 32)
  int i;
  uint32_t z;

  z = 0;
  i = 0;
  while (i < 32) {
  //for (i = 0; i < 32; i ++) {
    z += x & -(y & 1);
    x <<= 1;
    y >>= 1;
    i ++;
  }
  return z;
}

/* static */ /* inline */ int32_t
muls32(int32_t x, int32_t y)
{
  uint32_t r;

  r = mulu32((uint32_t)x, (uint32_t)y);
  return *(int32_t *)&r;
}

/* static */ /* inline */ uint64_t
mulu32w(uint32_t x, uint32_t y)
{
  int i;
  uint64_t xe; uint64_t z;

  z = 0;
  xe = x;
  i = 0;
  while (i < 32) {
  //for (i = 0; i < 32; i ++) {
    z += xe & -(uint64_t)(y & 1);
    xe <<= 1;
    y >>= 1;
    i ++;
  }
  return z;
}

/* static */ /* inline */ int64_t
muls32w(int32_t x, int32_t y)
{
  uint32_t xu; uint32_t yu; uint32_t xh; uint32_t yh;
  uint64_t z;

  xu = (uint32_t)x;
  yu = (uint32_t)y;
  xh = xu >> 31;
  yh = yu >> 31;
  xu &= 0x7FFFFFFF;
  yu &= 0x7FFFFFFF;
  z = mulu32w(xu, yu);
  z -= ((uint64_t)(xu & -yh) + (uint64_t)(yu & -xh)) << 31;
  z += (uint64_t)(xh & yh) << 62;
  return *(int64_t *)&z;
}

/* static */ /* inline */ uint64_t
mulu64(uint64_t x, uint64_t y)
{
  _(loop 64)
  uint64_t z;
  int i;

  z = 0;
  i = 0;
  while (i < 64) {
  //for (i = 0; i < 64; i ++) {
    z += x & -(y & 1);
    x <<= 1;
    y >>= 1;
    i ++;
  }
  return z;
}

/* static */ /* inline */ int64_t
muls64(int64_t x, int64_t y)
{
  uint64_t r;

  r = mulu64((uint64_t)x, (uint64_t)y);
  return *(int64_t *)&r;
}

/* ==================================================================== */

