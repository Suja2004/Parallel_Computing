#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int arr[5];

    MPI_Init(&argc, &argv);              
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (rank == 0)
    {
        printf("Enter 5 integers: ");
        for (int i = 0; i < 5; i++)
        {
            scanf("%d", &arr[i]);
        }
    }

    MPI_Bcast(arr, 5, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received array: ", rank);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    MPI_Finalize(); 
    return 0;
}
