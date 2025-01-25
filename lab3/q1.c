#include "mpi.h"      
#include <stdio.h>

int factorial(int n){
	if(n==1 || n==0) return 1;
	return n * factorial(n-1);
}

int main(int argc, char *argv[]) {
    int rank, size,N,A[10],B[10],c,i, sum;   
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (rank==0){
        N = size;
        printf("enter %d values in process 0: \n",N);
        
        for (i=0;i<N;i++){
            scanf("%d", &A[i]);
        }
    }
    MPI_Scatter(A,1,MPI_INT, &c, 1, MPI_INT,0,MPI_COMM_WORLD);
    printf("i have recieved %d in process %d \n",c,rank);
    
    c = factorial(c);
    MPI_Gather(&c,1,MPI_INT, B, 1, MPI_INT,0,MPI_COMM_WORLD);
   if (rank==0){
        printf("result gathered in root \n");
        sum =0;
        for (i=0;i<N;i++){
            printf( "%d\t",B[i]);
            sum=sum+B[i];
        }
        printf("fimal sum is %d \n", sum);
        
    }
    MPI_Finalize();
    return 0;
}