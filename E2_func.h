/*
E2_func.h
 
*/

#ifndef _E2_func_h
#define _E2_func_h
#define n 32
extern void calc_acc(double *, double *, double,  int);

extern void calcModes(double *, double *, int, double [][n]);

extern void calcInvers(double *, double *, int, double [][n]);

extern double calcEnergy(double , double , double);

#endif
