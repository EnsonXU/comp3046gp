#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "vector.h"

int checkans(int a, double *oA, double *x, double *b)
{
    int i;
    int result = 0;
    double *re;

    re = (double *)malloc(a * sizeof(double));
    if (re == NULL)
        return -1;

    for (int r; r < a; r++)
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
        if (fabs(b[i] - re[i]) <= 0.0000001)
        {
            result = result + 1;
        }
    }

    return (result);
}

int main()
{
    double *A, *B, *y, *x, *oA, *oB, *tmp; /* A and B */
    int a, b;                              /*size of A and B*/
    int i, j, k, n;
    double max;
    int result, index;

    //generate A and B with random size
    srand((unsigned)time(NULL));
    a = (int)((rand() % (9)) + 1);

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

    tmp = (double *)malloc(a * sizeof(double));
    if (tmp == NULL)
        return -1;

    for (int w = 0; w < a; w++)
    {
        x[w] = 0;
        y[w] = 0;
        tmp[w] = 0;
    }

    for (int e = 0; e < a * a; e++)
    {
        oA[e] = 0;
    }

    Mat_Init(a, a, A);
    Vec_Init(a, B);

    for (int q = 0; q < a * a; q++)
    {
        oA[q] = A[q];
    }

    for (int q = 0; q < a; q++)
    {
        oB[q] = B[q];
    }
    printf("A:\n");
    Mat_Show(a, a, A);
    printf("B:\n");
    Vec_Show(a, B);

    //partial pivoting
    /*
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

    printf("max index: %d\n", index);
    printf("max: %f\n", A[index * a]);

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

    printf("after pp A:\n");
    Mat_Show(a, a, A);
    printf("after pp B:\n");
    Vec_Show(a, B);
    */

    // n = col = row = a

    for (k = 0; k < a; k++)
    {
        // printf("The %d th iteration:\n", k);
        // printf("A:\n");
        // Mat_Show(a, a, A);
        // printf("B:\n");
        // Vec_Show(a, B);

        //partial pivoting
        index = k;
        max = A[k * a + k];
        for (int q = k; q < a; q++)
        {
            if (A[q * a + k] > max)
            {
                index = q;
                max = A[q * a + k];
            }
        }

        //printf("The index is: %d\n", index);

        for (int p = k; p < a; p++)
        {
            double tmp = A[k * a + p];
            A[k * a + p] = A[index * a + p];
            A[index * a + p] = tmp;
        }

        double tmp2 = 0.0;
        tmp2 = B[k];
        B[k] = B[index];
        B[index] = tmp2;

        // printf("after pp A:\n");
        // Mat_Show(a, a, A);
        // printf("after pp B:\n");
        // Vec_Show(a, B);
        // printf("\n");

        for (j = k + 1; j < a; j++)
        {
            A[k * a + j] = A[k * a + j] / A[k + k * a];
        }
        y[k] = B[k] / A[k + k * a];
        //printf("A now is \n %f, ",A[k + k * a]);
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
    //printf("y:\n");
    //Vec_Show(a, y);
    // printf("after calculation A:\n");
    // Mat_Show(a, a, A);
    /*
    printf("after calculation B:\n");
    Vec_Show(a, B);
    */

    for (k = a - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (i = k - 1; i >= 0; i--)
        {
            y[i] = y[i] - x[k] * A[i * a + k];
            /*
              int num = i;
              int num1 = k;
            int num2 = k + i * a;
            printf("%d, %d, %d\n",num,num1,num2);
            */
        }
    }

    printf("\nThe solution is: \n");
    Vec_Show(a, x);

    result = checkans(a, oA, x, oB);
    printf("%d ", result);
    if (result == a)
    {
        printf("The ans is right!");
    }
    else
    {
        printf("The ans is wrong!");
    }

    free(A);
    free(oA);
    free(B);
    free(oB);
    free(x);
    free(y);
    // free(re);

    return (0);
}