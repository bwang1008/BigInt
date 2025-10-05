
#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp"

#include <vector>

namespace BigInt {

auto GradeSchoolMultiplier::multiply_positive(const BigInt &left,
                                              const BigInt &right) -> BigInt {
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

    std::vector<unsigned int> digits(product.size());
    for(size_t i = 0; i < product.size(); ++i) {
        digits[i] = static_cast<unsigned int>(product[i]);
    }

    return BigInt(false, digits);
}

} // namespace BigInt
