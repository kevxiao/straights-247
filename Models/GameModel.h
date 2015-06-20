#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <queue>

#include "GameEvent.h"
#include "PlayerModel.h"
#include "../Lib/Subject.h"

enum GameStatus {INIT_GAME, START_ROUND, START_TURN, IN_TURN, DECK, RAGEQUIT, END_TURN, END_ROUND, END_GAME, STATUS_COUNT};

class GameModel: public Subject
{
public:
    GameModel();
    ~GameModel();
    GameStatus gameStatus() const;
    void setGameStatus(GameStatus newGameStatus);
    std::queue<GameEvent *> getGameEvents();
    void addPlayer(PlayerModel * playerToAdd);
    PlayerModel * getPlayerModel(unsigned int playerNum);
    unsigned int getCurPlayerNum();
    void incrementCurPlayerNum();

private:
    GameStatus gameStatus_;
    unsigned int curPlayerNum_;
    std::vector<PlayerModel *> players_;
};

#endif
