#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Models/GameModel.h"
#include <string>

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
