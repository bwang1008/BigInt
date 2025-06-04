#include <sstream> // std::stringstream
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/BigInt/include/big_int.hpp"

TEST_CASE("Check output representation", "[print]") {
    const BigInt::BigInt x{"123"};
    std::stringstream ss;
    ss << x;
    const std::string printed_representation = ss.str();
    REQUIRE(printed_representation == "123");
}

TEST_CASE("Negation of positive", "[negate]") {
    const BigInt::BigInt x("3");
    const BigInt::BigInt y = -x;
    REQUIRE(y.str() == "-3");
}

TEST_CASE("Negation of negative", "[negate]") {
    const BigInt::BigInt x("-3");
    const BigInt::BigInt y = -x;
    REQUIRE(y.str() == "3");
}

TEST_CASE("Negation of zero", "[negate]") {
    const BigInt::BigInt x("0");
    const BigInt::BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negation of negative zero", "[negate]") {
    const BigInt::BigInt x("-0");
    const BigInt::BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negation string representation", "[negate]") {
    const std::string digits = "9999999999999999999";
    const BigInt::BigInt x(digits);
    const BigInt::BigInt y = -x;
    REQUIRE(y.str() == "-" + digits);
}

TEST_CASE("Negation of long negative", "[negate]") {
    const std::string digits = "-9999999999999999999";
    const BigInt::BigInt x(digits);
    const BigInt::BigInt y = -x;
    REQUIRE(y.str() == digits.substr(1, digits.size() - 1));
}

TEST_CASE("Copy", "[copy]") {
    const BigInt::BigInt x{"3"};
    const BigInt::BigInt y =
        x; // NOLINT(performance-unnecessary-copy-initialization)
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Copy of large number", "[copy]") {
    const BigInt::BigInt x{"12345678901234567890234568790"};
    const BigInt::BigInt y =
        x; // NOLINT(performance-unnecessary-copy-initialization)
    REQUIRE(y.str() == x.str());
}
