#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int send_data = world_rank + 1;

    int* recv_data = nullptr;

    if (world_rank == 0) {
        recv_data = new int[world_size];
    }

    MPI_Gather(&send_data, 1, MPI_INT, recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        std::cout << "Gathered data on root process (rank 0): ";
        for (int i = 0; i < world_size; ++i) {
            std::cout << recv_data[i] << " ";
        }
        std::cout << std::endl;

        delete[] recv_data;
    }

    MPI_Finalize();
    return 0;
}

