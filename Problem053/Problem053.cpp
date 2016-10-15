/*
There are exactly ten ways of selecting three from five, 12345:

123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

In combinatorics, we use the notation, 5C3 = 10.

nCr = n!/r!(n-r)!, where r <= n.

It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

How many, not necessarily distinct, values of nCr, for 1 <= n <= 100, are greater than one-million?
*/

#include "TestUtils.h"

#include <cassert>
#include <vector>

template<typename T>
void tryFactorOut(std::vector<bool>& factors, T& value)
{
	bool done = true;
	for (int i = 0; i < factors.size(); ++i)
	{
		if (!factors[i]) continue; // already factored out
		int factor = i + 2; // skip 0 and 1
		if (value % factor == 0) // this is the "try"
		{
			value /= factor;
			factors[i] = false;
		}
		else
		{
			done = false;
		}
	}

	if (done)
	{
		factors.clear(); // save some iteration next time
	}
}

unsigned long long calcResult(unsigned long long n, unsigned long long d1, unsigned long long d2)
{
	double answer = static_cast<double>(n);
	for (; d1; --d1) answer /= d1;
	for (; d2; --d2) answer /= d2;
	return static_cast<unsigned long long>(answer);
}

void factorOut(std::vector<bool>& factors1, double& approxResult)
{
	for (int i = 0; i < factors1.size(); ++i)
	{
		if (!factors1[i]) continue;
		approxResult /= (i + 2);
	}
}

unsigned long long nCr(int n, int r)
{
	if (n == r) return 1;

	static std::vector<bool> factors1;
	static std::vector<bool> factors2;

	factors1.assign(r - 1, true);
	factors2.assign(n - r - 1, true);

	// The main goal of this loop is to try not to overflow. We loop to calculate n!, but greedily factor out the denominator as we go.
	unsigned long long answer = 1;
	for (; n > 1; --n)
	{
		if (answer >= std::numeric_limits<unsigned long long>::max() / n)
		{
			// Do not overflow. This will fall through to an approximate calculation below
			break;
		}

		answer *= n;
		tryFactorOut(factors1, answer);
		tryFactorOut(factors2, answer);
	}

	if( n > 1 )
	{
		// We're in approximation territory. Instead of using BigInt, let's instead give up some accuracy, returning std::numeric_limits::max if we overflow.
		double approxResult = static_cast<double>(answer);
		factorOut(factors1, approxResult); // probably not many of these left since we factor out this set first
		for (; n > 1; --n)
		{
			approxResult *= n;
		}

		factorOut(factors2, approxResult);

		// don't return a value greater that max()
		if (approxResult > static_cast<double>(std::numeric_limits<unsigned long long>::max()))
		{
			return std::numeric_limits<unsigned long long>::max();
		}

		return static_cast<unsigned long long>(approxResult);
	}

	assert(std::find(factors1.begin(), factors1.end(), true) == factors1.end());
	assert(std::find(factors2.begin(), factors2.end(), true) == factors2.end());

	return answer;
}

int main()
{
	assert(nCr(23, 10) == 1144066);
	assert(nCr(24, 10) == 1961256);
	assert(nCr(45, 19) > 2.4e+12);
	assert(nCr(71, 35) == std::numeric_limits<unsigned long long>::max());
	START_TIMER;

	unsigned int count = 0;
	for (int n = 1; n <= 100; ++n)
	{
		for (int r = 1; r <= n; ++r)
		{
			if (nCr(n, r) > 1000000)
			{
				++count;
			}
		}
	}

	return result(4075, count);
}
