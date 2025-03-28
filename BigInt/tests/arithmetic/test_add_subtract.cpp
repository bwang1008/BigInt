#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/include/big_int.hpp"

using BigInt::operator""_b;

TEST_CASE("Addition of small positive", "[add]") {
    const BigInt::BigInt x = 1_b;
    const BigInt::BigInt y = 2_b;
    const BigInt::BigInt z = x + y;

    REQUIRE(z.str() == "3");
}

TEST_CASE("Addition to doubling", "[add]") {
    const std::string zero12 = "000000000000";

    const BigInt::BigInt x{"1" + zero12};
    const BigInt::BigInt z = x + x;

    REQUIRE(x.str() == "1" + zero12);
    REQUIRE(z.str() == "2" + zero12);
}

TEST_CASE("Addition of positive", "[add]") {
    const BigInt::BigInt x{"5"};
    const BigInt::BigInt y{"3"};

    const BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Addition with negative", "[add]") {
    const BigInt::BigInt x{"5"};
    const BigInt::BigInt y{"-3"};
    const BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Addition with zero", "[add]") {
    const BigInt::BigInt x{5};
    const BigInt::BigInt y{0};
    const BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "5");
}

TEST_CASE("Addition of negative with positive", "[add]") {
    const BigInt::BigInt x{"-3"};
    const BigInt::BigInt y{"5"};
    const BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Addition of negative with negative", "[add]") {
    const BigInt::BigInt x{"-3"};
    const BigInt::BigInt y{"-5"};
    const BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "-8");
}

TEST_CASE("Addition with negative flipped", "[add]") {
    const BigInt::BigInt x{"3"};
    const BigInt::BigInt y{"-5"};
    const BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "-2");
}

TEST_CASE("Addition of opposites", "[add]") {
    const BigInt::BigInt x{"3"};
    const BigInt::BigInt y{"-3"};
    const BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Addition of large positives", "[add]") {
    const BigInt::BigInt x{
        "936999595749669676277240766303535945713821785251664274"};
    const BigInt::BigInt y{
        "751058209749445923078164062862089986280348253421170679"};
    const BigInt::BigInt z = x + y;

    REQUIRE(z.str() ==
            "1688057805499115599355404829165625931994170038672834953");
}

TEST_CASE("Subtraction of positives", "[sub]") {
    const BigInt::BigInt x{"100"};
    const BigInt::BigInt y{"99"};

    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "1");
}

TEST_CASE("Subtraction of positives with large difference", "[sub]") {
    const BigInt::BigInt x{"98765432109876543210"};
    const BigInt::BigInt y{"1234567890"};

    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "98765432108641975320");
}

TEST_CASE("Subtraction of same number", "[sub]") {
    const BigInt::BigInt x{"98765432109876543210"};
    const BigInt::BigInt y{"98765432109876543210"};

    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Subtraction of small positives", "[sub]") {
    const BigInt::BigInt x{"5"};
    const BigInt::BigInt y{"3"};

    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Subtraction of negative number", "[sub]") {
    const BigInt::BigInt x{"5"};
    const BigInt::BigInt y{"-3"};
    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Subtraction with bigger negative number", "[sub]") {
    const BigInt::BigInt x{"3"};
    const BigInt::BigInt y{"-5"};
    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Subtraction of opposites", "[sub]") {
    const BigInt::BigInt x{"3"};
    const BigInt::BigInt y{"-3"};
    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "6");
}

TEST_CASE("Subtraction of large value", "[sub]") {
    const BigInt::BigInt x{"1"};
    const BigInt::BigInt y{"100000000000000000000"};
    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "-99999999999999999999");
}

TEST_CASE("Subtraction: negative with positive", "[sub]") {
    const BigInt::BigInt x{-3};
    const BigInt::BigInt y{5};
    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "-8");
}

TEST_CASE("Subtraction: negative with negative", "[sub]") {
    const BigInt::BigInt x{-3};
    const BigInt::BigInt y{-5};
    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Subtraction from zero", "[sub]") {
    const BigInt::BigInt x{0};
    const BigInt::BigInt y{5};
    const BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "-5");
}

TEST_CASE("Plus equals", "[add]") {
    BigInt::BigInt x{"-5"};
    const BigInt::BigInt y(7);
    x += y;
    REQUIRE(x.str() == "2");
}

TEST_CASE("Subtract equals", "[add]") {
    BigInt::BigInt x{"5"};
    const BigInt::BigInt y(7);
    x -= y;
    REQUIRE(x.str() == "-2");
}
