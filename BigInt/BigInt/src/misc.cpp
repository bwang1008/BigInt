#include "BigInt/BigInt/include/big_int.hpp"

#include <utility> // std::swap

namespace BigInt {

auto BigInt::swap(BigInt &other) -> void {
    std::swap(this->digits, other.digits);
    std::swap(this->negative, other.negative);
}

} // namespace BigInt
