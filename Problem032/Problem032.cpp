/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
*/

#include "MathUtils.h"
#include "TestUtils.h"

#include <algorithm>
#include <numeric>
#include <vector>

// returns product if pandigital, 0 otherwise.
int pandigital(int i, int j)
{
	int digits[10] = {0};
	auto accumulateDigits = [&digits] (int d) { ++digits[d]; };
	forEachDigit(i, accumulateDigits);
	forEachDigit(j, accumulateDigits);
	forEachDigit(i*j, accumulateDigits);

	if( digits[0] ) return 0;
	for( int k = 1; k < 10; ++k )
	{
		if( digits[k] != 1 )
		{
			return 0;
		}
	}

	return i*j;
}

std::vector<int> s_panset;
void includeif(int pan)
{
	// std::find on a vector may be slow, but the vast majority of cases are going to be 0, so it doesn't really matter.
	if( pan > 0 && std::find(s_panset.begin(), s_panset.end(), pan) == s_panset.end() )
	{
		s_panset.push_back(pan);
	}
}

int main()
{
	START_TIMER;

	// In order to use all 9 digits, we can restrict our search to 2-digit * 3-digit and 1-digit * 4-digit.

	int sum = 0;

	// handle 2 and 3 digit products
	for( int i = 10; i < 100; ++i )
	{
		for( int j = 100; j < 1000; ++j )
		{
			includeif(pandigital(i, j));
		}
	}

	// handle 1 and 4 digit products
	for( int i = 1; i < 10; ++i )
	{
		for( int j = 1000; j < 10000; ++j )
		{
			includeif(pandigital(i, j));
		}
	}

	return result(45228, std::accumulate(s_panset.begin(), s_panset.end(), 0));
}
