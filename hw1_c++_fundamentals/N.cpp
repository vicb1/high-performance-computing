#include <iostream>
#include <string>

int main() {
  std::cout << "AMATH 583 VECTOR" << std::endl;
  int inputNum;
  std::cin >> inputNum;
  //int outputNumDefault;
    int outputNum;
  if ( inputNum < 0 ) {
    std::cout << "-2" << std::endl;
  }
  else {
    for(int a = 0; a < inputNum; a = a + 1) {
      outputNum = a;
      std::cout << outputNum << std::endl;
    }
  }
  std::cout << "THIS IS THE END" << std::endl;
  return 0;
}
