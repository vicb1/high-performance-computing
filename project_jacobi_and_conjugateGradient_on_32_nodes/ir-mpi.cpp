#include <iostream>
#include <mpi.h>
#include "Grid.hpp"
#include "mpiStencil.hpp"
#include "Final.hpp"

int main(int argc, char* argv[]) {
  MPI::Init();

  size_t xsize              = 128, ysize = 128;
  size_t max_iters          = xsize;
  double tol                = 1.E-4;

  if (argc >= 2) xsize = ysize = std::stol(argv[1]);
  if (argc >= 3) max_iters     = std::stol(argv[2]);
  if (argc >= 4) tol           = std::stol(argv[3]);

  // unsigned int myrank = MPI::COMM_WORLD.Get_rank();
  unsigned int mysize = MPI::COMM_WORLD.Get_size();

  if(xsize % mysize != 0){
    std::cout << "Cannot parallelize, make sure xsize == MPIsize" << std::endl;
    exit(-1);
  }

  size_t ysizeLocal = ysize/mysize;

  Grid X0(xsize, ysizeLocal), X1(xsize, ysizeLocal);

    for (size_t i = 1; i < ysizeLocal+1; ++i) {
      X1(0, i) = X0(0, i) = 1.0;
    }

  mpiStencil A;

  ir(A, X1, X0, max_iters, tol);

  MPI::Finalize();
  return 0;
}
