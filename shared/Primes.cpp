#include "Primes.h"

#include <algorithm>

const Primes& Primes::get()
{
	static Primes primes;
	return primes;
}

Primes::Primes()
{
	m_isPrime.push_back(false);
	m_isPrime.push_back(false);
	m_isPrime.push_back(true);
	m_primes.push_back(2);
}

// returns true if the given number is prime
bool Primes::isPrime(size_t n) const
{
	grow(n);
	return m_isPrime[n];
}

unsigned int Primes::nthPrime(size_t n) const
{
	while( n >= m_primes.size() )
	{
		grow(static_cast<size_t>(m_isPrime.size()*1.5) + 1);
	}
	return m_primes[n-1];
}

std::vector<int> Primes::primeFactors(size_t v) const
{
	std::vector<int> factors;
	grow(v);
	for( size_t i = 0; i < m_primes.size() && m_primes[i] <= v; ++i )
	{
		factors.resize(i + 1, 0);
		while( v % m_primes[i] == 0 )
		{
			v /= m_primes[i];
			++factors[i];
		}
	}

	return factors;
}

// Sieve of Eratosthenes
void Primes::grow(size_t minN) const
{
	unsigned int highestIndex = static_cast<unsigned int>(m_isPrime.size() - 1);
	if( minN <= highestIndex )
	{
		return;
	}

	size_t newSize = std::max(minN + 1, static_cast<size_t>(m_isPrime.size() * 1.5));

	m_isPrime.resize(newSize, true);

	// Apply sieve with all the existing primes
	for( auto pi = m_primes.begin(); pi != m_primes.end(); ++pi )
	{
		sieve(highestIndex, *pi);
	}

	for( unsigned int i = highestIndex + 1; i < newSize; ++i )
	{
		// The first number we have not sieved out will be prime.
		if( m_isPrime[i] )
		{
			m_primes.push_back(static_cast<unsigned int>(i));

			// sieve out each new prime.
			sieve(i, i);
		}
	}
}

void Primes::sieve(unsigned int start, unsigned int p) const
{
	for( size_t cur = start + (p - (start % p)); cur < m_isPrime.size(); cur += p )
	{
		m_isPrime[cur] = false;
	}
}
