#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <cstddef>   // std::size_t
#include <stdexcept> // std::runtime_error
#include <utility>   // std::swap

namespace BigInt {

auto SquareMatrix::inverse() const -> SquareMatrix {
    SquareMatrix copy = *this;
    SquareMatrix inverse = identity(this->length);

    for(std::size_t row = 0; row < this->length; ++row) {
        const std::size_t pivot_row = copy.find_pivot(row);
        std::swap(copy.data[row], copy.data[pivot_row]);
        std::swap(inverse.data[row], inverse.data[pivot_row]);

        const Rational scalar = copy.data[row][row];
        for(std::size_t col = 0; col < this->length; ++col) {
            copy.data[row][col] /= scalar;
            inverse.data[row][col] /= scalar;
        }

        for(std::size_t row2 = 0; row2 < this->length; ++row2) {
            if(row2 == row) {
                continue;
            }
            const Rational scalar2 = copy.data[row2][row];
            for(std::size_t col = 0; col < this->length; ++col) {
                copy.data[row2][col] -= scalar2 * copy.data[row][col];
                inverse.data[row2][col] -= scalar2 * inverse.data[row][col];
            }
        }
    }

    return inverse;
}

auto SquareMatrix::find_pivot(const std::size_t current_row) const
    -> std::size_t {
    for(std::size_t i = current_row; i < this->length; ++i) {
        if(this->data[i][current_row] != Rational()) {
            return i;
        }
    }
    throw std::runtime_error("Matrix is not invertible");
}

} // namespace BigInt
