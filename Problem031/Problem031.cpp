/*
In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
*/

#include "TestUtils.h"

#include <array>

enum Denom                             {TwoPound, OnePound, FiftyPence, TwentyPence, TenPence, FivePence, TwoPence, OnePence};
std::array<int, 8> s_denominations = {200,      100,      50,         20,          10,       5,         2,        1};

// Iterating over enums needs some casting...
void next(Denom& denom) { denom = static_cast<Denom>(static_cast<int>(denom) + 1); }

int combinations(int v, Denom highestDenomination = TwoPound)
{
	// What is the highest denomination we can use?
	for( highestDenomination; s_denominations[highestDenomination] > v; next(highestDenomination) )
		;

	// Choose the highest denomination to start with, subtract it out and recurse, until you finish.
	// Then choose the next highest denomination, and repeat.
	int count = 0;
	while( highestDenomination < OnePence )
	{
		int nextV = v - s_denominations[highestDenomination];
		count += nextV == 0 ? 1 : combinations(nextV, highestDenomination);
		next(highestDenomination);
	}

	// +1 for handling the OncePence case. Faster doing it here then handling it with recursion.
	return count + 1;
}

int main()
{
	START_TIMER;
	return result(73682, combinations(200));
}
