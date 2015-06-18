#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "Card.h"

class PlayerModel
{
public:
    unsigned int playerNum; 
    unsigned int score;
    bool isComputer;
    vector<Card *> hand_; //Change this to shared_ptr
    vector<Card *> discard_; //Change this to shared_ptr
};

#endif
