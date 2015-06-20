#ifndef COMPUTERPLAYERCONTROLLER_H
#define COMPUTERPLAYERCONTROLLER_H

#include "PlayerController.h"

// controller for the computer players, derived from player controller
class ComputerPlayerController : public PlayerController
{
public:
    ComputerPlayerController(TableController* table);       // constructor
    ~ComputerPlayerController();                            // destructor
    void performMove(unsigned int playerNum);               // mutator - AI perform move for the specified computer player
};

#endif
