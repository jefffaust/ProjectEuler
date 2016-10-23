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

#include <algorithm>
#include <array>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

const int keySize = 3;
typedef std::string Message;
typedef std::vector<char> Cipher;

class Key
{
public:
	typedef std::array<char, 3> KeyType;
	Key(KeyType k)
		: m_key(k)
	{
	}

	Key() : Key({ 'a', 'a', 'a' })
	{
	}

	char encrypt(char c, size_t keyIndex) const
	{
		return c ^ m_key[keyIndex % m_key.size()];
	}

	char decrypt(char c, size_t keyIndex) const
	{
		// same as encrypt
		return encrypt(c, keyIndex);
	}

	// increments m_key
	void next(int i = 0)
	{
		if (m_key[i] < 'z')
		{
			++m_key[i];
			return;
		}

		if (i + 1 == m_key.size())
		{
			m_done = true;
			return;
		}

		m_key[i] = 'a';
		return next(i + 1);
	}

	operator bool() const
	{
		return !m_done;
	}

private:
	KeyType m_key;
	bool m_done = false;
};

bool isDelimiter(char c)
{
	return isspace(c) || c == '.' || c == ';' || c == ',' || c == '-' || c == '?' || c == '!' || c == '(' || c == ')';
}

bool charInWord(char c)
{
	return isalnum(c) || c == '\''; // Handle single quotes for contractions
}

Message tryDecryptWord(Cipher::const_iterator& iter, const Cipher::const_iterator& end, Key& key, size_t& index)
{
	Message word;
	for (; iter != end; ++iter, ++index )
	{
		auto c = key.decrypt(*iter, index);
		if (isDelimiter(c))
		{
			// reached end of word
			return word;
		}

		if (!charInWord(c))
		{
			// illegal character
			return Message();
		}

		// valid character
		word.push_back(c);
	}
	return word;
}

Message tryDecrypt(const Cipher& cipher, Key& key)
{
	Message message;
	auto end = cipher.end();
	size_t index = 0;
	for (auto iter = cipher.begin(); iter != end;)
	{
		// skip over delimiters
		while (iter != end && isDelimiter(key.decrypt(*iter, index)))
		{
			message.push_back(key.decrypt(*iter, index++));
			++iter;
		}

		// process a word at a time
		Message word = tryDecryptWord(iter, end, key, index);
		if (iter == end)
		{
			// success!
			return message;
		}

		if (word.empty())
		{
			// wrong key
			return word;
		}

		// so far so good...
		message += word;
	}

	// success!
	return message;
}

Message tryDecrypt(const Cipher& cipher)
{
	for (Key key; key; key.next())
	{
		Message message = tryDecrypt(cipher, key);
		if (!message.empty())
		{
			return message;
		}
	}
	return Message("??");
}

Cipher readCipher()
{
	std::ifstream cipherFile("cipher.txt");
	Cipher cipher;
	while (cipherFile.good())
	{
		int c;
		cipherFile >> c;
		if( cipherFile.good())
		{
			cipher.push_back(c);
			cipherFile.ignore(1); // ignore ','
		}
	}
	return cipher;
}

int main()
{
	START_TIMER;
	Cipher cipher = readCipher();
	Message message = tryDecrypt(cipher);
	return result(107359, std::accumulate(message.begin(), message.end(), 0));
}
