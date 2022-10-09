/* constant-time selection. From: 
   https://github.com/binsec/rel_bench/blob/main/src/ct/ct-select/lib.c
*/

typedef unsigned int uint32_t;
typedef int _bool;

/* Program */
int ct_isnonzero_u32(uint32_t x) {
  return (x|-x)>>31;
}

uint32_t ct_mask_u32(uint32_t bit) {
  return -(uint32_t) ct_isnonzero_u32(bit);
}

uint32_t ct_select_u32_v1(uint32_t x, uint32_t y, _bool bit) {
  uint32_t m = ct_mask_u32(bit);
  return (x&m) | (y&~m);
}

uint32_t ct_select_u32_v2(uint32_t x, uint32_t y, _bool bit) {
  uint32_t m = -(uint32_t) (((uint32_t)bit|-(uint32_t)bit)>>31);
  return (x&m) | (y&~m);
}

uint32_t ct_select_u32_v3(uint32_t x, uint32_t y, _bool bit) {
  int b = 1-bit;
  return (x*bit) | (y*b);
}


uint32_t ct_select_u32_v4(uint32_t x, uint32_t y, _bool bit) {
  int b = 0-bit;
  return (x&b) | (y&~b);
}

uint32_t ct_select_u32_naive(uint32_t x, uint32_t y, _bool bit) {
  return bit ? x : y;
}

int get_val();
int main(){
  uint32_t x = get_val();
  uint32_t y = get_val();
  _bool bit = get_val();
  ct_select_u32_v1(x,y,bit);
  ct_select_u32_v2(x,y,bit);
  ct_select_u32_v3(x,y,bit);
  ct_select_u32_v4(x,y,bit);
  ct_select_u32_naive(x,y,bit);        
}
