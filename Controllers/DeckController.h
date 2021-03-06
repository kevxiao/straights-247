/* Deck controller may not be needed since it only calls
 * methods from the deck model. The deck model can simply be
 * used in other controllers instead of having everything go
 * through the deck controller.
 */

#ifndef DECKCONTROLLER_H
#define DECKCONTROLLER_H

#include <vector>

#include "../Models/GameModel.h"
#include "../Models/CardModel.h"

// controller for the deck of cards
class DeckController
{
public:
    DeckController(GameModel *);                                    // constructor
    ~DeckController();                                              // destructor
    void reset();                                                   // mutator - reset deck order
    void setSeed(unsigned long);                                    // mutator - set the shuffle seed
    void shuffle();                                                 // mutator - shuffle the deck
    const std::vector<std::shared_ptr<Card> > * getCards() const;   // accessor - get card list in order
private:
    GameModel * gameModel_;                                         // pointer to the deck's model
    unsigned long shuffleSeed_;                                     // seed to use for shuffling
};

#endif
