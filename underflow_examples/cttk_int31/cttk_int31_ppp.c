// derived from https://github.com/pornin/CTTK/blob/master/src/int31.c

// preprocessed via cc -E

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

#define NULL ((void*)0)
#include "underflow.h"

typedef unsigned int cttk_bool;
typedef unsigned long size_t;
typedef unsigned long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned int * uintptr_t;
typedef int int32_t;
typedef long int64_t;
cttk_bool
cttk_bool_of_u32(uint32_t x)
{
  cttk_bool c;

  c = x;
  return c;
}

cttk_bool
cttk_u32_neq0(uint32_t x)
{
  uint32_t q;

  q = x | -x;
  return cttk_bool_of_u32((q | -q) >> 31);
}
cttk_bool
cttk_not(cttk_bool c)
{
        c ^= (uint32_t)1;
        return c;
}

// from cttk.h
cttk_bool
cttk_u32_eq0(uint32_t x)
{
	return cttk_not(cttk_u32_neq0(x));
}


cttk_bool
cttk_i31_isnan(const uint32_t *x)
{
	return cttk_bool_of_u32(x[0] >> 31);
}


cttk_bool
cttk_or(cttk_bool c1, cttk_bool c2)
{
	c1 |= c2;
	return c1;
}

static inline unsigned
top_index(uint32_t h)
{
 h = (h & 31) - 1;
 return h + (31 & (h >> 5));
}




static inline uint32_t
signext(uint32_t v, unsigned n)
{
 uint32_t hi, lo;

 hi = -(uint32_t)((v >> (n - 1)) & 1) << (n - 1);
 lo = v & ((uint32_t)-1 >> (32 - n));
 return hi | lo;
}


// XXX manual spec without coercions that would break the memory model
void memcpy32(uint32_t *d, uint32_t *s, uint32_t len){
  int i;
  for (i=0; i<len; i++){
    d[i] = s[i];
  }
}
void memset32(uint32_t *p, uint32_t v, uint32_t len){
  int i;
  for (i=0; i<len; i++){
    p[i] = v;
  }
}
void
cttk_i31_init(uint32_t *x, unsigned size)
{
 uint32_t h;

 h = (uint32_t)size + ((uint32_t)size / 31);
 *x = h | 0x80000000;
 memset32(x + 1, 0, ((h + 31) >> 5));
}

void main_init(){
  uint32_t a[9];
  cttk_i31_init(a,8);
}

void
cttk_i31_set_u32(uint32_t *x, uint32_t v)
{
 uint32_t h, size;
 size_t len;

 x[0] &= 0x7FFFFFFF;
 h = x[0];
 len = (h + 31) >> 5;
 size = h - (h >> 5);





 memset32(x + 2, 0, (len - 1));
 x[1] = v & 0x7FFFFFFF;
 if (size >= 32) {
  x[2] = v >> 31;
 }
 if (size <= 32) {
  x[0] |= cttk_u32_neq0(v >> (size - 1)) << 31;
 }
}


void main_set_u32(){
  uint32_t a[9];
  uint32_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_u32(a,v);
}

void
cttk_i31_set_u32_trunc(uint32_t *x, uint32_t v)
{
 uint32_t h, size;
 size_t len;

 x[0] &= 0x7FFFFFFF;
 h = x[0];
 len = (h + 31) >> 5;
 size = h - (h >> 5);
 memset32(x + 1, 0, len);
 if (size > 32) {
  x[1] = v & 0x7FFFFFFF;
  x[2] = v >> 31;
 } else if (size == 32) {
  x[1] = v & 0x7FFFFFFF;
  x[2] = -(v >> 31) >> 1;
 } else {
  x[1] = signext(v, size) & 0x7FFFFFFF;
 }
}

void main_set_u32_trunc(){
  uint32_t a[9];
  uint32_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_u32_trunc(a,v);
}


cttk_bool
cttk_u64_neq0(uint64_t x)
{
	uint64_t q;

	q = x | -x;
	return cttk_bool_of_u32((uint32_t)((q | -q) >> 63));
}

void
cttk_i31_set_u64(uint32_t *x, uint64_t v)
{
 uint32_t h, size;
 size_t len;

 x[0] &= 0x7FFFFFFF;
 h = x[0];
 len = (h + 31) >> 5;
 size = h - (h >> 5);
 memset32(x + 1, 0, len);
 x[1] = (uint32_t)v & 0x7FFFFFFF;
 if (size > 31) {
  x[2] = (uint32_t)(v >> 31) & 0x7FFFFFFF;
 }
 if (size > 62) {
  x[3] = (uint32_t)(v >> 62);
 }
 if (size <= 64) {
  x[0] |= cttk_u64_neq0(v >> (size - 1)) << 31;
 }
}

void main_set_u64(){
  uint32_t a[9];
  uint64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_u64(a,v);
}

void
cttk_i31_set_u64_trunc(uint32_t *x, uint64_t v)
{
 uint32_t h, size;
 size_t len;

 x[0] &= 0x7FFFFFFF;
 h = x[0];
 len = (h + 31) >> 5;
 size = h - (h >> 5);
 memset32(x + 1, 0, len);
 if (size >= 65) {
  x[1] = (uint32_t)v & 0x7FFFFFFF;
  x[2] = (uint32_t)(v >> 31) & 0x7FFFFFFF;
  x[3] = (uint32_t)(v >> 62);
 } else if (size >= 63) {
  x[1] = (uint32_t)v & 0x7FFFFFFF;
  x[2] = (uint32_t)(v >> 31) & 0x7FFFFFFF;
  x[3] = signext((uint32_t)(v >> 62), size - 62) & 0x7FFFFFFF;
 } else if (size >= 32) {
  x[1] = (uint32_t)v & 0x7FFFFFFF;
  x[2] = signext((uint32_t)(v >> 31), size - 31) & 0x7FFFFFFF;
 } else {
  x[1] = signext((uint32_t)v, size) & 0x7FFFFFFF;
 }
}

void main_set_u64_trunc(){
  uint32_t a[9];
  uint64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_u64_trunc(a,v);
}


void
cttk_i31_set_s32(uint32_t *x, int32_t v)
{
 uint32_t h, size;
 size_t u, len;
 uint32_t w;

 x[0] &= 0x7FFFFFFF;
 h = x[0];
 len = (h + 31) >> 5;
 size = h - (h >> 5);
 w = (uint32_t)v;
 x[1] = w & 0x7FFFFFFF;
 if (size >= 32) {
  w = -(w >> 31) >> 1;
  for (u = 1; u < len; u ++) {
   x[u + 1] = w;
  }
 } else {
  uint32_t m;

  m = (uint32_t)-1 << (size - 1);
  w &= m;
  x[0] |= (cttk_u32_neq0(w) & cttk_u32_neq0(w ^ m)) << 31;
 }
}

void main_set_s32(){
  uint32_t a[9];
  int32_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s32(a,v);
}

void
cttk_i31_set_s64(uint32_t *x, int64_t v)
{
 uint32_t h, size;
 size_t u, len;
 uint64_t w;
 x[0] &= 0x7FFFFFFF;
 h = x[0];
 len = (h + 31) >> 5;
 size = h - (h >> 5);
 w = (uint64_t)v;
 x[1] = (uint32_t)w & 0x7FFFFFFF;
 if (size >= 63) {
  uint32_t h;
  x[2] = (uint32_t)(w >> 31) & 0x7FFFFFFF;
  x[3] = signext((uint32_t)(w >> 62), 2) & 0x7FFFFFFF;
  h = -(uint32_t)(w >> 63) >> 1;
  for (u = 3; u < len; u ++) {
   x[u + 1] = h;
  }
 } else if (size >= 32) {
  x[2] = (uint32_t)(w >> 31) & 0x7FFFFFFF;
 }
 if (size < 64) {
  uint64_t m;
  m = (uint64_t)-1 << (size - 1);
  w &= m;
  x[0] |= (cttk_u64_neq0(w) & cttk_u64_neq0(w ^ m)) << 31;
 }
}

void main_set_s64(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
}


void
cttk_i31_set(uint32_t *d, const uint32_t *a)
{
 uint32_t h;
 size_t dlen, alen;
 if (a == d) {
  return;
 }
 h = a[0] & 0x7FFFFFFF;
 alen = (h + 31) >> 5;

 h = d[0] & 0x7FFFFFFF;
 dlen = (h + 31) >> 5;
 d[0] = h | (a[0] & 0x80000000);

 if (dlen > alen) {
  size_t u;
  uint32_t w;

  memcpy32(d + 1, a + 1, alen);
  w = -(a[alen] >> 30) >> 1;
  for (u = alen; u < dlen; u ++) {
   d[1 + u] = w;
  }
 } else {
  size_t u;
  uint32_t w, m;
  memcpy32(d + 1, a + 1, dlen);
  m = -(a[alen] >> 30) >> 1;
  w = (d[dlen] ^ m) & ((uint32_t)-1 << top_index(h));
  for (u = dlen; u < alen; u ++) {
   w |= a[u + 1] ^ m;
  }
  d[0] |= (w | -w) & 0x80000000;
 }
}

// works with the -prune:max_latency 4000 and -timeout 4000 
void main_set(){
  uint32_t a[9];
  int64_t v;
  
  uint32_t b[9];
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  
  cttk_i31_init(b,8); // b needs its length initialised
  cttk_i31_set(b,a);
  cttk_i31_init(b,6); // b needs its length initialised
  cttk_i31_set(b,a);
}

void
cttk_i31_set_trunc(uint32_t *d, const uint32_t *a)
{
 uint32_t h;
 size_t dlen, alen;
 if (a == d) {
  return;
 }
 h = a[0] & 0x7FFFFFFF;
 alen = (h + 31) >> 5;
 h = d[0] & 0x7FFFFFFF;
 dlen = (h + 31) >> 5;
 d[0] = h | (a[0] & 0x80000000);
 if (dlen > alen) {
  size_t u;
  uint32_t w;
  memcpy32(d + 1, a + 1, alen);
  w = -(a[alen] >> 30) >> 1;
  for (u = alen; u < dlen; u ++) {
   d[1 + u] = w;
  }
 } else {
  uint32_t m, sb;
  memcpy32(d + 1, a + 1, dlen);
  m = (uint32_t)1 << top_index(h);
  sb = d[dlen] & m;
  d[dlen] &= m - 1;
  d[dlen] |= -sb & 0x7FFFFFFF;
 }
}

void main_set_trunc(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  
  cttk_i31_init(b,8); // b needs its length initialised
  cttk_i31_set_trunc(b,a);
  cttk_i31_init(b,6); // b needs its length initialised
  cttk_i31_set_trunc(b,a);
}
uint32_t
cttk_i31_to_u32_trunc(const uint32_t *x)
{
 uint32_t r;
 r = x[1];
 if ((x[0] & 0x7FFFFFFF) > 32) {
  r |= x[2] << 31;
 } else {
  r |= (r & 0x40000000) << 1;
 }
 return r & (uint32_t)((x[0] >> 31) - 1);
}

uint32_t main_to_u32_trunc(){
  uint32_t a[9];
  
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);  
  return cttk_i31_to_u32_trunc(a);
}


int32_t main_to_s32_trunc(){
  uint32_t a[9];
  
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);  
  return cttk_i31_to_s32_trunc(a);
}

int32_t
cttk_i31_to_s32_trunc(const uint32_t *x)
{
 uint32_t r;

 r = cttk_i31_to_u32_trunc(x);
 return *(int32_t *)&r;
}

uint64_t
cttk_i31_to_u64_trunc(const uint32_t *x)
{
 uint32_t h;
 uint64_t r;
 h = x[0] & 0x7FFFFFFF;
 r = x[1];
 if (h > 64) {
  r |= (uint64_t)x[2] << 31 | (uint64_t)x[3] << 62;
 } else if (h > 32) {
  r |= (uint64_t)x[2] << 31;
  r |= -(r & ((uint64_t)1 << 61));
 } else {
  r |= -(r & ((uint64_t)1 << 30));
 }
 return r & ((uint64_t)(x[0] >> 31) - 1);
}

int64_t
cttk_i31_to_s64_trunc(const uint32_t *x)
{
 uint64_t r;

 r = cttk_i31_to_u64_trunc(x);
 return *(int64_t *)&r;
}

int64_t main_to_s64_trunc(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);  
  return cttk_i31_to_s64_trunc(a);
}

uint64_t main_to_u64_trunc(){
  uint32_t a[9];
  
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);  
  return cttk_i31_to_u64_trunc(a);
}

// from cttk.h
cttk_bool
cttk_and(cttk_bool c1, cttk_bool c2)
{
	c1 &= c2;
	return c1;
}

// from cttk.h
cttk_bool
cttk_u32_eq(uint32_t x, uint32_t y)
{
	return cttk_u32_eq0(x ^ y);
}

static void
gendec(uint32_t *x, const unsigned char *src, size_t src_len, int be, int sig, int trunc)
{
 uint32_t h, top, top2;
 const unsigned char *buf;
 size_t u, v, len;
 unsigned ssb, ssx, k, hk, extra_bits, extra_bits_len;
 cttk_bool in_range;

 x[0] &= 0x7FFFFFFF;
 h = x[0];
 len = (h + 31) >> 5;
 memset32(x + 1, 0, len);
 if (src_len == 0) {
  if (sig) {
   x[0] |= 0x80000000;
  }
  return;
 }
 buf = src;
 hk = top_index(h);




 if (sig) {
  if (be) {
   ssb = -(unsigned)(buf[0] >> 7) & 0xFF;
  } else {
   ssb = -(unsigned)(buf[src_len - 1] >> 7) & 0xFF;
  }
 } else {
  ssb = 0;
 }






 u = 0;
 k = 0;
 v = 0;






 in_range = 1 /* cttk_true */;
 ssx = 0;





 extra_bits = 0;
 extra_bits_len = 0;

 while (u < len || v < src_len) {
  unsigned b;




  if (v < src_len) {
    b = (be ? (buf[src_len - 1 - v]) : (buf[v]));
  } else {
   b = ssb;
  }
  v ++;

  if (u < len) {
   if (k <= 23) {
    x[1 + u] |= (uint32_t)b << k;
   } else {






    x[1 + u] |= ((uint32_t)b << k) & 0x7FFFFFFF;
    if ((u + 1) < len) {
     x[2 + u] |= (uint32_t)b >> (31 - k);
    } else {
     extra_bits = (uint32_t)b >> (31 - k);
     extra_bits_len = k - 23;
    }
   }

   k += 8;
   if (k >= 31) {
    k -= 31;
    u ++;
    if (u == len) {
     ssx = -(unsigned)((x[len] >> hk) & 1)
      & 0xFF;
    }
   }
  } else {





   in_range = cttk_and(in_range, cttk_u32_eq(b, ssx));
  }
 }
 top = x[len];
 top2 = signext(top, hk + 1) & 0x7FFFFFFF;
 if (trunc) {
  x[len] = top2;
 } else {
  in_range = cttk_and(in_range, cttk_u32_eq(top, top2));
  if (extra_bits_len > 0) {
   in_range = cttk_and(in_range, cttk_u32_eq(extra_bits,
    ssx >> (8 - extra_bits_len)));
  }
  if (!sig) {
   in_range = cttk_and(in_range, cttk_u32_eq0(ssx));
  }
  x[0] |= cttk_not(in_range) << 31;
 }
}




static void
genenc(unsigned char *dst, size_t dst_len, const uint32_t *x, int be)
{
 unsigned char *buf;
 uint32_t h, acc, ssx;
 unsigned mask, acc_len;
 size_t u, len, v;

 h = x[0];
 mask = (h >> 31) - 1;
 h &= 0x7FFFFFFF;
 len = (h + 31) >> 5;

 ssx = -(uint32_t)((x[len] >> top_index(h)) & 1) >> 1;
 acc = x[1];
 acc_len = 31;
 u = 1;
 buf = dst;
 for (v = 0; v < dst_len; v ++) {
  unsigned b;

  if (acc_len >= 8) {
   b = acc & 0xFF;
   acc >>= 8;
   acc_len -= 8;
  } else {
   b = acc;
   if (u < len) {
    acc = x[1 + u];
    u ++;
   } else {
    acc = ssx;
   }
   b |= acc << acc_len;
   acc >>= (8 - acc_len);
   acc_len += 23;
  }
  b &= mask;
  if (be) {
   buf[dst_len - 1 - v] = b;
  } else {
   buf[v] = b;
  }
 }
}

void
cttk_i31_decbe_signed(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 1, 1, 0);
}

// XXX: 0 contracts
void main_decbe_signed(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decbe_signed(a,num,7);
}

void
cttk_i31_decbe_unsigned(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 1, 0, 0);
}

// XXX: 0 contracts
void main_decbe_unsigned(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decbe_unsigned(a,num,7);
}

void
cttk_i31_decbe_signed_trunc(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 1, 1, 1);
}

// XXX: 0 contracts
void main_decbe_signed_trunc(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decbe_signed_trunc(a,num,7);
}

void
cttk_i31_decbe_unsigned_trunc(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 1, 0, 1);
}

// XXX: 0 contracts
void main_decbe_unsigned_trunc(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decbe_unsigned_trunc(a,num,7);
}

void
cttk_i31_decle_signed(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 0, 1, 0);
}


// XXX: 0 contracts
void main_decle_signed(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decle_signed(a,num,7);
}

void
cttk_i31_decle_unsigned(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 0, 0, 0);
}

void main_decle_unsigned(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decle_unsigned(a,num,7);
}

void
cttk_i31_decle_signed_trunc(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 0, 1, 1);
}

// XXX: 0 contracts
void main_decle_signed_trunc(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decle_signed_trunc(a,num,7);
}

void
cttk_i31_decle_unsigned_trunc(uint32_t *x, const unsigned char *src, size_t len)
{
 gendec(x, src, len, 0, 0, 1);
}

void main_decle_unsigned_trunc(){
  unsigned char num[7];
  uint32_t a[9];
  cttk_i31_init(a,8);
  cttk_i31_decle_unsigned_trunc(a,num,7);
}

void
cttk_i31_encbe(unsigned char *dst, size_t len, const uint32_t *x)
{
 genenc(dst, len, x, 1);
}

// XXX: 0 contracts
void main_encbe(){
  unsigned char num[7];
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_encbe(num,7,a);
}

void
cttk_i31_encle(unsigned char *dst, size_t len, const uint32_t *x)
{
 genenc(dst, len, x, 0);
}

void main_encle(){
  unsigned char num[7];
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_encle(num,7,a);
}

static cttk_bool
val_eq0(const uint32_t *x)
{
 uint32_t h, r;
 size_t len, u;

 h = x[0] & 0x7FFFFFFF;
 len = (h + 31) >> 5;
 r = 0;
 for (u = 0; u < len; u ++) {
  r |= x[u + 1];
 }
 return cttk_u32_eq0(r);
}






static cttk_bool
val_lt0(const uint32_t *x)
{
 uint32_t h;
 size_t len;

 h = x[0] & 0x7FFFFFFF;
 len = (h + 31) >> 5;
 return cttk_bool_of_u32((x[len] >> 30) & 1);
}


uint32_t
cttk_u32_bitlength(uint32_t x)
{
  uint32_t xh, b;
  uint32_t r;

  r = 0;

  /*
   * We split x into its high and low halves. If the high half is
   * 0, then the bit length of x is the bit length of the low
   * half. If the high half is not 0, then the bitlength is 16
   * added to the bit length of the high half.
   *
   * To test for equality with 0, we add 0xFFFF: this produces a
   * carry into bit 16, except for 0.
   */
  xh = x >> 16;
  b = (xh + 0xFFFF) >> 16;
  x ^= (x ^ xh) & -b;
  r |= b << 4;

  /*
   * We use the same method to reduce the length of x to 8 bits,
   * then 4 bits, then 2 bits.
   */
  xh = x >> 8;
  b = (xh + 0xFF) >> 8;
  x ^= (x ^ xh) & -b;
  r |= b << 3;
  xh = x >> 4;
  b = (xh + 0x0F) >> 4;
  x ^= (x ^ xh) & -b;
  r |= b << 2;
  xh = x >> 2;
  b = (xh + 0x03) >> 2;
  x ^= (x ^ xh) & -b;
  r |= b << 1;

  /*
   * Now, x fits on two bits: its value is 0, 1, 2 or 3. The
   * possible lengths (to add to the current value of r) are:
   *   x  length
   *   0    0
   *   1    1
   *   2    2
   *   3    2
   *
   * Thus, x is equal to its length, unless it has value 3.
   */
  return r + x - ((x + 1) >> 2);
}

uint32_t
cttk_u32_mux(cttk_bool ctl, uint32_t x, uint32_t y)
{
  return y ^ (-ctl & (x ^ y));
}

static uint32_t
real_bitlength(const uint32_t *x)
{
 uint32_t h, mx, t, g;
 size_t len, u;
 unsigned k;

 h = x[0] & 0x7FFFFFFF;
 len = (h + 31) >> 5;
 k = top_index(h);
 mx = -(uint32_t)((x[len] >> k) & 1) >> 1;

 t = x[1];
 g = 0;
 for (u = 1; u < len; u ++) {
  uint32_t w;
  cttk_bool nz;

  w = x[u + 1] ^ mx;
  nz = cttk_u32_neq0(w);
  t = cttk_u32_mux(nz, w, t);
  g = cttk_u32_mux(nz, (uint32_t)u, g);
 }

 return cttk_u32_bitlength(t) + (g << 5) - g;
}

// from cttk.h
cttk_bool
cttk_u32_gt(uint32_t x, uint32_t y)
{
	/*
	 * If both x < 2^31 and y < 2^31, then y-x will have its high
	 * bit set if x > y, cleared otherwise.
	 *
	 * If either x >= 2^31 or y >= 2^31 (but not both), then the
	 * result is the high bit of x.
	 *
	 * If both x >= 2^31 and y >= 2^31, then we can virtually
	 * subtract 2^31 from both, and we are back to the first
	 * case. Since (y-2^31)-(x-2^31) = y-x, the direct subtraction
	 * is already fine.
	 */
	uint32_t z;

	z = y - x;
	return cttk_bool_of_u32((z ^ ((x ^ y) & (x ^ z))) >> 31);
}
cttk_bool
cttk_u32_lt(uint32_t x, uint32_t y)
{
	return cttk_u32_gt(y, x);
}

uint32_t
cttk_i31_to_u32(const uint32_t *x)
{
 uint32_t r;

 r = cttk_i31_to_u32_trunc(x);
 r &= -cttk_u32_lt(real_bitlength(x), 33);
 r &= val_lt0(x) - 1;
 return r;
}

// needs -prune:max-latency 10000 -timeout 10000 both cranked up
uint32_t main_to_u32(){
  unsigned char num[7];
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_to_u32(a);
}

// needs -prune:max-latency 5000 -timeout 5000 both cranked up
int32_t main_to_s32(){
  unsigned char num[7];
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_to_s32(a);
}

int32_t
cttk_i31_to_s32(const uint32_t *x)
{
 uint32_t r;

 r = cttk_i31_to_u32_trunc(x);
 r &= -cttk_u32_lt(real_bitlength(x), 32);
 return *(int32_t *)&r;
}

uint64_t
cttk_i31_to_u64(const uint32_t *x)
{
 uint64_t r;

 r = cttk_i31_to_u64_trunc(x);
 r &= -(uint64_t)cttk_u32_lt(real_bitlength(x), 65);
 r &= (uint64_t)val_lt0(x) - 1;
 return r;
}

// needs -prune:max-latency 10000 -timeout 10000 both cranked up
uint64_t main_to_u64(){
  unsigned char num[7];
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_to_u64(a);
}

cttk_bool
cttk_u64_gt(uint64_t x, uint64_t y)
{
  /*
   * If both x < 2^63 and y < 2^63, then y-x will have its high
   * bit set if x > y, cleared otherwise.
   *
   * If either x >= 2^63 or y >= 2^63 (but not both), then the
   * result is the high bit of x.
   *
   * If both x >= 2^63 and y >= 2^63, then we can virtually
   * subtract 2^63 from both, and we are back to the first
   * case. Since (y-2^63)-(x-2^63) = y-x, the direct subtraction
   * is already fine.
   */
  uint64_t z;

  z = y - x;
  return cttk_bool_of_u32((uint32_t)((z ^ ((x ^ y) & (x ^ z))) >> 63));
}

cttk_bool
cttk_u64_lt(uint64_t x, uint64_t y)
{
  return cttk_u64_gt(y, x);
}

int64_t
cttk_i31_to_s64(const uint32_t *x)
{
 uint64_t r;

 r = cttk_i31_to_u64_trunc(x);
 r &= -(uint64_t)cttk_u64_lt(real_bitlength(x), 64);
 return *(int64_t *)&r;
}


// needs -prune:max-latency 5000 -timeout 5000 both cranked up
int64_t main_to_s64(){
  unsigned char num[7];
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_to_s64(a);
}

cttk_bool
cttk_i31_eq0(const uint32_t *x)
{
 return cttk_and(val_eq0(x), cttk_not(cttk_i31_isnan(x)));
}

// needs -timeout 2000 -prune:max-latency 2000
cttk_bool main_eq0(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_eq0(a);
}

cttk_bool
cttk_i31_neq0(const uint32_t *x)
{
 return cttk_not(cttk_or(val_eq0(x), cttk_i31_isnan(x)));
}

// needs -timeout 2000 -prune:max-latency 2000
cttk_bool main_neq0(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_neq0(a);
}

cttk_bool
cttk_i31_gt0(const uint32_t *x)
{
 return cttk_not(cttk_or(cttk_or(val_eq0(x), val_lt0(x)),
  cttk_i31_isnan(x)));
}

// needs -timeout 60000 -prune:max-latency 60000 (or at least bigger than 30s)
cttk_bool main_gt0(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_gt0(a);
}

cttk_bool
cttk_i31_lt0(const uint32_t *x)
{
 return cttk_and(val_lt0(x), cttk_not(cttk_i31_isnan(x)));
}

cttk_bool main_lt0(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_lt0(a);
}

cttk_bool
cttk_i31_geq0(const uint32_t *x)
{
 return cttk_not(cttk_or(val_lt0(x), cttk_i31_isnan(x)));
}

cttk_bool main_geq0(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_geq0(a);
}


cttk_bool
cttk_i31_leq0(const uint32_t *x)
{
 return cttk_and(cttk_or(val_eq0(x), val_lt0(x)),
  cttk_not(cttk_i31_isnan(x)));
}


// needs -timeout 60000 -prune:max-latency 60000 (or at least > 30s)
cttk_bool main_leq0(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_leq0(a);
}

static inline cttk_bool
tst_nan2(const uint32_t *x, const uint32_t *y)
{
 return cttk_bool_of_u32((x[0] | y[0]) >> 31);
}

static cttk_bool
val_eq(const uint32_t *x, const uint32_t *y)
{
 size_t u, len;
 uint32_t r;

 len = ((x[0] & 0x7FFFFFFF) + 31) >> 5;
 r = 0;
 for (u = 0; u < len; u ++) {
  r |= x[1 + u] ^ y[1 + u];
 }
 return cttk_u32_eq0(r);
}

static cttk_bool
val_lt(const uint32_t *x, const uint32_t *y)
{
 size_t u, len;
 uint32_t cc;

 len = ((x[0] & 0x7FFFFFFF) + 31) >> 5;
 cc = 0;
 for (u = 0; u < len; u ++) {
  uint32_t wx, wy, wz;

  wx = x[u + 1];
  wy = y[u + 1];
  wz = wx - wy - cc;
  cc = (wz >> 31);
 }
 cc ^= (x[len] ^ y[len]) >> 30;
 return cttk_bool_of_u32(cc);
}






static uint32_t
val_cmp(const uint32_t *x, const uint32_t *y)
{
 size_t u, len;
 uint32_t cc, t;

 len = ((x[0] & 0x7FFFFFFF) + 31) >> 5;
 cc = 0;
 t = 0;
 for (u = 0; u < len; u ++) {
  uint32_t wx, wy, wz;

  wx = x[u + 1];
  wy = y[u + 1];
  wz = wx - wy - cc;
  cc = (wz >> 31);
  t |= wz;
 }




 cc ^= (x[len] ^ y[len]) >> 30;
 return cttk_u32_neq0(t) | -cc;
}

cttk_bool
cttk_i31_eq(const uint32_t *x, const uint32_t *y)
{
 if ((uint32_t)((x[0] ^ y[0]) << 1) != 0) {
  return 0 /* cttk_false */;
 }
 return cttk_and(val_eq(x, y), cttk_not(tst_nan2(x, y)));
}

// needs -timeout 2000 -prune:max-latency 2000 
cttk_bool main_eq(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_init(b,8);
  cttk_i31_set_s64(a,v2);
  return cttk_i31_eq(a,b);
}

// needs -timeout 2000 -prune:max-latency 2000 
cttk_bool main_neq(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_init(b,8);
  cttk_i31_set_s64(a,v2);
  return cttk_i31_eq(a,b);
}

cttk_bool
cttk_i31_neq(const uint32_t *x, const uint32_t *y)
{
 if ((uint32_t)((x[0] ^ y[0]) << 1) != 0) {
  return 0 /* cttk_false */;
 }
 return cttk_not(cttk_or(val_eq(x, y), tst_nan2(x, y)));
}

cttk_bool
cttk_i31_lt(const uint32_t *x, const uint32_t *y)
{
 if ((uint32_t)((x[0] ^ y[0]) << 1) != 0) {
  return 0 /* cttk_false */;
 }
 return cttk_and(val_lt(x, y), cttk_not(tst_nan2(x, y)));
}

// works with -timeout 2000 -prune:max-latency 2000 
cttk_bool main_lt(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_init(b,8);
  cttk_i31_set_s64(a,v2);
  return cttk_i31_lt(a,b);
}

cttk_bool
cttk_i31_leq(const uint32_t *x, const uint32_t *y)
{
 if ((uint32_t)((x[0] ^ y[0]) << 1) != 0) {
  return 0 /* cttk_false */;
 }
 return cttk_not(cttk_or(val_lt(y, x), tst_nan2(x, y)));
}

// works with -timeout 2000 -prune:max-latency 2000 
cttk_bool main_leq(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_init(b,8);
  cttk_i31_set_s64(a,v2);
  return cttk_i31_leq(a,b);
}

cttk_bool
cttk_i31_gt(const uint32_t *x, const uint32_t *y)
{
 if ((uint32_t)((x[0] ^ y[0]) << 1) != 0) {
  return 0 /* cttk_false */;
 }
 return cttk_and(val_lt(y, x), cttk_not(tst_nan2(x, y)));
}

// works with -timeout 2000 -prune:max-latency 2000 
cttk_bool main_gt(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_init(b,8);
  cttk_i31_set_s64(a,v2);
  return cttk_i31_gt(a,b);
}

cttk_bool
cttk_i31_geq(const uint32_t *x, const uint32_t *y)
{
 if ((uint32_t)((x[0] ^ y[0]) << 1) != 0) {
  return 0 /* cttk_false */;
 }
 return cttk_not(cttk_or(val_lt(x, y), tst_nan2(x, y)));
}

// works with -timeout 2000 -prune:max-latency 2000 
cttk_bool main_geq(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_init(b,8);
  cttk_i31_set_s64(a,v2);
  return cttk_i31_geq(a,b);
}

int main_sign(){
  uint32_t a[9];
  int64_t v;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  return cttk_i31_sign(a);
}

int
cttk_i31_sign(const uint32_t *x)
{
 uint32_t w;

 w = (val_eq0(x) ^ (uint32_t)1) | -val_lt0(x);
 w &= (x[0] >> 31) - 1;
 return *(int32_t *)&w;
}


// works with -timeout 2000 -prune:max-latency 2000 
int32_t main_cmp(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_init(b,8);
  cttk_i31_set_s64(a,v2);
  return cttk_i31_cmp(a,b);
}

int32_t
cttk_i31_cmp(const uint32_t *x, const uint32_t *y)
{
 uint32_t w;

 if ((uint32_t)((x[0] ^ y[0]) << 1) != 0) {
  return 0;
 }
 w = val_cmp(x, y) & (uint32_t)(((x[0] | y[0]) >> 31) - 1);
 return *(int32_t *)&w;
}

void
cttk_i31_copy(uint32_t *d, const uint32_t *s)
{
 if (d != s) {
  if ((uint32_t)((d[0] ^ s[0]) << 1) != 0) {
   d[0] |= 0x80000000;
   return;
  }
  memcpy32(d, s, (((s[0] & 0x7FFFFFFF) + 63) >> 5));
 }
}

// insecurity BUG FOUND in cttk_i31_copy() line 1560, col 6
void main_copy(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_copy(b,a);
}

void
cttk_i31_mux(cttk_bool ctl, uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 size_t u, len;

 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 63) >> 5;
 for (u = 0; u < len; u ++) {
  d[u] = cttk_u32_mux(ctl, a[u], b[u]);
 }
}

void
cttk_i31_cond_copy(cttk_bool ctl, uint32_t *d, const uint32_t *s)
{
 cttk_i31_mux(ctl, d, s, d);
}

// insecurity BUG FOUND in cttk_i31_mux() line 1690, col 6
void main_cond_copy(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  cttk_bool ctl;
  cttk_i31_init(a,8);
  cttk_i31_set_s64(a,v);
  cttk_i31_cond_copy(ctl,b,a);
}

void
cttk_i31_swap(uint32_t *a, uint32_t *b)
{
 size_t u, len;

 if (a == b) {
  return;
 }
 if ((uint32_t)((a[0] ^ b[0]) << 1) != 0) {
  a[0] |= 0x80000000;
  b[0] |= 0x80000000;
  return;
 }
 len = ((a[0] & 0x7FFFFFFF) + 63) >> 5;
 for (u = 0; u < len; u ++) {
  uint32_t w;

  w = a[u];
  a[u] = b[u];
  b[u] = w;
 }
}

void main_swap(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_swap(a,b);
}

void
cttk_i31_cond_swap(cttk_bool ctl, uint32_t *a, uint32_t *b)
{
 size_t u, len;

 if (a == b) {
  return;
 }
 if ((uint32_t)((a[0] ^ b[0]) << 1) != 0) {
  a[0] |= 0x80000000;
  b[0] |= 0x80000000;
  return;
 }
 len = ((a[0] & 0x7FFFFFFF) + 63) >> 5;
 for (u = 0; u < len; u ++) {
  uint32_t wa, wb, wt;

  wa = a[u];
  wb = b[u];
  wt = (wa ^ wb) & -ctl;
  a[u] = wa ^ wt;
  b[u] = wb ^ wt;
 }
}

void main_cond_swap(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  cttk_bool ctl;
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);    
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_cond_swap(ctl,a,b);
}

void main_mux(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  uint32_t c[9];
  int64_t v3;  
  cttk_bool ctl;
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);
  cttk_i31_init(c,8);    
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);
  //cttk_i31_set_s64(c,v3); not needed since it's value is overwritten
  cttk_i31_mux(ctl,c,a,b);
}

void
cttk_i31_add(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h, cc, tt;
 size_t len, u;
 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 tt = a[len] ^ b[len];
 cc = 0;
 for (u = 0; u < len; u ++) {
  uint32_t wa, wb, wd;
  wa = a[u + 1];
  wb = b[u + 1];
  wd = wa + wb + cc;
  d[u + 1] = wd & 0x7FFFFFFF;
  cc = wd >> 31;
 }
 d[0] |= (((tt ^ d[len]) >> top_index(h)) ^ cc) << 31;
}

void main_add(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  uint32_t c[9];
  int64_t v3;  
  cttk_bool ctl;
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);
  cttk_i31_init(c,8);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);
  cttk_i31_set_s64(c,v3);    
  cttk_i31_add(c,a,b);
}

void
cttk_i31_add_trunc(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h, cc;
 size_t len, u;
 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 cc = 0;
 for (u = 0; u < len; u ++) {
  uint32_t wa, wb, wd;
  wa = a[u + 1];
  wb = b[u + 1];
  wd = wa + wb + cc;
  d[u + 1] = wd & 0x7FFFFFFF;
  cc = wd >> 31;
 }
 d[len] = signext(d[len], top_index(h) + 1) & 0x7FFFFFFF;
}

void main_add_trunc(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  uint32_t c[9];
  int64_t v3;  
  cttk_bool ctl;
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);
  cttk_i31_init(c,8);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);
  cttk_i31_set_s64(c,v3);    
  cttk_i31_add_trunc(c,a,b);
}

void
cttk_i31_sub(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h, cc, tt;
 size_t len, u;
 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 tt = a[len] ^ b[len];
 cc = 0;
 for (u = 0; u < len; u ++) {
  uint32_t wa, wb, wd;
  wa = a[u + 1];
  wb = b[u + 1];
  wd = wa - wb - cc;
  d[u + 1] = wd & 0x7FFFFFFF;
  cc = wd >> 31;
 }
 d[0] |= (((tt ^ d[len]) >> top_index(h)) ^ cc) << 31;
}

void main_sub(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  uint32_t c[9];
  int64_t v3;  
  cttk_bool ctl;
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);
  cttk_i31_init(c,8);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);
  cttk_i31_sub(c,a,b);
}

void
cttk_i31_sub_trunc(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h, cc;
 size_t len, u;
 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 cc = 0;
 for (u = 0; u < len; u ++) {
  uint32_t wa, wb, wd;
  wa = a[u + 1];
  wb = b[u + 1];
  wd = wa - wb - cc;
  d[u + 1] = wd & 0x7FFFFFFF;
  cc = wd >> 31;
 }
 d[len] = signext(d[len], top_index(h) + 1) & 0x7FFFFFFF;
}


void main_sub_trunc(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  uint32_t c[9];
  int64_t v3;  
  cttk_bool ctl;
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);
  cttk_i31_init(c,8);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);
  cttk_i31_sub_trunc(c,a,b);
}

void
cttk_i31_neg(uint32_t *d, const uint32_t *x)
{
 uint32_t h, cc, tt;
 size_t u, len;
 h = x[0] & 0x7FFFFFFF;
 if ((uint32_t)((h ^ d[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 d[0] = x[0];
 len = (h + 31) >> 5;
 cc = 1;
 tt = x[len];
 for (u = 0; u < len; u ++) {
  uint32_t w;
  w = x[u + 1];
  w = ~w + cc;
  d[u + 1] = w & 0x7FFFFFFF;
  cc = (w >> 31) ^ 1;
 }
 d[0] |= (uint32_t)(((d[len] & tt) >> top_index(h)) & 1) << 31;
}

void main_neg(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);  
  cttk_i31_set_s64(a,v);
  cttk_i31_neg(b,a);
}

void
cttk_i31_neg_trunc(uint32_t *d, const uint32_t *x)
{
 uint32_t h, cc;
 size_t u, len;
 h = x[0] & 0x7FFFFFFF;
 if ((uint32_t)((h ^ d[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 d[0] = x[0];
 len = (h + 31) >> 5;
 cc = 1;
 for (u = 0; u < len; u ++) {
  uint32_t w;
  w = x[u + 1];
  w = ~w + cc;
  d[u + 1] = w & 0x7FFFFFFF;
  cc = (w >> 31) ^ 1;
 }
 d[len] = signext(d[len], top_index(h) + 1) & 0x7FFFFFFF;
}

void main_neg_trunc(){
  uint32_t a[9];
  int64_t v;
  uint32_t b[9];
  int64_t v2;  
  cttk_i31_init(a,8);
  cttk_i31_init(b,8);  
  cttk_i31_set_s64(a,v);
  cttk_i31_neg_trunc(b,a);
}

uint64_t
mulu32w(uint32_t x, uint32_t y)
{
  int i;
  uint64_t xe, z;
  z = 0;
  xe = x;
  for (i = 0; i < 32; i ++) {
    z += xe & -(uint64_t)(y & 1);
    xe <<= 1;
    y >>= 1;
  }
  return z;
}

static cttk_bool
genmul_separate(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h, ssa, ssb, ssd;
 size_t u, v, len;
 uint64_t cc;
 cttk_bool only0, only1, opz;

 h = d[0] & 0x7FFFFFFF;
 len = (h + 31) >> 5;
 ssa = -(uint32_t)(a[len] >> 30) >> 1;
 ssb = -(uint32_t)(b[len] >> 30) >> 1;
 only0 = 1 /* cttk_true */;
 only1 = 1 /* cttk_true */;
 opz = cttk_or(cttk_i31_eq0(a), cttk_i31_eq0(b));

 cc = 0;
 for (u = 0; u < (len << 1); u ++) {
  uint32_t wd;
  uint64_t zd;

  zd = cc;
  cc = 0;
  for (v = 0; v <= u; v ++) {
   uint32_t wa, wb;
   uint64_t zr;

   wa = v < len ? a[1 + v] : ssa;
   wb = (v + len) > u ? b[1 + u - v] : ssb;
   zr = mulu32w(wa, wb);
   zd += zr & 0x7FFFFFFF;
   cc += zr >> 31;
  }
  cc += zd >> 31;
  wd = (uint32_t)zd & 0x7FFFFFFF;
  if (u < len) {
   d[1 + u] = wd;
  } else {
   only0 = cttk_and(only0, cttk_u32_eq0(wd));
   only1 = cttk_and(only1, cttk_u32_eq0(wd ^ 0x7FFFFFFF));
  }
 }
 ssd = ssa ^ ssb;
 ssd &= (uint32_t)(opz - 1);
 return cttk_and(
  cttk_bool_of_u32(cttk_u32_mux(
   cttk_bool_of_u32(ssd & 1), only1, only0)),
  cttk_u32_eq0((d[len] ^ ssd) >> top_index(h)));
}
static cttk_bool
genmul_stack(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t t[9];  // 36 / 4
 uint32_t h;
 size_t len;
 cttk_bool r;

 h = d[0] & 0x7FFFFFFF;
 t[0] = h;
 len = (h + 31) >> 5;
 memset32(t + 1, 0, len);
 r = genmul_separate(t, a, b);
 memcpy32(d + 1, t + 1, len);
 return r;
}

static cttk_bool
genmul(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 size_t blen;

 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return 0 /* cttk_false */;
 }
 d[0] = a[0] | b[0];

 if (d != a && d != b) {
  return genmul_separate(d, a, b);
 }
 blen = ((h + 63) >> 5) * 4;
 if (blen <= 36) {
  return genmul_stack(d, a, b);
 }

 {
  uint32_t *t;

  t = malloc(blen);
  if (t != NULL) {
   cttk_bool r;
   size_t len;

   t[0] = h;
   len = (h + 31) >> 5;
   memset32(t + 1, 0, len);
   r = genmul_separate(t, a, b);
   memcpy32(d + 1, t + 1, len);
   free(t);
   return r;
  }
 }

 d[0] |= 0x80000000;
 return 0 /* cttk_false */;
}

void
cttk_i31_mul(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 cttk_bool r;

 r = genmul(d, a, b);
 d[0] |= (r ^ 1) << 31;
}

// OK (58 contracts discovered, took 17 hours, 15 minutes, 13 seconds)
void main_mul(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;  
  uint32_t c[4];
  cttk_i31_init(a,3);
  cttk_i31_init(b,3);  
  cttk_i31_init(c,3);
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_mul(c,a,b);
}

void
cttk_i31_mul_trunc(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 size_t len;

 genmul(d, a, b);
 h = d[0] & 0x7FFFFFFF;
 len = (h + 31) >> 5;
 d[len] = signext(d[len], top_index(h) + 1) & 0x7FFFFFFF;
}

// OK (58 ok contracts found). Took 17 hours, 38 minutes
void main_mul_trunc(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;  
  uint32_t c[4];
  cttk_i31_init(a,3);
  cttk_i31_init(b,3);  
  cttk_i31_init(c,3);
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_mul_trunc(c,a,b);
}

static cttk_bool
genlsh(uint32_t *d, const uint32_t *a, uint32_t nd, unsigned nm, cttk_bool ctl)
{
 uint32_t n, h, hk, bl, ssa, tt;
 size_t len, u;
 cttk_bool r;

 d[0] = a[0];
 h = d[0] & 0x7FFFFFFF;
 len = (h + 31) >> 5;
 bl = h - (h >> 5);
 n = 31 * nd + nm;
 ssa = -(a[len] >> 30) & 0x7FFFFFFF;






 if (n >= bl) {
  r = 1 /* cttk_true */;
  for (u = 0; u < len; u ++) {
   uint32_t wa;

   wa = a[1 + u];
   r = cttk_and(r, cttk_u32_eq0(wa));
   d[1 + u] = wa & (uint32_t)(ctl - 1);
  }
  return cttk_or(r, cttk_not(ctl));
 }
 r = 1 /* cttk_true */;
 for (u = len; u > len - nd; u --) {
  r = cttk_and(r, cttk_u32_eq(ssa, a[u]));
 }
 if (nm == 0) {
  for (u = len; u > nd; u --) {
   d[u] = cttk_u32_mux(ctl, a[u - nd], a[u]);
  }
 } else {
  r = cttk_and(r,
   cttk_u32_eq0((a[len - nd] ^ ssa) >> (31 - nm)));
  for (u = len; u > nd; u --) {
   uint32_t wa, wd;

   wa = a[u - nd];
   wd = (wa << nm) & 0x7FFFFFFF;
   if ((u - nd) > 1) {
    wd |= a[u - nd - 1] >> (31 - nm);
   }
   d[u] = cttk_u32_mux(ctl, wd, a[u]);
  }
 }
 for (u = nd; u > 0; u --) {
  d[u] = a[u] & (ctl - 1);
 }
 hk = top_index(h);
 tt = signext(d[len], hk + 1) & 0x7FFFFFFF;
 r = cttk_and(r, cttk_u32_eq(d[len], tt));
 d[len] = tt;
 r = cttk_and(r, cttk_u32_eq0((tt ^ ssa) >> hk));
 return cttk_or(r, cttk_not(ctl));
}

static void
genrsh(uint32_t *d, const uint32_t *a, uint32_t nd, unsigned nm, cttk_bool ctl)
{
 uint32_t h, ssa, n, bl;
 size_t u, len;

 d[0] = a[0];
 h = d[0] & 0x7FFFFFFF;
 len = (h + 31) >> 5;
 bl = h - (h >> 5);
 n = 31 * nd + nm;
 ssa = -(a[len] >> 30) & 0x7FFFFFFF;
 if ((n + 1) >= bl) {
  for (u = 0; u < len; u ++) {
   d[1 + u] = cttk_u32_mux(ctl, ssa, a[1 + u]);
  }
  return;
 }
 if (nm == 0) {
  for (u = 0; u < (len - nd); u ++) {
   d[1 + u] = cttk_u32_mux(ctl, a[1 + u + nd], a[1 + u]);
  }
 } else {
  for (u = 0; u < (len - nd - 1); u ++) {
   uint32_t wa;

   wa = ((a[1 + u + nd] >> nm)
    | (a[2 + u + nd] << (31 - nm))) & 0x7FFFFFFF;
   d[1 + u] = cttk_u32_mux(ctl, wa, a[1 + u]);
  }
  d[len - nd] = cttk_u32_mux(ctl,
   ((a[len] >> nm) | (ssa << (31 - nm))) & 0x7FFFFFFF,
   a[len - nd]);
 }
 for (u = len - nd; u < len; u ++) {
  d[1 + u] = cttk_u32_mux(ctl, ssa, a[1 + u]);
 }
}



/* XXX don't support globals -- FIXME by using a function with a spec instead
static const uint32_t p2m31[] = {
 ((uint32_t)1 << 0) / 31, ((uint32_t)1 << 0) % 31,
 ((uint32_t)1 << 1) / 31, ((uint32_t)1 << 1) % 31,
 ((uint32_t)1 << 2) / 31, ((uint32_t)1 << 2) % 31,
 ((uint32_t)1 << 3) / 31, ((uint32_t)1 << 3) % 31,
 ((uint32_t)1 << 4) / 31, ((uint32_t)1 << 4) % 31,
 ((uint32_t)1 << 5) / 31, ((uint32_t)1 << 5) % 31,
 ((uint32_t)1 << 6) / 31, ((uint32_t)1 << 6) % 31,
 ((uint32_t)1 << 7) / 31, ((uint32_t)1 << 7) % 31,
 ((uint32_t)1 << 8) / 31, ((uint32_t)1 << 8) % 31,
 ((uint32_t)1 << 9) / 31, ((uint32_t)1 << 9) % 31,
 ((uint32_t)1 << 10) / 31, ((uint32_t)1 << 10) % 31,
 ((uint32_t)1 << 11) / 31, ((uint32_t)1 << 11) % 31,
 ((uint32_t)1 << 12) / 31, ((uint32_t)1 << 12) % 31,
 ((uint32_t)1 << 13) / 31, ((uint32_t)1 << 13) % 31,
 ((uint32_t)1 << 14) / 31, ((uint32_t)1 << 14) % 31,
 ((uint32_t)1 << 15) / 31, ((uint32_t)1 << 15) % 31,
 ((uint32_t)1 << 16) / 31, ((uint32_t)1 << 16) % 31,
 ((uint32_t)1 << 17) / 31, ((uint32_t)1 << 17) % 31,
 ((uint32_t)1 << 18) / 31, ((uint32_t)1 << 18) % 31,
 ((uint32_t)1 << 19) / 31, ((uint32_t)1 << 19) % 31,
 ((uint32_t)1 << 20) / 31, ((uint32_t)1 << 20) % 31,
 ((uint32_t)1 << 21) / 31, ((uint32_t)1 << 21) % 31,
 ((uint32_t)1 << 22) / 31, ((uint32_t)1 << 22) % 31,
 ((uint32_t)1 << 23) / 31, ((uint32_t)1 << 23) % 31,
 ((uint32_t)1 << 24) / 31, ((uint32_t)1 << 24) % 31,
 ((uint32_t)1 << 25) / 31, ((uint32_t)1 << 25) % 31,
 ((uint32_t)1 << 26) / 31, ((uint32_t)1 << 26) % 31,
 ((uint32_t)1 << 27) / 31, ((uint32_t)1 << 27) % 31,
 ((uint32_t)1 << 28) / 31, ((uint32_t)1 << 28) % 31,
 ((uint32_t)1 << 29) / 31, ((uint32_t)1 << 29) % 31,
 ((uint32_t)1 << 30) / 31, ((uint32_t)1 << 30) % 31,
 ((uint32_t)1 << 31) / 31, ((uint32_t)1 << 31) % 31,
};
*/

uint32_t get_low();
_(presumes true covers result :: low)

void
cttk_i31_lsh(uint32_t *d, const uint32_t *a, uint32_t n)
{
 cttk_bool r;

 if (((d[0] ^ a[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 r = genlsh(d, a, n / 31, n % 31, 1 /* cttk_true */);
 d[0] |= (r ^ 1) << 31;
}

// OK
void main_lsh(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  uint32_t n = get_low(); // shift amount must be low
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_lsh(b,a,n);
}

/* XXX no p2m31 at present
void
cttk_i31_lsh_prot(uint32_t *d, const uint32_t *a, uint32_t n)
{
 int i;

 if (((d[0] ^ a[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 for (i = 0; i < 32; i ++) {
  cttk_bool r;

  r = genlsh(d, a, p2m31[i << 1], p2m31[(i << 1) + 1],
   cttk_u32_neq0(n & ((uint32_t)1 << i)));
  d[0] |= (r ^ 1) << 31;
  a = d;
 }
}
*/
void
cttk_i31_lsh_trunc(uint32_t *d, const uint32_t *a, uint32_t n)
{
 if (((d[0] ^ a[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 genlsh(d, a, n / 31, n % 31, 1 /* cttk_true */);
}

// OK
void main_lsh_trunc(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  uint32_t n = get_low(); // shift amount must be low
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_lsh_trunc(b,a,n);
}

/* no p2m31 at present
void
cttk_i31_lsh_trunc_prot(uint32_t *d, const uint32_t *a, uint32_t n)
{
 int i;

 if (((d[0] ^ a[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 for (i = 0; i < 32; i ++) {
  genlsh(d, a, p2m31[i << 1], p2m31[(i << 1) + 1],
   cttk_u32_neq0(n & ((uint32_t)1 << i)));
  a = d;
 }
}
*/


void
cttk_i31_rsh(uint32_t *d, const uint32_t *a, uint32_t n)
{
 if (((d[0] ^ a[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 genrsh(d, a, n / 31, n % 31, 1 /* cttk_true */);
}

// memory BUG detected WTF on line 2319, col 8
void main_rsh(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  uint32_t n = get_low(); // shift amount must be low
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_rsh(b,a,n);
}

/* no p2m31 at present
void
cttk_i31_rsh_prot(uint32_t *d, const uint32_t *a, uint32_t n)
{
 int i;

 if (((d[0] ^ a[0]) << 1) != 0) {
  d[0] |= 0x80000000;
  return;
 }
 for (i = 0; i < 32; i ++) {
  genrsh(d, a, p2m31[i << 1], p2m31[(i << 1) + 1],
   cttk_u32_neq0(n & ((uint32_t)1 << i)));
  a = d;
 }
}
*/
static void
gendiv_inner(uint32_t *q, uint32_t *r, const uint32_t *a,
 const uint32_t *b, uint32_t *t1, uint32_t *t2, int mod)
{
 uint32_t h, n, hk, sa, sb;
 size_t ud, len, u;
 unsigned um;
 cttk_bool a_isnan, a_isminv, b_isnan, b_isminv, b_iszero, b_ismone;
 cttk_bool both_nan, half_nan;

 h = b[0] & 0x7FFFFFFF;
 hk = top_index(h);
 n = h - (h >> 5);
 ud = h >> 5;
 um = h & 31;
 len = (h + 31) >> 5;
 a_isnan = cttk_i31_isnan(a);
 b_isnan = cttk_i31_isnan(b);
 a_isminv = 1 /* cttk_true */;
 b_isminv = 1 /* cttk_true */;
 b_iszero = 1 /* cttk_true */;
 b_ismone = 1 /* cttk_true */;
 for (u = 0; (u + 1) < len; u ++) {
  a_isminv = cttk_and(a_isminv, cttk_u32_eq0(a[1 + u]));
  b_isminv = cttk_and(b_isminv, cttk_u32_eq0(b[1 + u]));
  b_iszero = cttk_and(b_iszero, cttk_u32_eq0(b[1 + u]));
  b_ismone = cttk_and(b_iszero,
   cttk_u32_eq(b[1 + u], 0x7FFFFFFF));
 }
 a_isminv = cttk_and(a_isminv,
  cttk_u32_eq(a[len], ((uint32_t)-1 << hk) & 0x7FFFFFFF));
 b_isminv = cttk_and(b_isminv,
  cttk_u32_eq(b[len], ((uint32_t)-1 << hk) & 0x7FFFFFFF));
 b_iszero = cttk_and(b_iszero, cttk_u32_eq0(b[len]));
 b_ismone = cttk_and(b_ismone, cttk_u32_eq(b[len], 0x7FFFFFFF));




 sa = a[len] >> 30;
 sb = b[len] >> 30;




 cttk_i31_neg(t2, b);
 cttk_i31_cond_copy(cttk_u32_eq0(sb), t2, b);





 cttk_i31_add(t1, a, t2);
 cttk_i31_cond_copy(cttk_not(a_isminv), t1, a);
 cttk_i31_neg(r, t1);
 cttk_i31_cond_copy(cttk_not(cttk_bool_of_u32(t1[len] >> 30)), r, t1);
 b = t2;
 if (q != NULL) {
  q[0] &= 0x7FFFFFFF;
  memset32(q + 1, 0, ((h + 31) >> 5));
 }
 while (n -- > 0) {
  cttk_bool e;
  cttk_i31_lsh(t1, b, n);
  e = cttk_i31_leq(t1, r);
  cttk_i31_sub(t1, r, t1);
  cttk_i31_cond_copy(e, r, t1);
  if (q != NULL) {
   if (um == 0) {
    um = 30;
    ud --;
   } else {
    um --;
   }
   q[1 + ud] |= e << um;
  }
 }




 if (q != NULL) {
  int32_t p;





  cttk_i31_set_u32_trunc(t1, 0);
  cttk_i31_cond_copy(b_isminv, q, t1);





  cttk_i31_neg(t1, q);
  cttk_i31_cond_copy(cttk_bool_of_u32(sa ^ sb), q, t1);
  p = cttk_bool_to_int(a_isminv);
  cttk_i31_set_s32(t1,
   cttk_s32_mux(cttk_bool_of_u32(sa ^ sb), -p, p));
  cttk_i31_add(q, q, t1);
 }
 cttk_i31_neg(t1, r);
 cttk_i31_cond_copy(cttk_bool_of_u32(sa), r, t1);
 cttk_i31_set_u32_trunc(t1, 0);
 if (q != NULL) {
  cttk_i31_cond_copy(
   cttk_and(b_isminv, cttk_not(a_isminv)), q, t1);
 }
 cttk_i31_cond_copy(cttk_and(b_isminv, a_isminv), r, t1);
 if (q != NULL) {
  cttk_i31_set_u32(t1, 1);
  cttk_i31_cond_copy(cttk_and(b_isminv, a_isminv), q, t1);
 }




 both_nan = cttk_or(cttk_or(a_isnan, b_isnan), b_iszero);
 half_nan = cttk_and(a_isminv, b_ismone);
 if (q != NULL) {
  q[0] |= cttk_or(both_nan, half_nan) << 31;
 }
 r[0] |= both_nan << 31;
 cttk_i31_set_u32_trunc(t1, 0);
 cttk_i31_cond_copy(half_nan, r, t1);
 if (mod) {
  uint32_t sr;

  sr = r[len] >> 30;
  cttk_i31_add(t1, r, b);
  cttk_i31_cond_copy(cttk_and(cttk_bool_of_u32(sr),
   cttk_not(b_isminv)), r, t1);





  r[len] ^= ((-(sr & b_isminv) << hk) & 0x7FFFFFFF);
 }
}

static void
gendiv_stack3(uint32_t *q, const uint32_t *a, const uint32_t *b, int mod)
{
 uint32_t tr[3] = {(uint32_t)0}; // 36 / (3 * 4)
 uint32_t t1[3] = {(uint32_t)0};
 uint32_t t2[3] = {(uint32_t)0};

 /*
 memset32(tr, 0, 3);  
 memset32(t1, 0, 3);
 memset32(t2, 0, 3);
 */
 tr[0] = t1[0] = t2[0] = a[0];
 gendiv_inner(q, tr, a, b, t1, t2, mod);
}

static void
gendiv_stack2(uint32_t *q, uint32_t *r,
 const uint32_t *a, const uint32_t *b, int mod)
{
 uint32_t t1[3] = {(uint32_t)0};  // 36 / (3 * 4)
 uint32_t t2[3] = {(uint32_t)0};

 //memset32(t1, 0, 3); 
 //memset32(t2, 0, 3);
 t1[0] = t2[0] = a[0];
 gendiv_inner(q, r, a, b, t1, t2, mod);
}
static void
gendiv(uint32_t *q, uint32_t *r, const uint32_t *a, const uint32_t *b, int mod)
{
 uint32_t h;
 size_t wlen;
 h = a[0] & 0x7FFFFFFF;
 wlen = (h + 63) >> 5;
 if (r == NULL) {
  if (wlen <= (36 / (3 * 4))) {
   gendiv_stack3(q, a, b, mod);
   return;
  }

  {
    uint32_t *tr; uint32_t *t1; uint32_t *t2;

   tr = malloc(wlen * 4);
   t1 = malloc(wlen * 4);
   t2 = malloc(wlen * 4);
   if (tr != NULL && t1 != NULL && t2 != NULL) {
    gendiv_inner(q, tr, a, b, t1, t2, mod);
    free(tr);
    free(t1);
    free(t2);
    return;
   }
   if (tr != NULL) {
    free(tr);
   }
   if (t1 != NULL) {
    free(t1);
   }
   if (t2 != NULL) {
    free(t2);
   }
  }

 } else {
  if (wlen <= (36 / (2 * 4))) {
   gendiv_stack2(q, r, a, b, mod);
   return;
  }

  {
   uint32_t *t1; uint32_t *t2;

   t1 = malloc(wlen * 4);
   t2 = malloc(wlen * 4);
   if (t1 != NULL && t2 != NULL) {
    gendiv_inner(q, r, a, b, t1, t2, mod);
    free(t1);
    free(t2);
    return;
   }
   if (t1 != NULL) {
    free(t1);
   }
   if (t2 != NULL) {
    free(t2);
   }
  }

 }




 if (q != NULL) {
  q[0] |= 0x80000000;
 }
 if (r != NULL) {
  r[0] |= 0x80000000;
 }
}

void
cttk_i31_divrem(uint32_t *q, uint32_t *r, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 h = a[0] & 0x7FFFFFFF;
 if (h != (b[0] & 0x7FFFFFFF)) {
  if (q != NULL) {
   q[0] |= 0x80000000;
  }
  if (r != NULL) {
   r[0] |= 0x80000000;
  }
  return;
 }
 if (q != NULL && h != (q[0] & 0x7FFFFFFF)) {
  q[0] |= 0x80000000;
  q = NULL;
 }
 if (r != NULL && h != (r[0] & 0x7FFFFFFF)) {
  r[0] |= 0x80000000;
  r = NULL;
 }
 if (q == NULL && r == NULL) {
  return;
 }
 if (q == r) {
  q[0] |= 0x80000000;
  r[0] |= 0x80000000;
  return;
 }
 gendiv(q, r, a, b, 0);
}

// XXX with 10 minute solver timeout and latency we get 0 contracts
void main_divrem(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;
  uint32_t r[4];
  uint32_t q[4];      
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_init(q,60);
  cttk_i31_init(r,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_divrem(q,r,a,b);
}

void
cttk_i31_mod(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;

 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 gendiv(NULL, d, a, b, 1);
}

void main_mod(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;
  uint32_t r[4];
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_init(r,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_mod(r,a,b);
}

void
cttk_i31_and(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 size_t len, u;

 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 for (u = 1; u <= len; u ++) {
  d[u] = a[u] & b[u];
 }
}


// OK
void main_and(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;
  uint32_t r[4];
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_init(r,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_and(r,a,b);
}

void
cttk_i31_or(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 size_t len, u;
 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 for (u = 1; u <= len; u ++) {
  d[u] = a[u] | b[u];
 }
}

// OK
void main_or(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;
  uint32_t r[4];
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_init(r,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_or(r,a,b);
}

void
cttk_i31_xor(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 size_t len, u;
 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 for (u = 1; u <= len; u ++) {
  d[u] = a[u] ^ b[u];
 }
}


// OK
void main_xor(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;
  uint32_t r[4];
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_init(r,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_xor(r,a,b);
}

void
cttk_i31_eqv(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
 uint32_t h;
 size_t len, u;
 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF) || h != (b[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0] | b[0];
 for (u = 1; u <= len; u ++) {
  d[u] = a[u] ^ b[u] ^ 0x7FFFFFFF;
 }
}

// OK
void main_eqv(){
  uint32_t a[4];
  int64_t v;
  uint32_t b[4];
  int64_t v2;
  uint32_t r[4];
  cttk_i31_init(a,60);
  cttk_i31_init(b,60);  
  cttk_i31_init(r,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_set_s64(b,v2);  
  cttk_i31_eqv(r,a,b);
}

void
cttk_i31_not(uint32_t *d, const uint32_t *a)
{
 uint32_t h;
 size_t len, u;

 h = d[0] & 0x7FFFFFFF;
 if (h != (a[0] & 0x7FFFFFFF)) {
  d[0] |= 0x80000000;
  return;
 }
 len = (h + 31) >> 5;
 d[0] = a[0];
 for (u = 1; u <= len; u ++) {
  d[u] = a[u] ^ 0x7FFFFFFF;
 }
}

// OK
void main_not(){
  uint32_t a[4];
  int64_t v;
  uint32_t r[4];
  cttk_i31_init(a,60);
  cttk_i31_init(r,60);  
  cttk_i31_set_s64(a,v);
  cttk_i31_not(r,a);
}
