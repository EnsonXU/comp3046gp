/* a simple library of matrix operations */
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

/* initialize a matrix x. You need to call srand() in advance. */
void Mat_Init(int row, int col, double *X)
{
    int i, size;

    size = row * col;
    for (i = 0; i < size; i++)
        X[i] = ((double)rand()) / ((double)RAND_MAX);
}

/* display a matrix */
void Mat_Show(int row, int col, double *X)
{
    int i, j;
    printf("row = %d col = %d\n", row, col);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            printf("%.4f ", X[col * i + j]);
        printf("\n");
    }
}

/* transpose a matrix: Y = transpose(X) */
void Mat_Transpose(int row, int col, double *X, double *Y)
{
    int i, j;
    for (i = 0; i < row; i++)
        for (j = 0; j < row; j++)
            Y[row * j + i] = X[col * i + j];
}

/* add two matrices: Z = X + Y */
void Mat_Add(int row, int col, double *X, double *Y, double *Z)
{
    int i, j, index;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
        {
            index = col * i + j;
            Z[index] = X[index] + Y[index];
        }
}

/* scalar matrix multiplication: Y = aX where a is a scalar */
void Mat_aX(int row, int col, double *X, double *Y, double a)
{
    int i, j, index;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
        {
            index = col * i + j;
            Y[index] = a * X[index];
        }
}

/* vector matrix multiplication: Y = vX where v and Y are vectors, X is a (row, col) matrix */
void Mat_vX(int row, int col, double *X, double *Y, double *v)
{
    int i, j;
    for (i = 0; i < col; i++)
    {
        Y[i] = 0;
        for (j = 0; j < row; j++)
            Y[i] += v[j] * X[col * j + i];
    }
}

/* matrix vector multiplication: Y = Xv where v is a vector */
void Mat_Xv(int row, int col, double *X, double *Y, double *v)
{
    /* please complete this function */
    int i, j;
    for (i = 0; i < row; i++)
    {
        Y[i] = 0;
        for (j = 0; j < col; j++)
            Y[i] += v[j] * X[row * j + i];
    }
}

/* matrix matrix multiplication: Z = XY */
void Mat_XY(int m, int k, int n, double *X, double *Y, double *Z)
{
    float z;
    int i, j, p;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
            z = 0;
            for (p = 0; p < k; p++)
                z += X[k * i + p] * Y[n * p + j];
            Z[n * i + j] = z;
        }
}
