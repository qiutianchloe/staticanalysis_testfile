#define NULL ((void*)0)

typedef struct {
  int key;
  int value;
} elem_t;

int lookup(elem_t *elems, int len, int key, int *valueOut)
{
//Test1: Work
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  int i = 0;
  elem_t *p = elems;
  int ret = 1;
//Test2: Work
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  while (i < len && ret == 1)
    {
//Test3: Do not work cause there is no function called this function 
    // int *o = NULL;  // x is a null pointer
    // int blah = *o; 
    if (p->key == key){
      *valueOut = p->value;
      ret = 0;
    }
    p++;
    i++;
  }
//Test4: Do not work cause there is no function called this function, so the function won't work after the while loop 
    // int *o = NULL;  // x is a null pointer
    // int blah = *o; 
  return ret;
}
int binsearch(elem_t *elems, int len, int key, int *valueOut)
{
//Test5: work
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
//   if (len <= 0){
// //Test6: Do not work cause there is no function called this function, so the function won't work after the while loop 
//     // int *o = NULL;  // x is a null pointer
//     // int blah = *o; 
//     return 1;
//   }
//Test7: Do not work cause there is no function called this function, but work after delete the if statement lines before
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  int mid = len/2;
  int k = (elems + mid)->key;
//Test8: Do not work cause there is no function called this function, but work after delete the if statement lines before
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  if (k == key){
//Test9: Works
    // int *o = NULL;  // x is a null pointer
    // int blah = *o; 
    *valueOut = (elems + mid)->value;
//Test10: Works
    // int *o = NULL;  // x is a null pointer
    // int blah = *o; 
    return 0;
  }else{
//Test11: Do not Works
    // int *o = NULL;  // x is a null pointer
    // int blah = *o; 
    if (len == 1){
      return 1;
    }
    if (k > key){
      int ret = binsearch(elems,mid-1,key,valueOut);
      return ret;
    }else{
      int ret = binsearch(elems+mid+1,len - mid - 1,key,valueOut);
      return ret;
    }
  }
}
int sum_all(elem_t *elems, int len, int key)
{
//Test13: Works
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  int sum = 0;
  elem_t *p = elems;
  int i = 0;
//Test14: Works
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  while (i < len)
    {
//Test15: Do not Work as expect
    // int *o = NULL;  // x is a null pointer
    // int blah = *o; 
    int k = p->key;
    int v = p->value;
    if (k == key){
      sum += v;
    }
    p++;
    i++;
  }
  return sum;
}
/*
int sum_all_rec(elem_t *p, int len, int key, int init)
{
  if (len > 0)
  {
    int k = p->key;
    int v = p->value;
    if (k == key){
      int s = sum_all_rec(p+1,len-1,key,init + v);
      return s;
    }else{
      int s = sum_all_rec(p+1,len-1,key,init);
      return s;
    }
  }else{
    return init;
  }
}
*/
void remove_all(elem_t *elems, int len, int key)
{
//Test16: Work as expect
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  int i = 0;
  elem_t *p = elems;
//Test17: Work as expect
  // int *o = NULL;  // x is a null pointer
  // int blah = *o; 
  while (i < len)
  {
//Test18: Do not Work as expect
    // int *o = NULL;  // x is a null pointer
    // int blah = *o; 
    int k = p->key;
    if (k == key){
      p->value = 0;
    }
    p++;
    i++;
  }
}
