#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <vector>
#include <memory>

#include "Card.h"
#include "PlayerMove.h"

class PlayerModel
{
public:
    PlayerModel(unsigned int playerNum, bool isComputer);
    ~PlayerModel();

    unsigned int getPlayerNum() const;
    unsigned int getScore() const;
    void incrementScore(unsigned int incrementAmount);
    bool isComputer() const;
    void makeComputer();
        
    std::vector<std::shared_ptr<Card> > getHand() const;
    std::vector<std::shared_ptr<Card> > getDiscards() const;
    std::vector<CardType> getLegalMoves() const;    

    void clearHand();
    void clearDiscards();
    unsigned int getValOfDiscards() const;
    void setHand(std::vector<std::shared_ptr<Card > > hand_);
    void setLegalMoves(std::vector<CardType> newLegalMoves);

    void discardCard(CardType valToDiscard);
    void playCard(CardType valToPlay);
    std::shared_ptr<Card> getCardFromHand(CardType valToGet) const;
    PlayerMove getLastMove() const;

private:
    int getIndexOfCardFromHand(CardType valToGet) const;
    void removeCardFromHand(CardType valToRemove);

    unsigned int playerNum_; 
    unsigned int score_;
    bool isComputer_;
    std::vector<std::shared_ptr<Card> > hand_;
    std::vector<std::shared_ptr<Card> > discards_;
    std::vector<CardType> legalMoves_;
    PlayerMove lastMove_;
};

#endif
