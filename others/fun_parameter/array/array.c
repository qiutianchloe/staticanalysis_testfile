#define NULL ((void *)0); 

void another_fun(int* arr){
	int result=arr[0]; 
}

/*Test 0: Initialize the test use the normal array operation */
// void array_normal(){
// 	int f = 0; 
// 	//1.1 declare a function with initial value
// 	int arr[4] = {1, 2, 3, 4}; 
// 	//1.2 declare a function witout initial value, just array size
// 	//int arr[5]; 
// 	//2.1 change the value in a initialized array
// 	arr[2] = 10; 
// 	//2.2 assign the value in the memory space in the array
// 	//arr[0] = 1; 
// 	//arr[1] = 2; 
// 	//arr[2] = 3; 
// 	//arr[3] = 4; 
// 	//3. get the value from the array
// 	int val1 = arr[1]; 
// 	int val2 = arr[2];
// 	//Do the following operation to that value 
// 	//4. get its memory address
// 	// int *ptr1 = &arr[1]; 
// 	//5. arithmetic operation
// 	// int j = arr[1]+arr[2]; 
// 	//6. relational operation
// 	// int j = (arr[1]>1); 
// 	//7. shift <<
// 	// int j = arr[1]<<1; 
// 	//8. assignment operation 
// 	// arr[1] = arr[1]+1; 
// 	//9. relational operation after assignment operation
// 	// int j = (arr[1]>0); 
// 	//10. if statement
// 	// if(arr[1]>0){
// 	// 	f++; 
// 	// }
// 	//11. for loop
// 	// int i = 0; 
// 	// for(i = 0; i<arr[1]; i++){
// 	// 	f++; 
// 	// }
// 	//12. with two variables, do the arithmetic/relational operation
// 	// int j = arr[1]<arr[2]; 
// 	//13. use in another function 
// 	//another_fun(arr); 
// 	int *p = NULL;
// 	int *q = *p; // null dereference
// 	//return 0; 
// }


/*Test 1.1 test array as input and with size of the array*/
// void fun(int arr[4]){
// 	int f = 0; 
// 	//2.1 Work. change the value in a initialized array
// 	// arr[2] = 10; 
// 	//2.2 Work assign the value in the memory space in the array
// 	// arr[0] = 1; 
// 	// arr[1] = 2; 
// 	// arr[2] = 3; 
// 	// arr[3] = 4; 
// 	//3. Work. get the value from the array
// 	int val1 = arr[1]; 
// 	int val2 = arr[2];
// 	//Do the following operation to that value 
// 	//4. work. get its memory address
// 	// int *ptr1 = &arr[1]; 
// 	//5. work. arithmetic operation
// 	// int j = arr[1]+arr[2]; 
// 	//6. Not work. relational operation
// 	// int j = (arr[1]>1); 
// 	//7. Work. shift <<
// 	// int j = arr[1]<<1; 
// 	//8. Work. assignment operation 
// 	// arr[1] = arr[1]+1; 
// 	//9. Not work. relational operation after assignment operation
// 	// int j = (arr[1]>0); 
// 	//10. Not work. if statement
// 	// if(arr[1]>0){
// 	// 	f++; 
// 	// }
// 	//11. Not work. for loop
// 	// int i = 0; 
// 	// for(i = 0; i<arr[1]; i++){
// 	// 	f++; 
// 	// }
// 	//12. Not work.  with two variables, do the arithmetic/relational operation
// 	// int j = arr[1]<arr[2]; 
// 	//13. Work. use in another function 
// 	another_fun(arr); 
// 	int *p = NULL;
// 	int *q = *p; // null dereference
// }


// /*Test 1.2 test array as input and without the size of the input */
// void fun(int* arr){
// 	int f = 0; 
// 	//2.1 Work. change the value in a initialized array. It will not handle the potential issues of array out of bound. 
// 	//But underflow will! Hooray!
// 	//arr[2] = 10; 
// 	//2.2 Work assign the value in the memory space in the array
// 	// arr[0] = 1; 
// 	// arr[1] = 2; 
// 	// arr[2] = 3; 
// 	// arr[3] = 4; 
// 	//3. Work. get the value from the array
// 	int val1 = arr[1]; 
// 	int val2 = arr[2];
// 	//Do the following operation to that value 
// 	//4. work. get its memory address
// 	// int *ptr1 = &arr[1]; 
// 	//5. work. arithmetic operation
// 	// int j = arr[1]+arr[2]; 
// 	//6. Not work. relational operation
// 	// int j = (arr[1]>1); 
// 	//7. Work. shift <<
// 	// int j = arr[1]<<1; 
// 	//8. Work. assignment operation 
// 	// arr[1] = arr[1]+1; 
// 	//9. Not work. relational operation after assignment operation
// 	// int j = (arr[1]>0); 
// 	//10. Not work. if statement
// 	// if(arr[1]>0){
// 	// 	f++; 
// 	// }
// 	//11. Not work. for loop
// 	// int i = 0; 
// 	// for(i = 0; i<arr[1]; i++){
// 	// 	f++; 
// 	// }
// 	//12. Not work.  with two variables, do the arithmetic/relational operation
// 	// int j = arr[1]<arr[2]; 
// 	//13. use in another function 
// 	// another_fun(arr); 
// 	int *p = NULL;
// 	int *q = *p; // null dereference
// }

// /*Test 2 test array with initialized array */
// void fun(int* arr){
// 	int f = 0; 
// 	//2.1 Work. change the value in a initialized array. It will not handle the potential issues of array out of bound. 
// 	//But underflow will! Hooray!
// 	//arr[2] = 10; 
// 	//2.2 Work assign the value in the memory space in the array
// 	// arr[0] = 1; 
// 	// arr[1] = 2; 
// 	// arr[2] = 3; 
// 	// arr[3] = 4; 
// 	//3. Work. get the value from the array
// 	int val1 = arr[1]; 
// 	int val2 = arr[2];
// 	//Do the following operation to that value 
// 	//4. work. get its memory address
// 	// int *ptr1 = &arr[1]; 
// 	//5. work. arithmetic operation
// 	// int j = arr[1]+arr[2]; 
// 	//6. Work. relational operation
// 	// int j = (arr[1]>1); 
// 	//7. Work. shift <<
// 	// int j = arr[1]<<1; 
// 	//8. Work. assignment operation 
// 	// arr[1] = arr[1]+1; 
// 	//9. Work. relational operation after assignment operation
// 	// int j = (arr[1]>0); 
// 	// //10. If statement
// 	// if(arr[1]>0){
// 	// 	f++; 
// 	// }
// 	//11.Work. for loop !!!!!!!!!!
// 	// int i = 0; 
// 	// for(i = 0; i<arr[3]; i++){
// 	// 	f++; 
// 	// }
// 	//12. work.  with two variables, do the arithmetic/relational operation
// 	// int j = arr[1]<arr[2]; 
// 	//13. use in another function 
// 	// another_fun(arr); 
// 	int *p = NULL;
// 	int *q = *p; // null dereference
// }


// void fun2(){
// 	int arr[4] = {1,2,3,4}; 
//   	fun(arr);
// }


/*Test 3 test array with initialized array */
void fun(int* arr){
	int f = 0; 
	//2.1 Work. change the value in a initialized array. It will not handle the potential issues of array out of bound. 
	//But underflow will! Hooray!
	//arr[2] = 10; 
	//2.2 Work assign the value in the memory space in the array
	// arr[0] = 1; 
	// arr[1] = 2; 
	// arr[2] = 3; 
	// arr[3] = 4; 
	//3. Work. get the value from the array
	int val1 = arr[1]; 
	int val2 = arr[2];
	//Do the following operation to that value 
	//4. work. get its memory address
	// int *ptr1 = &arr[1]; 
	//5. work. arithmetic operation
	// int j = arr[1]+arr[2]; 
	//6. Work. relational operation
	// int j = (arr[1]>1); 
	//7. Work. shift <<
	// int j = arr[1]<<1; 
	//8. Work. assignment operation 
	// arr[1] = arr[1]+1; 
	//9. Work. relational operation after assignment operation
	// int j = (arr[1]>0); 
	// //10. If statement
	// if(arr[1]>0){
	// 	f++; 
	// }
	//11.Work. for loop !!!!!!!!!!
	// int i = 0; 
	// for(i = 0; i<arr[3]; i++){
	// 	f++; 
	// }
	//12. work.  with two variables, do the arithmetic/relational operation
	// int j = arr[1]<arr[2]; 
	//13. use in another function 
	// another_fun(arr); 
	int *p = NULL;
	int *q = *p; // null dereference
}


void fun2(){
	int arr[4];
  	fun(arr);
}





