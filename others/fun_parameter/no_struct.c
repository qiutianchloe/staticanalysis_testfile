#define NULL ((void *)0); 


/*Test 1: The fun() will execute even if there is no call to it*/

// void fun(int n, int m){
// //1. Work: without using parameter
//   //int j = 0;
// //2. Work: use parameter to assign an value
//   //int j = n;
// //3. Work: use the parater doing the arithmetic operation
//   //int j = n+1;
// //4. Not Work:  use the parater doing the conditional operation
//   //int j = n>1;
// //5. Work:  use the parater doing the shift operation
//   //int j = n>>1;
// //6. Work: Pointer to that variable 
//   //int *j = &n;
// //7. Not Work: loop 
//   // int j; 
//   // for (int i = 0; i<n; i++){
//   //   j++;
//   // }
// //8. Work: use the parater doing the assignment operation
//   //n = n+1;
// //9. Not Work: use the parater doing the conditional operation after assignment operation
//   //int j = n>1;
// //10. Not Work: with the variable that assigned to the parameter
//   //int j = n;
//   //int x = j>1;
// //11. Work: with two paramters' arithmetic operation 
//   //int j = n+m;
// //12. Not Work: with the two parameters' comparation operation
//   //int j = n<m;
//   int *p = NULL;
//   int *q = *p; // null dereference
// }

/*Test 2: The fun() will execute when there is a call to it and real number parameter*/
// int get_val_LOW();

// void fun(int n, int m){
// //1. Work: without using parameter
//   //int j = 0;
// //2. Work: use parameter to assign an value
//   //int j = n;
// //3. Work: use the parater doing the arithmetic operation
//   //int j = n+1;
// //4. Work!:  use the parater doing the conditional operation
//   //int j = n>1;
// //5. Work:  use the parater doing the shift operation
//   //int j = n>>1;
// //6. Work: Pointer to that variable 
//   //int *j = &n;
// //7. Not Work???????: loop 
//   // int j; 
//   // for (int i = 0; i<n; i++){
//   //   j++;
//   // }
// //8. Work: use the parater doing the assignment operation
//   //n = n+1;
// //9. Work!: use the parater doing the conditional operation after assignment operation
//   //int j = n>1;
// //10. Work!: with the variable that assigned to the parameter
//   // int j = n;
//   // int x = j>1;
// //11. Work: with two paramters' arithmetic operation 
//   //int j = n+m;
// //12. Work!: with the two parameters' comparation operation
//   //int j = n<m;
//   int *p = NULL;
//   int *q = *p; // null dereference
// }

// int main(){
//   int m = 1; 
//   int n = 2; 
//   fun(m, n);
//   return 0;
// }

/*Test 3: The fun() will execute when there is a call to it and initiallized but not real number parameter*/
// int get_val_LOW();

// void fun(int n, int m){
// //1. Work: without using parameter
//   //int j = 0;
// //2. Work: use parameter to assign an value
//   //int j = n;
// //3. Work: use the parater doing the arithmetic operation
//   //int j = n+1;
// //4. Work!:  use the parater doing the conditional operation
//   //int j = n>1;
// //5. Work:  use the parater doing the shift operation
//   //int j = n>>1;
// //6. Work: Pointer to that variable 
//   //int *j = &n;
// //7. Work!!!!!!!: loop 
//   // int j; 
//   // for (int i = 0; i<n; i++){
//   //   j++;
//   // }
// //8. Work: use the parater doing the assignment operation
//   //n = n+1;
// //9. Work!: use the parater doing the conditional operation after assignment operation
//   //int j = n>1;
// //10. Work: with the variable that assigned to the parameter
//   // int j = n;
//   // int x = j>1;
// //11. Work: with two paramters' arithmetic operation 
//   //int j = n+m;
// //12. Work!: with the two parameters' comparation operation
//   //int j = n<m;
//   int *p = NULL;
//   int *q = *p; // null dereference
// }

// int main(){
//   int m = get_val_LOW(); 
//   int n = get_val_LOW(); 
//   fun(m, n);
//   return 0;
// }

/*Test 4: The fun() will execute when the parameter is pass from another function's parameter*/

// void fun(int n, int m){
// //1. Work: without using parameter
//   //int j = 0;
// //2. Work: use parameter to assign an value
//   //int j = n;
// //3. Work: use the parater doing the arithmetic operation
//   //int j = n+1;
// //4. Not Work:  use the parater doing the conditional operation
//   //int j = n>1;
// //5. Work:  use the parater doing the shift operation
//   //int j = n>>1;
// //6. Work: Pointer to that variable 
//   //int *j = &n;
// //7. Not Work: loop 
//   // int j; 
//   // for (int i = 0; i<n; i++){
//   //   j++;
//   // }
// //8. Work: use the parater doing the assignment operation
//   //n = n+1;
// //9. Not Work: use the parater doing the conditional operation after assignment operation
//   //int j = n>1;
// //10. Not Work: with the variable that assigned to the parameter
//   // int j = n;
//   // int x = j>1;
// //11. Work: with two paramters' arithmetic operation 
//   //int j = n+m;
// //12. Not Work: with the two parameters' comparation operation
//   //int j = n<m;
//   int *p = NULL;
//   int *q = *p; // null dereference
// }

// int fun2(int a, int b, int c){
//   fun(b, c);
//   return 0;
// }


/*Test 5: The fun() will execute when there but not*/

// void fun(int n, int m);
// int fun2(){
//   int m = 1; 
//   int n = 2; 
//   fun(m, n);
//   return 0;
// }

// void fun(int n, int m){
// //1. Work: without using parameter
//   //int j = 0;
// //2. Work: use parameter to assign an value
//   //int j = n;
// //3. Work: use the parater doing the arithmetic operation
//   //int j = n+1;
// //4. Work!:  use the parater doing the conditional operation
//   //int j = n>1;
// //5. Work:  use the parater doing the shift operation
//   //int j = n>>1;
// //6. Work: Pointer to that variable 
//   //int *j = &n;
// //7. Not Work: loop 
//   // int j; 
//   // for (int i = 0; i<n; i++){
//   //   j++;
//   // }
// //8. Work: use the parater doing the assignment operation
//   //n = n+1;
// //9. Work!: use the parater doing the conditional operation after assignment operation
//   //int j = n>1;
// //10. Work!: with the variable that assigned to the parameter
//   // int j = n;
//   // int x = j>1;
// //11. Work: with two paramters' arithmetic operation 
//   // int j = n+m;
// //12. Work!: with the two parameters' comparation operation
//   // int j = n<m;
//   int *p = NULL;
//   int *q = *p; // null dereference
// }


