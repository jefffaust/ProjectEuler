#pragma once

#include <boost/chrono.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

#include <iostream>
#include <cmath>

template<typename T>
bool answerMatchesExpected(T expected, T answer)
{
	return expected == answer;
}

template<typename T1, typename T2>
bool answerMatchesExpected(T1 expected, T2 answer)
{
	return boost::lexical_cast<std::string>(answer) == boost::lexical_cast<std::string>(expected);
}

inline void reportTime(boost::timer::auto_cpu_timer& timer)
{
	timer.stop();
	long double elapsed = static_cast<long double>(timer.elapsed().wall);
	std::string symbol = "ns";

	if( elapsed > 1000 )
	{
		elapsed /= 1000.;
		symbol = "\xE6s";
	}

	if( elapsed > 1000 )
	{
		elapsed /= 1000.;
		symbol = "ms";
	}

	if( elapsed > 1000 )
	{
		elapsed /= 1000.;
		symbol = "seconds";
	}

	std::cout << "Finished in " << elapsed << " " << symbol << std::endl << std::endl;
}

template<typename T1, typename T2>
inline int handleResult(boost::timer::auto_cpu_timer& timer, T1 expected, T2 answer)
{
	reportTime(timer);
	if( answerMatchesExpected(expected, answer) )
	{
		std::cout << "Answer:   " << answer << std::endl;
	}
	else
	{
		std::cout << "   *** FAILED *** " << std::endl;
		std::cout << "Result:   " << answer << std::endl;
		std::cout << "Expected: " << expected << std::endl;
	}

	std::cout << std::endl;

	return 0;
}

#define START_TIMER boost::timer::auto_cpu_timer _t_(9, "%w seconds\n\n")
#define result(_expected_, _result_) handleResult(_t_, _expected_, _result_)
