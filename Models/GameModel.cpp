#include "GameModel.h"

// constructor for game model
GameModel::GameModel() : gameStatus_(INIT_GAME)
{
}

// default destructor
GameModel::~GameModel() 
{
}

// get the game status
GameStatus GameModel::getGameStatus() const 
{
    return gameStatus_;
}

// set the game status and notify observers when new status is set
void GameModel::setGameStatus(GameStatus newGameStatus) 
{
    gameStatus_ = newGameStatus;
    notify();
}

// add a player to the game
void GameModel::addPlayer(std::shared_ptr<PlayerModel> playerToAdd) 
{
    players_.push_back(playerToAdd);
}

// get a player using the identifier
std::shared_ptr<PlayerModel> GameModel::getPlayerModel(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> selectedModel = nullptr;
    for(unsigned int counter = 0; counter < players_.size(); counter++)
    {
        if(players_.at(counter)->getPlayerNum() == playerNum)
        {
            selectedModel = players_.at(counter);
        }
    }
    return selectedModel;
}

// get the player whose turn it is
unsigned int GameModel::getCurPlayerNum() const
{
    return curPlayerNum_;
}

// set the player whose turn it will be
void GameModel::setCurPlayerNum(unsigned int newPlayerNum)
{
    curPlayerNum_ = newPlayerNum;
}

// increment and rotate through current players
void GameModel::incrementCurPlayerNum()
{
    ++curPlayerNum_;
    curPlayerNum_ = curPlayerNum_ % NUM_PLAYERS;
}

// set the winners of the game
void GameModel::setWinners(std::vector<unsigned int> winners)
{
    winners_ = winners;
}

// get the list of winners
std::vector<unsigned int> GameModel::getWinners() const
{
    return winners_;
}