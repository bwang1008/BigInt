#include <sstream> // std::stringstream
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/include/big_int.hpp"

TEST_CASE("Check output representation", "[print]") {
    BigInt::BigInt x{"123"};
    std::stringstream ss;
    ss << x;
    const std::string printed_representation = ss.str();
    REQUIRE(printed_representation == "123");
}

TEST_CASE("Negation of positive", "[negate]") {
    BigInt::BigInt x("3");
    BigInt::BigInt y = -x;
    REQUIRE(y.str() == "-3");
}

TEST_CASE("Negation of negative", "[negate]") {
    BigInt::BigInt x("-3");
    BigInt::BigInt y = -x;
    REQUIRE(y.str() == "3");
}

TEST_CASE("Negation of zero", "[negate]") {
    BigInt::BigInt x("0");
    BigInt::BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negation of negative zero", "[negate]") {
    BigInt::BigInt x("-0");
    BigInt::BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negation string representation", "[negate]") {
    const std::string digits = "9999999999999999999";
    BigInt::BigInt x(digits);
    BigInt::BigInt y = -x;
    REQUIRE(y.str() == "-" + digits);
}

TEST_CASE("Negation of long negative", "[negate]") {
    const std::string digits = "-9999999999999999999";
    BigInt::BigInt x(digits);
    BigInt::BigInt y = -x;
    REQUIRE(y.str() == digits.substr(1, digits.size() - 1));
}

TEST_CASE("Copy", "[copy]") {
    BigInt::BigInt x{"3"};
    BigInt::BigInt y = x; // NOLINT(performance-unnecessary-copy-initialization)
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Copy of large number", "[copy]") {
    BigInt::BigInt x{"12345678901234567890234568790"};
    BigInt::BigInt y = x; // NOLINT(performance-unnecessary-copy-initialization)
    REQUIRE(y.str() == x.str());
}