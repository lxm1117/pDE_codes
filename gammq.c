#include <math.h>
#include "jLib.h"

/* ================================================================================
   Returns the incomplete gamma function P(a,x) pp 172
   ================================================================================ */
double gammp( double a, double x ){
  double	gamser, gln;
  void		gser(), gcf(), nerror();

  if( x<0.0 || a<=0.0 ) nerror( "gammp: Invalid arguments" );
  if( x < (a+1.0) ){
    gser( &gamser, a, x, &gln );
    return gamser;
  }
  else {
    gcf( &gamser, a, x, &gln );
    return 1.0 - gamser;
  }
}

/* =====================================================================================
   Returns the incomplete gamma function Q(a,x) = 1 - P(a,x) (173-ff)
   ===================================================================================== */
double gammq( double a, double x ){
  double	gamser, gammcf, gln;
  void		gcf(), gser(), nerror();

  if( x < 0.0 || a <= 0.0 ) nerror( "gammq : invalid argument" );
  if( x < (a+1.0) ){
    gser( &gamser, a, x, &gln );
    return( 1.0 - gamser );
  }
  else {
    gcf( &gammcf, a, x, &gln );
    return gammcf;
  }
}

/* =====================================================================================
   returns the incomplete gamma function P(a,x) evaluated by its series representation
   as gamser. Also returs ln(gamma(a)) in gln
   ===================================================================================== */
#define ITMAX 	100
#define EPS 	3.0e-7

void gser( double *gamser, double a, double x, double *gln ){
  int 		n;
  double	sum, del, ap;
  double	gammln();
  void		nerror();

  *gln = gammln( a );
  if( x <= 0.0 ) {
    if( x < 0.0 ) nerror( "gser : Error, x less than zero" );
    *gamser = 0.0;
    return;
  }
  else {
    ap = a;
    del = sum = 1.0/a;
    for( n=1; n<=ITMAX; ++n ){
      ap += 1.0;
      del *= x/ap;
      sum += del;
      if( fabs(del) < fabs(sum)*EPS ) {
	*gamser = sum * exp( -x + a*log(x)-(*gln));
	return;
      }
    }
    nerror( "gser : didn't converge; a too large, ITMAX too small" );
    return;
  }
}

/* =====================================================================================
   return the incomplete gamma function Q(a,x) evaluated by its continued fraction
   representation as gammcf. Also returs ln(gamma(a)) in gln.
   ===================================================================================== */

void gcf( double *gammcf, double a, double x, double *gln ){
  int		n;
  double	gold=0.0, g, fac=1.0, b1=1.0;
  double	b0=0.0, anf, ana, an, a1, a0=1.0;
  double	gammln();
  void		nerror();

  *gln = gammln( a );
  a1 = x;
  for( n=1; n<=ITMAX; ++n ){
    an = (double) n;
    ana = an - a;
    a0 = (a1 + a0*ana)*fac;
    b0 = (b1 + b0*ana)*fac;
    anf = an*fac;
    a1 = x*a0 + anf*a1;
    b1 = x*b0 + anf*b1;
    if( a1 ) {
      fac = 1.0/a1;
      g = b1*fac;
      if( fabs((g-gold)/g) < EPS ) {
	*gammcf = exp( -x + a*log(x) - (*gln)) * g;
	return;
      }
      gold = g;
    }
  }
  nerror( "gcf: didn't converge; a too large, ITMAX too small" );
}

/* =====================================================================================
   Returns the value of ln(abs(gamma(xx))) for xx>0.
   Full accuracy is obtained for xx>1. 
   For 0<xx<1 the reflection formula can be used first.
   ===================================================================================== */

double gammln( double xx ){
  double 	x, tmp, ser;
  static double cof[6] = { 76.18009173,
	                  -86.50532033,
			   24.01409822,
			   -1.231739516,
			    0.120858003e-2,
			   -0.536382e-5};
  int		j;

  x = xx - 1.0;
  tmp = x + 5.5;
  tmp -= (x+0.5) * log(tmp);
  ser = 1.0;
  for( j=0; j<=5; ++j ) {
    x += 1.0;
    ser += cof[j]/x;
  }
  return -tmp + log( 2.50662827465 * ser );
}

/* ================================================================================
   Return the error function erf(x) pp 175 
   ================================================================================ */
double erf( double x ){
  double gammp();
  
  return x<0.0 ? -gammp(0.5, x*x) : gammp(0.5, x*x);
}

/* ================================================================================
   Return the complementary error function erf(x) pp 175 
   ================================================================================ */
double erfc( double x ){
  double gammp(), gammq();
  
  return x<0.0 ? 1.0+gammp(0.5, x*x) : gammq(0.5, x*x);
}

/* ================================================================================
   Return the complementary error function with fractional error everywhere less 
   than 1.2 x 10^{-7}
   ================================================================================ */
double erfcc( double x ){
  double	t, z, ans;

  z = fabs( x );
  t = 1.0 / (1.0+0.5*z);
  ans = t * exp( -z*z -1.26551223 + t*(1.00002368 +t*(0.37409196 +t*(0.09678418 
		  + t*(-0.18628806 +t*(0.27886807 +t*(-1.13520398 +t*(1.48851587 
		  + t*(-0.82215223 +t*(0.17087277 ))))))))));
  return x>=0.0 ? ans : 2.0-ans;
}
						    
