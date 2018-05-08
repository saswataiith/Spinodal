#include"binary.h"
void Evolve()
{
 
void Output_Conf (int steps);

int loop_condition, count;

double dkx, dky, kx, ky, kpow2, kpow4;

double rc, fp, rc_new;

double total;
 
double *tempreal;
 
double lhs, rhs;

double err, maxerror;

tempreal = (double *) malloc(sizeof(double) * nx * ny);

dkx = 2.0 * PI / ((double) nx * dx);
dky = 2.0 * PI / ((double) ny * dy);

 
 for (int j = 0; j < ny; j++) 
  for (int i = 0; i < nx; i++)
   tempreal[j + i * ny] = comp[j + i * ny][Re];
 
loop_condition = 1;

fftw_execute_dft (p_up, comp, comp);
alloycomp = comp[0][Re] * one_by_nxny;

//Start the evolution

 for (count = 0; count <= num_steps; count++) {
  
  if (((count % 200)==0) || (count == num_steps) || (loop_condition == 0)) {
   printf ("total_time=%lf\n", sim_time);
   printf ("writing configuration to file!\n");
   Output_Conf(count);
  }
  
  if (count > num_steps || loop_condition == 0)
  break;

// Evaluate dfdc in real space
 for (int j = 0; j < ny; j++) {
  for (int i = 0; i < nx; i++) {
   double ctemp;
   ctemp = dfdc[j + i * ny][Re];
   dfdc[j + i * ny][Re] = 2.0 * A * ctemp * (1.0 - ctemp) * (1.0 - 2.0 * ctemp); 
   dfdc[j + i * ny][Im] = 0.0;
  }
 }
  
fftw_execute_dft (p_up, dfdc, dfdc);

 for (int j = 0; j < ny; j++) {
  if (j <= ny_half)
   ky = (double) j * dky;
  else
   ky = (double) (j - ny) * dky;
   
  ky = ky * ky;
   
  for (int i = 0; i < nx; i++) {
   if (i <= nx_half)
    kx = (double) i * dkx;
   else
    kx = (double) (i - nx) * dkx;
    
  kx = kx * kx;
  kpow2 = kx + ky;
  kpow4 = kpow2 * kpow2;

  lhs = 1.0 + 2.0 * mobility * kappa_c * kpow4 * dt;
    
  rc = comp[j + i * ny][Re];
  fp = dfdc[j + i * ny][Re];
  rhs = rc - mobility * kpow2 * dt * fp;
  rc_new = rhs / lhs;
  comp[j + i * ny][Re] = rc_new;
  dfdc[j + i * ny][Re] = comp[j + i * ny][Re];

  rc = comp[j + i * ny][Im];
  fp = dfdc[j + i * ny][Im];
  rhs = rc - mobility * kpow2 * dt * fp;
  rc_new = rhs / lhs;
  comp[j + i * ny][Im] = rc_new;
  dfdc[j + i * ny][Im] = comp[j + i * ny][Im];
  }
 }

/* Check for conservation of mass */
  total = dfdc[0][Re] * one_by_nxny;
  err = fabs (total - alloycomp);
  if (err > COMPERR) {
   printf ("ELEMENTS ARE NOT CONSERVED,SORRY!!!!\n");
   printf ("error=%lf\n", err);
   exit (0);
  }

  fftw_execute_dft (p_dn, dfdc, dfdc);

  for (int j = 0; j < ny; j++) {
   for (int i = 0; i < nx; i++) {
    dfdc[j + i * ny][Re] *= one_by_nxny;
    dfdc[j + i * ny][Im] *= one_by_nxny;
   }
  }


/* Check for bounds */
   for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
     if (dfdc[j + i * ny][Re] < -0.2
        || dfdc[j + i * ny][Re] > 1.2) {
     printf ("Compositions out of bounds. Exiting\n");
     exit (0);
    }
   }
  }

  
/* Check for convergence */
  maxerror = 0.0;
   for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
      err = fabs (tempreal[j + i * ny] - dfdc[j + i * ny][Re]);
      if (err > maxerror)
     maxerror = err;
   }
  }
  if (maxerror <= Tolerance) {
   printf ("maxerror=%lf\tnumbersteps=%d\n", maxerror, count);
   loop_condition = 0;
  }
  sim_time = sim_time + dt;
  printf("time=%lf\n", sim_time);
  for (int j = 0; j < ny; j++) {
   for (int i = 0; i < nx; i++) {
    tempreal[j + i * ny] = dfdc[j + i * ny][Re];
   }
  }
 }
}
