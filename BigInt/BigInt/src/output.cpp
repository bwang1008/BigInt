#include "BigInt/BigInt/include/big_int.hpp"

#include <cstddef> // std::size_t
#include <ostream>
#include <sstream> // std::stringstream
#include <string>  // std::to_string
#include <vector>

constexpr int BASE10 = 10;

namespace BigInt {

auto add_1_to_base10_string(const std::string &num) -> std::string;

auto add_1_to_base10_string(const std::string &num) -> std::string {
    std::vector<char> digits;
    int carry = 0;
    for(std::string::const_reverse_iterator it = num.crbegin();
        it != num.crend(); ++it) {
        const int digit = *it - '0';
        const int remainder = (digit + carry) % BASE10;
        digits.push_back(static_cast<char>(remainder + '0'));
        carry = (digit + carry) / BASE10;
    }
    if(carry != 0) {
        digits.push_back(static_cast<char>(carry + '0'));
    }

    return std::string(digits.rbegin(), digits.rend());
}

auto double_base10_string(const std::string &num) -> std::string;

auto double_base10_string(const std::string &num) -> std::string {
    std::vector<char> digits;
    int carry = 0;
    for(std::string::const_reverse_iterator it = num.crbegin();
        it != num.crend(); ++it) {
        const int digit = *it - '0';
        const int sum = (2 * digit + carry);
        digits.push_back(static_cast<char>(sum % BASE10 + '0'));
        carry = sum / BASE10;
    }
    if(carry != 0) {
        digits.push_back(static_cast<char>(carry + '0'));
    }

    return std::string(digits.rbegin(), digits.rend());
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

    std::string base10_repr = "0";
    for(auto it = integer.digits.crbegin(); it != integer.digits.crend();
        ++it) {
        unsigned int bucket = *it;
        for(unsigned int bit_iteration = 0;
            bit_iteration < BigInt::num_bits_per_bucket; ++bit_iteration) {
            const unsigned int bit = bucket % 2;
            bucket /= 2;
            base10_repr = double_base10_string(base10_repr);
            if(bit != 0) {
                base10_repr = add_1_to_base10_string(base10_repr);
            }
        }
    }

    out << base10_repr;
    return out;
}

} // namespace BigInt
