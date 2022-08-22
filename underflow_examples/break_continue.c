

int test1(){
  // manually set loop bound big enough to find the contract
  _(loop 7)
  int i = 0;
  while (1) {
    if (i == 12)
      break;
    if (i % 2 == 0) {
      i++;
      continue;
    }
    i+=3;
  }
  return i;
}
  
