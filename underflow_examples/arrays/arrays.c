#include "underflow.h"
void main(){
  char array[5] = {1};
  char b = array[2];
  _(assert b == 1)
}



void memset32(int *p, int v, int n){
  int i;
  for (i=0;i<n;i++){
    p[i] = v;
  }
}

void main2_error(){
  int array[10];
  memset32(array+1,4,10);
}
