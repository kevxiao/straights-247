#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "CardType.h"

class Card
{
public:
    Card(Suit, Rank);
    Card(CardType);
    ~Card();
    Suit getSuit() const;
	Rank getRank() const;
    bool hasValue(CardType typeToCompare) const;

private:
    friend std::ostream & operator<<(std::ostream &out, const Card &c);
    CardType cardValue_;
};

#endif
