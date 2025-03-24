#include "BigInt/include/big_int.hpp"

#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::endl
#include <ostream>
#include <sstream> // std::stringstream
#include <string>  // std::to_string

namespace BigInt {

auto BigInt::operator-() const -> BigInt { return BigInt(!negative, digits); }

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

} // namespace BigInt
