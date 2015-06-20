#include <cassert>
#include "GameController.h"

GameController::GameController(GameModel *gameModel, DeckController *deckController, TableController * tableController) :
                               gameModel_(gameModel), deckController_(deckController), tableController_(tableController)
{
    humanPlayerController_ = new HumanPlayerController(tableController);
    computerPlayerController_ = new ComputerPlayerController(tableController);
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
    gameModel_->setGameStatus(INIT_GAME);
}

void GameController::startRound()
{
    deckController_->shuffle();
    auto deck = deckController_->getCards();
    std::vector<std::shared_ptr<Card> > hand;
    for (int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        for (int j = 0; j < deck->size() / gameModel_->getNumPlayers(); ++j)
        {
            hand.push_back((*deck).at(i * (deck->size() / gameModel_->getNumPlayers()) + j));
        }
        if (gameModel_->getPlayerModel(i)->isComputer())
        {
            computerPlayerController_->resetHand(hand, i);
        }
        else
        {
            humanPlayerController_->resetHand(hand, i);
        }
        hand.clear();
    }
    gameModel_->setCurPlayerNum(determineStartPlayer());
    gameModel_->setGameStatus(START_ROUND);
    startTurn();
}

void GameController::startTurn()
{
    if (gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->isComputer())
    {
        computerPlayerController_->setLegalMoves(gameModel_->getCurPlayerNum());
        computerPlayerController_->performMove(gameModel_->getCurPlayerNum());
        gameModel_->setGameStatus(END_TURN);
        gameModel_->incrementCurPlayerNum();
        startTurn();
    }
    else
    {
        humanPlayerController_->setLegalMoves(gameModel_->getCurPlayerNum());
        gameModel_->setGameStatus(START_TURN);
        gameModel_->setGameStatus(IN_TURN);
    }
}

void GameController::initGame(std::string userInput)
{
    assert(userInput.size() > 0 && (userInput.at(0) == 'h' || userInput.at(0) == 'c'));
    
    std::shared_ptr<PlayerModel> newPlayerModel = std::make_shared<PlayerModel>(gameModel_->getCurPlayerNum(), userInput.at(0) == 'c');
    gameModel_->addPlayer(newPlayerModel);
    gameModel_->incrementCurPlayerNum();

    if(userInput.at(0) == 'h')
    {
        humanPlayerController_->addPlayerModel(newPlayerModel);
    }
    else
    {
        computerPlayerController_->addPlayerModel(newPlayerModel);
    }
    if (gameModel_->getCurPlayerNum() == 0)
    {
        startRound();
    }
    else
    {
        gameModel_->setGameStatus(INIT_GAME);
    }
}

unsigned int GameController::determineStartPlayer()
{
    for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        if (gameModel_->getPlayerModel(i)->getCardFromHand(CardType(SPADE, SEVEN)) != std::shared_ptr<Card>(nullptr))
        {
            return i;
        }
    }
}

void GameController::processPlayerCommand(std::string userInput)
{
    Command playerCommand = Command(userInput);
    if(playerCommand.getType() == PLAY || playerCommand.getType() == DISCARD)
    {
        humanPlayerController_->processCommand(playerCommand, gameModel_->getCurPlayerNum());
    }
}
