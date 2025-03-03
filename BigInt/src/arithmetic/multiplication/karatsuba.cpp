#include "BigInt/include/big_int.hpp"

#include <cstddef>  // std::size_t
#include <cstdint>  // int64_t
#include <iterator> // std::advance
#include <vector>

namespace BigInt {

auto BigInt::multiply_karatsuba(const BigInt &left, const BigInt &right)
    -> BigInt {
    if(left.is_zero() || right.is_zero()) {
        return BigInt();
    }

    // convert both to the same lengths
    BigInt smaller = BigInt(false, left.digits);
    BigInt bigger = BigInt(false, right.digits);

    if(smaller.digits.size() > bigger.digits.size()) {
        BigInt temp = smaller;
        smaller = bigger;
        bigger = temp;
    }

    while(smaller.digits.size() < bigger.digits.size()) {
        smaller.digits.push_back(0);
    }

    BigInt product = BigInt::multiply_karatsuba_helper(smaller, bigger);
    product.negative = left.negative ^ right.negative;

    return product;
}

auto BigInt::multiply_karatsuba_helper(const BigInt &left, const BigInt &right)
    -> BigInt {
    const std::size_t size = left.digits.size();
    if(size == 1) {
        return BigInt::multiply_grade_school(left, right);
    }

    // split both left and right
    const std::size_t split_point = size / 2;

    auto left_mid = left.digits.begin();
    std::advance(left_mid, split_point);
    auto right_mid = right.digits.begin();
    std::advance(right_mid, split_point);

    const BigInt a(false, std::vector<int>(left_mid, left.digits.end()));
    const BigInt b(false, std::vector<int>(left.digits.begin(), left_mid));
    const BigInt c(false, std::vector<int>(right_mid, right.digits.end()));
    const BigInt d(false, std::vector<int>(right.digits.begin(), right_mid));

    const BigInt a_plus_b = a + b;
    const BigInt c_plus_d = c + d;

    const BigInt h = BigInt::multiply_karatsuba_helper(a_plus_b, c_plus_d);
    const BigInt f = BigInt::multiply_karatsuba_helper(a, c);
    const BigInt g = BigInt::multiply_karatsuba_helper(b, d);

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
    std::vector<int> digits(product.size());
    for(std::size_t i = 0; i < product.size(); ++i) {
        digits[i] = static_cast<int>(product[i]);
    }

    return BigInt(false, digits);
}

} // namespace BigInt