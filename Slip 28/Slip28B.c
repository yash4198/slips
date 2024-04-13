#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int rank, size;
    int i;
    double local_sum = 0.0, global_sum = 0.0;
    double numbers[1000];

    MPI_Init(&argc, &argv); //MPI initialization

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rank of process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // total number of processes

    srand(rank); // random number generator initilization based on rank

    // random numbers generation
    for (i = 0; i < 1000; i++) 
    {
        numbers[i] = (double)rand() / RAND_MAX; // Random numbers between 0 and 1
    }

    // local sum calculation
    for (i = 0; i < 1000; i++) 
    {
        local_sum += numbers[i];
    }

    // sum of all local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // result 
    if (rank == 0) 
    {
        printf("Sum of %d randomly generated numbers: %lf\n", 1000 * size, global_sum);
    }

    MPI_Finalize(); // finalize

    return 0;
}