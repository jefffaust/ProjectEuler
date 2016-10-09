/*
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by canceling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

#include "MathUtils.h"
#include "TestUtils.h"
#include "Primes.h"

#include <cassert>

bool curiousFraction(short num, short den)
{
	const double n1 = num % 10;
	const double n2 = num / 10;
	const double d1 = den % 10;
	const double d2 = den / 10;
	if( n1 == 0 || d1 == 0 ) return false;
	if( n1 == d1 && n2/d2 == num/static_cast<double>(den) ) return true;
	if( n1 == d2 && n2/d1 == num/static_cast<double>(den) ) return true;
	if( n2 == d1 && n1/d2 == num/static_cast<double>(den) ) return true;
	if( n2 == d2 && n1/d1 == num/static_cast<double>(den) ) return true;
	return false;
}

void reduceFraction(unsigned int& num, unsigned int& den)
{
	const Primes& primes = Primes::get();
	unsigned int p = 0;
	unsigned int sqrtnum = sqrt(num);
	for( unsigned int n = 1; p < sqrtnum; ++n )
	{
		p = primes.nthPrime(n);
		while( num%p == 0 && den%p == 0 )
		{
			num /= p;
			den /= p;
		}
	}
}

int main()
{
	START_TIMER;
	assert(curiousFraction(49, 98));
	unsigned int numProd = 1;
	unsigned int denProd = 1;
	for( short num = 11; num < 100; ++num )
	{
		for( short den = num + 1; den < 100; ++den )
		{
			if( curiousFraction(num, den) )
			{
				numProd *= num;
				denProd *= den;
			}
		}
	}

	reduceFraction(numProd, denProd);

	return result(100, denProd);
}
