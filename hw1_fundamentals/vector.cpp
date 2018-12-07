#include <iostream>
#include <string>
#include <numeric>
#include <vector>

std::vector<double> readVector(const int &numValsFunction) {
    std::vector<double> numsFunction;
    double sumNewFunction;
    for (int a = 1; a <= numValsFunction; a = a + 1) {
        std::cin >> sumNewFunction;
        numsFunction.push_back(sumNewFunction);
    }
    return numsFunction;
}
