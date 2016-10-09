/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include "BigInt.h"

int main()
{
	START_TIMER;

	BigInt bi = 2;
	for( int pow = 1; pow < 1000; ++pow ) bi += bi;

	return result(1366, sumDigits(bi));
}
