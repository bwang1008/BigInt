
#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp"

namespace BigInt {

auto GradeSchoolMultiplier::multiply_positive(const BigInt &left,
                                              const BigInt &right) -> BigInt {
    return BigInt::multiply_grade_school(left, right);
}

} // namespace BigInt
