#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int numProcesses, myRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    const int n = 20;
    int array[n] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4};
    const int key = 3;

    int elementsPerProcess = n / numProcesses;
    int count = 0;
    MPI_Status status;

    int startIndex = myRank * elementsPerProcess;
    int endIndex = (myRank == numProcesses - 1) ? n : startIndex + elementsPerProcess;

    for (int i = startIndex; i < endIndex; ++i) {
        if (array[i] == key) {
            count++;
        }
    }

    cout << "Process " << myRank << " found: " << count << " occurrences." << endl;

    if (myRank != 0) {
        MPI_Send(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < numProcesses; ++i) {
            int countRecv = 0;
            MPI_Recv(&countRecv, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            count += countRecv;
        }
        cout << "Total count: " << count << " occurrences." << endl;
    }

    MPI_Finalize();
    return 0;
}

