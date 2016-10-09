/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143?
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include "Primes.h"

int main()
{
	START_TIMER;
	const Primes& primes = Primes::get();
	unsigned int p = 1;
	const unsigned long long max = sqrt(600851475143ULL) + 1;
	unsigned int maxFactor = 1;
	for( int n = 1; p < max; ++n )
	{
		p = primes.nthPrime(n);
		if( 600851475143 % p == 0 )
		{
			maxFactor = p;
		}
	}

	return result(6857, maxFactor);
}
