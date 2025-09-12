#include "BigInt/BigInt/include/big_int.hpp"

#include <cstddef> // std::size_t
#include <cstdint> // int64_t
#include <string>  // std::stoi
#include <vector>

namespace BigInt {

auto divide_base10_string_by_2(const std::string &num) -> std::string;

auto divide_base10_string_by_2(const std::string &num) -> std::string {
    std::vector<char> digits;
    int carry = 0;
    for(const char digit : num) {
        const int operand = digit - '0' + ((carry == 1) ? 10 : 0);
        digits.push_back(static_cast<char>(operand / 2 + '0'));
        carry = operand % 2;
    }

    return std::string(digits.begin(), digits.end());
}

BigInt::BigInt(std::string num) : negative(false) {
    if(num.empty()) {
        this->digits.push_back(0);
        return;
    }

    this->negative = (num[0] == '-');
    if(this->negative) {
        num = num.substr(1);
    }

    unsigned int num_iterations = 0;
    unsigned int bucket = 0;
    while(!num.empty() && num != "0") {
        ++num_iterations;
        const unsigned int bit =
            static_cast<unsigned int>(num[num.size() - 1] - '0') % 2;
        bucket = 2 * bucket + bit;
        if(num_iterations % BigInt::num_bits_per_bucket == 0) {
            this->digits.push_back(bucket);
            bucket = 0;
        }
        num = divide_base10_string_by_2(num);
    }
    if(bucket > 0) {
        this->digits.push_back(bucket);
    }

    if(this->digits.size() == 1 && this->digits[0] == 0 && this->negative) {
        this->negative = false;
    }
}

BigInt::BigInt(const int64_t num) : BigInt(std::to_string(num)) {}

BigInt::BigInt() : negative(false), digits{0} {}

BigInt::BigInt(bool negative_, std::vector<unsigned int> digits_)
    : negative(negative_), digits(std::move(digits_)) {}

inline namespace literals {
auto operator"" _b(const char *s) -> BigInt { return BigInt(s); }
} // namespace literals

} // namespace BigInt
