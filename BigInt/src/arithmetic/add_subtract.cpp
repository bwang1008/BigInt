#include "BigInt/include/big_int.hpp"

#include <algorithm> // std::max
#include <vector>

namespace BigInt {

auto operator+(const BigInt &left, const BigInt &right) -> BigInt {
    if(left.is_zero()) {
        return right;
    }
    if(right.is_zero()) {
        return left;
    }

    if(left.is_positive()) {
        if(right.is_positive()) {
            return BigInt::half_add(left, right);
        }
        // 3 + (-5) => 3 - 5
        return left - (-right);
    }

    // left is negative
    if(right.is_positive()) {
        // (-3) + (5) => (5) - (3)
        return right - (-left);
    }

    // right is negative
    // (-3) + (-5) => -(3 + 5)
    return -((-left) + (-right));
}

auto operator-(const BigInt &left, const BigInt &right) -> BigInt {
    if(left.is_zero()) {
        return -right;
    }

    if(right.is_zero()) {
        return left;
    }

    if(left.is_positive()) {
        if(right.is_positive()) {
            if(left < right) {
                // 3 - 5 => -(5 - 3)
                return -(right - left);
            }
            // 5 - 3  OR  5 - 5
            return BigInt::half_subtract(left, right);
        }
        // right negative
        // 3 - (-5) => 3 + 5
        return left + (-right);
    }

    // left is negative
    if(right.is_positive()) {
        // -3 - (5) => -(3 + 5)
        return -((-left) + right);
    }

    // right is negative
    // -3 - (-5) => -3 + 5 => 5 - 3
    return ((-right) - (-left));
}

auto BigInt::half_add(const BigInt &left, const BigInt &right) -> BigInt {
    std::vector<int> summed_digits;

    int carry = 0;
    for(size_t i = 0; i < std::max(left.digits.size(), right.digits.size());
        ++i) {
        const int op1 = (i < left.digits.size()) ? left.digits[i] : 0;
        const int op2 = (i < right.digits.size()) ? right.digits[i] : 0;

        const int bucketSum = op1 + op2 + carry;
        carry = bucketSum / BigInt::bucket_mod;
        summed_digits.push_back(bucketSum % BigInt::bucket_mod);
    }

    summed_digits.push_back(carry);
    return BigInt(false, summed_digits);
}

auto BigInt::half_subtract(const BigInt &left, const BigInt &right) -> BigInt {
    // assume left >= right >= 0

    std::vector<int> subtracted_digits;
    bool borrow = false;

    for(size_t i = 0; i < std::max(left.digits.size(), right.digits.size());
        ++i) {
        int op1 = (i < left.digits.size()) ? left.digits[i] : 0;
        const int op2 = (i < right.digits.size()) ? right.digits[i] : 0;

        if(borrow) {
            --op1;
        }
        borrow = false;

        if(op1 < op2) {
            borrow = true;
            op1 += BigInt::bucket_mod;
        }

        subtracted_digits.push_back(op1 - op2);
    }

    return BigInt(false, subtracted_digits);
}

} // namespace BigInt