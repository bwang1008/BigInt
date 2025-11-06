#include "BigInt/BigInt/include/big_int.hpp"       // BigInt
#include "BigInt/Multiplier/include/toom_cook.hpp" // ToomCookMultiplier

#include <catch2/catch_test_macros.hpp>

TEST_CASE("small test case", "[mul]") {
    BigInt::ToomCookMultiplier multiplier(3);
    const int a = 55; // 110111_2
    const int b = 46; // 101110_2

    const BigInt::BigInt a2(a);
    const BigInt::BigInt b2(b);

    const BigInt::BigInt product = multiplier.multiply(a2, b2);
    REQUIRE(product == BigInt::BigInt(a * b));
}

TEST_CASE("medium test case", "[mul]") {
    BigInt::ToomCookMultiplier multiplier(3);
    const int a = 2730; // 101010101010_2
    const int b = 2205; // 100010011101_2

    const BigInt::BigInt a2(a);
    const BigInt::BigInt b2(b);

    const BigInt::BigInt product = multiplier.multiply(a2, b2);
    REQUIRE(product == BigInt::BigInt(a * b));
}
