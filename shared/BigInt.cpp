#include "BigInt.h"

#include "MathUtils.h"

#include <algorithm>
#include <numeric> // accumulate
#include <vector>

BigInt::BigInt()
	: m_digitsPerValue(17), m_maxValue(1000000000000000000)
{
}

BigInt::BigInt(long long i)
	: m_digitsPerValue(17), m_maxValue(1000000000000000000)
{
	if( i != 0 )
	{
		m_value.push_back(i);
		normalize();
	}
}

BigInt::BigInt(const std::string& str)
	: m_digitsPerValue(17), m_maxValue(1000000000000000000)
{
	int digit = 0;
	InternalType curValue = 0;
	InternalType multiplier = 1;
	for( auto iter = str.rbegin(); iter != str.rend(); ++iter )
	{
		curValue += multiplier * (*iter - '0');
		multiplier *= 10;
		if( digit++ == m_digitsPerValue )
		{
			m_value.push_front(curValue);
			digit = 0;
			curValue = 0;
			multiplier = 1;
		}
	}

	if( curValue )
	{
		m_value.push_front(curValue);
	}
}

BigInt& BigInt::operator=(long long i)
{
	m_value.clear();
 	if( i != 0 )
	{
		m_value.push_back(i);
		normalize();
	}
	return *this;
}

bool BigInt::operator==(const BigInt& rhs) const
{
	return m_value == rhs.m_value;
}

bool BigInt::operator<(const BigInt& rhs) const
{
	if( m_value.size() < rhs.m_value.size() )
	{
		return true;
	}

	if( m_value.size() > rhs.m_value.size() )
	{
		return false;
	}

	return m_value < rhs.m_value;
}

unsigned long long BigInt::numDigits() const
{
	if( m_value.empty() )
	{
		return 1;
	}

	return countDigits(m_value.front()) + (m_digitsPerValue + 1) * (m_value.size() - 1);
}

BigInt& BigInt::operator+=(const BigInt& rhs)
{
	while( m_value.size() < rhs.m_value.size() )
	{
		m_value.push_front(0);
	}

	auto iter = m_value.rbegin();

	for( auto rhs_iter = rhs.m_value.rbegin(); rhs_iter != rhs.m_value.rend(); ++rhs_iter )
	{
		*iter++ += *rhs_iter;
	}

	return normalize();
}

BigInt& BigInt::operator*=(BigInt rhs)
{
	const int digitsAtATime = 9;
	const int maxAtATime = 1000000000;

	auto construct = [&] (InternalType i1, InternalType i2, int multiplier) -> BigInt {
		BigInt bi(i1 * i2);
		if( !multiplier || !bi ) return bi;

		if( multiplier % 2 ) // odd
		{
			InternalType upper = bi.m_value[0] / maxAtATime;
			if( upper )
			{
				bi.m_value.push_front(upper);
			}

			bi.m_value.back() = (bi.m_value.back() % maxAtATime) * maxAtATime;
			--multiplier;
		}
		if( !multiplier ) return bi;

		int count = multiplier / 2;
		while( count-- )
		{
			bi.m_value.push_back(0);
		}

		return bi;
	};

	std::vector<BigInt> toAdd;
	for( auto outer = rhs.m_value.rbegin(); outer != rhs.m_value.rend(); ++outer )
	{
		for( auto inner = m_value.rbegin(); inner != m_value.rend(); ++inner )
		{
			// Just like we learned to multiply in school, but with bigger "digits" at a time.
			int multiplier = (distance(rhs.m_value.rbegin(), outer) + distance(m_value.rbegin(), inner)) * 2;
			InternalType outer_lower = *outer % maxAtATime;
			InternalType outer_upper = *outer / maxAtATime;
			InternalType inner_lower = *inner % maxAtATime;
			InternalType inner_upper = *inner / maxAtATime;
			toAdd.push_back(construct(outer_lower, inner_lower, multiplier));
			toAdd.push_back(construct(outer_lower, inner_upper, multiplier + 1));
			toAdd.push_back(construct(outer_upper, inner_lower, multiplier + 1));
			toAdd.push_back(construct(outer_upper, inner_upper, multiplier + 2));
		}
	}

	return *this = std::accumulate(toAdd.begin(), toAdd.end(), BigInt());
}

BigInt& BigInt::operator/=(long long rhs)
{
	if( m_value.empty() )
	{
		return *this;
	}

	for( auto iter = m_value.rbegin(); iter != m_value.rend(); ++iter )
	{
		const InternalType cur = *iter;
		*iter /= rhs;
		if( iter != m_value.rbegin() )
		{
			auto prev = iter - 1;
			*prev += (cur % rhs) * (m_maxValue / rhs);
		}
	}

	return normalize();
}

BigInt& BigInt::operator%=(long long rhs)
{
	if( m_value.empty() )
	{
		return *this;
	}

	unsigned long long result = m_value.back() % rhs;
	m_value.clear();
	m_value.push_front(result);
	return normalize();
}

std::ostream& operator<<(std::ostream& ostr, const BigInt& bi)
{
	if( bi.m_value.empty() )
	{
		return ostr << "0";
	}

	if( bi.m_value.size() == 1 )
	{
		return ostr << bi.m_value[0];
	}

	for( size_t i = 0; i < bi.m_value.size(); ++i )
	{
		auto curValue = bi.m_value[i];
		if( i != 0 )
		{
			// pad with zeros
			BigInt::InternalType multiplier = 10;
			while( multiplier < bi.m_maxValue )
			{
				if( multiplier > curValue )
				{
					ostr << '0';
				}
				multiplier *= 10;
			}
		}
		ostr << curValue;
	}

	return ostr;
}

bool operator==(const BigInt& lhs, int rhs)
{
	return lhs == BigInt(rhs);
}

BigInt& BigInt::normalize()
{
	while( !m_value.empty() && m_value.front() == 0 )
	{
		m_value.pop_front();
	}

	for( size_t i = m_value.size(); i--; )
	{
		auto curValue = m_value[i];
		if( curValue >= m_maxValue )
		{
			// An operation caused us to exceed the max value we allow. Note that we leave an extra digit to make addition easy.
			// We may need to gain that back or the next operation may not be correct.
			m_value[i] = curValue % m_maxValue;
			curValue /= m_maxValue;
			if( i > 0 )
			{
				m_value[i - 1] += curValue;
			}
			else
			{
				m_value.push_front(curValue);
			}
		}
	}

	return *this;
}
