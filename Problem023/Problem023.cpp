/*
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the
proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant
numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two
abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest
number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include <vector>

int main()
{
	START_TIMER;

	auto isAbundant = [] (unsigned int n) { return sumDivisors(n) > n; };

	// Identify all the abundants
	std::vector<unsigned int> abundants;
	const unsigned int upper = 28123;
	for( unsigned int i = 1; i <= upper; ++i )
	{
		if( isAbundant(i) ) abundants.push_back(i);
	}

	// find all perfect sums
	std::vector<bool> perfectSums(upper, false);
	for( auto iter1 = abundants.begin(); iter1 != abundants.end(); ++iter1 )
	{
		for( auto iter2 = iter1; iter2 != abundants.end(); ++iter2 )
		{
			auto curSum = *iter1 + *iter2;
			if( curSum > upper ) break;
			perfectSums[curSum] = true;
		}
	}

	// sum everything that is not a perfect sum
	unsigned int answer = 0;
	for( size_t i = 0; i < perfectSums.size(); ++i )
	{
		if( !perfectSums[i] ) answer += i;
	}

	return result(4179871, answer);
}
