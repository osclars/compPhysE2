/*
E2_func.c
 
*/

#include <math.h>
#define PI 3.141592653589

/*
Function that calculates the acceleration based on the Hamiltonian.
The acceleration is calculated based on the displacements u and then stored in a
u and a should be vectors of the same size, size_of_u
*/
void calc_acc(double *a, double *u,  int size_of_u)
{
    /* Declaration of variables */
    int i;
    
    /* Calculating the acceleration on the boundaries */
    a[0] = (- 2*u[0] + u[1]);
    a[size_of_u - 1] = (u[size_of_u - 2] - 2*u[size_of_u - 1]);
    
    /* Calculating the acceleration of the inner points */
    for (i = 1; i < size_of_u - 1; i++){
        a[i] = (u[i - 1] - 2*u[i] + u[i + 1]);
    }
}


void calcModes(double *modes, double *u, int nbr_of_particles)
{ 
    int i,k;
    double factor;
    double trans_matrix[nbr_of_particles][nbr_of_particles];
    
    factor = 1 / ((double) nbr_of_particles + 1);
    for (k=0; k < nbr_of_particles; k++) {
        for (i=0; i < nbr_of_particles; i++) {
            trans_matrix[k][i] = sqrt(2 * factor) * sin((i + 1) * (k + 1) * PI * factor);
        }
    }


    /* Transformation to normal modes Q from displacements q.  */
    double sum;
    for (k = 0; k < nbr_of_particles; k++){
        sum = 0;
        for (i = 0; i < nbr_of_particles; i++){
            sum += u[i] * trans_matrix[k][i];
        }
        modes[k] = sum;
    }
}

void calcInvers(double *u, double *modes, int nbr_of_particles)
{  
    int i,k;
    double factor;
    double trans_matrix[nbr_of_particles][nbr_of_particles];
    
    factor = 1 / ((double) nbr_of_particles + 1.0);
    for (k=0; k < nbr_of_particles; k++) {
        for (i=0; i < nbr_of_particles; i++) {
            trans_matrix[i][k] = sqrt(2 * factor) * sin((i + 1) * (k + 1) * PI * factor);
        }
    }
    
    /* Transformation to normal modes Q from displacements q.  */
    double sum;
    for (k = 0; k < nbr_of_particles; k++){
        sum = 0;
        for (i = 0; i < nbr_of_particles; i++){
            sum += modes[i] * trans_matrix[k][i];
        }
        u[k] = sum;
    }
}

double calcEnergy(double P, double Q, double w)
{
	double E;
	E = (P*P+w*w*Q*Q)/2.0;
	return E;
}

