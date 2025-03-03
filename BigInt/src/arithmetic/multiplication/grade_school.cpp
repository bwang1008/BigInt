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

} // namespace BigInt