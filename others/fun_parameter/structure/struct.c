#include <stdio.h>
#include <stdlib.h>
  
struct Node {
    int data;
    int* ptr; 
    int arr[2];  
    struct Node* next;
};

/*Without initialized the struct*/
// void use_struct(struct Node* node)
// {
//    /*1. test the integer*/
//    // 0. Work.  access the the integer
//    int n = node ->data; 
//    // 1. Work: without using parameter
//    //   int j = 0;
//    // 2. Work: use parameter to assign an value
//      // int j = n;
//    // 3. Work: use the parater doing the arithmetic operation
//      // int j = n+1;
//    // 4. Not Work:  use the parater doing the conditional operation
//      // int j = n>1;
//    // 5. Work:  use the parater doing the shift operation
//      // int j = n>>1;
//    // 6. Work: Pointer to that variable 
//      // int *j = &n;
//    // 7. Not Work: loop 
//      // int j=0;
//      // int i = 0;  
//      // for (i = 0; i<n; i++){
//      //   j++;
//      // }
//    // 8. Not Work: issues inside the loop 
//      // int j=0; 
//      // while(j<n){
//      //      int *p = NULL;
//      //      int *q = *p; // null dereference
//      //      j++;
//      // }
//    // 9. Work: use the parater doing the assignment operation
//      // n = n+1;
//    // 10. Not Work: use the parater doing the conditional operation after assignment operation
//      // int j = n>1;
//    // 11. Not Work: with the variable that assigned to the parameter
//      // int j = n;
//      // int x = j>1;

//    /*1. test the pointer*/
//    // int f = 0; 

//    // int *ptr1 = node ->ptr;  
//    // int result1 = *ptr1;
//    //2. work. store pointer in another pointer variable
//    //int *ptr3 = ptr1; 
//    //3. Work/ pointer to this pointer 
//    //int **ptr4 = &ptr1; 
//    //4. Work ncrement pointer operation 
//    // ptr1++; 
//    //5. Work. decrement pointer operation
//    //ptr1--; 
//    //7(1). Not work
//    // if(*ptr1<20){
//    //    // int *p = NULL;
//    //    // int *q = *p; // null dereference
//    //    f++;
//    // }
//    //7(2). Not Work
//    // if(*ptr1<*ptr2){
//    //    f++; 
//    // }
//    //8.Not Work. compare the value after assign to an variable
//    // int j = result1<10;
//    //9.Not Work. use the value that get from the pointer to execute the loop
//    // int i = 0, l = 0; 
//    // for(i=0; i<result1; i++){
//    //    l++;
//    // }
//    //12.Not Work compare pointer itself
//    // if(ptr1>ptr2){
//    //    num1++; 
//    // }
//    //13. Not Work with comparsion with integer
//    // if(ptr1==1){
//    //    //do nothing ;
//    // }
//    // int w = ptr1>3; 
//    //14.Work use to call another function
//    //another_fun(ptr1, ptr2); 
//    // int *p = NULL;
//    // int *q = *p; // null dereference

//    /*3. test the the array*/
//    int f = 0; 
//    //1. access the array from the struct
//    int* arr = node->arr; 
//    //2.1 Work. change the value in a initialized array
//    arr[1] = 10; 
//    //3. Work. get the value from the array
//    int val1 = arr[0]; 
//    int val2 = arr[1];
//    //Do the following operation to that value 
//    //4. work. get its memory address
//    // int *ptr1 = &arr[1]; 
//    //5. work. arithmetic operation
//    // int j = arr[1]+arr[2]; 
//    //6. Not work. relational operation
//    // int j = (arr[1]>1); 
//    //7. Work. shift <<
//    // int j = arr[1]<<1; 
//    //8. Work. assignment operation 
//    // arr[1] = arr[1]+1; 
//    //9. Work!!!!!!!!! relational operation after assignment operation
//    //int j = (arr[1]>0); 
//    //10. Work!!!!!!!!!!. if statement
//    // if(arr[1]>0){
//    //    f++; 
//    // }
//    //11. Not work. for loop
//    // int i = 0; 
//    // for(i = 0; i<arr[1]; i++){
//    //    f++; 
//    // }
//    //12. Not work.  with two variables, do the arithmetic/relational operation
//    // int j = arr[1]<arr[0]; 


//    /*4. test the struct itself*/
//    //Not working!
//     while (node != NULL) {
//         printf(" %d ", node->data);
//         node = node->next;
//     }
//   int *p = NULL;
//   int *q = *p; // null dereference
// }


/*Initialized the struct*/
void use_struct(struct Node* node)
{
   /*1. test the integer*/
   // 0. Work.  access the the integer
   int n = node ->data; 
   // 1. Work: without using parameter
     // int j = 0;
   // 2. Work: use parameter to assign an value
     // int j = n;
   // 3. Work: use the parater doing the arithmetic operation
     // int j = n+1;
   // 4. Work:  use the parater doing the conditional operation
     // int j = n>1;
   // 5. Work:  use the parater doing the shift operation
     // int j = n>>1;
   // 6. Work: Pointer to that variable 
     // int *j = &n;
   // 7. Work!!!!: loop 
     // int j=0;
     // int i = 0;  
     // for (i = 0; i<n; i++){
     //   j++;
     // }
   // 8. Work: issues inside the loop 
     // int j=0; 
     // while(j<n){
     //      int *p = NULL;
     //      int *q = *p; // null dereference
     //      j++;
     // }
   // 9. Work: use the parater doing the assignment operation
     // n = n+1;
   // 10. Work: use the parater doing the conditional operation after assignment operation
     // int j = n>1;
   // 11. Work: with the variable that assigned to the parameter
     // int j = n;
     // int x = j>1;

   /*1. test the pointer*/
   int f = 0; 

   // int *ptr1 = node ->ptr;  
   // int result1 = *ptr1;
   //2. work. store pointer in another pointer variable
   // int *ptr3 = ptr1; 
   //3. Work/ pointer to this pointer 
   // int **ptr4 = &ptr1; 
   //4. Work ncrement pointer operation 
   // ptr1++; 
   //5. Work. decrement pointer operation
   // ptr1--; 
   //7(1). work
   // if(*ptr1<20){
   //    // int *p = NULL;
   //    // int *q = *p; // null dereference
   //    f++;
   // }
   //7(2). Not Work
   // if(*ptr1<*ptr2){
   //    f++; 
   // }
   //8.Work. compare the value after assign to an variable
   // int j = result1<10;
   //9.Work. use the value that get from the pointer to execute the loop
   // int i = 0, l = 0; 
   // for(i=0; i<result1; i++){
   //    l++;
   // }
   //12.Not Work compare pointer itself
   // if(ptr1>ptr2){
   //    num1++; 
   // }
   //13.Work with comparsion with integer
   // if(ptr1==1){
   //    //do nothing ;
   // }
   // int w = ptr1>3; 
   //14.Work use to call another function
   // another_fun(ptr1, ptr2); 

   // /*3. test the the array*/
   // int f = 0; 
   // //1. access the array from the struct
   int* arr = node->arr; 
   // //2.1 Work. change the value in a initialized array
   // arr[1] = 10; 
   // //3. Work. get the value from the array
   // int val1 = arr[0]; 
   // int val2 = arr[1];
   //Do the following operation to that value 
   //4. work. get its memory address
   // int *ptr1 = &arr[1]; 
   //5. work. arithmetic operation
   // int j = arr[1]+arr[2]; 
   //6. Not work. relational operation
   // int j = (arr[1]>1); 
   //7. Work. shift <<
   // int j = arr[1]<<1; 
   //8. Work. assignment operation 
   // arr[1] = arr[1]+1; 
   //9. Work!!!!!!!!! relational operation after assignment operation
   // int j = (arr[1]>0); 
   //10. Work!!!!!!!!!!. if statement
   // if(arr[1]>0){
   //    f++; 
   // }
   //11. work. for loop
   // int i = 0; 
   // for(i = 0; i<arr[1]; i++){
   //    f++; 
   // }
   //12. Not work.  with two variables, do the arithmetic/relational operation
   // int j = arr[1]<arr[0]; 


   /*4. test the struct itself*/
   //working!
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
  int *p = NULL;
  int *q = *p; // null dereference
}

int main()
{
   int one = 1; 
   int two = 2; 
   int three = 3; 
   struct Node* head = NULL;
   struct Node* second = NULL;
   struct Node* third = NULL;

   // allocate 3 nodes in the heap
   head = (struct Node*)malloc(sizeof(struct Node));
   second = (struct Node*)malloc(sizeof(struct Node));
   third = (struct Node*)malloc(sizeof(struct Node));
   assert(head!=NULL); 
   assert(second!=NULL); 
   assert(third!=NULL); 


   head->data = 1; // assign data in first node
   head->ptr = &one; 
   head->arr[0] = 0; 
   head->arr[1] = 1; 
   head->next = second; // Link first node with

   // assign data to second node
   second->data = 2;
   second->ptr = &two; 
   second->arr[0] = 2; 
   second->arr[1] = 3; 
   // Link second node with the third node
   second->next = third;

   third->data = 3; // assign data to third node
   second->ptr = &three; 
   second->arr[0] = 4; 
   second->arr[1] = 5; 
   third->next = NULL;

   use_struct(head); 
   free(head); 
   free(second); 
   free(third); 
   return 0;
}