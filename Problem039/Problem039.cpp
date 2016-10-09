/*
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximized?
*/

#include "TestUtils.h"

#include <map>

typedef std::map<unsigned int, unsigned int> Perimiters;

Perimiters fillPerimiters()
{
	Perimiters perimiters;

	// a + b > c for right triangles, so the hypotenuse is < 500.
	const unsigned int maxHypot = 500;
	for( unsigned int a = 1; a < maxHypot; ++a )
	{
		for( unsigned int b = a + 1; b < maxHypot; ++b )
		{
			unsigned int maxC = std::min(maxHypot, 1000 - (a + b));
			for( unsigned int c = b + 1; c < maxC; ++c )
			{
				if( a*a + b*b == c*c ) // converse of Pythagoras holds--this is a right triangle
				{
					++perimiters[a + b + c];
				}
			}
		}
	}

	return perimiters;
}

int main()
{
	START_TIMER;
	Perimiters perimiters = fillPerimiters();
	auto iter = perimiters.begin();
	auto answer = iter++;
	for( ; iter != perimiters.end(); ++iter )
	{
		// remember max count
		if( iter->second > answer->second )
		{
			answer = iter;
		}
	}

	return result(840, answer->first);
}
