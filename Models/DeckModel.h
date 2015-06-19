#ifndef DECKMODEL_H
#define DECKMODEL_H

#include <memory>

#include "Card.h"
#include "CardType.h"

const unsigned short CARD_COUNT = 52;

class DeckModel
{
public:
    DeckModel();
    ~DeckModel();
    void shuffle(unsigned long);
    const std::vector<std::shared_ptr<Card> > * getCards() const;
private:
    std::vector<std::shared_ptr<Card> > cards_;
};

#endif
