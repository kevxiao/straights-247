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
