#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <catch2/catch_test_macros.hpp>

#include <vector>

TEST_CASE("equals", "[comparison]") {
    const std::vector<std::vector<BigInt::Rational>> data1({
        {BigInt::Rational(3), BigInt::Rational(2)},
        {BigInt::Rational(7), BigInt::Rational(5)},
    });
    const std::vector<std::vector<BigInt::Rational>> data2({
        {BigInt::Rational(3), BigInt::Rational(2)},
        {BigInt::Rational(7), BigInt::Rational(5)},
    });
    const std::vector<std::vector<BigInt::Rational>> data3({
        {BigInt::Rational(-3), BigInt::Rational(-2)},
        {BigInt::Rational(-7), BigInt::Rational(-5)},
    });
    const BigInt::SquareMatrix mat1{data1};
    const BigInt::SquareMatrix mat2{data2};
    const BigInt::SquareMatrix mat3{data3};

    REQUIRE(mat1 == mat2);
    REQUIRE_FALSE(mat1 != mat2);
    REQUIRE(mat1 != mat3);
    REQUIRE_FALSE(mat1 == mat3);
}
