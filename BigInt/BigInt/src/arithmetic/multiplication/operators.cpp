#include "BigInt/BigInt/include/big_int.hpp"

namespace BigInt {

auto operator*(const BigInt &left, const BigInt &right) -> BigInt {
    return BigInt::multiply_karatsuba(left, right);
}

auto BigInt::operator*=(const BigInt &right) -> BigInt & {
    BigInt product = BigInt::multiply_grade_school(*this, right);
    swap(product);
    return *this;
}

} // namespace BigInt
