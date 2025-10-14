#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
  const int N = 10000000;

  int rank, size;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) 
    printf("Running %d processes.\n", size);

  int startidx = (N * rank / size) + 1;
  int   endidx = N * (rank+1) / size;

  unsigned int proc_sum = 0;
  for (int i = startidx; i <= endidx; ++i)
      proc_sum += i;
  
  printf("Process %d has local sum %u\n", rank, proc_sum);

  if (rank > 0) {
    MPI_Send(&proc_sum, 1, MPI_UNSIGNED, 0, 1, MPI_COMM_WORLD);
  } else {
    unsigned int remote_sum;
    for(int src = 1; src < size; ++src) {
      MPI_Recv(&remote_sum, 1, MPI_UNSIGNED, src, 1, MPI_COMM_WORLD, &status);
      proc_sum += remote_sum;
    }
  }

  if(rank == 0) printf("The sum of 1 to %d is %u.\n", N, proc_sum);

  MPI_Finalize();

  return 0;
}