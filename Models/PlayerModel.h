#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "Card.h"
#include <vector>

class PlayerModel
{
public:
    unsigned int playerNum; 
    unsigned int score;
    bool isComputer;
    std::vector<Card *> hand_; //Change this to shared_ptr
    std::vector<Card *> discard_; //Change this to shared_ptr
};

#endif
