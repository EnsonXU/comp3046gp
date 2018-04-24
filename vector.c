/* implementation of vector operations */
#include "vector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* initialize a vector x */
void Vec_Init(int size, double *x)
{
    int i;

    for (i = 0; i < size; i++)
        x[i] = ((double)rand()) / ((double)RAND_MAX);
}

/* display a vector */
void Vec_Show(int size, double *x)
{
    int i;

    printf("vector size = %d\n", size);
    for (i = 0; i < size; i++)
        printf("%.4f ", x[i]);
    printf("\n");
}

/* return the mean value of the vector components */
double Vec_Mean(int size, double *x)
{
    double sum = 0.0;
    int i;
    for (i = 0; i < size; i++)
        sum += x[i];
    if (size != 0)
        return (double)sum / size;
    else
        return 0;
}

/* return the Euclidean norm (or L2 norm, length) of a vector x: ||x|| */
double Euclidean_Norm(int size, double *x)
{
    double sum = 0.0;
    int i;
    for (i = 0; i < size; i++)
        sum += x[i] * x[i];
    return sqrt(sum);
}

/* add two vectors */
void Vec_Add(int size, double *x, double *y, double *z)
{
    int i;
    for (i = 0; i < size; i++)
        z[i] = x[i] + y[i];
}

/* Generalized vector addition: y = ax + y */
void Vec_Axpy(int size, double *x, double *y, double a)
{
    int i;
    for (i = 0; i < size; i++)
        y[i] += a * x[i];
}

/* dot product: return the dot product of vectors x and y */
double Dot_Product(int size, double *x, double *y)
{
    /* Please complete this function */
    int i;
    double z = 0;
    for (i = 0; i < size; i++)
    {
        z += x[i] * y[i];
    }
    return z;
}