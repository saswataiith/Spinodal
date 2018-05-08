#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<fftw3.h>
#define PI acos(-1.0) 
#define Tolerance 1.0e-08
#define COMPERR 1.0e-8
#define Re 0
#define Im 1 

// FFTW related
unsigned fftw_flag;

// Variables : composition field, derivative of bulk free energy w.r.t. composition
fftw_complex *comp, *dfdc;

//p_up for forward transform and p_dn for backward transform
fftw_plan p_up, p_dn;

//total number of simulation steps
int num_steps;

//Configuration to be initialized or to be read
int initcount, initflag;

// Alloy composition, amplitude of white noise to be added to the system
double alloycomp, noise_level; 

//Step size along x and y, timestep
double dx, dy, dt;

//Total simulation time (nondimensional)
double sim_time, total_time;

//System dimensions along x and y
int nx, ny, nx_half, ny_half;

//Bulk free energy coefficients
double A;

//Gradient energy coefficients associated with composition and structural
//order parameter fields
double kappa_c;

//Mobility of solute required for CH equation (mobility)
//Relaxation coefficient for CA equation (relax_coeff)
double mobility;
 
//Required for scaling
double one_by_nxny;

FILE *fpout;
