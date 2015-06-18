#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "Card.h"

class TableModel
{
public:
    TableModel();
    ~TableModel();
    
    void resetTable();
    
private:
    vector<Card *> cardsOnTable; //Split into array of vectors of card *
};

#endif
