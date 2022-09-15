#include "underflow.h"
#define NULL ((void *)0); 

int get_val_LOW();

enum auction_status
{
  Ready,
  Ongoing,
  Closed
};
typedef enum auction_status database_status;

struct idqt
{
  int id;
  int qt;
};

// struct MyStruct_s 
// {
//     int id;
// } MyStruct_default = {3};

// typedef struct MyStruct_s MyStruct;


// struct idqt
// {
//   int id;
//   int qt;
// }idqt_default = {0, 1};

typedef struct idqt idqt;

enum ret_code
{
  Failure,
  Success
};
typedef enum ret_code status_code;
enum auc_code
{
  Running,
  Finished
};
typedef enum auc_code event_code;

/* external functions to log events in the auction */
void log_current_max(int id, int qt);
_(presumes true covers true)
void log_closed();
_(presumes true covers true)

status_code start_auction(struct idqt *s, database_status *d)
{
  *d = Ready;
//Test 1. It works here with default mode --pulse-widen-threshold 0 --pulse-max-disjuncts 1 
  // int *p = NULL;
  // int blah = *p; // null pointer dereference
  // but the memory issues will not detect after adding this bug
  return Success;
}

/* constant-time computation of maximum of two bids. max is put into a */
// So in this function, the only thing that not detectable is the comparison statement 
// Don't know how to change since there is no place reference to it. 
void idqt_max_ct(struct idqt *a, struct idqt *b)
{
  int aid = a->id;
  int aqt = a->qt;
  int bid = b->id;
  int bqt = b->qt;
//Test 2. It works here with default mode --pulse-widen-threshold 0 --pulse-max-disjuncts 1 
  // int *p = NULL;
  // int blah = *p; // null pointer dereference
//different from test 1 cause it is not being referenced by main
  //int t = (aqt >= bqt);
  int t = aqt;
  int rid = t * aid + (1 - t) * bid; 
  int rqt = t * aqt + (1 - t) * bqt;
  a->id = rid; 
  a->qt = rqt;
  log_current_max(a->id, a->qt);
//Test 4. Work here ~
  // int *p = NULL;
  // int blah = *p; // null pointer dereference  
  return;  
}

/* computation of max of two bids. The current maximum is stored in a.
   The new bid is stored in b. We update the current max with the new one
   if it is larger */
void idqt_max(struct idqt *a, struct idqt *b)
{
  if (b->qt > a->qt){
    a->id = b->id;
    a->qt = b->qt;
    // only log the maximum when it changes
    log_current_max(a->id, a->qt);
//Test 5. Work here ~
    //int *p = NULL;
    //int blah = *p; // null pointer dereference 
  }
  return;
}

/* called to register newly received bids */
status_code register_bid(struct idqt *s, database_status *d, struct idqt *bid)
{
    database_status stp = *d;
//Test 9. Work here
    // int *p = NULL;
    // int blah = *p; // null pointer dereference 
    if (stp == Closed)
    {
    //Test 10. Do not work here, since there is a not defined the parameter here
      // int *p = NULL;
      // int blah = *p; // null pointer dereference 
      return Failure;
    }
    else if(stp == Ready)
    {
      s->id = bid->id;
      s->qt = bid->qt;
      *d = Ongoing;
      log_current_max(bid->id, bid->qt);
    //Test 11. But it works here :< :< :< ahhhhhhhh!
      // int *p = NULL;
      // int blah = *p; // null pointer dereference 
      return Success;
    }
    else
    {
    //Test 12. But it works here :< :< :< ahhhhhhhh!
      // int *p = NULL;
      // int blah = *p; // null pointer dereference 
      idqt_max(s, bid);
      return Success;
    }
}

/* should be used when there is no 'reserve' set */
status_code close_auction_and_get_winner(struct idqt *s, database_status *d, int *p, int *q)
{
    database_status stp = *d;
//Test 13. Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
    if(stp == Ready)
    {
//Test 14. Not Work
      // int *x = NULL;
      // int blah = *x; // null pointer dereference 
      return Failure;
    }
    else if (stp == Closed)
    {
//Test 15. Not Work
      // int *x = NULL;
      // int blah = *x; // null pointer dereference 
      return Failure;
    }
    else
    {
//Test 16. Not Work
      // int *x = NULL;
      // int blah = *x; // null pointer dereference 
      *d = Closed;
      *p = s->id;
      *q = s->qt;
      log_closed();
      return Success;
    }
}

/* close the auction but do not compute the winner. Should be used only
   with get_winner_with_reserve() below */
status_code close_auction(struct idqt *s, database_status *d)
{
    database_status stp = *d;
//Test 17. Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
    if(stp == Ready)
    {
//Test 18. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
      return Failure;
    }
    else if (stp == Closed)
    {
//Test 19. Not Work
      // int *x = NULL;
      // int blah = *x; // null pointer dereference 
      return Failure;
    }
    else
    {
//Test 20. Not Work
      // int *x = NULL;
      // int blah = *x; // null pointer dereference 
      *d = Closed;
      log_closed();
      return Success;
    }
//Test 22. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
}

/* should be called to get the winner after callling close_auction(), when
   a reserve exists */
status_code get_winner_with_reserve(struct idqt *s, database_status *d, int reserve, int *p, int *q)
{
  database_status stp = *d;
// Test 22. Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
  if(stp == Ready)
  {
//Test 23. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
    return Failure;
  }
  else if (stp == Ongoing)
  {
//Test 24. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
    return Failure;
  }
  else
  {
//Test 25. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
    int sid = s->id;
    int sqt = s->qt;
    if (sqt >= reserve)
    {
//Test 26. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
      *p = s->id;
      *q = s->qt;
      return Success;
    }
    else
    {
//Test 27. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
      return Failure;
    }
//Test 28. Not Work
    // int *x = NULL;
    // int blah = *x; // null pointer dereference 
  }
}

/* external allocation functions */
struct idqt * alloc_idqt();
_(presumes true covers exists int _id, int _qt. &result->id |-> _id &*& &result->qt |-> _qt &*& result :: low)

/* axiomatise current time as being low (public) since bidders can always 
   tell when the auction is closed and the server does not try to keep that
   a secret (e.g. once enough time has passed new bids cannot be accepted) */
int time();
_(presumes true covers result :: low)

/* external function that blocks waiting for the next bid to arrive */
void get_bid(int is_sealed, struct idqt *bid);
_(presumes exists int _id, int _qt. &bid->id |-> _id &*& &bid->qt |-> _qt covers exists int _nid, int _nqt. &bid->id |-> _nid &*& &bid->qt |-> _nqt &*& _nqt :: (is_sealed ? high : low))
_(presumes exists int _id. &bid->id |-> _id &*& &bid->qt |-\-> fails memory exists int _nid. &bid->id |-> _nid &*& &bid->qt |-\->)
_(presumes &bid->id |-\-> fails memory &bid->id |-\->)

/* called to print out the winner */
void print_winner(int winid, int winqt);
_(presumes true covers true)

/* top-level function to run the auction, in the absence of a reserve price.
   Insecurity is detected with a loop unrolling bound of at least 2
   since we are only insecure when the second bid comes in and hte >=
   comparison is performed insecurely */
void run_auction(int is_sealed){
  database_status d;
  struct idqt *s = alloc_idqt();
  struct idqt *bid = alloc_idqt();//It says memory leakage if I delete while loop
  int winid;
  int winqt;
  //Test 8.  While loop
  // int *q = NULL;
  // int blahq = *q; // null pointer dereference 
  //status_code res = close_auction_and_get_winner(s,&d,&winid,&winqt);
  start_auction(s,&d);
  int start = time();
  while (time() - start < 300) {
    get_bid(is_sealed,bid);
    register_bid(s,&d,bid);
//Test 6. While loop Work here ~
    // int *p = NULL;
    // int blah = *p; // null pointer dereference 
  }
  status_code res = close_auction_and_get_winner(s,&d,&winid,&winqt);
//Test 7.  While loop, not work after the while loop
  // int *p = NULL;
  // int blah = *p; // null pointer dereference 
  if (res == Success) {
    print_winner(winid,winqt);
  }
}
