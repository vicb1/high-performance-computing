#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#include "amath583.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " N" << endl;
        return 0;
    }
    int inputNumRandVec = stoi(argv[1]);
    vector<double> test1 = randomVector(inputNumRandVec);

    for (unsigned long y = 0; y < test1.size(); ++y)
        cout << test1.at(y) << endl;
    return 0;
}
