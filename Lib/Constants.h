#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };
const unsigned short CARD_COUNT = 52;                                   // constant value for the number of cards in deck
const unsigned short UI_SPACING = 10;                                   // constant value for spacing in the UI
const unsigned short NUM_PLAYERS = 4;                                   // constant number of players for the game

#endif
