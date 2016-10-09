#pragma once

#include <boost/noncopyable.hpp>
#include <vector>

class Primes : boost::noncopyable
{
public:
	static const Primes& get();

	// returns true if the given number is prime
	bool isPrime(size_t n) const;

	// returns the nth prime
	unsigned int nthPrime(size_t n) const;

	// returns the prime factors where each index is the nthPrime() and each value is how many factors of that prime.
	std::vector<int> primeFactors(size_t v) const;

private:
	Primes();

	void grow(size_t minN) const;
	void sieve(unsigned int start, unsigned int p) const;

	// unknown state means it has not been evaluated as prime or not.
	mutable std::vector<bool> m_isPrime;
	mutable std::vector<unsigned int> m_primes;
};
