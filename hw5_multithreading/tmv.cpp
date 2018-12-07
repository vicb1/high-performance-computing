#include <cassert>
#include <cmath>
#include <random>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include "Vector.hpp"
#include "Matrix.hpp"


void task_matvec(const Matrix &A, const Vector &x, Vector &y, size_t partitions) {
    unsigned long rowsNum = x.numRows();
    std::vector <std::thread> threads;
    for (unsigned long k = 0; k < partitions; ++k) {
        threads.push_back(std::thread(matvec_helper, std::cref(A), std::cref(x), std::ref(y),
                                      std::cref(rowsNum) * k / std::cref(partitions),
                                      std::cref(rowsNum) * (k + 1) / std::cref(partitions)));
    }
    for (unsigned long k = 0; k < partitions; ++k) {
        threads[k].join();
    }
}

void matvec_helper(const Matrix &A, const Vector &x, Vector &y, size_t begin, size_t end) {
    std::mutex normMutex;
    //
    unsigned long rowsNum = x.numRows();
    Vector yPre(rowsNum);
    zeroize(yPre);
    for (unsigned long i = 0; i < end - begin; ++i) {
        for (unsigned long j = 0; j < rowsNum; ++j) {
            yPre(i) += A(i + begin, j) * x(j);
        }
    }
    normMutex.lock();
    for (unsigned long n = 0; n < rowsNum; ++n) {
        y(n) += yPre(n);
    }
    normMutex.unlock();
}
