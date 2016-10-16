/*
In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:

High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair
of eights beats a pair of fives (see example 1 below). But if two ranks tie, for example, both players have a
pair of queens, then highest cards in each hand are compared (see example 4 below); if the highest cards tie
then the next highest cards are compared, and so on.

Consider the following five hands dealt to two players:

Hand	 	Player 1	 	Player 2	 	Winner
1	 	 5H 5C 6S 7S KD   2C 3S 8S 8D TD   Player 2
         Pair of Fives     Pair of Eights

2	 	5D 8C 9S JS AC    2C 5C 7D 8S QH   Player 1
       Highest card Ace  Highest card Queen

3	 	2D 9C AS AH AC    3D 6D 7D TD QD   Player 2
          Three Aces     Flush with Diamonds

4	 	4D 6S 9H QH QC    3D 6D 7H QD QS   Player 1
		Pair of Queens    Pair of Queens
        Highest card Nine Highest card Seven

5	 	2H 2D 4C 4D 4S    3C 3D 3S 9S 9D   Player 1
        Full House        Full House
        With Three Fours  with Three Threes

The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains
ten cards (separated by a single space): the first five are Player 1's cards and the last five are Player 2's
cards. You can assume that all hands are valid (no invalid characters or repeated cards), each player's hand
is in no specific order, and in each hand there is a clear winner.

How many hands does Player 1 win?
*/

#include "TestUtils.h"

#include <algorithm>
#include <array>
#include <fstream>

enum Suit
{
	Clubs,
	Hearts,
	Diamonds,
	Spades
};

class Card
{
public:
	friend std::istream& operator>>(std::istream& istr, Card& card)
	{
		std::string value;
		istr >> value;
		switch (value[0])
		{
		case 'A':
			card.m_value = 12;
			break;
		case 'K':
			card.m_value = 11;
			break;
		case 'Q':
			card.m_value = 10;
			break;
		case 'J':
			card.m_value = 9;
			break;
		case 'T':
			card.m_value = 8;
			break;
		default:
			card.m_value = value[0] - '2';
			break;
		}

		switch (value[1])
		{
		case 'C':
			card.m_suit = Clubs;
			break;
		case 'H':
			card.m_suit = Hearts;
			break;
		case 'D':
			card.m_suit = Diamonds;
			break;
		case 'S':
			card.m_suit = Spades;
			break;
		}

		return istr;
	}

	Suit suit() const { return m_suit; }
	
	// '2' has value 0, '3' has value 1, ... 'A' has value 12
	int value() const { return m_value; }

private:
	Suit m_suit;
	int m_value;
};

class Hand
{
public:
	typedef std::pair<int, int> Score;

	Score score() const
	{
		Score score(0, 0);
		bool handled =
			isRoyalFlush(score) ||
			isStraightFlush(score) ||
			isFullHouse(score) ||
			isFourOfKind(score) ||
			isFlush(score) ||
			isStraight(score) ||
			isThreeOfKind(score) ||
			isTwoPair(score) ||
			isPair(score) ||
			isHighCard(score);

		return score;
	}

	friend std::istream& operator>>(std::istream& istr, Hand& hand)
	{
		for (Card& card : hand.m_cards)
		{
			istr >> card;
		}

		hand.sort();

		return istr;
	}

private:
	void sort()
	{
		std::sort(m_cards.begin(), m_cards.end(), [](const Card& c1, const Card& c2) {
			return c1.value() > c2.value();
		});
	}

	// Royal Flush : (9, 0)
	bool isRoyalFlush(Score& s) const
	{
		if (v(0) != 12)
		{
			return false;
		}

		if (!isStraightFlush(s))
		{
			return false;
		}

		s.first = 9; s.second = 0;
		return true;
	}

	// Straight Flush : (8, card1)
	bool isStraightFlush(Score& s) const
	{
		if (!isFlush(s))
		{
			return false;
		}

		if (!isStraight(s))
		{
			return false;
		}

		s.first = 8;
		s.second = v(0);
		return true;
	}

	// Four of a Kind : (7, 13*quad + card)
	bool isFourOfKind(Score& s) const
	{
		const bool ok = (v(1) == v(2) && v(2) == v(3)) && (v(0) == v(1) || v(3) == v(4));
		if (!ok)
		{
			return false;
		}

		// calculate score
		s.first = 7;
		s.second = 13 * v(1);
		s.second += v(0) != v(1) ? v(0) : v(4);
		return true;
	}

	// Full House : (6, 13*triple + pair)
	bool isFullHouse(Score& s) const
	{
		const bool ok = v(0) == v(1) && v(3) == v(4) && (v(2) == v(1) || v(2) == v(3));
		if (!ok)
		{
			return false;
		}

		s.first = 6;
		s.second = 13 * v(2);
		s.second += v(2) == v(1) ? v(3) : v(1);
		return true;
	}

	// Flush : (5, 13^4*card1 + 13^3*card2 + 13^2*card3 + 13*card4 + card5)
	bool isFlush(Score& s) const
	{
		const Suit suit = m_cards[0].suit();
		for (int i = 1; i < m_cards.size(); ++i)
		{
			if (suit != m_cards[i].suit())
			{
				return false;
			}
		}

		// calculate score
		s.first = 5;
		s.second = 0;
		int p = 4;
		for (int i = 0; i < m_cards.size(); ++i, --p)
		{
			s.second += v(i) * intPow(13, p);
		}

		return true;
	}

	// Straight : (4, card1)
	bool isStraight(Score& s) const
	{
		auto value = v(0);
		for (int i = 1; i < m_cards.size(); ++i)
		{
			if (v(i) != --value)
			{
				return false;
			}
		}

		// calculate score
		s.first = 4;
		s.second = v(0);
		return true;
	}

	// Three of a Kind : (3, 13^2*triple + 13*card1 + card2)
	bool isThreeOfKind(Score& s) const
	{
		s.first = 3;
		if (v(0) == v(1) && v(1) == v(2))
		{
			s.second = 13 * 13 * v(0) + 13 * v(3) + v(4);
			return true;
		}

		if (v(1) == v(2) && v(2) == v(3))
		{
			s.second = 13 * 13 * v(1) + 13 * v(0) + v(4);
			return true;
		}

		if (v(2) == v(3) && v(3) == v(4))
		{
			s.second = 13 * 13 * v(2) + 13 * v(0) + 13 * v(1);
			return true;
		}

		return false;
	}

	// Two Pairs : (2, 13^2*pair1 + 13*pair2 + card)
	bool isTwoPair(Score& s) const
	{
		s.first = 2;
		if (v(0) == v(1))
		{
			if (v(2) == v(3))
			{
				s.second = 13 * 13 * v(0) + 13 * v(2) + v(4);
				return true;
			}

			if (v(3) == v(4))
			{
				s.second = 13 * 13 * v(0) + 13 * v(3) + v(2);
				return true;
			}

			return false;
		}

		if (v(1) == v(2))
		{
			if (v(3) == v(4))
			{
				s.second = 13 * 13 * v(1) + 13 * v(3) + v(0);
				return true;
			}
		}

		return false;
	}

	// One Pair : (1, 13^3*pair + 13^2*card1 + 13*card2 + card3)
	bool isPair(Score& s) const
	{
		s.first = 1;
		if (v(0) == v(1))
		{
			s.second = 13 * 13 * 13 * v(0) + 13 * 13 * v(2) + 13 * v(3) + v(4);
			return true;
		}

		if (v(1) == v(2))
		{
			s.second = 13 * 13 * 13 * v(1) + 13 * 13 * v(0) + 13 * v(3) + v(4);
			return true;
		}

		if (v(2) == v(3))
		{
			s.second = 13 * 13 * 13 * v(2) + 13 * 13 * v(0) + 13 * v(1) + v(4);
			return true;
		}

		if (v(3) == v(4))
		{
			s.second = 13 * 13 * 13 * v(3) + 13 * 13 * v(0) + 13 * v(1) + v(2);
			return true;
		}

		return false;
	}

	// High Card : (0, 13^4*card1 + 13^3*card2 + 13^2*card3 + 13*card4 + card5)
	bool isHighCard(Score& s) const
	{
		s.first = 0;
		s.second = v(0);
		return true;
	}

	int v(size_t i) const
	{
		return m_cards[i].value();
	}

	int intPow(int b, unsigned int p) const
	{
		if (p == 0) return 1;
		while (--p) b *= b;
		return b;
	}

	std::array<Card, 5> m_cards;
};

int main()
{
	START_TIMER;

	std::ifstream ifstr("poker.txt");
	unsigned int answer = 0;
	for (int i = 0; i < 1000; ++i)
	{
		Hand hand1, hand2;
		ifstr >> hand1 >> hand2;
		if (hand1.score() > hand2.score()) ++answer;
	}

	return result(376, answer);
}
