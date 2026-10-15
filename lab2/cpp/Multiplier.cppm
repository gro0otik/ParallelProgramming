export module Multiplier;

import std;

#include <omp.h>

export void multiplyMatricesParallel(const std::vector<int>& matA,
    const std::vector<int>& matB,
    std::vector<long long>& matC,
    std::size_t n) {
    matC.assign(n * n, 0);
    long long N = static_cast<long long>(n);

#pragma omp parallel for
    for (long long row = 0; row < N; ++row) {
        for (long long inner = 0; inner < N; ++inner) {
            long long a_element = matA[row * N + inner];
            for (long long col = 0; col < N; ++col) {
                matC[row * N + col] += a_element * matB[inner * N + col];
            }
        }
    }
}