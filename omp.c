#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <Windows.h>
#include <math.h>
#include "matrix.h"
#include "vector.h"
#include <omp.h>

int checkans(int a, double *oA, double *x, double *b)
{
	int i, r;
	int result = 0;
	double *re;

	re = (double *)malloc(a * sizeof(double));
	if (re == NULL)
		return -1;

	for (r = 0; r < a; r++)
	{
		re[r] = 0;
	}

	for (int p = 0; p < a; p++)
	{
		for (int q = 0; q < a; q++)
		{
			re[p] += oA[p * a + q] * x[q];
		}
	}

	for (i = 0; i < a; i++)
	{
		if (fabs(b[i] - re[i]) <= 0.0001)
		{
			result = result + 1;
		}
	}

	free(re);
	return (result);
}

int checkansO(int a, double *oA, double *x, double *b, int thread_count)
{
	int i, r, n, q, p;
	int result = 0, myresult = 0;
	double *re;

	re = (double *)malloc(a * sizeof(double));
	if (re == NULL)
		return -1;
	for (r = 0; r < a; r++)
	{
		re[r] = 0;
	}

#pragma omp for collapse(2)
	for (int p = 0; p < a; p++)
	{
		for (int q = 0; q < a; q++)
		{
			re[p] += oA[p * a + q] * x[q];
		}
	}

#pragma omp parallel for num_threads(thread_count) \
	reduction(+                                    \
			  : result) private(i)
	for (i = 0; i < a; i++)
	{
		if (fabs(b[i] - re[i]) <= 0.0001)
		{
			result = result + 1;
		}
	}
	free(re);
	return (result);
}

int main()
{
	double *A, *B, *y, *x, *oA, *oB, *tmp, *tmpO; /* A and B */
	//DWORD start, end;
	int a, b; /*size of A and B*/
	int i, j, k, n;
	int result, resultO;
	int index, indexO;
	int thread_count;
	double max, maxO;
	double start, startO, end, endO;
	double *AO, *BO, *yO, *xO, *oAO, *oBO;

	//generate A and B with input size
	srand((unsigned)time(NULL));
	printf("Please input a number: ");
	scanf("%d", &a);

	A = (double *)malloc(a * a * sizeof(double));
	if (A == NULL)
		return -1;

	oA = (double *)malloc(a * a * sizeof(double));
	if (oA == NULL)
		return -1;

	B = (double *)malloc(a * sizeof(double));
	if (B == NULL)
		return -1;

	oB = (double *)malloc(a * sizeof(double));
	if (oB == NULL)
		return -1;

	x = (double *)malloc(a * sizeof(double));
	if (x == NULL)
		return -1;

	y = (double *)malloc(a * sizeof(double));
	if (y == NULL)
		return -1;

	oAO = (double *)malloc(a * a * sizeof(double));
	if (oAO == NULL)
		return -1;

	oBO = (double *)malloc(a * sizeof(double));
	if (oBO == NULL)
		return -1;

	xO = (double *)malloc(a * sizeof(double));
	if (xO == NULL)
		return -1;

	yO = (double *)malloc(a * sizeof(double));
	if (yO == NULL)
		return -1;

	AO = (double *)malloc(a * a * sizeof(double));
	if (AO == NULL)
		return -1;

	BO = (double *)malloc(a * sizeof(double));
	if (BO == NULL)
		return -1;

	tmp = (double *)malloc(a * sizeof(double));
	if (tmp == NULL)
		return -1;

	tmpO = (double *)malloc(a * sizeof(double));
	if (tmpO == NULL)
		return -1;

	for (int w = 0; w < a; w++)
	{
		x[w] = 0;
		y[w] = 0;
		xO[w] = 0;
		yO[w] = 0;
	}

	for (int e = 0; e < a * a; e++)
	{
		oA[e] = 0;
		oAO[e] = 0;
	}

	Mat_Init(a, a, A);
	Vec_Init(a, B);

	for (int q = 0; q < a * a; q++)
	{
		oA[q] = A[q];
		oAO[q] = A[q];
		AO[q] = A[q];
	}

	for (int q = 0; q < a; q++)
	{
		oB[q] = B[q];
		BO[q] = B[q];
		oBO[q] = B[q];
	}
	start = 0;
	end = 0;
	// without using openmp
	start = clock();

	//partial pivoting
	index = 0;
	max = A[0];
	for (k = 0; k < a; k++)
	{
		if (A[k * a] > max)
		{
			index = k;
			max = A[k * a];
		}
	}

	for (k = 0; k < a; k++)
	{
		tmp[k] = A[k];
		A[k] = A[index * a + k];
		A[index * a + k] = tmp[k];
	}

	double tmp2 = 0.0;
	tmp2 = B[0];
	B[0] = B[index];
	B[index] = tmp2;

	for (k = 0; k < a; k++)
	{
		for (j = k + 1; j < a; j++)
		{
			A[k * a + j] = A[k * a + j] / A[k + k * a];
		}
		y[k] = B[k] / A[k + k * a];

		A[k + k * a] = 1;
		for (i = k + 1; i < a; i++)
		{
			for (j = k + 1; j < a; j++)
			{
				A[i * a + j] = A[i * a + j] - A[i * a + k] * A[k * a + j];
			}
			B[i] = B[i] - A[i * a + k] * y[k];
			A[i * a + k] = 0;
		}
	}
	for (k = a - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (i = k - 1; i >= 0; i--)
		{
			y[i] = y[i] - x[k] * A[i * a + k];
		}
	}
	result = checkans(a, oA, x, oB);
	//printf("%d ", result);
	if (result == a)
	{
		printf("The CPU ans is right!\n");
	}
	else
	{
		printf("The CPU ans is wrong!\n");
	}
	end = clock();
	double Total_time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("It takes %f seconds for no openmp\n", Total_time);

	//using openmp
	printf("Please input the number of threads: ");
	scanf("%d", &thread_count);

	startO = clock();

	/*
	for (i = 0; i < a - 1; i++)
	{
#pragma omp parallel for
		for (j = i; j < a; j++)
		{
			double ratio = AO[i * a + j] / AO[i * a + i];
			for (int k = i; k < a; k++)
			{
				AO[k * a + j] -= (ratio * AO[k * a + i]);
				BO[j] -= (ratio * BO[i]);
			}
		}
	}
	*/

	for (int norm = 0; norm < a - 1; norm++)
	{
#pragma omp parallel for shared(A, B) private(multiplier, row, col)
		for (int row = norm + 1; row < a; row++)
		{
			double multiplier = AO[row * a + norm] / AO[norm * a + norm];
			for (int col = norm; col < a; col++)
			{
				AO[row * a + col] -= AO[norm * a + col] * multiplier;
			}
			BO[row] -= BO[norm] * multiplier;
		}
	}

	// printf("after ge A:\n");
	// Mat_Show(a, a, A);
	// printf("after ge B:\n");
	// Vec_Show(a, B);

	/* Back substitution */

	/* Back substitution */
	for (int row = a - 1; row >= 0; row--)
	{
		xO[row] = BO[row];
		for (int col = a - 1; col > row; col--)
		{
			xO[row] -= AO[row * a + col] * xO[col];
		}
		xO[row] /= AO[row * a + row];
	}
	/*
	for (k = a - 1; k >= 0; k--)
	{
		xO[k] = yO[k];
//third
#pragma omp parallel for num_threads(thread_count)
		for (i = k - 1; i >= 0; i--)
		{
			yO[i] = yO[i] - xO[k] * AO[i * a + k];
		}
	}
	*/

	/*
	//partial pivoting
	indexO = 0;
	maxO = AO[0];

	for (k = 0; k < a; k++)
	{
		if (AO[k * a] > max)
		{
			indexO = k;
			maxO = AO[k * a];
		}
	}

	for (k = 0; k < a; k++)
	{
		tmpO[k] = AO[k];
		AO[k] = AO[indexO * a + k];
		AO[indexO * a + k] = tmpO[k];
	}

	double tmp2O = 0.0;
	tmp2O = BO[0];
	BO[0] = BO[indexO];
	BO[indexO] = tmp2O;
*/

	/*
	for (k = 0; k < a; k++)
	{
//the first
#pragma omp parallel for num_threads(thread_count)
		for (j = k + 1; j < a; j++)
		{
			AO[k * a + j] = AO[k * a + j] / AO[k + k * a];
		}
		yO[k] = BO[k] / AO[k + k * a];
		AO[k + k * a] = 1;
//the second
#pragma omp parallel for num_threads(thread_count) default(none) private(i, j) shared(a, AO, BO, yO, k)
		for (i = k + 1; i < a; i++)
		{
			for (j = k + 1; j < a; j++)
			{
				AO[i * a + j] = AO[i * a + j] - AO[i * a + k] * AO[k * a + j];
			}
			BO[i] = BO[i] - AO[i * a + k] * yO[k];
			AO[i * a + k] = 0;
		}
	}


		for (k = a - 1; k >= 0; k--)
		{
			xO[k] = yO[k];
//third
#pragma omp parallel for num_threads(thread_count)
			for (i = k - 1; i >= 0; i--)
			{
				yO[i] = yO[i] - xO[k] * AO[i * a + k];
			}
		}
		*/

	//forth
	resultO = checkansO(a, oAO, xO, oBO, thread_count);
	//resultO = checkans(a, oAO, xO, oBO);
	//printf("%d ", resultO);
	if (resultO == a)
	{
		printf("The CPU using openmp ans is right\n!");
	}
	else
	{
		printf("The CPU using openmp ans is wrong\n!");
	}
	endO = clock();
	double Total_timeO = (double)(endO - startO) / CLOCKS_PER_SEC;
	printf("It takes %f seconds for using openmp\n", Total_timeO);

	free(A);
	free(oA);
	free(B);
	free(x);
	free(oB);
	free(y);
	free(yO);
	free(AO);
	free(BO);
	free(oAO);
	free(oBO);
	free(xO);

	return (0);
}
