#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include "../Models/GameModel.h"
#include "DeckController.h"
#include "HumanPlayerController.h"
#include "ComputerPlayerController.h"
#include "TableController.h"

class GameController
{
public:
    GameController(GameModel *, DeckController *, TableController *);
    ~GameController();
    void processInput(std::string userInput);
    void startGame();
    void startRound();
    void startTurn();
    void endTurn();
    void endRound();

private:
    void initGame(std::string userInput);
    unsigned int determineStartPlayer() const;
    int determineWinner() const;
    void processPlayerCommand(std::string userInput);

    GameModel * gameModel_;
    DeckController * deckController_;
    TableController * tableController_;
    HumanPlayerController * humanPlayerController_;
    ComputerPlayerController * computerPlayerController_;
};

#endif
