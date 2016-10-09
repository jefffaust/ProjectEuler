/*
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/

#include "MathUtils.h"
#include "TestUtils.h"

#include <array>

std::array<int, 10> createHistogram(unsigned int n)
{
	std::array<int, 10> digits = { 0 };
	forEachDigit(n, [&digits](int d) {
		++digits[d];
	});
	return digits;
}

int main()
{
	assert(createHistogram(125874) == createHistogram(2 * 125874));

	START_TIMER;

	unsigned int x = 142857;
	for (unsigned int x = 1; ; ++x)
	{
		auto histX = createHistogram(x);
		for (int m = 2; m <= 6; ++m)
		{
			if (histX != createHistogram(m*x)) break;
			if( m == 6 ) return result(142857, x);
		}
	}
}
