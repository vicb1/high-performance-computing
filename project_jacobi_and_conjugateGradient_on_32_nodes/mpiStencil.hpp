#ifndef __MPI_STENCIL_HPP
#define __MPI_STENCIL_HPP

#include "Grid.hpp"

class mpiStencil {
};

Grid operator*(const mpiStencil &A, const Grid &x);

#endif // __MPI_STENCIL_HPP
