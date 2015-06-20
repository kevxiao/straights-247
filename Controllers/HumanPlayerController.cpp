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
            throw "This is not a legal play.";
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
            throw "You have a legal play. You may not discard.";
        }
    }
}

void HumanPlayerController::removePlayerModel(unsigned int playerNum)
{
    //TODO: Do stuff here
}
