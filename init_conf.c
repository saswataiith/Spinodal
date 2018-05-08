#include"binary.h"

void Init_Conf()
{
FILE *fp;
char fn[100];
double *random_num;
double sum, mean;

random_num = (double*) malloc(sizeof(double) * nx * ny);
 
sum = 0.0;
 for (int j = 0; j < ny; j++) {
  for (int i = 0; i < nx; i++) {
    random_num[j + i * ny] = (double) rand() / RAND_MAX;
    random_num[j + i * ny] = 2.0 * random_num[j + i * ny] - 1.0;
    random_num[j + i * ny] *= noise_level;
    sum += random_num[j + i * ny];
  }
 } 
  
 mean = sum * one_by_nxny;  
    
 for (int j = 0; j < ny; j++) {
  for (int i = 0; i < nx; i++) {
        comp[j + i * ny][Re] = alloycomp + random_num[j + i * ny] - mean;
        comp[j + i * ny][Im] = 0.0;
  }
 }
 
          
 for (int j = 0; j < ny; j++) {
  for (int i = 0; i < nx; i++) {
   dfdc[j + i * ny][Re] = comp[j + i * ny][Re];
   dfdc[j + i * ny][Im] = comp[j + i * ny][Im];
  }
 }
 

 sprintf(fn, "profile.in");  
 if (!(fp = fopen (fn, "w"))) {
  printf ("File:%s could not be opened \n", fn);
  exit (1);
 }
 for (int j = 0; j < ny; j++) {
  for (int i = 0; i < nx; i++) {
   fprintf(fp,"%d\t%d\t%lf\n",j,i,comp[j+i*ny][Re]);
  }
 fprintf(fp,"\n");
 }
fclose(fp);
free(random_num); 
}

void Read_Restart()
{
 FILE *fpread;
 char fr[100];

 sprintf (fr,"conf.%06d", initcount);
 fpread = fopen (fr, "r");
 if(fread (&comp[0][0], sizeof(double), 2 * nx * ny, fpread));
 fclose (fpread);
 
 for (int j = 0; j < ny; j++) {
  for (int i = 0; i < nx; i++) {
   dfdc[j + i * ny][Re] = comp[j + i * ny][Re];
   dfdc[j + i * ny][Im] = comp[j + i * ny][Im];
  }
 }
}
