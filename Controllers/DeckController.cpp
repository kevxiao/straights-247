/* Deck controller may not be needed since it only calls
 * methods from the deck model. The deck model can simply be
 * used in other controllers instead of having everything go
 * through the deck controller.
 */

#include "DeckController.h"

// construct deck controller with a seed value for random shuffle and a deck model
DeckController::DeckController(GameModel * gameModel): gameModel_(gameModel), shuffleSeed_(0)
{
}

// default destructor
DeckController::~DeckController()
{
}

// reset the deck by replacing the deck model
void DeckController::reset() {
    gameModel_->resetDeck();
}

// set the seed to use for shuffling the deck
void DeckController::setSeed(unsigned long seed)
{
    shuffleSeed_ = seed;
}

// shuffle cards in specified way using the seed
void DeckController::shuffle() {
    gameModel_->shuffle(shuffleSeed_);
}

// return the list of cards in the deck.
const std::vector<std::shared_ptr<Card> > * DeckController::getCards() const {
    return gameModel_->getCards();
}
