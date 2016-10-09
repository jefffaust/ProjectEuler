/*
You are given the following information, but you may prefer to do some research for yourself.

	1 Jan 1900 was a Monday.
	Thirty days has September,
	April, June and November.
	All the rest have thirty-one,
	Saving February alone,
	Which has twenty-eight, rain or shine.
	And on leap years, twenty-nine.
	A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/

#include "TestUtils.h"

bool isLeapYear(int year)
{
	return (!(year % 4) && (year % 100)) || !(year % 400);
}

enum Month { January, February, March, April, May, June, July, August, September, October, November, December };
Month nextMonth(Month month)
{
	return static_cast<Month>((static_cast<int>(month) + 1) % 12);
}

// clumsy, but works...
void nextSunday(int& dayOfMonth, Month& month, int& year)
{
	dayOfMonth += 7;
	if( dayOfMonth <= 28 )
	{
		return;
	}

	if( month == February )
	{
		bool leap = isLeapYear(year);
		if( dayOfMonth == 29 && leap )
		{
			return;
		}

		month = nextMonth(month);
		dayOfMonth %= leap ? 29 : 28;
		return;
	}

	if( dayOfMonth <= 30 )
	{
		return;
	}

	if( month == September || month == April || month == June || month == November )
	{
		month = nextMonth(month);
		dayOfMonth %= 30;
		return;
	}

	if( dayOfMonth <= 31 )
	{
		return;
	}

	dayOfMonth %= 31;
	month = nextMonth(month);
	if( month == January )
	{
		++year;
	}
}

int main()
{
	START_TIMER;

	int dayOfMonth = 7; // first Sunday
	Month month = January;
	int year = 1900;

	int answer = 0;
	while( year < 2001 )
	{
		if( dayOfMonth == 1 && year > 1900 )
		{
			++answer;
		}
		nextSunday(dayOfMonth, month, year);
	}

	return result(171, answer);
}
