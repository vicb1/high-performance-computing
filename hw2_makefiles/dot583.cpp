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
  // cout << "start" <<endl;
  vector<double> y = randomVector(N);
  double n1 = dot583(x, y);
  cout << n1 << endl;
  return 0;
}
