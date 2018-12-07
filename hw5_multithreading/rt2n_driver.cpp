#include <iostream>
#include <fstream>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>
#include "Vector.hpp"
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " vectorSize numRecursiveLevels " << std::endl;
    return 0;
  }

  typedef unsigned long size_t;
  int vectorSize = std::stoi(argv[1]);
  Vector x(vectorSize);
  randomize(x);

  auto seqStart = std::chrono::system_clock::now();
  double seqAns = twoNorm(x);
  auto seqEnd = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> seqElapsed = seqEnd - seqStart;

  size_t numThr = std::stoi(argv[2]);
  auto parStart = std::chrono::system_clock::now();
  double parAns = recursiveTwoNorm(x, numThr);
  auto parEnd = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> parElapsed = parEnd - parStart;

  std::cout << vectorSize << " " << seqElapsed.count() << " " << parElapsed.count() << " " << (seqElapsed.count() / parElapsed.count()) << " "<< (seqAns - parAns) << std::endl;

  return 0;
  }
