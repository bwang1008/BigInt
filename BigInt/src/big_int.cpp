#include "big_int.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

BigInt::BigInt(const std::string &num) {
    int start = 0;
    if(num[0] == '-') {
        this->negative = true;
        start = 1;
    } else {
        this->negative = false;
    }

    for(int sectionEnd = static_cast<int>(num.size()),
            sectionStart =
                std::max(sectionEnd - BigInt::digitsPerBucket, start);
        sectionEnd != start; sectionEnd = sectionStart,
            sectionStart = std::max(sectionEnd - BigInt::digitsPerBucket,
                                    start)) {
        this->digits.push_back(std::stoi(
            num.substr(static_cast<size_t>(sectionStart),
                       static_cast<size_t>(sectionEnd - sectionStart))));
    }

    normalizeDigits();
}

BigInt::BigInt(const int64_t num) {
    if(num == 0) {
        this->negative = false;
        this->digits.push_back(0);
        normalizeDigits();
        return;
    }

    this->negative = (num < 0);
    long long N = num;

    // can't do abs on num: abs doesn't return a positive number of
    // LONG_LONG_MIN

    while(N != 0) {
        long long tempDigits = std::abs(N % BigInt::bucketMod);
        this->digits.push_back(static_cast<int>(tempDigits));
        N /= BigInt::bucketMod;
    }

    normalizeDigits();
}

BigInt BigInt::operator-() const {
    if(!isZero()) {
        BigInt clone = this->clone();
        clone.negative = !clone.negative;

        return clone;
    }

    return BigInt("0");
}

BigInt BigInt::clone() const { return BigInt(this->negative, this->digits); }

std::string BigInt::str() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream &operator<<(std::ostream &out, const BigInt &integer) {
    if(integer.negative) {
        out << "-";
    }

    for(std::vector<int>::const_reverse_iterator it = integer.digits.crbegin();
        it != integer.digits.crend(); ++it) {
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

BigInt operator"" _b(const char *s) { return BigInt(s); }

BigInt operator+(const BigInt &left, const BigInt &right) {
    if(left.isZero()) {
        return right.clone();
    }
    if(right.isZero()) {
        return left.clone();
    }

    if(left.isPos()) {
        if(right.isPos()) {
            return BigInt::halfAdd(left, right);
        } else {
            // 3 + (-5) => 3 - 5
            return left - (-right);
        }
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

BigInt operator-(const BigInt &left, const BigInt &right) {
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
            } else {
                // 5 - 3  OR  5 - 5
                return BigInt::halfSubtract(left, right);
            }
        } else {
            // right negative
            // 3 - (-5) => 3 + 5
            // 5 - (-3) => 5 + 3
            // 5 - (-5) => 5 + 5
            return left + (-right);
        }
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

BigInt operator*(const BigInt &left, const BigInt &right) {
    // return BigInt::multiplyNaive(left, right);
    return BigInt::multiplyKaratsuba(left, right);
}

int BigInt::compare(const BigInt &left, const BigInt &right) {
    if(left.isNeg()) {
        if(!right.isNeg()) {
            return -1;
        }

        return compare(-right, -left);
    } else if(left.isZero()) {
        if(right.isNeg()) {
            return 1;
        } else if(right.isZero()) {
            return 0;
        } else {
            return -1;
        }
    }

    // left is positive
    if(!right.isPos()) {
        return 1;
    }

    // right is positive
    if(left.digits.size() < right.digits.size()) {
        return -1;
    } else if(left.digits.size() > right.digits.size()) {
        return 1;
    }

    // compare from most significant digits down
    std::vector<int>::const_reverse_iterator it1 = left.digits.crbegin();
    std::vector<int>::const_reverse_iterator it2 = right.digits.crbegin();

    while(it1 != left.digits.crend() && it2 != right.digits.crend()) {
        int valLeft = *it1;
        int valRight = *it2;

        if(valLeft < valRight) {
            return -1;
        } else if(valLeft > valRight) {
            return 1;
        }

        ++it1;
        ++it2;
    }

    return 0;
}

void BigInt::printInternal() const {
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

void BigInt::normalizeDigits() {
    // remove leading 0's
    while(this->digits.size() > 0 && this->digits.back() == 0) {
        this->digits.pop_back();
    }

    // if no digits, initiailize with one 0
    if(this->digits.size() == 0) {
        this->digits.push_back(0);
    }

    // turn -0 to 0
    if(this->digits.size() == 1 && this->digits[0] == 0) {
        this->negative = false;
    }
}
bool BigInt::isZero() const {
    return this->digits.size() == 1 && this->digits[0] == 0;
}

bool BigInt::isPos() const { return !this->isZero() && !this->negative; }

bool BigInt::isNeg() const { return !this->isZero() && this->negative; }

BigInt BigInt::halfAdd(const BigInt &left, const BigInt &right) {
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

BigInt BigInt::halfSubtract(const BigInt &left, const BigInt &right) {
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

BigInt BigInt::multiplyNaive(const BigInt &left, const BigInt &right) {
    if(left.isZero() || right.isZero()) {
        return 0_b;
    }

    std::vector<long long> product(left.digits.size() + right.digits.size() +
                                   2);

    for(size_t i = 0; i < left.digits.size(); ++i) {
        for(size_t j = 0; j < right.digits.size(); ++j) {
            long long val1 = left.digits[i];
            long long val2 = right.digits[j];

            long long prod = val1 * val2;
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

BigInt BigInt::multiplyKaratsuba(const BigInt &left, const BigInt &right) {
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

BigInt BigInt::multiplyKaratsubaHelper(const BigInt &left,
                                       const BigInt &right) {
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

    std::vector<long long> product(2 * size + 2);

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

bool operator==(const BigInt &left, const BigInt &right) {
    return BigInt::compare(left, right) == 0;
}

bool operator!=(const BigInt &left, const BigInt &right) {
    return !(left == right);
}

bool operator<(const BigInt &left, const BigInt &right) {
    return BigInt::compare(left, right) < 0;
}

bool operator>(const BigInt &left, const BigInt &right) {
    return BigInt::compare(left, right) > 0;
}

bool operator<=(const BigInt &left, const BigInt &right) {
    return BigInt::compare(left, right) <= 0;
}

bool operator>=(const BigInt &left, const BigInt &right) {
    return BigInt::compare(left, right) >= 0;
}
