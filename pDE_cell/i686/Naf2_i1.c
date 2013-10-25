/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 
#include "md1redef.h"
#include "section.h"
#include "md2redef.h"

#if METHOD3
extern int _method3;
#endif

#undef exp
#define exp hoc_Exp
extern double hoc_Exp();
 
#define _threadargscomma_ /**/
#define _threadargs_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gbar _p[0]
#define gbar16 _p[1]
#define sfrac _p[2]
#define sfrac2 _p[3]
#define g _p[4]
#define g2 _p[5]
#define i _p[6]
#define n _p[7]
#define h _p[8]
#define s _p[9]
#define n2 _p[10]
#define h2 _p[11]
#define s2 _p[12]
#define ena _p[13]
#define Dn _p[14]
#define Dh _p[15]
#define Ds _p[16]
#define Dn2 _p[17]
#define Dh2 _p[18]
#define Ds2 _p[19]
#define ina _p[20]
#define _g _p[21]
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static int _hoc_Boltz_m1();
 static int _hoc_BorgMod_tau();
 static int _hoc_Boltzmann();
 static int _hoc_ngate_adjust();
 static int _hoc_rates();
 static int _mechtype;
extern int nrn_get_mechtype();
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_Naf2_i1", _hoc_setdata,
 "Boltz_m1_Naf2_i1", _hoc_Boltz_m1,
 "BorgMod_tau_Naf2_i1", _hoc_BorgMod_tau,
 "Boltzmann_Naf2_i1", _hoc_Boltzmann,
 "ngate_adjust_Naf2_i1", _hoc_ngate_adjust,
 "rates_Naf2_i1", _hoc_rates,
 0, 0
};
#define Boltz_m1 Boltz_m1_Naf2_i1
#define BorgMod_tau BorgMod_tau_Naf2_i1
#define Boltzmann Boltzmann_Naf2_i1
 extern double Boltz_m1();
 extern double BorgMod_tau();
 extern double Boltzmann();
 /* declare global and static user variables */
#define gates_n gates_n_Naf2_i1
 double gates_n = 3;
#define inf_s2 inf_s2_Naf2_i1
 double inf_s2 = 0;
#define inf_h2 inf_h2_Naf2_i1
 double inf_h2 = 0;
#define inf_n2 inf_n2_Naf2_i1
 double inf_n2 = 0;
#define inf_s inf_s_Naf2_i1
 double inf_s = 0;
#define inf_h inf_h_Naf2_i1
 double inf_h = 0;
#define inf_n inf_n_Naf2_i1
 double inf_n = 0;
#define needAdj needAdj_Naf2_i1
 double needAdj = 1;
#define slope_s slope_s_Naf2_i1
 double slope_s = 8;
#define slope_h slope_h_Naf2_i1
 double slope_h = 8;
#define slp_adj2 slp_adj2_Naf2_i1
 double slp_adj2 = 0;
#define slopeA_n2 slopeA_n2_Naf2_i1
 double slopeA_n2 = 0;
#define slp_adj slp_adj_Naf2_i1
 double slp_adj = 0;
#define slopeA_n slopeA_n_Naf2_i1
 double slopeA_n = 0;
#define slope_n slope_n_Naf2_i1
 double slope_n = -7;
#define tau0_s tau0_s_Naf2_i1
 double tau0_s = 0.01;
#define tauF_s tauF_s_Naf2_i1
 double tauF_s = 0;
#define tauG_s tauG_s_Naf2_i1
 double tauG_s = 0.5;
#define tauDv_s tauDv_s_Naf2_i1
 double tauDv_s = 0;
#define tauA_s tauA_s_Naf2_i1
 double tauA_s = 2000;
#define tau0_h tau0_h_Naf2_i1
 double tau0_h = 0.01;
#define tauF_h tauF_h_Naf2_i1
 double tauF_h = 0;
#define tauG_h tauG_h_Naf2_i1
 double tauG_h = 0.5;
#define tauDv_h tauDv_h_Naf2_i1
 double tauDv_h = 0;
#define tauA_h tauA_h_Naf2_i1
 double tauA_h = 20;
#define tau0_n tau0_n_Naf2_i1
 double tau0_n = 0.001;
#define tauF_n tauF_n_Naf2_i1
 double tauF_n = 0;
#define tauG_n tauG_n_Naf2_i1
 double tauG_n = 0.5;
#define tauDv_n tauDv_n_Naf2_i1
 double tauDv_n = 0;
#define tauA_n tauA_n_Naf2_i1
 double tauA_n = 0.5;
#define tau_s2 tau_s2_Naf2_i1
 double tau_s2 = 0;
#define tau_h2 tau_h2_Naf2_i1
 double tau_h2 = 0;
#define tau_n2 tau_n2_Naf2_i1
 double tau_n2 = 0;
#define tau_s tau_s_Naf2_i1
 double tau_s = 0;
#define tau_h tau_h_Naf2_i1
 double tau_h = 0;
#define tau_n tau_n_Naf2_i1
 double tau_n = 0;
#define vhalfD_s2 vhalfD_s2_Naf2_i1
 double vhalfD_s2 = -40;
#define vhalfD_s vhalfD_s_Naf2_i1
 double vhalfD_s = -40;
#define vhalfD_h2 vhalfD_h2_Naf2_i1
 double vhalfD_h2 = -40;
#define vhalfD_h vhalfD_h_Naf2_i1
 double vhalfD_h = -40;
#define v5_adj2 v5_adj2_Naf2_i1
 double v5_adj2 = 0;
#define vhalfA_n2 vhalfA_n2_Naf2_i1
 double vhalfA_n2 = 0;
#define vhalfD_n2 vhalfD_n2_Naf2_i1
 double vhalfD_n2 = -10;
#define v5_adj v5_adj_Naf2_i1
 double v5_adj = 0;
#define vhalfA_n vhalfA_n_Naf2_i1
 double vhalfA_n = 0;
#define vhalf_n vhalf_n_Naf2_i1
 double vhalf_n = -30;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "vhalf_n_Naf2_i1", "mV",
 "slope_n_Naf2_i1", "mV",
 "vhalfA_n_Naf2_i1", "mV",
 "slopeA_n_Naf2_i1", "mV",
 "vhalfD_n2_Naf2_i1", "mV",
 "vhalfA_n2_Naf2_i1", "mV",
 "slopeA_n2_Naf2_i1", "mV",
 "tauA_n_Naf2_i1", "ms",
 "tauDv_n_Naf2_i1", "mV",
 "tau0_n_Naf2_i1", "ms",
 "vhalfD_h_Naf2_i1", "mV",
 "slope_h_Naf2_i1", "mV",
 "vhalfD_h2_Naf2_i1", "mV",
 "tauA_h_Naf2_i1", "ms",
 "tauDv_h_Naf2_i1", "mV",
 "tau0_h_Naf2_i1", "ms",
 "vhalfD_s_Naf2_i1", "mV",
 "slope_s_Naf2_i1", "mV",
 "vhalfD_s2_Naf2_i1", "mV",
 "tauA_s_Naf2_i1", "ms",
 "tauDv_s_Naf2_i1", "mV",
 "tau0_s_Naf2_i1", "ms",
 "tau_n_Naf2_i1", "ms",
 "tau_n2_Naf2_i1", "ms",
 "tau_h_Naf2_i1", "ms",
 "tau_h2_Naf2_i1", "ms",
 "tau_s_Naf2_i1", "ms",
 "tau_s2_Naf2_i1", "ms",
 "gbar_Naf2_i1", "pS/um2",
 "gbar16_Naf2_i1", "pS/um2",
 "g_Naf2_i1", "pS/um2",
 "g2_Naf2_i1", "pS/um2",
 "i_Naf2_i1", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double h20 = 0;
 static double h0 = 0;
 static double n20 = 0;
 static double n0 = 0;
 static double s20 = 0;
 static double s0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "gates_n_Naf2_i1", &gates_n_Naf2_i1,
 "vhalf_n_Naf2_i1", &vhalf_n_Naf2_i1,
 "slope_n_Naf2_i1", &slope_n_Naf2_i1,
 "needAdj_Naf2_i1", &needAdj_Naf2_i1,
 "vhalfA_n_Naf2_i1", &vhalfA_n_Naf2_i1,
 "slopeA_n_Naf2_i1", &slopeA_n_Naf2_i1,
 "v5_adj_Naf2_i1", &v5_adj_Naf2_i1,
 "slp_adj_Naf2_i1", &slp_adj_Naf2_i1,
 "vhalfD_n2_Naf2_i1", &vhalfD_n2_Naf2_i1,
 "vhalfA_n2_Naf2_i1", &vhalfA_n2_Naf2_i1,
 "slopeA_n2_Naf2_i1", &slopeA_n2_Naf2_i1,
 "v5_adj2_Naf2_i1", &v5_adj2_Naf2_i1,
 "slp_adj2_Naf2_i1", &slp_adj2_Naf2_i1,
 "tauA_n_Naf2_i1", &tauA_n_Naf2_i1,
 "tauDv_n_Naf2_i1", &tauDv_n_Naf2_i1,
 "tauG_n_Naf2_i1", &tauG_n_Naf2_i1,
 "tauF_n_Naf2_i1", &tauF_n_Naf2_i1,
 "tau0_n_Naf2_i1", &tau0_n_Naf2_i1,
 "vhalfD_h_Naf2_i1", &vhalfD_h_Naf2_i1,
 "slope_h_Naf2_i1", &slope_h_Naf2_i1,
 "vhalfD_h2_Naf2_i1", &vhalfD_h2_Naf2_i1,
 "tauA_h_Naf2_i1", &tauA_h_Naf2_i1,
 "tauDv_h_Naf2_i1", &tauDv_h_Naf2_i1,
 "tauG_h_Naf2_i1", &tauG_h_Naf2_i1,
 "tauF_h_Naf2_i1", &tauF_h_Naf2_i1,
 "tau0_h_Naf2_i1", &tau0_h_Naf2_i1,
 "vhalfD_s_Naf2_i1", &vhalfD_s_Naf2_i1,
 "slope_s_Naf2_i1", &slope_s_Naf2_i1,
 "vhalfD_s2_Naf2_i1", &vhalfD_s2_Naf2_i1,
 "tauA_s_Naf2_i1", &tauA_s_Naf2_i1,
 "tauDv_s_Naf2_i1", &tauDv_s_Naf2_i1,
 "tauG_s_Naf2_i1", &tauG_s_Naf2_i1,
 "tauF_s_Naf2_i1", &tauF_s_Naf2_i1,
 "tau0_s_Naf2_i1", &tau0_s_Naf2_i1,
 "inf_n_Naf2_i1", &inf_n_Naf2_i1,
 "inf_n2_Naf2_i1", &inf_n2_Naf2_i1,
 "tau_n_Naf2_i1", &tau_n_Naf2_i1,
 "tau_n2_Naf2_i1", &tau_n2_Naf2_i1,
 "inf_h_Naf2_i1", &inf_h_Naf2_i1,
 "inf_h2_Naf2_i1", &inf_h2_Naf2_i1,
 "tau_h_Naf2_i1", &tau_h_Naf2_i1,
 "tau_h2_Naf2_i1", &tau_h2_Naf2_i1,
 "inf_s_Naf2_i1", &inf_s_Naf2_i1,
 "inf_s2_Naf2_i1", &inf_s2_Naf2_i1,
 "tau_s_Naf2_i1", &tau_s_Naf2_i1,
 "tau_s2_Naf2_i1", &tau_s2_Naf2_i1,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[3]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"Naf2_i1",
 "gbar_Naf2_i1",
 "gbar16_Naf2_i1",
 "sfrac_Naf2_i1",
 "sfrac2_Naf2_i1",
 0,
 "g_Naf2_i1",
 "g2_Naf2_i1",
 "i_Naf2_i1",
 0,
 "n_Naf2_i1",
 "h_Naf2_i1",
 "s_Naf2_i1",
 "n2_Naf2_i1",
 "h2_Naf2_i1",
 "s2_Naf2_i1",
 0,
 0};
 static Symbol* _na_sym;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 22, _prop);
 	/*initialize range parameters*/
 	gbar = 1000;
 	gbar16 = 2500;
 	sfrac = 0;
 	sfrac2 = 0;
 	_prop->param = _p;
 	_prop->param_size = 22;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 _Naf2_i1_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 4);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Naf2_i1 /home/ximing/Documents/lab_stuff/pDE_cell/i686/Naf2_i1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Naf2 channel";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static ngate_adjust();
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[6], _dlist1[6];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dn = ( inf_n - n ) / tau_n ;
   Dh = ( inf_h - h ) / tau_h ;
   Ds = ( inf_s - s ) / tau_s ;
   Dn2 = ( inf_n2 - n2 ) / tau_n2 ;
   Dh2 = ( inf_h2 - h2 ) / tau_h2 ;
   Ds2 = ( inf_s2 - s2 ) / tau_s2 ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_n )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_h )) ;
 Ds = Ds  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_s )) ;
 Dn2 = Dn2  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_n2 )) ;
 Dh2 = Dh2  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_h2 )) ;
 Ds2 = Ds2  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_s2 )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( inf_n ) ) / tau_n ) / ( ( ( ( - 1.0) ) ) / tau_n ) - n) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( inf_h ) ) / tau_h ) / ( ( ( ( - 1.0) ) ) / tau_h ) - h) ;
    s = s + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_s)))*(- ( ( ( inf_s ) ) / tau_s ) / ( ( ( ( - 1.0) ) ) / tau_s ) - s) ;
    n2 = n2 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n2)))*(- ( ( ( inf_n2 ) ) / tau_n2 ) / ( ( ( ( - 1.0) ) ) / tau_n2 ) - n2) ;
    h2 = h2 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h2)))*(- ( ( ( inf_h2 ) ) / tau_h2 ) / ( ( ( ( - 1.0) ) ) / tau_h2 ) - h2) ;
    s2 = s2 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_s2)))*(- ( ( ( inf_s2 ) ) / tau_s2 ) / ( ( ( ( - 1.0) ) ) / tau_s2 ) - s2) ;
   }
  return 0;
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   if ( needAdj > 0.0 ) {
     needAdj = 0.0 ;
     ngate_adjust ( _threadargscomma_ gates_n , vhalf_n , slope_n ) ;
     vhalfA_n = v5_adj ;
     slopeA_n = slp_adj ;
     vhalfA_n2 = v5_adj + vhalfD_n2 ;
     }
   inf_n = Boltzmann ( _threadargscomma_ _lv , vhalfA_n , slopeA_n ) ;
   tau_n = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n , slope_n , tau0_n , tauA_n , tauG_n , tauF_n , tauDv_n ) ;
   inf_h = Boltzmann ( _threadargscomma_ _lv , vhalf_n + vhalfD_h , slope_h ) ;
   tau_h = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n + vhalfD_h , slope_h , tau0_h , tauA_h , tauG_h , tauF_h , tauDv_h ) ;
   inf_s = Boltzmann ( _threadargscomma_ _lv , vhalf_n + vhalfD_s , slope_s ) ;
   tau_s = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n + vhalfD_s , slope_s , tau0_s , tauA_s , tauG_s , tauF_s , tauDv_s ) ;
   inf_n2 = Boltzmann ( _threadargscomma_ _lv , vhalfA_n2 , slopeA_n ) ;
   tau_n2 = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n + vhalfD_n2 , slope_n , tau0_n , tauA_n , tauG_n , tauF_n , tauDv_n ) ;
   inf_h2 = Boltzmann ( _threadargscomma_ _lv , vhalf_n + vhalfD_n2 + vhalfD_h , slope_h ) ;
   tau_h2 = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n + vhalfD_n2 + vhalfD_h , slope_h , tau0_h , tauA_h , tauG_h , tauF_h , tauDv_h ) ;
   inf_s2 = Boltzmann ( _threadargscomma_ _lv , vhalf_n + vhalfD_n2 + vhalfD_s , slope_s ) ;
   tau_s2 = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n + vhalfD_n2 + vhalfD_s , slope_s , tau0_s , tauA_s , tauG_s , tauF_s , tauDv_s ) ;
    return 0; }
 
static int _hoc_rates() {
  double _r;
   _r = 1.;
 rates (  *getarg(1) ) ;
 ret(_r);
}
 
double Boltzmann (  _lv , _lv5 , _ls )  
	double _lv , _lv5 , _ls ;
 {
   double _lBoltzmann;
 _lBoltzmann = 1.0 / ( 1.0 + exp ( ( _lv - _lv5 ) / _ls ) ) ;
   
return _lBoltzmann;
 }
 
static int _hoc_Boltzmann() {
  double _r;
   _r =  Boltzmann (  *getarg(1) , *getarg(2) , *getarg(3) ) ;
 ret(_r);
}
 
double BorgMod_tau (  _lv , _lv5 , _ls , _ltau0 , _ltauA , _ltauG , _ltauF , _ltauDv )  
	double _lv , _lv5 , _ls , _ltau0 , _ltauA , _ltauG , _ltauF , _ltauDv ;
 {
   double _lBorgMod_tau;
 double _lkc , _lkr , _lDv , _lwr ;
 _lkr = 1000.0 ;
   _lwr = 1000.0 ;
   _lDv = ( _lv - ( _lv5 + _ltauDv ) ) * 1.0 ;
   _lkc = _lkr * pow( 10.0 , _ltauF ) / _ls * 1.0 ;
   _lBorgMod_tau = _ltau0 + _ltauA * 2.0 * sqrt ( _ltauG * ( 1.0 - _ltauG ) ) * ( exp ( - _lDv * _ltauG / _lwr / _lkc ) + exp ( _lDv * ( 1.0 - _ltauG ) / _lwr / _lkc ) ) / ( exp ( - _lDv * ( 1.0 - _ltauG ) * _lkc / _lkr ) + exp ( _lDv * _lkc * _ltauG / _lkr ) ) ;
   
return _lBorgMod_tau;
 }
 
static int _hoc_BorgMod_tau() {
  double _r;
   _r =  BorgMod_tau (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) , *getarg(6) , *getarg(7) , *getarg(8) ) ;
 ret(_r);
}
 
double Boltz_m1 (  _lx , _lv5 , _ls )  
	double _lx , _lv5 , _ls ;
 {
   double _lBoltz_m1;
 _lBoltz_m1 = _ls * log ( 1.0 / _lx - 1.0 ) + _lv5 ;
   
return _lBoltz_m1;
 }
 
static int _hoc_Boltz_m1() {
  double _r;
   _r =  Boltz_m1 (  *getarg(1) , *getarg(2) , *getarg(3) ) ;
 ret(_r);
}
 
static int  ngate_adjust (  _lng , _lvh , _lslp )  
	double _lng , _lvh , _lslp ;
 {
   double _lx1 , _lx2 , _lv1 , _lv2 ;
 _lx1 = 0.3 ;
   _lx2 = 0.7 ;
   _lv1 = Boltz_m1 ( _threadargscomma_ _lx1 , _lvh , _lslp ) ;
   _lv2 = Boltz_m1 ( _threadargscomma_ _lx2 , _lvh , _lslp ) ;
   slp_adj = ( _lv2 - _lv1 ) / ( log ( pow( ( 1.0 / _lx2 ) , ( 1.0 / _lng ) ) - 1.0 ) - log ( pow( ( 1.0 / _lx1 ) , ( 1.0 / _lng ) ) - 1.0 ) ) ;
   v5_adj = _lv1 - slp_adj * log ( 1.0 / pow( _lx1 , ( 1.0 / _lng ) ) - 1.0 ) ;
    return 0; }
 
static int _hoc_ngate_adjust() {
  double _r;
   _r = 1.;
 ngate_adjust (  *getarg(1) , *getarg(2) , *getarg(3) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 6;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
     _ode_spec1 ();
  }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 6; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
 _ode_matsol1 ();
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h2 = h20;
  h = h0;
  n2 = n20;
  n = n0;
  s2 = s20;
  s = s0;
 {
   needAdj = 1.0 ;
   rates ( _threadargscomma_ v ) ;
   n = inf_n ;
   h = inf_h ;
   s = inf_s ;
   n2 = inf_n2 ;
   h2 = inf_h2 ;
   s2 = inf_s2 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  ena = _ion_ena;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   g = 0.0 ;
   g2 = 0.0 ;
   if ( n >= 0.0 ) {
     g = gbar * pow( n , gates_n ) * h * ( 1.0 + sfrac * ( s - 1.0 ) ) ;
     }
   if ( n2 >= 0.0 ) {
     g2 = gbar16 * pow( n2 , gates_n ) * h2 * ( 1.0 + sfrac2 * ( s2 - 1.0 ) ) ;
     }
   i = g * ( v - ena ) * ( 1e-4 ) + g2 * ( v - ena ) * ( 1e-4 ) ;
   ina = i ;
   }
 _current += ina;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  ena = _ion_ena;
 _g = _nrn_current(_v + .001);
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
 double _break, _save;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _break = t + .5*dt; _save = t;
 v=_v;
{
  ena = _ion_ena;
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 116 in file Naf2_i1.mod:\n  SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(n) - _p;  _dlist1[0] = &(Dn) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
 _slist1[2] = &(s) - _p;  _dlist1[2] = &(Ds) - _p;
 _slist1[3] = &(n2) - _p;  _dlist1[3] = &(Dn2) - _p;
 _slist1[4] = &(h2) - _p;  _dlist1[4] = &(Dh2) - _p;
 _slist1[5] = &(s2) - _p;  _dlist1[5] = &(Ds2) - _p;
_first = 0;
}
