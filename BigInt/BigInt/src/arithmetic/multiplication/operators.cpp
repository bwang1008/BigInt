#include "BigInt/include/big_int.hpp"

namespace BigInt {

auto operator*(const BigInt &left, const BigInt &right) -> BigInt {
    return BigInt::multiply_karatsuba(left, right);
}

auto BigInt::operator*=(const BigInt &right) -> BigInt & {
    const BigInt product = BigInt::multiply_karatsuba(*this, right);
    this->negative = product.negative;
    this->digits = product.digits;
    return *this;
}

} // namespace BigInt
