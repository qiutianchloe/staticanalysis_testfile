int main(){
    int x = 3; 
    int *p = &x;    
    free(p);
    free(p); 
}