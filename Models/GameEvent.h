#ifndef GAMEEVENT_H
#define GAMEEVENT_H

//Main reason for this class is so we can have single queue of game events to output

enum EventType { END_OF_ROUND, PLAYERMOVE};

struct GameEvent
{
    EventType typeOfEvent;
};

#endif
