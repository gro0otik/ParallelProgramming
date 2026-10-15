export module IOMatrix;
import std;

export void dumpVectorToFile(const std::vector<int>& data, const std::string& filepath) {
    if (data.empty()) return;

    std::ofstream out(filepath);
    if (!out) throw std::runtime_error("Cannot open file for writing: " + filepath);

    for (const auto& val : data) {
        std::println(out, "{}", val);
    }
}

export bool loadVectorFromFile(std::vector<int>& data, const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) return false;

    int temp;
    while (in >> temp) {
        data.push_back(temp);
    }
    return true;
}

export void saveComputationResult(const std::vector<long long>& matrix,
    const std::string& filename,
    std::size_t dimension,
    double elapsedSeconds) {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open result file: " + filename);
    std::println(out, "# --- Computation Report ---");
    std::println(out, "# Time elapsed: {:.6f} sec", elapsedSeconds);
    std::println(out, "# Matrix dimension: {}x{}", dimension, dimension);
    std::println(out, "# Total elements: {}", dimension * dimension);
    std::println(out, "# --------------------------");
    for (std::size_t i = 0; i < dimension; ++i) {
        for (std::size_t j = 0; j < dimension; ++j) {
            std::print(out, "{:10}", matrix[i * dimension + j]);
        }
        std::println(out, ""); 
    }
    std::println("Result successfully saved to {}", filename);
}