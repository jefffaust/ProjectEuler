/*
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the
digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d[1] be the 1st digit, d[2] be the 2nd digit, and so on. In this way, we note the following:

d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.
*/

#include "TestUtils.h"

#include <boost/array.hpp>

// Ugly but fast: 321 us
int main()
{
	START_TIMER;
	boost::array<bool, 10> used = {false};
	boost::array<int, 11> d; // we don't use d[0], just to match problem description
	unsigned long long sum = 0;

	for( int div2Iter = 10; div2Iter < 1000; div2Iter += 2 )
	{
		assert(std::count(used.begin(), used.end(), true) == 0);
		int div2 = div2Iter;
		d[4] = div2 % 10; div2 /= 10;
		d[3] = div2 % 10; div2 /= 10;
		d[2] = div2 % 10; div2 /= 10;
		if( d[2] == d[3] || d[3] == d[4] || d[2] == d[4] ) continue;
		used[d[2]] = used[d[3]] = used[d[4]] = true;
		assert(std::count(used.begin(), used.end(), true) == 3);

		for( d[5] = 0; d[5] < 10; ++d[5] )
		{
			if( used[d[5]] ) continue;
			if( (d[3] * 100 + d[4] * 10 + d[5]) % 3 ) continue;
			used[d[5]] = true;
			assert(std::count(used.begin(), used.end(), true) == 4);
			for( d[6] = 0; d[6] < 10; ++d[6] )
			{
				if( used[d[6]] ) continue;
				if( (d[4] * 100 + d[5] * 10 + d[6]) % 5 ) continue;
				used[d[6]] = true;
				assert(std::count(used.begin(), used.end(), true) == 5);
				for( d[7] = 0; d[7] < 10; ++d[7] )
				{
					if( used[d[7]] ) continue;
					if( (d[5] * 100 + d[6] * 10 + d[7]) % 7 ) continue;
					used[d[7]] = true;
					assert(std::count(used.begin(), used.end(), true) == 6);
					for( d[8] = 0; d[8] < 10; ++d[8] )
					{
						if( used[d[8]] ) continue;
						if( (d[6] * 100 + d[7] * 10 + d[8]) % 11 ) continue;
						used[d[8]] = true;
						assert(std::count(used.begin(), used.end(), true) == 7);
						for( d[9] = 0; d[9] < 10; ++d[9] )
						{
							if( used[d[9]] ) continue;
							if( (d[7] * 100 + d[8] * 10 + d[9]) % 13 ) continue;
							used[d[9]] = true;
							assert(std::count(used.begin(), used.end(), true) == 8);
							for( d[10] = 0; d[10] < 10; ++d[10] )
							{
								if( used[d[10]] ) continue;
								if( (d[8] * 100 + d[9] * 10 + d[10]) % 17 ) continue;
								used[d[10]] = true;
								assert(std::count(used.begin(), used.end(), true) == 9);
								// Find the unused digit
								auto iter = std::find(used.begin(), used.end(), false);
								d[1] = static_cast<int>(std::distance(used.begin(), iter));
								used[d[1]] = true;
								assert(std::count(used.begin(), used.end(), true) == 10);
								if( d[1] != 0 )
								{
									sum += d[1] * 1000000000ULL + d[2] * 100000000 + d[3] * 10000000 + d[4] * 1000000 + d[5] * 100000 + d[6] * 10000 + d[7] * 1000 + d[8] * 100 + d[9] * 10 + d[10];
								}
								used[d[1]] = false;
								used[d[10]] = false;
							}
							used[d[9]] = false;
						}
						used[d[8]] = false;
					}
					used[d[7]] = false;
				}
				used[d[6]] = false;
			}
			used[d[5]] = false;
		}
		used[d[2]] = used[d[3]] = used[d[4]] = false;
	}

	return result(16695334890, sum);
}
