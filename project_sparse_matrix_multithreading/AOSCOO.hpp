#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Vector.hpp"

class AOSMatrix {
public:
  AOSMatrix(int M, int N) : iRows(M), jCols(N) {}


  void push_back(int i, int j, double val){
    Element eNew;
    eNew.row = i;
    eNew.col = j;
    eNew.val = val;
    arrayData.push_back(eNew);
  }
  void clear(){
    arrayData.clear();
  }
  void reserve(int n){
    arrayData.reserve(n);
  }

  int numRows(){
    return iRows;
  }
  int numCols(){
    return jCols;
  }
  int numNonzeros(){
    return arrayData.size();
  }

  void matvec(const Vector& x, Vector& y) const {
    for (int k=0; k<arrayData.size(); ++k) {
      y(arrayData[k].row)+=arrayData[k].val * x(arrayData[k].col);
    }
  }

  void streamMatrix(std::ostream& outputFile) const {
    outputFile << "AMATH 583 AOSCOOMATRIX" << std::endl;
    outputFile << iRows << " " << jCols << std::endl;

    for (int i = 0; i < arrayData.size(); ++i) {
      outputFile << arrayData[i].row << " ";
      outputFile << arrayData[i].col << " ";
      outputFile << arrayData[i].val << " ";
      outputFile << std::endl;
    }
    outputFile << "THIS IS THE END" << std::endl;
  }

private:
  class Element {
    public:
    int row, col;
    double val;
  };

  int iRows, jCols;
  std::vector<Element> arrayData;
};
