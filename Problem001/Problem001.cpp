/*
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/

#include "TestUtils.h"

#include <boost/array.hpp>

int main()
{
	START_TIMER;

	// Use a version of the Sieve of Eratosthenes, something we'll see in later problems.
	boost::array<bool, 1000> multiples = {false};
	for( int i = 3; i < 1000; i += 3 ) multiples[i] = true;
	for( int i = 5; i < 1000; i += 5 ) multiples[i] = true;

	// Sum up all multiples
	unsigned int sum = 0;
	for( int i = 0; i < 1000; ++i )
	{
		if( multiples[i] )
		{
			sum += i;
		}
	}

	return result(233168, sum);
}
