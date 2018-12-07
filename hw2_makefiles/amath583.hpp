#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>

using std::cin;
using std::exit;
using std::getline;
using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::istream;
using std::ostream;
using std::ofstream;
using std::ios;
using std::ifstream;
using std::abs;

vector<double> readVector(istream &inputStream);

vector<double> readVector(string fileName);

vector<double> randomVector(int N);

vector<double> randomVector();

double twoNorm(const vector<double> &x);

void writeVector(const vector<double> &x, ostream &output);

void writeVector(const vector<double> &x, string fileName);

double dot583(const vector<double> &x, const vector<double> &y);
