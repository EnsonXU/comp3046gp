/* A simple vector library */
#ifndef VECTOR_H
#define VECTOR_H

/* initialize a vector x */
void Vec_Init(int size, float *x); 

/* display a vector */
void Vec_Show(int size, float *x); 

/* return the mean value of the vector components */
float Vec_Mean(int size, float *x);

/* return the Euclidean norm (or L2 norm, length) of a vector x: ||x|| */
float Euclidean_Norm(int size, float *x);

/* add two vectors */
void Vec_Add(int size, float *x, float *y, float *z);

/* Generalized vector addition: y = ax + y */
void Vec_Axpy(int size, float *x, float *y, float a);

/* dot product: return the dot product of vectors x and y */
float Dot_Product(int size, float *x, float *y);

#endif