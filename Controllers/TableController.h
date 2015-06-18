#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include "../Models/TableModel.h"

class TableController
{
public:
    TableController();
    ~TableController();
private:
    TableModel * tableModel;
};

#endif
