/*
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names,
begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value
by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the
938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/

#include "TestUtils.h"

#include <cassert>
#include <fstream>
#include <numeric>
#include <set>
#include <string>

typedef std::string Name;
typedef std::set<Name> Names;

Name readName(std::istream& istr)
{
	Name name;
	char ch = 0;
	istr.get(ch);
	while( ch != '"' )
	{
		name.push_back(ch);
		istr.get(ch);
	}

	return name;
}

Names readNames()
{
	Names names;
	std::ifstream ifstr("names.txt");
	while( ifstr.good() )
	{
		char ch = 0;
		ifstr.get(ch);
		assert(ch == '"');
		names.insert(readName(ifstr));
		ifstr.get(ch);
		assert(!ifstr.good() || ch == ',');
	}

	return names;
}

long long valueOf(const Name& name)
{
	return std::accumulate(name.begin(), name.end(), 0LL, [](long long val, char ch){
		return val + (ch - 'A') + 1;
	});
}

int main()
{
	START_TIMER;
	Names names = readNames();
	long long answer = 0;
	int i = 1;
	for( auto iter = names.begin(); iter != names.end(); ++iter, ++i)
	{
		answer += i * valueOf(*iter);
	}
	return result(871198282, answer);
}
