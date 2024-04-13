//int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
//sendbuf:address of the data to be aggregated
//recvbuf:address of the root process
//count:number of elements(in send)
//datatype: data type of the elements
//op:reduce operation (sum,max,min,prod)
//root:rank of process to recieve the result
//comm:communicator over which the reduction operation has to be performed

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int i;
    double local_sum = 0.0, global_sum = 0.0;
    double local_avg = 0.0, global_avg = 0.0;
    double numbers[1000];

    MPI_Init(&argc, &argv); //MPI initialization

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rank of process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // total number of processes

    srand(rank); // random number generator initialization based on rank

    // random numbers generation
    for (i = 0; i < 1000; i++) {
        numbers[i] = (double)rand() / RAND_MAX; // Random numbers between 0 and 1
    }

    // local sum calculation
    for (i = 0; i < 1000; i++) {
        local_sum += numbers[i];
    }

    // sum of all local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // calculate local average
    local_avg = local_sum / 1000;

    // sum of all local averages to get global average
    MPI_Reduce(&local_avg, &global_avg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // result
    if (rank == 0) {
        printf("Rank %d: Sum of %d randomly generated numbers: %lf\n", rank, 1000, global_sum);
        printf("Rank %d: Average of %d randomly generated numbers: %lf\n", rank, 1000, global_avg / size);
    } else {
        printf("Rank %d: Sum of %d randomly generated numbers: %lf\n", rank, 1000, local_sum);
        printf("Rank %d: Average of %d randomly generated numbers: %lf\n", rank, 1000, local_avg);
    }

    MPI_Finalize(); // finalize

    return 0;
}
