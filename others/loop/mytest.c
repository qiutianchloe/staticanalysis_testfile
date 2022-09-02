#define NULL ((void*)0)

int main(){   
    int i;
    int j=0;  
    for(i=0; i<4; i++){
        j++; 
    }
    int *x = NULL;  // x is a null pointer
    int y = *x; 
    return 0; 
}

/*
#define NULL ((void*)0)

int main(){   
    int i;
    int j=0;  
    for(i=0; i<4; i++){
        if(j<=0){
            j++;  
        }else{
            int *x = NULL;  // x is a null pointer
            int y = *x;
            j--; 
        }
    }
    return 0; 
}
*/