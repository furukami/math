#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100000

int main(void){
	double rd,xr,yr,pi;
	unsigned int now;
	int i,n = 0;
	FILE *fp1,*fp2,*gp;
	
	fp1 = fopen("enshuuin.d","w");
	fp2 = fopen("enshuuout.d","w");
	now = (unsigned int)time(0);
	srand48(now);
	for(i = 0;i<N;i++){
		xr = drand48();
		yr = drand48();
		if(xr*xr+yr*yr < 1.0){
			fprintf(fp1,"%f %f\n",xr,yr);
			n++;
		}else{
			fprintf(fp2,"%f %f\n",xr,yr);
		}
	}
	pi = (double)n/N*4;
	printf("pi = %f\n",pi);
	printf("M_PI =  %.f\n",M_PI);
	printf("Relative error = %f\n",fabs(pi-M_PI)/M_PI);
	fclose(fp1);
	fclose(fp2); 

	gp = popen("gnuplot -persist","w");
	fprintf(gp,"set xrange[-0.1:1.1]\n");
	fprintf(gp,"set yrange[-0.1:1.1]\n");
	fprintf(gp,"set size square\n");
	fprintf(gp,"plot \"enshuuin.d\",\"enshuuout.d\",sqrt(1-x*x)\n");
	fprintf(gp,"set terminal postscript eps\n");
	fprintf(gp,"set output \"enshuu.eps\"\n");
	fprintf(gp,"replot\n");
	fprintf(gp,"exit\n");
	pclose(gp);
	return 0;
}
