#ifndef DECKMODEL_H
#define DECKMODEL_H

#include "Card.h"
#include "CardType.h"

const unsigned short CARD_COUNT = 52;

class DeckModel
{
public:
    DeckModel();
    ~DeckModel();
    void shuffle(unsigned long);
    std::vector<Card *> getCards() const;
private:
    std::vector<Card *> cards_;
};

#endif
