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
    explicit ToomCookMultiplier(const unsigned int k_);

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
};

} // namespace BigInt

#endif
