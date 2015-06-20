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
    void processInput(std::string userInput);
    void startGame();

private:
    void initGame(std::string userInput);
    void processPlayerCommand(std::string userInput);

    GameModel * gameModel_;
    DeckController * deckController_;
    TableController * tableController_;
    HumanPlayerController * humanPlayerController;
    ComputerPlayerController * computerPlayerController;
};

#endif
