#include "Grid.hpp"
#include "mpiStencil.hpp"
#include "Final.hpp"
#include <cmath>
#include <iostream>
#include <mpi.h>
#include <vector>

size_t ir(const mpiStencil &A, Grid &x, const Grid &b, size_t max_iter, double tol) {
    unsigned int myrank = MPI::COMM_WORLD.Get_rank();
    unsigned int mysize = MPI::COMM_WORLD.Get_size();
    int prev = (myrank == 0 ? MPI::PROC_NULL : myrank - 1);
    int next = (myrank == mysize - 1 ? MPI::PROC_NULL : myrank + 1);

    std::vector<double> sendBottom(x.numX());
    std::vector<double> recvTop(x.numX());
    std::vector<double> sendTop(x.numX());
    std::vector<double> recvBottom(x.numX());

    for (size_t iter = 0; iter < max_iter; ++iter) {
        for (int i = 0; i < x.numX(); ++i)
            sendBottom[i] = x(i, x.numY() - 2);
        MPI::COMM_WORLD.Sendrecv(&sendBottom[0], x.numX(), MPI::DOUBLE, next, 42, &recvTop[0], x.numX(), MPI::DOUBLE,
                                 prev, 42);
        for (int i = 0; i < x.numX(); ++i)
            x(i, 0) = recvTop[i];

        for (int i = 0; i < x.numX(); ++i)
            sendTop[i] = x(i, 1);
        MPI::COMM_WORLD.Sendrecv(&sendTop[0], x.numX(), MPI::DOUBLE, prev, 42, &recvBottom[0], x.numX(), MPI::DOUBLE,
                                 next, 42);
        for (int i = 0; i < x.numX(); ++i)
            x(i, (x.numY() - 2) + 1) = recvBottom[i];

        Grid r = b - A * x;

        double rho = mpiDot(r, r);

        if (myrank == 0)
            std::cout << "||r|| = " << std::sqrt(rho) << std::endl;

        if (std::sqrt(rho) < tol) return iter;
        x += r;
    }
    return max_iter;
}

double mpiDot(const Grid &X, const Grid &Y) {
    double rho = 0.0;
    for (size_t j = 1; j < X.numY() - 1; ++j) {
        for (size_t i = 0; i < X.numX(); ++i) {
            rho += X(i, j) * Y(i, j);
        }
    }
    double sigma = 0.0;
    MPI::COMM_WORLD.Allreduce(&rho, &sigma, 1, MPI::DOUBLE, MPI::SUM);
    return sigma;
}

double mpiDotCG(const Grid &X, const Grid &Y) {
    double rho = 0.0;
    for (size_t j = 0; j < X.numY(); ++j) {
        for (size_t i = 1; i < X.numX() - 1; ++i) {
            rho += X(i, j) * Y(i, j);
        }
    }
    double sigma = 0.0;
    MPI::COMM_WORLD.Allreduce(&rho, &sigma, 1, MPI::DOUBLE, MPI::SUM);
    return sigma;
}

size_t cg(const mpiStencil &A, Grid &x, const Grid &b, size_t max_iter, double tol) {
    unsigned int myrank = MPI::COMM_WORLD.Get_rank();
    unsigned int mysize = MPI::COMM_WORLD.Get_size();
    int prev = (myrank == 0 ? MPI::PROC_NULL : myrank - 1);
    int next = (myrank == mysize - 1 ? MPI::PROC_NULL : myrank + 1);

    Grid r = b - A * x, p(b);
    std::vector<double> sendBottom(p.numY());
    std::vector<double> recvTop(p.numY());
    std::vector<double> sendTop(p.numY());
    std::vector<double> recvBottom(p.numY());

    double rho = mpiDotCG(r, r), rho_1 = 0.0;

    for (size_t iter = 0; iter < max_iter; ++iter) {
        if (myrank == 0)
            std::cout << "||r|| = " << std::sqrt(rho) << std::endl;

        if (iter == 0) {
            p = r;
        } else {
            double beta = (rho / rho_1);
            p = r + beta * p;
        }

        for (int i = 0; i < p.numY(); ++i)
            sendBottom[i] = p(p.numX() - 2, i);
        MPI::COMM_WORLD.Sendrecv(&sendBottom[0], p.numY(), MPI::DOUBLE, next, 42, &recvTop[0], p.numY(), MPI::DOUBLE,
                                 prev, 42);
        for (int i = 0; i < p.numY(); ++i)
            p(0, i) = recvTop[i];

        for (int i = 0; i < p.numY(); ++i)
            sendTop[i] = p(1, i);
        MPI::COMM_WORLD.Sendrecv(&sendTop[0], p.numY(), MPI::DOUBLE, prev, 42, &recvBottom[0], p.numY(), MPI::DOUBLE,
                                 next, 42);
        for (int i = 0; i < p.numY(); ++i)
            p((p.numX() - 2) + 1, i) = recvBottom[i];

        Grid q = A * p;
        double alpha = rho / mpiDotCG(p, q);
        x += alpha * p;
        rho_1 = rho;
        r -= alpha * q;
        rho = mpiDotCG(r, r);

        if (rho < tol) return iter;
    }
    return max_iter;
}
