#include <iostream>
#include <fstream>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <omp.h>
#include "Vector.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " vectorSize numRepetition " << std::endl;
        return 0;
    }

    typedef unsigned long size_t;
    int vectorSize = std::stoi(argv[1]);
    Vector x(vectorSize);
    randomize(x);
    size_t numRep = std::stoi(argv[2]);

    double seqAns = 0.0;
    auto seqStart = std::chrono::system_clock::now();
    for (int i = 0; i < numRep; ++i) {
        seqAns = twoNorm(x);
    }
    auto seqEnd = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> seqElapsed = seqEnd - seqStart;

    double parAns = 0.0;
    auto parStart = std::chrono::system_clock::now();
    for (int i = 0; i < numRep; ++i) {
        parAns = ompTwoNorm(x);
    }
    auto parEnd = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> parElapsed = parEnd - parStart;

    std::cout << vectorSize << " " << seqElapsed.count() / numRep << " " << parElapsed.count() / numRep << " "
              << (seqElapsed.count() / parElapsed.count()) << " " << (seqAns - parAns) << std::endl;

    return 0;
}
