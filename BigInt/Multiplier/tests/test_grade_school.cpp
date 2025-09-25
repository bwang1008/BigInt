#include <catch2/catch_test_macros.hpp>

#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp"

TEST_CASE("Grade school multiplication", "[mul]") {
    const BigInt::BigInt x{3};
    const BigInt::BigInt y{5};
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "15");
}
