#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int send_arr[4] = {1, 2, 3, 4}; 
    int recv_val;                   
    int gathered[4];               

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4)
    {
        if (rank == 0)
        {
            printf("This program requires exactly 4 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    MPI_Scatter(send_arr, 1, MPI_INT, &recv_val, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int squared = recv_val * recv_val;
    printf("Process %d got %d -> squared = %d\n", rank, recv_val, squared);

    MPI_Gather(&squared, 1, MPI_INT, gathered, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Gathered result at Process 0: [");
        for (int i = 0; i < 4; i++)
        {
            printf("%d", gathered[i]);
            if (i != 3)
                printf(", ");
        }
        printf("]\n");
    }

    MPI_Finalize();
    return 0;
}
