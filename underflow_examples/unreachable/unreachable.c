#include "underflow.h"

/* a file full of intentionally unreachable contracts, to serve as a 
   bunch of regression tests. 
  
   For each function we expect to see Underflow report 0 contracts satisfied.

   If any of these become satisfiable, it indicates a likely bug in Underflow.
*/

// this contract should fail because there exists no path by which that result
// state can be reached: when result == 1, p |-> 5, not 10. 
int test(int *p)
  _(presumes exists int v. p |-> v covers p |-> v &*& v == 10 && result == 1)
{
  int x = *p;
  if (x == 5) return 1; else return 0;
}

// this contract should fail because the result also covers result states
// (e.g. in which x == 0 and result == x, not x+1) that cannot be reached
// from any initial state
int func3(int x)
  _(presumes true covers x >= 0 && (result == x+1))
{
  if(x > 0){
    return (x+1);
  }else{
    return x;
  }
}

/* this contract doesn't hold without an additional equality on y and v,
   e.g. in the result is sufficient */
int test2(int *p)
  _(presumes exists int v, int y. p |-> v covers p |-> y &*& result == 0)
{
  return 0;
}

/* the first contract doesn't hold because it doesn't constrain the result.
   the second one doesn't hold because it doesn't sufficiently constrain the result */
int blah()
  _(presumes true covers true)
  _(presumes true covers result >= 0)  
{
  return 0;
}

/* this contract is clearly unsatisfiable. But for Underflow to figure
   that it it needs to not existentially quantify x when testing the
   final x < 0 ==> x > 0, which took some care to get right in
   Prove.reachable() (see underflow/src/underflow/c/Prove.scala) */
void meh()
  _(presumes exists int x. x > 0 covers x < 0)
{
}
