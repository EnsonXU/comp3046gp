#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

int main()
{ 
    double *X, *Y, *Z; /* matrices */
	int m, k, n;

	printf("Please input three positive integers:");
	scanf("%d%d%d", &m, &k, &n);

	X = (double*)malloc(m*k*sizeof(double));
	if(X == NULL)
		return -1;

	Y = (double*)malloc(k*n*sizeof(double));
	if(Y == NULL)
		return -1;

	Z = (double*)malloc(m*n*sizeof(double));
	if(Y == NULL)
		return -1;
        
	Mat_Init(m, k, X);
	Mat_Init(k, n, Y);
    
	Mat_Show(m, k, X);
	Mat_Show(k, n, Y);
	Mat_Show(m, n, Z);


    for(j=0; j<=n-1; j++) /* loop for the generation of upper triangular matrix*/
    {
        for(i=j+1; i<=n-1; i++)
        {
            if(i>j)
            {
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x[n]=A[n][n+1]/A[n][n];
    /* this loop is for backward substitution*/
    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
        {
            sum=sum+A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-sum)/A[i][i];
    }
    printf("\nThe solution is: \n");
    for(i=1; i<=n; i++)
    {
        printf("\nx%d=%f\t",i,x[i]); /* x1, x2, x3 are the required solutions*/
    }
    return(0);
}