#include "AllPlayersWidget.h"
#include "../Controllers/GameController.h"

AllPlayersWidget::AllPlayersWidget(GameController *gameController, GameModel *gameModel) : gameController_(gameController),
        gameModel_(gameModel), players_(true, UI_SPACING), handFrame_(gameModel_)
{
    add(players_);
    std::shared_ptr<PlayerWidget> onePlayer;
    for (unsigned int i = 0; i < NUM_PLAYERS; ++i)
    {
        onePlayer = std::make_shared<PlayerWidget>(gameController_, gameModel_, i);
        eachPlayer_.push_back(onePlayer);
        players_.add(*onePlayer);
        eachPlayer_.at(i)->disable();
    }
    eachPlayer_.at(2)->setActive();

    add(handFrame_);

    show_all();
}

AllPlayersWidget::~AllPlayersWidget()
{

}

void AllPlayersWidget::setDiscards(unsigned int playerNum, unsigned int newNumDiscards)
{
    eachPlayer_.at(playerNum)->setDiscards(newNumDiscards);
}

void AllPlayersWidget::setPoints(unsigned int playerNum, unsigned int newNumPoints)
{
    eachPlayer_.at(playerNum)->setPoints(newNumPoints);
}
