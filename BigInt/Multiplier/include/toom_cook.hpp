#ifndef TOOM_COOK_HPP
#define TOOM_COOK_HPP // NOLINT(clang-diagnostic-unused-macros)

#include "BigInt/BigInt/include/big_int.hpp"             // BigInt::BigInt
#include "BigInt/Multiplier/include/multiplier.hpp"      // BigInt::Multiplier
#include "BigInt/SquareMatrix/include/square_matrix.hpp" // BigInt::SquareMatrix

namespace BigInt {

/**
 * Multiplier class that multiplies two BigInts using Toom-Cook's algorithm.
 *
 * See https://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplication
 */
class ToomCookMultiplier final : public Multiplier {
  public:
    /**
     * Constructor that takes in a single positive integer.
     *
     * Toom-Cook's algorithm is parameterized by a positive integer, independent
     * of the sizes of the two input. This must be at least 2.
     * @param k parameter of Toom-Cook's algorithm
     */
    explicit ToomCookMultiplier(unsigned int k_);

  protected:
    /**
     * Multiplies two positive BigInts using Toom-Cook's algorithm.
     *
     * @param left First BigInt to be multiplied with `right`. Must be positive.
     * @param right Second BigInt to be multiplied with `left`. Must be
     * positive.
     * @return product of `left` and `right`
     */
    [[nodiscard]] BigInt
    multiply_positive( // NOLINT(modernize-use-trailing-return-type)
        const BigInt &left, const BigInt &right) override;

  private:
    /// @brief parameter to Toom-Cook's algorithm that determines how much to
    /// split inputs by
    unsigned int k;
    /// @brief matrix to evaluate polynomial at several points
    SquareMatrix evaluation_matrix;
    /// @brief inverse matrix of evaluation matrix to convert points to
    /// coefficients
    SquareMatrix interpolation_matrix;

    /**
     * Split the digits of `n` into `k` pieces, each of `subwidth` digits.
     *
     * Starts with least-significant digits of `n`, `subwidth` digits at a time.
     * If more digits are requested than exist in `n`, than is it padded with
     * 0s.
     *
     * @param n BigInt whose digits we want to split
     * @param k number of pieces to split into
     * @param subwidth number of digits of each piece, subject to padding by 0
     * @return list of BigInts, the pieces of `n` to split into `k` parts.
     * Ordered from least significant to most significant
     */
    [[nodiscard]] static auto partition_bigint_digits(const BigInt &n,
                                                      unsigned int k,
                                                      unsigned int subwidth)
        -> std::vector<BigInt>;

    /**
     * Find a common subwidth to split both inputs by.
     *
     * Refer to
     * https://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplication#Splitting
     *
     * @param left First BigInt to be multiplied with `right`
     * @param right Second BigInt to be multiplied with `left`
     * @param k number of pieces to split into
     * @return integer representing number of digits each of the `k` pieces of
     * `left` and `right` should have
     */
    [[nodiscard, gnu::pure]] static auto
    find_common_subwidth(const BigInt &left, const BigInt &right,
                         unsigned int k) -> std::size_t;
};

} // namespace BigInt

#endif
