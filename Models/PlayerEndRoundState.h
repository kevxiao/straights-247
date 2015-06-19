#ifndef PLAYERENDROUNDSTATE_H
#define PLAYERENDROUNDSTATE_H

#include <vector>
#include "Card.h"

struct PlayerEndRoundState
{
    int playerNum;
    std::vector<Card *> discardedCards;
    int playerOldScore;
    int playerNewScore;
};

#endif
