#include "BigInt/BigInt/include/big_int.hpp"

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

    BigInt product = BigInt::multiply_karatsuba_helper(left, right);
    product.negative = left.negative ^ right.negative;

    return product;
}

auto BigInt::multiply_karatsuba_helper(const BigInt &left, const BigInt &right)
    -> BigInt {
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
        return BigInt::multiply_grade_school(smaller, bigger);
    }

    // split both left and right
    const std::size_t split_point = size / 2;

    auto smaller_mid = smaller.digits.begin();
    std::advance(smaller_mid, split_point);
    auto bigger_mid = bigger.digits.begin();
    std::advance(bigger_mid, split_point);

    const BigInt a(false, std::vector<int>(smaller_mid, smaller.digits.end()));
    const BigInt b(false,
                   std::vector<int>(smaller.digits.begin(), smaller_mid));
    const BigInt c(false, std::vector<int>(bigger_mid, bigger.digits.end()));
    const BigInt d(false, std::vector<int>(bigger.digits.begin(), bigger_mid));

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
        product[i + 1] += (product[i] / 2);
        product[i] %= 2;
    }

    // convert to ints
    std::vector<int> digits(product.size());
    for(std::size_t i = 0; i < product.size(); ++i) {
        digits[i] = static_cast<int>(product[i]);
    }

    return BigInt(false, digits);
}

} // namespace BigInt
