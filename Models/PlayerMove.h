#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "../Models/CardType.h"

enum MoveType { PLAY, DISCARD};

struct PlayerMove
{
    MoveType moveType;
    CardType cardVale;
};

#endif
