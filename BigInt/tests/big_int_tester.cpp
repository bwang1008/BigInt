#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#define CATCH_CONFIG_MAIN  // Catch2 will generate the main function
#include <catch2/catch.hpp>

#include "BigInt/src/big_int.hpp"


TEST_CASE("Constructor 00", "[constructor]") {
	std::string digits = "-3051029301904293";
    BigInt x(digits);

	REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor 01", "[constructor]") {
	std::string digits = "-0";
    BigInt x(digits);

    REQUIRE(x.str() == "0");
}

TEST_CASE("Constructor 02", "[constructor]") {
    std::string digits = "0";
    BigInt x(digits);

    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor 03", "[constructor]") {
    std::string digits = "-03";
    BigInt x(digits);

    REQUIRE(x.str() == "-3");
}

TEST_CASE("Constructor 04", "[constructor]") {
    std::string digits = "-00000000000000000000003";
    BigInt x(digits);

    REQUIRE(x.str() == "-3");
}

TEST_CASE("Constructor 05", "[constructor]") {
    std::string digits = "0000000000000000000000000000000003";
    BigInt x(digits);

    REQUIRE(x.str() == "3");
}

TEST_CASE("Constructor 06", "[constructor]") {
    const std::string digits = "123";
    BigInt x(digits);

    REQUIRE(x.str() == "123");
}

TEST_CASE("Constructor 07", "[constructor]") {
    const std::string digits = "1000000000000000";
    BigInt x{digits};
    REQUIRE(x.str() == digits);
}

TEST_CASE("Constructor 08", "[constructor]") {
    BigInt x{-103};
    REQUIRE(x.str() == "-103");
}

TEST_CASE("Constructor 09", "[constructor]") {
    BigInt x = -103;
    REQUIRE(x.str() == "-103");
}

TEST_CASE("Constructor 10", "[constructor]") {
    BigInt x = 0;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Literal 00", "[literal]") {
    BigInt x = 123_b;
    REQUIRE(x.str() == "123");
}

TEST_CASE("Literal 01", "[literal]") {
    BigInt x = 0_b;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Literal 02", "[literal]") {
    BigInt x = -0_b;
    REQUIRE(x.str() == "0");
}

TEST_CASE("Literal 03", "[literal]") {
    BigInt x = 99999999999999999999999999999999999999999_b;
    REQUIRE(x.str() == "99999999999999999999999999999999999999999");
}

TEST_CASE("Print 00", "[print]") {
    BigInt x{"123"};
    std::cout << "Testing printing from " << __func__ << std::endl;
    std::cout << x << std::endl;
    std::cout << "------" << std::endl;
    REQUIRE(true);
}

TEST_CASE("Negate 00", "[negate]") {
    BigInt x("3");
    BigInt y = -x;
    REQUIRE(y.str() == "-3");
}

TEST_CASE("Negate 01", "[negate]") {
    BigInt x("-3");
    BigInt y = -x;
    REQUIRE(y.str() == "3");
}

TEST_CASE("Negate 02", "[negate]") {
    BigInt x("0");
    BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negate 03", "[negate]") {
    BigInt x("-0");
    BigInt y = -x;
    REQUIRE(y.str() == "0");
}

TEST_CASE("Negate 04", "[negate]") {
    const std::string digits = "9999999999999999999";
    BigInt x(digits);
    BigInt y = -x;
    REQUIRE(y.str() == "-" + digits);
}

TEST_CASE("Negate 05", "[negate]") {
    const std::string digits = "-9999999999999999999";
    BigInt x(digits);
    BigInt y = -x;
    REQUIRE(y.str() == digits.substr(1, digits.size() - 1));
}

TEST_CASE("Clone 00", "[clone]") {
    BigInt x{"003"};
    BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Clone 01", "[clone]") {
    BigInt x{"-0"};
    BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Clone 02", "[clone]") {
    BigInt x{"12345678901234567890234568790"};
    BigInt y = x.clone();
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Add 00", "[add]") {
    BigInt x = 1_b;
    BigInt y = 2_b;
    BigInt z = x + y;

    REQUIRE(z.str() == "3");
}

TEST_CASE("Add 01", "[add]") {
    std::string zero12 = "000000000000";

    BigInt x{"1" + zero12};
    BigInt z = x + x;

    REQUIRE(x.str() == "1" + zero12);
    REQUIRE(z.str() == "2" + zero12);
}

TEST_CASE("Add 02", "[add]") {
    BigInt x{"5"};
    BigInt y{"3"};

    BigInt z = x + y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Add 03", "[add]") {
    BigInt x{"5"};
    BigInt y{"-3"};
    BigInt z = x + y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Add 04", "[add]") {
    BigInt x{"3"};
    BigInt y{"-5"};
    BigInt z = x + y;
    REQUIRE(z.str() == "-2");
}

TEST_CASE("Add 05", "[add]") {
    BigInt x{"3"};
    BigInt y{"-3"};
    BigInt z = x + y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Add 06", "[add]") {
    BigInt x{"936999595749669676277240766303535945713821785251664274"};
    BigInt y{"751058209749445923078164062862089986280348253421170679"};
    BigInt z = x + y;

    REQUIRE(z.str() == "1688057805499115599355404829165625931994170038672834953");
}

TEST_CASE("Sub 00", "[sub]") {
    BigInt x{"100"};
    BigInt y{"99"};

    BigInt z = x - y;
    REQUIRE(z.str() == "1");
}

TEST_CASE("Sub 01", "[sub]") {
    BigInt x{"98765432109876543210"};
    BigInt y{"1234567890"};

    BigInt z = x - y;
    REQUIRE(z.str() == "98765432108641975320");
}

TEST_CASE("Sub 02", "[sub]") {
    BigInt x{"98765432109876543210"};
    BigInt y{"98765432109876543210"};

    BigInt z = x - y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Sub 03", "[sub]") {
    BigInt x{"5"};
    BigInt y{"3"};

    BigInt z = x - y;
    REQUIRE(z.str() == "2");
}

TEST_CASE("Sub 04", "[sub]") {
    BigInt x{"5"};
    BigInt y{"-3"};
    BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Sub 05", "[sub]") {
    BigInt x{"3"};
    BigInt y{"-5"};
    BigInt z = x - y;
    REQUIRE(z.str() == "8");
}

TEST_CASE("Sub 06", "[sub]") {
    BigInt x{"3"};
    BigInt y{"-3"};
    BigInt z = x - y;
    REQUIRE(z.str() == "6");
}

TEST_CASE("Sub 07", "[sub]") {
    BigInt x{"1"};
    BigInt y{"100000000000000000000"};
    BigInt z = x - y;
    REQUIRE(z.str() == "-99999999999999999999");
}

TEST_CASE("Mul 00", "[mul]") {
    BigInt x = 0_b;
    BigInt y = 12345678901234567890_b;

    BigInt z = x * y;
    REQUIRE(z.str() == "0");
}

TEST_CASE("Mul 01", "[mul]") {
    BigInt x = 2_b;
    BigInt y = 3_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "6");
}

TEST_CASE("Mul 02", "[mul]") {
    BigInt x = 12345678901234567890_b;
    BigInt y = 98765432109876543210_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "1219326311370217952237463801111263526900");
}

TEST_CASE("Mul 03", "[mul]") {
    BigInt x = 123_b;
    BigInt y = -1_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "-123");
}

TEST_CASE("Mul 04", "[mul]") {
    BigInt x = -123_b;
    BigInt y = 1_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "-123");
}

TEST_CASE("Mul 05", "[mul]") {
    BigInt x = -123_b;
    BigInt y = -1_b;
    BigInt z = x * y;

    REQUIRE(z.str() == "123");
}

TEST_CASE("Mul 06", "[mul]") {
    BigInt x{"98765432109876543210"};
    BigInt y{"98765432109876543210"};

    BigInt z = x * y;
    REQUIRE(z.str() == "9754610579850632525677488187778997104100");
}

TEST_CASE("mul 07", "[mul]") {
    BigInt x{"31415926535897932384626433832795028841971693993751058209749445923"
             "078164062862089986280348253421170679"};
    BigInt y{"27182818284590452353602874713526624977572470936999595749669676277"
             "240766303535945713821785251664274"};
    BigInt z = x * y;

    REQUIRE(z.str() ==
           "8539734222673567065463550869546574495034888535765114961879601130179"
           "2286111574783895762507500032728659347816207067867304373545360378584"
           "8133094851462428844661315312664336578255202869537848950160622046");
}

TEST_CASE("Equality 00", "[equality]") {
    std::string digits = "-1234567890123456789";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality 01", "[equality]") {
    std::string digits = "-1";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality 02", "[equality]") {
    std::string digits = "0";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality 03", "[equality]") {
    std::string digits = "25";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality 04", "[equality]") {
    std::string digits = "1234567890123456789";
    BigInt x{digits};
    BigInt y{digits};

    REQUIRE(x == y);
}

TEST_CASE("Equality 05", "[equality]") {
    BigInt x{"-0"};
    BigInt y{"0"};

    REQUIRE(x == y);
}

TEST_CASE("Inequality 00", "[inequality]") {
    BigInt x{"-0123456789"};
    BigInt y{"-1234567890"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality 01", "[inequality]") {
    BigInt x{"-1"};
    BigInt y{"-2"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality 02", "[inequality]") {
    BigInt x{"-1"};
    BigInt y{"0"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality 03", "[inequality]") {
    BigInt x{"-1"};
    BigInt y{"1"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality 04", "[inequality]") {
    BigInt x{"0"};
    BigInt y{"-1"};

    REQUIRE(x != y);
}

TEST_CASE("Inequality 05", "[inequality]") {
    BigInt x{"1"};
    BigInt y{"2"};

    REQUIRE(x != y);
}

TEST_CASE("Compare 00", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"-1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare 01", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"0"};

    REQUIRE(x < y);
}

TEST_CASE("Compare 02", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare 03", "[compare]") {
    BigInt x{"0"};
    BigInt y{"1"};

    REQUIRE(x < y);
}

TEST_CASE("Compare 04", "[compare]") {
    BigInt x{"1"};
    BigInt y{"2"};

    REQUIRE(x < y);
}

TEST_CASE("Compare 05", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"-1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare 06", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"0"};

    REQUIRE(y > x);
}

TEST_CASE("Compare 07", "[compare]") {
    BigInt x{"-2"};
    BigInt y{"1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare 08", "[compare]") {
    BigInt x{"0"};
    BigInt y{"1"};

    REQUIRE(y > x);
}

TEST_CASE("Compare 09", "[compare]") {
    BigInt x{"1"};
    BigInt y{"2"};

    REQUIRE(y > x);
}

TEST_CASE("Compare 10", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 11", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567790"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 12", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 13", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"0"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 14", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 15", "[compare]") {
    BigInt x{"0"};
    BigInt y{"0"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 16", "[compare]") {
    BigInt x{"0"};
    BigInt y{"12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 17", "[compare]") {
    BigInt x{"123"};
    BigInt y{"123"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 18", "[compare]") {
    BigInt x{"123"};
    BigInt y{"12345678901234567890"};

    REQUIRE(x <= y);
}

TEST_CASE("Compare 19", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567890"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 20", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567790"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 21", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 22", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"0"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 23", "[compare]") {
    BigInt x{"-12345678901234567890"};
    BigInt y{"123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 24", "[compare]") {
    BigInt x{"0"};
    BigInt y{"0"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 25", "[compare]") {
    BigInt x{"0"};
    BigInt y{"12345678901234567890"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 26", "[compare]") {
    BigInt x{"123"};
    BigInt y{"123"};

    REQUIRE(y >= x);
}

TEST_CASE("Compare 27", "[compare]") {
    BigInt x{"123"};
    BigInt y{"12345678901234567890"};

    REQUIRE(y >= x);
}
