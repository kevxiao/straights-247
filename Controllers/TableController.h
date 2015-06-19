#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include "../Models/TableModel.h"

class TableController 
{
public:
    TableController(TableModel *);
    ~TableController();
    bool isPlayValid(std::shared_ptr<Card> cardToAdd) const;
    void addCardToTable(std::shared_ptr<Card> cardToAdd);
private:
    TableModel * tableModel_;
};

#endif
