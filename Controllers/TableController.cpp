
#include "TableController.h"

// constructor using the table model
TableController::TableController(GameModel * gameModel) : gameModel_(gameModel)
{
}

// default destructor
TableController::~TableController() 
{
}

// check if a card is a valid play
bool TableController::isPlayValid(std::shared_ptr<Card> cardToAdd) const
{
    auto table = gameModel_->getCardsOnTable();
    // has to be a 7 or adjacent to a card on the table
    return cardToAdd->getRank() == SEVEN ||
        table->find(cardToAdd->getSuit())->second.find((Rank)(int(cardToAdd->getRank()) + 1)) != table->find(cardToAdd->getSuit())->second.cend() ||
        table->find(cardToAdd->getSuit())->second.find((Rank)(int(cardToAdd->getRank()) - 1)) != table->find(cardToAdd->getSuit())->second.cend();
}

// add a card to table if it is valid
void TableController::addCardToTable(std::shared_ptr<Card> cardToAdd) 
{
    if (isPlayValid(cardToAdd)) {
        gameModel_->addCardToTable(cardToAdd);
    }
}

// clear the table
void TableController::resetTable()
{
    gameModel_->resetTable();
}
