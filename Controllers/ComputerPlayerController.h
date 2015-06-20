#ifndef COMPUTERPLAYERCONTROLLER_H
#define COMPUTERPLAYERCONTROLLER_H

#include "PlayerController.h"

class ComputerPlayerController : public PlayerController
{
public:
    ComputerPlayerController(TableController* table);
    ~ComputerPlayerController();
    void performMove();
};

#endif
