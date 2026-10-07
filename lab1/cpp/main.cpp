import RMatrix;
import IOMatrix;
import Multiplier;

import std;

int main() {
    constexpr std::array validSizes = { 300, 600, 900, 1200, 1500 };
    std::println("=== Matrix Multiplication Lab (Sequential) ===");
    std::println("Available sizes: 300, 600, 900, 1200, 1500");
    std::print("Enter matrix size: ");
    int n = 0;
    while (true) {
        std::cin >> n;
        if (std::ranges::contains(validSizes, n)) break;
        std::print("Invalid size. Try again: ");
    }
    auto getDataPath = [](int size, int index) {
        return std::format("../data/matrix_{}_{}.txt", size, index);
        };
    std::vector<int> matrixA, matrixB;
    std::vector<long long> matrixC;
    bool isLoaded = loadVectorFromFile(matrixA, getDataPath(n, 1))
        && loadVectorFromFile(matrixB, getDataPath(n, 2));
    if (!isLoaded) {
        std::println("\n[INFO] Data files not found. Generating new random matrices...");
        matrixA = fillRandomValues(n * n);
        matrixB = fillRandomValues(n * n);
        dumpVectorToFile(matrixA, getDataPath(n, 1));
        dumpVectorToFile(matrixB, getDataPath(n, 2));
        std::println("[INFO] Matrices saved to data/ folder.");
    }
    else {
        std::println("\n[INFO] Matrices loaded from files.");
    }
    std::println("\n[PROCESS] Multiplying {}x{} matrices...", n, n);
    auto startTime = std::chrono::steady_clock::now();
    multiplyMatricesSequential(matrixA, matrixB, matrixC, n);
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    std::println("[DONE] Computation finished in {:.4f} seconds.", elapsed.count());
    std::string resultFilename = std::format("../data/result_{}.txt", n);
    saveComputationResult(matrixC, resultFilename, n, elapsed.count());
    return 0;
}
