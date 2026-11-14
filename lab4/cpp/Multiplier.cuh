#pragma once
#include <vector>
#include <cstddef>

void multiplyMatricesCUDA(const std::vector<int>& matA,
    const std::vector<int>& matB,
    std::vector<long long>& matC,
    std::size_t n,
    int blockSize);