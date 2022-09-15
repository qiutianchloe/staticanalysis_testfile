#include "underflow.h"

/* the current semantics of Underflow is as follows: 

   It has two modes of operation: "validate" mode and "discover" mode.

   Validate Mode:
   -------------

   Validate mode is the default. In this mode:

   Each _(presumes P covers Q) or 
        _(presumes P fails kind Q) for each function forms a specification.
  
   /kind/ is either "memory" (for memory-safety errors) or "insecure" for
   information flow errors.
   
   Underflow then symbolically executes from P. For each /kind/ final state T
   reached, it checks whether T is consistent and whether (exists vs. T(old)) <== Q,
   where T(old) denotes T but with all function arguments referring to their *initial*
   values, and vs are local variables in state T. If this implications holds for any 
   such final state, the contract is satisfied.

   We check Q ==> (exists vs. T(old)) for two reasons:
   1. We use T(old) rather than T because we are proving a contract that we wish to refer
      to the function's *external* behaviour: when a caller calls the function it does not
      see modifications to local variables like paramters. 
   2. This also explains why we use (exists vs. ...) because the vs are local variables that 
      are not visible outside the function.

   The upshot of this is that when we write:
   _(presumes P (covers | fails blah) Q) any (non-spatial) constraints that Q places on the 
   function arguments can effectively be treated as a precondition since this triple says for 
   all states that satisfy Q, there exists a state satisfying P that can reach the Q-state.

   For this reason, the presumption P often looks weaker than one might expect, but that is
   no problem because all useful information can be put into the result Q without loss of
   fidelity. Indeed if Q' is the pure part of Q, we have that if
   _(presumes P (covers | fails blah) Q) holds, then it follows that
   _(presumes P &*& Q' (covers | fails blah) Q) must also hold.

   Note that in Underflow's current implementation, for contracts that want to quantify over 
   logical variables, the variable should be introduced via "exists" in the presumption, 
   and can then be referred to freely in the result, for instance:
   _(presumes exists x. P covers Q) where P and Q mention x, means
   forall x. _(presumes P covers Q)

   If any contract is not satisfied, Underflow reports that the contract is unreachable. 
   XXX: at present this happens for any function for which symbolic execution
        cannot find any consistent final state.

   Underflow will use bi-abduction based symbolic execution (SE)
   to strengthen specifications as needed to progress symbolic execution and
   to help it discover as many paths as it can. 

   Discover Mode:
   --------------

   In Discover mode (enabled via the -discover option), Underflow uses SE to
   infer as many contracts as it can for each function. When function f calls
   function g, it uses the contracts on function g to progress symbolic
   execution, so its ability to discover contracts for function f will depend on
   the quality of the contracts for those functions f calls.   

   Command-line options (all optional):
   ------------------------------------

     -strengthen

     Supplying the -strengthen option causes Underflow to back-propagate non-spatial assertions,
     which at present it does not do by default as such information always shows up in the
     result anyway and so avoids duplication in the discovered contracts


     -discover

     Runs Underflow is discover mode (see above).


     -loop N

     For a positive integer N, defines how many times to unroll loops.


     -timeout Nmillisecs

     For a positive integer Nmillisecs defines the solver timeout in
     milliseconds.
*/

/* Note, from above, that the "covers" (likeewise "fails") condition refers to the 
   *initial* values of parameters, and can also refer to a distinguished variable called "result"
   that denotes the return-value (if the function has one). */


/* note that in under-approximate logics like InsecSL (Insecurity
   Separation Logic) the result assertion must imply the final state,
   which is the reverse for ordinary Hoare logic. This is why we use
   the keyword 'covers', to sugges that the final states reachable
   cover the case e.g. as below in which x > 1, under the presumption
   that e.g. x > 0. */
void test_conseq(int x)
  _(presumes x > 0 covers x > 1)
{
}

/* when calling a function, we conjoin the non-spatial part of its presumption
   with the current state, to make its presumption valid. This works because
   the consequence rule of under-approximate logic allows us to strengthen the
   current presumption (at odds which Hoare logic, in which one can only weaken
   the current precondition). Specifically, from x > 2 we conjoin x > 0 to obtain
   x > 2 && x > 0. We then let x > 2 be the frame and execute the function, to obtain
   x > 1 && x > 2 && x > 0. The final covers is satisfied because x == 5 ==> x > 2. */
void test_conseq2(int x)
  _(presumes x > 2 covers x == 5)
{
  test_conseq(x);
}


/* the first contract is what one would expect to characterise the path through this
   function in which it returns 1.
   The second contract is an insecurity contract stating that this function is insecure and
   leaks the value of (b > 0) to the attacker (by branching on it) */
int test1(int b)
  _(presumes true covers b > 0 && result == 1)
  _(presumes true fails insecure (b > 0) :!: attacker)  
{
  if (b > 0){
    return 1;
  }else{
    return 0;
  }
}


/* This function is likewise insecure, even if the attacker is allowed to know whether
   (b > 0) since on the second loop iteration is leaks (b - 1 > 0) which might contain more
   information than b > 0 (e.g. consider two initial values for b being 1 and 2).
   Note that for two values of b that are not > 0, (b - 1 > 0) :: attacker. Hence,
    (b > 0) :: attacker && (b - 1 > 0) :!: attacker implies that b > 0 holds. Hence
   we do not need to say that explicitly in the result assertion (covers) here */
int test2(int b)
  _(presumes true fails insecure (b > 0) && (b - 1 > 0) :!: attacker)
{
  while (b > 0){
    b--;
  }
  return b;
}

/* At present in Underflow each result assertion can refer to only path, hence the commented-out
   contract below does not hold and instead we need to specify two separate ones. */
int test3(int b)
//_(presumes true covers (b > 0) :: low && (result == 0 || result == 1))
  _(presumes true covers b > 0 && result == 1)
  _(presumes true covers b <= 0 && result == 0)
{
  if(b > 0){
    return 1;
  }else{
    return 0;
  }
}


/* changing the covers to result == 1 gives the error that that case
   is unreachable */
int test4()
  _(presumes true covers result == 0)
{
  if (0){
    return 1;
  }

  return 0;
}

/* there are two possibilities for this function that we can express: 
   (1) either it immediately finishes (x == 0), or
   (2) it immediately leaks information.

   The third commented-out contract does not hold because there exists no final
   consistent state implied by x != 0.
*/  
void run_forever(int x)
  _(presumes true covers x == 0)
  _(presumes true fails insecure (x == 0) :!: attacker)
//_(presumes true covers x != 0)
{
  while(x){
  }
}


/* this function is behaves insecurely whenever (x == 0) is not known to the attacker,
   because it leaks that information. */
int run_forever2(int x)
  _(presumes true fails insecure (x == 0) :!: attacker)
{
  while(1){
    if (x){
    }
  }
}


/* a few memory safety examples, since InsecSL also detects memory
   safety problems, similarly to how Incorrectness Separation Logic
   (ISL) does. The contract for the `free` function says that it will
   run successfully if given a valid pointer and, afterwards, the
   pointer will be invalid. However it will fail with a memory error
   if the given pointer is invalid. */
void free(int * p);
  _(presumes exists int v. p |-> v covers p |-\->)
  _(presumes p |-\-> fails memory p |-\->)


void do_free(int * p)
  _(presumes exists int v. p |-> v covers (p + 0) |-\->)
{
  free(p);
}

/* detect write after free */
void do_free_use(int * p)
  _(presumes exists int v. p |-> v fails memory p |-\->)
{
  free(p);
  p[0] = 0;
}

/* detect read after free */
void do_free_use2(int * p)
  _(presumes exists int v. p |-> v fails memory p |-\->)
{
  free(p);
  int x = *(p + 0);
}

/* detect double-free */
void double_free(int * p)
  _(presumes exists int v. p |-> v fails memory p |-\->)
{
  free(p);
  free(p);
}


/* Examples from the under-approximate relational logic on IMP, 
   originally inspired by examples in O'Hearn, PACMPL 2019 (POPL 2020) */
int get_y(int n);
  _(presumes true covers result :: low && n :: low && n > 0)

/* mimics the command to output on the low channel. Its contract says
   that calling this function is insecure if the argument is not low
   (i.e. not known to the low attacker). We specify this using the
   /insecurity/ assertion :!:. Just as |-\-> is the invalid
   counterpart to |->, :!: is the invalid counterpart to ::, the
   security assertion. 

   Remember that non-spatial assertions in the 'covers / fails' part should be
   read as "preconditions" */
void output_low(int x);
  _(presumes true fails insecure x :!: low)
  _(presumes true covers x :: low)

/* the insecurity of this example can be demonstrated by unfolding the
   loop just once, when the non-low value h is output to the low
   attacker, when n was initially 2000000 */
void example2(int n, int h)
  _(presumes true fails insecure n == 2000000 && h :!: low)
{
  int x = 0;
  while (n > 0){
    x = x + n;
    n = get_y(n);
  }
  if (x == 2000000){
    output_low(h);
  }
}

/* this example does not demonstrate insecurity (under the contract
   for get_y above), since then we can conclude that the loop guard n
   is always low and x is always low, hence the if-condition and 
   outputting x are both secure. */
void example2_secure(int n)
  _(presumes true covers n == 2000000)
{
  int x = 0;
  while (n > 0){
    x = x + n;
    n = get_y(n);
  }
  if (x == 2000000){
    output_low(x);
  }
}
void load_and_output(int *p)
  _(presumes exists int v2. p |-> v2 covers exists int v. p |-> v &*& v :: low)
{
  int x = *p;
  output_low(x);
}


/* Notice how we put the information about v being low into the result.
   That is totally OK since v is a logical variable, i.e. like an argument
   its value once the function finishes is the same as when it began, so
   knowing v :: low in the result implies we could put it into the
   presumption too.

   However in its current implementation Underflow doesn't back-propagate
   the v :: low into the presumption (even when -strengthen is supplied)
   because it doesn't back-propagate information obtained from the result
   of a callee (like output_low() in this case, where v :: low comes from)
*/
void load_and_output_and_zero(int *p)
  _(presumes exists int v. p |-> v covers p |-> 0 &*& v :: low)
{
  int x = *p;
  output_low(x);
  *p = 0;
  // ...  other stuff here ...
}


/* a false negative due to under-approximation. To detect this
   we would need to implement a version of the backwards variant
   rule and allow the user to supply (or automatically infer) the
   backwards variant (or unroll the loop four million times) 

   Note that the trivial contract below is not currently validated
   because Underflow regards any contract as false when it cannot find
   any consistent result state, even if the result assertion itself is
   unsatisfiable. That limitation we might remove in future. */
void false_negative(int high)
//_(presumes true covers true)
{
  int x = 0;
  while (x < 4000000){
    x++;
    if (x == 2000000){
      output_low(high);
    }
  }
}

/* This example /rightly/ has an assertion violation.  This was very
   surprising to me but (after extracting the model from Z3) the
   reason has to do with the meaning of x > 0 ? (x > 0)::low :
   (x>0)::low There are two cases: the first case is when x > 0 is
   true. This means that x > 0 holds in both states. In that case of
   course (x > 0)::low holds.  The other case is when x > 0 is not
   true. Note that is /not/ the same as !(x>0) being true. The former
   just means that x > 0 does not evaluate true in both states.  In
   that case it is not true that (x > 0)::low holds. So the negation
   of the assertion is rightly satisfiable */
int curious(int x)
  _(presumes true fails assertion !((x > 0)?(x > 0)::low:(x>0)::low))
{
  _(assert ((x > 0)?(x > 0)::low:(x>0)::low))
  return (x > 0);
}


/* Note, however, that this function does /not/ have a violated
   assert, despite the above discussion. The reason is because 
   (x > 0) ? (x > 0) : (!(x>0)) is interpreted as a pure 
   (non-relational) condition  and so it holds when it holds in 
   both states individually, which of course it does. In other
   words the assertion is a tautology. */
int curious_no_violated_assert(int x)
  _(presumes true covers result == (x > 0))
{
  _(assert ((x > 0)?(x > 0):(!(x>0))))
  return (x > 0);
}

/* this one has no violated assert (although it is insecure). The
   reason is because by nature it only considers the two cases in
   which x > 0 is either true in both states or is false in both
   states. */
int curious_no_violated_assert2(int x)
  _(presumes true covers x > 0 && result == (x > 0))
  _(presumes true covers x <= 0 && result == (x > 0))  
{
  if (x > 0){
    _(assert (x > 0)::low)
  } else {
    _(assert (x > 0)::low)
  }
  return (x > 0);
}


/* multiple kinds of failures, each with thier own contract. */
void error_and_insecure(int x, int *p)
  _(presumes exists int v. p |-> v covers p |-\-> &*& x :: low)
  _(presumes p |-\-> fails memory p |-\->)
  _(presumes exists int v. p |-> v fails insecure p |-\-> &*& x :!: low)
{
  free(p);
  output_low(x);
}



/* The 'push-back' example from the ISL paper
 * Fig 2., Raad et al., CAV 2020
 */

int **palloc();
_(presumes true covers exists int * p, int v. result |-> p &*& p |-> v)

int *alloc();
_(presumes true covers exists int v. result |-> v)


int nondet();
_(presumes true covers result :: low)

/* Note that variables introduced via "exists" in presumptions can be freely referred to
   in the result, and this is Underflow's way of universally quantifying over such. */
void push_back(int **v)
_(presumes exists int *p, int v2. v |-> p &*& p |-> v2 covers exists int *r, int _r. p |-\-> &*& v |-> r &*& r |-> _r)
{
  if (nondet()){
    int *y = *v;
    free(y);
    y = alloc();
    *v = y;
  }
}

/* Underflow does in fact detect the failure here (use the -discover option to see it).
   However there is no way for us to write the contract so that Underflow will match it
   because it currently doesn't know how to match spatial assertions p |-> ? or p |-\-> 
   in the contract's result when p is existentially quantified and is not determined by some
   other points-to assertion.  */
void isl_push_back()
//_(presumes true fails memory exists int* r, int _r, int** re, int* p. r |-> _r && re |-> r && p |-\->)
{
    int **v = palloc();
    int *x = *v;
    push_back(v);
    //HERE!
    *x = 88;
}


/* The following commented covers illustrates a limitation of Underflow's current
   design. Note that the contract below is met by this function: for
   all final states in which b < 5, there exists an initial state
   identical to that final one in which the final state can be reached
   by running this function.

   However Underflow cannot determine this. The reason is because the
   if-statement causes it to fork the execution and the final contract
   is evaluated against each final state individually (rather than e.g. taking
   the disjunction of all final states and evaluating the contract against
   that).

   Specifically, the current Underflow implementation says the contract is
   satisfied only when one of the following two conditions hold:
   (1) b > 0     <==    b < 5 
   (1) b <= 0    <==    b < 5
   Of course neither of them do. However if we took the disjunction of the
   final states we would instead have to prove:
   (*) b > 0  || b <= 0    <==   
       b < 5 
   which does hold.

   We leave it as future work to extend Underflow's implementation to handle
   proving these kinds of contracts.
*/   
void limitedIF(int b)
  _(presumes true covers b > 0)
//_(presumes true covers b < 5)
{
  if (b > 0)
    ;
}

/* Note that when SE strengthens a presumption with non-spatial assertions
   it means the original contract did not hold. Underflow will report it therefore
   as unreachable e.g. in the case of the commented-out contract below */
void error_and_insecure2(int x, int *p)
  _(presumes exists int v. p |-> v &*& x :: low covers p |-\-> &*& x :: low)
  _(presumes p |-\-> fails memory p |-\->)
  _(presumes exists int v. p |-> v fails insecure x :!: low &*& p |-\->)
//_(presumes true fails insecure x :!: low &*& p |-\->)
{
  free(p);
  output_low(x);
}

int func2(int x)
  _(presumes x >= 0 covers x >= 0 && result == x+1)
  _(presumes true covers x < 0 && result == x)
{
  if(x >= 0){
    int y = x;
    x = 5;
    return (y+1);
  }else{
    return x;
  }
}

int func1(int x)
  _(presumes true covers x > 0 && result == x+1)
{
  if(x > 0) return func2(x); else return x;
}

/* this contract is satisfied because of the equality in the result */
int test5(int *p)
  _(presumes exists int v, int y. p |-> v covers p |-> y &*& result == 0 && v == y)
{
  return 0;
}


void load_and_branch(int *arr, int off){
  int *p = arr + off;
  //HERE! memory error
  int v = *p;
  //HERE! insec
  if (v);
}
