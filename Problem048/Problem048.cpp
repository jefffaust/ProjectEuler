/*
The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
*/

#include "BigInt.h"
#include "TestUtils.h"

// bigpow is based on https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Basic_method
// But since we need only the last 10 digits, we can trim off all leading digits each iteration.
// This saves a lot of computation:
// Without trimming: 270 seconds
// With trimming: 130 ms
// Using unsigned long long almost works, but fails during iteration for 16^16, for example.
BigInt bigpow(unsigned int b, unsigned int p, unsigned long long trim = 0)
{
	BigInt answer(1);
	if( p == 0 ) return answer;
	BigInt bb(b);
	while( p > 1 )
	{
		if( p % 2 == 0 )
		{
			bb *= bb;
			p /= 2;
		}
		else
		{
			answer *= bb;
			bb *= bb;
			p = (p-1)/2;
		}

		if( trim )
		{
			answer %= trim;
			bb %= trim;
		}
	}
	answer *= bb;
	if( trim )
	{
		answer %= trim;
	}

	return answer;
}

int main()
{
	START_TIMER;

	BigInt answer;
	const unsigned long long trim = 10000000000;
	for( unsigned int i = 1; i <= 1000; ++i )
	{
		answer += bigpow(i, i, trim);
	}

	answer %= trim;
	return result(9110846700, answer);
}
