/*
 E2.c
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include"E2_func.h"
#define PI 3.141592653589

/* Main program */
int main()
{
	int nbr_of_particles;
	int nbr_of_timesteps, nPlotModes;
	int i,j,k;
	double timestep;
	double alfa,E;

	/*setting variables */
	nbr_of_timesteps =10000000 ; 
	timestep = 0.1;
	nbr_of_particles = 32;
	alfa = 0.1;
	nPlotModes =nbr_of_particles;/*how many mode energies that are saved*/
	/* Declaration of arrays */
	double u[nbr_of_particles],v[nbr_of_particles],a[nbr_of_particles];
	double Q[nbr_of_particles], P[nbr_of_particles], w[nbr_of_particles];

	/* constructing transformation matrix */
    double factor;
    double trans_matrix[nbr_of_particles][nbr_of_particles];
    
    factor = 1 / ((double) nbr_of_particles + 1.0);
    for (k=0; k < nbr_of_particles; k++) {
        for (i=0; i < nbr_of_particles; i++) {
            trans_matrix[i][k] = sqrt(2 * factor) * sin((i + 1) * (k + 1) * PI * factor);
        }
    }
    for (k=0; k < nbr_of_particles; k++){ 
		w[k] = 2 * sin((1+k)*PI/(double)(2*(nbr_of_particles+1)));
	}
	/* Initial condition */
	for (k=0; k < nbr_of_particles; k++){
		Q[k] = 0;
		P[k] = 0;
	}
	/* All energy in first P mode*/
	P[0] = sqrt(2.0*nbr_of_particles);
	
	/* make and open data file */
	FILE *d_file;
	d_file = fopen("modeEnergy.data","w");
	fprintf(d_file, "%.3f", 0.0);
	/*printf("T: %.3f\n", 0.0);*/
	for (k=0; k < nPlotModes; k++) {
		E = calcEnergy(P[k], Q[k], w[k]);
		fprintf(d_file, "\t %e", E);
		/*printf("E: %0.2f\tQ: %0.2f\tP: %0.2f\tw: %0.2f\n", E, Q[k], P[k], w);*/
	}
	fprintf(d_file, "\n");

	/* Calculate initial accelerations based on initial conditions */
	calcInvers(u, Q, nbr_of_particles, trans_matrix);
	calcInvers(v, P, nbr_of_particles, trans_matrix);
	calc_acc(a, u, alfa, nbr_of_particles);
    /* timesteps according to velocity Verlet algorithm */
	for (i = 1; i < nbr_of_timesteps + 1; i++){
		/* v(t+dt/2) */
		for (j = 0; j < nbr_of_particles; j++){
		    v[j] += timestep * 0.5 * a[j];
		} 
		/* u(t+dt) */
		for (j = 0; j < nbr_of_particles; j++){
		    u[j] += timestep * v[j];
		}

		/* a(t+dt) */
		calc_acc(a, u, alfa, nbr_of_particles);

		/* v(t+dt) */
		for (j = 0; j < nbr_of_particles; j++){
		    v[j] += timestep * 0.5 * a[j];
		} 
		/* only print every 1000th step */
		if (i % 1000 == 0 ){
			calcModes(Q, u, nbr_of_particles, trans_matrix);
			calcModes(P, v, nbr_of_particles, trans_matrix);
			fprintf(d_file, "%.3f", i*timestep);
			/*printf("\nT: %.3f\n", i*timestep);*/
			for (k=0; k < nPlotModes; k++){
				E=calcEnergy(P[k], Q[k], w[k]);
				fprintf(d_file, "\t %e", E);
				/*printf("E: %0.2f\tQ: %0.2f\tP:%0.2f\tw:%0.2f\n", E, Q[k], P[k], w);*/
			}
			fprintf(d_file, "\n");
		}
	}
	fclose(d_file);
	return 0;
}
