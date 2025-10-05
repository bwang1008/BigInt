#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("negative, negative multiplication", "[mul]") {
    const BigInt::BigInt x{-3};
    const BigInt::BigInt y{-5};
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "15");
}

TEST_CASE("negative, positive multiplication", "[mul]") {
    const BigInt::BigInt x{-3};
    const BigInt::BigInt y{5};
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "-15");
}

TEST_CASE("positive, negative multiplication", "[mul]") {
    const BigInt::BigInt x{3};
    const BigInt::BigInt y{-5};
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "-15");
}

TEST_CASE("positive, positive multiplication", "[mul]") {
    const BigInt::BigInt x{3};
    const BigInt::BigInt y{5};
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "15");
}

TEST_CASE("left zero multiplication", "[mul]") {
    const BigInt::BigInt x;
    const BigInt::BigInt y{5};
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "0");
}

TEST_CASE("left zero negative multiplication", "[mul]") {
    const BigInt::BigInt x;
    const BigInt::BigInt y{-5};
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "0");
}

TEST_CASE("right zero multiplication", "[mul]") {
    const BigInt::BigInt x{3};
    const BigInt::BigInt y;
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "0");
}

TEST_CASE("right zero negative multiplication", "[mul]") {
    const BigInt::BigInt x{-3};
    const BigInt::BigInt y;
    BigInt::GradeSchoolMultiplier multiplier;
    const BigInt::BigInt z = multiplier.multiply(x, y);
    REQUIRE(z.str() == "0");
}
