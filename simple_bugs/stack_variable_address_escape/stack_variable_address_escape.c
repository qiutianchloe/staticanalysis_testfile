int* foo() {
   int x = 42;
   return &x; // <-- warn here that "&x" will escape
}