#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int rank, size;
    int i;
    double local_even_sum = 0.0, global_even_sum = 0.0;
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

    // Local sum calculation for even numbers
    for (i = 0; i < 1000; i++) {
        if ((int)(numbers[i] * 1000) % 2 == 0) 
        {
            local_even_sum += numbers[i];
        }
    }

    // Sum all local sums of even numbers to get the global sum
    MPI_Reduce(&local_even_sum, &global_even_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print result from root process
    if (rank == 0) 
    {
        printf("Sum of all even randomly generated %d numbers: %lf\n", 1000 * size, global_even_sum);
    }

    MPI_Finalize(); // Finalize MPI

    return 0;
}
