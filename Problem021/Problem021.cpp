/*
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper
divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/

#include "MathUtils.h"
#include "TestUtils.h"

#include <vector>

int main()
{
	START_TIMER;
	std::vector<unsigned int> d(10001, 0);
	d[1] = 1;

	// calculate d for each number
	for( unsigned int a = 2; a <= 10000; ++a )
	{
		d[a] = sumDivisors(a);
	}

	// Find each amicable pair.
	unsigned int answer = 0;
	for( unsigned int a = 2; a < 10000; ++a )
	{
		const unsigned int b = d[a];
		if( b <= 10000 && b != a && d[b] == a )
		{
			answer += a;
		}
	}

	return result(31626, answer);
}
