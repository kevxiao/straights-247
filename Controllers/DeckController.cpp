/* Deck controller may not be needed since it only calls
 * methods from the deck model. The deck model can simply be
 * used in other controllers instead of having everything go
 * through the deck controller.
 */

#include "DeckController.h"

DeckController::DeckController(unsigned long seed, DeckModel * deckModel): deckModel_(deckModel), shuffleSeed_(seed)
{
}

DeckController::~DeckController()
{
    delete deckModel_;
}

void DeckController::reset() {
    delete deckModel_;
    deckModel_ = new DeckModel();
}

void DeckController::shuffle() {
    deckModel_->shuffle(shuffleSeed_);
}

const std::vector<std::shared_ptr<Card> > * DeckController::getCards() const {
    return deckModel_->getCards();
}
