#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <cstddef> // std::size_t

namespace BigInt {

auto SquareMatrix::get(const std::size_t row, const std::size_t col) const
    -> Rational {
    return this->data[row][col];
}

} // namespace BigInt
