
#include "TableController.h"

TableController::TableController() 
{
}

TableController::~TableController() 
{
}

void TableController::addCardToTable(std::shared_ptr<Card> cardToAdd) 
{
    tableModel_->addCardToTable(cardToAdd);
}
