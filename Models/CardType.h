#ifndef _CARDTYPE_
#define _CARDTYPE_

#include <ostream>
#include <istream>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

// value of cards
class CardType {
public:
	CardType(Suit, Rank);                                           // constructor - using suit and rank
    CardType(std::string cardTypeinString);                         // constructor - using string
	Suit getSuit() const;                                           // accessor - suit value
	Rank getRank() const;                                           // accessor - rank value
	
private:
	Suit suit_;                                                     // suit of card
	Rank rank_;                                                     // rank of card
};

bool operator==(const CardType &, const CardType &);                // check if values are equal

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const CardType &);

#endif
