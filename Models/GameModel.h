#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <queue>

#include "GameEvent.h"
#include "../Lib/Subject.h"

enum GameStatus {INIT_GAME, PLAYER_TURN, END_ROUND, END_GAME, STATUS_COUNT};

class GameModel: public Subject
{
public:
    GameModel();
    ~GameModel();
    GameStatus gameStatus() const;
    void setGameStatus(GameStatus newGameStatus);
    std::queue<GameEvent *> getGameEvents();

private:
    GameStatus gameStatus_;
    std::queue<GameEvent *> gameEvents_;
};

#endif
