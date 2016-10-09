/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include "TestUtils.h"

#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <string>

// Takes the first half of a palindrome and appends the reverse of it to create a palindrome.
int constructPalindrome(int front)
{
	std::string palindrome = boost::lexical_cast<std::string>(front);
	std::reverse_copy(palindrome.begin(), palindrome.end(), std::back_inserter(palindrome));
	return boost::lexical_cast<int>(palindrome);
}

bool hasTwo3DigitProducts(int p)
{
	for( int i = 100; i < 1000; ++i )
	{
		if( p % i == 0 )
		{
			int product = p / i;
			if( product > 100 && product < 1000 )
			{
				return true;
			}
		}
	}

	return false;
}

int main()
{
	// The smallest product of 2 3-digit numbers is 100 * 100 = 10000. The largest is 999 * 999 = 998001. Instead of checking all combinations
	// of 3-digit number products to see if they result in a palindrome, it might be faster to figure out which are palindromes.

	START_TIMER;
	int answer = 0;

	// I'm guessing that the palindrome will be 6 digits instead of 5.
	for( int i = 999; i >= 100 && !answer; --i )
	{
		int palindrome = constructPalindrome(i);
		if( hasTwo3DigitProducts(palindrome) )
		{
			answer = palindrome;
		}
	}

	return result(906609, answer);
}
