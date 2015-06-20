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
    delete humanPlayerController_;
    delete computerPlayerController_;
    delete deckController_;
    delete tableController_;
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
    for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        for (unsigned int j = 0; j < deck->size() / gameModel_->getNumPlayers(); ++j)
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
    tableController_->resetTable();
    gameModel_->setCurPlayerNum(determineStartPlayer());
    gameModel_->setGameStatus(START_ROUND);
    startTurn();
}

void GameController::startTurn()
{
    if (gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->isComputer())
    {
        if (!computerPlayerController_->hasCards(gameModel_->getCurPlayerNum()))
        {
            endRound();
            return;
        }
        computerPlayerController_->setLegalMoves(gameModel_->getCurPlayerNum());
        computerPlayerController_->performMove(gameModel_->getCurPlayerNum());
        endTurn();
    }
    else
    {
        if (!humanPlayerController_->hasCards(gameModel_->getCurPlayerNum()))
        {
            endRound();
            return;
        }
        humanPlayerController_->setLegalMoves(gameModel_->getCurPlayerNum());
        gameModel_->setGameStatus(START_TURN);
        gameModel_->setGameStatus(IN_TURN);
    }
}

void GameController::endTurn()
{
    gameModel_->setGameStatus(END_TURN);
    gameModel_->incrementCurPlayerNum();
    startTurn();
}

void GameController::endRound()
{
    gameModel_->setGameStatus(END_ROUND);
    for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        if (gameModel_->getPlayerModel(i)->isComputer())
        {
            computerPlayerController_->incrementScore(gameModel_->getPlayerModel(i)->getValOfDiscards(), i);
        }
        else
        {
            humanPlayerController_->incrementScore(gameModel_->getPlayerModel(i)->getValOfDiscards(), i);
        }
    }
    int winner = determineWinner();
    if (winner >= 0)
    {
        gameModel_->setCurPlayerNum((unsigned int)winner);
        gameModel_->setGameStatus(END_GAME);
    }
    else
    {
        startRound();
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

unsigned int GameController::determineStartPlayer() const
{
    for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        if (gameModel_->getPlayerModel(i)->getCardFromHand(CardType(SPADE, SEVEN)) != std::shared_ptr<Card>(nullptr))
        {
            return i;
        }
    }
    return 0;
}

int GameController::determineWinner() const
{
    unsigned int max = gameModel_->getPlayerModel(0)->getScore();
    unsigned int min = max, minPlayer = 0;
    unsigned int value;
    for (unsigned int i = 1; i < gameModel_->getNumPlayers(); ++i)
    {
        value = gameModel_->getPlayerModel(i)->getScore();
        if (value > max)
        {
            max = value;
        }
        else if (value < min)
        {
            min = value;
            minPlayer = i;
        }
    }
    if (max >= 80)
    {
        return minPlayer;
    }
    else
    {
        return -1;
    }
}

void GameController::processPlayerCommand(std::string userInput)
{
    Command playerCommand = Command(userInput);
    if(playerCommand.getType() == Type::PLAY || playerCommand.getType() == Type::DISCARD)
    {
        humanPlayerController_->processCommand(playerCommand, gameModel_->getCurPlayerNum());
        endTurn();
    }
    else if(playerCommand.getType() == Type::DECK)
    {
        gameModel_->setGameStatus(DECK_COMMAND);
        gameModel_->setGameStatus(IN_TURN);
    }
    else if(playerCommand.getType() == Type::RAGEQUIT)
    {
        gameModel_->setGameStatus(RAGEQUIT_COMMAND);
        std::shared_ptr<PlayerModel> modelToComputerize = gameModel_->getPlayerModel(gameModel_->getCurPlayerNum());
        humanPlayerController_->removePlayerModel(gameModel_->getCurPlayerNum());
        computerPlayerController_->addPlayerModel(modelToComputerize);
        modelToComputerize->makeComputer();
        startTurn();
    }
    else if(playerCommand.getType() == Type::QUIT)
    {
        gameModel_->setGameStatus(EXIT_GAME);
    }
}
