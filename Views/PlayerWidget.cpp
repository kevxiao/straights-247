#include "PlayerWidget.h"
#include "../Lib/CardType.h"
#include "DiscardsDialog.h"

PlayerWidget::PlayerWidget(GameController * gameController, GameModel * gameModel, unsigned int playerNum) : gameController_(gameController),
        gameModel_(gameModel), playerNum_(playerNum + 1), playerBox(false, UI_SPACING), name(), playerType(), points("Points: 0"),
        discards("Discards: 0"), ragequit("Ragequit")
{
    add(playerBox);
    playerBox.set_border_width(UI_SPACING);
    name.set_markup("<big><u>Player " + std::to_string(playerNum_) + "</u></big>");
    name.set_tooltip_text("In case you forgot, you are Player " + std::to_string(playerNum_));
    playerBox.add(name);
    playerBox.add(playerType);
    points.set_tooltip_text("Player " + std::to_string(playerNum_) + " has 0 points.");
    playerBox.add(points);
    discards.set_tooltip_text("Click to check which cards Player " + std::to_string(playerNum_) + " has discarded.");
    playerBox.add(discards);
    ragequit.set_tooltip_markup("<span foreground=\"red\">Player " + std::to_string(playerNum_) + ", please don't be mad. :(</span>");
    playerBox.add(ragequit);
    discards.signal_clicked().connect(sigc::mem_fun(*this, &PlayerWidget::discardsClicked));
    ragequit.signal_clicked().connect(sigc::mem_fun(*this, &PlayerWidget::ragequitClicked));
    discards.set_sensitive(false);
    ragequit.set_sensitive(false);
}

PlayerWidget::~PlayerWidget()
{

}

void PlayerWidget::discardsClicked()
{
    DiscardsDialog dialog(gameModel_, playerNum_);
    dialog.run();
}

void PlayerWidget::ragequitClicked()
{
    discards.set_sensitive(false);
    ragequit.set_sensitive(false);
    gameController_->processInput("ragequit");
}

void PlayerWidget::disable()
{
    name.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("gray"));
    name.set_markup("<big><u>Player " + std::to_string(playerNum_) + "</u></big>");
    playerType.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("gray"));
    points.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("gray"));
    discards.set_sensitive(false);
    ragequit.set_sensitive(false);
}

void PlayerWidget::setActive(bool buttons)
{
    name.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("black"));
    name.set_markup("<big><u><b>Player " + std::to_string(playerNum_) + "</b></u></big>");
    playerType.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("black"));
    points.modify_fg(Gtk::STATE_NORMAL, Gdk::Color("black"));
    discards.set_sensitive(buttons);
    ragequit.set_sensitive(buttons);
}

void PlayerWidget::setPoints(unsigned int newPoints)
{
    points.set_label("Points: " + std::to_string(newPoints));
    points.set_tooltip_text("Player " + std::to_string(playerNum_) + " has 0 points.");
}

void PlayerWidget::setDiscards(unsigned long newDiscards)
{
    discards.set_label("Discards: " + std::to_string(newDiscards));
}

