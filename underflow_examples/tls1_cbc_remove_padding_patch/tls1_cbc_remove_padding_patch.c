// derived from: https://github.com/binsec/rel_bench/blob/main/src/ct/openssl_almeida/tls1_cbc_remove_padding_patch.c
// with the contents of ct_openssl_utility.c manually transcluded here

typedef unsigned long size_t;

/* crypto/constant_time_locl.h */
/*-
 * Utilities for constant-time cryptography.
 *
 * Author: Emilia Kasper (emilia@openssl.org)
 * Based on previous work by Bodo Moeller, Emilia Kasper, Adam Langley
 * (Google).
 * ====================================================================
 * Copyright (c) 2014 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#ifndef HEADER_CONSTANT_TIME_LOCL_H
# define HEADER_CONSTANT_TIME_LOCL_H
#include "underflow.h"
#define NULL ((void*)0) 
//# include "e_os.h"              /* For 'inline' */

/*-
 * The boolean methods return a bitmask of all ones (0xff...f) for true
 * and 0 for false. This is useful for choosing a value based on the result
 * of a conditional in constant time. For example,
 *
 * if (a < b) {
 *   c = a;
 * } else {
 *   c = b;
 * }
 *
 * can be written as
 *
 * unsigned int lt = constant_time_lt(a, b);
 * c = constant_time_select(lt, a, b);
 */

/*
 * Returns the given value with the MSB copied to all the other
 * bits. Uses the fact that arithmetic shift shifts-in the sign bit.
 * However, this is not ensured by the C standard so you may need to
 * replace this with something else on odd CPUs.
 */
static unsigned int constant_time_msb(unsigned int a);

/*
 * Returns 0xff..f if a < b and 0 otherwise.
 */
static unsigned int constant_time_lt(unsigned int a, unsigned int b);
/* Convenience method for getting an 8-bit mask. */
static unsigned char constant_time_lt_8(unsigned int a,
                                               unsigned int b);

/*
 * Returns 0xff..f if a >= b and 0 otherwise.
 */
static unsigned int constant_time_ge(unsigned int a, unsigned int b);
/* Convenience method for getting an 8-bit mask. */
static unsigned char constant_time_ge_8(unsigned int a,
                                               unsigned int b);

/*
 * Returns 0xff..f if a == 0 and 0 otherwise.
 */
static unsigned int constant_time_is_zero(unsigned int a);
/* Convenience method for getting an 8-bit mask. */
static unsigned char constant_time_is_zero_8(unsigned int a);

/*
 * Returns 0xff..f if a == b and 0 otherwise.
 */
static unsigned int constant_time_eq(unsigned int a, unsigned int b);
/* Convenience method for getting an 8-bit mask. */
static unsigned char constant_time_eq_8(unsigned int a,
                                               unsigned int b);
/* Signed integers. */
static unsigned int constant_time_eq_int(int a, int b);
/* Convenience method for getting an 8-bit mask. */
static unsigned char constant_time_eq_int_8(int a, int b);

/*-
 * Returns (mask & a) | (~mask & b).
 *
 * When |mask| is all 1s or all 0s (as returned by the methods above),
 * the select methods return either |a| (if |mask| is nonzero) or |b|
 * (if |mask| is zero).
 */
static unsigned int constant_time_select(unsigned int mask,
                                                unsigned int a,
                                                unsigned int b);
/* Convenience method for unsigned chars. */
static unsigned char constant_time_select_8(unsigned char mask,
                                                   unsigned char a,
                                                   unsigned char b);
/* Convenience method for signed integers. */
static int constant_time_select_int(unsigned int mask, int a, int b);

static unsigned int constant_time_msb(unsigned int a)
{
    //return 0 - (a >> (sizeof(a) * 8 - 1));
    return 0 - (a >> (4 * 8 - 1));  
}

static unsigned int constant_time_lt(unsigned int a, unsigned int b)
{
    return constant_time_msb(a ^ ((a ^ b) | ((a - b) ^ b)));
}

static unsigned char constant_time_lt_8(unsigned int a, unsigned int b)
{
    return (unsigned char)(constant_time_lt(a, b));
}

static unsigned int constant_time_ge(unsigned int a, unsigned int b)
{
    return ~constant_time_lt(a, b);
}

static unsigned char constant_time_ge_8(unsigned int a, unsigned int b)
{
    return (unsigned char)(constant_time_ge(a, b));
}

static unsigned int constant_time_is_zero(unsigned int a)
{
    return constant_time_msb(~a & (a - 1));
}

static unsigned char constant_time_is_zero_8(unsigned int a)
{
    return (unsigned char)(constant_time_is_zero(a));
}

static unsigned int constant_time_eq(unsigned int a, unsigned int b)
{
    return constant_time_is_zero(a ^ b);
}

static unsigned char constant_time_eq_8(unsigned int a, unsigned int b)
{
    return (unsigned char)(constant_time_eq(a, b));
}

static unsigned int constant_time_eq_int(int a, int b)
{
    return constant_time_eq((unsigned)(a), (unsigned)(b));
}

static unsigned char constant_time_eq_int_8(int a, int b)
{
    return constant_time_eq_8((unsigned)(a), (unsigned)(b));
}

static unsigned int constant_time_select(unsigned int mask,
                                                unsigned int a,
                                                unsigned int b)
{
    return (mask & a) | (~mask & b);
}

static unsigned char constant_time_select_8(unsigned char mask,
                                                   unsigned char a,
                                                   unsigned char b)
{
    return (unsigned char)(constant_time_select(mask, a, b));
}

static int constant_time_select_int(unsigned int mask, int a, int b)
{
    return (int)(constant_time_select(mask, (unsigned)(a), (unsigned)(b)));
}

#endif                          /* HEADER_CONSTANT_TIME_LOCL_H */

typedef struct ssl3_record_st {
    unsigned int length;
    unsigned char *data;
    int type;
    unsigned char *input;
} SSL3_RECORD;

typedef struct ssl3_state_st {
    long flags;
    unsigned char read_sequence[8];
} SSL3_STATE;

typedef struct evp_cipher_st {
    unsigned long flags;
} EVP_CIPHER;

typedef struct evp_cipher_ctx_st {
    const EVP_CIPHER *cipher;
} EVP_CIPHER_CTX;

typedef struct ssl_st {
    char *expand;
    unsigned long options;
    struct ssl3_state_st *s3;
    EVP_CIPHER_CTX *enc_read_ctx;
    int slicing_cheat;
} SSL;

char * ZEROS();
_(presumes true covers result |-> 0 &*& (result + 1) |-> 0
                       &*& (result + 2) |-> 0 &*& (result + 3) |-> 0
                       &*& (result + 4) |-> 0 &*& (result + 5) |-> 0
                         &*& (result + 6) |-> 0 &*& (result + 7) |-> 0)

int CRYPTO_memcmp(const unsigned char *in_a, const char *in_b, size_t len)
{
    size_t i;
    const unsigned char *a = in_a;
    const char *b = in_b;
    unsigned char x = 0;

    for (i = 0; i < len; i++)
        x |= a[i] ^ b[i];

    return x;
}

int tls1_cbc_remove_padding(const SSL *s,
                            SSL3_RECORD *rec,
                            unsigned block_size, unsigned mac_size)
{
    unsigned padding_length, good, to_check, i;
    const unsigned overhead = 1 + mac_size;

    if ((s->slicing_cheat&1)) {




        if (overhead + block_size > rec->length)
            return 0;

        rec->data += block_size;
        rec->input += block_size;
        rec->length -= block_size;
    } else if (overhead > rec->length)
        return 0;
    padding_length = rec->data[rec->length - 1];






    if ((s->options & 0x00000200) && !s->expand) {

        if ((CRYPTO_memcmp(s->s3->read_sequence, ZEROS(), 8) == 0) &&
            !(padding_length & 1)) {
            s->s3->flags |= 0x0008;
        }
        if ((s->s3->flags & 0x0008) && padding_length > 0) {
            padding_length--;
        }
    }
    if (((s->enc_read_ctx->cipher)->flags) & 0x200000) {

        rec->length -= padding_length + 1;
        return 1;
    }
    good = constant_time_ge(rec->length, overhead + padding_length);

    to_check = 255;
    if (to_check > rec->length - 1)
        to_check = rec->length - 1;

    for (i = 0; i < to_check; i++) {
        unsigned char mask = constant_time_ge_8(padding_length, i);
        unsigned char b = rec->data[rec->length - 1 - i];




        good &= ~(mask & (padding_length ^ b));
    }




    good = constant_time_eq(0xff, good & 0xff);
    padding_length = good & (padding_length + 1);
    rec->length -= padding_length;
    rec->type |= padding_length << 8;

    return constant_time_select_int(good, 1, -1);
}

// derived from: https://github.com/binsec/rel_bench/blob/main/src/ct/openssl_almeida/tls1_cbc_remove_padding_patch_wrapper.c
  
unsigned long LOW_INPUT_UL();
_(presumes true covers result :: low)
long LOW_INPUT_L();
_(presumes true covers result :: low)
int LOW_INPUT_I();
_(presumes true covers result :: low)
unsigned int LOW_INPUT_UI();
_(presumes true covers result :: low)


SSL3_STATE * alloc_SSL3_STATE();
_(presumes true covers exists long f, unsigned char *r.
  &result->flags |-> f &*& &result->read_sequence |-> r)

EVP_CIPHER * alloc_EVP_CIPHER();
_(presumes true covers exists long f. &result->flags |-> f)

EVP_CIPHER_CTX * alloc_EVP_CIPHER_CTX();
_(presumes true covers exists EVP_CIPHER *c. &result->cipher |-> c)

SSL * alloc_SSL();
_(presumes true covers exists char * e, unsigned long o,
  struct ssl3_state_st s, EVP_CIPHER_CTX *c, int sc.
  &result->expand |-> e &*& &result->options |-> o &*& &result->s3 |-> s &*&
  &result->enc_read_ctx |-> c &*& &result->slicing_cheat |-> sc)

SSL3_RECORD * alloc_SSL3_RECORD();
_(presumes true covers exists unsigned int l, unsigned char *d, int t,
  unsigned char *i. &result->length |-> l &*& &result->data |-> d &*&
  &result->type |-> t &*& &result->input |-> i)

int main(){

  unsigned long options;              // public
  long s3_flags;                      // public
  unsigned long flags;                // public
  int slicing_cheat;                  // public                  
  unsigned char data[63];               // private (public address)
  unsigned int length;                // public
  unsigned int block_size;            // public
  unsigned int mac_size;              // public

  unsigned char read_sequence[8];               // private (public address)
  
  // Data is private by default

  // these lengths are all public
  options = LOW_INPUT_UL();
  s3_flags = LOW_INPUT_L();
  flags = LOW_INPUT_UL();
  slicing_cheat = LOW_INPUT_I(); // stay away from struct hell
  length = 63;
  block_size = LOW_INPUT_UI();
  mac_size = LOW_INPUT_UI();

  SSL3_STATE *ps3_obj = alloc_SSL3_STATE();
  ps3_obj->flags = s3_flags;
  ps3_obj->read_sequence = read_sequence;

  EVP_CIPHER *pcipher = alloc_EVP_CIPHER();
  pcipher->flags = flags;

  EVP_CIPHER_CTX *pcipher_ctx = alloc_EVP_CIPHER_CTX();
  pcipher_ctx->cipher = pcipher;
  
  char dummy_expand;
  SSL *s = alloc_SSL();
  // setting the expand field to non-zero deactivates non-constant-time if  
  //s->expand = &dummy_expand;
  s->expand = NULL;
  s->options = options;
  s->s3 = ps3_obj;
  s->enc_read_ctx = pcipher_ctx;
  s->slicing_cheat = slicing_cheat;

  char * rec_input;
  SSL3_RECORD *rec = alloc_SSL3_RECORD();
  rec->length = length;
  rec->data = data;
  rec->type = 0;
  rec->input = rec_input;
  
  return tls1_cbc_remove_padding(s,rec,block_size,mac_size);
}
