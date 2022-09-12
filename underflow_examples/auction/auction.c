#include "underflow.h"

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
  return Success;
}

/* constant-time computation of maximum of two bids. max is put into a */
void idqt_max_ct(struct idqt *a, struct idqt *b)
{
  int aid = a->id;
  int aqt = a->qt;
  int bid = b->id;
  int bqt = b->qt;
  
  int t = (aqt >= bqt);
  int rid = t * aid + (1 - t) * bid; 
  int rqt = t * aqt + (1 - t) * bqt;
  a->id = rid; 
  a->qt = rqt;
  log_current_max(a->id, a->qt);
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
  }
  return;
}

/* called to register newly received bids */
status_code register_bid(struct idqt *s, database_status *d, struct idqt *bid)
{
    database_status stp = *d;
    if (stp == Closed)
    {
      return Failure;
    }
    else if(stp == Ready)
    {
      s->id = bid->id;
      s->qt = bid->qt;
      *d = Ongoing;
      log_current_max(bid->id, bid->qt);
      return Success;
    }
    else
    {
      idqt_max(s, bid);
      return Success;
    }
}

/* should be used when there is no 'reserve' set */
status_code close_auction_and_get_winner(struct idqt *s, database_status *d, int *p, int *q)
{
    database_status stp = *d;
    if(stp == Ready)
    {
      return Failure;
    }
    else if (stp == Closed)
    {
      return Failure;
    }
    else
    {
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
    if(stp == Ready)
    {
      return Failure;
    }
    else if (stp == Closed)
    {
      return Failure;
    }
    else
    {
      *d = Closed;
      log_closed();
      return Success;
    }
}

/* should be called to get the winner after callling close_auction(), when
   a reserve exists */
status_code get_winner_with_reserve(struct idqt *s, database_status *d, int reserve, int *p, int *q)
{
  database_status stp = *d;
  if(stp == Ready)
  {
    return Failure;
  }
  else if (stp == Ongoing)
  {
    return Failure;
  }
  else
  {
    int sid = s->id;
    int sqt = s->qt;
    if (sqt >= reserve)
    {
      *p = s->id;
      *q = s->qt;
      return Success;
    }
    else
    {
      return Failure;
    }
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
void get_bid(struct idqt *bid);
_(presumes exists int _id, int _qt. &bid->id |-> _id &*& &bid->qt |-> _qt covers exists int _nid, int _nqt. &bid->id |-> _nid &*& &bid->qt |-> _nqt)
_(presumes exists int _id. &bid->id |-> _id &*& &bid->qt |-\-> fails memory exists int _nid. &bid->id |-> _nid &*& &bid->qt |-\->)
_(presumes &bid->id |-\-> fails memory &bid->id |-\->)

/* called to print out the winner */
void print_winner(int winid, int winqt);
_(presumes true covers true)

/* top-level function to run the auction, in the absence of a reserve price.
   Insecurity is detected with a loop unrolling bound of at least 2
   since we are only insecure when the second bid comes in and hte >=
   comparison is performed insecurely */
void run_auction(){
  _(loop 2)
  database_status d;
  struct idqt *s = alloc_idqt();
  struct idqt *bid = alloc_idqt();
  int winid;
  int winqt;
  start_auction(s,&d);
  int start = time();
  while (time() - start < 300) {
    get_bid(bid);
    register_bid(s,&d,bid);
  }
  status_code res = close_auction_and_get_winner(s,&d,&winid,&winqt);
  if (res == Success) {
    print_winner(winid,winqt);
  }
}
