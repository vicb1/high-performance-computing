#include "Grid.hpp"
#include "mpiStencil.hpp"


//update boundaries appropriately when using this function.  this is the same as seq
Grid operator*(const mpiStencil& A, const Grid& x) {
  Grid y(x);

  for (size_t i = 1; i < x.numX() - 1; ++i) {
    for (size_t j = 1; j < x.numY() - 1; ++j) {
      y(i, j) = x(i, j) - (x(i - 1, j) + x(i + 1, j) + x(i, j - 1) + x(i, j + 1)) / 4.0;
    }
  }
  return y;
}
