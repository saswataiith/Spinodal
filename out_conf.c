#include"binary.h"
void Output_Conf (int steps)
{
 FILE *fpt;
 
 char fn[100];

 sprintf (fn, "conf.%06d", steps);

 fpt = fopen (fn, "w");
 fwrite (&dfdc[0][0], sizeof(double), 2 * nx * ny, fpt);
 fclose (fpt);

 sprintf (fn, "prof_gp.%06d", steps);
 fpt = fopen (fn, "w");
 for (int j = 0; j < ny; j++) {
	for (int i = 0; i < nx; i++) {
	 fprintf(fpt,"%d\t%d\t%lf\n",j,i,dfdc[j+i*ny][Re]);
	}
  fprintf(fpt,"\n");
 }
 fclose(fpt); 
}
