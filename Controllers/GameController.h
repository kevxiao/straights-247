#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameModel.h"

class GameController
{
public:
    GameController();
    ~GameController();
    void processInput(std::string input);
private:
    GameModel * gameModel;
};

#endif
