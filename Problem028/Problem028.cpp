/*
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/

#include "TestUtils.h"

int main()
{
	START_TIMER;

	int answer = 1; // center
	for( int d = 3; d <= 1001; d += 2 )
	{
		// The highest diagonal is the square of the dimension. Then just march around the square for the other three values.
		unsigned int diag = d*d;
		answer += diag;
		diag -= (d - 1);
		answer += diag;
		diag -= (d - 1);
		answer += diag;
		diag -= (d - 1);
		answer += diag;
	}

	return result(669171001, answer);
}
