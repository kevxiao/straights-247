#ifndef PLAYERENDROUNDSTATE_H
#define PLAYERENDROUNDSTATE_H

#include "Card.h"

struct PlayerEndRoundState
{
    int playerNum;
    vector<Card *> discardedCards;
    int playerOldScore;
    int playerNewScore;
};

#endif
