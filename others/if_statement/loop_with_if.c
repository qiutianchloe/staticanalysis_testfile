#define NULL ((void*)0)

int fun(int t){   
    int i;
    int j=0;
    int f = 0;   
    for(i=0; i<4; i++){
        if(j<=t){
            // int *x = NULL;  // x is a null pointer
            // int y = *x;
            f++;
            return 3; 
        }else{
            // int *x = NULL;  // x is a null pointer
            // int y = *x;
            f--; 
        }
    // int *x = NULL;  // x is a null pointer
    // int y = *x;
    }
    int *x = NULL;  // x is a null pointer
    int y = *x;
    return 0; 
}

void call(){
    fun(3); 
}