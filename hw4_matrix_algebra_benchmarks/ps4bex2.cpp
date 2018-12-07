#include <iostream>

int main() {

 std::cout<<"Routine Clock CPUID Loop-ops Scalar 2-wide 4-wide 4-wide-fma Achieved"<<std::endl;//loops<<" loops took "<<T.elapsed()<<" milliseconds"<<endl;
 std::cout<<"hoisted 2.3e9 AVX 12 1.5e9 3.0e9 6.0e9 12.1e9 4.7e9"<<std::endl;
 std::cout<<"coo 2.3e9 AVX 7 3.3e9 6.6e9 13.2e9 26.4e9 10.2e9"<<std::endl;

return 0;
}
