// derived from https://github.com/binsec/rel_bench/blob/main/src/ct/libsodium/libsodium/src/libsodium/sodium/utils.c
#define NULL ((void*)0)

typedef unsigned int size_t;

// void * changed to char * in the args

int
sodium_memcmp(const char * const b1_, const char * const b2_, size_t len)
{
//Test 1. Work 
    // int *x = NULL;  // x is a null pointer
    // int y = *x; 
    const unsigned char *b1 = (const unsigned char *) b1_;
    const unsigned char *b2 = (const unsigned char *) b2_;
    size_t               i;
    unsigned char        d = (unsigned char) 0U;

    for (i = 0U; i < len; i++) {
// Test 2. Work here
        // int *x = NULL;  // x is a null pointer
        // int y = *x; 
        d |= b1[i] ^ b2[i];
    }
//Test 3. Work with parameter --pulse-widen-threshold 64 --pulse-max-disjuncts 69
    // int *x = NULL;  // x is a null pointer
    // int y = *x; 
    return (int) ((1 & ((d - 1) >> 8)) - 1);
}

int main(){
//Test 4. Work here  
  // int *x = NULL;  // x is a null pointer
  // int y = *x; 
  char mem1[64];
  char mem2[64];
  return sodium_memcmp(mem1,mem2,64);
}
