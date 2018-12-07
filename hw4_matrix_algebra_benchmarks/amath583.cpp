#include <cassert>
#include <cmath>
#include <random>
#include <algorithm>
#include <functional>
#include <vector>

#include "Vector.hpp"
#include "Matrix.hpp"

void zeroize2(Vector &v) {
    for (int i = 0; i < v.numRows(); ++i) {
        v(i) = 0.0;
    }
}

Vector operator*(const Matrix &A, const Vector &x) {
    // ----------------------------------------------------------------
    // Your implementation goes here
    // It should allocate a vector, zero it out, call matvec(),
    //   and return the result
    // ----------------------------------------------------------------
    Vector y(x.numRows());
    zeroize2(y);
    matvec(A, x, y);
    return y;
}

void matvec(const Matrix &A, const Vector &x, Vector &y) {
    assert(A.numCols() == x.numRows());
    for (int i = 0; i < A.numRows(); ++i) {
        for (int j = 0; j < A.numCols(); ++j) {
            y(j) += A(i, j) * x(j);
        }
    }
}
