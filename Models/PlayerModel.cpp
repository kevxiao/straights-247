#include "PlayerModel.h"

// create player model with the identifier and whether it is a computer
PlayerModel::PlayerModel(unsigned int playerNum, bool isComputer):playerNum_(playerNum), isComputer_(isComputer)
{
}

// default destructor
PlayerModel::~PlayerModel()
{
}

// get the player identifier number
unsigned int PlayerModel::getPlayerNum() const
{
    return playerNum_;
}

// get the player's current score
unsigned int PlayerModel::getScore() const
{
    return score_;
}

// increase the player's score by a specified amount
void PlayerModel::incrementScore(unsigned int incrementAmount)
{
    score_ += incrementAmount;
}

// check if player is computer or not
bool PlayerModel::isComputer() const
{
    return isComputer_;
}

// make a player a computer player
void PlayerModel::makeComputer()
{
    isComputer_ = true;
}

// get the list of cards in the player's hand
std::vector<std::shared_ptr<Card> > PlayerModel::getHand() const
{
    return hand_;
}

// get the list of cards discarded by the player
std::vector<std::shared_ptr<Card> > PlayerModel::getDiscards() const
{
    return discards_;
}

// get the list of legal moves for this table
std::vector<CardType> PlayerModel::getLegalMoves() const
{
    return legalMoves_;
}

// clear the cards in the hand
void PlayerModel::clearHand()
{
    hand_.clear();
}

// clear the discards list
void PlayerModel::clearDiscards()
{
    discards_.clear();
}

// calculate the value of the discarded cards
unsigned int PlayerModel::getValOfDiscards() const
{
    unsigned int discardsVal = 0;
    std::vector<std::shared_ptr<Card> >::const_iterator discardsIt = discards_.begin();
    // add up the value of each card in the discards list
    while(discardsIt != discards_.end())
    {
        discardsVal += (*(discardsIt))->getRank() + 1;
        discardsIt++;
    }
    return discardsVal;
}

// set a new hand
void PlayerModel::setHand(std::vector<std::shared_ptr<Card > > newHand)
{
    //We'll clear the hand just in case it has data in it
    clearHand();

    hand_ = newHand;
}

// set a list of legal moves for this table
void PlayerModel::setLegalMoves(std::vector<CardType> newLegalMoves)
{
    legalMoves_.clear();
    legalMoves_ = newLegalMoves;
}

// discard a card from the hand into the discarded list
void PlayerModel::discardCard(CardType valToDiscard)
{
    // remove card from hand and add to discards,then set as last move
    std::shared_ptr<Card> cardToDiscard = getCardFromHand(valToDiscard);
    removeCardFromHand(valToDiscard);
    discards_.push_back(cardToDiscard);
    lastMove_ = PlayerMove(MoveType::DISCARD_CARD, valToDiscard);
}

// play a card from hand
void PlayerModel::playCard(CardType valToPlay)
{
    // remove card from hand, then set as last move
    removeCardFromHand(valToPlay);
    lastMove_ = PlayerMove(MoveType::PLAY_CARD, valToPlay);
}

// get the index of a card in the hand
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

// get a card of specific value from the hand
std::shared_ptr<Card> PlayerModel::getCardFromHand(CardType valToGet) const
{
    int indexOfCard = getIndexOfCardFromHand(valToGet);
    // return the pointer if found, otherwise return null pointer
    if(indexOfCard == -1)
    {
        return std::shared_ptr<Card>(nullptr);
    }
    else
    {
        return hand_.at(indexOfCard);
    }
}

// remove a card from the hand
void PlayerModel::removeCardFromHand(CardType valToRemove)
{
    int indexOfCard = getIndexOfCardFromHand(valToRemove);
    if(indexOfCard != -1)
    {
        hand_.erase(hand_.begin() + indexOfCard);
    }    
}

// get the last move a player made
PlayerMove PlayerModel::getLastMove() const
{
    return lastMove_;
}

