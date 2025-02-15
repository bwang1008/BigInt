#ifndef BIG_INT_H
#define BIG_INT_H // NOLINT(clang-diagnostic-unused-macros)

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

class BigInt {
  public:
    // Constructors
    explicit BigInt(
        const std::string &num); // takes in a string of digits, in base 10
    BigInt(int64_t num);

    // Overloaded unary operators
    auto operator-() const -> BigInt; // Return a negative version

    // helper functions
    [[nodiscard]] auto clone() const -> BigInt; // return a copy
    [[nodiscard]] auto str() const
        -> std::string; // return string representation of the bigint

    // friend functions
    friend auto operator<<(std::ostream &out, const BigInt &integer)
        -> std::ostream &; // Outputting a BigInt
    friend auto operator+(const BigInt &left, const BigInt &right)
        -> BigInt; // add two bigints
    friend auto operator-(const BigInt &left,
                          const BigInt &right)
        -> BigInt; // subtract two bigints
    friend auto operator*(const BigInt &left,
                          const BigInt &right)
        -> BigInt; // multiply two bigints

    // static functions
    static auto compare(const BigInt &left, const BigInt &right)
        -> int; // -1 if left < right; 0 if left ==
                // right, and 1 if left > right

  private:
    bool negative;
    std::vector<int> digits;
    const static int digitsPerBucket = 9;
    const static int bucketMod = 1000000000;

    BigInt(bool negative_, std::vector<int> digits_);

    void normalizeDigits(); // Remove leading 0's; if no digits, initialize as
                            // 0; change -0 to 0
    [[nodiscard]] auto isZero() const -> bool; // check if number is 0
    [[nodiscard]] auto isPos() const -> bool;  // check if number is positive
    [[nodiscard]] auto isNeg() const -> bool;  // check if number is negative
    static auto halfAdd(const BigInt &left, const BigInt &right)
        -> BigInt; // add two non-negative bigints
    static auto halfSubtract(const BigInt &left, const BigInt &right)
        -> BigInt; // subtract smaller from bigger
    static auto multiplyNaive(const BigInt &left, const BigInt &right)
        -> BigInt; // grade-school multiplication
    static auto multiplyKaratsuba(const BigInt &left, const BigInt &right)
        -> BigInt; // Karatsuba multiplication
    static auto multiplyKaratsubaHelper(const BigInt &left, const BigInt &right)
        -> BigInt; // Karatsuba multiplication
    auto printInternal() const
        -> void; // show internal information for debugging
};

// declare function so any file that uses this header can see it
// (friend does not bring it into scope)
auto operator==(const BigInt &left, const BigInt &right) -> bool; // comparison
auto operator!=(const BigInt &left, const BigInt &right) -> bool;
auto operator<(const BigInt &left, const BigInt &right) -> bool;
auto operator>(const BigInt &left, const BigInt &right) -> bool;
auto operator<=(const BigInt &left, const BigInt &right) -> bool;
auto operator>=(const BigInt &left, const BigInt &right) -> bool;
auto operator"" _b(const char *s)
    -> BigInt; // user defined literal: can use as "BigInt num = 123_b;"

#endif
