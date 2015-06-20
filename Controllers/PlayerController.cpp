#include "PlayerController.h"

PlayerController::PlayerController(TableController *table):table_(table)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::addPlayerModel(std::shared_ptr<PlayerModel> newPlayer)
{
    players_.insert(std::pair<unsigned int, std::shared_ptr<PlayerModel> >(newPlayer->getPlayerNum(), newPlayer));
}

//Deleting all card references in player model and updates score
void PlayerController::resetHand(std::vector<std::shared_ptr<Card> > newHand, unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> playerToReset = getPlayerModel(playerNum);

    playerToReset->clearHand();
    playerToReset->clearDiscards();
    playerToReset->setHand(newHand);
}

bool PlayerController::hasCards(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    return !curPlayer->getHand().empty();
}

bool PlayerController::doesPlayerExistHere(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    return curPlayer != nullptr;
}

unsigned int PlayerController::getScore(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    return curPlayer->getScore();
}

void PlayerController::incrementScore(unsigned int amountToIncrement, unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    curPlayer->incrementScore(amountToIncrement);
}

void PlayerController::setLegalMoves(unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
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
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    std::shared_ptr<Card> cardToPlay = curPlayer->getCardFromHand(valToPlay);
    curPlayer->playCard(valToPlay);
    table_->addCardToTable(cardToPlay);
}

void PlayerController::discardCard(CardType valToDiscard, unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    curPlayer->discardCard(valToDiscard);
}

std::shared_ptr<PlayerModel> PlayerController::getPlayerModel(unsigned int playerNum) const
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
