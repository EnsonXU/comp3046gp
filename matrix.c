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
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
			printf("%.4f ", X[col * i + j]);
		printf("\n");
	}
}


