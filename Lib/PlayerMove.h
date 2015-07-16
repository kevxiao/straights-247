#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "CardType.h"

enum MoveType {PLAY_CARD, DISCARD_CARD};                                        // different type of moves

// struct for a player's move value
struct PlayerMove
{
    MoveType moveType;                                                          // type of move
    CardType cardValue;                                                         // value of card associated with move
    PlayerMove():moveType(PLAY_CARD), cardValue(Suit::SPADE, Rank::ACE) {}      // constructor - default
    PlayerMove(MoveType newMoveType, CardType newCardValue): moveType(newMoveType), cardValue(newCardValue) {}  // constructor - specified values
};

#endif
