#define NULL ((void *)0); 
#define n 4
#define m 5
void another_fun(int a, int b){
	int result=a+b; 
}

// /*Test 1: use #define value*/
// void fun(){
// //1. Work: without using parameter
//   //int j = 0;
// //2. Work: use parameter to assign an value
//   //int j = n;
// //3. Work: use the parater doing the arithmetic operation
//   //int j = n+1;
// //4. Work:  use the parater doing the conditional operation
//   //int j = n>1;
// //5. Work:  use the parater doing the shift operation
//   //int j = n>>1;
// //6. Pointer to that variable 
//   //int *j = &n;
// //7. Work: loop 
//   // int j=0;
//   // int i = 0;  
//   // for (i = 0; i<n; i++){
//   //   j++;
//   // }
// //8. Work: issues inside the loop 
//   // int j; 
//   // while(j<n){
// 	 //    int *p = NULL;
// 	 //    int *q = *p; // null dereference
// 	 //    j++;
//   // }
// //9. use the parater doing the assignment operation
//   //n = n+1;
// //10. use the parater doing the conditional operation after assignment operation
//   //int j = n>1;
// //11. Work: with the variable that assigned to the parameter
//   // int j = n;
//   // int x = j>1;
// //12. Work: with two paramters' arithmetic operation 
//   //int j = n+m;
// //13. Not Work: with the two parameters' comparation operation
//   //int j = n<m;
// //14. Work: use in another function 
//   //another_fun(m, n); 
//   int *p = NULL;
//   int *q = *p; // null dereference
// }


// /*Test 2 use defined const value in call function*/
// void fun(int c, int d){
// //1. Work: without using parameter
//   //int j = 0;
// //2. Work: use parameter to assign an value
//   //int j = c;
// //3. Work: use the parater doing the arithmetic operation
//   //int j = c+1;
// //4. Work:  use the parater doing the conditional operation
//   //int j = c>1;
// //5. Work:  use the parater doing the shift operation
//   //int j = c>>1;
// //6. Work: Pointer to that variable 
//   //int *j = &c;
// //7. Work: loop !!!!!!!!
//   // int j=0;
//   // int i = 0;  
//   // for (i = 0; i<c; i++){
//   //   j++;
//   // }
// //8. Work: issues inside the loop 
//   // int j; 
//   // while(j<c){
// 	 //    int *p = NULL;
// 	 //    int *q = *p; // null dereference
// 	 //    j++;
//   // }
// //9. use the parater doing the assignment operation
//   //c = c+1;
// //10. use the parater doing the conditional operation after assignment operation
//   //int j = c>1;
// //11. Work: with the variable that assigned to the parameter
//   // int j = c;
//   // int x = j>1;
// //12. Work: with two paramters' arithmetic operation 
//   //int j = c+d;
// //13. Not Work: with the two parameters' comparation operation
//   //int j = c<d;
// //14. Work: use in another function 
//   //another_fun(c, d); 
//   int *p = NULL;
//   int *q = *p; // null dereference
// }

// int call(){
//   int const e = 3; 
//   int const f = 2; 
//   fun(e, f);
//   return 0;
// }
