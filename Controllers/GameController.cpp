#include "GameController.h"

GameController::GameController(GameModel *gameModel, DeckController *deckController) : gameModel_(gameModel), deckController_(deckController)
{
}

GameController::~GameController()
{
}

void GameController::processInput(std::string input)
{
}

void GameController::startGame() {
    deckController_->shuffle();
    gameModel_->setGameStatus(INIT_GAME);
}