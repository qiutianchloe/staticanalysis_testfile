int ackermann(int m, int n) {
  if (m==0) return n+1;
  if (n==0) return ackermann(m-1,1);
  return ackermann(m-1,ackermann(m,n-1));
}

int input();
_(presumes true covers result :: low)

void log(int n, int m);
_(presumes true covers true)
  
void main() {
  int m = input(), n = input();
  // choke point
  if ((m < 0 || m > 3) || (n < 0 || n > 23)) {
    log(n,m); // common branch
    return;
  } else {
    int r = ackermann(m,n); // rare branch
    _(assert (m < 2 || r >= 4))
  }
}
