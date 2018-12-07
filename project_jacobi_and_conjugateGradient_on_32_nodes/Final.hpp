//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef __FINAL_HPP
#define __FINAL_HPP

#include <iostream>
#include "Grid.hpp"
#include "mpiStencil.hpp"

double mpiDot(const Grid& X, const Grid& Y);
double mpiDotCG(const Grid& X, const Grid& Y);
size_t ir(const mpiStencil& A, Grid& x, const Grid& b, size_t max_iter, double tol);
size_t cg(const mpiStencil& A, Grid& x, const Grid& b, size_t max_iter, double tol);

#endif // __FINAL_HPP
