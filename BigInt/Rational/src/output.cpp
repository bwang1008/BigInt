#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Rational/include/rational.hpp"

#include <ostream>
#include <sstream> // std::stringstream
#include <string>

namespace BigInt {

auto operator<<(std::ostream &out, const Rational &r) -> std::ostream & {
    out << r.numerator << "/" << r.denominator;
    return out;
}

auto Rational::str() const -> std::string {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

auto Rational::get_numerator() const -> BigInt { return this->numerator; }

auto Rational::get_denominator() const -> BigInt { return this->denominator; }

} // namespace BigInt
