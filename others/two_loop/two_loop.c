#define NULL ((void*)0)

void fun_with_issue(){
    int i;
    int j=0;  
    for(i=0; i<3; i++){
        j++; 
    }
    int *x = NULL;  // x is a null pointer
    int y = *x; 
}

int main(){   
    int i;
    int j=0;  
    for(i=0; i<4; i++){
        j++; 
    }
    // /*Once there is an issues, the second issue would not detect*/
    // int *p = NULL;  // p is a null pointer
    // int wrong = *p; 
    for(j=0; j<5; j++){
    	i++;
    }
    int *x = NULL;  // x is a null pointer
    int y = *x; 

    fun_with_issue();
    return 0; 
}