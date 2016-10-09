/*
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/

#include "MathUtils.h"
#include "TestUtils.h"

unsigned int sum5thPowerDigits(unsigned int i)
{
	unsigned int sum = 0;
	forEachDigit(i, [&sum](int d) { sum += d*d*d*d*d; });
	return sum;
}

int main()
{
	START_TIMER;
	unsigned int sum = 0;

	// I chose an upper bound by trial-and-error. How do you analytically choose it?
	for( int i = 10; i < 1000000; ++i )
	{
		if( sum5thPowerDigits(i) == i )
		{
			sum += i;
		}
	}

	return result(443839, sum);
}
