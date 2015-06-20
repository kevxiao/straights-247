#include "PlayerController.h"

// create player controller with reference to the table controller
PlayerController::PlayerController(TableController *table):table_(table)
{
}

// default destructor
PlayerController::~PlayerController()
{
}

// add a player to the player controller
void PlayerController::addPlayerModel(std::shared_ptr<PlayerModel> newPlayer)
{
    players_.insert(std::pair<unsigned int, std::shared_ptr<PlayerModel> >(newPlayer->getPlayerNum(), newPlayer));
}

// deleting all card references in player model and sets a new hand
void PlayerController::resetHand(std::vector<std::shared_ptr<Card> > newHand, unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> playerToReset = getPlayerModel(playerNum);
    playerToReset->clearHand();
    playerToReset->clearDiscards();
    playerToReset->setHand(newHand);
}

// check if hand is empty or not
bool PlayerController::hasCards(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    return !curPlayer->getHand().empty();
}

// check that the player identifier exists
bool PlayerController::doesPlayerExistHere(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    return curPlayer != nullptr;
}

// get the current score for a player
unsigned int PlayerController::getScore(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    return curPlayer->getScore();
}

// ingrement score by an amount
void PlayerController::incrementScore(unsigned int amountToIncrement, unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    curPlayer->incrementScore(amountToIncrement);
}

// check for all legal moves and create the list
void PlayerController::setLegalMoves(unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    std::vector<std::shared_ptr<Card> > playerHand = curPlayer->getHand();

    std::vector<CardType> legalMoves;
    bool has7S = false;

    // check every card in player hand to see if it is a valid move
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
    // if there is a 7 of spades, only that card is a valid move
    if(has7S)
    {
        legalMoves.clear();
        legalMoves.push_back(CardType(Suit::SPADE, Rank::SEVEN));
    }
    curPlayer->setLegalMoves(legalMoves);
}

// play card by removing from hand and adding to table
void PlayerController::playCard(CardType valToPlay, unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    std::shared_ptr<Card> cardToPlay = curPlayer->getCardFromHand(valToPlay);
    curPlayer->playCard(valToPlay);
    table_->addCardToTable(cardToPlay);
}

// discard card by removing from hand and adding to discard
void PlayerController::discardCard(CardType valToDiscard, unsigned int playerNum)
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    curPlayer->discardCard(valToDiscard);
}

// remove a player from the controller
void PlayerController::removePlayer(unsigned int playerNum)
{
    players_.erase(playerNum);
}

// get a player model fromt he identifier
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
