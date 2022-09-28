// adapted from https://github.com/pornin/CTTK/blob/master/src/hex.c
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
#include "underflow.h"
#define NULL ((void *)0)

typedef unsigned int uint32_t;
typedef unsigned long size_t;

/*
 * \brief Hex decoding flag: pad final half-byte with a 0.
 */
#define CTTK_HEX_PAD_ODD       0x0001

/*
 * \brief Hex decoding flag: silently skip whitespace.
 */
#define CTTK_HEX_SKIP_WS       0x0002

/*
 * \brief Hex encoding flag: use uppercase letters.
 */
#define CTTK_HEX_UPPERCASE     0x0001

typedef unsigned int cttk_bool;

cttk_bool
cttk_bool_of_u32(uint32_t x)
{
	cttk_bool c;

	c = x;
//Test 1. Work here
	// int *p = NULL;
	// int blah = *p; // null pointer dereference 
	return c;
}

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
//Test 2. Work here
	// int *p = NULL;
	// int blah = *p; // null pointer dereference 
	return cttk_bool_of_u32((z ^ ((x ^ y) & (x ^ z))) >> 31);
}

cttk_bool
cttk_u32_lt(uint32_t x, uint32_t y)
{
//Test 3. Work here
// 	int *p = NULL;
// 	int blah = *p; // null pointer dereference 
	return cttk_u32_gt(y, x);
}


/* see cttk.h */
int
cttk_hexval(char c)
{
	/*
	 * Code below assumes an ASCII compatible charset.
	 *
	 * Decimal digits are 0x30 to 0x39.
	 * Uppercase letters 'A' to 'F' are 0x41 to 0x46.
	 * Lowercase letters 'a' to 'f' are 0x61 to 0x66.
	 *
	 * Only one of the three clauses (at most) will yield a non-zero
	 * value; we increment it by 1 to get a value from 1 to 16, or 0
	 * if the source character is not an hexadecimal digit. A final
	 * subtraction ensures that we get -1 on an invalid source digit.
	 */
	uint32_t x, y, z, r;

	x = (uint32_t)c - 0x30;
	y = (uint32_t)c - 0x41;
	z = (uint32_t)c - 0x61;
	r = ((x + 1) & -cttk_u32_lt(x, 10))
		| ((y + 11) & -cttk_u32_lt(y, 6))
		| ((z + 11) & -cttk_u32_lt(z, 6));
//Test 4. Work here
	// int *p = NULL;
	// int blah = *p; // null pointer dereference 
	return (int)r - 1;
}

/* see cttk.h */
char
cttk_hexdigit(int x, int uppercase)
{
	unsigned off;

	/*
	 * 'off' is the offset to add to the character value if going
	 * beyond '9' (0x39) so that a letter is obtained ('A' is 0x41,
	 * 'a' is 0x61).
	 */
	off = (0x41 - 0x3A);
	if (!uppercase) {
		off += 0x20;
	}

	/*
	 * If x >= 10, then the subtraction will yield upper bits of
	 * value 0.
	 */
//Test 5. Work here with parameter --pulse-widen-threshold 1 --pulse-max-disjuncts 24
	//because the uppercase letter is referred by the function. 
	// int *p = NULL;
	// int blah = *p; // null pointer dereference 
	return (char)(0x30 + x + (off & ~(((unsigned)x - 10) >> 8)));
}

/* see cttk.h */
size_t
cttk_hexscan(const char *src, size_t src_len, int skipws)
{
	size_t u;

	for (u = 0; u < src_len; u ++) {
		int c;

		c = src[u];
		if (skipws && c <= 0x20) {
			continue;
		}
		if (cttk_hexval(c) < 0) {
			break;
		}
	}
//Test 6. Not able to work here, since src function is not being referred. 
	// int *p = NULL;
	// int blah = *p; // null pointer dereference 
	return u;
}
size_t
cttk_hextobin_gen2(unsigned char *dst, size_t dst_len,
	const char *src, size_t src_len, const char **err, unsigned flags)
{
	return dst_len; 
}
/* see cttk.h */
size_t
cttk_hextobin_gen(unsigned char *dst, size_t dst_len,
	const char *src, size_t src_len, const char **err, unsigned flags)
{
	size_t u, v;
	unsigned char *buf;
	int halfbyte;
	int acc;

	buf = dst;
	halfbyte = 0;
	acc = 0;
	v = 0;
//Test 7. Work here
	// int *p = NULL;
	// int blah = *p; // null pointer dereference 
	for (u = 0; u < src_len; u ++) {//threashold should be equal or larger than 16
		int c, d;
//Test 8. Work here
	// int *p = NULL;
	// int blah = *p; // null pointer dereference 
		
		 // * We read source characters as unsigned bytes, so that
		 // * values are positive and bytes beyond 0x7F are not
		 // * considered whitespace.
		 
		c = *((const unsigned char *)src + u);
		d = cttk_hexval(c);

		/*
		 * If the character is not an hex digit, it may be
		 * whitespace to be ignored; otherwise, this is an
		 * error to report. Padding of half-bytes must be applied
		 * where necessary (in such a case, output buffer capacity
		 * was already checked).
		 */
		if (d < 0) {

//Test 9. Work here
			// int *p = NULL;
			// int blah = *p; // null pointer dereference
			if ((flags & 0x0002 /* CTTK_HEX_SKIP_WS */) != 0 && c <= 32) {
//Test10: do not work here
					// int *p = NULL;
					// int blah = *p; // null pointer dereference
				continue;
			}
			if (err != NULL) {
//Test11: do not work here
					// int *p = NULL;
					// int blah = *p; // null pointer dereference
				*err = src + u;
			}
			if (halfbyte && (flags & 0x0001 /* CTTK_HEX_PAD_ODD */) != 0) {
//Test12: do not work here
					// int *p = NULL;
					// int blah = *p; // null pointer dereference
				if (buf != NULL) {
//Test13: do not work here
					// int *p = NULL;
					// int blah = *p; // null pointer dereference
					buf[v] = acc;
				}
				v ++;
			} 
//Test14: Worked here
			// int *p = NULL;
			// int blah = *p; // null pointer dereference
		}
		 // * We have a new digit. We either keep it in the accumulator
		 // * (first digit of the next byte) or store it into the output
		 // * buffer.
		 // *
		 // * Output buffer overflow is detected on the first digit,
		 // * not the second.
		 
//Test15 Work here
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
		if (halfbyte) {
//Test16 Work here
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
			if (buf != NULL) {
//Test17 Work here
				// int *p = NULL;
				// int blah = *p; // null pointer dereference
				buf[v] = acc + d;
			}
//Test18 Work here
				// int *p = NULL;
				// int blah = *p; // null pointer dereference
			v ++;
		} else {
//Test19 Work here
			// int *p = NULL;
			// int blah = *p; // null pointer dereference
			if (buf != NULL && v == dst_len) {
//Test20 Do not Work here
				// int *p = NULL;
				// int blah = *p; // null pointer dereference
				if (err != NULL) {
//Test21 Do Work here
				// int *p = NULL;
				// int blah = *p; // null pointer dereference
					*err = src + u;
				}
				return v;
			}
//Test22 Work here
			// int *p = NULL;
			// int blah = *p; // null pointer dereference
			acc = d << 4;
//Test23 Work here
			// int *p = NULL;
			// int blah = *p; // null pointer dereference
		}
		halfbyte = !halfbyte;
//Test24 Work here
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
	}
// //Test25 Work here? No the function reach the return statement 
// 		// int *p = NULL;
// 		// int blah = *p; // null pointer dereference
	
// 	 * This part is reached when the source string is finished. We
// 	 * encountered no error so far. If there is a pending digit,
// 	 * then we either pad it into a full byte, or report an error,
// 	 * depending on the relevant flag. Note that output buffer
// 	 * capacity was already checked when that first digit was read.
	 
	if (halfbyte) {
		if ((flags & 0x0001 /* CTTK_HEX_PAD_ODD */) != 0) {
			if (buf != NULL) {
				buf[v] = acc;
			}
			v ++;
		} else {
			if (err != NULL) {
				*err = src + src_len;
			}
			return v;
		}
	}
	if (err != NULL) {
		*err = NULL;
	}
	return v;
}

/* see cttk.h */
size_t
cttk_bintohex_gen(char *dst, size_t dst_len,
	const unsigned char *src, size_t src_len, unsigned flags)
{
	const unsigned char *buf;
	size_t u, v;
	int halflast, uppercase;
//Test26 Work here
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
	if (dst == NULL) {
//Test27 Do not Work here(but work if dst != NULL)
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
		return (src_len << 1);
	}
//Test28 work
		// int *p = NULL;
		// int blah = *p; // null pointer dereference

	/*
	 * Special case: destination buffer has size 0; we cannot even
	 * write the terminating null byte.
	 */
	if (dst_len == 0) {
//Test29 do not work
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
		return 0;
	}
//Test30 work
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
	/*
	 * Adjust lengths. Three situations:
	 *
	 *  - Destination is large enough for all characters.
	 *  - Destination is too short, but may accommodate an even number
	 *    of digits.
	 *  - Destination is too short, but may accommodate an odd number
	 *    of digits.
	 */
	halflast = 0;
//Test31 work
	// int *p = NULL;
	// int blah = *p; // null pointer dereference
	if (dst_len < (1 + (src_len << 1))) {
//Test32 Do not work
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
		if ((dst_len & 1) == 0) {
			src_len = (dst_len - 1) >> 1;
			halflast = 1;
		} else {
			src_len = dst_len >> 1;
		}
	}
//Test33 work
		// int *p = NULL;
		// int blah = *p; // null pointer dereference

	buf = src;
	v = 0;
	uppercase = (flags & 0x0001 /* CTTK_HEX_UPPERCASE */) != 0;
//Test34 work
	// int *p = NULL;
	// int blah = *p; // null pointer dereference
	for (u = 0; u < src_len; u ++) {
		int x;
//Test35 work 
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
		x = buf[u];
		dst[v ++] = cttk_hexdigit(x >> 4, uppercase);
		dst[v ++] = cttk_hexdigit(x & 15, uppercase);
	}
//Test36 work with --pulse-widen-threshold 8 --pulse-max-disjuncts 72
	// int *p = NULL;
	// int blah = *p; // null pointer dereference
	if (halflast) {//halflast assigned with value 0 at line 371
//Test37 Do not work 
		// int *p = NULL;
		// int blah = *p; // null pointer dereference
		int x;

		x = buf[u];
		dst[v ++] = cttk_hexdigit(x >> 4, uppercase);
	}

	dst[v] = 0;
//Test38 work with --pulse-widen-threshold 8 --pulse-max-disjuncts 82
	// int *p = NULL;
	// int blah = *p; // null pointer dereference
	return v;
}


void main_hextobin(){
//Test39 work 
	// int *p = NULL;
	// int blah = *p; // null pointer dereference
  char hexstring[17]; // 16 chars plus trailing NUL byte
  unsigned char bytes[8];
//Test40 work 
	// int *p = NULL;
	// int blah = *p; // null pointer dereference
  size_t res =
    cttk_hextobin_gen(bytes, 8, hexstring, 16, NULL, 0);

}

void main_bintohex(){
//Test41 work 
	// int *p = NULL;
	// int blah = *p; // null pointer dereference
  char hexstring[17]; // 16 chars plus trailing NUL byte
  unsigned char bytes[8];
  size_t res =  cttk_bintohex_gen(hexstring,17,bytes,8,0);
}
