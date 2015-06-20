#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <queue>

#include "PlayerModel.h"
#include "../Lib/Subject.h"

enum GameStatus {INIT_GAME, START_ROUND, START_TURN, IN_TURN, DECK_COMMAND, RAGEQUIT_COMMAND, END_TURN, END_ROUND, END_GAME, STATUS_COUNT};

class GameModel: public Subject
{
public:
    GameModel();
    ~GameModel();
    GameStatus getGameStatus() const;
    void setGameStatus(GameStatus newGameStatus);
    void addPlayer(std::shared_ptr<PlayerModel> playerToAdd);
    std::shared_ptr<PlayerModel> getPlayerModel(unsigned int playerNum) const;
    unsigned int getCurPlayerNum() const;
    void setCurPlayerNum(unsigned int newPlayerNum);

    unsigned int getNumPlayers() const;

private:
    GameStatus gameStatus_;
    unsigned int curPlayerNum_;
    std::vector<std::shared_ptr<PlayerModel> > players_;

    static const unsigned int NUM_PLAYERS = 4;
};

#endif
