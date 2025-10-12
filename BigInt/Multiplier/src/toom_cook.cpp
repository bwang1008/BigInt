#include "BigInt/Multiplier/include/toom_cook.hpp"
#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Rational/include/rational.hpp"
#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include <cstddef>   // std::size_t
#include <stdexcept> // std::invalid_argument
#include <vector>

/**
 * Returns the n'th number used as an evaluation point for polynomials.
 *
 * @param n index of sequence to access
 * @return nth number of 0-indexed sequence [0, 1, -1, 2, -2, 3, -3, ...]
 */
[[nodiscard, gnu::const]] constexpr auto get_evaluation_point(unsigned int n)
    -> int;

constexpr auto get_evaluation_point(const unsigned int n) -> int {
    const int abs_value = static_cast<int>((n + 1) / 2);
    return (n % 2 == 0) ? abs_value : -abs_value;
}

/**
 * Split interval of [0, n) into k pieces of roughly the same size.
 *
 * For example, splitting n=8 into 3 pieces would return [3, 6, 8] because [0,
 * 3), [3, 6], and [6, 8) split the interval [0, 8] into 3 subsequences of
 * approximately the same size.
 *
 * @param vec n size of interval
 * @param k number of subsequences to split n into
 * @return indices of right-hand side of intervals of subsequences
 */
[[nodiscard, gnu::const]] auto get_split_right_indices(const std::size_t n,
                                                       const unsigned int k)
    -> std::vector<std::size_t>;

auto get_split_right_indices(const std::size_t n, const std::size_t k)
    -> std::vector<std::size_t> {
    std::vector<std::size_t> right_indices;
    for(std::size_t i = 1; i <= k; ++i) {
        const std::size_t numerator = n * i;
        const std::size_t additional = (i <= numerator % k) ? 1 : 0;
        right_indices.push_back(numerator / k + additional);
    }
    return right_indices;
}

namespace BigInt {

/**
 * Matrix of size (2k - 1) * (2k - 1), where each row represents the powers of
 * each evaluation point.
 *
 * @param k Initial size of polynomial for which we want to find 2k-1 evaluation
 * points
 * @return matrix, where matrix[0][0] = matrix[last][last] = 1, and the other
 * rows are the powers of the evaluation points
 */
[[nodiscard]] auto get_evaluation_matrix(const unsigned int k) -> SquareMatrix;

auto get_evaluation_matrix(const unsigned int k) -> SquareMatrix {
    std::vector<std::vector<Rational>> evaluation_data(
        2 * k - 1, std::vector<Rational>(2 * k - 1));
    evaluation_data[0][0] = Rational(1);
    evaluation_data[2 * k - 2][2 * k - 2] = Rational(1);

    for(std::size_t row = 1; row < 2 * k - 2; ++row) {
        const int evaluation_x =
            get_evaluation_point(static_cast<unsigned int>(row));
        evaluation_data[row][0] = Rational(1);
        for(std::size_t col = 1; col < 2 * k - 1; ++col) {
            evaluation_data[row][col] =
                evaluation_data[row][col - 1] * Rational(evaluation_x);
        }
    }

    return SquareMatrix(evaluation_data);
}

ToomCookMultiplier::ToomCookMultiplier(const unsigned int k_)
    : k{k_}, evaluation_matrix{SquareMatrix::identity(2 * k - 1)},
      interpolation_matrix{SquareMatrix(2 * k - 1)} {
    if(this->k <= 1) {
        throw std::invalid_argument(
            "Parameter to Toom-Cook algorithm must be at least 2");
    }

    this->evaluation_matrix = get_evaluation_matrix(this->k);
    this->interpolation_matrix = this->evaluation_matrix.inverse();
}

/**
 * Split the digits of n into k pieces, each roughly the same amount of digits.
 *
 * @param n BigInt whose digits we want to split
 * @param k number of pieces to split into
 * @return list of BigInts, the pieces of n to split into k parts. Ordered from
 * least significant to most significant
 */
[[nodiscard]] auto partition_bigint_digits(const BigInt &n,
                                           const unsigned int k)
    -> std::vector<BigInt>;

auto partition_bigint_digits(const BigInt &n, const unsigned int k)
    -> std::vector<BigInt> {}

auto ToomCookMultiplier::multiply_positive(const BigInt &left,
                                           const BigInt &right) -> BigInt {}

} // namespace BigInt
