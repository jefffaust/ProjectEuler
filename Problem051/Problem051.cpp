/*
By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible
values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the
first example having seven primes among the ten generated numbers, yielding the family: 56003,
56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this
family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits)
with the same digit, is part of an eight prime value family.
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include "Primes.h"

#include <boost/array.hpp>

unsigned int replaceDigits(unsigned int n, unsigned int d, unsigned int mask)
{
	unsigned int nextN = 0;
	unsigned int pow10 = 1;
	unsigned int pow2 = 1;

	// Break down and rebuild n, but substitute d for every digit covered by mask.
	forEachDigit(n, [&](int digit) {
		if (pow2 & mask) digit = d;
		nextN += pow10*digit;
		pow10 *= 10;
		pow2 *= 2;
	});

	return nextN;
}

int primeFamilySize(unsigned int p, unsigned int d, unsigned int mask)
{
	int familySize = 1; // always 1 for self
	if (!mask) return familySize;

	// Go through each digit from d + 1 through 9. We don't look lower because we use p as the starting
	// point for the family size.
	for( ++d; d < 10; ++d )
	{
		// replace the digits of p with d using the given mask.
		p = replaceDigits(p, d, mask);

		// Check if the new number is prime.
		if (Primes::get().isPrime(p))
		{
			++familySize;
		}
	}

	return familySize;
}

// Creates a bit mask of all instances of d in n.
unsigned int createMask(unsigned int n, unsigned int d)
{
	unsigned int mask = 0;
	unsigned int pow2 = 1;
	forEachDigit(n, [&](int digit){
		if (digit == d) mask += pow2;
		pow2 *= 2;
	});
	return mask;
}

unsigned int primeFamilySize(unsigned int p)
{
	int familySize = 1; // we will return the max family size we find
	for (unsigned int digitIndex = 0; digitIndex < 10; ++digitIndex)
	{
		// using a mask for digitIndex (which may be 0), find the prime family size.
		familySize = std::max(familySize, primeFamilySize(p, digitIndex, createMask(p, digitIndex)));
	}

	return familySize;
}

void runTests()
{
	assert(replaceDigits(112233, 4, 0) == 112233);
	assert(replaceDigits(112233, 4, 1) == 112234);
	assert(replaceDigits(112233, 8, 16 + 4 + 1) == 182838);
	assert(createMask(112233, 4) == 0);
	assert(createMask(112233, 3) == 1 + 2);
	assert(createMask(112233, 2) == 4 + 8);
	assert(createMask(112233, 1) == 16 + 32);
	assert(replaceDigits(1234543, 8, createMask(1234543, 3)) == 1284548);
	assert(primeFamilySize(13) == 6);
	assert(primeFamilySize(56003) == 7);
}

int main()
{
	runTests();
	START_TIMER;
	const Primes& primes = Primes::get();
	unsigned int p = 0;

	// for each prime...
	for (unsigned int n = 1; ; ++n)
	{
		const unsigned int p = primes.nthPrime(n);
		// ... find the first with a family size of 8.
		if (primeFamilySize(p) == 8)
		{
			return result(121313, p);
		}
	}
}
