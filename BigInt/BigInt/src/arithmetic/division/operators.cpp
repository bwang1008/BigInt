#include "BigInt/BigInt/include/big_int.hpp"

namespace BigInt {

[[nodiscard, gnu::pure]] auto operator/(const BigInt &left, const BigInt &right)
    -> BigInt {
    return BigInt::divide_grade_school(left, right);
}

auto BigInt::operator/=(const BigInt &right) -> BigInt & {
    BigInt division = BigInt::divide_grade_school(*this, right);
    swap(division);
    return *this;
}

[[nodiscard, gnu::pure]] auto operator%(const BigInt &left, const BigInt &right)
    -> BigInt {
    return BigInt::remainder_grade_school(left, right);
}

auto BigInt::operator%=(const BigInt &right) -> BigInt & {
    BigInt remainder = BigInt::remainder_grade_school(*this, right);
    swap(remainder);
    return *this;
}

} // namespace BigInt
