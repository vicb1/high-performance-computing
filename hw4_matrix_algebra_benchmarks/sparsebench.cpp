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
#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "COO.hpp"
#include "Timer.hpp"
#include <functional>

using namespace std;


double benchmark_sparse(int M, int N, int K, long numruns, function<void(const COOMatrix&, const Vector&, Vector&)>);
void runBenchmark_sparse(function<void (const COOMatrix&, const Vector&, Vector&)>f, long maxsize);

void matvec_sparse(const COOMatrix& A, const Vector& x, Vector& y) {
  A.matvec(x, y);
}

int main(int argc, char *argv[]) {
  if (argc != 2) return -1;

 if (string(argv[1]) == "sparse")
    runBenchmark_sparse(matvec_sparse, 32L*8192L);
  else return -2;

  return 0;
}


void runBenchmark_sparse(function<void (const COOMatrix&, const Vector&, Vector&)>f, long maxsize) {
  cout << "N\tN*N\tTime\tFlops\tTperX"  << endl;
  for (long i = 16; i <= maxsize; i *= 4) {
    long numruns = 4L*1048L*1048L*1048L/(i*i) + 2;
    double t = benchmark_sparse(i, i, i, numruns, f);

    //
    // Fill in the next line with the correct formula
    double flops = f.numNonzeros()*numruns;
    //

    cout << i << "\t" << i*i << "\t" << t << "\t" << flops / t << "\t" << t/((double)numruns)  << endl;
  }
}


double benchmark_sparse(int M, int N, int K, long numruns, function<void (const COOMatrix&, const Vector&, Vector&)>f) {
  int xpoints = std::sqrt((double) M);
  assert(xpoints*xpoints == M);

  COOMatrix A(M, M);
  Vector x(M), y(M);
  piscetize(A, xpoints, xpoints);
  randomize(x);
  randomize(y);

  Timer T;
  T.start();
  for (int i = 0; i < numruns; ++i) {
    f(A, x, y);
  }
  T.stop();

  zeroize(y);

  return T.elapsed();
}
