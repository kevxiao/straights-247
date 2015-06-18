#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "PlayerModel.h"

class PlayerController
{
public:
    PlayerController();
    virtual ~PlayerController();

    void resetHand(vector<Card*> newHand, int playerNum);//Responsible for deleting all card references in player model and making score
    bool hasCards(int playerNum);

    bool doesPlayerExistHere(int playerNum);
    int getScore(int playerNum);
    int getValOfDiscards(int playerNum);

protected:
    void playCard(Card *, int playerNum);
    void discardCard(Card *, int playerNum);

private:
    vector<PlayerModel *> players_;
};

#endif
