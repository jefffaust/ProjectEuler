/*
A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost 
unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
*/

#include "BigInt.h"
#include "MathUtils.h"
#include "TestUtils.h"

int main()
{
	START_TIMER;

	unsigned int answer = 0;
	for (int a = 1; a < 100; ++a)
	{
		for (int b = 1; b < 100; ++b)
		{
			answer = std::max(answer, sumDigits(bigpow(a, b)));
		}
	}

	return result(972, answer);
}
