#ifndef COMPUTERPLAYERCONTROLLER_H
#define COMPUTERPLAYERCONTROLLER_H

#include "PlayerController.h"
#include "../Models/PlayerMoveEvent.h"

class ComputerPlayerController : public PlayerController
{
public:
    ComputerPlayerController();
    ~ComputerPlayerController();
    
    PlayerMoveEvent performMove();
};

#endif
