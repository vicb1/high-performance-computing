#include <iostream>
#include <fstream>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <omp.h>
#include "Vector.hpp"
#include "COO.hpp"



// int omp_thread_count() {
//   int n = 0;
// #pragma omp parallel reduction(+:n) num_threads(omp_get_max_threads())
//   n += 1;
//   return n;
// }

// std::string getenv_to_string(const char *in) {
//   char *gotten = std::getenv(in);
//   if (NULL == gotten) {
//     return std::string("");
//   } else {
//     return std::string(gotten);
//   }
// }
//
// std::string getenv(const std::string& in) {
//   return getenv_to_string(in.c_str());
// }

int main(int argc, char *argv[]) {
  // if(thds)
  //   std::cout << "is null"<< std::endl;
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " vectorSize " << std::endl;
    return 0;
  }

  // typedef unsigned long size_t;
  int vectorSize = std::stoi(argv[1]);
  if(vectorSize != std::round(std::sqrt(vectorSize))*std::round(std::sqrt(vectorSize)))
    exit(-1);

  int numRuns = 100;
  if(vectorSize<10000)
    numRuns = 100000;
  else
    numRuns = 100;

  Vector x(vectorSize);
  randomize(x);
  COOMatrix A(vectorSize, vectorSize);
  piscetize(A, std::sqrt(vectorSize), std::sqrt(vectorSize));
  Vector y(vectorSize);
  zeroize(y);

  auto seqStart = std::chrono::system_clock::now();
  for (int i = 0; i < numRuns; ++i)
    matvec(A, x, y);
  auto seqEnd = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> seqElapsed = seqEnd - seqStart;
  double seqAns = twoNorm(y);
  zeroize(y);

  auto parStart = std::chrono::system_clock::now();
  for (int i = 0; i < numRuns; ++i)
    ompMatvec(A, x, y);
  auto parEnd = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> parElapsed = parEnd - parStart;
  double parAns = twoNorm(y);

  // int thds = std::stoi(getenv("OMP_NUM_THREADS"));

  std::cout <<std::thread::hardware_concurrency()<<" "<<omp_get_max_threads()<< " " << vectorSize << " " << seqElapsed.count()/numRuns << " " << parElapsed.count()/numRuns << " " << (seqElapsed.count() / parElapsed.count()) << " "<< (seqAns - parAns) << std::endl;

  return 0;
  }
