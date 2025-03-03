#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/include/big_int.hpp"

TEST_CASE("Equality from same constructor", "[equality]") {
    std::string digits = "-1234567890123456789";
    BigInt::BigInt x{digits};
    BigInt::BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of same negative number", "[equality]") {
    std::string digits = "-1";
    BigInt::BigInt x{digits};
    BigInt::BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of 0", "[equality]") {
    std::string digits = "0";
    BigInt::BigInt x{digits};
    BigInt::BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of small positive number", "[equality]") {
    std::string digits = "25";
    BigInt::BigInt x{digits};
    BigInt::BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of big positive number", "[equality]") {
    std::string digits = "1234567890123456789";
    BigInt::BigInt x{digits};
    BigInt::BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of 0 and negative 0", "[equality]") {
    BigInt::BigInt x{"-0"};
    BigInt::BigInt y{"0"};

    REQUIRE(x == y);
}

TEST_CASE("Inequality of negative numbers", "[inequality]") {
    BigInt::BigInt x{"-0123456789"};
    BigInt::BigInt y{"-1234567890"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality of small negative numbers", "[inequality]") {
    BigInt::BigInt x{"-1"};
    BigInt::BigInt y{"-2"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality with 0", "[inequality]") {
    BigInt::BigInt x{"-1"};
    BigInt::BigInt y{"0"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality for different signs", "[inequality]") {
    BigInt::BigInt x{"-1"};
    BigInt::BigInt y{"1"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality of 0 but flipped", "[inequality]") {
    BigInt::BigInt x{"0"};
    BigInt::BigInt y{"-1"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality of small positives", "[inequality]") {
    BigInt::BigInt x{"1"};
    BigInt::BigInt y{"2"};

    REQUIRE(x != y);
}

TEST_CASE("Compare less than of negative numbers", "[compare]") {
    BigInt::BigInt x{"-2"};
    BigInt::BigInt y{"-1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare negative less than 0", "[compare]") {
    BigInt::BigInt x{"-2"};
    BigInt::BigInt y{"0"};

    REQUIRE(x < y);
}

TEST_CASE("Compare negative less than positive", "[compare]") {
    BigInt::BigInt x{"-2"};
    BigInt::BigInt y{"1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare zero less than positive", "[compare]") {
    BigInt::BigInt x{"0"};
    BigInt::BigInt y{"1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare small positives", "[compare]") {
    BigInt::BigInt x{"1"};
    BigInt::BigInt y{"2"};

    REQUIRE(x < y);
}

TEST_CASE("Compare greater of negative numbers", "[compare]") {
    BigInt::BigInt x{"-2"};
    BigInt::BigInt y{"-1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare zero greater than negative", "[compare]") {
    BigInt::BigInt x{"-2"};
    BigInt::BigInt y{"0"};

    REQUIRE(y > x);
}

TEST_CASE("Compare positive greater than negative", "[compare]") {
    BigInt::BigInt x{"-2"};
    BigInt::BigInt y{"1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare positive greater than zero", "[compare]") {
    BigInt::BigInt x{"0"};
    BigInt::BigInt y{"1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare greater-than for small positives", "[compare]") {
    BigInt::BigInt x{"1"};
    BigInt::BigInt y{"2"};

    REQUIRE(y > x);
}

TEST_CASE("Compare less-than-equal of same numbers", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"-12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of large negatives", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"-12345678901234567790"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of big and small negatives", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"-123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal with 0", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"0"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal with negative and positive", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of zero with itself", "[compare]") {
    BigInt::BigInt x{"0"};
    BigInt::BigInt y{"0"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of 0 with large positive", "[compare]") {
    BigInt::BigInt x{"0"};
    BigInt::BigInt y{"12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of same positive number", "[compare]") {
    BigInt::BigInt x{"123"};
    BigInt::BigInt y{"123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of small and big positives", "[compare]") {
    BigInt::BigInt x{"123"};
    BigInt::BigInt y{"12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare greater-or-equal of same numbers", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"-12345678901234567890"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of large negative numbers", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"-12345678901234567790"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of small and large negatives",
          "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"-123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of zero with negative", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"0"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of positive with negative", "[compare]") {
    BigInt::BigInt x{"-12345678901234567890"};
    BigInt::BigInt y{"123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of both zero", "[compare]") {
    BigInt::BigInt x{"0"};
    BigInt::BigInt y{"0"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of positive with zero", "[compare]") {
    BigInt::BigInt x{"0"};
    BigInt::BigInt y{"12345678901234567890"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of same positive number", "[compare]") {
    BigInt::BigInt x{"123"};
    BigInt::BigInt y{"123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of small and big positive number",
          "[compare]") {
    BigInt::BigInt x{"123"};
    BigInt::BigInt y{"12345678901234567890"};

    REQUIRE(y >= x);
}
