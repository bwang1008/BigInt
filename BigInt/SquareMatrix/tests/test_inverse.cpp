#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include <stdexcept> // std::runtime_error
#include <vector>

TEST_CASE("invert1", "[invert]") {
    const std::vector<std::vector<BigInt::Rational>> data(
        {{BigInt::Rational(3)}});
    const BigInt::SquareMatrix mat{data};

    const BigInt::SquareMatrix inv = mat.inverse();
    REQUIRE(inv.get(0, 0) == BigInt::Rational(1, 3));

    REQUIRE(mat * inv == BigInt::SquareMatrix::identity(1));
    REQUIRE(inv * mat == BigInt::SquareMatrix::identity(1));
}

TEST_CASE("invert2", "[invert]") {
    const std::vector<std::vector<BigInt::Rational>> data({
        {BigInt::Rational(3), BigInt::Rational(2)},
        {BigInt::Rational(7), BigInt::Rational(5)},
    });
    const BigInt::SquareMatrix mat{data};

    const BigInt::SquareMatrix inv = mat.inverse();
    REQUIRE(inv.get(0, 0) == BigInt::Rational(5));
    REQUIRE(inv.get(0, 1) == BigInt::Rational(-2));
    REQUIRE(inv.get(1, 0) == BigInt::Rational(-7));
    REQUIRE(inv.get(1, 1) == BigInt::Rational(3));

    REQUIRE(mat * inv == BigInt::SquareMatrix::identity(2));
    REQUIRE(inv * mat == BigInt::SquareMatrix::identity(2));
}

TEST_CASE("non-invertible", "[invert]") {
    const std::vector<std::vector<BigInt::Rational>> data({
        {BigInt::Rational(1), BigInt::Rational(2)},
        {BigInt::Rational(3), BigInt::Rational(6)},
    });
    const BigInt::SquareMatrix mat{data};
    REQUIRE_THROWS_MATCHES(
        mat.inverse(), std::runtime_error,
        Catch::Matchers::Message("Matrix is not invertible"));
}
