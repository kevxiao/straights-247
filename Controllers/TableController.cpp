
#include "TableController.h"

TableController::TableController(TableModel * tableModel) : tableModel_(tableModel)
{
}

TableController::~TableController() 
{
}

bool TableController::isPlayValid(std::shared_ptr<Card> cardToAdd) const
{
    auto table = tableModel_->getCardsOnTable();
    return cardToAdd->getRank() == SEVEN ||
        table->find(cardToAdd->getSuit())->second.find((Rank)(int(cardToAdd->getRank()) + 1)) != table->find(cardToAdd->getSuit())->second.cend() ||
        table->find(cardToAdd->getSuit())->second.find((Rank)(int(cardToAdd->getRank()) - 1)) != table->find(cardToAdd->getSuit())->second.cend();
}

void TableController::addCardToTable(std::shared_ptr<Card> cardToAdd) 
{
    if (isPlayValid(cardToAdd)) {
        tableModel_->addCardToTable(cardToAdd);
    }
}
