#include "GameModel.h"

GameModel::GameModel() : gameStatus_(INIT_GAME)
{
}

GameModel::~GameModel() 
{
}

GameStatus GameModel::gameStatus() const 
{
    return gameStatus_;
}

void GameModel::setGameStatus(GameStatus newGameStatus) 
{
    gameStatus_ = newGameStatus;
    notify();
}

std::queue<GameEvent *> GameModel::getGameEvents() 
{
    return gameEvents_;
}

void GameModel::addPlayer(PlayerModel * playerToAdd) 
{
    players_.push_back(playerToAdd);
}

PlayerModel * GameModel::getPlayerModel(unsigned int playerNum)
{
    PlayerModel *selectedModel = nullptr;
    for(unsigned int counter = 0; counter < players_.size(); counter++)
    {
        if(players_.at(counter)->getPlayerNum() == playerNum)
        {
            selectedModel = players_.at(counter);
        }
    }
    return selectedModel;
}

unsigned int GameModel::getCurPlayerNum()
{
    return curPlayerNum_;
}

void GameModel::incrementCurPlayerNum()
{
    curPlayerNum_ = (curPlayerNum_ + 1)%4; //TODO: Change 4 to be the NUMOFPLAYERS
}
