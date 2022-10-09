// need to run this with:
// --pulse-widen-threshold 1 --pulse-max-disjuncts 14 --pulse-model-skip-pattern "get\_val\|time"

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
status_code start_auction(struct idqt *s, database_status *d)
{
  *d = Ready;
  return Success;
}
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
  return;
}
void idqt_max(struct idqt *a, struct idqt *b)
{
  if (b->qt > a->qt){
    a->id = b->id;
    a->qt = b->qt;
  }
  return;
}
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
      return Success;
    }
    else
    {
      idqt_max(s, bid);
      return Success;
    }
}
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
      return Success;
    }
}
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
      return Success;
    }
}
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
int time();
int get_val();
void get_bid(struct idqt *bid){
  bid->id = get_val();
  bid->qt = get_val();
}
int main(){
  database_status d;
  struct idqt s;
  struct idqt bid;
  int winid;
  int winqt;
  start_auction(&s,&d);
  int start = time();
  while (time() - start < 5) {
    get_bid(&bid);
    register_bid(&s,&d,&bid);
  }
  status_code res = close_auction_and_get_winner(&s,&d,&winid,&winqt);
  if (res == Success) {
  }
}
