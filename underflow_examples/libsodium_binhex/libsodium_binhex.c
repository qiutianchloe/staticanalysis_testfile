#include "underflow.h"
#define NULL ((void*)0)
// from https://github.com/binsec/rel_bench/blob/main/src/ct/libsodium/libsodium/src/libsodium/sodium/utils.c

typedef unsigned long size_t;

// replace SIZE_MAX by a function
size_t SIZE_MAX();
_(presumes true covers result :: low && result > 64UL)

void abort();
_(presumes true fails memory true)

/* Derived from original code by CodesInChaos */
char *
sodium_bin2hex(char * const hex, const size_t hex_maxlen,
               const unsigned char * const bin, const size_t bin_len)
{
  size_t       i = (size_t) 0U;
  unsigned int x;
  int          b;
  int          c;

  if (bin_len >= SIZE_MAX() / 2 || hex_maxlen < bin_len * 2U) {
    abort(); /* LCOV_EXCL_LINE */
  }
  while (i < bin_len) {
    c = bin[i] & 0xf;
    b = bin[i] >> 4;
    x = (unsigned char) (87U + c + (((c - 10U) >> 8) & ~38U)) << 8 |
      (unsigned char) (87U + b + (((b - 10U) >> 8) & ~38U));
    hex[i * 2U] = (char) x;
    x >>= 8;
    hex[i * 2U + 1U] = (char) x;
    i++;
  }
  hex[i * 2U] = 0U;

  return hex;
}



int
sodium_hex2bin(unsigned char * const bin, const size_t bin_maxlen,
               const char * const hex, const size_t hex_len,
               const char * const ignore, size_t * const bin_len,
               const char ** const hex_end)
{
  size_t        bin_pos = (size_t) 0U;
  size_t        hex_pos = (size_t) 0U;
  int           ret = 0;
  unsigned char c;
  unsigned char c_acc = 0U;
  unsigned char c_alpha0; unsigned char c_alpha;
  unsigned char c_num0; unsigned char c_num;
  unsigned char c_val;
  unsigned char state = 0U;

  while (hex_pos < hex_len) {
    // XXX: parser issue? had to add extra brackets
    c = (unsigned char) (hex[hex_pos]);
    c_num = c ^ 48U;
    c_num0 = (c_num - 10U) >> 8;
    c_alpha = (c & ~32U) - 55U;
    c_alpha0 = ((c_alpha - 10U) ^ (c_alpha - 16U)) >> 8;
    if ((c_num0 | c_alpha0) == 0U) {
      if (ignore != NULL) {
        // XXX: factor this out into a separate conditional so symex can
        // see the contradiction before having to execute strchr()
        if (state == 0U && strchr(ignore, c) != NULL) {
          hex_pos++;
          continue;
        }
      }
      break;
    }
    c_val = (c_num0 & c_num) | (c_alpha0 & c_alpha);
    if (bin_pos >= bin_maxlen) {
      ret = -1;
      //errno = ERANGE;  XXX: errno not supported at present
      break;
    }
    if (state == 0U) {
      c_acc = c_val * 16U;
    } else {
      bin[bin_pos++] = c_acc | c_val;
    }
    state = ~state;
    hex_pos++;
  }
  if (state != 0U) {
    hex_pos--;
  }  
  if (hex_end != (char **)NULL) {
    *hex_end = &hex[hex_pos];
  }
  if (bin_len != NULL) {
    *bin_len = bin_pos;
  }
  return ret;
}


size_t binlen();
_(presumes true covers result :: low && result == 31UL)

void main_bin2hex(){
  char bin[32];
  char hex[65]; // including trailing ASCII NUL
  size_t rbinlen;
  sodium_bin2hex(hex,65,bin,binlen());
}

void main_hex2bin(){
  char bin[32];
  char hex[65]; // including trailing ASCII NUL
  size_t rbinlen;
  sodium_hex2bin(bin,32,hex,64,NULL,&rbinlen,NULL);  
}
