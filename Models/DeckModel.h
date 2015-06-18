#ifndef DECKMODEL_H
#define DECKMODEL_H

#include "Card.h"
#include "CardType.h"

const short CARD_COUNT = SUIT_COUNT * RANK_COUNT;

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
