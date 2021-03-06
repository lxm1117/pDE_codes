: Extracellular potassium ion accumulation

NEURON {
   SUFFIX kext
   USEION k READ ik WRITE ko
:   GLOBAL kbath
   RANGE fhspace, txfer, kbath
}

UNITS{
   (mV)	=	(millivolt)
   (mA)	=	(milliamp)
   FARADAY	=	(faraday) (coulombs)
   (molar)	=	(1/liter)
   (mM)		=	(millimolar)
}

PARAMETER {
   kbath	=	3.4  (mM)
   fhspace  =	3000   (angstrom)
   txfer	=	50   (ms)
}

ASSIGNED  {  ik  (mA/cm2)  }

STATE { ko (mM) }

BREAKPOINT  { SOLVE state METHOD derivimplicit}

DERIVATIVE state  {
   ko' = (1e8)*ik/(fhspace*FARADAY) + (kbath - ko)/txfer
}
