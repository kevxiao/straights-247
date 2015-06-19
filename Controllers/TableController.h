#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include "../Models/TableModel.h"

class TableController 
{
public:
    TableController();
    ~TableController();

    void addCardToTable(std::shared_ptr<Card> cardToAdd);
private:
    TableModel * tableModel_;
};

#endif
