#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <map>
#include <memory>
#include "Card.h"
#include "CardType.h"
#include "../Lib/Constants.h"

// model of a table and cards played on it
class TableModel 
{
public:
    TableModel();                                                                               // constructor
    ~TableModel();                                                                              // destructor
    void resetTable();                                                                          // mutator - clear cards on table
    void addCardToTable(std::shared_ptr<Card> cardToAdd);                                       // mutator - add one card to table
    const std::map<Suit, std::map<Rank, std::shared_ptr<Card> > > * getCardsOnTable() const;    // accessor - get the list of cards on table
private:
    std::map<Suit, std::map<Rank, std::shared_ptr<Card> > > cardsOnTable_;                      // ordered map of cards on table
};

#endif
