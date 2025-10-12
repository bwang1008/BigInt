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

namespace BigInt {

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

} // namespace BigInt
