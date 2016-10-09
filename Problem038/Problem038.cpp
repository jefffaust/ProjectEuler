/*
Take the number 192 and multiply it by each of 1, 2, and 3:

192 × 1 = 192
192 × 2 = 384
192 × 3 = 576

By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?
*/

#include "MathUtils.h"
#include "TestUtils.h"

unsigned int concat(unsigned int left, unsigned int right)
{
	return left*getPow10(right)*10 + right;
}

unsigned int pandigitalMultiple(unsigned int n)
{
	bool digits[10] = {false};
	bool pandigital = true;
	int digitCount = 0;
	auto accumulateDigits = [&] (int d) {
		// Can't have zeros, or repeated digits
		if( d == 0 || digits[d] )
		{
			pandigital = false;
			return;
		}

		// set this digit and increment the digit count.
		digits[d] = true;
		++digitCount;
	};

	unsigned int pan = n;
	forEachDigit(1*n, accumulateDigits);
	for( int i = 2; pandigital && digitCount < 9; ++i )
	{
		forEachDigit(i*n, accumulateDigits);
		if( pandigital )
		{
			pan = concat(pan, i*n);
		}
	}

	return pandigital ? pan : 0;
}

int main()
{
	START_TIMER;
	assert(concat(9,18) == 918);
	assert(concat(918, 27) == 91827);
	assert(pandigitalMultiple(9) == 918273645);
	assert(pandigitalMultiple(192) == 192384576);

	unsigned int maxPan = 0;
	// concat(1*9877, 2*9877) == 987719754, which is greater than the max possible 987654321
	for( unsigned int i = 1; i < 9877; ++i )
	{
		unsigned int pan = pandigitalMultiple(i);
		if( pan > maxPan )
		{
			maxPan = pan;
		}
	}

	return result(932718654, maxPan);
}
