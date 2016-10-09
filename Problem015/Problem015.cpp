/*
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
*/

#include "TestUtils.h"

int main()
{
	START_TIMER;

	// In each solution, you must move right 20 times and down 20 times, so the answer
	// is the number of distinct permutations of the sequence "rrrrrrrrrrrrrrrrrrrrdddddddddddddddddddd"
	// The answer is given by the equation 40!/(20!20!).

	int dim = 20;

	long long answer = 1;
	// Let's avoid the number getting too big by dividing by each divisor in 20! when we can. There's probably a better way to do this...
	int curDivisor = dim;
	for( long long i = 2*dim; i > dim; --i )
	{
		answer *= i;
		if( answer % curDivisor == 0 )
		{
			answer /= curDivisor--;
		}
	}

	// Our "greedy" approach may have left some over. Everything left should be evenly divisible.
	while( curDivisor > 1 )
	{
		answer /= curDivisor--;
	}

	return result(137846528820, answer);
}
