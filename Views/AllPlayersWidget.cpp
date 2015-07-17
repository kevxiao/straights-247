#include "AllPlayersWidget.h"
#include "../Controllers/GameController.h"

AllPlayersWidget::AllPlayersWidget(GameController *gameController, GameModel *gameModel) : gameController_(gameController),
        gameModel_(gameModel), players_(true, UI_SPACING), hand_(true, UI_SPACING)
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
    show_all();
}

AllPlayersWidget::~AllPlayersWidget()
{

}