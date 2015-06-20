#include <cassert>
#include <algorithm>
#include "HumanPlayerController.h"

HumanPlayerController::HumanPlayerController(TableController *table):PlayerController(table)
{
}

HumanPlayerController::~HumanPlayerController()
{
}

void HumanPlayerController::processCommand(Command commandToProcess, unsigned int playerNum)
{
    assert(commandToProcess.getType() == Type::PLAY || commandToProcess.getType() == Type::DISCARD);

    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    std::vector<CardType> curLegalMoves = curPlayer->getLegalMoves();

    if(commandToProcess.getType() == Type::PLAY)
    {
        if(std::find(curLegalMoves.begin(), curLegalMoves.end(), commandToProcess.getCardType()) != curLegalMoves.end())
        {
            playCard(commandToProcess.getCardType(), playerNum);
        }
        else
        {
            throw InvalidPlayException();
        }
    }
    else
    {
        if(curLegalMoves.empty())
        {
             discardCard(commandToProcess.getCardType(), playerNum);
        }
        else
        {
            throw InvalidDiscardException();
        }
    }
}

void HumanPlayerController::removePlayerModel(unsigned int playerNum)
{
    //TODO: Do stuff here
}
