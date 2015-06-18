#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "CardValue.h"

enum MoveType { PLAY, DISCARD}

struct PlayerMove
{
    MoveType moveType;
    CardValue movedCard;
}

#endif
