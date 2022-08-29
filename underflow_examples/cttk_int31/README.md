## Some Updates

3.add #include "underflow.h" to include the head file

2.add #define NULL ((void*)0) to define NULL

1.Change the order of the code to make Infer able to run

## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh ./examples/cttk_int31_ppp.c `|???s|???|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/cttk_int31_ppp.c`|1.959s|No issues found|
|Infer bufferoverrun|`infer --bufferoverrun -- gcc -c -I./include/ ./examples/cttk_int31_ppp.c`|7.07s|257 issues found|







Infer bufferoverrun
examples/cttk_int31_ppp.c:88: error: Integer Overflow L2
  ([0, min(31, `h`)] - 1):unsigned32.
  86. top_index(uint32_t h)
  87. {
  88.  h = (h & 31) - 1;
       ^
  89.  return h + (31 & (h >> 5));
  90. }

examples/cttk_int31_ppp.c:131: error: Buffer Overrun L2
  Offset: [1, 47] (⇐ 1 + [0, 46]) Size: 9 by call to `cttk_i31_init`.
  129. void main_init(){
  130.   uint32_t a[9];
  131.   cttk_i31_init(a,8);
         ^
  132. }
  133. 

examples/cttk_int31_ppp.c:155: error: Integer Overflow L2
  ([-`x`, min(32, `x`)] - 1):unsigned32.
  153.  }
  154.  if (size <= 32) {
  155.   x[0] |= cttk_u32_neq0(v >> (size - 1)) << 31;
                 ^
  156.  }
  157. }

examples/cttk_int31_ppp.c:149: error: Integer Overflow L2
  ([0, `x` + 31] - 1):unsigned64.
  147. 
  148. 
  149.  memset32(x + 2, 0, (len - 1));
        ^
  150.  x[1] = v & 0x7FFFFFFF;
  151.  if (size >= 32) {

examples/cttk_int31_ppp.c:163: error: Buffer Overrun L2
  Offset: [1, 47] (⇐ 1 + [0, 46]) Size: 9 by call to `cttk_i31_init`.
  161.   uint32_t a[9];
  162.   uint32_t v;
  163.   cttk_i31_init(a,8);
         ^
  164.   cttk_i31_set_u32(a,v);
  165. }


Found 257 issues (console output truncated to 5, see '/Users/tianqiu/Desktop/research_project/underflow/underflow/infer-out/report.txt' for the full list)
                          Issue Type(ISSUED_TYPE_ID): #
                Buffer Overrun L2(BUFFER_OVERRUN_L2): 120
            Uninitialized Value(UNINITIALIZED_VALUE): 82
            Integer Overflow L2(INTEGER_OVERFLOW_L2): 36
                Buffer Overrun L1(BUFFER_OVERRUN_L1): 12
                Buffer Overrun L3(BUFFER_OVERRUN_L3): 5
  Inferbo Alloc May Be Big(INFERBO_ALLOC_MAY_BE_BIG): 2
