﻿/*
Triangle, pentagonal, and hexagonal numbers are generated by the following formulas:

Triangle	   Tn=n(n+1)/2    1, 3, 6, 10, 15, ...
Pentagonal  Pn=n(3n−1)/2   1, 5, 12, 22, 35, ...
Hexagonal   Hn=n(2n−1)     1, 6, 15, 28, 45, ...
It can be verified that T285 = P165 = H143 = 40755.

Find the next triangle number that is also pentagonal and hexagonal.
*/

#include "MathUtils.h"
#include "TestUtils.h"

int main()
{
	START_TIMER;

	assert(invHexagonal(40755) == 143);
	assert(hexagonal(143) == 40755);
	assert(invPentagonal(40755) == 165);
	assert(pentagonal(165) == 40755);
	assert(invTriangular(40755) == 285);
	assert(triangular(285) == 40755);

	for( unsigned long long n = 144; ; ++n )
	{
		// hexagonal numbers grow faster, so let's use those.
		unsigned long long h = hexagonal(n);
		if( invTriangular(h) && invPentagonal(h) )
		{
			return result(1533776805, h);
		}
	}
}
