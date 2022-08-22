/* some small test cases for rudimentary functionality for taking the
   address of a stack variable and then passing those addresses to functions.

   NOTE: this will do weird things if you do for instance (&x) + 1, etc.
         or you pass &x to a function that does pointer arithmetic.
*/
void use(int *p){
  *p = 5;
}

void isfive(int *p){
  if (*p == 5) {
  }
}

int test(){
  int x;
  int *p = &x;
  //use(&x);
  use(p+0);
  isfive(&x);
  return x;
}

int test2(int y){
  use(&y);
  return y;
}
