/*
An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...
             -

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
*/

#include "MathUtils.h"
#include "TestUtils.h"

int main()
{
	START_TIMER;
	unsigned int product = 1;

	// Remember digits per number we are iterating over. Cheaper than calculating for each.
	unsigned int digitsPerN = 1;

	// The tricky part is keeping the two indices straight.
	// n: index over natural numbers
	// d: index of digit of concatenated natural numbers

	unsigned int nextd = 1;
	unsigned int curd = 1;
	for( unsigned int max = 10; nextd <= 1000000; max *= 10, ++digitsPerN )
	{
		for( unsigned int n = max / 10; n < max && nextd <= 1000000; ++n, curd += digitsPerN )
		{
			if( curd + digitsPerN > nextd )
			{
				// The digit is in the current number.
				unsigned int n2 = n;

				// Truncate left until the next digit is leftmost.
				for( unsigned int d = curd; d != nextd; ++d )
				{
					truncateLeft(n2);
				}

				// Truncate from the right until we have one digit.
				while( n2 >= 10 )
				{
					truncateRight(n2);
				}

				// We found our digit. Include it in the product.
				product *= n2;

				// set up for the next digit
				nextd *= 10;
			}
		}
	}

	return result(210, product);
}
