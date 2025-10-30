#include "BigInt/BigInt/include/big_int.hpp"       // BigInt
#include "BigInt/Multiplier/include/toom_cook.hpp" // ToomCookMultiplier

#include <catch2/catch_test_macros.hpp>

TEST_CASE("small test case", "[mul]") {
    BigInt::ToomCookMultiplier multiplier(3);
    const int a = 55;
    const int b = 46;

    const BigInt::BigInt a2(a);
    const BigInt::BigInt b2(b);

    const BigInt::BigInt product = multiplier.multiply(a2, b2);
    REQUIRE(product == BigInt::BigInt(a * b));
}
