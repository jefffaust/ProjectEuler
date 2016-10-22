/*
Each character on a computer is assigned a unique code and the preferred standard is ASCII
(American Standard Code for Information Interchange).
For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each
byte with a given value, taken from a secret key. The advantage with the XOR function is that
using the same encryption key on the cipher text, restores the plain text;
for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, and the key
is made up of random bytes. The user would keep the encrypted message and the encryption key in
different locations, and without both "halves", it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is to use a
password as a key. If the password is shorter than the message, which is likely, the key is
repeated cyclically throughout the message. The balance for this method is using a sufficiently
long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters.
Using cipher.txt (right click and 'Save Link/Target As...'), a file containing the encrypted
ASCII codes, and the knowledge that the plain text must contain common English words, decrypt
the message and find the sum of the ASCII values in the original text.
*/

#include "TestUtils.h"

#include <boost/noncopyable.hpp>

#include <array>
#include <cassert>
#include <fstream>
#include <numeric>
#include <vector>

typedef std::vector<int> Cipher;
typedef std::string Message;

class Key : boost::noncopyable
{
	static const int KeySize = 3;
	typedef std::array<char, KeySize> KeyType;
public:
	Key()
	{
		m_key.fill('a');
		for (auto& allowed : m_allowed) allowed.fill(true);
	}

	operator bool() const
	{
		return !m_done;
	}

	void ignore()
	{
		auto& allowed = m_allowed[m_keyIndex];
		const auto c = m_key[m_keyIndex];
		int allowedIndex = c - 'a';
		allowed[allowedIndex] = false;
		next(m_keyIndex);
		m_keyIndex = 0;
	}

	void next()
	{
		next(0);
	}

	char decryptChar(int i) const
	{
		i ^= m_key[m_keyIndex];
		return (i > 0 && i <= std::numeric_limits<char>::max()) ? static_cast<char>(i) : 0;
	}

	void step()
	{
		m_keyIndex = (m_keyIndex + 1) % m_key.size();
	}

private:
	bool next(size_t i)
	{
		if (i >= m_key.size())
		{
			m_done = true;
			return false;
		}

		const auto& allowed = m_allowed[i];
		for (auto c = m_key[i] + 1; c <= 'z'; ++c)
		{
			if (allowed[c - 'a'])
			{
				m_key[i] = c;
				return true;
			}
		}

		for (auto c = 'a'; c < m_key[i]; ++c)
		{
			if (allowed[c - 'a'])
			{
				m_key[i] = c;
			}
		}

		return next(i + 1);
	}

	KeyType m_key;
	size_t m_keyIndex = 0;
	std::array<std::array<bool, 26>, KeySize> m_allowed;
	bool m_done = false;
};

bool isEnglish(const Message& message)
{
	return false;
}

bool allowedPunctuation(char c)
{
	return c == '.' || c == '!' || c == '?' || c == ',';
}

bool allowed(char c)
{
	return isalnum(c) || isspace(c) || allowedPunctuation(c);
}

bool isWord(const Message& word)
{
	if (word.length() > 15)
	{
		return false;
	}

	for (size_t i = 0; i < word.size() - 1; ++i )
	{
		if (!isalpha(word[i])) return false;
	}

	if (word.length() == 1)
	{
		return isalnum(word[0]) && true;
	}

	return true;
}

Message decrypt(Key& key, const Cipher& cipher)
{
	Message message;
	Message word;
	for (auto i : cipher)
	{
		char c = key.decryptChar(i);
		if (!allowed(c))
		{
			key.ignore();
			return Message();
		}

		if( !word.empty() || !isspace(c) )
		{
			word.push_back(c);
		}

		if (!isWord(word))
		{
			key.next();
			return Message();
		}

		if (isspace(c))
		{
			word.clear();
		}
		message.push_back(c);
		key.step();
	}

	if (!isEnglish(message))
	{
		key.next();
		return Message();
	}

	return message;
}

Cipher readCipher()
{
	std::ifstream cipherFile("cipher.txt");
	Cipher cipher;
	while (cipherFile.good())
	{
		Cipher::value_type c;
		cipherFile >> c;
		cipher.push_back(c);
		cipherFile.ignore(1); // ignore ','
	}
	return cipher;
}

int main()
{
	START_TIMER;

	Cipher cipher = readCipher();

	Key key;
	while (key)
	{
		Message message = decrypt(key, cipher);
		if (!message.empty())
		{
			unsigned int sum = std::accumulate(message.begin(), message.end(), 0);
			return result(107359, sum);
		}
	}
}
