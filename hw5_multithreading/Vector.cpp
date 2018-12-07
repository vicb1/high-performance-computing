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

using namespace std;

double oneNorm(const Vector &v) {
    double d = 0.0;
    for (int i = 0; i < v.numRows(); ++i)
        d += std::abs(v(i));
    return d;
}


double twoNorm(const Vector &v) {
    double d = 0.0;
    for (int i = 0; i < v.numRows(); ++i)
        d += v(i) * v(i);
    return std::sqrt(d);
}


double infinityNorm(const Vector &v) {
    double d = 0.0;
    for (int i = 0; i < v.numRows(); ++i)
        d = std::max(d, std::abs(v(i)));
    return d;
}


Vector operator+(const Vector &x, const Vector &y) {
    assert(x.numRows() == y.numRows());

    Vector z(x.numRows());
    for (int i = 0; i < x.numRows(); ++i) {
        z(i) = x(i) + y(i);
    }
    return z;
}


Vector operator-(const Vector &x, const Vector &y) {
    assert(x.numRows() == y.numRows());

    Vector z(x.numRows());
    for (int i = 0; i < x.numRows(); ++i) {
        z(i) = x(i) - y(i);
    }
    return z;
}


void zeroize(Vector &v) {
    for (int i = 0; i < v.numRows(); ++i) {
        v(i) = 0.0;
    }
}


void randomize(Vector &v) {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(2.0, 32.0);
    static auto dice = bind(distribution, generator);

    for (int i = 0; i < v.numRows(); ++i) {
        v(i) = dice();
    }
}

void matvec(const Matrix &A, const Vector &x, Vector &y) {
    assert(A.numCols() == x.numRows());
    for (int i = 0; i < A.numRows(); ++i) {
        for (int j = 0; j < A.numCols(); ++j) {
            y(j) += A(i, j) * x(j);
        }
    }
}

void matvec_inner(const Matrix &A, const Vector &x, Vector &y) {
    assert(A.numCols() == x.numRows());
    for (int i = 0; i < A.numRows(); ++i) {
        for (int j = 0; j < A.numCols(); ++j) {
            y(j) += A(i, j) * x(j);
        }
    }
}

void matvec_outer(const Matrix &A, const Vector &x, Vector &y) {
    assert(A.numCols() == x.numRows());
    for (int j = 0; j < A.numRows(); ++j) {
        for (int i = 0; i < A.numCols(); ++i) {
            y(j) += A(i, j) * x(j);
        }
    }
}

void matvec_student(const Matrix &A, const Vector &x, Vector &y) {
    assert(A.numCols() == x.numRows());
    for (int j = 0; j < A.numRows(); ++j) {
        double t2 = y(j);
        for (int i = 0; i < A.numCols(); ++i) {
            t2 += A(i, j) * x(j);
        }
        y(j) = t2;
    }
}

double partitionedTwoNorm(const Vector &x, size_t partitions) {
    double partial = 0.0;
    unsigned long rowsNum = x.numRows();
    std::vector <std::thread> threads;
    for (unsigned long k = 0; k < partitions; ++k) {
        threads.push_back(std::thread(ptn_worker, std::cref(x), std::cref(rowsNum) * k / std::cref(partitions),
                                      std::cref(rowsNum) * (k + 1) / std::cref(partitions), std::ref(partial)));
    }
    for (unsigned long k = 0; k < partitions; ++k) {
        threads[k].join();
    }
    return std::sqrt(partial);
}


void ptn_worker(const Vector &x, size_t begin, size_t end, double &partial) {
    std::mutex normMutex;
    double partialPre = 0.0;
    for (unsigned long i = begin; i < end; ++i) {
        partialPre += x(i) * x(i);
    }
    normMutex.lock();
    partial += partialPre;
    normMutex.unlock();
}

double recursiveTwoNorm(const Vector &x, size_t levels) {
    int rowsNum = x.numRows();
    std::mutex normMutex;
    normMutex.lock();
    std::future<double> parAns2 = std::async(std::launch::deferred, rtn_worker, std::cref(x), 0, std::cref(rowsNum),
                                             levels);
    normMutex.unlock();
    return std::sqrt(parAns2.get());
}

double rtn_worker(const Vector &x, size_t begin, size_t end, size_t level) {
    double partial = 0.0;
    if (level == 0) {
        for (int i = begin; i < end; ++i) {
            partial += x(i) * x(i);
        }
        return partial;
    } else {
        return rtn_worker(x, begin, begin + (end - begin) / 2, level - 1)
               + rtn_worker(x, begin + (end - begin) / 2, end, level - 1);
    }
}

double inner_dot(const Matrix &A, const Vector &x, unsigned long i, double init) {
    for (unsigned long j = 0; j < A.numCols(); ++j) {
        init += A(i, j) * x(j);
    }
    return init;
}
