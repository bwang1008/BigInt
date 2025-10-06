#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <cstddef>   // std::size_t
#include <stdexcept> // std::invalid_argument
#include <vector>

namespace BigInt {

SquareMatrix::SquareMatrix(const std::size_t N)
    : length(N), data(std::vector<std::vector<Rational>>(
                     N, std::vector<Rational>(N, Rational()))) {
    if(N == 0) {
        throw std::invalid_argument("N must be positive");
    }
}

SquareMatrix::SquareMatrix(const std::vector<std::vector<Rational>> &input_data)
    : length(input_data.size()), data(input_data) {
    if(input_data.empty()) {
        throw std::invalid_argument("N must be positive");
    }
    if(input_data.size() != input_data[0].size()) {
        throw std::invalid_argument("input_data must be square");
    }
}

auto SquareMatrix::identity(const std::size_t N) -> SquareMatrix {
    std::vector<std::vector<Rational>> input_data(
        N, std::vector<Rational>(N, Rational()));
    for(std::size_t i = 0; i < N; ++i) {
        input_data[i][i] = Rational(1);
    }
    return SquareMatrix(input_data);
}

} // namespace BigInt
