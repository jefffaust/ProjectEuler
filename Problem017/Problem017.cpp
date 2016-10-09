/*
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen)
contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
*/

#include "TestUtils.h"

#include <cassert>
#include <numeric>
#include <vector>

namespace
{
	std::vector<int> letterCount(1001, 0);
}

template<size_t L>
int len(const char(&)[L])
{
	return L - 1;
}

void fillTo19()
{
	letterCount[1] = len("one");
	letterCount[2] = len("two");
	letterCount[3] = len("three");
	letterCount[4] = len("four");
	letterCount[5] = len("five");
	letterCount[6] = len("six");
	letterCount[7] = len("seven");
	letterCount[8] = len("eight");
	letterCount[9] = len("nine");
	letterCount[10] = len("ten");
	letterCount[11] = len("eleven");
	letterCount[12] = len("twelve");
	letterCount[13] = len("thirteen");
	letterCount[14] = len("fourteen");
	letterCount[15] = len("fifteen");
	letterCount[16] = len("sixteen");
	letterCount[17] = len("seventeen");
	letterCount[18] = len("eighteen");
	letterCount[19] = len("nineteen");
}

void fillTens(int start, int startLen)
{
	letterCount[start] = startLen;
	for( int i = start + 1; i <= start + 9; ++i )
	{
		assert(!letterCount[i]);
		letterCount[i] = letterCount[start] + letterCount[i % start];
	}
}

void fillHundreds(int h)
{
	const int start = h * 100;
	const int baseCount = letterCount[start] = letterCount[h] + len("hundred");
	for( int i = start + 1; i < start + 100; ++i )
	{
		assert(!letterCount[i]);
		letterCount[i] = baseCount + len("and") + letterCount[i % start];
	}
}

int main()
{
	START_TIMER;

	fillTo19();
	fillTens(20, len("twenty"));
	fillTens(30, len("thirty"));
	fillTens(40, len("forty"));
	fillTens(50, len("fifty"));
	fillTens(60, len("sixty"));
	fillTens(70, len("seventy"));
	fillTens(80, len("eighty"));
	fillTens(90, len("ninety"));

	for( int i = 1; i < 10; ++i )
	{
		fillHundreds(i);
	}

	letterCount[1000] = letterCount[1] + len("thousand");

	return result(21124, std::accumulate(letterCount.begin() + 1, letterCount.end(), 0));
}
