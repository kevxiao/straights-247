#ifndef HUMANPLAYERCONTROLLER_H
#define HUMANPLAYERCONTROLLER_H

#include "PlayerController.h"
#include "../Models/Command.h"

// controller for the human players, derived from player controller
class HumanPlayerController : public PlayerController
{
public:
    HumanPlayerController(TableController *table);                          // constructor
    ~HumanPlayerController();                                               // destructor
    void processCommand(Command commandToProcess, unsigned int playerNum);  // mutator - handle a command for a specific player
    void removePlayerModel(unsigned int playerNum);                         // mutator - remove a player as a human

    class InvalidPlayException {};                                          // exception for invalid play commands
    class InvalidDiscardException {};                                       // exception for invalid discard commands
};

#endif
