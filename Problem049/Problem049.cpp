/*
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways:
	(i) each of the three terms are prime, and,
	(ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property,
but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include "Primes.h"

#include <array>

template<typename T>
bool isPermuation(T n1, T n2)
{
	std::array<int, 10> n1digits = {0};
	std::array<int, 10> n2digits = {0};
	forEachDigit(n1, [&n1digits] (short d) {++n1digits[d];} );
	forEachDigit(n2, [&n2digits] (short d) {++n2digits[d];} );
	return n1digits == n2digits;
}

int main()
{
	START_TIMER;
	const Primes& primes = Primes::get();
	unsigned int p1 = 0;
	unsigned n = 1;

	// Find the first prime > 1487. Although the problem didn't say the answer is larger, I'm going to assume it.
	for( ; p1 <= 1487; ++n, p1 = primes.nthPrime(n) )
		;

	for( ;; ++n, p1 = primes.nthPrime(n) )
	{
		// add i*3330 for the next two numbers
		const unsigned int p2 = p1 + 3330;
		const unsigned int p3 = p1 + 6660;

		// check if they're prime and permutations of each other
		if( primes.isPrime(p2) && primes.isPrime(p3) && isPermuation(p1, p2) && isPermuation(p2, p3) )
		{
			return result(296962999629, static_cast<unsigned long long>(p1) * 100000000 + p2 * 10000 + p3);
		}
	}
}
