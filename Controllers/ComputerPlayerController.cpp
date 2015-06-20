#include "ComputerPlayerController.h"

// construct computer player controller using base class constructor
ComputerPlayerController::ComputerPlayerController(TableController *table):PlayerController(table)
{
}

// default destructor
ComputerPlayerController::~ComputerPlayerController() 
{
}

// perform a computer-calculated move for a specified player
void ComputerPlayerController::performMove(unsigned int playerNum) 
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    if(curPlayer->getLegalMoves().empty())
    {
        // discard first card from hand if no legal moves
        std::shared_ptr<Card> cardToDiscard = curPlayer->getHand().at(0);
        CardType cardTypeToDiscard = CardType(cardToDiscard->getSuit(), cardToDiscard->getRank());
        discardCard(cardTypeToDiscard, playerNum);
    }
    else
    {
        // play first legal move if it exists
        CardType cardTypeToPlay = curPlayer->getLegalMoves().at(0);
        playCard(cardTypeToPlay, playerNum);
    }
}
