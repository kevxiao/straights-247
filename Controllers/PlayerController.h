#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <map>

#include "TableController.h"
#include "../Models/Card.h"
#include "../Models/PlayerModel.h"

class PlayerController {
public:
    PlayerController();
    virtual ~PlayerController();

    void resetHand(std::vector<std::shared_ptr<Card> > newHand, unsigned int playerNum);
    bool hasCards(unsigned int playerNum) const;

    bool doesPlayerExistHere(unsigned int playerNum) const;
    unsigned int getScore(unsigned int playerNum) const;
    unsigned int getValOfDiscards(unsigned int playerNum) const;

protected:
    void setLegalMoves(unsigned int playerNum) const;
    void playCard(CardType typeToPlay, unsigned int playerNum);
    void discardCard(CardType typeToPlay, unsigned int playerNum);
    PlayerModel * getPlayerModel(unsigned int playerNum) const;

private:
    std::map<unsigned int, PlayerModel *> players_;
    TableController * table_;
};

#endif
