/* Deck controller may not be needed since it only calls
 * methods from the deck model. The deck model can simply be
 * used in other controllers instead of having everything go
 * through the deck controller.
 */

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
