#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Rational/include/rational.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include <stdexcept> // std::invalid_argument

TEST_CASE("Default rational constructor", "[constructor]") {
    const BigInt::Rational r;
    REQUIRE(r.get_numerator() == BigInt::BigInt(0));
    REQUIRE(r.get_denominator() == BigInt::BigInt(1));
}

TEST_CASE("Rational constructor, one int arg", "[constructor]") {
    const BigInt::Rational r(-5);
    REQUIRE(r.get_numerator() == BigInt::BigInt(-5));
    REQUIRE(r.get_denominator() == BigInt::BigInt(1));
}

TEST_CASE("Rational constructor, two int args", "[constructor]") {
    const BigInt::Rational r(5, -3);
    REQUIRE(r.get_numerator() == BigInt::BigInt(-5));
    REQUIRE(r.get_denominator() == BigInt::BigInt(3));
}

TEST_CASE("Rational constructor, one bigint arg", "[constructor]") {
    const BigInt::Rational r(BigInt::BigInt(7));
    REQUIRE(r.get_numerator() == BigInt::BigInt(7));
    REQUIRE(r.get_denominator() == BigInt::BigInt(1));
}

TEST_CASE("Rational constructor, two bigint args", "[constructor]") {
    const BigInt::Rational r(BigInt::BigInt(7), BigInt::BigInt(83));
    REQUIRE(r.get_numerator() == BigInt::BigInt(7));
    REQUIRE(r.get_denominator() == BigInt::BigInt(83));
}

TEST_CASE("Rational constructor reduce", "[constructor]") {
    const BigInt::Rational r(15, 6);
    REQUIRE(r.get_numerator() == BigInt::BigInt(5));
    REQUIRE(r.get_denominator() == BigInt::BigInt(2));
}

TEST_CASE("Rational constructor double negative", "[constructor]") {
    const BigInt::Rational r(-15, -6);
    REQUIRE(r.get_numerator() == BigInt::BigInt(5));
    REQUIRE(r.get_denominator() == BigInt::BigInt(2));
}

TEST_CASE("Rational constructor fails on 0 denominator", "[constructor]") {
    REQUIRE_THROWS_MATCHES(BigInt::Rational(15, 0), std::invalid_argument,
                           Catch::Matchers::Message("Cannot divide by 0"));
}
