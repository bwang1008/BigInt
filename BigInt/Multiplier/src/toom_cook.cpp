#include "BigInt/Multiplier/include/toom_cook.hpp"
#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp" // GradeSchoolMultiplier
#include "BigInt/Rational/include/rational.hpp"
#include "BigInt/SquareMatrix/include/square_matrix.hpp"

#include <algorithm> // std::max, std::min
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
    return (n % 2 == 1) ? abs_value : -abs_value;
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
            const Rational evaluation_matrix_value =
                (evaluation_index + 1 == num_evaluation_points &&
                 coefficient_index + 1 == coefficients.size())
                    ? Rational(1)
                    : this->evaluation_matrix.get(evaluation_index,
                                                  coefficient_index);
            const Rational subproduct =
                evaluation_matrix_value *
                Rational(coefficients[coefficient_index]);
            evaluations[evaluation_index] += subproduct;
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
    std::vector<BigInt> products(left.size());
    GradeSchoolMultiplier grade_school_multiplier;
    for(std::size_t i = 0; i < left.size(); ++i) {
        // recursive step; multiplicands could be negative
        products[i] = multiply(left[i], right[i]);
    }

    return products;
}

auto ToomCookMultiplier::interpolate(const std::vector<BigInt> &y_values) const
    -> std::vector<BigInt> {
    std::vector<BigInt> results(2 * this->k - 1, BigInt());
    for(std::size_t i = 0; i < 2 * this->k - 1; ++i) {
        Rational total;
        for(std::size_t j = 0; j < 2 * this->k - 1; ++j) {
            total +=
                this->interpolation_matrix.get(i, j) * Rational(y_values[j]);
        }
        results[i] = total.get_numerator();
    }

    return results;
}

auto ToomCookMultiplier::recompose(const std::vector<BigInt> &r_coefficients,
                                   const std::size_t subwidth) -> BigInt {
    std::size_t max_coefficient_size = 1;
    for(const BigInt &r_coefficient : r_coefficients) {
        max_coefficient_size =
            std::max(r_coefficient.digits.size(), max_coefficient_size);
    }
    const std::size_t product_num_digits =
        subwidth * (r_coefficients.size() - 1) + max_coefficient_size + 2;

    std::vector<unsigned int> product_digits(product_num_digits);
    unsigned int carry = 0;

    for(std::size_t i = 0; i < r_coefficients.size(); ++i) {
        const BigInt r_coefficient = r_coefficients[i];
        for(std::size_t digit_index = 0;
            digit_index < r_coefficient.digits.size(); ++digit_index) {
            const unsigned int sum =
                product_digits[subwidth * i + digit_index] +
                r_coefficient.digits[digit_index] + carry;
            product_digits[subwidth * i + digit_index] =
                sum % BigInt::bucket_mod;
            carry = sum / BigInt::bucket_mod;
        }
        if(carry > 0) {
            product_digits[subwidth * i + r_coefficient.digits.size()] = 1;
            carry = 0;
        }
    }

    return BigInt(false, product_digits);
}

auto ToomCookMultiplier::multiply_positive(const BigInt &left,
                                           const BigInt &right) -> BigInt {
    // splitting
    const auto subwidth =
        static_cast<unsigned int>(find_common_subwidth(left, right, this->k));

    // determine whether to use another multiplication method more suited for
    // smaller values
    const unsigned int largest_evaluation_point = this->k - 1;
    // if splitting a 1-bit number, results in constant polynomial;
    // i.e. the evaluation point isn't even used. Use base case for this.
    // Otherwise, if evaluation points are greater or equal to multiplying
    // out polynomial directly, then use simpler multiplication method
    const bool switch_to_base_case =
        (std::max(left.digits.size(), right.digits.size()) <= 1) ||
        ((1U << (BigInt::num_bits_per_bucket * subwidth)) <=
         largest_evaluation_point);
    if(switch_to_base_case) {
        GradeSchoolMultiplier grade_school_multiplier;
        return grade_school_multiplier.multiply(left, right);
    }

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

    // interpolation
    const std::vector<BigInt> r_coefficients = interpolate(r_values);

    // recompose
    BigInt answer = recompose(r_coefficients, subwidth);
    return answer;
}

} // namespace BigInt
