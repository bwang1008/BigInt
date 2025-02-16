#include <string> // std::to_string

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "BigInt/src/big_int.hpp"

TEST_CASE("Multiplication with 0", "[mul]") {
    BigInt x = 0_b;
    BigInt y = 12345678901234567890_b;

    BigInt z = x * y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Multiplication of small positives", "[mul]") {
    BigInt x = 2_b;
    BigInt y = 3_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "6");
}

TEST_CASE("Multiplication of medium-sized positives", "[mul]") {
    BigInt x = 12345678901234567890_b;
    BigInt y = 98765432109876543210_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "1219326311370217952237463801111263526900");
}

TEST_CASE("Multiplication with negative 1", "[mul]") {
    BigInt x = 123_b;
    BigInt y = -1_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "-123");
}

TEST_CASE("Multiplication with 1", "[mul]") {
    BigInt x = -123_b;
    BigInt y = 1_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "-123");
}

TEST_CASE("Multiplication of two negatives", "[mul]") {
    BigInt x = -123_b;
    BigInt y = -1_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "123");
}

TEST_CASE("Multiplication to square", "[mul]") {
    BigInt x{"98765432109876543210"};
    BigInt y{"98765432109876543210"};

    BigInt z = x * y;
    REQUIRE(z.str() == "9754610579850632525677488187778997104100");
}

TEST_CASE("Multiplication of large positives", "[mul]") {
    BigInt x{"31415926535897932384626433832795028841971693993751058209749445923"
             "078164062862089986280348253421170679"};
    BigInt y{"27182818284590452353602874713526624977572470936999595749669676277"
             "240766303535945713821785251664274"};
    BigInt z = x * y;

    REQUIRE(
        z.str() ==
        "8539734222673567065463550869546574495034888535765114961879601130179"
        "2286111574783895762507500032728659347816207067867304373545360378584"
        "8133094851462428844661315312664336578255202869537848950160622046");
}