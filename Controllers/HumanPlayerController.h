#ifndef HUMANPLAYERCONTROLLER_H
#define HUMANPLAYERCONTROLLER_H

#include "PlayerController.h"
#include "../Models/Command.h"
#include "../Models/PlayerMove.h"
#include "../Models/PlayerModel.h"

class HumanPlayerController : public PlayerController
{
public:
    HumanPlayerController();
    ~HumanPlayerController();
    PlayerMove processCommand(Command commandToProcess, int playerNum);
    PlayerModel * getPlayerModel(int playerNum);
    void removePlayerModel(int playerNum);
private:
    //Top secret stuff
};

#endif
