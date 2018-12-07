#include <iostream>
#include <string>
#include <mpi.h>
#include "Vector.hpp"
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    MPI::Init();

    size_t localVecSize = 1;
    if (argc > 1) localVecSize = std::stol(argv[1]);

    int myrank = MPI::COMM_WORLD.Get_rank();
    int mysize = MPI::COMM_WORLD.Get_size();

    if (mysize < 2) {
        std::cout << "MPI::COMM_WORLD.Get_size() not large enough! " << std::endl;
        exit(-1);
    }

    Vector localVec(localVecSize);

    int globalVecSize = localVecSize * mysize;
    Vector globalVec(globalVecSize);

    if (0 == myrank) {
        randomize(globalVec);
        MPI::COMM_WORLD.Scatter(&globalVec(0), localVecSize, MPI::DOUBLE, &localVec(0), localVecSize, MPI::DOUBLE, 0);
    } else {
        MPI::COMM_WORLD.Scatter(NULL, localVecSize, MPI::DOUBLE, &localVec(0), localVecSize, MPI::DOUBLE, 0);
    }

    double sum3 = mpiTwoNorm(localVec);

    if (0 == myrank) {
        std::cout << mysize << "\t";
        std::cout << "\t" << twoNorm(globalVec) << "\t";
        std::cout << "\t" << sum3 << "\t";
        std::cout << "\t" << std::abs(twoNorm(globalVec) - sum3);
        std::cout << std::endl;
        return 0;
    }

    MPI::Finalize();
}
