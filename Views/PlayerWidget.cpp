#include "PlayerWidget.h"
#include "../Lib/CardType.h"
#include "DiscardsDialog.h"

PlayerWidget::PlayerWidget(GameController * gameController, GameModel * gameModel, unsigned int playerNum) : gameController_(gameController),
        gameModel_(gameModel), playerNum_(playerNum + 1), playerBox_(false, UI_SPACING), name_(), playerType_(), points_("Points: 0"),
        discards_("Discards: 0"), ragequit_("Ragequit")
{
    add(playerBox_);
    playerBox_.set_border_width(UI_SPACING);
    name_.set_markup("<big><u>Player " + std::to_string(playerNum_) + "</u></big>");
    name_.set_tooltip_text("In case you forgot, you are Player " + std::to_string(playerNum_));
    playerBox_.add(name_);
    playerBox_.add(playerType_);
    points_.set_tooltip_text("Player " + std::to_string(playerNum_) + " has 0 points.");
    playerBox_.add(points_);
    discards_.set_tooltip_text("Click to check which cards Player " + std::to_string(playerNum_) + " has discarded.");
    playerBox_.add(discards_);
    ragequit_.set_tooltip_markup("<span foreground=\"red\">Player " + std::to_string(playerNum_) + ", please don't be mad. :(</span>");
    playerBox_.add(ragequit_);
    discards_.signal_clicked().connect(sigc::mem_fun(*this, &PlayerWidget::discardsClicked));
    ragequit_.signal_clicked().connect(sigc::mem_fun(*this, &PlayerWidget::ragequitClicked));
    discards_.set_sensitive(false);
    ragequit_.set_sensitive(false);
}

PlayerWidget::~PlayerWidget()
{

}

void PlayerWidget::discardsClicked()
{
    DiscardsDialog dialog(gameModel_, playerNum_ - 1);
    dialog.run();
}

void PlayerWidget::ragequitClicked()
{
    discards_.set_sensitive(false);
    ragequit_.set_sensitive(false);
    gameController_->processInput("ragequit");
}

void PlayerWidget::disable()
{
    name_.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("gray"));
    name_.set_markup("<big><u>Player " + std::to_string(playerNum_) + "</u></big>");
    playerType_.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("gray"));
    points_.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("gray"));
    discards_.set_sensitive(false);
    ragequit_.set_sensitive(false);
}

void PlayerWidget::setActive(bool buttons)
{
    name_.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("black"));
    name_.set_markup("<big><u><b>Player " + std::to_string(playerNum_) + "</b></u></big>");
    playerType_.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("black"));
    points_.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("black"));
    discards_.set_sensitive(buttons);
    ragequit_.set_sensitive(buttons);
}

void PlayerWidget::setPoints(unsigned int newPoints)
{
    points_.set_label("Points: " + std::to_string(newPoints));
    points_.set_tooltip_text("Player " + std::to_string(playerNum_) + " has 0 points.");
}

void PlayerWidget::setDiscards(unsigned long newDiscards)
{
    discards_.set_label("Discards: " + std::to_string(newDiscards));
}

void PlayerWidget::setType(bool human)
{
    playerType_.set_text(human ? "Human" : "Computer");
}

void PlayerWidget::resetPlayer()
{
    setActive(false);
    playerType_.set_text("");
    setDiscards(0);
    setPoints(0);
}
