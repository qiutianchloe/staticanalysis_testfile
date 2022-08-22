// derived from https://github.com/binsec/rel_bench/blob/main/src/ct/libsodium/libsodium/src/libsodium/sodium/utils.c

typedef unsigned int size_t;

// 0U changed to 0
// void * changed to char * in the args
// remove use of const
// for-loop changed to while-loop

int
sodium_memcmp(/* const */ char * /* const */ b1_, /* const */ char * /* const */ b2_, size_t len)
{
    /* const */ unsigned char *b1 = (/* const */ unsigned char *) b1_;
    /* const */ unsigned char *b2 = (/* const */ unsigned char *) b2_;
    size_t               i;
    unsigned char        d = (unsigned char) 0;

    i = 0;
    while (i < len) {
        d |= b1[i] ^ b2[i];
        i++;
    }
    return (int) ((1 & ((d - 1) >> 8)) - 1);
}

