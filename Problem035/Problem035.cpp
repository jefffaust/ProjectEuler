/*
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?
*/

#include "TestUtils.h"
#include "Primes.h"

unsigned int rotate(unsigned int n, unsigned int pow10)
{
	return n/10 + (n%10)*pow10;
}

bool isCircularPrime(unsigned int n, unsigned int pow10)
{
	const Primes& primes = Primes::get();
	for( int rn = rotate(n, pow10); rn != n; rn = rotate(rn, pow10) )
	{
		if( !primes.isPrime(rn) )
		{
			return false;
		}
	}

	return true;
}

int main()
{
	START_TIMER;
	int count = 0;
	const Primes& primes = Primes::get();

	unsigned int p = 2;
	unsigned int n = 1;
	for( unsigned int pow10 = 1; pow10 < 1e6; pow10 *= 10 )
	{
		do
		{
			if( isCircularPrime(p, pow10) )
			{
				++count;
			}
		} while( (p = primes.nthPrime(++n)) < pow10*10 );
	}

	return result(55, count);
}
