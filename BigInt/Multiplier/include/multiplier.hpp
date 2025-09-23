#ifndef MULTIPLIER_HPP
#define MULTIPLIER_HPP // NOLINT(clang-diagnostic-unused-macros)

#include "BigInt/BigInt/include/big_int.hpp"

namespace BigInt {

/**
 * Base class of all multiplication methods.
 */
class Multiplier {
  public:
    /**
     * Main multiplication method of two BigInt that users seee.
     *
     * This function is a wrapper around multiply_positive that handles negative
     * and 0 cases of the two inputs first.
     * @param left First BigInt to be multiplied with
     * @param right Second BigInt to be multiplied with left
     * @return product of left and right
     */
    auto multiply(const BigInt &left, const BigInt &right) -> BigInt;

    /**
     * Copy assignment operator.
     *
     * @param other Multiplier object to copy
     * @return existing object
     */
    auto operator=(const Multiplier &other) -> Multiplier & = default;

    /**
     * Copy constructor.
     *
     * @param other Multiplier object to copy
     */
    Multiplier(const Multiplier &other) = default;

    /**
     * Move assignment operator.
     *
     * @param other Multiplier rvalue reference to move to current object
     * @return existing object
     */
    auto operator=(Multiplier &&other) -> Multiplier & = default;

    /**
     * Move constructor.
     *
     * @param other Multiplier rvalue reference to construct object out of
     */
    Multiplier(Multiplier &&other) = default;

    /**
     * Destructor.
     *
     * Classes with virtual methods must have a virtual destructor.
     */
    virtual ~Multiplier() = default;

  protected:
    /**
     * Multiplies two nonnegative BigInts.
     *
     * Must be overrided by subclasses of Multiplier.
     * @param left First BigInt to be multiplied with. Must be positive.
     * @param right Second BigInt to be multiplied with right. Must be
     * positive.
     * @return product of left and right
     */
    virtual auto multiply_positive(const BigInt &left, const BigInt &right)
        -> BigInt = 0;
};

class GradeSchoolMultiplier : public Multiplier {
  protected:
    /**
     * Multiplies two nonnegative BigInts using grade-school algorithm.
     *
     * @param left First BigInt to be multiplied with. Must be positive.
     * @param right Second BigInt to be multiplied with right. Must be
     * positive.
     * @return product of left and right
     */
    BigInt multiply_positive( // NOLINT(modernize-use-trailing-return-type)
        const BigInt &left, const BigInt &right) override;
};

} // namespace BigInt

#endif
