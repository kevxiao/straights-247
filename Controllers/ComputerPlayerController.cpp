#include "ComputerPlayerController.h"

ComputerPlayerController::ComputerPlayerController(TableController *table):PlayerController(table)
{
}

ComputerPlayerController::~ComputerPlayerController() 
{
}

void ComputerPlayerController::performMove(unsigned int playerNum) 
{
    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    if(curPlayer->getLegalMoves().empty())
    {
        std::shared_ptr<Card> cardToDiscard = curPlayer->getDiscards().at(0);
        CardType cardTypeToDiscard = CardType(cardToDiscard->getSuit(), cardToDiscard->getRank());
        discardCard(cardTypeToDiscard, playerNum);
    }
    else
    {
        CardType cardTypeToPlay = curPlayer->getLegalMoves().at(0);
        playCard(cardTypeToPlay, playerNum);
    }
}
