/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

#include "TestUtils.h"
#include "Primes.h"

#include <vector>

// Here is a simple solution.  The idea is to account for all the prime factors for each number.
int penAndPaper()
{
	// We know that all the primes < 20 will be factors.
	int result = 2*3*5*7*11*13*17*19;

	result *= 2; // 4 needs another 2

	result *= 2; // 8 needs a third 2

	result *= 3; // 9 needs another 3

	result *= 2; // 16 needs a 4th 2

	return result;
}

void addTo(std::vector<int>& primeFactors1, const std::vector<int>& primeFactors2)
{
	primeFactors1.resize(std::max(primeFactors1.size(), primeFactors2.size()));
	for( size_t i = 0; i < primeFactors2.size(); ++i )
	{
		primeFactors1[i] = std::max(primeFactors1[i], primeFactors2[i]);
	}
}

size_t expandPrimeFactors(const std::vector<int>& primeFactors)
{
	size_t result = 1;
	const Primes& primes = Primes::get();
	for( size_t n = 0; n < primeFactors.size(); ++n )
	{
		size_t p = primes.nthPrime(n+1);
		for( int i = 0; i < primeFactors[n]; ++i )
		{
			result *= p;
		}
	}

	return result;
}

int algorithmic(size_t upTo)
{
	const Primes& primes = Primes::get();
	std::vector<int> primeFactors;

	for( size_t i = 2; i <= upTo; ++i )
	{
		addTo(primeFactors, primes.primeFactors(i));
	}

	return expandPrimeFactors(primeFactors);
}

int main()
{
	START_TIMER;
	//return result(232792560, penAndPaper());
	return result(232792560, algorithmic(20));
}
