/* The 'push-back' example from the ISL paper
 * Fig 2., Raad et al., CAV 2020
 *
 * run with -discover to show inference of the memory-safety issue demonstrated
 * in that paper, here by inter-procedural analysis (whereas their paper did only
 * intra-procedural)
 */

int **palloc();
_(presumes true covers exists int * p, int v. result |-> p &*& p |-> v)

int *alloc();
_(presumes true covers exists int v. result |-> v)


int nondet();
_(presumes true covers result :: low)

void free(int * p);
  _(presumes exists int v. p |-> v covers p |-\->)
  _(presumes p |-\-> fails memory p |-\->)

void push_back(int **v)
{
  if (nondet()){
    int *y = *v;
    free(y);
    y = alloc();
    *v = y;
  }
}

void isl_push_back()
{
    int *v = palloc();
    int *x = *v;
    push_back(v);
    *x = 88;
}
