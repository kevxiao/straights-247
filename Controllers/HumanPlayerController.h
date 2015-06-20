#ifndef HUMANPLAYERCONTROLLER_H
#define HUMANPLAYERCONTROLLER_H

#include "PlayerController.h"
#include "../Models/Command.h"

class HumanPlayerController : public PlayerController
{
public:
    HumanPlayerController(TableController *table);
    ~HumanPlayerController();
    void processCommand(Command commandToProcess, int playerNum);
    void removePlayerModel(int playerNum);
private:
    //Top secret stuff
};

#endif
