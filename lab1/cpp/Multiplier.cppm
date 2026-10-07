export module Multiplier;
import std;

export void multiplyMatricesSequential(const std::vector<int>& matA,
    const std::vector<int>& matB,
    std::vector<long long>& matC,
    std::size_t n) {
    matC.assign(n * n, 0);
    for (std::size_t row = 0; row < n; ++row) {
        for (std::size_t inner = 0; inner < n; ++inner) {
            long long a_element = matA[row * n + inner];
            for (std::size_t col = 0; col < n; ++col) {
                matC[row * n + col] += a_element * matB[inner * n + col];
            }
        }
    }
}