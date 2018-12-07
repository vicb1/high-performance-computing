#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Vector.hpp"

class CSCMatrix {
  public:
    CSCMatrix(int M, int N) : iRows(M), jCols(N), colIndices(jCols+1, 0) {}

    void openForPushBack() { is_open = true;}

    void closeForPushBack(){
      is_open=false;
      for(int i=0; i<jCols; ++i) colIndices[i+1] += colIndices[i];
        for(int i=jCols; i>0; --i) colIndices[i] = colIndices[i-1];
          colIndices[0]=0;
    }

    void push_back(int i, int j, double val){
      ++colIndices[j];
      rowIndices.push_back(i);
      arrayData.push_back(val);
    }

    void clear() {
      arrayData.clear();
    }
    void reserve(int n) {
      arrayData.reserve(n);
    }

    int numRows() const {
      return iRows;
    }
    int numCols() const {
      return jCols;
    }
    int numNonzeros() const {
      return arrayData.size();
    }

    void matvec(const Vector& x, Vector& y) const {
      for(int j=0; j<jCols; ++j)
        for(int i=rowIndices[j]; i<colIndices[j+1]; ++i)
          y(j) += arrayData[i] * x(rowIndices[i]);
    }

    void streamMatrix(std::ostream& outputFile) const {
      outputFile << "AMATH 583 CSCMATRIX" << std::endl;
      outputFile << iRows << " " << jCols << std::endl;

      for (int i = 0; i < arrayData.size(); ++i) {
        outputFile << rowIndices[i] << " ";
        outputFile << colIndices[i] << " ";
        outputFile << arrayData[i] << " ";
        outputFile << std::endl;
      }
      outputFile << "THIS IS THE END" << std::endl;
    }

  private:
    int iRows, jCols;
    bool is_open;
    std::vector<int> rowIndices, colIndices;
    std::vector<double> arrayData;
};
