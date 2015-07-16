#include <iostream>
#include "CardModel.h"

// constructor usign the suit and the rank
Card::Card(Suit cardSuit, Rank cardRank) : cardValue_(cardSuit, cardRank)
{
}

// constructor using a card type
Card::Card(CardType cardType) : cardValue_(cardType.getSuit(), cardType.getRank())
{
}

// default destructor
Card::~Card()
{
}

// get suit of card
Suit Card::getSuit() const
{
    return cardValue_.getSuit();
}

// get rank of card
Rank Card::getRank() const
{
    return cardValue_.getRank();
}

// check if card equals a value
bool Card::hasValue(CardType typeToCompare) const
{
    return cardValue_ == typeToCompare;
}

// print out the card value
std::ostream &operator<<(std::ostream &out, const Card &c){
    out << c.cardValue_;
    return out;
}
