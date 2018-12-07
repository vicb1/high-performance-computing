
#include "amath583.hpp"

// int victest(int a)
// {
//   return a*1;
// }
// int victest(double b)
// {
//   return 256*b;
// }

vector<double> readVector(istream& inputStream)
{
  int int_input;
  string string_input;

  getline(inputStream,string_input);
  if (string_input.compare("AMATH 583 VECTOR") != 0) exit(-1);

  inputStream >> int_input;
  if (int_input < 0) exit(-2);

  vector<double> double_input(int_input);
  for (int i=0; i < int_input; i++)
    inputStream >> double_input[i];

  getline(inputStream,string_input); // This grabs the '\n' left by cin'
  getline(inputStream,string_input);

  if (string_input.compare("THIS IS THE END") != 0) exit(-1);

  return double_input;
}

// vector<double> readVectorFile(string fileName) {
//   ifstream readfile("foo.txt");
//   string lineContents;
//   vector<double> vecinput;
//   // readfile.open (fileName);
//     while(getline(readfile,lineContents))//!readfile.eof()) // To get you all the lines.
//     {
//       // getline(readfile,lineContents); // Saves the line in STRING.
//       istringstream iss(lineContents);
//       vecinput = readVector(iss);
//       // cout<<lineContents; // Prints our STRING.
//     }
// 	// readfile.close();
//     // file << a << endl;
//   return vecinput;
// }
vector<double> readVector(string fileName) {
  ifstream readfile(fileName);
  int int_input;
  string string_input;

  getline(readfile,string_input);
  cout << string_input <<endl;
  if (string_input.compare("AMATH 583 VECTOR") != 0) exit(-1);

  readfile >> int_input;
  cout << int_input <<endl;
  // cout << "afterf1" <<endl;
  if (int_input < 0) exit(-2);

  vector<double> double_input(int_input);
  for (int i=0; i < int_input; i++) //++i instead?
    readfile >> double_input[i];

  getline(readfile,string_input);
  getline(readfile,string_input);

  if (string_input.compare("THIS IS THE END") != 0) exit(-1);

  return double_input;
}

vector<double> randomVector(int N) {
  vector<double> double_input(N);
  double x;
  for (int i=0; i < N; ++i){
    x = ((double) rand() / (RAND_MAX));
    double_input[i] = x;
  }

  return double_input;
}

vector<double> randomVector(){
  return {0};
}

double sqrt583(const double& y) {
  double x = 1.0, dx;
  do {
    dx = - (x*x-y) / (2.0*x);
    x += dx;
  } while (abs(dx) > 1.e-9);
  return x;
}

double twoNorm(const vector<double>& x){
  double sum = 0.0;
  for (unsigned int i = 0; i<x.size(); ++i)
    sum += (x.at(i))*(x.at(i));
  double norm = sqrt583(sum);
  return norm;
}

void writeVector(const vector<double>& x, ostream& output) {
  for (unsigned int i = 0; i<x.size(); ++i)
    output << x.at(i) << endl;
  // return double_input;
}

void writeVector(const vector<double>& x, string fileName) {
  ofstream readfile(fileName, ios::out | ios::binary);
  for (unsigned int i = 0; i<x.size(); ++i) {
    readfile << x.at(i) << endl;
  }
}

double dot583(const vector<double>& x, const vector<double>& y) {
  double sum = 0.0;
  for (unsigned int i = 0; i<x.size(); ++i)
    sum += (x.at(i))*(y.at(i));

  return sum;
}
