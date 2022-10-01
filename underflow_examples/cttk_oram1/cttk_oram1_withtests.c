#define NULL ((void*)0)
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
//Test1: Work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
	if ((uintptr_t)dst <= (uintptr_t)src) {
//Test2: Work here
		// int *p = NULL;  // x is a null pointer
		// int blah = *p; 
		u = 0;
		while (u < len) {//len = 2
//Test3: Work here
			// int *p = NULL;  // x is a null pointer
			// int blah = *p;
			bdst[u] ^= (bsrc[u] ^ bdst[u]) & -ctl;
			u ++;
//Test4: Work here
			// int *p = NULL;  // x is a null pointer
			// int blah = *p;
		}
//Test5: Work here: Default would work 
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	} else {
//Test6: Work here: Default would work 
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
		u = len;
		while (u > 0) {
//Test7: Work here: Default would work 
			// int *p = NULL;  // x is a null pointer
			// int blah = *p;
			u --;
			bdst[u] ^= (bsrc[u] ^ bdst[u]) & -ctl;
		}
//Test8: Work here: Default would work 
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
	}
//Test9: Work here: Default would work 
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
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
//Test10: Work here: Default would work 
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	for (u = 0; u < len; u ++) {
//Test11: Do not work here since there is no call function 
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
		uint32_t x;

		x = ((za[u]) ^ (zb[u])) & (-ctl);
		za[u] ^= x;
		zb[u] ^= x;
	}
//Test12: Do not work here since there is no call function 
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
}

// manual implementation to give it a spec
void memset(unsigned char *d, int c, size_t len){
	//d, 0, elt_len=3
//Test13: Work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
  size_t i;
  for (i=0;i<len;i++){
//Test14: Work here
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
    *d = (unsigned char)c;
    d++;
  }
//Test15: Work here with Default mode --pulse-widen-threshold 3 --pulse-max-disjuncts 10
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
}

cttk_bool
cttk_bool_of_u32(uint32_t x)
{
        cttk_bool c;

        c = x;
//Test16: Work here
				// int *p = NULL;  // x is a null pointer
				// int blah = *p;
        return c;
}

cttk_bool
cttk_u64_neq0(uint64_t x)
{
        uint64_t q;

        q = x | -x;
//Test17: Work here
				// int *p = NULL;  // x is a null pointer
				// int blah = *p;
        return cttk_bool_of_u32((uint32_t)((q | -q) >> 63));
}

cttk_bool
cttk_not(cttk_bool c)
{
        c ^= (uint32_t)1;
//Test18: Work here
				// int *p = NULL;  // x is a null pointer
				// int blah = *p;
        return c;
}

cttk_bool
cttk_u64_eq0(uint64_t x)
{
//Test19: Work here
				// int *p = NULL;  // x is a null pointer
				// int blah = *p;
        return cttk_not(cttk_u64_neq0(x));
}

cttk_bool
cttk_u64_eq(uint64_t x, uint64_t y)
{
//Test20: Work here
				// int *p = NULL;  // x is a null pointer
				// int blah = *p;
        return cttk_u64_eq0(x ^ y);
}

/* see cttk.h */
void
cttk_array_read(unsigned char *d,
	const unsigned char *a, size_t elt_len, size_t num_len, size_t index)
{
	//(array2,array1,3,2,1) d, 0, elt_len=3
//Test21: Work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	size_t u;
	const unsigned char *b;

	memset(d, 0, elt_len);
//Test22: Work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	for (u = 0, b = a; u < num_len; u ++, b += elt_len) {
//Test23: Work here Work here with --pulse-widen-threshold 3 --pulse-max-disjuncts 11
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
		cttk_cond_copy(cttk_u64_eq(u, index), d, b, elt_len);
	}
//Test24: Work here with --pulse-widen-threshold 3 --pulse-max-disjuncts 31
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
}

/* see cttk.h */
void
cttk_array_write(unsigned char *a, size_t elt_len, size_t num_len,
	size_t index, const unsigned char *s)
{
	size_t u;
	unsigned char *b;
//Test25: Work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	for (u = 0, b = a; u < num_len; u ++, b += elt_len) {
//Test26: Work here
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
		cttk_cond_copy(cttk_u64_eq(u, index), b, s, elt_len);
	}
//Test27: Work here  --pulse-widen-threshold 3 --pulse-max-disjuncts 18
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
}

// from cttk.h


cttk_bool
cttk_u32_neq0(uint32_t x)
{
        uint32_t q;

        q = x | -x;
//Test28: Work here
				// int *p = NULL;  // x is a null pointer
				// int blah = *p;
        return cttk_bool_of_u32((q | -q) >> 31);
}


cttk_bool
cttk_u32_eq0(uint32_t x)
{
//Test29: Work here
				// int *p = NULL;  // x is a null pointer
				// int blah = *p;
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
//Test30: Work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	for (u = 0; u < len; u ++) {
//Test31: Work here
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
		r |= buf1[u] ^ buf2[u];
	}
//Test32: Work here with --pulse-widen-threshold 8 --pulse-max-disjuncts 13
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
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
//Test33: Work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	for (u = 0; u < len; u ++) {
		uint32_t z;
//Test34: Work here
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;

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
//Test35: Work here
		// int *p = NULL;  // x is a null pointer
		// int blah = *p;
	}
//Test36: Work here with --pulse-widen-threshold 8 --pulse-max-disjuncts 13 
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
	return *(int32_t *)&r;
}

void main_array_cmp(){
//Test37: work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_cmp(array1,array2,8);
//Test38: Work here with --pulse-widen-threshold 8 --pulse-max-disjuncts 13 
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
}

void main_array_eq(){
//Test39: work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_eq(array1,array2,8);
//Test40: Work here with --pulse-widen-threshold 8 --pulse-max-disjuncts 13 
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
}

void main_array_read(){
//Test41: work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_read(array2,array1,3,2,1);
//Test42: Work here with --pulse-widen-threshold 3 --pulse-max-disjuncts 31
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
}

void main_array_write(){
//Test43: work here
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
  unsigned char array1[8];
  unsigned char array2[8];
  cttk_array_write(array1,3,2,1,array2);
//Test44: Work here with --pulse-widen-threshold 3 --pulse-max-disjuncts 18
	// int *p = NULL;  // x is a null pointer
	// int blah = *p;
}

