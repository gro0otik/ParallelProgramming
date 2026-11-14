#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <array>
#include <algorithm>
#include <cstdlib>
#include "RMatrix.hpp"
#include "IOMatrix.hpp"
#include "Multiplier.cuh"

int main(int argc, char* argv[]) {
    constexpr std::array validSizes = { 200, 400, 800, 1200, 1600, 2000 };
    int n = 0;
    if (argc > 1) n = std::atoi(argv[1]);
    else {
        std::cout << "Available sizes: 200, 400, 800, 1200, 1600, 2000\nEnter size: ";
        while (true) {
            std::cin >> n;
            if (std::find(validSizes.begin(), validSizes.end(), n) != validSizes.end()) break;
            std::cout << "Invalid size. Try again: ";
        }
    }
    int blockSize = 16;
    if (argc > 2) blockSize = std::atoi(argv[2]);
    std::cout << "=== CUDA Matrix Mult ===\n";
    std::cout << "Size: " << n << "x" << n << ", Block size: " << blockSize << "x" << blockSize << "\n";
    auto getDataPath = [](int size, int idx) {
        return "../data/matrix_" + std::to_string(size) + "_" + std::to_string(idx) + ".txt";
        };
    std::vector<int> A, B;
    std::vector<long long> C(n * n);
    bool isLoaded = loadVectorFromFile(A, getDataPath(n, 1))
        && loadVectorFromFile(B, getDataPath(n, 2));
    if (!isLoaded) {
        std::cout << "[INFO] Generating new matrices...\n";
        A = fillRandomValues(n * n);
        B = fillRandomValues(n * n);
        dumpVectorToFile(A, getDataPath(n, 1));
        dumpVectorToFile(B, getDataPath(n, 2));
    }
    else {
        std::cout << "[INFO] Loaded from files.\n";
    }
    auto start = std::chrono::steady_clock::now();
    multiplyMatricesCUDA(A, B, C, n, blockSize);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "[DONE] Time: " << elapsed.count() << " seconds\n";
    std::string resultName = "../data/result_" + std::to_string(n) + "_b" + std::to_string(blockSize) + ".txt";
    saveComputationResult(C, resultName, n, elapsed.count());
    return 0;
}
