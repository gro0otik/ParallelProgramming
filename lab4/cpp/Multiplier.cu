#include "Multiplier.cuh"
#include <cuda_runtime.h>
#include <stdexcept>

__global__ void multiplyKernel(const int* A, const int* B, long long* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < N && col < N) {
        long long sum = 0;
        for (int k = 0; k < N; ++k) {
            sum += (long long)A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}

void multiplyMatricesCUDA(const std::vector<int>& matA,
    const std::vector<int>& matB,
    std::vector<long long>& matC,
    std::size_t n,
    int blockSize) {
    int* d_A;
    int* d_B;
    long long* d_C;
    cudaMalloc(&d_A, n * n * sizeof(int));
    cudaMalloc(&d_B, n * n * sizeof(int));
    cudaMalloc(&d_C, n * n * sizeof(long long));
    cudaMemcpy(d_A, matA.data(), n * n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, matB.data(), n * n * sizeof(int), cudaMemcpyHostToDevice);
    dim3 block(blockSize, blockSize);
    dim3 grid((n + blockSize - 1) / blockSize, (n + blockSize - 1) / blockSize);
    multiplyKernel << <grid, block >> > (d_A, d_B, d_C, n);
    cudaError_t err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        throw std::runtime_error("CUDA error: " + std::string(cudaGetErrorString(err)));
    }
    cudaMemcpy(matC.data(), d_C, n * n * sizeof(long long), cudaMemcpyDeviceToHost);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}