#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include "../Models/GameModel.h"
#include "DeckController.h"
#include "HumanPlayerController.h"
#include "ComputerPlayerController.h"
#include "TableController.h"

// controller for main game states and flow
class GameController
{
public:
    GameController(GameModel *, DeckController *, TableController *);   // constructor
    ~GameController();                                                  // destructor
    void processInput(std::string userInput);                           // mutator - process input
    void startGame();                                                   // mutator - set states and perform start of game actions
    void startRound();                                                  // mutator - set states and perform start of round actions
    void startTurn();                                                   // mutator - determine which player has 7S and needs to start
    void endTurn();                                                     // mutator - end a turn and move on to the next turn
    void endRound();                                                    // mutator - display required info and transiton to next round

private:
    void initGame(std::string userInput);                               // mutator - initialize game with players
    unsigned int determineStartPlayer() const;                          // accessor - determine player to start a round
    int determineWinner() const;                                        // accessor - determine if round ends with a winner
    void processPlayerCommand(std::string userInput);                   // mutator - process command by a human player into actions

    GameModel * gameModel_;                                             // pointer to the model
    DeckController * deckController_;                                   // pointer to the deck controller
    TableController * tableController_;                                 // pointer to the table controller
    HumanPlayerController * humanPlayerController_;                     // pointer to human player controller
    ComputerPlayerController * computerPlayerController_;               // pointer to computer player controller
};

#endif
