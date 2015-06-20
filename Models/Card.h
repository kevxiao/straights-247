#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "CardType.h"

// model for a card entity
class Card
{
public:
    Card(Suit, Rank);                                                       // constructor - using suit and rank
    Card(CardType);                                                         // constructor - using cardtype
    ~Card();                                                                // destructor
    Suit getSuit() const;                                                   // accessor - suit
	Rank getRank() const;                                                   // accessor - rank
    bool hasValue(CardType typeToCompare) const;                            // accessor - check if card has certain value

private:
    friend std::ostream & operator<<(std::ostream &out, const Card &c);     // output operator to output a card
    CardType cardValue_;                                                    // value of the card entity
};

#endif
