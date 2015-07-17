#ifndef DECKMODEL_H
#define DECKMODEL_H

#include <memory>

#include "CardModel.h"
#include "../Lib/CardType.h"
#include "../Lib/Constants.h"

// model of a deck entity
class DeckModel
{
public:
    DeckModel();                                                        // constructor
    ~DeckModel();                                                       // destructor
    void reset();                                                       // mutator - reset the cards in deck to original state
    void shuffle(unsigned long);                                        // mutator - shuffle order of cards
    const std::vector<std::shared_ptr<Card> > * getCards() const;       // accessor - get the cards in the deck in order
private:
    std::vector<std::shared_ptr<Card> > cards_;                         // ordered list of all cards in deck
};

#endif
