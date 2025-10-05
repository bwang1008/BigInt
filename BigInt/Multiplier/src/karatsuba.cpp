#include "BigInt/BigInt/include/big_int.hpp"
#include "BigInt/Multiplier/include/multiplier.hpp"

#include <cstddef>  // std::size_t
#include <cstdint>  // int64_t
#include <iterator> // std::advance
#include <vector>

namespace BigInt {

auto KaratsubaMultiplier::multiply_positive(const BigInt &left,
                                            const BigInt &right) -> BigInt {
    BigInt smaller = left;
    BigInt bigger = right;
    if(smaller.digits.size() > bigger.digits.size()) {
        const BigInt temp = smaller;
        smaller = bigger;
        bigger = temp;
    }
    // convert both to the same lengths
    while(smaller.digits.size() < bigger.digits.size()) {
        smaller.digits.push_back(0);
    }

    const std::size_t size = smaller.digits.size();
    if(size == 1) {
        return GradeSchoolMultiplier().multiply(smaller, bigger);
    }

    // split both left and right
    const std::size_t split_point = size / 2;

    auto smaller_mid = smaller.digits.begin();
    std::advance(smaller_mid, split_point);
    auto bigger_mid = bigger.digits.begin();
    std::advance(bigger_mid, split_point);

    const BigInt a(
        false, std::vector<unsigned int>(smaller_mid, smaller.digits.end()));
    const BigInt b(
        false, std::vector<unsigned int>(smaller.digits.begin(), smaller_mid));
    const BigInt c(false,
                   std::vector<unsigned int>(bigger_mid, bigger.digits.end()));
    const BigInt d(
        false, std::vector<unsigned int>(bigger.digits.begin(), bigger_mid));

    const BigInt a_plus_b = a + b;
    const BigInt c_plus_d = c + d;

    // size > 1, so can multiply using positive
    const BigInt h = multiply_positive(a_plus_b, c_plus_d);
    const BigInt f = multiply_positive(a, c);
    const BigInt g = multiply_positive(b, d);

    const BigInt k = h - f - g;

    std::vector<int64_t> product(2 * size + 2);

    // f is most significant, k is middle, g is least significant
    for(std::size_t i = 0; i < f.digits.size(); ++i) {
        product[2 * (size / 2) + i] += f.digits[i];
    }
    for(std::size_t i = 0; i < k.digits.size(); ++i) {
        product[(size / 2) + i] += k.digits[i];
    }
    for(std::size_t i = 0; i < g.digits.size(); ++i) {
        product[i] += g.digits[i];
    }

    // do carry-overs
    for(std::size_t i = 0; i + 1 < product.size(); ++i) {
        product[i + 1] += (product[i] / BigInt::bucket_mod);
        product[i] %= BigInt::bucket_mod;
    }

    // convert to ints
    std::vector<unsigned int> digits(product.size());
    for(std::size_t i = 0; i < product.size(); ++i) {
        digits[i] = static_cast<unsigned int>(product[i]);
    }

    return BigInt(false, digits);
}

} // namespace BigInt
