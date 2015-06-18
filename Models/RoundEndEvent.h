#ifndef ROUNDENDEVENT_H
#define ROUNDENDEVENT_H

#include "GameEvent.h"
#include "PlayerEndRoundState.h"

struct RoundEndEvent : public GameEvent
{
    vector<PlayerEndRoundState *> playerStates; //Maybe we should change this to an array of size 4?
};

#endif
