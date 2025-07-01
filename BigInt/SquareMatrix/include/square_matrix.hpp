#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP // NOLINT(clang-diagnostic-unused-macros)

#include "BigInt/Rational/include/rational.hpp"

#include <cstdint> // std::size_t
#include <vector>

namespace BigInt {

class SquareMatrix {
  public:
    explicit SquareMatrix(const std::vector<std::vector<Rational>> &input_data);

    auto operator[](std::size_t row) -> std::vector<Rational>;
    auto invert() -> SquareMatrix;

    static auto identity(std::size_t N) -> SquareMatrix;

  private:
    std::size_t length;
    std::vector<std::vector<Rational>> data;
};

} // namespace BigInt

#endif
