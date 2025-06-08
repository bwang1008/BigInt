#include "BigInt/BigInt/include/big_int.hpp"

#include <ostream>

namespace BigInt {

class Rational {
  public:
    Rational();
    explicit Rational(int numerator_);
    explicit Rational(const BigInt &numerator_);
    Rational(int numerator_, int denominator_);
    Rational(const BigInt &numerator_, const BigInt &denominator);

    friend auto operator<<(std::ostream &os, const Rational &r)
        -> std::ostream &;
    friend auto operator+(const Rational &left, const Rational &right)
        -> Rational;
    friend auto operator-(const Rational &left, const Rational &right)
        -> Rational;
    friend auto operator*(const Rational &left, const Rational &right)
        -> Rational;
    friend auto operator/(const Rational &left, const Rational &right)
        -> Rational;

    auto operator+=(const Rational &right) -> Rational &;
    auto operator-=(const Rational &right) -> Rational &;
    auto operator*=(const Rational &right) -> Rational &;
    auto operator/=(const Rational &right) -> Rational &;

    [[nodiscard]] auto get_numerator() const -> BigInt;
    [[nodiscard]] auto get_denominator() const -> BigInt;

  private:
    BigInt numerator;
    BigInt denominator;
};

} // namespace BigInt
