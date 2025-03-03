#include "BigInt/include/big_int.hpp"

#include <algorithm> // std::max
#include <cstddef>   // std::size_t
#include <cstdint>   // int64_t
#include <iostream>  // std::cout, std::endl
#include <iterator>  // std::advance
#include <ostream>
#include <sstream> // std::stringstream
#include <string>  // std::to_string
#include <vector>

namespace BigInt {

auto BigInt::operator-() const -> BigInt { return BigInt(!negative, digits); }

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

inline namespace literals {
auto operator"" _b(const char *s) -> BigInt { return BigInt(s); }
} // namespace literals

auto BigInt::print_internal() const -> void {
    std::cout << "Is negative? " << this->negative << std::endl;
    std::cout << "digits list: ";
    for(const int i : this->digits) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
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

auto operator*(const BigInt &left, const BigInt &right) -> BigInt {
    // return BigInt::multiplyNaive(left, right);
    return BigInt::multiply_karatsuba(left, right);
}

} // namespace BigInt