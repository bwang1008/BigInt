#include <string> // std::to_string

#include <catch2/catch_test_macros.hpp>

#include "BigInt/BigInt/include/big_int.hpp"

TEST_CASE("Test multiplication methods match", "[mul]") {
    const int a = 7;
    const int b = 11;
    const std::string expected_result = std::to_string(a * b);

    const BigInt::BigInt x{a};
    const BigInt::BigInt y{b};
    const BigInt::BigInt result = x * y;
    REQUIRE(result.str() == expected_result);

    const BigInt::BigInt result2 = BigInt::BigInt::multiply_grade_school(x, y);
    REQUIRE(result2.str() == expected_result);

    const BigInt::BigInt result3 = BigInt::BigInt::multiply_karatsuba(x, y);
    REQUIRE(result3.str() == expected_result);
}

TEST_CASE("Multiplication equals operator", "[mul]") {
    const int a = 5;
    const int b = 3;
    BigInt::BigInt x{a};
    const BigInt::BigInt y{b};
    x *= y;
    REQUIRE(x.str() == "15");
}
