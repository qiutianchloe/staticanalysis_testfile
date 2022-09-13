#include "underflow.h"
int *malloc(int x);
_(presumes true covers result ==> exists int _v. result |-> _v)

void free(int *p);
_(presumes exists int _v. p |-> _v covers p |-\->)
_(presumes p |-\-> fails memory p |-\->)

void double_free(){
  int *p = malloc(4); // size is ignored
  if (p){
    free(p);
    free(p);
  }
}