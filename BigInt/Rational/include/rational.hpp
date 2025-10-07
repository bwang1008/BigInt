#ifndef RATIONAL_HPP
#define RATIONAL_HPP // NOLINT(clang-diagnostic-unused-macros)

#include "BigInt/BigInt/include/big_int.hpp"

#include <ostream>
#include <string>

namespace BigInt {

/**
 * Class that represents rational numbers.
 *
 * These numbers are stored as holding two BigInts, the numerator and the
 * denominator. The values of the numerator and denominator that are stored
 * should be relatively prime.
 */
class Rational {
  public:
    /**
     * Default constructor that holds the rational number of 0.
     */
    Rational();
    /**
     * Constructor that creates a Rational number representing the integer
     * `numerator_`.
     *
     * @param numerator_ int whose value the Rational number should have
     */
    explicit Rational(int numerator_);
    /**
     * Constructor that creates a Rational number representing the integer
     * `numerator_`.
     *
     * @param numerator_ BigInt whose value the Rational number should have
     */
    explicit Rational(const BigInt &numerator_);
    /**
     * Constructor that creates a Rational number with given numerator and
     * denominator.
     *
     * @param numerator_ value of numerator the Rational number should have,
     * subject to reducing by gcd
     * @param denominator_ value of denominator the Rational number should have,
     * subject to reducing by gcd. If 0 is provided, then std::invalid_argument
     * will be thrown
     */
    Rational(int numerator_, int denominator_);
    /**
     * Constructor that creates a Rational number with given numerator and
     * denominator.
     *
     * @param numerator_ BigInt value of numerator the Rational number should
     * have, subject to reducing by gcd
     * @param denominator_ BigInt value of denominator the Rational number
     * should have, subject to reducing by gcd. If 0 is provided, then
     * std::invalid_argument will be thrown
     */
    Rational(const BigInt &numerator_, const BigInt &denominator);

    /**
     * Return numerator of Rational number.
     *
     * @return numerator of current Rational number
     */
    [[nodiscard, gnu::pure]] auto get_numerator() const -> BigInt;
    /**
     * Return denominator of Rational number.
     *
     * @return denominator of current Rational number
     */
    [[nodiscard, gnu::pure]] auto get_denominator() const -> BigInt;
    /**
     * String representation of Rational number.
     *
     * @return string of numerator, concatted with forward slash, concatted with
     * denominator
     */
    [[nodiscard, gnu::pure]] auto str() const -> std::string;

    /**
     * Friend function overload of << that allows printing of Rational number.
     *
     * Ex:
     * BigInt::Rational x{5, 3};
     * std::cout << x;
     * @param out output stream, such as std::cout from <iostream>
     * @param integer Rational to be outputted
     * @return reference to `out` parameter
     */
    friend auto operator<<(std::ostream &out, const Rational &r)
        -> std::ostream &;
    /**
     * Adds two Rational numbers.
     *
     * @param left First Rational to be added with
     * @param right Second Rational to be added with
     * @return sum of `left` and `right`
     */
    friend auto operator+(const Rational &left, const Rational &right)
        -> Rational;
    /**
     * Subtracts two Rational numbers.
     *
     * @param left Rational to be subtracted from
     * @param right Rational amount to subtract from `left`
     * @return the difference between `left` and `right`
     */
    friend auto operator-(const Rational &left, const Rational &right)
        -> Rational;
    /**
     * Multiplies two Rational numbers.
     *
     * @param left First Rational to be multiplied with
     * @param right Second Rational to be multiplied with `left`
     * @return product of `left` and `right`
     */
    friend auto operator*(const Rational &left, const Rational &right)
        -> Rational;
    /**
     * Divides two Rational numbers.
     *
     * @param left First Rational to be divided
     * @param right Rational amount that `left` should be divided by. If 0 is
     * provided, then std::invalid_argument will be thrown
     * @return division of `left` with `right`
     */
    friend auto operator/(const Rational &left, const Rational &right)
        -> Rational;

    /**
     * Update the current Rational value to be the sum of itself with `right`.
     *
     * @param right amount to add to current Rational value
     * @return reference to current Rational
     */
    auto operator+=(const Rational &right) -> Rational &;
    /**
     * Update the current Rational value to subtract the amount by `right`.
     *
     * @param right amount to subtract from current Rational value
     * @return reference to current Rational
     */
    auto operator-=(const Rational &right) -> Rational &;
    /**
     * Update the current Rational value to be product of itself with `right`.
     *
     * @param right amount to multiply by current Rational value
     * @return reference to current Rational
     */
    auto operator*=(const Rational &right) -> Rational &;
    /**
     * Update the current Rational value to be division of itself with `right`.
     *
     * @param right amount to divide the current Rational value by. If 0 is
     * provided, then std::invalid_argument will be thrown
     * @return reference to current Rational
     */
    auto operator/=(const Rational &right) -> Rational &;

    /**
     * Returns boolean indicating if `left` has a smaller value than `right`.
     *
     * @param left Rational to be compared with `right`
     * @param right Rational to be compared with `left`
     * @return true if `left` has a smaller value than `right`, otherwise false
     */
    friend auto operator<(const Rational &r1, const Rational &r2) -> bool;
    /**
     * Returns boolean indicating if `left` has a smaller or equal value to
     * `right`.
     *
     * @param left Rationl to be compared with `right`
     * @param right Rational to be compared with `left`
     * @return true if `left` has a smaller or equal value to `right`, otherwise
     * false
     */
    friend auto operator<=(const Rational &r1, const Rational &r2) -> bool;
    /**
     * Returns boolean indicating if `left` has a greater value than `right`.
     *
     * @param left Rational to be compared with `right`
     * @param right Rational to be compared with `left`
     * @return true if `left` has a greater value than `right`, otherwise false
     */
    friend auto operator>(const Rational &r1, const Rational &r2) -> bool;
    /**
     * Returns boolean indicating if `left` has a greater or equal value to
     * `right`.
     *
     * @param left Rational to be compared with `right`
     * @param right Rational to be compared with `left`
     * @return true if `left` has a greater or equal value to `right`, otherwise
     * false
     */
    friend auto operator>=(const Rational &r1, const Rational &r2) -> bool;
    /**
     * Returns boolean indicating if `left` has the same value as `right`.
     *
     * @param left Rational to be compared with `right`
     * @param right Rational to be compared with `left`
     * @return true if `left` has the same value as `right`, otherwise false
     */
    friend auto operator==(const Rational &r1, const Rational &r2) -> bool;
    /**
     * Returns boolean indicating if `left` has a different value from `right`.
     *
     * @param left Rational to be compared with `right`
     * @param right Rational to be compared with `left`
     * @return true if `left` has a different value as `right`, false if they
     * have the same value
     */
    friend auto operator!=(const Rational &r1, const Rational &r2) -> bool;

    /**
     * Static method that adds two Rational numbers.
     *
     * @param left First Rational to be added with
     * @param right Second Rational to be added with
     * @return sum of `left` and `right`
     */
    [[nodiscard, gnu::pure]] static auto add(const Rational &left,
                                             const Rational &right) -> Rational;
    /**
     * Static method that subtracts two Rational numbers.
     *
     * @param left Rational to be subtracted from
     * @param right Rational amount to subtract from `left`
     * @return the difference between `left` and `right`
     */
    [[nodiscard, gnu::pure]] static auto subtract(const Rational &left,
                                                  const Rational &right)
        -> Rational;
    /**
     * Static method that multiplies two Rational numbers.
     *
     * @param left First Rational to be multiplied with
     * @param right Second Rational to be multiplied with `left`
     * @return product of `left` and `right`
     */
    [[nodiscard, gnu::pure]] static auto multiply(const Rational &left,
                                                  const Rational &right)
        -> Rational;
    /**
     * Static method that divides two Rational numbers.
     *
     * @param left First Rational to be divided
     * @param right Rational amount that `left` should be divided by. If 0 is
     * provided, then std::invalid_argument will be thrown
     * @return division of `left` with `right`
     */
    [[nodiscard, gnu::pure]] static auto divide(const Rational &left,
                                                const Rational &right)
        -> Rational;

  private:
    /// @brief Numerator of the fraction this Rational represents
    BigInt numerator;
    /// @brief Denominator of the fraction this Rational represents
    BigInt denominator;
};

} // namespace BigInt

#endif
