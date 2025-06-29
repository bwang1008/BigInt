#include "BigInt/Rational/include/rational.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("output positive fraction", "[output]") {
    const BigInt::Rational r(5, 3);
    REQUIRE(r.str() == "5/3");
}

TEST_CASE("output negative fraction", "[output]") {
    const BigInt::Rational r(-3, 5);
    REQUIRE(r.str() == "-3/5");
}

TEST_CASE("output zero fraction", "[output]") {
    const BigInt::Rational r;
    REQUIRE(r.str() == "0/1");
}
