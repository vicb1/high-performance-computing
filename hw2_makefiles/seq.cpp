#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " N [-o outputfile]" << endl;
    return 0;
  }
  int N = stoi(argv [1]);
  if(argc == 2) {
    for(int a = 0; a < N; ++a) {
      std::cout << a << std::endl;
    }
  }
  else{
    string outputFilename= "";
    for (int opt = 2; opt < argc; ++opt) { // skip argv[0] and argv[1]
      if (string(argv[opt]) == "-o") {
        ++opt; // skip to next token
        if (opt >= argc) {
          cout << "No output file specified" << endl;
          return 0;
        }
        else {
          outputFilename=argv[opt];
          ofstream file(outputFilename);
          for(int a = 0; a < N; ++a) {
            file << a << endl;
          }
        }
      }
    }

  }
  return 0;
}
