#include <iostream>
#include <string>
#include <numeric>
#include <vector>

int main() {
    std::string line1, line2, end1, end2;
    std::vector<double> nums;
    std::getline(std::cin, line1);

    int numVals;
    double sumTotal;
    double sumNew;
    if (line1 == "AMATH 583 VECTOR") {
        std::cin >> numVals;
        for (int a = 1; a <= numVals; a = a + 1) {
            std::cin >> sumNew;
            nums.push_back(sumNew);
            sumTotal = std::accumulate(nums.begin(), nums.end(), 0.0);
        }
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
