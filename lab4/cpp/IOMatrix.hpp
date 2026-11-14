#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <format>

inline void dumpVectorToFile(const std::vector<int>& data, const std::string& filepath) {
    if (data.empty()) return;
    std::ofstream out(filepath);
    if (!out) throw std::runtime_error("Cannot open file for writing: " + filepath);
    for (const auto& val : data) out << val << "\n";
}

inline bool loadVectorFromFile(std::vector<int>& data, const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) return false;
    int temp;
    while (in >> temp) data.push_back(temp);
    return true;
}

inline void saveComputationResult(const std::vector<long long>& matrix, const std::string& filename, std::size_t dimension, double elapsedSeconds) {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open result file: " + filename);
    out << "# Time elapsed: " << elapsedSeconds << " sec\n";
    out << "# Dimension: " << dimension << "x" << dimension << "\n";
    for (std::size_t i = 0; i < dimension; ++i) {
        for (std::size_t j = 0; j < dimension; ++j)
            out << matrix[i * dimension + j] << " ";
        out << "\n";
    }
    std::cout << "Result saved to " << filename << std::endl;
}