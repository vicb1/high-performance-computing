#include "Vector.hpp"

using namespace std;

double oneNorm(const Vector &v) {
    double sum = 0.0;
    for (unsigned int i = 0; i < v.numRows(); ++i)
        sum += std::abs(v(i));
    return sum;
}


double twoNorm(const Vector &v) {
    double sum = 0.0;
    for (unsigned int i = 0; i < v.numRows(); ++i)
        sum += v(i) * v(i);
    return std::sqrt(sum);
}

double infinityNorm(const Vector &v) {
    double d = 0.0;
    for (unsigned int i = 0; i < v.numRows(); ++i)
        d = std::max(d, std::abs(v(i)));
    return d;
}


Vector operator*(const double &a, const Vector &x) {
    Vector y(x.numRows());
    for (unsigned int i = 0; i < x.numRows(); ++i) {
        y(i) = a * x(i);
    }
    return y;
}

Vector operator+(const Vector &x, const Vector &y) {
    assert(x.numRows() == y.numRows());

    Vector z(x.numRows());
    for (unsigned int i = 0; i < x.numRows(); ++i) {
        z(i) = x(i) + y(i);
    }
    return z;
}


Vector operator-(const Vector &x, const Vector &y) {
    assert(x.numRows() == y.numRows());

    Vector z(x.numRows());
    for (unsigned int i = 0; i < x.numRows(); ++i) {
        z(i) = x(i) - y(i);
    }
    return z;
}


double dot(const Vector &x, const Vector &y) {
    assert(x.numRows() == y.numRows());
    double sum = 0.0;
    for (unsigned int i = 0; i < x.numRows(); ++i) {
        sum += x(i) * y(i);
    }
    return sum;
}


void zeroize(Vector &v) {
    for (unsigned int i = 0; i < v.numRows(); ++i) {
        v(i) = 0.0;
    }
}


void randomize(Vector &v) {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(2.0, 32.0);
    static auto dice = std::bind(distribution, generator);

    for (unsigned int i = 0; i < v.numRows(); ++i) {
        v(i) = dice();
    }
}

// double mpiTwoNorm(Vector& v){
//   double sum = 0.0;
//
//   for (unsigned int i = 0; i < v.numRows(); ++i)
//     sum += v(i)*v(i);
//
//   return sum;
//
// }
double mpiTwoNorm(Vector &v) {
    double sum = 0.0;
    for (unsigned int i = 0; i < v.numRows(); ++i)
        sum += v(i) * v(i);
    double sum2 = 0.0;
    MPI::COMM_WORLD.Allreduce(&sum, &sum2, 1, MPI::DOUBLE, MPI::SUM);
    double sum3 = 0.0;
    if (0 == MPI::COMM_WORLD.Get_rank()) {
        sum3 = std::sqrt(sum2);
    }
    return sum3;
}

double mpiTwoNormTimer(Vector &v) {
    double sum = 0.0;
    for (unsigned int i = 0; i < v.numRows(); ++i)
        sum += v(i) * v(i);

    return sum;
}
