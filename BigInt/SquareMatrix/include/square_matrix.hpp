#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP // NOLINT(clang-diagnostic-unused-macros)

#include "BigInt/Rational/include/rational.hpp"

#include <cstddef> // std::size_t
#include <vector>

namespace BigInt {

/**
 * Class that represents N x N matrices of Rational numbers.
 */
class SquareMatrix {
  public:
    /**
     * Constructor that creates a `N` x `N` matrix of 0s.
     *
     * @param N side length of matrix. If 0 is provided, then
     * std::invalid_argument will be thrown
     */
    explicit SquareMatrix(std::size_t N);
    /**
     * Constructor that creates a `N` x `N` matrix with values from
     * `input_data`.
     *
     * @param input_data 2D vector of Rational. If the number of rows does not
     * match the number of columns, then std::invalid_argument will be thrown
     */
    explicit SquareMatrix(const std::vector<std::vector<Rational>> &input_data);

    /**
     * Retrieve the value at the `row` row and `col` column of the matrix.
     *
     * @param row Row number to search for entry
     * @param col Column to search for in `row`
     * @return entry at matrix's `row` row, `col` column
     */
    [[nodiscard]] auto get(std::size_t row, std::size_t col) const -> Rational;
    /**
     * Multiplies the current SquareMatrix with `right`.
     *
     * @param right SquareMatrix that current SquareMatrix should multiply with
     * @return product of current SquareMatrix with `right`
     */
    [[nodiscard]] auto multiply(const SquareMatrix &right) const
        -> SquareMatrix;
    /**
     * Return the multiplicative inverse of the current SquareMatrix.
     *
     * If the current SquareMatrix is not invertible, then std::runtime_error
     * will be thrown.
     * @return Multiplicative inverse of current SquareMatrix
     */
    [[nodiscard]] auto inverse() const -> SquareMatrix;

    /**
     * Multiplies two SquareMatrices.
     *
     * @param left First SquareMatrix to be multiplied
     * @param right Second SquareMatrix to be multiplied with `left`. Both must
     * have the same number of rows. If not, then std::invalid_argument will be
     * thrown
     * @return product of `left` and `right`
     */
    friend auto operator*(const SquareMatrix &left, const SquareMatrix &right)
        -> SquareMatrix;
    /**
     * Returns boolean indicating if `left` has the same value as `right`.
     *
     * @param left SquareMatrix to be compared with `right`
     * @param right SquareMatrix to be compared with `left`
     * @return true if `left` has the same values as `right` for each row and
     * column, otherwise false
     */
    friend auto operator==(const SquareMatrix &left, const SquareMatrix &right)
        -> bool;
    /**
     * Returns boolean indicating if `left` has a different value from `right`.
     *
     * @param left SquareMatrix to be compared with `right`
     * @param right SquareMatrix to be compared with `left`
     * @return true if `left` has some different value than `right`, false if
     * they have the same values at each row and column.
     */
    friend auto operator!=(const SquareMatrix &left, const SquareMatrix &right)
        -> bool;

    /**
     * Creates the `N` x `N` identity matrix.
     *
     * Every entry is 0, except for the main diagonal, which has each entry as
     * value 1.
     * @param N number of rows of identity matrix
     * @return SquareMatrix that is the identity matrix of size `N` by `N`
     */
    static auto identity(std::size_t N) -> SquareMatrix;

  private:
    /// @brief number of rows (and also number of columns) of SquareMatrix
    std::size_t length;
    /// @brief 2D vector of size `N` rows of `N` columns of Rational numbers
    std::vector<std::vector<Rational>> data;

    /**
     * Finds the smallest row number, greater or equal to `current_row`, whose
     * `current_row` column is non-zero.
     *
     * Used in Gaussian elimination.
     * @param current_row row number to start searching from, and which
     * subsequent rows must be searched to find row where the `current_row`
     * column is non-zero
     * @return row number whose `current_row` column value is non-zero
     */
    [[nodiscard]] auto find_pivot(std::size_t current_row) const -> std::size_t;
};

} // namespace BigInt

#endif
