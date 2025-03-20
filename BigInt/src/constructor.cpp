#include "BigInt/include/big_int.hpp"

#include <cstddef> // std::size_t
#include <cstdint> // int64_t
#include <string>  // std::stoi, std::to_string
#include <vector>

namespace BigInt {

BigInt::BigInt(const std::string &num) : negative(false) {
    if(num.empty()) {
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

BigInt::BigInt(bool negative_, std::vector<int> digits_)
    : negative(negative_), digits(std::move(digits_)) {
    this->normalize_digits();
}

inline namespace literals {
auto operator"" _b(const char *s) -> BigInt { return BigInt(s); }
} // namespace literals

} // namespace BigInt