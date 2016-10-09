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

#include <algorithm>

int primeFamilySize(unsigned int p)
{

}

int main()
{
	START_TIMER;
	std::vector<unsigned int> primes2Same;
	std::vector<unsigned int> primes3Same;
	std::vector<unsigned int> primes4Same;
	std::vector<unsigned int> primes5Same;
	const Primes& primes = Primes::get();
	unsigned int p = 0;
	for( unsigned int n = 1; p < 1000000; ++n )
	{
		p = primes.nthPrime(n);
		boost::array<int, 10> digHist = {0};
		forEachDigit(p, [&digHist] (short d) { ++digHist[d]; });
		std::nth_element(digHist.begin(), digHist.begin() + 9, digHist.end());
		switch(digHist[9])
		{
		case 2:
			primes2Same.push_back(p);
			break;
		case 3:
			primes3Same.push_back(p);
			break;
		case 4:
			primes4Same.push_back(p);
			break;
		case 5:
			primes5Same.push_back(p);
			break;
		}
	}

	return result(121313, 0);
}
