
#include "PlayerModel.h"

PlayerModel::PlayerModel()
{
}

PlayerModel::~PlayerModel()
{
}

unsigned int PlayerModel::getPlayerNum() const
{
    return playerNum_;
}

unsigned int PlayerModel::getScore() const
{
    return score_;
}

void PlayerModel::incrementScore(unsigned int incrementAmount)
{
    score_ += incrementAmount;
}

void PlayerModel::makeComputer()
{
    isComputer_ = true;
}
    
std::vector<std::shared_ptr<Card> > PlayerModel::getHand() const
{
    return hand_;
}

std::vector<std::shared_ptr<Card> > PlayerModel::getDiscards() const
{
    return discards_;
}

std::vector<CardType> PlayerModel::getLegalMoves() const
{
    return legalMoves_;
}

void PlayerModel::clearHand()
{
    hand_.clear();
}

void PlayerModel::clearDiscards()
{
    discards_.clear();
}

void PlayerModel::setHand(std::vector<std::shared_ptr<Card > > newHand)
{
    //We'll clear the hand just in case it has data in it
    clearHand();

    hand_ = newHand;
}

void PlayerModel::setLegalMoves(std::vector<CardType> newLegalMoves)
{
    legalMoves_.clear();
    legalMoves_ = newLegalMoves;
}

void PlayerModel::discardCard(CardType valToDiscard)
{
    std::shared_ptr<Card> cardToDiscard = getCardFromHand(valToDiscard);
    removeCardFromHand(valToDiscard);
    discards_.push_back(cardToDiscard);
}

void PlayerModel::playCard(CardType valToPlay)
{
    removeCardFromHand(valToPlay);
}

int PlayerModel::getIndexOfCardFromHand(CardType valToGet) const
{
    int indexOfCard = -1;
    for(unsigned int counter = 0; counter < hand_.size(); counter++)
    {
        if(hand_.at(counter)->hasValue(valToGet))
        {
            indexOfCard = counter;
        }
    }
    return indexOfCard;
}

std::shared_ptr<Card> PlayerModel::getCardFromHand(CardType valToGet) const
{
    int indexOfCard = getIndexOfCardFromHand(valToGet);
    if(indexOfCard == -1)
    {
        return std::shared_ptr<Card>();
    }
    else
    {
        return hand_.at(indexOfCard);
    }
}

void PlayerModel::removeCardFromHand(CardType valToRemove)
{
    int indexOfCard = getIndexOfCardFromHand(valToRemove);
    if(indexOfCard != -1)
    {
        hand_.erase(hand_.begin() + indexOfCard);
    }    
}

