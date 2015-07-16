#ifndef _CARDTYPE_
#define _CARDTYPE_

#include <ostream>
#include <istream>
#include "../Lib/Constants.h"

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
