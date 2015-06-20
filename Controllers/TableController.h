#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include "../Models/TableModel.h"

// controller for the cards on the table
class TableController 
{
public:
    TableController(TableModel *);                              // constructor
    ~TableController();                                         // destructor
    bool isPlayValid(std::shared_ptr<Card> cardToAdd) const;    // accessor - check if a card is a valid play
    void addCardToTable(std::shared_ptr<Card> cardToAdd);       // mutator -  add card to table
    void resetTable();                                          // mutator - clear table of cards
private:
    TableModel * tableModel_;                                   // pointer to table model
};

#endif
