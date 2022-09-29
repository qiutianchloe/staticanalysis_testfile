#include "underflow.h"
#define NULL ((void*)0)

void test1(unsigned int x){
//Test1: Work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
  if (++x >= 0){
//Test2: Work here
    // int *p = NULL;  // x is a null pointer
    // int blah = *p; 
  }
}

void test2(unsigned char x){
//Test3: Work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
  if (x >= 0){
//Test4: Do not work here
    // int *p = NULL;  // x is a null pointer
    // int blah = *p; 
  }
}

void test3(unsigned char x){
//Test5: Work here
  // int *p = NULL;  // x is a null pointer
  // int blah = *p; 
  if (x >= 256){
//Test6: Do not work here
    // int *p = NULL;  // x is a null pointer
    // int blah = *p; 
  }
}

char retbig(){
//Test7: work here
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  return 257;
}

void blah(){
  int x = retbig();
//Test8: work here
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  _(assert x == 1)
//Test10: work here
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
}

char callmewithchar(char c){
//Test10: work here
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  return (c+1);
}

int callmewithint(int i){
//Test11: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  return (i+1);
}


void testcalls(int i, char c){
//Test12: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  int i_copy = i;
  int c_copy = c;
  i = callmewithchar(i);
  c = callmewithint(c);
//Test13: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  _(assert i == (int)(((char)i_copy)+1))
  _(assert c == (char)(((int)c_copy)+1))
//Test14: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
}

void testbig(){
  int x = 0xFFFFFFFF;
//Test15: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  _(assert x == -1)
//Test16: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
}

void testlong(){
//Test17: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  long x = -1;
  int xlow = x;
  int xhigh = (x >> 32);
  _(assert xlow == 0xFFFFFFFF)
  _(assert xhigh == 0xFFFFFFFF)
//Test18: work
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  unsigned long y = 0xEFFFFFFFFFFFFFFFUL;
  unsigned int ylow = y;
  unsigned int yhigh = (y >> 32);
//Test19: Do not work here
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  _(assert ylow == 0xFFFFFFFF)
 _(assert yhigh == 0xEFFFFFFF)
//Test20: 
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
}

void testU(){
//Test21: 
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
  unsigned int x = 55U;
  _(assert x == 55)
//Test22: 
  // int *p = NULL;  // x is a null pointer
  // int blah = *p;
}


