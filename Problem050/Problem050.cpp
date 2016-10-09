/*
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?
*/

#include "TestUtils.h"
#include "Primes.h"

int main()
{
	START_TIMER;
	// We know the the number of terms > 21. If 22, the average value for a prime around 1000000 would be
	// about 45000.  As we find a newer max consecutive counts, we could use a newer maxPrime value, but we
	// don't because it's faster to do the extra iteration than the extra division.
	const unsigned int maxSum = 1000000;
	const Primes& primes = Primes::get();
	unsigned int maxConsecutiveCount = 22;
	unsigned int answer = 0;
	unsigned int maxPrime = maxSum / maxConsecutiveCount;
	primes.isPrime(1000000); // a bit faster to precompute

	for( unsigned int startingN = 1; primes.nthPrime(startingN) < maxPrime; ++startingN )
	{
		unsigned int sum = 0;
		unsigned int consecutiveCount = 0;
		for( unsigned int n = startingN; sum < maxSum; ++n, ++consecutiveCount, sum += primes.nthPrime(n) )
		{
			if( consecutiveCount > maxConsecutiveCount && primes.isPrime(sum) )
			{
				answer = sum;
				maxConsecutiveCount = consecutiveCount;
				// This actually makes it slower
				//maxPrime = maxSum / maxConsecutiveCount;
			}
		}
	}

	return result(997651, answer);
}
