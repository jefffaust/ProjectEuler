/*
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

#include "TestUtils.h"

#include <vector>

size_t collatz(size_t n)
{
	return n % 2 == 0 ? n/2 : 3*n + 1;
}

size_t collatzLength(size_t n)
{
	// Remember previous lengths. We can expect most numbers to be < 1 million, but common to go
	// up to 3 million. Many will go above, but will be repeated less. This caching of previous
	// values results in about a 10x improvement in speed.
	static std::vector<size_t> lengths(3000000);

	if( n == 1 )
	{
		// base recursion case
		return 0;
	}

	// If we already calculated this length, return it.
	if( n < lengths.size() && lengths[n] != 0 )
	{
		return lengths[n];
	}

	// recurse. We could make it faster with an iterative solution, but recursion is fun.
	const size_t len = 1 + collatzLength(collatz(n));

	// Remember length for next time if < 3 million
	return ( n < lengths.size() ) ? lengths[n] = len : len;
}

int main()
{
	START_TIMER;
	size_t answer = 0;
	size_t maxLen = 0;
	for( size_t n = 1; n < 1000000; ++n )
	{
		size_t len = collatzLength(n);
		if( len > maxLen )
		{
			answer = n;
			maxLen = len;
		}
	}

	return result(837799, answer);
}
