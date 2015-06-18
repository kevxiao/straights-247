#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "../Lib/Subject.h"

enum GameStatus {INIT_GAME, PLAYER_TURN, END_ROUND, END_GAME};

class GameModel: public Subject
{
    GameModel();
    ~GameModel();
    GameStatus gameStatus();
    void setGameStatus(GameStatus newGameStatus);
private:
    GameStatus gameStatus_;
};

#endif
