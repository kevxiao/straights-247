#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <map>

#include "TableController.h"
#include "../Models/Card.h"
#include "../Models/PlayerModel.h"

// controller for the players in the game
class PlayerController {
public:
    PlayerController(TableController *table);                                               // constructor
    virtual ~PlayerController();                                                            // destructor

    void addPlayerModel(std::shared_ptr<PlayerModel> newPlayer);                            // mutator - add player

    void resetHand(std::vector<std::shared_ptr<Card> > newHand, unsigned int playerNum);    // mutator - replace player hand with new hand
    bool hasCards(unsigned int playerNum) const;                                            // accessor - check for cards in hand

    bool doesPlayerExistHere(unsigned int playerNum) const;                                 // accessor - check player existence
    unsigned int getScore(unsigned int playerNum) const;                                    // accessor - get current score
    void incrementScore(unsigned int amountToIncrement, unsigned int playerNum);            // mutator - add to player score
    void setLegalMoves(unsigned int playerNum);                                             // mutator - create list of legal moves

protected:
    void playCard(CardType typeToPlay, unsigned int playerNum);                             // mutator - move card from hand to table
    void discardCard(CardType typeToPlay, unsigned int playerNum);                          // mutator - move card from hand to discard
    void removePlayer(unsigned int playerNum);                                              // mutator - remove player
    std::shared_ptr<PlayerModel> getPlayerModel(unsigned int playerNum) const;              // accessor - get the player model

private:
    std::map<unsigned int, std::shared_ptr<PlayerModel> > players_;                         // map of players of this player type
    TableController * table_;                                                               // reference to the table
};

#endif
