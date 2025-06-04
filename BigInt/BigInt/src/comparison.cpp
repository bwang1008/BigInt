#include "BigInt/BigInt/include/big_int.hpp"

namespace BigInt {

auto BigInt::compare(const BigInt &left, const BigInt &right) -> int {
    if(left.is_negative()) {
        if(!right.is_negative()) {
            return -1;
        }

        return compare(-right, -left);
    }

    if(left.is_zero()) {
        if(right.is_negative()) {
            return 1;
        }
        if(right.is_zero()) {
            return 0;
        }
        return -1;
    }

    // left is positive
    if(!right.is_positive()) {
        return 1;
    }

    // right is positive
    if(left.digits.size() < right.digits.size()) {
        return -1;
    }
    if(left.digits.size() > right.digits.size()) {
        return 1;
    }

    // compare from most significant digits down
    auto it1 = left.digits.crbegin();
    auto it2 = right.digits.crbegin();

    while(it1 != left.digits.crend() && it2 != right.digits.crend()) {
        const int valLeft = *it1;
        const int valRight = *it2;

        if(valLeft < valRight) {
            return -1;
        }
        if(valLeft > valRight) {
            return 1;
        }

        ++it1;
        ++it2;
    }

    return 0;
}

[[nodiscard]] [[gnu::pure]] auto BigInt::is_zero() const -> bool {
    return this->digits.size() == 1 && this->digits[0] == 0;
}

[[nodiscard]] [[gnu::pure]] auto BigInt::is_positive() const -> bool {
    return !this->is_zero() && !this->negative;
}

[[nodiscard]] [[gnu::pure]] auto BigInt::is_negative() const -> bool {
    return !this->is_zero() && this->negative;
}

auto operator==(const BigInt &left, const BigInt &right) -> bool {
    return BigInt::compare(left, right) == 0;
}

auto operator!=(const BigInt &left, const BigInt &right) -> bool {
    return !(left == right);
}

auto operator<(const BigInt &left, const BigInt &right) -> bool {
    return BigInt::compare(left, right) < 0;
}

auto operator>(const BigInt &left, const BigInt &right) -> bool {
    return BigInt::compare(left, right) > 0;
}

auto operator<=(const BigInt &left, const BigInt &right) -> bool {
    return BigInt::compare(left, right) <= 0;
}

auto operator>=(const BigInt &left, const BigInt &right) -> bool {
    return BigInt::compare(left, right) >= 0;
}

} // namespace BigInt
