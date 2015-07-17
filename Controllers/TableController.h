#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include "../Models/GameModel.h"

// controller for the cards on the table
class TableController 
{
public:
    TableController(GameModel *);                              // constructor
    ~TableController();                                         // destructor
    bool isPlayValid(std::shared_ptr<Card> cardToAdd) const;    // accessor - check if a card is a valid play
    void addCardToTable(std::shared_ptr<Card> cardToAdd);       // mutator -  add card to table
    void resetTable();                                          // mutator - clear table of cards
private:
    GameModel * gameModel_;                                   // pointer to table model
};

#endif
