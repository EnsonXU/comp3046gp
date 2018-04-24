#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "vector.h"

int main()
{
    double *A, *B, *y, *x, *U, *r; /* A and B */
    int a, b;                      /*size of A and B*/
    int i, j, k, n;

    //generate A and B with random size
    srand((unsigned)time(NULL));
    a = (int)((rand() % (9)) + 1);

    A = (double *)malloc(a * a * sizeof(double));
    if (A == NULL)
        return -1;

    B = (double *)malloc(a * sizeof(double));
    if (B == NULL)
        return -1;

    r = (double *)malloc(a * sizeof(double));
    if (r == NULL)
        return -1;

    U = (double *)malloc(a * a * sizeof(double));
    if (U == NULL)
        return -1;

    x = (double *)malloc(a * sizeof(double));
    if (x == NULL)
        return -1;

    y = (double *)malloc(a * a * sizeof(double));
    if (y == NULL)
        return -1;

    Mat_Init(a, a, A);
    Vec_Init(a, B);

    Mat_Show(a, a, A);
    Vec_Show(a, B);

    //initialize the U
    int count = 0;
    for (i = 0; i < a; i++)
    {
        count = 0;
        for (j = 0; j < a; j++)
        {
            if (count < i)
            {
                U[i * a + j] = 0;
                count++;
            }
            else
            {
                U[i * a + j] = 1;
            }
        }
    }

    //Mat_Show(a, a, U);

    // n-1 = col = row = a

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

    for (k = a; k > 0; k--)
    {
        x[k] = y[k];
        for (i = k - 1; i > 0; i--)
        {
            y[i] = y[i] - x[k] * U[i * a + k];
        }
    }

    printf("\nThe solution is: \n");
    Vec_Show(a, x);
    /*
    printf("vector size = %d\n", a);
    for (i = 0; i < a; i++)
        printf("%f ", x[i]);
    printf("\n");
    */

    Mat_Xv(a,a,A,r,x);
    Vec_Show(a,r);
   

/*
    for (i = 0; i < a; i++)
    {
        if (r[i] == fabs(B[i]))
        {
            printf("Correct\n");
        }
        else
        {
            printf("Wrong!!!\n");
        }
    }
    */

    return (0);
}