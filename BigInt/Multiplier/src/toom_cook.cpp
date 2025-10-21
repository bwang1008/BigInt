#include "BigInt/Multiplier/include/toom_cook.hpp"
#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp" // GradeSchoolMultiplier
#include "BigInt/Rational/include/rational.hpp"
#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include <algorithm> // std::max
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

/**
 * Matrix of size (2k - 1) * (2k - 1), where each row represents the powers of
 * each evaluation point.
 *
 * @param k Initial size of polynomial for which we want to find 2k-1 evaluation
 * points
 * @return matrix, where matrix[0][0] = matrix[last][last] = 1, and the other
 * rows are the powers of the evaluation points
 */
[[nodiscard]] auto get_evaluation_matrix(unsigned int k) -> SquareMatrix;

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

auto ToomCookMultiplier::partition_bigint_digits(const BigInt &n,
                                                 const unsigned int k,
                                                 const unsigned int subwidth)
    -> std::vector<BigInt> {
    std::vector<BigInt> sub_bigint;
    for(unsigned int i = 0; i < k; ++i) {
        const std::size_t candidate_left_index = subwidth * i;
        const std::size_t candidate_right_index = subwidth * (1 + i);
        const std::vector<unsigned int>::difference_type left_index =
            (candidate_left_index >= n.digits.size())
                ? static_cast<std::vector<unsigned int>::difference_type>(
                      n.digits.size())
                : static_cast<std::vector<unsigned int>::difference_type>(
                      candidate_left_index);
        const std::vector<unsigned int>::difference_type right_index =
            (candidate_right_index >= n.digits.size())
                ? static_cast<std::vector<unsigned int>::difference_type>(
                      n.digits.size())
                : static_cast<std::vector<unsigned int>::difference_type>(
                      candidate_right_index);
        const std::vector<unsigned int> subdigits(
            n.digits.begin() + left_index, n.digits.begin() + right_index);
        sub_bigint.push_back(BigInt(false, subdigits));
    }
    return sub_bigint;
}

auto ToomCookMultiplier::find_common_subwidth(const BigInt &left,
                                              const BigInt &right,
                                              const unsigned int k)
    -> std::size_t {
    const std::size_t candidate1 = (left.digits.size() - 1) / k;
    const std::size_t candidate2 = (right.digits.size() - 1) / k;
    return std::max(candidate1, candidate2) + 1;
}

auto ToomCookMultiplier::evaluate_polynomial(
    const std::vector<BigInt> &coefficients) const -> std::vector<BigInt> {
    const std::size_t num_evaluation_points = 2 * this->k - 1;
    std::vector<Rational> evaluations(num_evaluation_points);
    for(std::size_t evaluation_index = 0;
        evaluation_index < num_evaluation_points; ++evaluation_index) {
        for(std::size_t coefficient_index = 0;
            coefficient_index < coefficients.size(); ++coefficient_index) {
            const Rational subproduct =
                this->evaluation_matrix.get(evaluation_index,
                                            coefficient_index) *
                Rational(coefficients[coefficient_index]);
            evaluations[coefficient_index] += subproduct;
        }
    }

    std::vector<BigInt> evaluations_integral(evaluations.size());
    for(std::size_t i = 0; i < evaluations.size(); ++i) {
        evaluations_integral[i] = evaluations[i].get_numerator();
    }

    return evaluations_integral;
}

auto ToomCookMultiplier::pointwise_multiplication(
    const std::vector<BigInt> &left, const std::vector<BigInt> &right)
    -> std::vector<BigInt> {
    // for now, don't recurse for ease of debugging
    std::vector<BigInt> products(left.size());
    GradeSchoolMultiplier grade_school_multiplier;
    for(std::size_t i = 0; i < left.size(); ++i) {
        products[i] = grade_school_multiplier.multiply(left[i], right[i]);
    }

    return products;
}

auto ToomCookMultiplier::multiply_positive(const BigInt &left,
                                           const BigInt &right) -> BigInt {
    // splitting
    const auto subwidth =
        static_cast<unsigned int>(find_common_subwidth(left, right, this->k));
    const std::vector<BigInt> left_split =
        partition_bigint_digits(left, this->k, subwidth);
    const std::vector<BigInt> right_split =
        partition_bigint_digits(right, this->k, subwidth);

    // evaluation
    const std::vector<BigInt> p_values = evaluate_polynomial(left_split);
    const std::vector<BigInt> q_values = evaluate_polynomial(right_split);

    // pointwise multiplication / recursive step
    const std::vector<BigInt> r_values =
        pointwise_multiplication(p_values, q_values);
}

} // namespace BigInt
