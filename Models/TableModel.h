#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <map>
#include "Card.h"
#include "CardType.h"

class TableModel
{
public:
    TableModel();
    ~TableModel();
    void resetTable();
    void addCardToTable(Card *);
    std::map<Suit, std::map<Rank, Card *> > getCardsOnTable() const;
    
private:
    std::map<Suit, std::map<Rank, Card *> > cardsOnTable_; //Split into array of vectors of card *
};

#endif
