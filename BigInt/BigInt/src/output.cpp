#include "BigInt/BigInt/include/big_int.hpp"

#include <cstddef> // std::size_t
#include <ostream>
#include <sstream> // std::stringstream
#include <string>  // std::to_string

namespace BigInt {
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

} // namespace BigInt
