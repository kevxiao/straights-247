#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "CardType.h"

enum MoveType { PLAY_CARD, DISCARD_CARD};

struct PlayerMove
{
    MoveType moveType;
    CardType cardValue;
    PlayerMove():moveType(PLAY_CARD), cardValue(Suit::SPADE, Rank::ACE) {}
    PlayerMove(MoveType newMoveType, CardType newCardValue): moveType(newMoveType), cardValue(newCardValue) {}
};

#endif
