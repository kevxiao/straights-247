#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <map>

#include "TableController.h"
#include "../Models/Card.h"
#include "../Models/PlayerModel.h"

class PlayerController {
public:
    PlayerController(TableController *table);
    virtual ~PlayerController();

    void addPlayerModel(std::shared_ptr<PlayerModel> newPlayer);

    void resetHand(std::vector<std::shared_ptr<Card> > newHand, unsigned int playerNum);
    bool hasCards(unsigned int playerNum) const;

    bool doesPlayerExistHere(unsigned int playerNum) const;
    unsigned int getScore(unsigned int playerNum) const;
    void setLegalMoves(unsigned int playerNum);

protected:
    void playCard(CardType typeToPlay, unsigned int playerNum);
    void discardCard(CardType typeToPlay, unsigned int playerNum);
    std::shared_ptr<PlayerModel> getPlayerModel(unsigned int playerNum) const;

private:
    std::map<unsigned int, std::shared_ptr<PlayerModel> > players_;
    TableController * table_;
};

#endif
