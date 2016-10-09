/*
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

#include "TestUtils.h"

#include <vector>

int main()
{
	START_TIMER;
	unsigned int longestSequence = 0;
	unsigned int dWithLongestSequence = 0;
	std::vector<short> dividends;
	for( unsigned int d = 2; d < 1000; ++d, dividends.clear() )
	{
		// The key to finding a repeating sequence is to find when the first dividend repeats in the process of grade
		// school long division. We don't need to keep track of the actual result of the division at all.

		// The first remainder is the numerator
		unsigned short dividend = 10;

		// Find the right starting dividend.
		while( dividend < d )
		{
			dividend *= 10;
		}

		// The idea here is to loop until we find a matching dividend.
		std::vector<short>::iterator iter = dividends.end();
		while( iter == dividends.end() && dividend != 0 )
		{
			dividends.push_back(dividend);
			dividend = dividend % d * 10;

			// A std::set would allow a faster search, but std::vector is probably still faster overall since we
			// don't typically have long sequences.
			iter = std::find(dividends.begin(), dividends.end(), dividend);
		}

		// The sequence may not start after the decimal, so calculate from iter.
		unsigned int sequence = std::distance(iter, dividends.end());

		// remember the longest
		if( sequence > longestSequence )
		{
			longestSequence = sequence;
			dWithLongestSequence = d;
		}
	}

	return result(983, dWithLongestSequence);
}
