#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int rank, size;
    int i;
    double local_max = 0.0, global_max = 0.0;
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

    // Local max calculation
    for (i = 0; i < 1000; i++) 
    {
        if (numbers[i] > local_max) 
        {
            local_max = numbers[i];
        }
    }

    // Find maximum number across all processes
    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // Print result from root process
    if (rank == 0) 
    {
        printf("Max number from randomly generated %d numbers: %lf\n", 1000 * size, global_max);
    }

    MPI_Finalize(); // Finalize MPI

    return 0;
}
