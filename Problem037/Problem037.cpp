/*
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and
remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include "Primes.h"

template<typename T, typename F>
bool truncatable(T n, F f)
{
	const Primes& primes = Primes::get();
	for( f(n); n; f(n) )
	{
		if( !primes.isPrime(n) )
		{
			return false;
		}
	}

	return true;
}

template<typename T>
bool leftTruncatablePrime(T n)
{
	return truncatable(n, truncateLeft<T>);
}

template<typename T>
bool rightTruncatablePrime(T n)
{
	return truncatable(n, truncateRight<T>);
}

template<typename T>
bool truncatablePrime(T n)
{
	// check if it's both left- and right-truncatable
	return rightTruncatablePrime(n) && leftTruncatablePrime(n);
}

int main()
{
	START_TIMER;
	assert(truncatablePrime(3797));

	const Primes& primes = Primes::get();
	unsigned int n = 5; // skip to 5th prime: 11--see problem description
	unsigned int sum = 0;
	for( int found = 0; found != 11; ++n )
	{
		unsigned int p = primes.nthPrime(n);
		if( truncatablePrime(p) )
		{
			sum += p;
			++found;
		}
	}

	return result(748317, sum);
}
