#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include "BigInt/Rational/include/rational.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include <stdexcept> // std::invalid_argument
#include <vector>

TEST_CASE("zero", "[constructor]") {
    const BigInt::SquareMatrix mat(2);
    REQUIRE(mat.get(0, 0) == BigInt::Rational());
    REQUIRE(mat.get(0, 1) == BigInt::Rational());
    REQUIRE(mat.get(1, 0) == BigInt::Rational());
    REQUIRE(mat.get(1, 1) == BigInt::Rational());
}

TEST_CASE("custom data", "[constructor]") {
    const std::vector<std::vector<BigInt::Rational>> data({
        {BigInt::Rational(3, 5), BigInt::Rational(7, 1)},
        {BigInt::Rational(-2, 9), BigInt::Rational(0)},
    });
    const BigInt::SquareMatrix mat{data};
    REQUIRE(mat.get(0, 0) == BigInt::Rational(3, 5));
    REQUIRE(mat.get(0, 1) == BigInt::Rational(7, 1));
    REQUIRE(mat.get(1, 0) == BigInt::Rational(-2, 9));
    REQUIRE(mat.get(1, 1) == BigInt::Rational());
}

TEST_CASE("Constructor fails on size 0", "[constructor]") {
    REQUIRE_THROWS_MATCHES(BigInt::SquareMatrix(0), std::invalid_argument,
                           Catch::Matchers::Message("N must be positive"));
}

TEST_CASE("Constructor fails on size 0 for custom data", "[constructor]") {
    const std::vector<std::vector<BigInt::Rational>> data;
    REQUIRE_THROWS_MATCHES(BigInt::SquareMatrix(data), std::invalid_argument,
                           Catch::Matchers::Message("N must be positive"));
}

TEST_CASE("Constructor fails on non-square custom data", "[constructor]") {
    const std::vector<std::vector<BigInt::Rational>> data(
        {{BigInt::Rational(3, 5)}, {BigInt::Rational(-2, 9)}});
    REQUIRE_THROWS_MATCHES(
        BigInt::SquareMatrix(data), std::invalid_argument,
        Catch::Matchers::Message("input_data must be square"));
}

TEST_CASE("identity", "[identity]") {
    const BigInt::SquareMatrix mat = BigInt::SquareMatrix::identity(2);
    REQUIRE(mat.get(0, 0) == BigInt::Rational(1));
    REQUIRE(mat.get(0, 1) == BigInt::Rational());
    REQUIRE(mat.get(1, 0) == BigInt::Rational());
    REQUIRE(mat.get(1, 1) == BigInt::Rational(1));
}
