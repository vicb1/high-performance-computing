//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef __GRID_HPP
#define __GRID_HPP

#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>


class Grid {

public:
  explicit Grid(size_t x, size_t y)              : xPoints(x+2), yPoints(y+2), arrayData(xPoints*yPoints) {}
  explicit Grid(size_t x, size_t y, double init) : xPoints(x+2), yPoints(y+2), arrayData(xPoints*yPoints, init) {}

        double &operator()(size_t i, size_t j)       { return arrayData[i*yPoints + j]; }
  const double &operator()(size_t i, size_t j) const { return arrayData[i*yPoints + j]; }

  size_t numX() const { return xPoints; }
  size_t numY() const { return yPoints; }

  void swap(Grid &x) {
    std::swap(x.xPoints, xPoints);
    std::swap(x.yPoints, yPoints);
    arrayData.swap(x.arrayData);
  }

  void operator=(const Grid& x) {
    assert(x.xPoints == xPoints && x.yPoints == yPoints);
    std::copy(x.arrayData.begin(), x.arrayData.end(), arrayData.begin());
  }

private:
  size_t xPoints, yPoints;
  std::vector<double> arrayData;
};

Grid operator-(const Grid& X, const Grid& Y);
Grid operator+(const Grid& X, const Grid& Y);
void operator+=(Grid& Z, const Grid& X);
void operator-=(Grid& Z, const Grid& X);
Grid operator*(double a, const Grid& Y);
double dot(const Grid& X, const Grid& Y);
double jacobiStep(const Grid& x, Grid& y);
void swap(Grid& x, Grid& y);
size_t jacobi(Grid& X0, Grid& X1, size_t max_iters, double tol);

#endif // __GRID_HPP

