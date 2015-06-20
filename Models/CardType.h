#ifndef _CARDTYPE_
#define _CARDTYPE_

#include <ostream>
#include <istream>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class CardType {
public:
	CardType(Suit, Rank);
    CardType(std::string cardTypeinString);
	Suit getSuit() const;
	Rank getRank() const;
	
private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const CardType &, const CardType &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const CardType &);

#endif
