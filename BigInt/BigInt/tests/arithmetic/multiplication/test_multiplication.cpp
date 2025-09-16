#include <string> // std::to_string
#include <tuple>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "BigInt/BigInt/include/big_int.hpp"

auto multiplication_test_cases()
    -> std::vector<std::tuple<std::string, std::string, std::string>>;

auto multiplication_test_cases()
    -> std::vector<std::tuple<std::string, std::string, std::string>> {
    return {
        {"0", "12345678901234567890", "0"},
        {"12345678901234567890", "0", "0"},
        {"12345678901234567890", "98765432109876543210",
         "1219326311370217952237463801111263526900"},
        {"123", "-1", "-123"},
        {"-123", "1", "-123"},
        {"-123", "-1", "123"},
        {"98765432109876543210", "98765432109876543210",
         "9754610579850632525677488187778997104100"},
        {"314159265358979323846264338327950288419716939937510582097494459230"
         "78164062862089986280348253421170679",
         "27182818284590452353602874713526624977572470936999595749669676"
         "277240766303535945713821785251664274",
         "85397342226735670654635508695465744950348885357651149618796011"
         "30179228611157478389576250750003272865934781620706786730437354"
         "53603785848133094851462428844661315312664336578255202869537848"
         "950160622046"}};
}

TEST_CASE("Grade-school multiplication small", "[mul]") {
    auto i = GENERATE(range(0, 11));
    auto j = GENERATE(range(0, 11));

    const BigInt::BigInt x{i};
    const BigInt::BigInt y{j};
    const BigInt::BigInt result = BigInt::BigInt::multiply_grade_school(x, y);
    REQUIRE(result.str() == std::to_string(i * j));
}

TEST_CASE("Grade-school multiplication", "[mul]") {
    for(const auto &[a, b, c] : multiplication_test_cases()) {
        const BigInt::BigInt x{a};
        const BigInt::BigInt y{b};
        const BigInt::BigInt result =
            BigInt::BigInt::multiply_grade_school(x, y);
        const BigInt::BigInt expected{c};
        REQUIRE(result == expected);
    }
}

TEST_CASE("Karatsuba multiplication small", "[mul]") {
    auto i = GENERATE(range(0, 11));
    auto j = GENERATE(range(0, 11));

    const BigInt::BigInt x{i};
    const BigInt::BigInt y{j};
    const BigInt::BigInt result = BigInt::BigInt::multiply_karatsuba(x, y);
    REQUIRE(result.str() == std::to_string(i * j));
}

TEST_CASE("Karatsuba multiplication", "[mul]") {
    for(const auto &[a, b, c] : multiplication_test_cases()) {
        const BigInt::BigInt x{a};
        const BigInt::BigInt y{b};
        const BigInt::BigInt result = BigInt::BigInt::multiply_karatsuba(x, y);
        const BigInt::BigInt expected{c};
        REQUIRE(result == expected);
    }
}
