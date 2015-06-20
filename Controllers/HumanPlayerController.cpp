#include <cassert>
#include <algorithm>
#include "HumanPlayerController.h"

// constructor for human player controller using base class constructor
HumanPlayerController::HumanPlayerController(TableController *table):PlayerController(table)
{
}

// default destructor
HumanPlayerController::~HumanPlayerController()
{
}

// process command for a specific player
void HumanPlayerController::processCommand(Command commandToProcess, unsigned int playerNum)
{
    assert(commandToProcess.getType() == Type::PLAY || commandToProcess.getType() == Type::DISCARD);

    std::shared_ptr<PlayerModel> curPlayer = getPlayerModel(playerNum);
    std::vector<CardType> curLegalMoves = curPlayer->getLegalMoves();

    if(commandToProcess.getType() == Type::PLAY)
    {
        // if playing legal card, play the card, otherwise throw exception
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
        // if no legal moves, discard the card, otherwise throw exception
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

// remove a player model from the human player controller
void HumanPlayerController::removePlayerModel(unsigned int playerNum)
{
    removePlayer(playerNum);
}
