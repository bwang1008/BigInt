#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <cstdint> // std::size_t
#include <vector>

namespace BigInt {

auto SquareMatrix::operator[](const std::size_t row) -> std::vector<Rational> {
    return this->data[row];
}

} // namespace BigInt
