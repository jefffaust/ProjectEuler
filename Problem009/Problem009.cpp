/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

#include "TestUtils.h"

int main()
{
	START_TIMER;

	// Very direct approach. It's fast, so no need to improve. Find each a < b < c triplet that sums to 1000 and
	// see if it is Pythagorean.
	for( int a = 1; a < 500; ++a )
	{
		for( int b = a + 1; b < 500; ++b )
		{
			int c = 1000 - (a + b);
			if( a*a + b*b == c*c )
			{
				return result(31875000, a * b * c);
			}
		}
	}
}
