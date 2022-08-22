void fill_array(int *a, int n){
    int i=0; 
    for(i=0; i<n; i++){
        a[i]=i;
    }
}

void main(){
    int a[1]; 
    fill_array(a, 5); 
}

