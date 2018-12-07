#include <cassert>
#include <cmath>
#include <random>
#include <functional>
#include <vector>
#include "Vector.hpp"

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
