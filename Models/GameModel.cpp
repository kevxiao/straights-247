#include "GameModel.h"

GameModel::GameModel() : gameStatus_(INIT_GAME)
{
}

GameModel::~GameModel() 
{
}

GameStatus GameModel::getGameStatus() const 
{
    return gameStatus_;
}

void GameModel::setGameStatus(GameStatus newGameStatus) 
{
    gameStatus_ = newGameStatus;
    notify();
}

void GameModel::addPlayer(std::shared_ptr<PlayerModel> playerToAdd) 
{
    players_.push_back(playerToAdd);
}

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

unsigned int GameModel::getCurPlayerNum() const
{
    return curPlayerNum_;
}

void GameModel::setCurPlayerNum(unsigned int newPlayerNum)
{
    curPlayerNum_ = newPlayerNum;
}

unsigned int GameModel::getNumPlayers() const
{
    return NUM_PLAYERS;
}

void GameModel::incrementCurPlayerNum()
{
    ++curPlayerNum_;
    if (curPlayerNum_ >= getNumPlayers())
    {
        curPlayerNum_ = 0;
    }
}
