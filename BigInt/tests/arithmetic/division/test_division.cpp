#include <utility> // std::pair

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "BigInt/include/big_int.hpp"

TEST_CASE("Division of lots of positives", "[div]") {
    auto i = GENERATE(range(0, 11));
    auto j = GENERATE(range(1, 11));

    const BigInt::BigInt x(i);
    const BigInt::BigInt y(j);
    const std::pair<BigInt::BigInt, BigInt::BigInt> z =
        BigInt::BigInt::quotient_and_remainder_grade_school(x, y);
    const BigInt::BigInt quotient = z.first;
    const BigInt::BigInt remainder = z.second;

    REQUIRE(quotient == BigInt::BigInt(i / j));
    REQUIRE(remainder == BigInt::BigInt(i % j));
}