#ifndef PLAYERMOVEEVENT_H
#define PLAYERMOVEEVENT_H

#include "GameEvent.h"
#include "CardType.h"

enum MoveType { PLAY, DISCARD};

struct PlayerMoveEvent : public GameEvent
{
    MoveType moveType;
    CardType cardValue;
};

#endif
