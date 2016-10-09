/*
The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)
*/

#include "TestUtils.h"

#include <algorithm>
#include <array>
#include <vector>

std::array<unsigned int, 20> pow2 = {524288, 262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};

const std::vector<short>& makeBinary(unsigned int n)
{
	static std::vector<short> binvec;
	binvec.clear();
	size_t i = 0;
	// find first non-zero
	for( ; i < pow2.size(); ++i )
	{
		if( pow2[i] <= n )
		{
			binvec.push_back(1);
			n -= pow2[i];
			break;
		}
	}

	// populate rest.
	++i;
	for( ; i < pow2.size(); ++i )
	{
		short dig = pow2[i] <= n ? 1 : 0;
		binvec.push_back(dig);
		if( dig )
		{
			n -= pow2[i];
		}
	}

	return binvec;
}

bool isBinaryPalindrome(unsigned int n)
{
	auto binary = makeBinary(n);

	// compare from both sides to the center
	return std::equal(binary.begin(), binary.begin() + binary.size()/2, binary.rbegin());
}

int main()
{
	START_TIMER;

	assert(isBinaryPalindrome(585));

	unsigned int sum = 0;

	// one digit palindromes
	for( int i = 1; i < 10; ++i )
	{
		if( isBinaryPalindrome(i) )
			sum += i;
	}

	// two digit palindromes
	for( int i = 11; i < 100; i += 11 )
	{
		if( isBinaryPalindrome(i) )
			sum += i;
	}

	// three digit palindromes
	for( int i = 1; i < 100; ++i )
	{
		const int p = (i%10) * 100 + i;
		if( p > 100 && isBinaryPalindrome(p) )
			sum += p;
	}

	// four digit palindromes
	for( int i = 1; i < 100; ++i )
	{
		const int p = (i % 10) * 1000 + (i / 10) * 100 + i;
		if( p > 1000 && isBinaryPalindrome(p) )
			sum += p;
	}

	// five digit palindromes
	for( int i = 1; i < 1000; ++i )
	{
		const int p = (i % 10) * 10000 + ((i/10)%10) * 1000 + i;
		if( p > 10000 && isBinaryPalindrome(p) )
			sum += p;
	}

	// six digit palindromes
	for( int i = 1; i < 1000; ++i )
	{
		const int p = (i % 10) * 100000 + ((i/10)%10) * 10000 + ((i/100)%10) * 1000 + i;
		if( p > 100000 && isBinaryPalindrome(p) )
			sum += p;
	}

	return result(872187, sum);
}
