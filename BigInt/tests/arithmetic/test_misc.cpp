#include <catch2/catch_test_macros.hpp>

#include "BigInt/include/big_int.hpp"

TEST_CASE("Abs of positive", "[abs]") {
    const BigInt::BigInt x("1");
    const BigInt::BigInt y = x.abs();
    REQUIRE(y.str() == "1");
}

TEST_CASE("Abs of zero", "[abs]") {
    const BigInt::BigInt x(0);
    const BigInt::BigInt y = x.abs();
    REQUIRE(y.str() == "0");
}

TEST_CASE("Abs of negative", "[abs]") {
    const BigInt::BigInt x("-1");
    const BigInt::BigInt y = x.abs();
    REQUIRE(y.str() == "1");
}

TEST_CASE("GCD with gcd > 1", "[gcd]") {
    const BigInt::BigInt x("9");
    const BigInt::BigInt y("15");
    const BigInt::BigInt z = BigInt::BigInt::gcd(x, y);
    REQUIRE(z.str() == "3");
}

TEST_CASE("GCD with coprime", "[gcd]") {
    const BigInt::BigInt x("8");
    const BigInt::BigInt y("15");
    const BigInt::BigInt z = BigInt::BigInt::gcd(x, y);
    REQUIRE(z.str() == "1");
}

TEST_CASE("GCD with 0", "[gcd]") {
    const BigInt::BigInt x("15");
    const BigInt::BigInt y(0);
    const BigInt::BigInt z = BigInt::BigInt::gcd(x, y);
    REQUIRE(z.str() == "15");
}

TEST_CASE("GCD with negative", "[gcd]") {
    const BigInt::BigInt x("15");
    const BigInt::BigInt y("-6");
    const BigInt::BigInt z = BigInt::BigInt::gcd(x, y);
    REQUIRE(z.str() == "3");
}

TEST_CASE("GCD with both negative", "[gcd]") {
    const BigInt::BigInt x("-15");
    const BigInt::BigInt y("-6");
    const BigInt::BigInt z = BigInt::BigInt::gcd(x, y);
    REQUIRE(z.str() == "3");
}
