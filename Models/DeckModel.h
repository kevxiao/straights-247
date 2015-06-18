#ifndef DECKMODEL_H
#define DECKMODEL_H

#include "Card.h"

class DeckModel
{
public:
    DeckModel();
    ~DeckModel();
    Card * cards_[52]; //Let's not make this public
};

#endif
