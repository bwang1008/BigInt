#include "BigInt/BigInt/include/big_int.hpp"

#include <stdexcept> // std::invalid_argument
#include <utility>   // std::pair
#include <vector>    // std::vector

namespace BigInt {

auto BigInt::quotient_and_remainder_grade_school(const BigInt &left,
                                                 const BigInt &right)
    -> std::pair<BigInt, BigInt> {
    if(right.is_zero()) {
        throw std::invalid_argument("Cannot divide by 0");
    }

    BigInt minuend(false, left.digits);
    std::vector<BigInt> subtrahends{BigInt(false, right.digits)};
    std::vector<BigInt> bases{BigInt(1)};
    BigInt next(0);
    while((next = subtrahends.back() * BigInt(2)) <= minuend) {
        subtrahends.push_back(next);
        bases.push_back(bases.back() * BigInt(2));
    }

    BigInt total(0);
    while(!subtrahends.empty()) {
        const BigInt subtrahend = subtrahends.back();
        subtrahends.pop_back();
        const BigInt base = bases.back();
        bases.pop_back();
        if(subtrahend <= minuend) {
            total += base;
            minuend -= subtrahend;
        }
    }

    const BigInt quotient(left.negative ^ right.negative, total.digits);
    const BigInt remainder(left.negative, minuend.digits);
    return std::pair<BigInt, BigInt>(quotient, remainder);
}

auto BigInt::divide_grade_school(const BigInt &left, const BigInt &right)
    -> BigInt {
    return quotient_and_remainder_grade_school(left, right).first;
}

auto BigInt::remainder_grade_school(const BigInt &left, const BigInt &right)
    -> BigInt {
    return quotient_and_remainder_grade_school(left, right).second;
}

} // namespace BigInt
