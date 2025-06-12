#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Rational/include/rational.hpp"

#include <stdexcept> // std::invalid_argument
#include <utility>   // std::pair

namespace BigInt {
auto reduce(const BigInt &numerator, const BigInt &denominator)
    -> std::pair<BigInt, BigInt> {
    if(denominator == BigInt()) {
        throw std::invalid_argument("Cannot divide by 0");
    }
    const bool signs_flipped = (denominator < BigInt());
    const BigInt g = BigInt::gcd(numerator, denominator);
    const BigInt numerator_reduced = numerator / g;
    const BigInt denominator_reduced = denominator / g;
    return std::pair<BigInt, BigInt>(
        signs_flipped ? -numerator_reduced : numerator_reduced,
        signs_flipped ? -denominator_reduced : denominator_reduced);
}

Rational::Rational() : Rational(0, 1) {}
Rational::Rational(const int numerator_) : Rational(numerator_, 1) {}
Rational::Rational(const BigInt &numerator_)
    : Rational(numerator_, BigInt(1)) {}
Rational::Rational(const int numerator_, const int denominator_)
    : Rational(BigInt(numerator_), BigInt(denominator_)) {}
Rational::Rational(const BigInt &numerator_, const BigInt &denominator_)
    : numerator(0), denominator(1) {
    const std::pair<BigInt, BigInt> reduced = reduce(numerator_, denominator_);
    this->numerator = reduced.first;
    this->denominator = reduced.second;
}

} // namespace BigInt
