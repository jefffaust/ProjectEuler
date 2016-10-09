/*

The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values
we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a
triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common
English words, how many are triangle words?
*/

#include "TestUtils.h"

#include <algorithm>
#include <fstream>
#include <vector>

std::string nextWord(std::istream& istr)
{
	if( !istr.good() ) return std::string();
	char ch = 0;
	istr.get(ch);
	assert(ch == '"');
	std::string word;
	istr.get(ch);
	while( ch != '"' )
	{
		word.push_back(ch);
		istr.get(ch);
	}

	istr.get(ch);
	assert(!istr.good() || ch == ',');
	return word;
}

unsigned int triangle(unsigned int n)
{
	return (n + 1)*n/2;
}

// Calculates triangle numbers up to maxN
std::vector<bool> calcTriangleNumbers(unsigned int maxN)
{
	std::vector<bool> triangleNumbers;
	triangleNumbers.resize(triangle(maxN), false);
	for( size_t n = 1; n < maxN; ++n )
	{
		triangleNumbers[triangle(n)] = true;
	}
	return triangleNumbers;
}

bool isTriangleNumber(unsigned int n)
{
	static std::vector<bool> triangleNumbers = calcTriangleNumbers(300);
	return triangleNumbers[n];
}

bool isTriangleWord(const std::string& word)
{
	// calculate sum of letters
	unsigned int sum = 0;
	std::for_each(word.begin(), word.end(), [&sum] (char c) { sum += c - 'A' + 1; });

	// return if it is a triangle number
	return isTriangleNumber(sum);
}

int main()
{
	START_TIMER;
	std::ifstream istr("words.txt");
	std::string word;
	unsigned int count = 0;

	// count up all triangle words
	while( !(word = nextWord(istr)).empty() )
	{
		if( isTriangleWord(word) )
		{
			++count;
		}
	}

	return result(162, count);
}
