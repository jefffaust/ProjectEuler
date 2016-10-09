/*
Euler discovered the remarkable quadratic formula:

n^2 + n + 41
It turns out that the formula will produce 40 primes for the consecutive integer values 0≤n≤39.
However, when n=40, 40^2+40+41 = 40(40+1)+41 is divisible by 41, and certainly when n=41, 41^2+41+41n is clearly divisible by 41.

The incredible formula n^2−79n+1601 was discovered, which produces 80 primes for the consecutive values 0≤n≤79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

n^2+an+b, where |a|<1000 and |b|≤1000

where |n| is the modulus/absolute value of n
e.g. |11|=11 and |−4|=4
Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n=0.
*/

#include "TestUtils.h"
#include "Primes.h"

#include <cassert>
#include <vector>

int countPrimesGenerated(int a, int b)
{
	const Primes& primes = Primes::get();
	int count = 0;
	for( int n = 0;; ++n )
	{
		int result = n*n + a*n + b;

		// return the count at the first non-prime.
		if( result < 0 || !primes.isPrime(result) )
		{
			return count;
		}

		++count;
	}

	assert(0 && "Should never get here");
	return 0;
}

int main()
{
	START_TIMER;

	int answer = 0;
	int maxCount = 0;

	// Check all values of a and b.
	for( int a = -999; a <= 999; ++a )
	{
		for( int b = -1000; b <= 1000; ++b )
		{
			// Remember largest count.
			int count = countPrimesGenerated(a, b);
			if( count > maxCount )
			{
				maxCount = count;
				answer = a * b;
			}
		}
	}

	return result(-59231, answer);
}
