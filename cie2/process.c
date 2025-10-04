#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int number;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2)
    {
        if (rank == 0)
        {
            printf("This program requires at least 2 MPI processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0)
    {
        number = 5;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent integer: %d\n", number);
    }
    else if (rank == 1)
    {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received %d\n", number);
        number *= 2;
        printf("Process 1 multiplied value = %d\n", number);
    }

    MPI_Finalize();
    return 0;
}
