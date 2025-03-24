#include "BigInt/include/big_int.hpp"

namespace BigInt {

auto operator*(const BigInt &left, const BigInt &right) -> BigInt {
    // return BigInt::multiply_grade_school(left, right);
    return BigInt::multiply_karatsuba(left, right);
}

} // namespace BigInt
