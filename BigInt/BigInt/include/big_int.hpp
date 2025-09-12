#ifndef BIG_INT_H
#define BIG_INT_H // NOLINT(clang-diagnostic-unused-macros)

#include <cstdint> // int64_t
#include <ostream>
#include <string>
#include <utility> // std::pair
#include <vector>

namespace BigInt {
class BigInt {
  public:
    // Constructors

    // takes in a string of digits in base 10 with optional negative sign
    explicit BigInt(std::string num);
    explicit BigInt(int64_t num);
    BigInt();

    // Overloaded unary operators

    // Return negative version
    auto operator-() const -> BigInt;

    // helper functions

    // return string representation of the BigInt
    [[nodiscard]] auto str() const -> std::string;

    // friend functions

    // Outputting a BigInt
    friend auto operator<<(std::ostream &out, const BigInt &integer)
        -> std::ostream &;

    // arithmetic operations
    friend auto operator+(const BigInt &left, const BigInt &right) -> BigInt;
    friend auto operator-(const BigInt &left, const BigInt &right) -> BigInt;
    friend auto operator*(const BigInt &left, const BigInt &right) -> BigInt;
    friend auto operator/(const BigInt &left, const BigInt &right) -> BigInt;
    friend auto operator%(const BigInt &left, const BigInt &right) -> BigInt;

    auto operator+=(const BigInt &right) -> BigInt &;
    auto operator-=(const BigInt &right) -> BigInt &;
    auto operator*=(const BigInt &right) -> BigInt &;
    auto operator/=(const BigInt &right) -> BigInt &;
    auto operator%=(const BigInt &right) -> BigInt &;

    // static functions

    // -1 if left < right; 0 if left == right, and 1 if left > right
    static auto compare(const BigInt &left, const BigInt &right) -> int;
    // grade-school multiplication
    static auto multiply_grade_school(const BigInt &left, const BigInt &right)
        -> BigInt;
    // Karatsuba multiplication
    static auto multiply_karatsuba(const BigInt &left, const BigInt &right)
        -> BigInt;

    static auto quotient_and_remainder_grade_school(const BigInt &left,
                                                    const BigInt &right)
        -> std::pair<BigInt, BigInt>;

    static auto divide_grade_school(const BigInt &left, const BigInt &right)
        -> BigInt;
    static auto remainder_grade_school(const BigInt &left, const BigInt &right)
        -> BigInt;

    [[nodiscard]] auto abs() const -> BigInt;
    static auto gcd(const BigInt &left, const BigInt &right) -> BigInt;

    auto swap(BigInt &other) -> void;

  private:
    bool negative;
    std::vector<unsigned int> digits{};
    static constexpr unsigned int num_bits_per_bucket = 1;
    static constexpr unsigned int bucket_mod =
        (1U << BigInt::num_bits_per_bucket);

    BigInt(bool negative_, std::vector<unsigned int> digits_);

    [[nodiscard]] [[gnu::pure]] auto is_zero() const -> bool;
    [[nodiscard]] [[gnu::pure]] auto is_positive() const -> bool;
    [[nodiscard]] [[gnu::pure]] auto is_negative() const -> bool;
    // add two non-negative bigints
    static auto half_add(const BigInt &left, const BigInt &right) -> BigInt;
    static auto add_helper(const BigInt &left, const BigInt &right) -> BigInt;
    // subtract smaller from bigger
    static auto half_subtract(const BigInt &left, const BigInt &right)
        -> BigInt;
    static auto subtract_helper(const BigInt &left, const BigInt &right)
        -> BigInt;

    // Karatsuba multiplication
    static auto multiply_karatsuba_helper(const BigInt &left,
                                          const BigInt &right) -> BigInt;

    static auto gcd_helper(const BigInt &left, const BigInt &right) -> BigInt;
};

// declare function so any file that uses this header can see it
// (friend does not bring it into scope)

// comparison functions
auto operator==(const BigInt &left, const BigInt &right) -> bool;
auto operator!=(const BigInt &left, const BigInt &right) -> bool;
auto operator<(const BigInt &left, const BigInt &right) -> bool;
auto operator>(const BigInt &left, const BigInt &right) -> bool;
auto operator<=(const BigInt &left, const BigInt &right) -> bool;
auto operator>=(const BigInt &left, const BigInt &right) -> bool;

inline namespace literals {
// user defined literal: can use as "BigInt num = 123_b;"
// see
// https://stackoverflow.com/questions/49054477/how-to-refer-to-user-defined-literal-operator-inside-a-namespace
auto operator"" _b(const char *s) -> BigInt;
} // namespace literals

} // namespace BigInt

#endif
