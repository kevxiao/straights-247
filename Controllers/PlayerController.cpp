#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

//Deleting all card references in player model and updates score
void PlayerController::resetHand(std::vector<std::shared_ptr<Card> > newHand, unsigned int playerNum)
{
    PlayerModel * playerToReset = getPlayerModel(playerNum);

    int discardVal = getValOfDiscards(playerNum);
    playerToReset->incrementScore(discardVal);

    playerToReset->clearHand();
    playerToReset->clearDiscards();
    playerToReset->setHand(newHand);
}

bool PlayerController::hasCards(unsigned int playerNum) const
{
    PlayerModel * curPlayer = getPlayerModel(playerNum);
    return curPlayer->getHand().empty();
}

bool PlayerController::doesPlayerExistHere(unsigned int playerNum) const
{
    PlayerModel * curPlayer = getPlayerModel(playerNum);
    return curPlayer != nullptr;
}

unsigned int PlayerController::getScore(unsigned int playerNum) const
{
    PlayerModel * curPlayer = getPlayerModel(playerNum);
    return curPlayer->getScore();
}

unsigned int PlayerController::getValOfDiscards(unsigned int playerNum) const
{
    PlayerModel * curPlayer = getPlayerModel(playerNum);
    std::vector<std::shared_ptr<Card> > playerHand = curPlayer->getHand();
    
    unsigned int discardsVal = 0;
    std::vector<std::shared_ptr<Card> >::iterator handIt = playerHand.begin();
    while(handIt != playerHand.end())
    {
        discardsVal += (*(handIt))->getRank();
        handIt++;
    }
    return discardsVal;
}

void PlayerController::setLegalMoves(unsigned int playerNum) const
{
    PlayerModel * curPlayer = getPlayerModel(playerNum);
    std::vector<std::shared_ptr<Card> > playerHand = curPlayer->getHand();

    std::vector<CardType> legalMoves;
    bool has7S = false;

    for(unsigned int counter = 0; counter < playerHand.size() && !has7S; counter++)
    {
        std::shared_ptr<Card> curCard = playerHand.at(counter);
        if(table_->isPlayValid(curCard))
        {
            legalMoves.push_back(CardType(curCard->getSuit(), curCard->getRank()));
        }
        if(curCard->getSuit() == Suit::SPADE && curCard->getRank() == Rank::SEVEN)
        {
            has7S = true;
        }
    }
    if(has7S)
    {
        legalMoves.clear();
        legalMoves.push_back(CardType(Suit::SPADE, Rank::SEVEN));
    }
    curPlayer->setLegalMoves(legalMoves);
}

void PlayerController::playCard(CardType valToPlay, unsigned int playerNum)
{
    PlayerModel * curPlayer = getPlayerModel(playerNum);
    std::shared_ptr<Card> cardToPlay = curPlayer->getCardFromHand(valToPlay);
    curPlayer->playCard(valToPlay);
    table_->addCardToTable(cardToPlay);
}

void PlayerController::discardCard(CardType valToDiscard, unsigned int playerNum)
{
    PlayerModel * curPlayer = getPlayerModel(playerNum);
    curPlayer->discardCard(valToDiscard);
}

PlayerModel * PlayerController::getPlayerModel(unsigned int playerNum) const
{
    if(players_.find(playerNum) != players_.end())
    {
        return players_.at(playerNum);
    }
    else
    {
        return nullptr;
    }
}
