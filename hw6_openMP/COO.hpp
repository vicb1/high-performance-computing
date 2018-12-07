//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef COO_HPP
#define COO_HPP

#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <omp.h>

#include "Vector.hpp"

class COOMatrix {
private:
  typedef std::vector<double>::size_type size_type;

public:
  COOMatrix(size_type M, size_type N) : iRows(M), jCols(N) {}

  void push_back(size_type i, size_type j, double val) {
    assert(i < iRows && i >= 0);
    assert(j < jCols && j >= 0);

    rowIndices.push_back(i);
    colIndices.push_back(j);
    arrayData.push_back(val);
  }

  void clear() {
    rowIndices.clear();
    colIndices.clear();
    arrayData.clear();
  }

  void reserve(size_type n) {
    assert(n >= 0);

    rowIndices.reserve(n);
    colIndices.reserve(n);
    arrayData.reserve(n);
  }

  size_type numRows()     const { return iRows; }
  size_type numCols()     const { return jCols; }
  size_type numNonzeros() const { return arrayData.size(); }

  void matvec(const Vector& x, Vector& y) const {
    for (size_type k = 0; k < arrayData.size(); ++k) {
      y(rowIndices[k]) += arrayData[k] * x(colIndices[k]);
    }
  }

  // void ompMatvec(const Vector& x, Vector& y) const {
  //   int sz = arrayData.size();
  //   double curVal;
  //   double newVal;
  //   #pragma omp parallel for num_threads(omp_get_max_threads()) \
  //   reduction(+: newVal) shared(sz, x, y) private(curVal) schedule(auto)
  //   for (size_type k = 0; k < sz; ++k) {
  //     curVal = arrayData[k] * x(colIndices[k]);
  //     newVal += curVal;
  //     y(rowIndices[k]) += newVal;
  //   }
  // }

  void ompMatvec(const Vector& x, Vector& y) const {
    int sz = arrayData.size();
    #pragma omp parallel for num_threads(omp_get_max_threads()) \
     default(none) shared(sz, x, y) schedule(runtime)
    for (size_type k = 0; k < sz; ++k) {
      y(rowIndices[k]) += arrayData[k] * x(colIndices[k]);
    }
  }

  void streamMatrix(std::ostream& outputFile) const {
    assert(arrayData.size() == rowIndices.size() && arrayData.size() == colIndices.size());

    outputFile << "AMATH 583 COOMATRIX" << std::endl;
    outputFile << iRows << " " << jCols << std::endl;

    // Write data
    for (size_type i = 0; i < arrayData.size(); ++i) {
      outputFile << rowIndices[i] << " ";
      outputFile << colIndices[i] << " ";
      outputFile << arrayData[i] << " ";
      outputFile << std::endl;
    }

    // Write tailer
    outputFile << "THIS IS THE END" << std::endl;
  }


private:
  size_type iRows, jCols;
  std::vector<size_type> rowIndices, colIndices;
  std::vector<double> arrayData;
};


Vector operator*(const COOMatrix& A, const Vector& x);
void matvec(const COOMatrix& A, const Vector& x, Vector& y);
void piscetize(COOMatrix& A, int xpoints, int ypoints);
void writeMatrix(const COOMatrix& A, const std::string& filename);
void streamMatrix(const COOMatrix&A);
void streamMatrix(const COOMatrix&A, std::ostream& outputFile);
void ompMatvec(const COOMatrix& A, const Vector& x, Vector& y);
// std::string getenv(const std::string& in);
// std::string getenv_to_string(const char *in);

#endif // COO_HPP
