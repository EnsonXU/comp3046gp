/* matrix.h */
#ifndef MATRIX_H
#define MATRIX_H

/* initialize a matrix x */
void Mat_Init(int row, int col, double *X); 

/* display a matrix */
void Mat_Show(int row, int col, double *X); 

/* transpose a matrix: Y = transpose(X) */
void Mat_Transpose(int row, int col, double *X, double *Y);

/* add two matrices: Z = X + Y */
void Mat_Add(int row, int col, double *X, double *Y, double *Z);

/* scalar matrix multiplication: Y = aX where a is a scalar */
void Mat_aX(int row, int col, double *X, double *Y, double a);

/* vector matrix multiplication: Y = vX where v is a vector */
void Mat_vX(int row, int col, double *X, double *Y, double *v);

/* matrix vector multiplication: Y = Xv where v is a vector */
void Mat_Xv(int row, int col, double *X, double *Y, double *v);

/* matrix matrix multiplication: Z = XY */
void Mat_XY(int m, int k, int n, double *X, double *Y, double *Z);

#endif