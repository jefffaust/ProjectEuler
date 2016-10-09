/*
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/

#include "MathUtils.h"
#include "TestUtils.h"

#include <cassert>

unsigned int fact[] =
{
	1,
	1,
	2,
	3 * 2,
	4 * 3 * 2,
	5 * 4 * 3 * 2,
	6 * 5 * 4 * 3 * 2,
	7 * 6 * 5 * 4 * 3 * 2,
	8 * 7 * 6 * 5 * 4 * 3 * 2,
	9 * 8 * 7 * 6 * 5 * 4 * 3 * 2
};

bool curiousNumber(unsigned int n)
{
	unsigned int sumFactDig = 0;
	forEachDigit(n, [&sumFactDig] (unsigned short d) { sumFactDig += fact[d]; });
	return sumFactDig == n;
}

int main()
{
	START_TIMER;
	assert(curiousNumber(145));
	unsigned int sum = 0;

	// After getting the answer, I know the upper limit is much lower, but that would be cheating...
	// Upper limit chosen because 7 * 9! < 9999999
	for( unsigned int n = 10; n <= 9999999; ++n )
	{
		if( curiousNumber(n) )
		{
			sum += n;
		}
	}

	return result(40730, sum);
}
