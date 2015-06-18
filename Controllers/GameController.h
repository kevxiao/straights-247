#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>

class GameController
{
public:
    GameController();
    ~GameController();
    void processInput(std::string input);

private:
    GameModel * gameModel_;
};

#endif
