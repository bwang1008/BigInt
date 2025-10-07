#include "BigInt/Rational/include/rational.hpp"

namespace BigInt {

[[nodiscard, gnu::pure]] auto operator+(const Rational &left,
                                        const Rational &right) -> Rational {
    return Rational::add(left, right);
}

auto Rational::operator+=(const Rational &right) -> Rational & {
    const Rational result = Rational::add(*this, right);
    this->numerator = result.numerator;
    this->denominator = result.denominator;
    return *this;
}

[[nodiscard, gnu::pure]] auto operator-(const Rational &left,
                                        const Rational &right) -> Rational {
    return Rational::subtract(left, right);
}

auto Rational::operator-=(const Rational &right) -> Rational & {
    const Rational result = Rational::subtract(*this, right);
    this->numerator = result.numerator;
    this->denominator = result.denominator;
    return *this;
}

[[nodiscard, gnu::pure]] auto operator*(const Rational &left,
                                        const Rational &right) -> Rational {
    return Rational::multiply(left, right);
}

auto Rational::operator*=(const Rational &right) -> Rational & {
    const Rational result = Rational::multiply(*this, right);
    this->numerator = result.numerator;
    this->denominator = result.denominator;
    return *this;
}

[[nodiscard, gnu::pure]] auto operator/(const Rational &left,
                                        const Rational &right) -> Rational {
    return Rational::divide(left, right);
}

auto Rational::operator/=(const Rational &right) -> Rational & {
    const Rational result = Rational::divide(*this, right);
    this->numerator = result.numerator;
    this->denominator = result.denominator;
    return *this;
}

auto Rational::add(const Rational &left, const Rational &right) -> Rational {
    return Rational(left.numerator * right.denominator +
                        left.denominator * right.numerator,
                    left.denominator * right.denominator);
}

auto Rational::subtract(const Rational &left, const Rational &right)
    -> Rational {
    return Rational(left.numerator * right.denominator -
                        left.denominator * right.numerator,
                    left.denominator * right.denominator);
}

auto Rational::multiply(const Rational &left, const Rational &right)
    -> Rational {
    return Rational(left.numerator * right.numerator,
                    left.denominator * right.denominator);
}

auto Rational::divide(const Rational &left, const Rational &right) -> Rational {
    return Rational(left.numerator * right.denominator,
                    left.denominator * right.numerator);
}
} // namespace BigInt
