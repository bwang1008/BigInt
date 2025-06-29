#include "BigInt/Rational/include/rational.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

TEST_CASE("addition", "[arithmetic]") {
    REQUIRE(BigInt::Rational(3, 5) + BigInt::Rational() ==
            BigInt::Rational(3, 5));
    REQUIRE(BigInt::Rational(3, 5) + BigInt::Rational(1, 2) ==
            BigInt::Rational(11, 10));
    REQUIRE(BigInt::Rational(3, 5) + BigInt::Rational(3, 5) ==
            BigInt::Rational(6, 5));
    REQUIRE(BigInt::Rational(3, 5) + BigInt::Rational(-3, 5) ==
            BigInt::Rational());
    REQUIRE(BigInt::Rational(3, 5) + BigInt::Rational(-2, 3) ==
            BigInt::Rational(-1, 15));
}

TEST_CASE("subtraction", "[arithmetic]") {
    REQUIRE(BigInt::Rational(3, 5) - BigInt::Rational() ==
            BigInt::Rational(3, 5));
    REQUIRE(BigInt::Rational(3, 5) - BigInt::Rational(1, 2) ==
            BigInt::Rational(1, 10));
    REQUIRE(BigInt::Rational(3, 5) - BigInt::Rational(3, 5) ==
            BigInt::Rational());
    REQUIRE(BigInt::Rational(3, 5) - BigInt::Rational(-3, 5) ==
            BigInt::Rational(6, 5));
    REQUIRE(BigInt::Rational(3, 5) - BigInt::Rational(-2, 3) ==
            BigInt::Rational(19, 15));
}

TEST_CASE("multiplication", "[arithmetic]") {
    REQUIRE(BigInt::Rational(3, 5) * BigInt::Rational() == BigInt::Rational());
    REQUIRE(BigInt::Rational(3, 5) * BigInt::Rational(1) ==
            BigInt::Rational(3, 5));
    REQUIRE(BigInt::Rational(3, 5) * BigInt::Rational(-1) ==
            BigInt::Rational(-3, 5));
    REQUIRE(BigInt::Rational(3, 5) * BigInt::Rational(3, 5) ==
            BigInt::Rational(9, 25));
}

TEST_CASE("division", "[arithmetic]") {
    REQUIRE(BigInt::Rational(3, 5) / BigInt::Rational(1) ==
            BigInt::Rational(3, 5));
    REQUIRE(BigInt::Rational(3, 5) / BigInt::Rational(3, 5) ==
            BigInt::Rational(1));
    REQUIRE(BigInt::Rational(3, 5) / BigInt::Rational(-2, 3) ==
            BigInt::Rational(-9, 10));

    REQUIRE_THROWS_MATCHES(BigInt::Rational(3, 5) / BigInt::Rational(),
                           std::invalid_argument,
                           Catch::Matchers::Message("Cannot divide by 0"));
}
