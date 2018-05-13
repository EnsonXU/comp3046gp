/* A simple vector library */
#ifndef VECTOR_H
#define VECTOR_H

/* initialize a vector x */
void Vec_Init(int size, double *x); 

/* display a vector */
void Vec_Show(int size, double *x); 

/* return the mean value of the vector components */
double Vec_Mean(int size, double *x);

/* return the Euclidean norm (or L2 norm, length) of a vector x: ||x|| */
double Euclidean_Norm(int size, double *x);

/* add two vectors */
void Vec_Add(int size, double *x, double *y, double *z);

/* Generalized vector addition: y = ax + y */
void Vec_Axpy(int size, double *x, double *y, double a);

/* dot product: return the dot product of vectors x and y */
double Dot_Product(int size, double *x, double *y);

#endif