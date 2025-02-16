#ifndef BIG_INT_H
#define BIG_INT_H // NOLINT(clang-diagnostic-unused-macros)

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

class BigInt {
  public:
    // Constructors

    // takes in a string of digits in base 10 with optional negative sign
    explicit BigInt(const std::string &num);
    BigInt(int64_t num);

    // Overloaded unary operators

    // Return negative version
    auto operator-() const -> BigInt;

    // helper functions

    // return a copy
    [[nodiscard]] auto clone() const -> BigInt;
    // return string representation of the BigInt
    [[nodiscard]] auto str() const -> std::string;

    // friend functions

    // Outputting a BigInt
    friend auto operator<<(std::ostream &out, const BigInt &integer)
        -> std::ostream &;
    // add two bigints
    friend auto operator+(const BigInt &left, const BigInt &right) -> BigInt;
    // subtract two bigints
    friend auto operator-(const BigInt &left, const BigInt &right) -> BigInt;
    // multiply two bigints
    friend auto operator*(const BigInt &left, const BigInt &right) -> BigInt;

    // static functions

    // -1 if left < right; 0 if left == right, and 1 if left > right
    static auto compare(const BigInt &left, const BigInt &right) -> int;

  private:
    bool negative;
    std::vector<int> digits;
    const static int digits_per_bucket = 9;
    const static int bucket_mod = 1000000000;

    BigInt(bool negative_, std::vector<int> digits_);

    // Remove leading 0's; if no digits, initialize as 0; change -0 to 0
    void normalize_digits();
    [[nodiscard]] auto is_zero() const -> bool;
    [[nodiscard]] auto is_positive() const -> bool;
    [[nodiscard]] auto is_negative() const -> bool;
    // add two non-negative bigints
    static auto half_add(const BigInt &left, const BigInt &right) -> BigInt;
    // subtract smaller from bigger
    static auto half_subtract(const BigInt &left, const BigInt &right)
        -> BigInt;
    // grade-school multiplication
    static auto multiply_naive(const BigInt &left, const BigInt &right)
        -> BigInt;
    // Karatsuba multiplication
    static auto multiply_karatsuba(const BigInt &left, const BigInt &right)
        -> BigInt;
    // Karatsuba multiplication
    static auto multiply_karatsuba_helper(const BigInt &left,
                                          const BigInt &right) -> BigInt;
    // show internal information for debugging
    auto print_internal() const -> void;
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
// user defined literal: can use as "BigInt num = 123_b;"
auto operator"" _b(const char *s) -> BigInt;

#endif
