#include "big_int.hpp"

#include <algorithm> // std::max
#include <cstdint>   // int64_t
#include <iostream>
#include <ostream>
#include <sstream>
#include <string> // std::stoi, std::string, std::to_string
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
            (chunk_end < digit_start + BigInt::digitsPerBucket)
                ? digit_start
                : chunk_end - BigInt::digitsPerBucket;
        this->digits.push_back(
            std::stoi(num.substr(chunk_start, chunk_end - chunk_start)));
        chunk_end = chunk_start;
    }

    normalizeDigits();
}

BigInt::BigInt(const int64_t num) : BigInt(std::to_string(num)) {}

auto BigInt::operator-() const -> BigInt {
    if(!isZero()) {
        BigInt clone = this->clone();
        clone.negative = !clone.negative;

        return clone;
    }

    return BigInt("0");
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
        int bucket = *it;
        size_t size = std::to_string(bucket).size();

        // pad with 0 so 0 -> "000000000" if not most significant
        if(it != integer.digits.crbegin()) {
            for(size_t i = 0; i < BigInt::digitsPerBucket - size; ++i) {
                out << "0";
            }
        }

        out << bucket;
    }

    return out;
}

auto operator"" _b(const char *s) -> BigInt { return BigInt(s); }

auto operator+(const BigInt &left, const BigInt &right) -> BigInt {
    if(left.isZero()) {
        return right.clone();
    }
    if(right.isZero()) {
        return left.clone();
    }

    if(left.isPos()) {
        if(right.isPos()) {
            return BigInt::halfAdd(left, right);
        }
        // 3 + (-5) => 3 - 5
        return left - (-right);
    }

    // left is negative
    if(right.isPos()) {
        // (-3) + (5) => (5) - (3)
        return right - (-left);
    }

    // right is negative
    // (-3) + (-5) => -(3 + 5)
    return -((-left) + (-right));
}

auto operator-(const BigInt &left, const BigInt &right) -> BigInt {
    if(left.isZero()) {
        return -right;
    }

    if(right.isZero()) {
        return left.clone();
    }

    if(left.isPos()) {
        if(right.isPos()) {
            if(left < right) {
                // 3 - 5 => -(5 - 3)
                return -(right - left);
            }
            // 5 - 3  OR  5 - 5
            return BigInt::halfSubtract(left, right);
        }
        // right negative
        // 3 - (-5) => 3 + 5
        // 5 - (-3) => 5 + 3
        // 5 - (-5) => 5 + 5
        return left + (-right);
    }

    // left is negative
    if(right.isPos()) {
        // -3 - (5) => -(3 + 5)
        return -((-left) + right);
    }

    // right is negative
    if(left < right) {
        // -5 - (-3) => -5 + 3 => 3 - 5
        return ((-right) - (-left));
    }

    // left >= right
    // -3 - (-5) => -3 + 5 => 5 - 3
    return ((-right) - (-left));
}

auto operator*(const BigInt &left, const BigInt &right) -> BigInt {
    // return BigInt::multiplyNaive(left, right);
    return BigInt::multiplyKaratsuba(left, right);
}

auto BigInt::compare(const BigInt &left, const BigInt &right) -> int {
    if(left.isNeg()) {
        if(!right.isNeg()) {
            return -1;
        }

        return compare(-right, -left);
    }

    if(left.isZero()) {
        if(right.isNeg()) {
            return 1;
        }
        if(right.isZero()) {
            return 0;
        }
        return -1;
    }

    // left is positive
    if(!right.isPos()) {
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
        int valLeft = *it1;
        int valRight = *it2;

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

auto BigInt::printInternal() const -> void {
    std::cout << "Is negative? " << this->negative << std::endl;
    std::cout << "digits list: ";
    for(int i : this->digits) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

BigInt::BigInt(bool negative_, std::vector<int> digits_) {
    this->negative = negative_;
    this->digits = digits_;

    this->normalizeDigits();
}

auto BigInt::normalizeDigits() -> void {
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

auto BigInt::isZero() const -> bool {
    return this->digits.size() == 1 && this->digits[0] == 0;
}

auto BigInt::isPos() const -> bool {
    return !this->isZero() && !this->negative;
}

auto BigInt::isNeg() const -> bool { return !this->isZero() && this->negative; }

auto BigInt::halfAdd(const BigInt &left, const BigInt &right) -> BigInt {
    std::vector<int> summedDigits;

    int carry = 0;
    for(size_t i = 0; i < std::max(left.digits.size(), right.digits.size());
        ++i) {
        int op1 = (i < left.digits.size()) ? left.digits[i] : 0;
        int op2 = (i < right.digits.size()) ? right.digits[i] : 0;

        const int bucketSum = op1 + op2 + carry;
        carry = bucketSum / BigInt::bucketMod;
        summedDigits.push_back(bucketSum % BigInt::bucketMod);
    }

    summedDigits.push_back(carry);

    return BigInt(false, summedDigits);
}

auto BigInt::halfSubtract(const BigInt &left, const BigInt &right) -> BigInt {
    // assume left >= right >= 0

    std::vector<int> subtractedDigits;
    bool borrow = false;

    for(size_t i = 0; i < std::max(left.digits.size(), right.digits.size());
        ++i) {
        int op1 = (i < left.digits.size()) ? left.digits[i] : 0;
        int op2 = (i < right.digits.size()) ? right.digits[i] : 0;

        if(borrow) {
            --op1;
        }
        borrow = false;

        if(op1 < op2) {
            borrow = true;
            op1 += BigInt::bucketMod;
        }

        subtractedDigits.push_back(op1 - op2);
    }

    return BigInt(false, subtractedDigits);
}

auto BigInt::multiplyNaive(const BigInt &left, const BigInt &right) -> BigInt {
    if(left.isZero() || right.isZero()) {
        return 0_b;
    }

    std::vector<int64_t> product(left.digits.size() + right.digits.size() + 2);

    for(size_t i = 0; i < left.digits.size(); ++i) {
        for(size_t j = 0; j < right.digits.size(); ++j) {
            int64_t val1 = left.digits[i];
            int64_t val2 = right.digits[j];

            int64_t prod = val1 * val2;
            product[i + j] += (prod % BigInt::bucketMod);
            product[i + j + 1] += (prod / BigInt::bucketMod);

            product[i + j + 1] += (product[i + j] / BigInt::bucketMod);
            product[i + j] %= BigInt::bucketMod;
        }
    }

    for(size_t i = 0; i + 1 < product.size(); ++i) {
        product[i + 1] += (product[i] / BigInt::bucketMod);
        product[i] %= BigInt::bucketMod;
    }

    std::vector<int> digits(product.size());
    for(size_t i = 0; i < product.size(); ++i) {
        digits[i] = static_cast<int>(product[i]);
    }

    return BigInt(left.negative ^ right.negative, digits);
}

auto BigInt::multiplyKaratsuba(const BigInt &left, const BigInt &right)
    -> BigInt {
    if(left.isZero() || right.isZero()) {
        return 0_b;
    }

    // convert both to the same lengths
    BigInt smaller = left;
    BigInt bigger = right;
    smaller.negative = false;
    bigger.negative = false;

    if(smaller.digits.size() > bigger.digits.size()) {
        BigInt temp = smaller;
        smaller = bigger;
        bigger = temp;
    }

    while(smaller.digits.size() < bigger.digits.size()) {
        smaller.digits.push_back(0);
    }

    BigInt product = BigInt::multiplyKaratsubaHelper(smaller, bigger);
    product.negative = left.negative ^ right.negative;

    return product;
}

auto BigInt::multiplyKaratsubaHelper(const BigInt &left, const BigInt &right)
    -> BigInt {
    size_t size = left.digits.size();
    if(size == 1) {
        return BigInt::multiplyNaive(left, right);
    }

    // split both left and right
    long splitPoint = static_cast<long>(size / 2);

    BigInt A(false, std::vector<int>(left.digits.begin() + splitPoint,
                                     left.digits.end()));
    BigInt B(false, std::vector<int>(left.digits.begin(),
                                     left.digits.begin() + splitPoint));
    BigInt C(false, std::vector<int>(right.digits.begin() + splitPoint,
                                     right.digits.end()));
    BigInt D(false, std::vector<int>(right.digits.begin(),
                                     right.digits.begin() + splitPoint));

    BigInt aPlusB = A + B;
    BigInt cPlusD = C + D;

    BigInt H = BigInt::multiplyKaratsubaHelper(aPlusB, cPlusD);
    BigInt F = BigInt::multiplyKaratsubaHelper(A, C);
    BigInt G = BigInt::multiplyKaratsubaHelper(B, D);

    BigInt K = H - F - G;

    std::vector<int64_t> product(2 * size + 2);

    // F is most significant, K is middle, G is least significant
    for(size_t i = 0; i < F.digits.size(); ++i) {
        product[2 * (size / 2) + i] += F.digits[i];
    }

    for(size_t i = 0; i < K.digits.size(); ++i) {
        product[(size / 2) + i] += K.digits[i];
    }

    for(size_t i = 0; i < G.digits.size(); ++i) {
        product[i] += G.digits[i];
    }

    // do carry-overs
    for(size_t i = 0; i + 1 < product.size(); ++i) {
        product[i + 1] += (product[i] / BigInt::bucketMod);
        product[i] %= BigInt::bucketMod;
    }

    // convert to ints
    std::vector<int> digits(product.size());
    for(size_t i = 0; i < product.size(); ++i) {
        digits[i] = product[i];
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
