/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include "Primes.h"

#include <numeric>

bool isPandigital(unsigned int n)
{
	int digits[10] = {0};
	auto accumulateDigits = [&digits] (int d) { ++digits[d]; };
	forEachDigit(n, accumulateDigits);

	if( digits[0] ) return false; // no zeros allowed
	if( digits[1] != 1 ) return false; // not pandigital

	for( int i = 2; i < 10; ++i )
	{
		if( digits[i] > 1 ) return false; // repeated digits
		if( digits[i] == 0 )
		{
			// must ensure rest are 0
			return std::accumulate(digits + i + 1, digits + 10, 0) == 0;
		}
	}

	return true;
}

// 16 seconds

int main()
{
	START_TIMER;
	unsigned int p = 1;
	const Primes& primes = Primes::get();
	unsigned int maxPan = 0;

	// After I implemented using the following max, I learned about the "divisibility rule" for number: If the sum of the digits
	// is divisible by 3, then the number is divisible by 3.  https://en.wikipedia.org/wiki/Divisibility_rule
	// Any combination of 12345678 (sum == 36) or 123456789 (sum == 45) is divisible by three, so can't be prime. Therefor, we only
	// need to check up to 7-digit primes. This is good because the original max ran in 16 seconds. The new one is ~150 ms.
	//unsigned int max = 987654321;
	const unsigned int max = 7654321;
	for( unsigned int n = 1; p < max; ++n )
	{
		p = primes.nthPrime(n);
		if( isPandigital(p) )
		{
			maxPan = p;
		}
	}

	return result(7652413, maxPan);
}
