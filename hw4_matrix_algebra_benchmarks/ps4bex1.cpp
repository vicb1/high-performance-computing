#include <iostream>

int main() {

    std::cout << "Routine Clock CPUID Loop-ops Scalar 2-wide 4-wide 4-wide-fma Achieved"
              << std::endl;
    std::cout << "hoisted 2.3e9 AVX 12 1.5e9 3.0e9 6.0e9 12.1e9 4.7e9" << std::endl;
    std::cout << "hoisted 2.3e9 AVX 20 0.9e9 1.8e9 3.7e9 7.4e9 4.7e9" << std::endl;
    std::cout << "copyblockhoisted 2.3e9 AVX 12 1.5e9 3.0e9 6.0e9 12.1e9 8.6e9" << std::endl;
    std::cout << "copyblockhoisted 2.3e9 AVX 20 0.9e9 1.8e9 3.7e9 7.4e9 8.6e9" << std::endl;

    return 0;
}
