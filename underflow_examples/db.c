typedef struct {
  int key;
  int value;
} elem_t;
int lookup(elem_t *elems, int len, int key, int *valueOut)
{
  int i = 0;
  elem_t *p = elems;
  int ret = 1;
  while (i < len && ret == 1)
    {
    if (p->key == key){
      *valueOut = p->value;
      ret = 0;
    }
    p++;
    i++;
  }
  return ret;
}
int binsearch(elem_t *elems, int len, int key, int *valueOut)
{
  if (len <= 0){
    return 1;
  }
  int mid = len/2;
  int k = (elems + mid)->key;
  if (k == key){
    *valueOut = (elems + mid)->value;
    return 0;
  }else{
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
  int sum = 0;
  elem_t *p = elems;
  int i = 0;
  while (i < len)
    {
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
void remove_all(elem_t *elems, int len, int key)
{
  int i = 0;
  elem_t *p = elems;
  while (i < len)
  {
    int k = p->key;
    if (k == key){
      p->value = 0;
    }
    p++;
    i++;
  }
}
