#include "BigInt/BigInt/include/big_int.hpp"

#include <ostream>
#include <string>

namespace BigInt {

class Rational {
  public:
    Rational();
    explicit Rational(int numerator_);
    explicit Rational(const BigInt &numerator_);
    Rational(int numerator_, int denominator_);
    Rational(const BigInt &numerator_, const BigInt &denominator);

    [[nodiscard]] auto get_numerator() const -> BigInt;
    [[nodiscard]] auto get_denominator() const -> BigInt;
    auto str() const -> std::string;

    friend auto operator<<(std::ostream &out, const Rational &r)
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

    static auto add(const Rational &left, const Rational &right) -> Rational;
    static auto subtract(const Rational &left, const Rational &right)
        -> Rational;
    static auto multiply(const Rational &left, const Rational &right)
        -> Rational;
    static auto divide(const Rational &left, const Rational &right) -> Rational;

  private:
    BigInt numerator;
    BigInt denominator;
};

} // namespace BigInt
