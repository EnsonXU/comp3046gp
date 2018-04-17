#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

int main()
{ 
    double *A, *B; /* A and B */
	int m, k, n; /*size of A and B*/
    int i;
    
    //generate A and B with random size
    int *i_array;
    printf("***");
    
    
    srand( (unsigned)time( NULL ) );
	for(i = 0; i < 3; i++) {
		i_array[i] = (int) rand()/RAND_MAX * 10;
	} 
    m = i_array[0];
    k = i_array[1];
    n = i_array[2];
    printf("%d %d %d",m,k,n);
    
    
    /*
	A = (double*)malloc(m*k*sizeof(double));
	if(A == NULL)
		return -1;

	B = (double*)malloc(k*n*sizeof(double));
	if(B == NULL)
		return -1;
        
	Mat_Init(m, k, A);
	Mat_Init(k, n, B);
    
	Mat_Show(m, k, A);
	Mat_Show(k, n, B);
    */

    // for(j=0; j<=n-1; j++) /* loop for the generation of upper triangular matrix*/
    // {
    //     for(i=j+1; i<=n-1; i++)
    //     {
    //         if(i>j)
    //         {
    //             c=A[i][j]/A[j][j];
    //             for(k=1; k<=n+1; k++)
    //             {
    //                 A[i][k]=A[i][k]-c*A[j][k];
    //             }
    //         }
    //     }
    // }
    // x[n]=A[n][n+1]/A[n][n];
    // /* this loop is for backward substitution*/
    // for(i=n-1; i>=1; i--)
    // {
    //     sum=0;
    //     for(j=i+1; j<=n; j++)
    //     {
    //         sum=sum+A[i][j]*x[j];
    //     }
    //     x[i]=(A[i][n+1]-sum)/A[i][i];
    // }
    // printf("\nThe solution is: \n");
    // for(i=1; i<=n; i++)
    // {
    //     printf("\nx%d=%f\t",i,x[i]); /* x1, x2, x3 are the required solutions*/
    // }
    return(0);
}