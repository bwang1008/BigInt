#include "BigInt/Rational/include/rational.hpp"
#include "BigInt/BigInt/include/big_int.hpp"

#include <ostream>

namespace BigInt {

auto operator<<(std::ostream &out, const Rational &num) -> std::ostream & {
    out << num.numerator << " / " << num.denominator;
    return out;
}

auto Rational::get_numerator() const -> BigInt { return this->numerator; }

auto Rational::get_denominator() const -> BigInt { return this->denominator; }

} // namespace BigInt
