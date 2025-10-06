#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <cstddef> // std::size_t

namespace BigInt {

auto operator==(const SquareMatrix &left, const SquareMatrix &right) -> bool {
    if(left.length != right.length) {
        return false;
    }

    for(std::size_t row = 0; row < left.length; ++row) {
        for(std::size_t col = 0; col < left.length; ++col) {
            if(left.data[row][col] != right.data[row][col]) {
                return false;
            }
        }
    }

    return true;
}

auto operator!=(const SquareMatrix &left, const SquareMatrix &right) -> bool {
    return !(left == right);
}

} // namespace BigInt
