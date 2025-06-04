#include <sstream> // std::stringstream
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/BigInt/include/big_int.hpp"

TEST_CASE("Check output representation", "[output]") {
    const BigInt::BigInt x{"123"};
    std::stringstream ss;
    ss << x;
    const std::string printed_representation = ss.str();
    REQUIRE(printed_representation == "123");
}

TEST_CASE("Check output string", "[output]") {
    const BigInt::BigInt x{"123"};
    const std::string str_representation = x.str();
    REQUIRE(str_representation == "123");
}
