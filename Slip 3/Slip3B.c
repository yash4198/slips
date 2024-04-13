#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int i;
    double local_sum = 0.0, global_sum = 0.0;
    double local_avg = 0.0, global_avg = 0.0;
    double numbers[1000];

    MPI_Init(&argc, &argv); // MPI initialization

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rank of process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total number of processes

    srand(rank); // Random number generator initialization based on rank

    // Random numbers generation
    for (i = 0; i < 1000; i++) {
        numbers[i] = (double)rand() / RAND_MAX; // Random numbers between 0 and 1
    }

    // Local sum calculation
    for (i = 0; i < 1000; i++) {
        local_sum += numbers[i];
    }

    // Sum of all local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Local average calculation
    local_avg = local_sum / 1000;

    // Sum of all local averages to get global average
    MPI_Reduce(&local_avg, &global_avg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Result
    printf("Rank %d: Sum of %d randomly generated numbers: %lf\n", rank, 1000, local_sum);
    printf("Rank %d: Average of %d randomly generated numbers: %lf\n", rank, 1000, local_avg);

    // Print global sum and average only for process 0
    if (rank == 0) {
        printf("Sum of all randomly generated numbers: %lf\n", global_sum);
        printf("Average of all randomly generated numbers: %lf\n", global_avg / size);
    }

    MPI_Finalize(); // Finalize MPI

    return 0;
}
