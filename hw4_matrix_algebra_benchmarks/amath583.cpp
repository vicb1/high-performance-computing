//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#include <cassert>
#include <cmath>
#include <random>
#include <algorithm>
#include <functional>
#include <vector>

#include "Vector.hpp"
#include "Matrix.hpp"

//copied
// class Matrix2 {
// public:
//   Matrix2(int M, int N) : iRows(M), jCols(N), arrayData(iRows*jCols) {}
//
//         double &operator()(int i, int j)       { return arrayData[i*jCols + j]; }
//   const double &operator()(int i, int j) const { return arrayData[i*jCols + j]; }
//
//   int numRows() const { return iRows; }
//   int numCols() const { return jCols; }
//
// private:
//   int iRows, jCols;
//   std::vector<double> arrayData;
// };
void zeroize2(Vector& v) {
  for (int i = 0; i < v.numRows(); ++i) {
    v(i) = 0.0;
  }
}

Vector operator* (const Matrix& A, const Vector& x) {
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

void matvec(const Matrix& A, const Vector& x, Vector& y) {
  assert(A.numCols() == x.numRows());
  for (int i = 0; i < A.numRows(); ++i) {
    for (int j = 0; j < A.numCols(); ++j) {
	      y(j) += A(i,j) * x(j);
    }
  }
}

// void matvec_inner(const Matrix& A, const Vector& x, Vector& y) {
//   assert(A.numCols() == x.numRows());
//   for (int i = 0; i < A.numRows(); ++i) {
//     for (int j = 0; j < A.numCols(); ++j) {
// 	      y(j) += A(i,j) * x(j);
//     }
//   }
// }

// void matvec_outer(const Matrix& A, const Vector& x, Vector& y) {
//   assert(A.numCols() == x.numRows());
//   for (int j = 0; j < A.numRows(); ++j) {
//     for (int i = 0; i < A.numCols(); ++i) {
// 	      y(j) += A(i,j) * x(j);
//     }
//   }
// }
//
// void matvec_student(const Matrix& A, const Vector& x, Vector& y) {
//   assert(A.numCols() == x.numRows());
//   for (int j = 0; j < A.numRows(); ++j) {
//     double t2 = y(j);
//     for (int i = 0; i < A.numCols(); ++i) {
// 	      t2 += A(i,j) * x(j);
//     }
//     y(j)=t2;
//   }
// }

// void zeroize(Vector& v) {
//   for (int i = 0; i < v.numRows(); ++i) {
//     v(i) = 0.0;
//   }
// }
//
//
// void randomize(Vector& v) {
//   static std::default_random_engine generator;
//   static std::uniform_real_distribution<double> distribution(2.0, 32.0);
//   static auto dice = bind(distribution, generator);
//
//   for (int i = 0; i < v.numRows(); ++i) {
//     v(i) = dice();
//   }
// }
