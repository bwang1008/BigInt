#include <sstream>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/src/big_int.hpp"

TEST_CASE("Constructor of Negative Number", "[constructor]") {
    std::string digits = "-3051029301904293";
    BigInt x(digits);

    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor of Negative Zero", "[constructor]") {
    std::string digits = "-0";
    BigInt x(digits);

    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor of Zero", "[constructor]") {
    std::string digits = "0";
    BigInt x(digits);

    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor of Negative Number with Leading Zero", "[constructor]") {
    std::string digits = "-03";
    BigInt x(digits);

    REQUIRE(x.str() == "-3");
}

TEST_CASE("Constructor of Negative Number with Leading Zeroes",
          "[constructor]") {
    std::string digits = "-00000000000000000000003";
    BigInt x(digits);

    REQUIRE(x.str() == "-3");
}

TEST_CASE("Constructor of Positive Number with Leading Zeroes",
          "[constructor]") {
    std::string digits = "0000000000000000000000000000000003";
    BigInt x(digits);

    REQUIRE(x.str() == "3");
}

TEST_CASE("Constructor of Positive Number", "[constructor]") {
    const std::string digits = "123";
    BigInt x(digits);

    REQUIRE(x.str() == "123");
}

TEST_CASE("Constructor of Large Positive Number", "[constructor]") {
    const std::string digits = "1000000000000000";
    BigInt x{digits};
    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor from int", "[constructor]") {
    const int negative_value = -103;
    BigInt x{negative_value};
    REQUIRE(x.str() == "-103");
}

TEST_CASE("Default Constructor", "[constructor]") {
    BigInt x;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor via literal", "[literal]") {
    BigInt x = 123_b;
    REQUIRE(x.str() == "123");
}

TEST_CASE("Constructor via literal of 0", "[literal]") {
    BigInt x = 0_b;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor via literal of negative 0", "[literal]") {
    BigInt x = -0_b;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor via big literal", "[literal]") {
    BigInt x = 99999999999999999999999999999999999999999_b;
    REQUIRE(x.str() == "99999999999999999999999999999999999999999");
}

TEST_CASE("Check output representation", "[print]") {
    BigInt x{"123"};
    std::stringstream ss;
    ss << x;
    const std::string printed_representation = ss.str();
    REQUIRE(printed_representation == "123");
}

TEST_CASE("Negation of positive", "[negate]") {
    BigInt x("3");
    BigInt y = -x;
    REQUIRE(y.str() == "-3");
}

TEST_CASE("Negation of negative", "[negate]") {
    BigInt x("-3");
    BigInt y = -x;
    REQUIRE(y.str() == "3");
}

TEST_CASE("Negattion of zero", "[negate]") {
    BigInt x("0");
    BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negation of negative zero", "[negate]") {
    BigInt x("-0");
    BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negation string representation", "[negate]") {
    const std::string digits = "9999999999999999999";
    BigInt x(digits);
    BigInt y = -x;
    REQUIRE(y.str() == "-" + digits);
}

TEST_CASE("Negation of long negative", "[negate]") {
    const std::string digits = "-9999999999999999999";
    BigInt x(digits);
    BigInt y = -x;
    REQUIRE(y.str() == digits.substr(1, digits.size() - 1));
}

TEST_CASE("Clone", "[clone]") {
    BigInt x{"003"};
    BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Clone of negative zero", "[clone]") {
    BigInt x{"-0"};
    BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Clone of large number", "[clone]") {
    BigInt x{"12345678901234567890234568790"};
    BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Addition of small positive", "[add]") {
    BigInt x = 1_b;
    BigInt y = 2_b;
    BigInt z = x + y;

    REQUIRE(z.str() == "3");
}

TEST_CASE("Addition to doubling", "[add]") {
    std::string zero12 = "000000000000";

    BigInt x{"1" + zero12};
    BigInt z = x + x;

    REQUIRE(x.str() == "1" + zero12);
    REQUIRE(z.str() == "2" + zero12);
}

TEST_CASE("Addition of positive", "[add]") {
    BigInt x{"5"};
    BigInt y{"3"};

    BigInt z = x + y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Addition with negative", "[add]") {
    BigInt x{"5"};
    BigInt y{"-3"};
    BigInt z = x + y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Addition with negative flipped", "[add]") {
    BigInt x{"3"};
    BigInt y{"-5"};
    BigInt z = x + y;
    REQUIRE(z.str() == "-2");
}

TEST_CASE("Addition of opposites", "[add]") {
    BigInt x{"3"};
    BigInt y{"-3"};
    BigInt z = x + y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Addition of large positives", "[add]") {
    BigInt x{"936999595749669676277240766303535945713821785251664274"};
    BigInt y{"751058209749445923078164062862089986280348253421170679"};
    BigInt z = x + y;

    REQUIRE(z.str() ==
            "1688057805499115599355404829165625931994170038672834953");
}

TEST_CASE("Subtraction of positives", "[sub]") {
    BigInt x{"100"};
    BigInt y{"99"};

    BigInt z = x - y;
    REQUIRE(z.str() == "1");
}

TEST_CASE("Subtraction of positives with large difference", "[sub]") {
    BigInt x{"98765432109876543210"};
    BigInt y{"1234567890"};

    BigInt z = x - y;
    REQUIRE(z.str() == "98765432108641975320");
}

TEST_CASE("Subtraction of same number", "[sub]") {
    BigInt x{"98765432109876543210"};
    BigInt y{"98765432109876543210"};

    BigInt z = x - y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Subtraction of small positives", "[sub]") {
    BigInt x{"5"};
    BigInt y{"3"};

    BigInt z = x - y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Subtraction of negative number", "[sub]") {
    BigInt x{"5"};
    BigInt y{"-3"};
    BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Subtraction with bigger negative number", "[sub]") {
    BigInt x{"3"};
    BigInt y{"-5"};
    BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Subtraction of opposites", "[sub]") {
    BigInt x{"3"};
    BigInt y{"-3"};
    BigInt z = x - y;
    REQUIRE(z.str() == "6");
}

TEST_CASE("Subtraction of large value", "[sub]") {
    BigInt x{"1"};
    BigInt y{"100000000000000000000"};
    BigInt z = x - y;
    REQUIRE(z.str() == "-99999999999999999999");
}

TEST_CASE("Equality from same constructor", "[equality]") {
    std::string digits = "-1234567890123456789";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of same negative number", "[equality]") {
    std::string digits = "-1";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of 0", "[equality]") {
    std::string digits = "0";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of small positive number", "[equality]") {
    std::string digits = "25";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of big positive number", "[equality]") {
    std::string digits = "1234567890123456789";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality of 0 and negative 0", "[equality]") {
    BigInt x{"-0"};
    BigInt y{"0"};

    REQUIRE(x == y);
}

TEST_CASE("Inequality of negative numbers", "[inequality]") {
    BigInt x{"-0123456789"};
    BigInt y{"-1234567890"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality of small negative numbers", "[inequality]") {
    BigInt x{"-1"};
    BigInt y{"-2"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality with 0", "[inequality]") {
    BigInt x{"-1"};
    BigInt y{"0"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality for different signs", "[inequality]") {
    BigInt x{"-1"};
    BigInt y{"1"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality of 0 but flipped", "[inequality]") {
    BigInt x{"0"};
    BigInt y{"-1"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality of small positives", "[inequality]") {
    BigInt x{"1"};
    BigInt y{"2"};

    REQUIRE(x != y);
}

TEST_CASE("Compare less than of negative numbers", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"-1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare negative less than 0", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"0"};

    REQUIRE(x < y);
}

TEST_CASE("Compare negative less than positive", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare zero less than positive", "[compare]") {
    BigInt x{"0"};
    BigInt y{"1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare small positives", "[compare]") {
    BigInt x{"1"};
    BigInt y{"2"};

    REQUIRE(x < y);
}

TEST_CASE("Compare greater of negative numbers", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"-1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare zero greater than negative", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"0"};

    REQUIRE(y > x);
}

TEST_CASE("Compare positive greater than negative", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare positive greater than zero", "[compare]") {
    BigInt x{"0"};
    BigInt y{"1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare greater-than for small positives", "[compare]") {
    BigInt x{"1"};
    BigInt y{"2"};

    REQUIRE(y > x);
}

TEST_CASE("Compare less-than-equal of same numbers", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of large negatives", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567790"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of big and small negatives", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal with 0", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"0"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal with negative and positive", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of zero with itself", "[compare]") {
    BigInt x{"0"};
    BigInt y{"0"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of 0 with large positive", "[compare]") {
    BigInt x{"0"};
    BigInt y{"12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of same positive number", "[compare]") {
    BigInt x{"123"};
    BigInt y{"123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare less-than-equal of small and big positives", "[compare]") {
    BigInt x{"123"};
    BigInt y{"12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare greater-or-equal of same numbers", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567890"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of large negative numbers", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567790"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of small and large negatives",
          "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of zero with negative", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"0"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of positive with negative", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of both zero", "[compare]") {
    BigInt x{"0"};
    BigInt y{"0"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of positive with zero", "[compare]") {
    BigInt x{"0"};
    BigInt y{"12345678901234567890"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of same positive number", "[compare]") {
    BigInt x{"123"};
    BigInt y{"123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare greater-or-equal of small and big positive number",
          "[compare]") {
    BigInt x{"123"};
    BigInt y{"12345678901234567890"};

    REQUIRE(y >= x);
}
