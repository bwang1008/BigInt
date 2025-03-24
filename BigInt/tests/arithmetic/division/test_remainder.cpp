#include <stdexcept> // std::invalid_argument
#include <utility>   // std::pair

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "BigInt/include/big_int.hpp"

TEST_CASE("Remainder operator", "[remainder]") {
    const BigInt::BigInt x(5);
    const BigInt::BigInt y(2);
    const BigInt::BigInt z = x % y;
    REQUIRE(z == BigInt::BigInt(5 % 2));
}

TEST_CASE("Remainder positive with negative", "[remainder]") {
    const BigInt::BigInt x(5);
    const BigInt::BigInt y(-2);
    const BigInt::BigInt z = x % y;
    REQUIRE(z == BigInt::BigInt(5 % -2));
}

TEST_CASE("Remainder negative with positive", "[remainder]") {
    const BigInt::BigInt x(-5);
    const BigInt::BigInt y(2);
    const BigInt::BigInt z = x % y;
    REQUIRE(z == BigInt::BigInt(-5 % 2));
}

TEST_CASE("Remainder negative with negative", "[remainder]") {
    const BigInt::BigInt x(-5);
    const BigInt::BigInt y(-2);
    const BigInt::BigInt z = x % y;
    REQUIRE(z == BigInt::BigInt(-5 % -2));
}

TEST_CASE("Remainder by zero", "[remainder]") {
    const BigInt::BigInt x(5);
    const BigInt::BigInt y(0);
    REQUIRE_THROWS_MATCHES(x % y, std::invalid_argument,
                           Catch::Matchers::Message("Cannot divide by 0"));
}
