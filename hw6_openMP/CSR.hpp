//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef CSR_HPP
#define CSR_HPP

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


class CSRMatrix {
  typedef std::vector<double>::size_type size_type;

public:
  CSRMatrix(size_type M, size_type N) : is_open(false), iRows(M), jCols(N), rowIndices(iRows+1, 0)  {}

  void openForPushBack()  { is_open = true; }

  void closeForPushBack() { is_open = false;
    for (size_type i = 0; i < iRows; ++i) {
      rowIndices[i+1] += rowIndices[i];
    }
    for (size_type i = iRows; i > 0; --i) {
      rowIndices[i] = rowIndices[i-1];
    }
    rowIndices[0] = 0;
  }

  void push_back(size_type i, size_type j, double value) {
    assert(is_open);
    assert(i < iRows && i >= 0);
    assert(j < jCols && j >= 0);

    ++rowIndices[i];
    colIndices.push_back(j);
    arrayData.push_back(value);
  }

  void matvec(const Vector& x, Vector& y) const {
    for (size_type i = 0; i < iRows; ++i) {
      for (size_type j = rowIndices[i]; j < rowIndices[i+1]; ++j) {
	y(i) += arrayData[j] * x(colIndices[j]);
      }
    }
  }

  void ompMatvec(const Vector& x, Vector& y) const {
    int curRows = iRows;
    #pragma omp parallel for num_threads(omp_get_max_threads()) \
     default(none) shared(curRows, x, y) schedule(runtime)
    for (size_type i = 0; i < curRows; ++i) {
      for (size_type j = rowIndices[i]; j < rowIndices[i+1]; ++j) {
        y(i) += arrayData[j] * x(colIndices[j]);
      }
    }
  }

  void clear() {
    colIndices.clear();
    arrayData.clear();
    std::fill(rowIndices.begin(), rowIndices.end(), 0);
  }

  void streamMatrix(std::ostream& outputFile) const {

    outputFile << "AMATH 583 CSRMATRIX" << std::endl;
    outputFile << iRows << " " << jCols << std::endl;

    // Write data
    for (size_type i = 0; i < iRows; ++i) {
      for (size_type j = rowIndices[i]; j < rowIndices[i+1]; ++j) {
	outputFile << arrayData[j] << " ";
      }
      outputFile << std::endl;
    }

    // Write tailer
    outputFile << "THIS IS THE END" << std::endl;
  }


  size_type numRows()     const { return iRows; }
  size_type numCols()     const { return jCols; }
  size_type numNonzeros() const { return arrayData.size(); }

private:
  bool is_open;
  size_type iRows, jCols;
  std::vector<size_type> rowIndices, colIndices;
  std::vector<double> arrayData;
};


Vector operator*(const CSRMatrix& A, const Vector& x);
void matvec(const CSRMatrix& A, const Vector& x, Vector& y);
void ompMatvec(const CSRMatrix& A, const Vector& x, Vector& y);
void piscetize(CSRMatrix& A, int xpoints, int ypoints);
void writeMatrix(const CSRMatrix& A, const std::string& filename);
void streamMatrix(const CSRMatrix&A);
void streamMatrix(const CSRMatrix&A, std::ostream& outputFile);

#endif // CSR_HPP
