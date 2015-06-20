#include <cassert>
#include "GameController.h"

GameController::GameController(GameModel *gameModel, DeckController *deckController) : gameModel_(gameModel), deckController_(deckController)
{
}

GameController::~GameController()
{
}

void GameController::processInput(std::string userInput)
{
    switch(gameModel_->getGameStatus())
    {
        case INIT_GAME:
            initGame(userInput);
            break;
        case IN_TURN:
            processPlayerCommand(userInput);
            break;
        default: break;
    }
}

void GameController::startGame() {
    deckController_->shuffle();
    gameModel_->setCurPlayerNum(0);
    gameModel_->setGameStatus(INIT_GAME);
}

void GameController::initGame(std::string userInput)
{
    assert(userInput.size() > 0 && (userInput.at(0) == 'h' || userInput.at(0) == 'c'));
    
    std::shared_ptr<PlayerModel> newPlayerModel = std::make_shared<PlayerModel>(gameModel_->getCurPlayerNum(), userInput.at(0) == 'c');
    gameModel_->addPlayer(newPlayerModel);

    if(userInput.at(0) == 'h')
    {
        //Add player to Human Player Controller
    }
    else
    {
        //Add player to Computer Player Controller
    }
}

void GameController::processPlayerCommand(std::string userInput)
{
    Command playerCommand = Command(userInput);
    if(playerCommand.getType() == PLAY || playerCommand.getType() == DISCARD)
    {
        humanPlayerController->processCommand(playerCommand, gameModel_->getCurPlayerNum());
    }
}
