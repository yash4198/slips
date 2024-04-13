#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int rank, size;
    int i;
    double local_min = 1.0, global_min = 1.0; // Initialize local_min and global_min to maximum value

    double numbers[1000];

    MPI_Init(&argc, &argv); // MPI initialization

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rank of process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total number of processes

    srand(rank); // Random number generator initialization based on rank

    // Random numbers generation
    for (i = 0; i < 1000; i++) 
    {
        numbers[i] = (double)rand() / RAND_MAX; // Random numbers between 0 and 1
    }

    // Local min calculation
    for (i = 0; i < 1000; i++) 
    {
        if (numbers[i] < local_min) 
        {
            local_min = numbers[i];
        }
    }

    // Find minimum number across all processes
    MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

    // Print result from root process
    if (rank == 0) 
    {
        printf("Min number from randomly generated %d numbers: %lf\n", 1000 * size, global_min);
    }

    MPI_Finalize(); // Finalize MPI

    return 0;
}
