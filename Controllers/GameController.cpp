#include <cassert>
#include "GameController.h"

// constructor for game controller with all the required models and controllers
GameController::GameController(GameModel *gameModel, DeckController *deckController, TableController * tableController) :
                               gameModel_(gameModel), deckController_(deckController), tableController_(tableController)
{
    // create the human and computer controllers
    humanPlayerController_ = new HumanPlayerController(tableController);
    computerPlayerController_ = new ComputerPlayerController(tableController);
}

// destructor deletes all the controllers that will not be deleted by the view
GameController::~GameController()
{
    delete humanPlayerController_;
    delete computerPlayerController_;
    delete deckController_;
    delete tableController_;
}

// process an input for a certain stage of the game
void GameController::processInput(std::string userInput)
{
    // deal with initialization stage and game stage separately
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

// start game with setting game status
void GameController::startGame() {
    gameModel_->setGameStatus(INIT_GAME);
}

// start a round by shuffling distributing the deck to the players' hands, resetting the player and determining starting player
void GameController::startRound()
{
    deckController_->shuffle();
    auto deck = deckController_->getCards();
    std::vector<std::shared_ptr<Card> > hand;
    // create the hand
    for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        for (unsigned int j = 0; j < deck->size() / gameModel_->getNumPlayers(); ++j)
        {
            hand.push_back((*deck).at(i * (deck->size() / gameModel_->getNumPlayers()) + j));
        }
        // set the player's hand to the allocated hand
        if (gameModel_->getPlayerModel(i)->isComputer())
        {
            computerPlayerController_->resetHand(hand, i);
        }
        else
        {
            humanPlayerController_->resetHand(hand, i);
        }
        // start new hand
        hand.clear();
    }
    tableController_->resetTable();
    // set the current player to the start player that is determined by the seven of spages
    gameModel_->setCurPlayerNum(determineStartPlayer());
    gameModel_->setGameStatus(START_ROUND);
    startTurn();
}

// start a player's turn by performing a move if computer, or displaying the legal moves and prompting the human player
void GameController::startTurn()
{
    if (gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->isComputer())
    {
        if (!computerPlayerController_->hasCards(gameModel_->getCurPlayerNum()))
        {
            endRound();
            return;
        }
        // perform a legal move
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
        // first start turn and then transition to being in the turn
        humanPlayerController_->setLegalMoves(gameModel_->getCurPlayerNum());
        gameModel_->setGameStatus(START_TURN);
        gameModel_->setGameStatus(IN_TURN);
    }
}

// end turn by moving to next player
void GameController::endTurn()
{
    gameModel_->setGameStatus(END_TURN);
    gameModel_->incrementCurPlayerNum();
    startTurn();
}

// end round by getting the values of the discards and then checking for a winner
void GameController::endRound()
{
    gameModel_->setGameStatus(END_ROUND);
    for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        // add the discard score to the total player score
        if (gameModel_->getPlayerModel(i)->isComputer())
        {
            computerPlayerController_->incrementScore(gameModel_->getPlayerModel(i)->getValOfDiscards(), i);
        }
        else
        {
            humanPlayerController_->incrementScore(gameModel_->getPlayerModel(i)->getValOfDiscards(), i);
        }
    }
    // check for winner
    auto winner = determineWinner();
    if (!winner.empty())
    {
        gameModel_->setWinners(winner);
        gameModel_->setGameStatus(END_GAME);
    }
    else
    {
        startRound();
    }
}

// initialize game with different type of players
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

// determine which player should start
unsigned int GameController::determineStartPlayer() const
{
    for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
    {
        // check for the 7 of spades
        if (gameModel_->getPlayerModel(i)->getCardFromHand(CardType(SPADE, SEVEN)) != std::shared_ptr<Card>(nullptr))
        {
            return i;
        }
    }
    return 0;
}

// determine if there is a winner at this time
std::vector<unsigned int> GameController::determineWinner() const
{
    unsigned int max = gameModel_->getPlayerModel(0)->getScore();
    unsigned int min = max;
    std::vector<unsigned int> winners;
    unsigned int value;
    for (unsigned int i = 1; i < gameModel_->getNumPlayers(); ++i)
    {
        value = gameModel_->getPlayerModel(i)->getScore();
        // set max value
        if (value > max)
        {
            max = value;
        }
        // set min value and player with min value
        else if (value < min)
        {
            min = value;
        }
    }
    // only return winner if someone has a score over 80
    if (max >= 80)
    {
        for (unsigned int i = 1; i < gameModel_->getNumPlayers(); ++i)
        {
            value = gameModel_->getPlayerModel(i)->getScore();
            if (value == min) {
                winners.push_back(i);
            }
        }
    }
    return winners;
}

// process a player's command and perform the correct answers
void GameController::processPlayerCommand(std::string userInput)
{
    Command playerCommand = Command(userInput);
    // make the action and move to next turn if playing or discarding
    if(playerCommand.getType() == Type::PLAY || playerCommand.getType() == Type::DISCARD)
    {
        humanPlayerController_->processCommand(playerCommand, gameModel_->getCurPlayerNum());
        endTurn();
    }
    // change game status to show deck and then go back to in turn
    else if(playerCommand.getType() == Type::DECK)
    {
        gameModel_->setGameStatus(DECK_COMMAND);
        gameModel_->setGameStatus(IN_TURN);
    }
    // move model from human controller to computer controller and restarts the turn
    else if(playerCommand.getType() == Type::RAGEQUIT)
    {
        gameModel_->setGameStatus(RAGEQUIT_COMMAND);
        std::shared_ptr<PlayerModel> modelToComputerize = gameModel_->getPlayerModel(gameModel_->getCurPlayerNum());
        humanPlayerController_->removePlayerModel(gameModel_->getCurPlayerNum());
        computerPlayerController_->addPlayerModel(modelToComputerize);
        modelToComputerize->makeComputer();
        startTurn();
    }
    // set exit game status if quitting
    else if(playerCommand.getType() == Type::QUIT)
    {
        gameModel_->setGameStatus(EXIT_GAME);
    }
}
