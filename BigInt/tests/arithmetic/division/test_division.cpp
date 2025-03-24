#include <stdexcept> // std::invalid_argument
#include <utility>   // std::pair

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

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

TEST_CASE("Division operator", "[div]") {
    const BigInt::BigInt x(5);
    const BigInt::BigInt y(2);
    const BigInt::BigInt z = x / y;
    REQUIRE(z == BigInt::BigInt(5 / 2));
}

TEST_CASE("Division positive with negative", "[div]") {
    const BigInt::BigInt x(5);
    const BigInt::BigInt y(-2);
    const BigInt::BigInt z = x / y;
    REQUIRE(z == BigInt::BigInt(5 / -2));
}

TEST_CASE("Division negative with positive", "[div]") {
    const BigInt::BigInt x(-5);
    const BigInt::BigInt y(2);
    const BigInt::BigInt z = x / y;
    REQUIRE(z == BigInt::BigInt(-5 / 2));
}

TEST_CASE("Division negative with negative", "[div]") {
    const BigInt::BigInt x(-5);
    const BigInt::BigInt y(-2);
    const BigInt::BigInt z = x / y;
    REQUIRE(z == BigInt::BigInt(-5 / -2));
}

TEST_CASE("Division by zero", "[div]") {
    const BigInt::BigInt x(5);
    const BigInt::BigInt y(0);
    REQUIRE_THROWS_MATCHES(x / y, std::invalid_argument,
                           Catch::Matchers::Message("Cannot divide by 0"));
}
