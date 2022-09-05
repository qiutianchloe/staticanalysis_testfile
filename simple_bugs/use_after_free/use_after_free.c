#include "underflow.h"
#include <stdio.h>
int main(){
    int x = 3; 
    int y = 4; 
    int *p = &x; 
    free(p);
    printf("test %d\n", *p); 

    return 0; 
}