#ifndef DECKMODEL_H
#define DECKMODEL_H

#include <memory>

#include "Card.h"
#include "CardType.h"

const unsigned short CARD_COUNT = 52;                                   // constant value for the number of cards in deck

// model of a deck entity
class DeckModel
{
public:
    DeckModel();                                                        // constructor
    ~DeckModel();                                                       // destructor
    void shuffle(unsigned long);                                        // mutator - shuffle order of cards
    const std::vector<std::shared_ptr<Card> > * getCards() const;       // accessor - get the cards in the deck in order
private:
    std::vector<std::shared_ptr<Card> > cards_;                         // ordered list of all cards in deck
};

#endif
