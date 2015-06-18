#ifndef DECKCONTROLLER_H
#define DECKCONTROLLER_H

#include "../Models/DeckModel.h"

class DeckController
{
public:
    DeckController();
    ~DeckController();
    void shuffle(int seed);
private:
    DeckModel * deckModel;
};

#endif
