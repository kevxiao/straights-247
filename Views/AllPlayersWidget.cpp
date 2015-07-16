#include "AllPlayersWidget.h"

AllPlayersWidget::AllPlayersWidget(GameController *gameController) : gameController_(gameController),
        players_(true, UI_SPACING), hand_(true, UI_SPACING)
{
    add(players_);
    std::shared_ptr<PlayerWidget> onePlayer;
    for (unsigned int i = 0; i < NUM_PLAYERS; ++i)
    {
        onePlayer = std::make_shared<PlayerWidget>(gameController, i);
        eachPlayer_.push_back(onePlayer);
        players_.add(*onePlayer);
        players_.set_sensitive(false);
    }
    show_all();
}

AllPlayersWidget::~AllPlayersWidget()
{

}