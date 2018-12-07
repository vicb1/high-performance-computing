#include <cassert>
#include <cmath>
#include <random>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <mpi.h>
#include <math.h>
#include <unistd.h>
// #include <omp.h>

#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <vector>

class Vector {
    typedef std::vector<double>::size_type size_type;

public:
    explicit Vector(size_type M) : iRows(M), arrayData(iRows) {}

    explicit Vector(size_type M, double init) : iRows(M), arrayData(iRows, init) {}

    double &operator()(size_type i) { return arrayData[i]; }

    const double &operator()(size_type i) const { return arrayData[i]; }

    size_type numRows() const { return arrayData.size(); }

private:
    size_type iRows;
    std::vector<double> arrayData;
};

double oneNorm(const Vector &v);

double twoNorm(const Vector &v);

double infinityNorm(const Vector &v);

Vector operator*(const double &a, const Vector &x);

Vector operator+(const Vector &x, const Vector &y);

Vector operator-(const Vector &x, const Vector &y);

double dot(const Vector &x, const Vector &y);

void zeroize(Vector &v);

void randomize(Vector &v);

double mpiTwoNorm(Vector &v);

double mpiTwoNormTimer(Vector &v);

#endif // VECTOR_HPP
