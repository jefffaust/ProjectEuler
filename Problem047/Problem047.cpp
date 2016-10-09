/*
The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers?
*/

#include "TestUtils.h"
#include "Primes.h"

#include <algorithm>

bool hasFourDistinctPrimeFactors(unsigned int n)
{
	auto factors = Primes::get().primeFactors(n);
	return std::count_if(factors.begin(), factors.end(), [](unsigned int f) { return f > 0; }) == 4;
}

int main()
{
	START_TIMER;

	unsigned int consecutiveIntegers = 0;
	for( unsigned int n = 1; ; ++n )
	{
		if( hasFourDistinctPrimeFactors(n) )
		{
			if( ++consecutiveIntegers == 4 )
			{
				return result(134043, n - 3);
			}
		}
		else
		{
			consecutiveIntegers = 0;
		}
	}
}
