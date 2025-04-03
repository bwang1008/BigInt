#include <string> // std::to_string

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "BigInt/include/big_int.hpp"

using BigInt::operator""_b;

TEST_CASE("Multiplication with 0", "[mul]") {
    const BigInt::BigInt x = 0_b;
    const BigInt::BigInt y = 12345678901234567890_b;

    const BigInt::BigInt z = x * y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Multiplication of lots of positives", "[mul]") {
    auto i = GENERATE(range(0, 11));
    auto j = GENERATE(range(0, 11));

    const BigInt::BigInt x(i);
    const BigInt::BigInt y(j);
    const BigInt::BigInt z = x * y;

    REQUIRE(z.str() == std::to_string(i * j));
}

TEST_CASE("Multiplication of medium-sized positives", "[mul]") {
    const BigInt::BigInt x = 12345678901234567890_b;
    const BigInt::BigInt y = 98765432109876543210_b;
    const BigInt::BigInt z = x * y;

    REQUIRE(z.str() == "1219326311370217952237463801111263526900");
}

TEST_CASE("Multiplication with negative 1", "[mul]") {
    const BigInt::BigInt x = 123_b;
    const BigInt::BigInt y = -1_b;
    const BigInt::BigInt z = x * y;

    REQUIRE(z.str() == "-123");
}

TEST_CASE("Multiplication with 1", "[mul]") {
    const BigInt::BigInt x = -123_b;
    const BigInt::BigInt y = 1_b;
    const BigInt::BigInt z = x * y;

    REQUIRE(z.str() == "-123");
}

TEST_CASE("Multiplication of two negatives", "[mul]") {
    const BigInt::BigInt x = -123_b;
    const BigInt::BigInt y = -1_b;
    const BigInt::BigInt z = x * y;

    REQUIRE(z.str() == "123");
}

TEST_CASE("Multiplication to square", "[mul]") {
    const BigInt::BigInt x{"98765432109876543210"};
    const BigInt::BigInt y{"98765432109876543210"};

    const BigInt::BigInt z = x * y;
    REQUIRE(z.str() == "9754610579850632525677488187778997104100");
}

TEST_CASE("Multiplication of large positives", "[mul]") {
    const BigInt::BigInt x{
        "31415926535897932384626433832795028841971693993751058209749445923"
        "078164062862089986280348253421170679"};
    const BigInt::BigInt y{
        "27182818284590452353602874713526624977572470936999595749669676277"
        "240766303535945713821785251664274"};
    const BigInt::BigInt z = x * y;

    REQUIRE(
        z.str() ==
        "8539734222673567065463550869546574495034888535765114961879601130179"
        "2286111574783895762507500032728659347816207067867304373545360378584"
        "8133094851462428844661315312664336578255202869537848950160622046");
}

TEST_CASE("Multiplication equals", "[mul]") {
    BigInt::BigInt x = -123_b;
    const BigInt::BigInt y = -5_b;
    x *= y;

    REQUIRE(x.str() == "615");
}
