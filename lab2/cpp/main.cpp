import RMatrix;
import IOMatrix;
import Multiplier;

import std;

#include <cstdlib>
#include <omp.h>

int main(int argc, char* argv[]) {
    constexpr std::array validSizes = { 200, 400, 800, 1200, 1600, 2000 };
    constexpr std::array validThreads = { 1, 2, 4, 8 };

    int n = 0;
    if (argc > 1) {
        n = std::atoi(argv[1]);
    }
    else {
        std::println("Available sizes: 200, 400, 800, 1200, 1600, 2000");
        std::print("Enter size: ");
        while (true) {
            std::cin >> n;
            if (std::ranges::contains(validSizes, n)) break;
            std::print("Invalid. Try again: ");
        }
    }

    int numThreads = 0;
    if (argc > 2) {
        numThreads = std::atoi(argv[2]);
    }
    else {
        std::println("Available threads: 1, 2, 4, 8");
        std::print("Enter threads: ");
        while (true) {
            std::cin >> numThreads;
            if (std::ranges::contains(validThreads, numThreads)) break;
            std::print("Invalid. Try again: ");
        }
    }

    omp_set_num_threads(numThreads);

    std::println("=== Matrix Multiplication (Parallel, OpenMP) ===");
    std::println("Size: {}x{}, Threads: {}", n, n, numThreads);

    auto getDataPath = [](int size, int idx) {
        return std::format("../data/matrix_{}_{}.txt", size, idx);
        };

    std::vector<int> A, B;
    std::vector<long long> C;

    bool isLoaded = loadVectorFromFile(A, getDataPath(n, 1))
        && loadVectorFromFile(B, getDataPath(n, 2));

    if (!isLoaded) {
        std::println("[INFO] Generating new matrices...");
        A = fillRandomValues(n * n);
        B = fillRandomValues(n * n);
        dumpVectorToFile(A, getDataPath(n, 1));
        dumpVectorToFile(B, getDataPath(n, 2));
    }
    else {
        std::println("[INFO] Loaded from files.");
    }

    auto start = std::chrono::steady_clock::now();
    multiplyMatricesParallel(A, B, C, n);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::println("[DONE] Time: {:.4f} seconds (threads={})", elapsed.count(), numThreads);

    std::string resultName = std::format("../data/result_{}_t{}.txt", n, numThreads);
    saveComputationResult(C, resultName, n, elapsed.count());

    return 0;
}
