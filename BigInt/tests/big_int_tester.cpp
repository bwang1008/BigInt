#include "BigInt/src/big_int.hpp"

#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

struct TestCasesSummary {
    int numPassed;
    int numFailed;
    int numErrored;
    std::list<std::string> failedFunctions;
    std::list<std::string> erroredFunctions;

    TestCasesSummary()
        : numPassed(0), numFailed(0), numErrored(0), failedFunctions(),
          erroredFunctions() {}
};

bool test_constructor_00() {
    std::string digits = "-3051029301904293";
    BigInt x(digits);

    return x.str() == digits;
}

bool test_constructor_01() {
    std::string digits = "-0";
    BigInt x(digits);

    return x.str() == "0";
}

bool test_constructor_02() {
    std::string digits = "0";
    BigInt x(digits);

    return x.str() == digits;
}

bool test_constructor_03() {
    std::string digits = "-03";
    BigInt x(digits);

    return x.str() == "-3";
}

bool test_constructor_04() {
    std::string digits = "-00000000000000000000003";
    BigInt x(digits);

    return x.str() == "-3";
}

bool test_constructor_05() {
    std::string digits = "0000000000000000000000000000000003";
    BigInt x(digits);

    return x.str() == "3";
}

bool test_constructor_06() {
    const std::string digits = "123";
    BigInt x(digits);

    return x.str() == "123";
}

bool test_constructor_07() {
    const std::string digits = "1000000000000000";
    BigInt x{digits};
    return x.str() == digits;
}

bool test_constructor_08() {
    BigInt x{-103};
    return x.str() == "-103";
}

bool test_constructor_09() {
    BigInt x = -103;
    return x.str() == "-103";
}

bool test_constructor_10() {
    BigInt x = 0;
    return x.str() == "0";
}

bool test_literal_00() {
    BigInt x = 123_b;
    return x.str() == "123";
}

bool test_literal_01() {
    BigInt x = 0_b;
    return x.str() == "0";
}

bool test_literal_02() {
    BigInt x = -0_b;
    return x.str() == "0";
}

bool test_literal_03() {
    BigInt x = 99999999999999999999999999999999999999999_b;
    return x.str() == "99999999999999999999999999999999999999999";
}

bool test_print_00() {
    BigInt x{"123"};
    std::cout << "Testing printing from " << __func__ << std::endl;
    std::cout << x << std::endl;
    std::cout << "------" << std::endl;
    return true;
}

bool test_negate_00() {
    BigInt x("3");
    BigInt y = -x;
    return y.str() == "-3";
}

bool test_negate_01() {
    BigInt x("-3");
    BigInt y = -x;
    return y.str() == "3";
}

bool test_negate_02() {
    BigInt x("0");
    BigInt y = -x;
    return y.str() == "0";
}

bool test_negate_03() {
    BigInt x("-0");
    BigInt y = -x;
    return y.str() == "0";
}

bool test_negate_04() {
    const std::string digits = "9999999999999999999";
    BigInt x(digits);
    BigInt y = -x;
    return y.str() == "-" + digits;
}

bool test_negate_05() {
    const std::string digits = "-9999999999999999999";
    BigInt x(digits);
    BigInt y = -x;
    return y.str() == digits.substr(1, digits.size() - 1);
}

bool test_clone_00() {
    BigInt x{"003"};
    BigInt y = x.clone();
    return y.str() == x.str();
}

bool test_clone_01() {
    BigInt x{"-0"};
    BigInt y = x.clone();
    return y.str() == x.str();
}

bool test_clone_02() {
    BigInt x{"12345678901234567890234568790"};
    BigInt y = x.clone();
    return y.str() == x.str();
}

bool test_add_00() {
    BigInt x = 1_b;
    BigInt y = 2_b;
    BigInt z = x + y;

    return z.str() == "3";
}

bool test_add_01() {
    std::string zero12 = "000000000000";

    BigInt x{"1" + zero12};
    BigInt z = x + x;

    return (x.str() == "1" + zero12) && (z.str() == "2" + zero12);
}

bool test_add_02() {
    BigInt x{"5"};
    BigInt y{"3"};

    BigInt z = x + y;
    return z.str() == "8";
}

bool test_add_03() {
    BigInt x{"5"};
    BigInt y{"-3"};
    BigInt z = x + y;
    return z.str() == "2";
}

bool test_add_04() {
    BigInt x{"3"};
    BigInt y{"-5"};
    BigInt z = x + y;
    return z.str() == "-2";
}

bool test_add_05() {
    BigInt x{"3"};
    BigInt y{"-3"};
    BigInt z = x + y;
    return z.str() == "0";
}

bool test_add_06() {
    BigInt x{"936999595749669676277240766303535945713821785251664274"};
    BigInt y{"751058209749445923078164062862089986280348253421170679"};
    BigInt z = x + y;

    return z.str() == "1688057805499115599355404829165625931994170038672834953";
}

bool test_sub_00() {
    BigInt x{"100"};
    BigInt y{"99"};

    BigInt z = x - y;
    return z.str() == "1";
}

bool test_sub_01() {
    BigInt x{"98765432109876543210"};
    BigInt y{"1234567890"};

    BigInt z = x - y;
    return z.str() == "98765432108641975320";
}

bool test_sub_02() {
    BigInt x{"98765432109876543210"};
    BigInt y{"98765432109876543210"};

    BigInt z = x - y;
    return z.str() == "0";
}

bool test_sub_03() {
    BigInt x{"5"};
    BigInt y{"3"};

    BigInt z = x - y;
    return z.str() == "2";
}

bool test_sub_04() {
    BigInt x{"5"};
    BigInt y{"-3"};
    BigInt z = x - y;
    return z.str() == "8";
}

bool test_sub_05() {
    BigInt x{"3"};
    BigInt y{"-5"};
    BigInt z = x - y;
    return z.str() == "8";
}

bool test_sub_06() {
    BigInt x{"3"};
    BigInt y{"-3"};
    BigInt z = x - y;
    return z.str() == "6";
}

bool test_sub_07() {
    BigInt x{"1"};
    BigInt y{"100000000000000000000"};
    BigInt z = x - y;
    return z.str() == "-99999999999999999999";
}

bool test_mul_00() {
    BigInt x = 0_b;
    BigInt y = 12345678901234567890_b;

    BigInt z = x * y;
    return z.str() == "0";
}

bool test_mul_01() {
    BigInt x = 2_b;
    BigInt y = 3_b;
    BigInt z = x * y;

    return z.str() == "6";
}

bool test_mul_02() {
    BigInt x = 12345678901234567890_b;
    BigInt y = 98765432109876543210_b;
    BigInt z = x * y;

    return z.str() == "1219326311370217952237463801111263526900";
}

bool test_mul_03() {
    BigInt x = 123_b;
    BigInt y = -1_b;
    BigInt z = x * y;

    return z.str() == "-123";
}

bool test_mul_04() {
    BigInt x = -123_b;
    BigInt y = 1_b;
    BigInt z = x * y;

    return z.str() == "-123";
}

bool test_mul_05() {
    BigInt x = -123_b;
    BigInt y = -1_b;
    BigInt z = x * y;

    return z.str() == "123";
}

bool test_mul_06() {
    BigInt x{"98765432109876543210"};
    BigInt y{"98765432109876543210"};

    BigInt z = x * y;
    return z.str() == "9754610579850632525677488187778997104100";
}

bool test_mul_07() {
    BigInt x{"31415926535897932384626433832795028841971693993751058209749445923"
             "078164062862089986280348253421170679"};
    BigInt y{"27182818284590452353602874713526624977572470936999595749669676277"
             "240766303535945713821785251664274"};
    BigInt z = x * y;

    return z.str() ==
           "8539734222673567065463550869546574495034888535765114961879601130179"
           "2286111574783895762507500032728659347816207067867304373545360378584"
           "8133094851462428844661315312664336578255202869537848950160622046";
}

bool test_equality_00() {
    std::string digits = "-1234567890123456789";
    BigInt x{digits};
    BigInt y{digits};

    return x == y;
}

bool test_equality_01() {
    std::string digits = "-1";
    BigInt x{digits};
    BigInt y{digits};

    return x == y;
}

bool test_equality_02() {
    std::string digits = "0";
    BigInt x{digits};
    BigInt y{digits};

    return x == y;
}

bool test_equality_03() {
    std::string digits = "25";
    BigInt x{digits};
    BigInt y{digits};

    return x == y;
}

bool test_equality_04() {
    std::string digits = "1234567890123456789";
    BigInt x{digits};
    BigInt y{digits};

    return x == y;
}

bool test_equality_05() {
    BigInt x{"-0"};
    BigInt y{"0"};

    return x == y;
}

bool test_inequality_00() {
    BigInt x{"-0123456789"};
    BigInt y{"-1234567890"};

    return x != y;
}

bool test_inequality_01() {
    BigInt x{"-1"};
    BigInt y{"-2"};

    return x != y;
}

bool test_inequality_02() {
    BigInt x{"-1"};
    BigInt y{"0"};

    return x != y;
}

bool test_inequality_03() {
    BigInt x{"-1"};
    BigInt y{"1"};

    return x != y;
}

bool test_inequality_04() {
    BigInt x{"0"};
    BigInt y{"-1"};

    return x != y;
}

bool test_inequality_05() {
    BigInt x{"1"};
    BigInt y{"2"};

    return x != y;
}

bool test_compare_00() {
    BigInt x{"-2"};
    BigInt y{"-1"};

    return (x < y);
}

bool test_compare_01() {
    BigInt x{"-2"};
    BigInt y{"0"};

    return (x < y);
}

bool test_compare_02() {
    BigInt x{"-2"};
    BigInt y{"1"};

    return (x < y);
}

bool test_compare_03() {
    BigInt x{"0"};
    BigInt y{"1"};

    return (x < y);
}

bool test_compare_04() {
    BigInt x{"1"};
    BigInt y{"2"};

    return (x < y);
}

bool test_compare_05() {
    BigInt x{"-2"};
    BigInt y{"-1"};

    return (y > x);
}

bool test_compare_06() {
    BigInt x{"-2"};
    BigInt y{"0"};

    return (y > x);
}

bool test_compare_07() {
    BigInt x{"-2"};
    BigInt y{"1"};

    return (y > x);
}

bool test_compare_08() {
    BigInt x{"0"};
    BigInt y{"1"};

    return (y > x);
}

bool test_compare_09() {
    BigInt x{"1"};
    BigInt y{"2"};

    return (y > x);
}

bool test_compare_10() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567890"};

    return (x <= y);
}

bool test_compare_11() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567790"};

    return (x <= y);
}

bool test_compare_12() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-123"};

    return (x <= y);
}

bool test_compare_13() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"0"};

    return (x <= y);
}

bool test_compare_14() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"123"};

    return (x <= y);
}

bool test_compare_15() {
    BigInt x{"0"};
    BigInt y{"0"};

    return (x <= y);
}

bool test_compare_16() {
    BigInt x{"0"};
    BigInt y{"12345678901234567890"};

    return (x <= y);
}

bool test_compare_17() {
    BigInt x{"123"};
    BigInt y{"123"};

    return (x <= y);
}

bool test_compare_18() {
    BigInt x{"123"};
    BigInt y{"12345678901234567890"};

    return (x <= y);
}

bool test_compare_19() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567890"};

    return (y >= x);
}

bool test_compare_20() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-12345678901234567790"};

    return (y >= x);
}

bool test_compare_21() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"-123"};

    return (y >= x);
}

bool test_compare_22() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"0"};

    return (y >= x);
}

bool test_compare_23() {
    BigInt x{"-12345678901234567890"};
    BigInt y{"123"};

    return (y >= x);
}

bool test_compare_24() {
    BigInt x{"0"};
    BigInt y{"0"};

    return (y >= x);
}

bool test_compare_25() {
    BigInt x{"0"};
    BigInt y{"12345678901234567890"};

    return (y >= x);
}

bool test_compare_26() {
    BigInt x{"123"};
    BigInt y{"123"};

    return (y >= x);
}

bool test_compare_27() {
    BigInt x{"123"};
    BigInt y{"12345678901234567890"};

    return (y >= x);
}

TestCasesSummary runTestCases() {
    TestCasesSummary summary;

    typedef bool (*functionPointer)(void);
    std::map<std::string, functionPointer> namesToFunctions;

    // constructor test cases
    namesToFunctions["test_constructor_00"] = &test_constructor_00;
    namesToFunctions["test_constructor_01"] = &test_constructor_01;
    namesToFunctions["test_constructor_02"] = &test_constructor_02;
    namesToFunctions["test_constructor_03"] = &test_constructor_03;
    namesToFunctions["test_constructor_04"] = &test_constructor_04;
    namesToFunctions["test_constructor_05"] = &test_constructor_05;
    namesToFunctions["test_constructor_06"] = &test_constructor_06;
    namesToFunctions["test_constructor_07"] = &test_constructor_07;
    namesToFunctions["test_constructor_08"] = &test_constructor_08;
    namesToFunctions["test_constructor_09"] = &test_constructor_09;
    namesToFunctions["test_constructor_10"] = &test_constructor_10;

    // user-defined literal test cases
    namesToFunctions["test_literal_00"] = &test_literal_00;
    namesToFunctions["test_literal_01"] = &test_literal_01;
    namesToFunctions["test_literal_02"] = &test_literal_02;
    namesToFunctions["test_literal_03"] = &test_literal_03;

    // printing test case
    namesToFunctions["test_print_00"] = &test_print_00;

    // negation test cases
    namesToFunctions["test_negate_00"] = &test_negate_00;
    namesToFunctions["test_negate_01"] = &test_negate_01;
    namesToFunctions["test_negate_02"] = &test_negate_02;
    namesToFunctions["test_negate_03"] = &test_negate_03;
    namesToFunctions["test_negate_04"] = &test_negate_04;
    namesToFunctions["test_negate_05"] = &test_negate_05;

    // clone test cases
    namesToFunctions["test_clone_00"] = &test_clone_00;
    namesToFunctions["test_clone_01"] = &test_clone_01;
    namesToFunctions["test_clone_02"] = &test_clone_02;

    // addition test cases
    namesToFunctions["test_add_00"] = &test_add_00;
    namesToFunctions["test_add_01"] = &test_add_01;
    namesToFunctions["test_add_02"] = &test_add_02;
    namesToFunctions["test_add_03"] = &test_add_03;
    namesToFunctions["test_add_04"] = &test_add_04;
    namesToFunctions["test_add_05"] = &test_add_05;
    namesToFunctions["test_add_06"] = &test_add_06;

    // subtraction test cases
    namesToFunctions["test_sub_00"] = &test_sub_00;
    namesToFunctions["test_sub_01"] = &test_sub_01;
    namesToFunctions["test_sub_02"] = &test_sub_02;
    namesToFunctions["test_sub_03"] = &test_sub_03;
    namesToFunctions["test_sub_04"] = &test_sub_04;
    namesToFunctions["test_sub_05"] = &test_sub_05;
    namesToFunctions["test_sub_06"] = &test_sub_06;
    namesToFunctions["test_sub_07"] = &test_sub_07;

    // multiplication test cases
    namesToFunctions["test_mul_00"] = &test_mul_00;
    namesToFunctions["test_mul_01"] = &test_mul_01;
    namesToFunctions["test_mul_02"] = &test_mul_02;
    namesToFunctions["test_mul_03"] = &test_mul_03;
    namesToFunctions["test_mul_04"] = &test_mul_04;
    namesToFunctions["test_mul_05"] = &test_mul_05;
    namesToFunctions["test_mul_06"] = &test_mul_06;
    namesToFunctions["test_mul_07"] = &test_mul_07;

    // equality test cases
    namesToFunctions["test_equality_00"] = &test_equality_00;
    namesToFunctions["test_equality_01"] = &test_equality_01;
    namesToFunctions["test_equality_02"] = &test_equality_02;
    namesToFunctions["test_equality_03"] = &test_equality_03;
    namesToFunctions["test_equality_04"] = &test_equality_04;
    namesToFunctions["test_equality_05"] = &test_equality_05;

    // inequality test cases
    namesToFunctions["test_inequality_00"] = &test_inequality_00;
    namesToFunctions["test_inequality_01"] = &test_inequality_01;
    namesToFunctions["test_inequality_02"] = &test_inequality_02;
    namesToFunctions["test_inequality_03"] = &test_inequality_03;
    namesToFunctions["test_inequality_04"] = &test_inequality_04;
    namesToFunctions["test_inequality_05"] = &test_inequality_05;

    // comparison test cases
    namesToFunctions["test_compare_00"] = &test_compare_00;
    namesToFunctions["test_compare_01"] = &test_compare_01;
    namesToFunctions["test_compare_02"] = &test_compare_02;
    namesToFunctions["test_compare_03"] = &test_compare_03;
    namesToFunctions["test_compare_04"] = &test_compare_04;
    namesToFunctions["test_compare_05"] = &test_compare_05;
    namesToFunctions["test_compare_06"] = &test_compare_06;
    namesToFunctions["test_compare_07"] = &test_compare_07;
    namesToFunctions["test_compare_08"] = &test_compare_08;
    namesToFunctions["test_compare_09"] = &test_compare_09;
    namesToFunctions["test_compare_10"] = &test_compare_10;
    namesToFunctions["test_compare_11"] = &test_compare_11;
    namesToFunctions["test_compare_12"] = &test_compare_12;
    namesToFunctions["test_compare_13"] = &test_compare_13;
    namesToFunctions["test_compare_14"] = &test_compare_14;
    namesToFunctions["test_compare_15"] = &test_compare_15;
    namesToFunctions["test_compare_16"] = &test_compare_16;
    namesToFunctions["test_compare_17"] = &test_compare_17;
    namesToFunctions["test_compare_18"] = &test_compare_18;
    namesToFunctions["test_compare_19"] = &test_compare_19;
    namesToFunctions["test_compare_20"] = &test_compare_20;
    namesToFunctions["test_compare_21"] = &test_compare_21;
    namesToFunctions["test_compare_22"] = &test_compare_22;
    namesToFunctions["test_compare_23"] = &test_compare_23;
    namesToFunctions["test_compare_24"] = &test_compare_24;
    namesToFunctions["test_compare_25"] = &test_compare_25;
    namesToFunctions["test_compare_26"] = &test_compare_26;
    namesToFunctions["test_compare_27"] = &test_compare_27;

    for(std::map<std::string, functionPointer>::iterator it =
            namesToFunctions.begin();
        it != namesToFunctions.end(); ++it) {
        std::string functionName = it->first;
        functionPointer func = it->second;

        try {
            bool passed = func();
            if(passed) {
                ++(summary.numPassed);
            } else {
                ++summary.numFailed;
                summary.failedFunctions.push_back(functionName);
            }
        } catch(const std::exception &e) {
            ++summary.numErrored;
            summary.erroredFunctions.push_back(functionName);
        }
    }

    return summary;
}

int main() {
    TestCasesSummary summary = runTestCases();

    const std::string outputSeparator = "-----------------------------";
    int numTestCases =
        (summary.numPassed + summary.numFailed + summary.numErrored);

    std::cout << "Ran " << numTestCases << " tests" << std::endl;

    std::cout << outputSeparator << std::endl;

    std::cout << "Number of tests passed    : " << summary.numPassed
              << std::endl;
    std::cout << "Number of tests failed    : " << summary.numFailed
              << std::endl;
    std::cout << "Number of tests errored   : " << summary.numErrored
              << std::endl;

    std::cout << outputSeparator << std::endl;

    if(summary.numPassed == numTestCases) {
        std::cout << "All test cases passed!" << std::endl;
    }

    if(summary.erroredFunctions.size() > 0) {
        std::cout << "First test case with compilation error: "
                  << summary.erroredFunctions.front() << std::endl;
    }

    if(summary.failedFunctions.size() > 0) {
        std::cout << "First test case which failed: "
                  << summary.failedFunctions.front() << std::endl;
    }

    std::cout << outputSeparator << std::endl;

    return 0;
}
