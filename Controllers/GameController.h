#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include "../Models/GameModel.h"
#include "DeckController.h"
#include "HumanPlayerController.h"
#include "ComputerPlayerController.h"

class GameController
{
public:
    GameController(GameModel *, DeckController *);
    ~GameController();
    void processInput(std::string input);
    void startGame();

private:
    GameModel * gameModel_;
    DeckController * deckController_;
};

#endif
