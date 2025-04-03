#include "BigInt/include/big_int.hpp"

namespace BigInt {

auto BigInt::abs() const -> BigInt { return BigInt(false, digits); }

auto BigInt::gcd(const BigInt &left, const BigInt &right) -> BigInt {
    return BigInt::gcd_helper(left.abs(), right.abs());
}

auto BigInt::gcd_helper(const BigInt &left, const BigInt &right) -> BigInt {
    return right.is_zero() ? left : BigInt::gcd_helper(right, left % right);
}
} // namespace BigInt
