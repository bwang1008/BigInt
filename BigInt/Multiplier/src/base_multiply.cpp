#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp"

namespace BigInt {

auto Multiplier::multiply(const BigInt &left, const BigInt &right) -> BigInt {
    if(left.is_zero() || right.is_zero()) {
        return BigInt();
    }
    BigInt nonnegative_product = multiply_positive(left, right);
    nonnegative_product.negative = left.negative ^ right.negative;
    return nonnegative_product;
}

} // namespace BigInt
