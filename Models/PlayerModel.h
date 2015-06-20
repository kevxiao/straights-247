#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <vector>
#include <memory>

#include "Card.h"
#include "PlayerMove.h"

// model for a player entity in the game
class PlayerModel
{
public:
    PlayerModel(unsigned int playerNum, bool isComputer);               // constructor
    ~PlayerModel();                                                     // destructor

    unsigned int getPlayerNum() const;                                  // accessor - get the player's number id
    unsigned int getScore() const;                                      // accessor - get player's current score
    void incrementScore(unsigned int incrementAmount);                  // mutator - increase score by amount
    bool isComputer() const;                                            // accessor - check if player is computer
    void makeComputer();                                                // mutator - change human player into computer
        
    std::vector<std::shared_ptr<Card> > getHand() const;                // accessor - get cards in player's hand
    std::vector<std::shared_ptr<Card> > getDiscards() const;            // accessor - get all cards discarded by player
    std::vector<CardType> getLegalMoves() const;                        // accessor - get all legal moves for current table

    void clearHand();                                                   // mutator - reset hand
    void clearDiscards();                                               // mutator - reset discards list
    unsigned int getValOfDiscards() const;                              // accessor - get the value of discarded cards
    void setHand(std::vector<std::shared_ptr<Card > > hand_);           // mutator - provide player's hand
    void setLegalMoves(std::vector<CardType> newLegalMoves);            // mutator - set the moves that are legal for current table

    void discardCard(CardType valToDiscard);                            // mutator - discard card from hand
    void playCard(CardType valToPlay);                                  // mutator - play card from hand to table
    std::shared_ptr<Card> getCardFromHand(CardType valToGet) const;     // accessor - get specific card from hand
    PlayerMove getLastMove() const;                                     // accessor - get last move made by player

private:
    int getIndexOfCardFromHand(CardType valToGet) const;                // accessor - get index of specific card in hand
    void removeCardFromHand(CardType valToRemove);                      // mutator - remove a card from player's hand

    unsigned int playerNum_;                                            // player identifier number
    unsigned int score_;                                                // current score of player
    bool isComputer_;                                                   // player is computer or not
    std::vector<std::shared_ptr<Card> > hand_;                          // list of cards in hand
    std::vector<std::shared_ptr<Card> > discards_;                      // list of cards discarded
    std::vector<CardType> legalMoves_;                                  // list of legal moves for current table
    PlayerMove lastMove_;                                               // previous move made by player
};

#endif
