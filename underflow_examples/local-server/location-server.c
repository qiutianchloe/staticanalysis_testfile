#include "underflow.h"
#if __UNDERFLOW
typedef int double;
#endif
#define NULL ((void *)0)
struct ulocation
{
  double lat;
  double lon;
  struct ulocation *nxt;
};
struct point
{
  double lat;
  double lon;
};
enum ev_status
{
  Consumed,
  Replenished
};
typedef enum ev_status event_status;
struct event
{
  event_status est;
  double noislat;
  double noislon;
};
enum ret_code
{
  Failure,
  Success
};
typedef enum ret_code status_code;
void get_real_location(struct point *p);
_(presumes exists double _lat, double _lon. &p->lat |-> _lat &*& &p->lon |-> _lon covers exists double _nlat, double _nlon. &p->lat |-> _nlat &*& &p->lon |-> _nlon &*& _nlat :!: attacker && _nlon :!: attacker)
_(presumes exists double _lat. &p->lat |-> _lat &*& &p->lon |-\-> fails memory exists double _nlat. &p->lat |-> _nlat &*& &p->lon |-\-> &*& _nlat :!: attacker)
_(presumes &p->lat |-\-> fails memory &p->lat |-\->)

struct event add_noise_to_real_point(struct point *p, double eps);
_(presumes exists double _lat, double _lon. &p->lat |-> _lat &*& &p->lon |-> _lon covers exists double _nlat, double _nlon. &p->lat |-> _nlat &*& &p->lon |-> _nlon &*& _nlat :!: attacker && _nlon :!: attacker && result.est == Consumed && result.noislat == _nlat && 
  result.noislon == _nlon)
_(presumes exists double _lat. &p->lat |-> _lat &*& &p->lon |-\-> fails memory exists double _nlat. &p->lat |-> _nlat &*& &p->lon |-\-> &*& _nlat :!: attacker)
_(presumes &p->lat |-\-> fails memory &p->lat |-\->)

struct event generate_replenished_event();
_(presumes true covers  result.est == Replenished && result.noislat == 0 && result.noislon == 0)

status_code start_the_location_server(struct ulocation *s, double *budget, double eps, double refvalue)
{
  *budget = 0;
  return Success;
}
status_code refill_budget(struct ulocation *s, double *budget, double eps, double refvalue)
{
  *budget = *budget + refvalue;
  struct event e = generate_replenished_event();
  return Success;
}
status_code release_current_location(struct ulocation *s, double *budget, double eps, double refvalue, struct point *p, struct ulocation *ncell)
{
  double cbudget = *budget;
  if(cbudget >= eps)
  {
        get_real_location(p);
        struct event e = add_noise_to_real_point(p, eps);
        double nlat = p->lat;
        double nlon = p->lon;
        *budget = cbudget - eps;
        ncell->lat = nlat;
        ncell->lon = nlon;
        ncell->nxt = s;
        return Success;
  }
  else
    return Failure;
}
void compute_the_values_recursively(struct ulocation *s, double eps, double refvalue,
  double *sumx, double *sumx2, double *sumxy, double *sumy, double *sumy2, int *n)
{
  if(s == NULL)
  {
    return;
  }
  else
  {
    int slat = s->lat;
    int slon = s->lon;
    *sumx += slat;
    *sumx2 += s->lat * s->lat;
    *sumxy += s->lat * s->lon;
    *sumy += s->lon;
    *sumy2 += s->lon * s->lon;
    *n = *n + 1;
    compute_the_values_recursively(s->nxt, eps, refvalue, sumx, sumx2, sumxy, sumy, sumy2, n);
    return;
  }
}
void compute_the_values_iteratively(struct ulocation *s, double eps, double refvalue,
  double *sumx, double *sumx2, double *sumxy, double *sumy, double *sumy2, int *n)
{
  while(s != NULL)
  {
    int slat = s->lat;
    int slon = s->lon;
    *sumx += slat;
    *sumx2 += s->lat * s->lat;
    *sumxy += s->lat * s->lon;
    *sumy += s->lon;
    *sumy2 += s->lon * s->lon;
    *n = *n + 1;
    s = s->nxt;
  }
}
status_code extrapolate_points(struct ulocation *s, struct point *p, double eps, double refvalue,
  double *sumx, double *sumx2, double *sumxy, double *sumy, double *sumy2, int *n)
{
  *sumx = 0;
  *sumx2 = 0;
  *sumxy = 0;
  *sumy = 0;
  *sumy2 = 0;
  *n = 0;
  //compute_the_values_recursively(s, eps, refvalue, sumx, sumx2, sumxy, sumy, sumy2, n);  
  compute_the_values_iteratively(s, eps, refvalue, sumx, sumx2, sumxy, sumy, sumy2, n);
  double denom = *n * *sumx2 - *sumx * *sumx;
  if (denom == 0)
  {
    return Failure;
  }
  double m = (*n * *sumxy - *sumx * *sumy)/denom;
  double b = (*sumy * *sumx2 - *sumx * *sumxy)/denom;
  p->lat = m;
  p->lon = b;
  return Success;
}
double sqrt(double x);
_(presumes true covers true)

status_code release_predicted_location(struct ulocation *s, double *budget, struct point *p, double eps, double refvalue, int prediction_count,
  double *sumx, double *sumx2, double *sumxy, double *sumy, double *sumy2, int *n)
{
  if(s == NULL)
  {
    return Failure;
  }
  else
  {
    status_code st = extrapolate_points(s, p, eps, refvalue, sumx, sumx2, sumxy, sumy, sumy2, n);
    if(st == Success)
    {
      double m = p->lat;
      double b = p->lon;
      double denom = m*m + 1;
      double latdisp = sqrt((prediction_count+1) * (prediction_count+1) / (100 * 100 * denom));
      p->lat = s->lat + latdisp;
      p->lon = m * p->lat + b;
    }
    else
    {
      p->lat = s->lat;
      p->lon = s->lon;
    }
    return Success;
  }
}
int database_length(struct ulocation *s, double eps, double refvalue)
{
  int ret = 0;
  while(s != NULL)
  {
    ret++;
    s = s->nxt;
  }
  return ret;
}
