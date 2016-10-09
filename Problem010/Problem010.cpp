/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

#include "TestUtils.h"
#include "Primes.h"

int main()
{
	START_TIMER;
	const Primes& primes = Primes::get();

	// Simply sum up all the primes.
	unsigned long long sum = 2;
	for( int i = 3; i < 2000000; i += 2 )
	{
		// Use isPrime instead of nthPrime as nthPrime will expand the sequence past 2 million to make
		// sure it gets the last one.
		if( primes.isPrime(i) )
		{
			sum += i;
		}
	}

	return result(142913828922ULL, sum);
}
