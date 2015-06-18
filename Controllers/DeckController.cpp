/* Deck controller may not be needed since it only calls
 * methods from the deck model. The deck model can simply be
 * used in other controllers instead of having everything go
 * through the deck controller.
 */

#include <vector>
#include "../Models/Card.h"
#include "DeckController.h"

DeckController::DeckController(): deckModel(new DeckModel())
{
};

DeckController::~DeckController()
{
    delete deckModel;
};

void DeckController::shuffle(unsigned long seed = 0){
    deckModel->shuffle(seed);
}

std::vector<Card *> DeckController::getCards() const {
    return deckModel->getCards();
}
