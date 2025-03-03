#include <sstream> // std::stringstream
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

TEST_CASE("Clone", "[clone]") {
    BigInt::BigInt x{"003"};
    BigInt::BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Clone of negative zero", "[clone]") {
    BigInt::BigInt x{"-0"};
    BigInt::BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Clone of large number", "[clone]") {
    BigInt::BigInt x{"12345678901234567890234568790"};
    BigInt::BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

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
