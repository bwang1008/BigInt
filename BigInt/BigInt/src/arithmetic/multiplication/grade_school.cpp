#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp"

namespace BigInt {

auto BigInt::multiply_grade_school(const BigInt &left, const BigInt &right)
    -> BigInt {
    GradeSchoolMultiplier multiplier;
    return multiplier.multiply(left, right);
}

} // namespace BigInt
