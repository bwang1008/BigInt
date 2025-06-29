#include "BigInt/Rational/include/rational.hpp"

namespace BigInt {

auto operator<(const Rational &r1, const Rational &r2) -> bool {
    return r1.numerator * r2.denominator < r2.numerator * r1.denominator;
}

auto operator<=(const Rational &r1, const Rational &r2) -> bool {
    return !(r2 < r1);
}

auto operator>(const Rational &r1, const Rational &r2) -> bool {
    return r2 < r1;
}

auto operator>=(const Rational &r1, const Rational &r2) -> bool {
    return !(r1 < r2);
}

auto operator==(const Rational &r1, const Rational &r2) -> bool {
    return r1.numerator == r2.numerator && r1.denominator == r2.denominator;
}

auto operator!=(const Rational &r1, const Rational &r2) -> bool {
    return !(r1 == r2);
}

} // namespace BigInt
