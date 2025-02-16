#include "big_int.hpp"

#include <algorithm> // std::max
#include <cstddef>   // std::size_t
#include <cstdint>   // int64_t
#include <iostream>  // std::cout, std::endl
#include <iterator>  // std::advance
#include <ostream>
#include <sstream> // std::stringstream
#include <string>  // std::stoi, std::to_string
#include <utility> // std::move
#include <vector>

BigInt::BigInt(const std::string &num) {
    if(num.empty()) {
        this->negative = false;
        this->digits.push_back(0);
        return;
    }

    this->negative = (num[0] == '-');
    const std::size_t digit_start = (this->negative ? 1 : 0);

    std::size_t chunk_end = num.size();
    while(chunk_end != digit_start) {
        const std::size_t chunk_start =
            (chunk_end < digit_start + BigInt::digits_per_bucket)
                ? digit_start
                : chunk_end - BigInt::digits_per_bucket;
        this->digits.push_back(
            std::stoi(num.substr(chunk_start, chunk_end - chunk_start)));
        chunk_end = chunk_start;
    }

    normalize_digits();
}

BigInt::BigInt(const int64_t num) : BigInt(std::to_string(num)) {}

BigInt::BigInt() : negative(false), digits{0} {}

auto BigInt::operator-() const -> BigInt {
    if(is_zero()) {
        return BigInt();
    }

    BigInt clone = this->clone();
    clone.negative = !clone.negative;

    return clone;
}

auto BigInt::clone() const -> BigInt {
    return BigInt(this->negative, this->digits);
}

auto BigInt::str() const -> std::string {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

auto operator<<(std::ostream &out, const BigInt &integer) -> std::ostream & {
    if(integer.negative) {
        out << "-";
    }

    for(auto it = integer.digits.crbegin(); it != integer.digits.crend();
        ++it) {
        const int bucket = *it;
        const std::size_t size = std::to_string(bucket).size();

        // pad with 0 so 0 -> "000000000" if not most significant
        if(it != integer.digits.crbegin()) {
            for(size_t i = size; i < BigInt::digits_per_bucket; ++i) {
                out << "0";
            }
        }

        out << bucket;
    }

    return out;
}

auto operator"" _b(const char *s) -> BigInt { return BigInt(s); }

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

auto operator*(const BigInt &left, const BigInt &right) -> BigInt {
    // return BigInt::multiplyNaive(left, right);
    return BigInt::multiply_karatsuba(left, right);
}

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

auto BigInt::print_internal() const -> void {
    std::cout << "Is negative? " << this->negative << std::endl;
    std::cout << "digits list: ";
    for(const int i : this->digits) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

BigInt::BigInt(bool negative_, std::vector<int> digits_) {
    this->negative = negative_;
    this->digits = std::move(digits_);

    this->normalize_digits();
}

auto BigInt::normalize_digits() -> void {
    // remove leading 0's
    while(!this->digits.empty() && this->digits.back() == 0) {
        this->digits.pop_back();
    }

    // if no digits, initiailize with one 0
    if(this->digits.empty()) {
        this->digits.push_back(0);
    }

    // turn -0 to 0
    if(this->digits.size() == 1 && this->digits[0] == 0) {
        this->negative = false;
    }
}

auto BigInt::is_zero() const -> bool {
    return this->digits.size() == 1 && this->digits[0] == 0;
}

auto BigInt::is_positive() const -> bool {
    return !this->is_zero() && !this->negative;
}

auto BigInt::is_negative() const -> bool {
    return !this->is_zero() && this->negative;
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

auto BigInt::multiply_grade_school(const BigInt &left, const BigInt &right)
    -> BigInt {
    if(left.is_zero() || right.is_zero()) {
        return BigInt();
    }

    std::vector<int64_t> product(left.digits.size() + right.digits.size() + 2);

    for(size_t i = 0; i < left.digits.size(); ++i) {
        for(size_t j = 0; j < right.digits.size(); ++j) {
            const int64_t val1 = left.digits[i];
            const int64_t val2 = right.digits[j];
            const int64_t prod = val1 * val2;

            product[i + j] += (prod % BigInt::bucket_mod);
            product[i + j + 1] += (prod / BigInt::bucket_mod);

            // resolve carries
            product[i + j + 1] += (product[i + j] / BigInt::bucket_mod);
            product[i + j] %= BigInt::bucket_mod;
        }
    }

    for(size_t i = 0; i + 1 < product.size(); ++i) {
        product[i + 1] += (product[i] / BigInt::bucket_mod);
        product[i] %= BigInt::bucket_mod;
    }

    std::vector<int> digits(product.size());
    for(size_t i = 0; i < product.size(); ++i) {
        digits[i] = static_cast<int>(product[i]);
    }

    return BigInt(left.negative ^ right.negative, digits);
}

auto BigInt::multiply_karatsuba(const BigInt &left, const BigInt &right)
    -> BigInt {
    if(left.is_zero() || right.is_zero()) {
        return BigInt();
    }

    // convert both to the same lengths
    BigInt smaller = BigInt(false, left.digits);
    BigInt bigger = BigInt(false, right.digits);

    if(smaller.digits.size() > bigger.digits.size()) {
        BigInt temp = smaller;
        smaller = bigger;
        bigger = temp;
    }

    while(smaller.digits.size() < bigger.digits.size()) {
        smaller.digits.push_back(0);
    }

    BigInt product = BigInt::multiply_karatsuba_helper(smaller, bigger);
    product.negative = left.negative ^ right.negative;

    return product;
}

auto BigInt::multiply_karatsuba_helper(const BigInt &left, const BigInt &right)
    -> BigInt {
    const std::size_t size = left.digits.size();
    if(size == 1) {
        return BigInt::multiply_grade_school(left, right);
    }

    // split both left and right
    const std::size_t split_point = size / 2;

    auto left_mid = left.digits.begin();
    std::advance(left_mid, split_point);
    auto right_mid = right.digits.begin();
    std::advance(right_mid, split_point);

    const BigInt a(false, std::vector<int>(left_mid, left.digits.end()));
    const BigInt b(false, std::vector<int>(left.digits.begin(), left_mid));
    const BigInt c(false, std::vector<int>(right_mid, right.digits.end()));
    const BigInt d(false, std::vector<int>(right.digits.begin(), right_mid));

    const BigInt a_plus_b = a + b;
    const BigInt c_plus_d = c + d;

    const BigInt h = BigInt::multiply_karatsuba_helper(a_plus_b, c_plus_d);
    const BigInt f = BigInt::multiply_karatsuba_helper(a, c);
    const BigInt g = BigInt::multiply_karatsuba_helper(b, d);

    const BigInt k = h - f - g;

    std::vector<int64_t> product(2 * size + 2);

    // f is most significant, k is middle, g is least significant
    for(std::size_t i = 0; i < f.digits.size(); ++i) {
        product[2 * (size / 2) + i] += f.digits[i];
    }
    for(std::size_t i = 0; i < k.digits.size(); ++i) {
        product[(size / 2) + i] += k.digits[i];
    }
    for(std::size_t i = 0; i < g.digits.size(); ++i) {
        product[i] += g.digits[i];
    }

    // do carry-overs
    for(std::size_t i = 0; i + 1 < product.size(); ++i) {
        product[i + 1] += (product[i] / BigInt::bucket_mod);
        product[i] %= BigInt::bucket_mod;
    }

    // convert to ints
    std::vector<int> digits(product.size());
    for(std::size_t i = 0; i < product.size(); ++i) {
        digits[i] = static_cast<int>(product[i]);
    }

    return BigInt(false, digits);
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
