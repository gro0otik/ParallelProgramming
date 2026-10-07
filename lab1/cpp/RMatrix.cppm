export module RMatrix;
import std;

export std::vector<int> fillRandomValues(std::size_t totalElements, int low = 0, int high = 100) {
    if (low > high) throw std::invalid_argument("Invalid range");

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(low, high);

    std::vector<int> data(totalElements);
    for (auto& value : data) {
        value = distribution(generator);
    }
    return data;
}