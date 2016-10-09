#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

#include <cmath>

// handles awkward casting
inline unsigned int sqrt(unsigned int n)
{
	return static_cast<unsigned int>(sqrt(static_cast<float>(n)));
}

inline unsigned long long sqrt(unsigned long long n)
{
	return static_cast<unsigned long long>(sqrt(static_cast<long double>(n)));
}

// Performs an operation on each proper divisor
template<typename F>
inline void forEachDivisor(unsigned int n, F f)
{
	if( n > 1 )
	{
		f(1); // one is always a divisor
	}

	// We only need to count up to sqrt(v) and sum each divisor and it's pair.
	const unsigned int sqrtn = sqrt(n);
	const bool perfectSquare = sqrtn * sqrtn == n;

	for( unsigned int d = 2; d <= sqrtn; ++d )
	{
		if( n % d == 0 )
		{
			f(d);
			if( !perfectSquare || d != sqrtn ) // avoid double-booking
			{
				f(n/d);
			}
		}
	}
}

inline unsigned int sumDivisors(unsigned int n)
{
	unsigned int sum = 0;
	forEachDivisor(n, [&sum] (unsigned int d) { sum += d; } );
	return sum;
}

template<typename T, typename F>
void forEachDigit(T t, F f)
{
	while( t )
	{
		f(t % 10);
		t /= 10;
	}
}

template<typename T>
T sumDigits(T t)
{
	T sum = 0;
	forEachDigit(t, [&sum] (const T& d) { sum += d; });
	return sum;
}

template<typename T>
T countDigits(T t)
{
	T count = 0;
	forEachDigit(t, [&count] (const T&) { ++count; });
	return count;
}

// Returns 1 for n == 1-9, 10 for n == 10-100, etc.
template<typename T>
T getPow10(T n)
{
	T pow10 = 1;
	for( n /= 10; n; n /= 10, pow10 *= 10 )
		;
	return pow10;
}

template<typename T>
void truncateRight(T& n)
{
	n /= 10;
}

template<typename T>
void truncateLeft(T& n)
{
	n %= getPow10(n);
}

inline bool isNaturalNumber(double n)
{
	return (n - floor(n)) < 1e-6;
}

template<typename T>
T asNaturalNumber(long double n)
{
	return isNaturalNumber(n) ? static_cast<T>(n) : 0;
}

template<typename T>
T triangular(T n)
{
	return n*(n+1)/2;
}

template<typename T>
T invTriangular(T t)
{
	// https://en.wikipedia.org/wiki/Triangular_number
	return asNaturalNumber<T>((sqrt(8*t + 1.) - 1) / 2);
}

template<typename T>
T pentagonal(T n)
{
	return n*(3*n-1)/2;
}

template<typename T>
T invPentagonal(T p)
{
	// https://en.wikipedia.org/wiki/Pentagonal_number
	return asNaturalNumber<T>((sqrt(24*p + 1.) + 1) / 6);
}

template<typename T>
T hexagonal(T n)
{
	return n*(2*n - 1);
}

template<typename T>
T invHexagonal(T h)
{
	// https://en.wikipedia.org/wiki/Hexagonal_number
	return asNaturalNumber<T>((sqrt(8*h + 1.) + 1) / 4);
}
