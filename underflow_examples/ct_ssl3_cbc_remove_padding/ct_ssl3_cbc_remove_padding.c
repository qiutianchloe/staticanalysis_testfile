#include "underflow.h"
#define NULL ((void*)0)
/* derived from https://github.com/binsec/rel_bench/blob/main/src/ct/openssl_almeida/ssl3_cbc_remove_padding.c 
   and stuff manually transcluded from ct_openssl_utility.c */

struct ssl3_record_st {
  unsigned int length;
  unsigned char *data;
  int type;
  unsigned char *input;
};
typedef struct ssl3_record_st SSL3_RECORD;

struct ssl3_state_st {
  long flags;
  //unsigned char read_sequence[8];
  unsigned char *read_sequence;
};
typedef struct ssl3_state_st SSL3_STATE;

struct evp_cipher_st {
  unsigned long flags;
};
typedef struct evp_cipher_st EVP_CIPHER;

struct evp_cipher_ctx_st {
  const EVP_CIPHER *cipher;
};
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;

struct ssl_st {
  char *expand;
  unsigned long options;
  struct ssl3_state_st *s3;
  EVP_CIPHER_CTX *enc_read_ctx;
  int slicing_cheat;
};
typedef struct ssl_st SSL;

unsigned int constant_time_msb(unsigned int a)
{
  //return 0 - (a >> (sizeof(a) * 8 - 1));
  return 0 - (a >> (4 * 8 - 1));
}

unsigned int constant_time_lt(unsigned int a, unsigned int b)
{
    return constant_time_msb(a ^ ((a ^ b) | ((a - b) ^ b)));
}

unsigned char constant_time_lt_8(unsigned int a, unsigned int b)
{
    return (unsigned char)(constant_time_lt(a, b));
}

unsigned int constant_time_ge(unsigned int a, unsigned int b)
{
    return ~constant_time_lt(a, b);
}

unsigned char constant_time_ge_8(unsigned int a, unsigned int b)
{
    return (unsigned char)(constant_time_ge(a, b));
}

unsigned int constant_time_is_zero(unsigned int a)
{
    return constant_time_msb(~a & (a - 1));
}

unsigned char constant_time_is_zero_8(unsigned int a)
{
    return (unsigned char)(constant_time_is_zero(a));
}

unsigned int constant_time_eq(unsigned int a, unsigned int b)
{
    return constant_time_is_zero(a ^ b);
}

unsigned char constant_time_eq_8(unsigned int a, unsigned int b)
{
    return (unsigned char)(constant_time_eq(a, b));
}

unsigned int constant_time_eq_int(int a, int b)
{
    return constant_time_eq((unsigned)(a), (unsigned)(b));
}

unsigned char constant_time_eq_int_8(int a, int b)
{
    return constant_time_eq_8((unsigned)(a), (unsigned)(b));
}

unsigned int constant_time_select(unsigned int mask,
                                                unsigned int a,
                                                unsigned int b)
{
    return (mask & a) | (~mask & b);
}

unsigned char constant_time_select_8(unsigned char mask,
                                                   unsigned char a,
                                                   unsigned char b)
{
    return (unsigned char)(constant_time_select(mask, a, b));
}

int constant_time_select_int(unsigned int mask, int a, int b)
{
    return (int)(constant_time_select(mask, (unsigned)(a), (unsigned)(b)));
}


# define SSL_OP_TLS_BLOCK_PADDING_BUG       0x00000200L
# define TLS1_FLAGS_TLS_PADDING_BUG         0x0008
# define SSL_USE_EXPLICIT_IV(a) (a->slicing_cheat&1) // slicing
# define EVP_CIPHER_flags(e)        ((e)->flags)
# define EVP_CIPH_FLAG_AEAD_CIPHER       0x200000
# define EVP_MAX_MD_SIZE                 64/* longest known is SHA512 */
# define OPENSSL_assert(a) 1; // slicing

/*-
 * ssl3_cbc_remove_padding removes padding from the decrypted, SSLv3, CBC
 * record in |rec| by updating |rec->length| in constant time.
 *
 * block_size: the block size of the cipher used to encrypt the record.
 * returns:
 *   0: (in non-constant time) if the record is publicly invalid.
 *   1: if the padding was valid
 *  -1: otherwise.
 */
int ssl3_cbc_remove_padding(const SSL *s,
                            SSL3_RECORD *rec,
                            unsigned int block_size, unsigned int mac_size)
{
  unsigned padding_length, good;
  const unsigned overhead = 1 /* padding length byte */  + mac_size;

  /*
   * These lengths are all public so we can test them in non-constant time.
   */
  if (overhead > (rec->length))
    return 0;

  padding_length = rec->data[rec->length - 1];
  good = constant_time_ge(rec->length, padding_length + overhead);
  /* SSLv3 requires that the padding is minimal. */
  good &= constant_time_ge(block_size, padding_length + 1);
  padding_length = good & (padding_length + 1);
  rec->length -= padding_length;
  rec->type |= padding_length << 8; /* kludge: pass padding length */
  return constant_time_select_int(good, 1, -1);
}

SSL * alloc_SSL();
_(presumes true covers exists char * e, unsigned long o,
  struct ssl3_state_st s, EVP_CIPHER_CTX *c, int sc.
  &result->expand |-> e &*& &result->options |-> o &*& &result->s3 |-> s &*&
  &result->enc_read_ctx |-> c &*& &result->slicing_cheat |-> sc)

SSL3_RECORD * alloc_SSL3_RECORD();
_(presumes true covers exists unsigned int l, unsigned char *d, int t,
  unsigned char *i. &result->length |-> l &*& &result->data |-> d &*&
  &result->type |-> t &*& &result->input |-> i)

unsigned int LOW_UI();
_(presumes true covers result :: low)
  
// derived from ssl3_cbc_remove_padding_patch_wrapper.c in https://github.com/binsec/rel_bench repo


/* Here, we have to concretize the length because we cannot work with a symbolic pointer */
/* Solution: malloc stub ? */

int main(){
  unsigned char data[200];      /* Private */
  unsigned int length = 200;    /* Public */
  unsigned int block_size = LOW_UI();      /* Public */
  unsigned int mac_size = LOW_UI();        /* Public */
  unsigned int rec_type = LOW_UI();        /* Public */
  // unused? unsigned char input[200];     /* Public */

  // s is actually not used in the function
  SSL s_obj;
  const SSL *s = alloc_SSL();

  // only the length and data fields are used in the function
  SSL3_RECORD * rec = alloc_SSL3_RECORD();
  rec->length = length;
  rec->data = data;
  rec->type = rec_type;
  rec->input = NULL;

  return ssl3_cbc_remove_padding(s,rec,block_size,mac_size);
}
