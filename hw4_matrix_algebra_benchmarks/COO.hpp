#ifndef COO_HPP
#define COO_HPP

#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>
#include "Matrix.hpp"
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

    size_type numRows() const { return iRows; }

    size_type numCols() const { return jCols; }

    size_type numNonzeros() const { return arrayData.size(); }

    void matvec(const Vector &x, Vector &y) const {
        for (size_type k = 0; k < arrayData.size(); ++k) {
            y(rowIndices[k]) += arrayData[k] * x(colIndices[k]);
        }
    }

    void trMatvec(const Vector &x, Vector &y) const {
        for (size_type k = 0; k < arrayData.size(); ++k) {
            y(colIndices[k]) += arrayData[k] * x(rowIndices[k]);
        }
    }

    void streamMatrix(std::ostream &outputFile) const {
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
    std::vector <size_type> rowIndices, colIndices;
    std::vector<double> arrayData;
};


Vector operator*(const COOMatrix &A, const Vector &x);

void matvec(const COOMatrix &A, const Vector &x, Vector &y);

void matvec(const Vector &x, Vector &y);

void trMatvec(const Vector &x, Vector &y);

void piscetize(COOMatrix &A, int xpoints, int ypoints);

void writeMatrix(const COOMatrix &A, const std::string &filename);

void streamMatrix(const COOMatrix &A);

void streamMatrix(const COOMatrix &A, std::ostream &outputFile);

#endif // COO_HPP
