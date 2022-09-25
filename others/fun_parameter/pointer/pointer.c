#define NULL ((void *)0); 

void another_fun(int* n, int* m){
	int result=*m+*n; 
}

/*Test 0: How pointer works inside the function*/
// void ptr_normal(){
// 	int num1 = 5; 
// 	int num2 = 6; 
// 	//1. declare an int pointer
// 	int *ptr1,*ptr2;  
// 	//2. assign value to the pointer 
// 	ptr1 = &num1; 
// 	ptr2 = &num2; 
// 	//3. access the value that this pointer is pointing to
// 	int result1 = *ptr1; 
// 	int result2 = *ptr2; 
// 	//4. store pointer in another pointer variable
// 	// int *ptr3 = ptr1; 
// 	//5. pointer to this pointer 
// 	// int **ptr4 = &ptr1; 
// 	//6. increment pointer operation 
// 	//ptr1++; 
// 	//7. decrement pointer operation
// 	//ptr1--; 
// 	//8. arithmetic operation to the value that store in the pointer
// 	//int result3 = result1+result2; 
// 	//9(1). work
// 	// if(*ptr1<20){
// 	// 	num2++; 
// 	// }
// 	//9(2). Work
// 	// if(*ptr1<*ptr2){
// 	// 	num2++; 
// 	// }
// 	//10.Work compare the value after assign to an variable
// 	// int j = result1<10;
// 	// int k = result1<result2; 
// 	//11. use the value that get from the pointer to execute the loop
// 	// int i = 0, l = 0; 
// 	// for(i=0; i<result2; i++){
// 	// 	l++;
// 	// }
// 	//12.Work compare pointer itself
// 	// if(ptr1>ptr2){
// 	// 	num1++; 
// 	// }
// 	//13. Work with comparsion with integer
// 	// if(ptr1==1){
// 	// 	//do nothing ;
// 	// }
// 	//int w = ptr1>3; //????????????????????????? it will detect 2 null-pointer dereference. 
// 	//14.Work use to call another function
// 	//another_fun(ptr1, ptr2); 
// 	int *p = NULL;
// 	int *q = *p; // null dereference
// }


/*Test 1: The fun() will execute even if there is no call to it*/

void fun(int* ptr1, int* ptr2){
	int f = 0; 
	//1. access the value that this pointer is pointing to
	int result1 = *ptr1; 
	int result2 = *ptr2; 
	//2. store pointer in another pointer variable
	//int *ptr3 = ptr1; 
	//3. pointer to this pointer 
	//int **ptr4 = &ptr1; 
	//4. increment pointer operation 
	//ptr1++; 
	//5. decrement pointer operation
	//ptr1--; 
	//6. arithmetic operation to the value that store in the pointer
	//int result3 = result1+result2; 
	//7(1). Not work
	// if(*ptr1<20){
	// 	// int *p = NULL;
	// 	// int *q = *p; // null dereference
	// 	f++
	// }
	//7(2). Not Work
	// if(*ptr1<*ptr2){
	// 	f++; 
	// }
	//8.Not Work. compare the value after assign to an variable
	// int j = result1<10;
	// int k = result1<result2; 
	//9.Not Work. use the value that get from the pointer to execute the loop
	// int i = 0, l = 0; 
	// for(i=0; i<result2; i++){
	// 	l++;
	// }
	//12.Not Work compare pointer itself
	// if(ptr1>ptr2){
	// 	num1++; 
	// }
	//13. Not Work with comparsion with integer
	// if(ptr1==1){
	// 	//do nothing ;
	// }
	//int w = ptr1>3; 
	//14.Work use to call another function
	//another_fun(ptr1, ptr2); 
	// int *p = NULL;
	// int *q = *p; // null dereference
}

/*Test 2: The fun() will execute when there is a call to it and real number parameter*/
// void fun(int* ptr1, int* ptr2){
// 	int f = 0; 
// 	//1. access the value that this pointer is pointing to
// 	int result1 = *ptr1; 
// 	int result2 = *ptr2; 
// 	//2. store pointer in another pointer variable
// 	//int *ptr3 = ptr1; 
// 	//3. pointer to this pointer 
// 	//int **ptr4 = &ptr1; 
// 	//4. increment pointer operation 
// 	//ptr1++; 
// 	//5. decrement pointer operation
// 	//ptr1--; 
// 	//6. arithmetic operation to the value that store in the pointer
// 	//int result3 = result1+result2; 
// 	//7(1). Work
// 	// if(*ptr1<20){
// 	// 	f++; 
// 	// }
// 	//7(2). Work
// 	// if(*ptr1<*ptr2){
// 	// 	f++; 
// 	// }
// 	//8.Work. compare the value after assign to an variable
// 	// int j = result1<10;
// 	//int k = result1<result2; 
// 	//9.Not Work. use the value that get from the pointer to execute the loop
// 	// int i = 0, l = 0; 
// 	// for(i=0; i<result2; i++){
// 	// 	l++;
// 	// }
// 	//10.Work compare pointer itself
// 	// if(ptr1>ptr2){
// 	// 	f++; 
// 	// }
// 	//11. Work with comparsion with integer
// 	// if(ptr1==1){
// 	// 	//do nothing ;
// 	// }
// 	//int w = ptr1>3; //????????????????????????? it will detect 2 null-pointer dereference. 
// 	//12.Work use to call another function
// 	//another_fun(ptr1, ptr2); 
// 	int *p = NULL;
// 	int *q = *p; // null dereference
// }

// int main(){
//   int o = 4; 
//   int p = 5; 
//   fun(&o, &p);
//   return 0;
// }

/*Test 3: The fun() will execute when there is a call to it and initiallized but not real number parameter*/
// int get_val_LOW();
// void fun(int* ptr1, int* ptr2){
// 	int f = 0; 
// 	//1. access the value that this pointer is pointing to
// 	int result1 = *ptr1; 
// 	int result2 = *ptr2; 
// 	//2. store pointer in another pointer variable
// 	//int *ptr3 = ptr1; 
// 	//3. pointer to this pointer 
// 	//int **ptr4 = &ptr1; 
// 	//4. increment pointer operation 
// 	//ptr1++; 
// 	//5. decrement pointer operation
// 	//ptr1--; 
// 	//6. arithmetic operation to the value that store in the pointer
// 	//int result3 = result1+result2; 
// 	//7(1). Work
// 	// if(*ptr1<20){
// 	// 	f++; 
// 	// }
// 	//7(2). Work
// 	// if(*ptr1<*ptr2){
// 	// 	f++; 
// 	// }
// 	//8.Work. compare the value after assign to an variable
// 	//int j = result1<10;
// 	//int k = result1<result2; 
// 	//9.Work. use the value that get from the pointer to execute the loop
// 	// int i = 0, l = 0; 
// 	// for(i=0; i<result2; i++){
// 	// 	l++;
// 	// }
// 	//10.Work compare pointer itself
// 	// if(ptr1>ptr2){
// 	// 	f++; 
// 	// }
// 	//11. Work with comparsion with integer
// 	// if(ptr1==1){
// 	// 	//do nothing ;
// 	// }
// 	//int w = ptr1>3; //????????????????????????? it will detect 2 null-pointer dereference. 
// 	//12.Work use to call another function
// 	// another_fun(ptr1, ptr2); 
// 	int *p = NULL;
// 	int *q = *p; // null dereference
// }

// int main(){
//   int o = get_val_LOW(); 
//   int p = get_val_LOW(); 
//   fun(&o, &p);
//   return 0;
// }
