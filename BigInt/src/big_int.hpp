#ifndef BIG_INT_H
#define BIG_INT_H

#include <ostream>
#include <string>
#include <vector>

class BigInt {
	public:
		// Constructors
		BigInt(const std::string &num);		// takes in a string of digits, in base 10
		BigInt(const long long num);

		// Overloaded unary operators
		BigInt operator -() const;			// Return a negative version

		// helper functions
		BigInt clone() const;				// return a copy
		std::string str() const;			// return string representation of the bigint

		// friend functions
		friend std::ostream& operator<<(std::ostream &out, const BigInt &integer);		// Outputting a BigInt
		friend BigInt operator "" _b(const char* s);	// user defined literal: can use as "BigInt num = 123_b;"
		friend BigInt operator +(const BigInt &left, const BigInt &right);	// add two bigints
		friend BigInt operator -(const BigInt &left, const BigInt &right);	// subtract two bigints
		friend BigInt operator *(const BigInt &left, const BigInt &right);	// multiply two bigints

		// static functions
		static int compare(const BigInt &left, const BigInt &right);		// -1 if left < right; 0 if left == right, and 1 if left > right

	private:
		bool negative;
		std::vector<int> digits;
		const static int digitsPerBucket = 9;
		const static int bucketMod = 1000000000;

		BigInt(bool negative_, std::vector<int> digits_);

		void normalizeDigits();				// Remove leading 0's; if no digits, initialize as 0; change -0 to 0
		bool isZero() const;				// check if number is 0
		bool isPos() const;					// check if number is positive
		bool isNeg() const;					// check if number is negative
		static BigInt halfAdd(const BigInt &left, const BigInt &right);  // add two non-negative bigints
		static BigInt halfSubtract(const BigInt &left, const BigInt &right);	// subtract smaller from bigger
		static BigInt multiplyNaive(const BigInt &left, const BigInt &right);	// grade-school multiplication
		static BigInt multiplyKaratsuba(const BigInt &left, const BigInt &right);	 // Karatsuba multiplication
		static BigInt multiplyKaratsubaHelper(const BigInt &left, const BigInt &right);	 // Karatsuba multiplication
		void printInternal() const;			// show internal information for debugging
};

// declare function so any file that uses this header can see it
// (friend does not bring it into scope)
bool operator ==(const BigInt &left, const BigInt &right);	// comparison
bool operator !=(const BigInt &left, const BigInt &right);
bool operator <(const BigInt &left, const BigInt &right);
bool operator >(const BigInt &left, const BigInt &right);
bool operator <=(const BigInt &left, const BigInt &right);
bool operator >=(const BigInt &left, const BigInt &right);
BigInt operator "" _b(const char* s);

#endif
