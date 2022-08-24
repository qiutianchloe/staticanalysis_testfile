

void test(unsigned int x){
  if (++x >= 0){
  }
}

void test(unsigned char x){
  if (x >= 0){
  }
}

void test(unsigned char x){
  if (x >= 256){
  }
}

char retbig(){
  return 257;
}

void blah(){
  int x = retbig();
  _(assert x == 1)
}

char callmewithchar(char c){
  return (c+1);
}

int callmewithint(int i){
  return (i+1);
}


void testcalls(int i, char c){
  int i_copy = i;
  int c_copy = c;
  i = callmewithchar(i);
  c = callmewithint(c);
  _(assert i == (int)(((char)i_copy)+1))
  _(assert c == (char)(((int)c_copy)+1))
}

void testbig(){
  int x = 0xFFFFFFFF;
  _(assert x == -1)
}

void testlong(){
  // XXX: so far all literals are treated as 32-bits wide
  long x = -1;
  int xlow = x;
  int xhigh = (x >> 32);
  _(assert xlow == 0xFFFFFFFF)
  _(assert xhigh == 0xFFFFFFFF)    
}

void testU(){
  unsigned int x = 55U;
  _(assert x == 55)
}
