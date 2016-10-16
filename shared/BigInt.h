#pragma once

#include <boost/operators.hpp>

#include <iosfwd>
#include <deque>
#include <string>

#define implicit /*explicit*/

class BigInt : public boost::operators<BigInt>
{
	// safe bool idiom
	typedef void (BigInt::*bool_type)() const;
	void this_type_does_not_support_comparisons() const {}

public:
	BigInt();
	implicit BigInt(long long i);

	BigInt& operator=(long long i);

	// Construct with a string of digits.
	explicit BigInt(const std::string& str);

	// Comparison
	bool operator==(const BigInt& rhs) const;
	bool operator<(const BigInt& rhs) const;

	operator bool_type() const { return m_value.empty() ? nullptr : &BigInt::this_type_does_not_support_comparisons; }

	// returns the number of digits
	unsigned long long numDigits() const;

	// Addition
	BigInt& operator+=(const BigInt& rhs);
	BigInt& operator+=(long long rhs) { return operator+=(BigInt(rhs)); }

	// Multiplication
	BigInt& operator*=(BigInt rhs);
	BigInt& operator*=(long long rhs) { return operator*=(BigInt(rhs)); }

	// Integer division -- currently can't divide by BigInt.
	BigInt& operator/=(long long rhs);
 	BigInt operator/(long long rhs) const { return BigInt(*this) /= rhs; }

	// Modulo -- currently can't mod by BigInt
	BigInt& operator%=(long long rhs);
	long long operator%(long long rhs) const;

	friend std::ostream& operator<<(std::ostream& ostr, const BigInt& i);

	// We can use 19 digits per value, although we only use 18 to simplify some operations.
	typedef unsigned long long InternalType;

private:
	// shifts digits, remove leading zero values, etc. Should be done internally after every operation.
	// Returns *this for convenience.
	BigInt& normalize();

	// halves m_digitsPerValue to allow room for multiplication
	void spread();

	// undo spread()
	void squeeze();

	std::deque<InternalType> m_value;
	int m_digitsPerValue;
	InternalType m_maxValue;
	//int m_sign;
};

bool operator==(const BigInt& lhs, int rhs);
inline BigInt operator+(long long i, const BigInt& rhs) { return rhs + i; }
inline bool operator<(long long i, const BigInt& rhs) { return BigInt(i) < rhs; }
inline bool operator<=(long long i, const BigInt& rhs) { return BigInt(i) <= rhs; }
inline bool operator>(long long i, const BigInt& rhs) { return BigInt(i) > rhs; }
inline bool operator>=(long long i, const BigInt& rhs) { return BigInt(i) >= rhs; }

// bigpow is based on https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Basic_method
BigInt bigpow(unsigned int b, unsigned int p);
