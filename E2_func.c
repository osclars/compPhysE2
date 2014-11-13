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
void calc_acc(double *a, double *u, double alfa, int size_of_u)
{
    /* Declaration of variables */
    int i;
    
    /* Calculating the acceleration on the boundaries */
    a[0] = (- 2*u[0] + u[1])+alfa*((u[1]-u[0])*(u[1]-u[0])-u[0]*u[0]);
    a[size_of_u - 1] = (u[size_of_u - 2] - 2*u[size_of_u - 1])+alfa*(u[size_of_u-1]*u[size_of_u-1]-(u[size_of_u-1]-u[size_of_u-2])*(u[size_of_u-1]-u[size_of_u-2]));
    
    /* Calculating the acceleration of the inner points */
    for (i = 1; i < size_of_u - 1; i++){
        a[i] = (u[i - 1] - 2*u[i] + u[i + 1])+alfa*((u[i+1]-u[i])*(u[i+1]-u[i])-(u[i]-u[i-1])*(u[i]-u[i-1]));
    }
}


void calcModes(double *modes, double *u, int nbr_of_particles, double trans_matrix[][32])
{ 
    int i,k;

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
/* calc u or v from Q or P*/
void calcInvers(double *u, double *modes, int nbr_of_particles, double trans_matrix[][32])
{  
    int i,k;
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
