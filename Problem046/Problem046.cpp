/*
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×1^2
15 = 7 + 2×2^2
21 = 3 + 2×3^2
25 = 7 + 2×3^2
27 = 19 + 2×2^2
33 = 31 + 2×1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
*/

#include "TestUtils.h"
#include "Primes.h"

int main()
{
	START_TIMER;

	const Primes& primes = Primes::get();

	for( unsigned int n = 3; ; n += 2 )
	{
		if( primes.isPrime(n) ) continue; // we only care about composites

		// Since squares grow so fast, let's iterate over them, subtract 2i^2 from n and see if the result is prime.
		// Either we will find a prime, orwe have found our smallest n once 2i^2 grows larger than n.
		for( unsigned int i = 1; ; ++i )
		{
			unsigned int i2 = 2 * i * i;
			if( i2 > n )
			{
				// n cannot be written as p + 2i^2
				return result(5777, n);
			}

			unsigned int p = n - i2;
			if( primes.isPrime(p) )
			{
				// n can be written as p + 2i^2
				//std::cout << n << " = " << p << " + 2*" << i << "^2" << std::endl;
				break;
			}
		}
	}
}
