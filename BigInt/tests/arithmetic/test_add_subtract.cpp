#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/include/big_int.hpp"

using BigInt::operator""_b;

TEST_CASE("Addition of small positive", "[add]") {
    BigInt::BigInt x = 1_b;
    BigInt::BigInt y = 2_b;
    BigInt::BigInt z = x + y;

    REQUIRE(z.str() == "3");
}

TEST_CASE("Addition to doubling", "[add]") {
    std::string zero12 = "000000000000";

    BigInt::BigInt x{"1" + zero12};
    BigInt::BigInt z = x + x;

    REQUIRE(x.str() == "1" + zero12);
    REQUIRE(z.str() == "2" + zero12);
}

TEST_CASE("Addition of positive", "[add]") {
    BigInt::BigInt x{"5"};
    BigInt::BigInt y{"3"};

    BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Addition with negative", "[add]") {
    BigInt::BigInt x{"5"};
    BigInt::BigInt y{"-3"};
    BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Addition with negative flipped", "[add]") {
    BigInt::BigInt x{"3"};
    BigInt::BigInt y{"-5"};
    BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "-2");
}

TEST_CASE("Addition of opposites", "[add]") {
    BigInt::BigInt x{"3"};
    BigInt::BigInt y{"-3"};
    BigInt::BigInt z = x + y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Addition of large positives", "[add]") {
    BigInt::BigInt x{"936999595749669676277240766303535945713821785251664274"};
    BigInt::BigInt y{"751058209749445923078164062862089986280348253421170679"};
    BigInt::BigInt z = x + y;

    REQUIRE(z.str() ==
            "1688057805499115599355404829165625931994170038672834953");
}

TEST_CASE("Subtraction of positives", "[sub]") {
    BigInt::BigInt x{"100"};
    BigInt::BigInt y{"99"};

    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "1");
}

TEST_CASE("Subtraction of positives with large difference", "[sub]") {
    BigInt::BigInt x{"98765432109876543210"};
    BigInt::BigInt y{"1234567890"};

    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "98765432108641975320");
}

TEST_CASE("Subtraction of same number", "[sub]") {
    BigInt::BigInt x{"98765432109876543210"};
    BigInt::BigInt y{"98765432109876543210"};

    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Subtraction of small positives", "[sub]") {
    BigInt::BigInt x{"5"};
    BigInt::BigInt y{"3"};

    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Subtraction of negative number", "[sub]") {
    BigInt::BigInt x{"5"};
    BigInt::BigInt y{"-3"};
    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Subtraction with bigger negative number", "[sub]") {
    BigInt::BigInt x{"3"};
    BigInt::BigInt y{"-5"};
    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Subtraction of opposites", "[sub]") {
    BigInt::BigInt x{"3"};
    BigInt::BigInt y{"-3"};
    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "6");
}

TEST_CASE("Subtraction of large value", "[sub]") {
    BigInt::BigInt x{"1"};
    BigInt::BigInt y{"100000000000000000000"};
    BigInt::BigInt z = x - y;
    REQUIRE(z.str() == "-99999999999999999999");
}
