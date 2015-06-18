#ifndef COMPUTERPLAYERCONTROLLER_H
#define COMPUTERPLAYERCONTROLLER_H

#include "PlayerController.h"
#include "../Models/PlayerMove.h"

class ComputerPlayerController : public PlayerController
{
public:
    ComputerPlayerController();
    ~ComputerPlayerController();
    
    PlayerMove performMove();
};

#endif
