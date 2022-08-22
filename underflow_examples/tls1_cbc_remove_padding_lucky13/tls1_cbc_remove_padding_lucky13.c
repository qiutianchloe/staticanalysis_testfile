// derived from: https://github.com/binsec/rel_bench/blob/main/src/ct/openssl_almeida/tls1_cbc_remove_padding_lucky13.c
#include "underflow.h"
typedef unsigned long size_t;
#define NULL ((void *)0)
typedef struct ssl3_record_st {
    unsigned int length;
    unsigned char *data;
    int type;
    unsigned char *input;
} SSL3_RECORD;

typedef struct ssl3_state_st {
    long flags;
    unsigned char * read_sequence;
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

/*
int memcmp(char *a, char *b, size_t len){
  size_t i=0;
  for (i=0; i<len; i++){
    if (a[i] != b[i]){
      return 1;
    }
  }
  return 0;
}
*/

int tls1_cbc_remove_padding(const SSL *s,
                            SSL3_RECORD *rec,
                            unsigned bs, unsigned mac_size)
{
  int ii, i, j;
  int l = rec->length;
  ii=i=rec->data[l-1];
  i++;
 

  if ((s->options&0x00000200))
    {

  //int *p = NULL;
  //int blah = *p; // null pointer dereference
  
      if ((memcmp(s->s3->read_sequence,
                  "\0\0\0\0\0\0\0\0",8) == 0) && !(ii & 1))
        s->s3->flags|=0x0008;
      if (s->s3->flags & 0x0008)
        i--;
    }

  if (i + bs > (int)(rec->length))
    {
      return -1;
    }
  for (j=(int)(l-i); j<(int)l; j++)
    {
      if (rec->data[j] != ii)
        {

     return -1;
        }
    }
  rec->length-=i;

  rec->data += bs;
  rec->input += bs;
  rec->length -= bs;

  return 1;
}

// derived from: https://github.com/binsec/rel_bench/blob/main/src/ct/openssl_almeida/tls1_cbc_remove_padding_lucky13_wrapper.c
  
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
