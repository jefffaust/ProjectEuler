/*
Starting with 1 and spiraling anticlockwise in the following way, a square spiral with side length 7 is formed.

37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting
is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ? 62%.

If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed.
If this process is continued, what is the side length of the square spiral for which the ratio of primes along
both diagonals first falls below 10%?
*/

#include "Primes.h"
#include "TestUtils.h"

// 17 seconds. Room for improvement?
int main()
{
	START_TIMER;

	unsigned int primeCount = 0;
	unsigned int count = 1;

	const Primes& primes = Primes::get();

	for (unsigned int sideLength = 3; ; sideLength += 2)
	{
		unsigned int a = sideLength * sideLength;
		unsigned int b = a - (sideLength - 1);
		unsigned int c = b - (sideLength - 1);
		unsigned int d = c - (sideLength - 1);

		count += 4;

		if (primes.isPrime(a)) ++primeCount;
		if (primes.isPrime(b)) ++primeCount;
		if (primes.isPrime(c)) ++primeCount;
		if (primes.isPrime(d)) ++primeCount;

		if (static_cast<double>(primeCount) / count < .1)
		{
			return result(26241, sideLength);
		}
	}
}
