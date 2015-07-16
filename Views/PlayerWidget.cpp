#include "PlayerWidget.h"

PlayerWidget::PlayerWidget(GameController * gameController, int playerNum) : gameController_(gameController), playerNum_(playerNum + 1),
        playerBox_(false, UI_SPACING), name_("Player " + std::to_string(playerNum_)), playerType_(""), points_("Points: 0"),
        discards_("Discards: 0"), ragequit_("Ragequit")
{
    add(playerBox_);
    playerBox_.set_border_width(UI_SPACING);
    name_.set_markup("<big><u>" + name_.get_label() + "</u></big>");
    playerBox_.add(name_);
    playerBox_.add(playerType_);
    playerBox_.add(points_);
    playerBox_.add(discards_);
    ragequit_.set_tooltip_markup("<span foreground=\"red\">" + ragequit_.get_label() + "</span>");
    playerBox_.add(ragequit_);
}

PlayerWidget::~PlayerWidget()
{

}

void PlayerWidget::setPoints(unsigned int)
{

}

void PlayerWidget::setDiscards(unsigned int)
{

}