#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP // NOLINT(clang-diagnostic-unused-macros)

#include "BigInt/Rational/include/rational.hpp"

#include <cstdint> // std::size_t
#include <vector>

namespace BigInt {

class SquareMatrix {
  public:
    explicit SquareMatrix(std::size_t N);
    explicit SquareMatrix(const std::vector<std::vector<Rational>> &input_data);

    [[nodiscard]] auto get(std::size_t row, std::size_t col) const -> Rational;
    [[nodiscard]] auto multiply(const SquareMatrix &right) const
        -> SquareMatrix;
    [[nodiscard]] auto invert() const -> SquareMatrix;

    friend auto operator*(const SquareMatrix &left, const SquareMatrix &right)
        -> SquareMatrix;

    static auto identity(std::size_t N) -> SquareMatrix;

  private:
    std::size_t length;
    std::vector<std::vector<Rational>> data;

    [[nodiscard]] auto find_pivot(std::size_t current_row) const -> std::size_t;
};

} // namespace BigInt

#endif
