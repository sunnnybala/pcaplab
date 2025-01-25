#include "mpi.h"      
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size,N,A[100],B[100],c[100],i, sum, M, j, temp;   
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (rank==0){
        fprintf(stdout, "enter M value in process 0: \n");
        scanf("%d", &M);
        N = size;
        fprintf(stdout, "enter %d values in process 0: \n",N*M);
        for (i=0;i<N*M;i++){
            scanf("%d", &A[i]);
        }
        fflush(stdout);
    }
    MPI_Bcast(&M, 1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(&A[rank*M],M,MPI_INT, c, M, MPI_INT,0,MPI_COMM_WORLD);
    fprintf(stdout, "i have recieved values in process %d \n",rank);
    //fprintf(stdout, "M value in process %d is %d\n",rank,M);
    sum =0 ;
    for (j=0;j<M;j++){
        sum+=c[j];
        fprintf(stdout, "%d\t", c[j]);
    }
    fflush(stdout);
    
    sum = sum/M;
    MPI_Gather(&sum,1,MPI_INT, B, 1, MPI_INT,0,MPI_COMM_WORLD);
   if (rank==0){
        fprintf(stdout, "result gathered in root \n");
        sum =0;
        for (i=0;i<N;i++){
            printf( "%d\t",B[i]);
            sum=sum+B[i];
        }
        fprintf(stdout, "fimal answer is is %d \n", sum/N);
        
    }
    MPI_Finalize();
    return 0;
}