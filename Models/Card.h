#ifndef CARD_H
#define CARD_H

#include "CardType.h"

class Card
{
    Card(Suit, Rank);
    Card(CardType);
    ~Card();
    Suit getSuit() const;
	Rank getRank() const;

private:
    CardType cardValue_;
};

#endif
