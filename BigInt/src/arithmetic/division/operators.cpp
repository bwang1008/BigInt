#include "BigInt/include/big_int.hpp"

namespace BigInt {

auto operator/(const BigInt &left, const BigInt &right) -> BigInt {
    return BigInt::divide_grade_school(left, right);
}

auto BigInt::operator/=(const BigInt &right) -> BigInt & {
    const BigInt division = BigInt::divide_grade_school(*this, right);
    this->negative = division.negative;
    this->digits = division.digits;
    return *this;
}

auto operator%(const BigInt &left, const BigInt &right) -> BigInt {
    return BigInt::remainder_grade_school(left, right);
}

auto BigInt::operator%=(const BigInt &right) -> BigInt & {
    const BigInt remainder = BigInt::remainder_grade_school(*this, right);
    this->negative = remainder.negative;
    this->digits = remainder.digits;
    return *this;
}

} // namespace BigInt
