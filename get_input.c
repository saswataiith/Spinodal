#include"binary.h"
void Get_Input_Parameters (char *fnin, char *fnout)
{
 FILE *fpin, *fpcout;
 char param[100], fn[100];

 if (!(fpcout = fopen (fnout, "w"))) {
  printf ("File:%s could not be opened \n", fnout);
  exit (1);
 }
 fprintf (fpcout, "The name of this file is : %s \n", fnout);
 fprintf (fpcout, "Input is from            : %s \n", fnin);

 if (!(fpin = fopen (fnin, "r"))) {
  printf ("File: %s could not be opened \n", fnin);
  exit (1);
 }

 if(fscanf (fpin, "%s%d", param,&nx));
 if(fscanf (fpin, "%s%d", param,&ny));
 if(fscanf (fpin, "%s%lf",param,&dx));
 if(fscanf (fpin, "%s%lf",param,&dy));
 if(fscanf (fpin, "%s%le",param,&dt));
 if(fscanf (fpin, "%s%d", param,&num_steps));
 if(fscanf (fpin, "%s%lf", param, &A));
 if(fscanf (fpin, "%s%lf",param,&alloycomp));
 if(fscanf (fpin, "%s%lf", param, &kappa_c));
 if(fscanf (fpin, "%s%lf", param, &mobility));
 if(fscanf (fpin, "%s%lf", param, &noise_level));
 if(fscanf (fpin, "%s%d", param,&initflag));
 if(fscanf (fpin, "%s%d", param,&initcount));
 if(fscanf (fpin, "%s%d", param,&fftw_flag));
 fclose (fpin);
 
 printf("nx=%d\n",nx);
 printf("ny=%d\n",ny);
 printf("dx=%lf\n",dx);
 printf("dy=%lf\n",dy);
 printf("dt=%le\n",dt); 
 printf("Simulation steps = %d\n", num_steps);
 printf("Bulk free energy coefficients A=%lf\n",A);
 printf("Alloy composition = %lf\n", alloycomp);
 printf("Kappa_c = %lf\n", kappa_c);
 printf("Mobility = %lf\n", mobility);
 printf("Initflag = %d\n", initflag);
 printf("File read from steps = %d\n", initcount);
 if(kappa_c <= 1.0e-08) {
  printf("Warning: too small or negative values for gradient energy coefficients\n");
  printf("Using default values\n");
  kappa_c = 1.0;
 }
 if(mobility <= 1.0e-08) {
  printf("Warning: too small or negative values for kinetic coefficient\n");
  printf("Using default values\n");
  mobility = 1.0;
 }
 if(initflag == 0) {
  printf("Configuration initialized by me\n");
  initcount = 0;
 } else {
  sprintf(fn,"conf.%06d", initcount);     
  printf("Configuration read from file %s\n",fn);
 }
 printf("FFTW_FLAG = %d\n",fftw_flag);
}
