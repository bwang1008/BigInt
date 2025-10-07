#include "BigInt/Rational/include/rational.hpp"
#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include <stdexcept> // std::invalid_argument

TEST_CASE("multiply", "[multiply]") {
    const std::vector<std::vector<BigInt::Rational>> data1(
        {{BigInt::Rational(3), BigInt::Rational(7)},
         {BigInt::Rational(-2), BigInt::Rational(1)}});
    const std::vector<std::vector<BigInt::Rational>> data2(
        {{BigInt::Rational(2), BigInt::Rational(9)},
         {BigInt::Rational(5), BigInt::Rational(6)}});

    const BigInt::SquareMatrix mat1{data1};
    const BigInt::SquareMatrix mat2{data2};
    const BigInt::SquareMatrix mat3 = mat1 * mat2;

    REQUIRE(mat3.get(0, 0) == BigInt::Rational(41));
    REQUIRE(mat3.get(0, 1) == BigInt::Rational(69));
    REQUIRE(mat3.get(1, 0) == BigInt::Rational(1));
    REQUIRE(mat3.get(1, 1) == BigInt::Rational(-12));
}

TEST_CASE("multiply invalid sizes", "[multiply]") {
    const std::vector<std::vector<BigInt::Rational>> data1(
        {{BigInt::Rational(3), BigInt::Rational(7)},
         {BigInt::Rational(-2), BigInt::Rational(1)}});
    const std::vector<std::vector<BigInt::Rational>> data2(
        {{BigInt::Rational(2)}});

    const BigInt::SquareMatrix mat1{data1};
    const BigInt::SquareMatrix mat2{data2};
    REQUIRE_THROWS_MATCHES(
        mat1 * mat2, std::invalid_argument,
        Catch::Matchers::Message(
            "Matrices of two different lengths cannot be multiplied together"));
}
