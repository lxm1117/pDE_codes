#include <stdio.h>
#include "NumRec.h"

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

  spear( x+1, y+1, n, &D, &zd, &pD, &rs, &prs );
  printf( "D %g zd %g pD %g rs %g prs %g\n", D, zd, pD, rs, prs );
}

