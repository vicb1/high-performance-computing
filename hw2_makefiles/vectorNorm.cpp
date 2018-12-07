#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include "amath583.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " N" << endl;
    return 0;
  }
  int N = stoi(argv[1]);
  vector<double> x = randomVector(N);
  std::sort(x.begin (), x.end ()); // sort vector in ascending order
  double n1= twoNorm(x);
  std::sort(x.rbegin (), x.rend ()); // sort vector in descending order
  double n2= twoNorm(x);
  cout << n1 << " " << n2 << " " << n1-n2 << endl;
  return 0;
}
