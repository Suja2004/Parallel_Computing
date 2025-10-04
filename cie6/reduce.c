#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int sum_reduce, sum_allreduce;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int my_value = rank;

    MPI_Reduce(&my_value, &sum_reduce, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("MPI_Reduce result at Process 0: Sum of ranks = %d\n", sum_reduce);
    }

    MPI_Allreduce(&my_value, &sum_allreduce, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("MPI_Allreduce result at Process %d: Sum of ranks = %d\n", rank, sum_allreduce);

    MPI_Finalize();
    return 0;
}
