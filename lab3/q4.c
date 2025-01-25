#include "mpi.h"      
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    int rank, size,N,A[100],c[100],i, sum, M, j, temp;
    char s1[100], s2[100], t1[100], t2[100], B[100], ans[100], final[100];   
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (rank==0){
        fprintf(stdout, "enter the string in process 0: \n");
        scanf("%s", s1);
        fprintf(stdout, "enter the string 2 in process 0: \n");
        scanf("%s", s2);
        N = size;
        M= strlen(s1)/N;
        printf("%s\n", s1);
        printf("%s\n", s2);
        fflush(stdout);
    }
    MPI_Bcast(&M, 1,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Scatter(&s1[rank*M],M,MPI_CHAR, t1, M, MPI_CHAR,0,MPI_COMM_WORLD);
    t1[M]='\0';
    MPI_Scatter(&s2[rank*M],M,MPI_CHAR, t2, M, MPI_CHAR,0,MPI_COMM_WORLD);
    t2[M]='\0';
    fprintf(stdout, "i have recieved values in process %d \n",rank);
    printf("%s\n", t1);
    printf("%s\n", t2);
    for (j=0;j<2*M;j=j+2){
        int temp = j/2;
        ans[j]=t1[temp];
        ans[j+1]=t2[temp];
    }
    ans[2 * M] = '\0';
    fflush(stdout);
    MPI_Gather(ans,2*M,MPI_CHAR, B, 2*M, MPI_CHAR,0,MPI_COMM_WORLD);
   if (rank==0){
        fprintf(stdout, "result gathered in root \n");
        B[size*M*2]='\0';
        for (i=0;i<N;i++){
            for (j=0;j<2*M;j++){
            printf( "%c\t",B[(i*2*M)+j]);
        }
        printf("\n");
        
        
    }
    fprintf(stdout, "fimal answer is is %s \n", B);
   }
    MPI_Finalize();
    return 0;
}