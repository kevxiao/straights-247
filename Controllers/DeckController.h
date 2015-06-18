#ifndef DECKCONTROLLER_H
#define DECKCONTROLLER_H

#include "../Models/DeckModel.h"
#include "../Models/Card.h"

class DeckController
{
public:
    DeckController();
    ~DeckController();
    void shuffle(unsigned long);
    std::vector<Card *> getCards() const;
private:
    DeckModel * deckModel;
};

#endif
