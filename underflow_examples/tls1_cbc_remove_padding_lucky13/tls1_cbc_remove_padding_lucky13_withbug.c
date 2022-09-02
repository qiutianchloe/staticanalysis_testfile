// derived from: https://github.com/binsec/rel_bench/blob/main/src/ct/openssl_almeida/tls1_cbc_remove_padding_lucky13.c
#include "underflow.h"
typedef unsigned long size_t;
#define NULL ((void *)0); 

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
    unsigned char * read_sequence;
};
typedef struct ssl3_state_st SSL3_STATE;

struct evp_cipher_st {
    unsigned long flags;
};
typedef struct evp_cipher_st EVP_CIPHER;

struct evp_cipher_ctx_st {
  /* const */ EVP_CIPHER *cipher;
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


char * ZEROS();
_(presumes true covers true)

int memcmp(char *a, char *b, size_t len);
_(presumes true covers true)

int tls1_cbc_remove_padding(/* const */ SSL *s,
                            SSL3_RECORD *rec,
                            unsigned bs, unsigned mac_size)
{

//Test Point 1： Work
  // int *p = NULL;
  // int blah = *p; // null pointer dereference  
  int ii; int i; int j;
  int l = rec->length;
  ii=i=rec->data[l-1];
  i++;



/*Original Code*/
  // if ((s->options&0x00000200))
  //   {
  //     if ((memcmp(s->s3->read_sequence,
  //                 ZEROS(),8) == 0) && !(ii & 1))
  //       s->s3->flags|=0x0008;
  //     if (s->s3->flags & 0x0008)
  //       i--;
  //   }


//Test Point 2:Work
  // if(1){
  //     int *p = NULL;
  //     int blah = *p; // null pointer dereference     
  // }



//   if ((s->options&0x00000200))
//     {
// //Test Point 3: Something wrong
//       int *p = NULL;
//       int blah = *p; // null pointer dereference  
//       // if ((memcmp(s->s3->read_sequence,
//       //             ZEROS(),8) == 0) && !(ii & 1))
//       //   s->s3->flags|=0x0008;
//       // if (s->s3->flags & 0x0008)
//       //   i--;
//     }

//   if (1)
//     {
// //Test Point 4: Work
//       int *p = NULL;
//       int blah = *p; // null pointer dereference  
//       if ((memcmp(s->s3->read_sequence,
//                   ZEROS(),8) == 0) && !(ii & 1))
//         s->s3->flags|=0x0008;
//       if (s->s3->flags & 0x0008)
//         i--;
//     }

//   if (1)
//     {
// //Test Point 5: Work
//       if ((memcmp(s->s3->read_sequence,ZEROS(),8) == 0) && !(ii & 1)) 
//         s->s3->flags|=0x0008;
//       int *p = NULL;
//       int blah = *p; // null pointer dereference 
//       if (s->s3->flags & 0x0008)
//         i--;
//     }

//   if (1)
//     {
// //Test Point 6: Don't Work Here
//       if ((memcmp(s->s3->read_sequence,ZEROS(),8) == 0) && !(ii & 1)) 
//         s->s3->flags|=0x0008;
//       if (s->s3->flags & 0x0008){
//         int *p = NULL;
//         int blah = *p; // null pointer dereference 
//         i--;
//       }
//     }

//   if (1)
//     {
// //Test Point 7: Work
//       if ((memcmp(s->s3->read_sequence,ZEROS(),8) == 0) && !(ii & 1)) 
//         s->s3->flags|=0x0008;
//       if (1){
//         int *p = NULL;
//         int blah = *p; // null pointer dereference 
//         i--;
//       }
//     }


  // if (1)
  //   {
// //Test Point 8: Work
//       if ((memcmp(s->s3->read_sequence,ZEROS(),8) == 0) && !(ii & 1)) 
//         s->s3->flags|=0x0008;
//       if (1){
//         i--;
//         int *p = NULL;
//         int blah = *p; // null pointer dereference 
//       }
//     }


/*After modification*/
  if (1)
    {
      if ((memcmp(s->s3->read_sequence,ZEROS(),8) == 0) && !(ii & 1)) 
        s->s3->flags|=0x0008;
      if (1){
        i--;
      }
    }
//Test Point 9: Work          
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 

/*Original Code*/
  // if (i + bs > (int)(rec->length))
  //   {
  //     return -1;
  //   }
  // j=(int)(l-i);

// //Test Point 10: Don't Work          
//   int *p = NULL;
//   int blah = *p; // null pointer dereference 

//--pulse-widen-threshold 1 --pulse-max-disjuncts 9 
//Part of test 12, 13
//l = 10;

/*After Modification*/
//This if statement is tend to define the value of j
  if (i)// + bs > (int)(rec->length))
    {
      return -1;
    }
  j=(int)(l-i);

// // Test Point 11: Work          
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 

//What is potential length value??????
//j = 0; 


  while (j<(int)l)
    {
// Test Point 12: Doesn't work
      // int *p = NULL;
      // int blah = *p; // null pointer dereference         
      if (rec->data[j] != ii)
        {

     return -1;
        }
      j++;
    }

//Test Point 13: Work 
    // int *p = NULL;
    // int blah = *p; // null pointer dereference 


  rec->length-=i;

  rec->data += bs;
  rec->input += bs;
  rec->length -= bs;

// Test Point 14: Work, It can work out with default command value
  int *p = NULL;
  int blah = *p; // null pointer dereference 
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
  unsigned char * data;               // private (public address)
  unsigned int length;                // public
  unsigned int block_size;            // public
  unsigned int mac_size;              // public

  // Data is private by default
// Test Point 15: Work
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 

  // these lengths are all public
  options = LOW_INPUT_UL();
  s3_flags = LOW_INPUT_L();
  flags = LOW_INPUT_UL();
  slicing_cheat = LOW_INPUT_I(); // stay away from struct hell
  length = LOW_INPUT_UI();
  block_size = LOW_INPUT_UI();
  mac_size = LOW_INPUT_UI();
// Test Point 16: Work
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 

  SSL3_STATE *ps3_obj = alloc_SSL3_STATE();
  ps3_obj->flags = s3_flags;

  EVP_CIPHER *pcipher = alloc_EVP_CIPHER();
  pcipher->flags = flags;

  EVP_CIPHER_CTX *pcipher_ctx = alloc_EVP_CIPHER_CTX();
  pcipher_ctx->cipher = pcipher;

// Test Point 17: Work
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 

  char dummy_expand;
  SSL *s = alloc_SSL();
  // setting the expand field to non-zero deactivates non-constant-time if  
  //s->expand = &dummy_expand;

// Test Point 18: Work
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 

  s->expand = NULL;
  s->options = options;
  s->s3 = ps3_obj;
  s->enc_read_ctx = pcipher_ctx;
  s->slicing_cheat = slicing_cheat;

// Test Point 19: Work
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 

  char * rec_input;
  SSL3_RECORD *rec = alloc_SSL3_RECORD();
// Test Point 20: Work
  // int *p1 = NULL;
  // int blah1 = *p1; // null pointer dereference
  rec->length = length;
// Test Point 21: Work
  // int *p1 = NULL;
  // int blah1 = *p1; // null pointer dereference
  rec->data = data;
// Test Point 22: Don't Work Here!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // int *p1 = NULL;
  // int blah1 = *p1; // null pointer dereference
  rec->type = 0;
  rec->input = rec_input;

// Test Point 22: Work
  // int *p2 = NULL;
  // int blah2 = *p2; // null pointer dereference 

  return tls1_cbc_remove_padding(s,rec,block_size,mac_size);
}