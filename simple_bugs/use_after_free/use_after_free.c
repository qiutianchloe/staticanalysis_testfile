int main(){
    char* p = malloc(1024 * 1024);
    free(p);
    free(p); 
}