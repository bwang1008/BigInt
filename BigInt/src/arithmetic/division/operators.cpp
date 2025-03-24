#include "BigInt/include/big_int.hpp"

namespace BigInt {

auto operator/(const BigInt &left, const BigInt &right) -> BigInt {
    return BigInt::divide_grade_school(left, right);
}

auto operator%(const BigInt &left, const BigInt &right) -> BigInt {
    return BigInt::remainder_grade_school(left, right);
}

} // namespace BigInt
