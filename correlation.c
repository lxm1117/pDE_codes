#include <stdio.h>
#include <math.h>

/* ================================================================================
   Fit y = a + bx by the least squares criterion.
   Arrays x[1..ndata] and y[1..ndata] are the input experimental points.
   The fitted parameters a, b are ouput along with r (the linear correlation) the
   z value, the t value and P (the probablity of the correlation).
   ================================================================================ */
#define TINY	1.0e-20

void linear_lsq( int n, double *x, double *y, 
		 double *a, double *b, double *r, double *z, double *t, double *prob )
{
  int		i;
  double	Sx, Sy, xm, ym, Sxx, Syy, Sxy, xt, yt, df;
  double	mSxx, mSxy;

  Sx = Sy = 0.0;
  for( i=1; i<=n; ++i ){
    Sx += x[i];
    Sy += y[i];
  }
  xm = Sx/(double)n; ym = Sy/(double)n;
  Sxx = Syy = Sxy = mSxx = mSxy = 0.0;
  for( i=1; i<=n; ++i ){
    xt = x[i] - xm;
    yt = y[i] - ym;
    Sxx += xt*xt;
    Syy += yt*yt;
    Sxy += xt*yt;
    
    mSxx += x[i]*x[i];
    mSxy += x[i]*y[i];
  }

  *a = ( mSxx*Sy - Sx*mSxy )/( n*mSxx - Sx*Sx );
  *b = ( n*mSxy - Sx*Sy ) / ( n*mSxx - Sx*Sx );

  *r = Sxy/sqrt( Sxx*Syy );
  *z = 0.5*log( (1.0+(*r)+TINY) / (1.0-(*r)+TINY) );
  df = n - 2;
  *t = (*r)*sqrt( df / ((1.0-(*r)+TINY)*(1.0+(*r)+TINY)) );
  *prob = betai( 0.5*df, 0.5, df/(df+(*t)*(*t)) );

}

/* ================================================================================ 
   Calculate Spearman rank-order correlation 
   See C recipes 507 ff
     NOTE: Error in equation 13.8.5 (Finally solved on 16 June '92):
       i) Correction factor 
          \frac{1}{12} \Sum_k (f_k^3 - f_k)  instead of \frac{1}{2}
          \frac{1}{12} \Sum_k (g_k^3 - g_k)  instead of \frac{1}{2}

       ii) Correction factor in denominator should have sqrt
          [ 1 - \Sum_k (f_k^3 - f_k)/(N^3 - N)] ^{1/2}
          [ 1 - \Sum_k (g_k^3 - g_k)/(N^3 - N)] ^{1/2}

   ================================================================================ */

/* ================================================================================
   Given sorted array w[0:n-1] replaces the elements by their rank, including midranking
   of ties. Returns as s the sum of f^3-f where f is the number of elements in each tie
   ================================================================================ */
static void crank( int n, double *w, double *s )
{
  int		j=0, ji, jt;
  double	t, rank;
  
  *s = 0.0;
  while( j < n-1 ) {
    if( w[j+1] != w[j] ){ w[j] = j; ++j; }
    else {
      for( jt=j+1; jt<n && w[jt]==w[j]; ++jt );
      rank = 0.5*(j+jt-1);
      for( ji=j; ji<=(jt-1); ++ji ) w[ji] = rank;
      t = jt - j;
      (*s) += t*t*t - t;
      j = jt;
    }
  }
  if( j == n-1 ) w[n-1] = n-1;
}

/* ================================================================================ 
   See C recipes p641ff
   Given arrays xa[0:n-1] ya[0:n-1]. Return
     d - 	sum-square difference of ranks
     zd - 	the number of SD by which d deviates from null hypothesis
     probd - 	two sided significance of zd
     rs - 	Spearman's rank correlation
     probrs - 	two sided significance pf rs
   Small value of probd or probrs indicates significant correlation (rs>0) or 
   anticorrelation (rs<0)
  ================================================================================ */
#define SQR(a,t)	(t=(a), t*t)

void spear( int n, double xa[], double ya[], 
       double *d, double *zd, double *probd, double *rs, double *t, double *probrs )
{
  int		i, j;
  double	*wkx, *wky, vard, sg, sf, fac, en3n, en, df, aved, tmp;

  wkx = (double *) xmalloc( n * sizeof( double ));
  wky = (double *) xmalloc( n * sizeof( double ));
  for( i=0; i<n; ++i ) {
    wkx[i] = xa[i];
    wky[i] = ya[i];
  }

  printf("before sort1 wkx, wky\n" ); for( i=0; i<n; ++i ) printf( "%d %g %g\n", i, wkx[i], wky[i] );
  shell_sort_d( n, wkx, wky );
  printf("after sort1 wkx, wky\n" ); for( i=0; i<n; ++i ) printf( "%d %g %g\n", i, wkx[i], wky[i] );
  crank( n, wkx, &sf );
  printf("after rank sf %g wkx, wky\n", sf ); for( i=0; i<n; ++i ) printf( "%d %g %g\n", i, wkx[i], wky[i] );
  shell_sort_d( n, wky, wkx );
  printf("after sort2 wkx, wky\n" ); for( i=0; i<n; ++i ) printf( "%d %g %g\n", i, wkx[i], wky[i] );
  crank( n, wky, &sg );
  printf("after rank2 sg %g wkx, wky\n", sg ); for( i=0; i<n; ++i ) printf( "%d %g %g\n", i, wkx[i], wky[i] );

  *d = 0.0;
  for( j=0; j<n; ++j ) *d += SQR( wkx[j] - wky[j], tmp );

  en = n;
  en3n = en*en*en - en;
  aved = en3n/6.0 - (sf+sg)/12.0;
  fac =  ( 1.0-sf/en3n )*( 1.0-sg/en3n );
  vard = ((en-1.0) *en*en * SQR(en+1.0,tmp)/36.0)*fac;
  *zd = (*d-aved)/sqrt(vard);
  *probd = erfcc( fabs(*zd)/1.4142136 ); 
  *rs = (1.0 - (6.0/en3n)*(*d+(sf+sg)/12.0))/sqrt(fac); 
  fac = (*rs+1.0)*(1.0-(*rs));
  if( fac > 0.0 ){
    *t = (*rs)*sqrt( (en-2.0)/fac);
    df = en - 2.0;
    *probrs = betai( 0.5*df, 0.5, df/(df+(*t)*(*t)) );
  }
  else {
    *t = 20.0;			/* some large number */
    *probrs = 0.0;
  }
  xfree( (char *) wkx );
  xfree( (char *) wky );
}

#ifdef TEST_CORR /*================================================================================*/
main( int argc, char* argv[] ){ 
  int           i, n, st;
  double        *x, *y, D, zd, pD, rs, t, prs;

  x = (double *) malloc( 2048 * sizeof( double ));
  y = (double *) malloc( 2048 * sizeof( double ));
  n = 0;
  while( 2 == (st = scanf( "%lf %lf", &(x[n]), &(y[n]) ))) ++n;
  if( st != EOF ) {
    fprintf( stderr, "bad input format" );
    exit( 1 );
  }

  printf( ">> data \n" );
  for( i=0; i<n; ++i ) printf( "%d %f %g\n", i, x[i], y[i] );

  spear( n, x, y, &D, &zd, &pD, &rs, &t, &prs );
  printf( "D %g zd %g pD %g rs %g t %g prs %g\n", D, zd, pD, rs, t, prs );
}

#endif /* TEST ================================================================================*/
