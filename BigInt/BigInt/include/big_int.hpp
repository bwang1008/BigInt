#ifndef BIG_INT_H
#define BIG_INT_H // NOLINT(clang-diagnostic-unused-macros)

#include <cstdint> // int64_t
#include <ostream>
#include <string>
#include <utility> // std::pair
#include <vector>

namespace BigInt {

class Multiplier;
class GradeSchoolMultiplier;
class KaratsubaMultiplier;

/**
 * Class that represents arbitrary-precision integers.
 */
class BigInt {
  public:
    // Constructors

    /**
     * Constructor takes in a string of base-10 digits.
     *
     * @param num string of base-10 digits. Can start with a minus sign to
     * signify the integer is negative.
     */
    explicit BigInt(std::string num);
    /**
     * Constructor takes in an int.
     *
     * @param num integral primitive that upcasts to an int64_t.
     */
    explicit BigInt(int64_t num);
    /**
     * Default constructor that has a value of 0.
     */
    BigInt();

    // Overloaded unary operators

    /**
     * Return a BigInt with a value of the opposite sign.
     */
    auto operator-() const -> BigInt;

    /**
     * Return string representation of the BigInt value.
     *
     * @return string representation of BigInt value in base-10.
     */
    [[nodiscard]] auto str() const -> std::string;

    // friend functions

    /**
     * Friend function overload of << that allows printing of BigInt string
     * representation.
     *
     * Ex:
     *
     * BigInt::BigInt x = 5;
     * std::cout << x;
     * @param out output stream, such as std::cout from <iostream>
     * @param integer BigInt to be outputted
     * @return reference to `out` parameter
     */
    friend auto operator<<(std::ostream &out, const BigInt &integer)
        -> std::ostream &;

    // arithmetic operations

    /**
     * Adds two BigInts.
     *
     * @param left First BigInt to be added with
     * @param right Second BigInt to be added with
     * @return sum of `left` and `right`
     */
    friend auto operator+(const BigInt &left, const BigInt &right) -> BigInt;
    /**
     * Subtracts two BigInts.
     *
     * @param left BigInt to be subtracted from
     * @param right BigInt amount to subtract from `left`
     * @return the difference between `left` and `right`
     */
    friend auto operator-(const BigInt &left, const BigInt &right) -> BigInt;
    /**
     * Multiplies two BigInts.
     *
     * This defaults to using Karatsuba's algorithm. To use another algorithm,
     * use the Multipler classes instead.
     * @param left First BigInt to be multiplied with
     * @param right Second BigInt to be multiplied with `left`
     * @return product of `left` and `right`
     */
    friend auto operator*(const BigInt &left, const BigInt &right) -> BigInt;
    /**
     * Divides two BigInts.
     *
     * This matches the division of int primitives.
     * @param left First BigInt to be divided
     * @param right BigInt amount that `left` should be divided by
     * @return the floor of abs(`left`) / abs(`right`), corrected for sign
     */
    friend auto operator/(const BigInt &left, const BigInt &right) -> BigInt;
    /**
     * Find remainder when two BigInts are divided.
     *
     * This matches the remainder of int primitives.
     * @param left First BigInt to find the remainder with `right`.
     * @param right BigInt amount that `left` should be divided by to find the
     * remainder.
     * @return left - (right * (left / right))
     */
    friend auto operator%(const BigInt &left, const BigInt &right) -> BigInt;

    /**
     * Update the current BigInt value to be the sum of itself with `right`.
     *
     * @param right amount to add to current BigInt value
     * @return reference to current BigInt
     */
    auto operator+=(const BigInt &right) -> BigInt &;
    /**
     * Update the current BigInt value to subtract the amount by `right`.
     *
     * @param right amount to subtract from current BigInt value
     * @return reference to current BigInt
     */
    auto operator-=(const BigInt &right) -> BigInt &;
    /**
     * Update the current BigInt value to be product of itself with `right`.
     *
     * @param right amount to multiply by current BigInt value
     * @return reference to current BigInt
     */
    auto operator*=(const BigInt &right) -> BigInt &;
    /**
     * Update the current BigInt value to be division of itself with `right`.
     *
     * @param right amount to divide the current BigInt value by
     * @return reference to current BigInt
     */
    auto operator/=(const BigInt &right) -> BigInt &;
    /**
     * Update the current BigInt value to be remainder of itself with `right`.
     *
     * @param right amount to divide the current BigInt value by to get
     * remainder
     * @return reference to current BigInt
     */
    auto operator%=(const BigInt &right) -> BigInt &;

    // static functions

    /**
     * Return an int indication result of comparing the values of two BigInts.
     *
     * @param left First BigInt to be compared with
     * @param right Second BigInt to be compared with
     * @return -1 if (`left` < `right`), 0 if `left` equals `right`, and 1 if
     * `left` > `right`
     */
    static auto compare(const BigInt &left, const BigInt &right) -> int;
    /**
     * Multiplies two BigInts using the grade-school multiplication algorithm.
     *
     * @param left First BigInt to be multiplied with
     * @param right Second BigInt to be multiplied with `left`
     * @return product of `left` and `right`
     */
    static auto multiply_grade_school(const BigInt &left, const BigInt &right)
        -> BigInt;
    /**
     * Multiplies two BigInts using Karatsuba's algorithm.
     *
     * @param left First BigInt to be multiplied with
     * @param right Second BigInt to be multiplied with `left`
     * @return product of `left` and `right`
     */
    static auto multiply_karatsuba(const BigInt &left, const BigInt &right)
        -> BigInt;

    /**
     * Find the division and remainder of two BigInts.
     *
     * This computes the division once to produce both values.
     *
     * @param left BigInt to be divided
     * @param right BigInt to divide `left` by
     * @return a tuple of two elements, the first being the result of (`left` /
     * `right`), the second being the result of (`left` % `right`)
     */
    static auto quotient_and_remainder_grade_school(const BigInt &left,
                                                    const BigInt &right)
        -> std::pair<BigInt, BigInt>;

    /**
     * Divides two BigInts.
     *
     * This uses the grade-school division algorithm.
     * @param left First BigInt to be divided
     * @param right BigInt amount that `left` should be divided by
     * @return the floor of abs(`left`) / abs(`right`), corrected for sign.
     */
    static auto divide_grade_school(const BigInt &left, const BigInt &right)
        -> BigInt;
    /**
     * Find remainder when two BigInts are divided.
     *
     * This uses the grade-school division algorithm to find the remainder.
     * @param left First BigInt to be divided
     * @param right BigInt amount that `left` should be divided by
     * @return `left` - (`right` * (`left` / `right`))
     */
    static auto remainder_grade_school(const BigInt &left, const BigInt &right)
        -> BigInt;

    /**
     * Return a BigInt with the same absolute value as the current, but
     * non-negative.
     *
     * @return non-negative BigInt with same absolute value as the current
     */
    [[nodiscard]] auto abs() const -> BigInt;

    /**
     * Returns the greatest common divisor (GCD) of two BigInts.
     *
     * @param left First BigInt to get greatest common divisor with `right`
     * @param right Second BigInt to get greatest common divisor with `left`
     * @return the greatest common divisor of `left` and `right`
     */
    static auto gcd(const BigInt &left, const BigInt &right) -> BigInt;

    /**
     * Swaps the values of the current BigInt with other.
     *
     * @param other BigInt to swap values with current BigInt
     */
    auto swap(BigInt &other) -> void;

  private:
    /// @brief true indicates BigInt value is negative; false indicates BigInt
    /// value is non-negative
    bool negative;
    /// @brief list of digits of BigInt starting from least-significant digits,
    /// represented in base `bucket_mod`
    std::vector<unsigned int> digits{};
    /// @brief number of bits each element of `digits` can have at most
    static constexpr unsigned int num_bits_per_bucket = 1;
    /// @brief base of each value in `digits`; each value must be less than this
    /// value
    static constexpr unsigned int bucket_mod =
        (1U << BigInt::num_bits_per_bucket);

    /**
     * Remove leading zeroes from `digits`.
     *
     * If there are no digits, initialize as 0.
     * In addition, change -0 to 0.
     */
    void normalize_digits();
    /**
     * Private constructor that takes in an explicit negative flag and list of
     * digits.
     *
     * @param negative_ true indicates BigInt value is negative; false indicates
     * BigInt value is non-negative
     * @param digits_ list of digits that will be placed in `digits`. Each value
     * must be less than `bucket_mod`
     */
    BigInt(bool negative_, std::vector<unsigned int> digits_);

    /// @brief Return boolean indicating if BigInt value is zero.
    /// @return true if current BigInt value is zero, false if not
    [[nodiscard]] [[gnu::pure]] auto is_zero() const -> bool;
    /// @brief Return boolean indicating if BigInt value is positive.
    /// @return  true if current BigInt value is positive, false if not
    [[nodiscard]] [[gnu::pure]] auto is_positive() const -> bool;
    /// @brief  Return boolean indicating if BigInt value is negative.
    /// @return true if current BigInt value is negative, false if not
    [[nodiscard]] [[gnu::pure]] auto is_negative() const -> bool;
    /**
     * Add two non-negative BigInts.
     *
     * @param left First BigInt to be added with. Must be non-negative
     * @param right Second BigInt to be added with `left`. Must be non-negative
     * @return sum of `left` and `right`
     */
    static auto half_add(const BigInt &left, const BigInt &right) -> BigInt;
    /**
     * Add two BigInts.
     *
     * Helper function that calls related half-adders or half-subtracters,
     * depending on signs of `left` and `right`.
     * @param left First BigInt to be added with
     * @param right Second BigInt to be added with `left`
     * @return sum of `left` and `right`
     */
    static auto add_helper(const BigInt &left, const BigInt &right) -> BigInt;
    /**
     * Subtracts `right` from `left`, where `left` >= `right`.
     *
     * @param left BigInt to be subtracted from. Must not be smaller than
     * `right`
     * @param right BigInt amount to subtract from `left`. Must not be greater
     * than `left`
     * @return the difference between `left` and `right`
     */
    static auto half_subtract(const BigInt &left, const BigInt &right)
        -> BigInt;
    /**
     * Subtracts two BigInts.
     *
     * Helper function that calls related half-adders or half-subtracters,
     * depending on signs of `left` and `right`.
     * @param left BigInt to be subtracted from
     * @param right BigInt amount to subtract from `left`
     * @return the difference between `left` and `right`
     */
    static auto subtract_helper(const BigInt &left, const BigInt &right)
        -> BigInt;

    /**
     * Returns the greatest common divisor (GCD) of two non-negative BigInts.
     *
     * @param left First BigInt to get greatest common divisor with `right`.
     * Must be non-negative
     * @param right Second BigInt to get greatest common divisor with `left`.
     * Must be non-negative
     * @return the greatest common divisor of `left` and `right`
     */
    static auto gcd_helper(const BigInt &left, const BigInt &right) -> BigInt;

    // Multiplier and its base classes can access a BigInt's internal attributes
    friend class Multiplier;
    friend class GradeSchoolMultiplier;
    friend class KaratsubaMultiplier;
};

// declare function so any file that uses this header can see and use it
// (friend does not bring it into scope)

// comparison functions

/**
 * Returns boolean indicating if `left` has the same value as `right`.
 *
 * @param left BigInt to be compared with `right`
 * @param right BigInt to be compared with `left`
 * @return true if `left` has the same value as `right`, otherwise false
 */
auto operator==(const BigInt &left, const BigInt &right) -> bool;
/**
 * Returns boolean indicating if `left` has a different value from `right`.
 *
 * @param left BigInt to be compared with `right`
 * @param right BigInt to be compared with `left`
 * @return true if `left` has a different value as `right`, false if they have
 * the same value
 */
auto operator!=(const BigInt &left, const BigInt &right) -> bool;
/**
 * Returns boolean indicating if `left` has a smaller value than `right`.
 *
 * @param left BigInt to be compared with `right`
 * @param right BigInt to be compared with `left`
 * @return true if `left` has a smaller value than `right`, otherwise false
 */
auto operator<(const BigInt &left, const BigInt &right) -> bool;
/**
 * Returns boolean indicating if `left` has a greater value than `right`.
 *
 * @param left BigInt to be compared with `right`
 * @param right BigInt to be compared with `left`
 * @return true if `left` has a greater value than `right`, otherwise false
 */
auto operator>(const BigInt &left, const BigInt &right) -> bool;
/**
 * Returns boolean indicating if `left` has a smaller or equal value to `right`.
 *
 * @param left BigInt to be compared with `right`
 * @param right BigInt to be compared with `left`
 * @return true if `left` has a smaller or equal value to `right`, otherwise
 * false
 */
auto operator<=(const BigInt &left, const BigInt &right) -> bool;
/**
 * Returns boolean indicating if `left` has a greater or equal value to `right`.
 *
 * @param left BigInt to be compared with `right`
 * @param right BigInt to be compared with `left`
 * @return true if `left` has a greater or equal value to `right`, otherwise
 * false
 */
auto operator>=(const BigInt &left, const BigInt &right) -> bool;

/**
 * Namespace that allows users to construct a BigInt using a user-defined
 * literal
 */
inline namespace literals {

/**
 * User-defined literal that allows users to construct a BigInt.
 *
 * Ex:
 * BigInt num = 123_b;
 * See
 * https://stackoverflow.com/questions/49054477/how-to-refer-to-user-defined-literal-operator-inside-a-namespace
 */
auto operator"" _b(const char *s) -> BigInt;
} // namespace literals

} // namespace BigInt

#endif
