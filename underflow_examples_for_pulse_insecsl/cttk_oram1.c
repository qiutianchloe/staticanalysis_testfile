// adapted from https://github.com/pornin/CTTK/blob/master/src/oram1.c

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

typedef unsigned int cttk_bool;
typedef unsigned long size_t;
typedef unsigned long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned int * uintptr_t;
typedef int int32_t;

/* see cttk.h */
void
cttk_cond_copy(cttk_bool ctl, unsigned char *dst, const unsigned char *src, size_t len)
{
	/*
	 * TODO: make optimised versions for special cases:
	 *
	 *  - We can copy by full words, depending on alignment (and
	 *    architecture tolerance for unaligned accesses), even in
	 *    case of overlap (it suffices to do the copy in the
	 *    appropriate direction).
	 *
	 *  - We may use SSE2, AVX2, or similar vector operands on
	 *    platforms that support them.
	 *
	 * Code below is the basic, portable variant. It relies on the
	 * idea that if source and destination overlap, then converting
	 * the pointers to integers should preserve ordering.
	 */
	unsigned char *bdst;
	const unsigned char *bsrc;
	size_t u;

	/*
	 * In order to perform a constant-time copy, we need to read the
	 * current contents of the destination buffer, which may be, from
	 * the point of view of the C compiler, uninitialised. Note that
	 * reading uninitialised values of a character type is actually
	 * supported by the C standard (values are unspecified, but this
	 * shall incur no trap representation, and therefore no undefined
	 * behaviour).
	 */
	bdst = dst;
	bsrc = src;
	if ((uintptr_t)dst <= (uintptr_t)src) {
		u = 0;
		while (u < len) {
			bdst[u] ^= (bsrc[u] ^ bdst[u]) & -ctl;
			u ++;
		}
	} else {
		u = len;
		while (u > 0) {
			u --;
			bdst[u] ^= (bsrc[u] ^ bdst[u]) & -ctl;
		}
	}
}

/* see cttk.h */
void
cttk_cond_swap(cttk_bool ctl, unsigned char *a, unsigned char *b, size_t len)
{
	/*
	 * TODO: make optimised versions for special cases:
	 *
	 *  - We can copy by full words, depending on alignment (and
	 *    architecture tolerance for unaligned accesses), even in
	 *    case of overlap (it suffices to do the copy in the
	 *    appropriate direction).
	 *
	 *  - We may use SSE2, AVX2, or similar vector operands on
	 *    platforms that support them.
	 *
	 * Code below is the basic, portable variant.
	 */
  unsigned char *za;
  unsigned char *zb;
	size_t u;

	za = a;
	zb = b;

	for (u = 0; u < len; u ++) {
		uint32_t x;

		x = ((za[u]) ^ (zb[u])) & (-ctl);
		za[u] ^= x;
		zb[u] ^= x;
	}
}

// manual implementation to give it a spec
void memset(unsigned char *d, int c, size_t len){
  size_t i;
  for (i=0;i<len;i++){
    *d = (unsigned char)c;
    d++;
  }
}

cttk_bool
cttk_bool_of_u32(uint32_t x)
{
        cttk_bool c;

        c = x;
        return c;
}

cttk_bool
cttk_u64_neq0(uint64_t x)
{
        uint64_t q;

        q = x | -x;
        return cttk_bool_of_u32((uint32_t)((q | -q) >> 63));
}

cttk_bool
cttk_not(cttk_bool c)
{
        c ^= (uint32_t)1;
        return c;
}

cttk_bool
cttk_u64_eq0(uint64_t x)
{
        return cttk_not(cttk_u64_neq0(x));
}

cttk_bool
cttk_u64_eq(uint64_t x, uint64_t y)
{
        return cttk_u64_eq0(x ^ y);
}

/* see cttk.h */
void
cttk_array_read(unsigned char *d,
	const unsigned char *a, size_t elt_len, size_t num_len, size_t index)
{
	size_t u;
	const unsigned char *b;

	memset(d, 0, elt_len);
	for (u = 0, b = a; u < num_len; u ++, b += elt_len) {
		cttk_cond_copy(cttk_u64_eq(u, index), d, b, elt_len);
	}
}

/* see cttk.h */
void
cttk_array_write(unsigned char *a, size_t elt_len, size_t num_len,
	size_t index, const unsigned char *s)
{
	size_t u;
	unsigned char *b;

	for (u = 0, b = a; u < num_len; u ++, b += elt_len) {
		cttk_cond_copy(cttk_u64_eq(u, index), b, s, elt_len);
	}
}

// from cttk.h


cttk_bool
cttk_u32_neq0(uint32_t x)
{
        uint32_t q;

        q = x | -x;
        return cttk_bool_of_u32((q | -q) >> 31);
}


cttk_bool
cttk_u32_eq0(uint32_t x)
{
        return cttk_not(cttk_u32_neq0(x));
}

/* see cttk.h */
cttk_bool
cttk_array_eq(const unsigned char *src1, const unsigned char *src2, size_t len)
{
  const unsigned char *buf1;
  const unsigned char *buf2;
	size_t u;
	uint32_t r;

	r = 0;
	buf1 = src1;
	buf2 = src2;
	for (u = 0; u < len; u ++) {
		r |= buf1[u] ^ buf2[u];
	}
	return cttk_u32_eq0(r);
}

/* see cttk.h */
int32_t
cttk_array_cmp(const unsigned char *src1, const unsigned char *src2, size_t len)
{
  const unsigned char *buf1;
  const unsigned char *buf2;
	uint32_t r;
	size_t u;

	buf1 = src1;
	buf2 = src2;
	r = 0;
	for (u = 0; u < len; u ++) {
		uint32_t z;

		/*
		 * If the bytes are equal, then z is zero.
		 * If buf1[u] > buf2[u], then z is in the 1..255 range.
		 * If buf1[u] < buf2[u], then bits 8..31 of z are set to 1.
		 */
		z = buf1[u] - buf2[u];

		/*
		 * Set bit 8 to 1 if bits 0..7 are not all zero.
		 */
		z |= z + 0xFF;

		/*
		 * At that point:
		 *  - If buf1[u] == buf2[u], then z == 0xFF.
		 *  - If buf1[u] < buf2[u], then bits 8..31 of z are all one.
		 *  - If buf1[u] > buf2[u], then bit 8 is one, and bits 9..31
		 *    are zero.
		 * We just need to shift the result to remove the low 8 bits,
		 * duplicating the sign bit as needed.
		 */
		z = (z >> 8) | (z & 0xFF000000);

		/*
		 * If r is 1 or -1 at this point, then its low bit is set,
		 * and "(r & 1) - 1" will be 0; in that case, r remains
		 * unmodified.
		 *
		 * If r is 0, then "(r & 1) - 1" will be -1, and r is set
		 * to the value of z (which is 0, 1 or -1).
		 */
		r |= (uint32_t)((r & 1) - 1) & z;
	}
	return *(int32_t *)&r;
}

void main_array_cmp(){
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_cmp(array1,array2,8);
}

void main_array_eq(){
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_eq(array1,array2,8);
}

void main_array_read(){
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_read(array2,array1,3,2,1);
}

void main_array_write(){
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_write(array1,3,2,1,array2);
}

