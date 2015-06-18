
#include "Card.h"

Card::Card(Suit cardSuit, Rank cardRank) : cardValue_(cardSuit, cardRank)
{
}

Card::Card(CardType cardType) : cardValue_(cardType.getSuit(), cardType.getRank())
{
}

Card::~Card()
{
}

Suit Card::getSuit() const
{
    return cardValue_.getSuit();
}

Rank Card::getRank() const
{
    return cardValue_.getRank();
}
