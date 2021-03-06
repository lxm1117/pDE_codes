TITLE KA channel
: Jose Ambros-Ingerson jose@kiubo.net 2006

NEURON {
  SUFFIX 	KA_i1
  USEION 	k READ ek WRITE ik
  RANGE		gbar, g, i

  GLOBAL 	inf_n, tau_n, inf_h, tau_h
}

PARAMETER {
  ek 			(mV)
  gbar		= 40 	(pS/um2)

  : inf_n parameters
  gates_n	= 4
  vhalf_n	= 11	(mV)	
  slope_n	= -18	(mV)
  needAdj = 1
  vhalfA_n 	= 0 (mV)		: adjusted for ngate power; Set in ngate_adjust()
  slopeA_n	= 0 (mV)
  v5_adj	= 0			: for return values in ngate_adjust
  slp_adj	= 0

  : tau_n parameters
  tauA_n	= 20 	(ms)
  tauDv_n	= 0	(mV)	: Delta to vhalf_n
  tauG_n	= 0.5		: Left-right bias. range is (0,1)
  tauF_n	= 0		: Up-Down bias. range is ~ -3.5(cup-shape), -3(flat), 0(from k), 1(sharper)
  tau0_n	= 0.01	(ms)	: minimum tau

  : inf_h parameters
  gates_h	= 1
  vhalfD_h	= -67   (mV)	:  vhalf_h = vhalf_n + vhalfD_h; 
  slope_h	= 8	(mV)

  : tau_h parameters
  tauA_h	= 40 	(ms)
  tauDv_h	= 0	(mV)	: Delta to vhalf_h
  tauG_h	= 0.5		: Left-right bias. range is (0,1)
  tauF_h	= 0		: Up-Down bias. range is ~ -3.5(cup-shape), -3(flat), 0(from k), 1(sharper)
  tau0_h	= 0.01	(ms)	: minimum tau
}

STATE {
  n	: activation
  h	: inactivation
}

ASSIGNED {
  v		(mV)
  celsius	(degC)
  ik 		(mA/cm2)
  g		(pS/um2)
  i		(mA/cm2)
  inf_n
  tau_n		(ms)
  inf_h
  tau_h		(ms)
}

BREAKPOINT {
  SOLVE states METHOD cnexp
  g = 0
  if( n >=0 ){	: make sure no domain error for pow. Cvode may test it
    g 	= gbar * n^gates_n * h
  }
  i	= g * ( v - ek ) * (1e-4)
  ik	= i
}

INITIAL {
  needAdj = 1
  rates( v )
  n = inf_n
  h = inf_h
}

UNITS {
  (mA)	= (milliamp)
  (mV)	= (millivolt)
  (pS)	= (picosiemens)
  (um)	= (micrometer)
}

DERIVATIVE states {     : exact when v held constant; integrates over dt step
  rates( v )
  n' = ( inf_n - n )/ tau_n
  h' = ( inf_h - h )/ tau_h
}

PROCEDURE rates( v (mV)){
  if( needAdj > 0 ){
    needAdj = 0
    ngate_adjust( gates_n, vhalf_n, slope_n )
    vhalfA_n = v5_adj
    slopeA_n = slp_adj
  }
  inf_n = Boltzmann( v, vhalfA_n, slopeA_n )
  tau_n = BorgMod_tau( v, vhalf_n, slope_n, tau0_n, tauA_n, tauG_n, tauF_n, tauDv_n )

  inf_h = Boltzmann( v, vhalf_n + vhalfD_h, slope_h )
  tau_h = BorgMod_tau( v, vhalf_n + vhalfD_h, slope_h, tau0_h, tauA_h, tauG_h, tauF_h, tauDv_h )
}

FUNCTION Boltzmann( v (mV), v5 (mV), s (mV) ){
  Boltzmann = 1 / (1 + exp( (v - v5) / s ))
}

FUNCTION BorgMod_tau( v (mV), v5 (mV), s (mV), tau0 (ms), tauA (ms), tauG, tauF, tauDv (mV) ) (ms) {
  LOCAL kc, kr, Dv, wr

  kr = 1000
  wr = 1000
  Dv = (v - ( v5 + tauDv )) * 1(1/mV)
  kc = kr * 10^tauF / s * 1(mV)

  BorgMod_tau = tau0 + tauA * 2 * sqrt( tauG * (1-tauG))
		* ( exp( - Dv *tauG/wr/kc ) + exp( Dv *(1-tauG)/wr/kc ))
 	        / ( exp( - Dv *(1-tauG)*kc/kr ) + exp( Dv *kc*tauG/kr ))
}

: Boltzmann's inverse
FUNCTION Boltz_m1( x, v5 (mV), s (mV) ) (mV) {
  Boltz_m1 = s * log( 1/x - 1 ) + v5
}

: Find parameters for a Boltzmann eq that when taken to the ngate power matches one with a single power
: return result in v5_adj and slp_adj
: We solve for exact match on two points
PROCEDURE ngate_adjust( ng, vh, slp ) {
  LOCAL x1, x2, v1, v2
  x1 = 0.3
  x2 = 0.7
  v1 = Boltz_m1( x1, vh, slp )
  v2 = Boltz_m1( x2, vh, slp )
  slp_adj = (v2 - v1)/( log( (1/x2)^(1/ng) - 1 ) - log( (1/x1)^(1/ng) - 1 ) )
  v5_adj = v1 - slp_adj * log( 1 / x1^(1/ng) - 1 )
}








