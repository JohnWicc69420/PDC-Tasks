#include <iostream>
#include <mpi.h>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int send_data_size = 20; 
    int* send_data = nullptr;
    int* recv_data = nullptr;
    int* send_counts = nullptr;
    int* displacements = nullptr;

    if (world_rank == 0) {
        send_data = new int[send_data_size];

        for (int i = 0; i < send_data_size; ++i) {
            send_data[i] = i;
        }

        send_counts = new int[world_size];
        for (int i = 0; i < world_size; ++i) {
            send_counts[i] = send_data_size / world_size;
        }
        send_counts[world_size - 1] += send_data_size % world_size; 
        displacements = new int[world_size];
        int displacement = 0;
        for (int i = 0; i < world_size; ++i) {
            displacements[i] = displacement;
            displacement += send_counts[i];
        }
    }

    int recv_count = send_data_size / world_size + (world_rank < send_data_size % world_size ? 1 : 0);
    recv_data = new int[recv_count];

    MPI_Scatterv(send_data, send_counts, displacements, MPI_INT, recv_data, recv_count, MPI_INT, 0, MPI_COMM_WORLD);

    std::cout << "Process " << world_rank << " received: ";
    for (int i = 0; i < recv_count; ++i) {
        std::cout << recv_data[i] << " ";
    }
    std::cout << std::endl;

    if (world_rank == 0) {
        delete[] send_data;
        delete[] send_counts;
        delete[] displacements;
    }
    delete[] recv_data;

    MPI_Finalize();
    return 0;
}
