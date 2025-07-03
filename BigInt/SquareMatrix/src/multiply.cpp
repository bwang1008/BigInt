#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

namespace BigInt {

auto SquareMatrix::multiply(const SquareMatrix &right) const -> SquareMatrix {
    SquareMatrix ans(this->length);
    for(std::size_t row = 0; row < this->length; ++row) {
        for(std::size_t col = 0; col < this->length; ++col) {
            Rational sum;
            for(std::size_t k = 0; k < this->length; ++k) {
                sum += this->data[row][k] * right.data[k][col];
            }
            ans.data[row][col] = sum;
        }
    }

    return ans;
}

auto operator*(const SquareMatrix &left, const SquareMatrix &right)
    -> SquareMatrix {
    return left.multiply(right);
}

} // namespace BigInt
