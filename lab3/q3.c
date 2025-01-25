#include "mpi.h"      
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    int rank, size,N,A[100],B[100],c[100],i, sum, M, j, temp;
    char s[100], t[100], check[5]={'a','e', 'i', 'o', 'u'};   
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (rank==0){
        fprintf(stdout, "enter the string in process 0: \n");
        scanf("%s", s);
        N = size;
        M= strlen(s)/N;
        printf("%s\n", s);
        fflush(stdout);
    }
    MPI_Bcast(&M, 1,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Scatter(&s[rank*M],M,MPI_CHAR, t, M, MPI_CHAR,0,MPI_COMM_WORLD);
    t[M]='\0';
    fprintf(stdout, "i have recieved values in process %d \n",rank);
    printf("%s\n", t);
    sum  =M;
    for (j=0;j<M;j++){
        for(i = 0; i<5; i++){
            if (t[j] == check[i]){
                sum =sum-1;
                break;
            }
        }
        
    }
    fflush(stdout);
    MPI_Gather(&sum,1,MPI_INT, B, 1, MPI_INT,0,MPI_COMM_WORLD);
   if (rank==0){
        fprintf(stdout, "result gathered in root \n");
        sum =0;
        for (i=0;i<N;i++){
            printf( "%d\t",B[i]);
            sum=sum+B[i];
        }
        fprintf(stdout, "fimal answer is is %d \n", sum);
        
    }
    MPI_Finalize();
    return 0;
}