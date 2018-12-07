#include <iostream>
#include <string>
#include <mpi.h>
#include "Vector.hpp"
#include <math.h>
#include <unistd.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>

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

    unsigned int numRuns = 10000;
    if (localVecSize > 1000)
        numRuns = 1000;
    double parAnswer = 0.0;

    MPI::COMM_WORLD.Barrier();
    auto parStart = std::chrono::system_clock::now();

    for (unsigned int i = 0; i < numRuns; ++i) {
        parAnswer = 0.0;
        for (unsigned int i = 0; i < localVecSize; ++i)
            parAnswer += localVec(i) * localVec(i);
    }
    MPI::COMM_WORLD.Barrier();
    auto parEnd = std::chrono::system_clock::now();

    double parAnswer2;
    MPI::COMM_WORLD.Allreduce(&parAnswer, &parAnswer2, 1, MPI::DOUBLE, MPI::SUM);

    if (0 == myrank) {
        double parAnswer3 = 0.0;
        auto parStart2 = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < numRuns; ++i)
            parAnswer3 = std::sqrt(parAnswer2);
        auto parEnd2 = std::chrono::system_clock::now();

        std::cout << mysize << "\t";
        std::cout << "\t" << globalVecSize << "\t";

        double seqAnswer = 0.0;

        auto seqStart = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < numRuns; ++i)
            seqAnswer = twoNorm(globalVec);
        auto seqEnd = std::chrono::system_clock::now();

        std::chrono::duration<double, std::milli> seqElapsed = seqEnd - seqStart;
        std::cout << "\t" << seqElapsed.count() / numRuns << "\t";

        std::chrono::duration<double, std::milli> parElapsed = parEnd - parStart;
        std::chrono::duration<double, std::milli> parElapsed2 = parEnd2 - parStart2;
        std::cout << "\t" << (parElapsed.count() + parElapsed2.count()) / numRuns << "\t";
        std::cout << "\t" << seqElapsed.count() / (parElapsed.count() + parElapsed2.count()) << "\t";

        std::cout << "\t" << std::abs(twoNorm(globalVec) - parAnswer3);

        std::cout << std::endl;
        return 0;
    }

    MPI::Finalize();
}
