#ifndef HUMANPLAYERCONTROLLER_H
#define HUMANPLAYERCONTROLLER_H

#include "PlayerController.h"
#include "../Models/Command.h"

class HumanPlayerController : public PlayerController
{
public:
    HumanPlayerController(TableController *table);
    ~HumanPlayerController();
    void processCommand(Command commandToProcess, unsigned int playerNum);
    void removePlayerModel(unsigned int playerNum);

    class InvalidPlayException {};
    class InvalidDiscardException {};

private:
    //Top secret stuff
};

#endif
