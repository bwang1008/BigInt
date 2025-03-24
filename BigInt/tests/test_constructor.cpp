#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/include/big_int.hpp"

using BigInt::operator""_b;

TEST_CASE("Constructor of Negative Number", "[constructor]") {
    std::string digits = "-3051029301904293";
    BigInt::BigInt x(digits);

    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor of Negative Zero", "[constructor]") {
    std::string digits = "-0";
    BigInt::BigInt x(digits);

    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor of Zero", "[constructor]") {
    std::string digits = "0";
    BigInt::BigInt x(digits);

    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor of Zero Via Empty String", "[constructor]") {
    BigInt::BigInt x("");
    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor of Negative Number with Leading Zero", "[constructor]") {
    std::string digits = "-03";
    BigInt::BigInt x(digits);

    REQUIRE(x.str() == "-3");
}

TEST_CASE("Constructor of Negative Number with Leading Zeroes",
          "[constructor]") {
    std::string digits = "-00000000000000000000003";
    BigInt::BigInt x(digits);

    REQUIRE(x.str() == "-3");
}

TEST_CASE("Constructor of Positive Number with Leading Zeroes",
          "[constructor]") {
    std::string digits = "0000000000000000000000000000000003";
    BigInt::BigInt x(digits);

    REQUIRE(x.str() == "3");
}

TEST_CASE("Constructor of Positive Number", "[constructor]") {
    const std::string digits = "123";
    BigInt::BigInt x(digits);

    REQUIRE(x.str() == "123");
}

TEST_CASE("Constructor of Large Positive Number", "[constructor]") {
    const std::string digits = "1000000000000000";
    BigInt::BigInt x{digits};
    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor from int", "[constructor]") {
    const int negative_value = -103;
    BigInt::BigInt x{negative_value};
    REQUIRE(x.str() == "-103");
}

TEST_CASE("Default Constructor", "[constructor]") {
    BigInt::BigInt x;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor via literal", "[literal]") {
    BigInt::BigInt x = 123_b;
    REQUIRE(x.str() == "123");
}

TEST_CASE("Constructor via literal of 0", "[literal]") {
    BigInt::BigInt x = 0_b;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor via literal of negative 0", "[literal]") {
    BigInt::BigInt x = -0_b;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor via big literal", "[literal]") {
    BigInt::BigInt x = 99999999999999999999999999999999999999999_b;
    REQUIRE(x.str() == "99999999999999999999999999999999999999999");
}
