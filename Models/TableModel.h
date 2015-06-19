#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <map>
#include <memory>
#include "Card.h"
#include "CardType.h"

class TableModel 
{
public:
    TableModel();
    ~TableModel();
    void resetTable();
    void addCardToTable(std::shared_ptr<Card> cardToAdd);
    std::map<Suit, std::map<Rank, std::shared_ptr<Card> > > getCardsOnTable() const;
private:
    std::map<Suit, std::map<Rank, std::shared_ptr<Card> > > cardsOnTable_; //Split into array of vectors of card *
};

#endif
