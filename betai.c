#include <math.h>
#include "jLib.h"

void nerror( char *msg ){
  printf( "%s\n", msg );
  exit( 1 );
}

/* =====================================================================================
   Return the incomplete beta function (pp 179-ff of C recipes )
   ===================================================================================== */
double betai( double a, double b, double x ){
  double        bt;
  double        gammln(), betacf();
  void          nerror();

  if( x < 0.0 || x > 1.0 ) nerror( "betai : bad x value" );
  if( x == 0.0 || x == 1.0 ) bt = 0.0;
  else 
    bt = exp( gammln(a+b) - gammln(a) - gammln(b) + a*log(x)+b*log(1.0-x) );
  if( x < (a+1.0)/(a+b+2.0))
    return bt * betacf( a, b, x ) / a;
  else
    return 1.0 - bt*betacf( b, a, 1.0-x )/b;
}

/* =====================================================================================
   Continued fraction for incomplete beta function
   ===================================================================================== */
#define ITMAX   100
#define EPS     3.0e-10

double betacf( double a, double b, double x ){
  int           m;
  double        qap, qam, qab, em, tem, d;
  double        bz, bm=1.0, bp, bpp;
  double        az=1.0, am=1.0, ap, app, aold;
  void          nerror();
  
  qab = a + b;
  qap = a + 1.0;
  qam = a - 1.0;
  bz = 1.0 - qab*x/qap;
  for( m=1; m<=ITMAX; ++m ) {
    em = (double) m;
    tem = em + em;
    d = em*(b-em)*x / ((qam+tem)*(a+tem));
    ap = az + d*am;
    bp = bz + d*bm;
    d = -(a+em) * (qab+em) * x / ((qap+tem)*(a+tem));
    app = ap + d*az;
    bpp = bp + d*bz;
    aold = az;
    am = ap/bpp;
    bm = bp/bpp;
    az = app/bpp;
    bz = 1.0;
    if( fabs( az-aold ) < (EPS*fabs( az )) ) return az;
  }
  /* nerror( "betacf : didn't converge " );*/
  return( 1.0/0.0 ); /* NaN */
}


