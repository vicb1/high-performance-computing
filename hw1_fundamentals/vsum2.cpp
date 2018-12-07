#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include "vector.cpp"

int main() {
    int numVals;
    std::string line1, line2, end1, end2;
    std::vector<double> nums;
    std::getline(std::cin, line1);

    double sumTotal;
    double sumNew;
    if (line1 == "AMATH 583 VECTOR") {
        std::cin >> numVals;
        nums = readVector(numVals);
        sumTotal = std::accumulate(nums.begin(), nums.end(), 0.0);
        if (sumTotal < 0) {
            sumTotal = -2;
        }
        std::cin.ignore(1000, '\n');
        std::getline(std::cin, line2);
        if (line2 != "THIS IS THE END") {
            sumTotal = -1;
        }
    } else {
        sumTotal = -1;
    }

    std::cout << sumTotal << std::endl;
    return 0;
}
