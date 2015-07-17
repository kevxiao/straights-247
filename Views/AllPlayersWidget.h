#ifndef ALLPLAYERSWIDGET_H
#define ALLPLAYERSWIDGET_H

#include <gtkmm.h>
#include <memory>
#include <vector>
#include "../Controllers/GameController.h"
#include "../Models/GameModel.h"
#include "../Lib/Constants.h"
#include "PlayerWidget.h"


class AllPlayersWidget : public Gtk::VBox
{
public:
    AllPlayersWidget(GameController *, GameModel *);                                         // constructor
    virtual ~AllPlayersWidget();                                                // destructor
private:
    GameController *gameController_;
    GameModel *gameModel_;
    Gtk::HBox players_;
    Gtk::HBox hand_;
    std::vector<std::shared_ptr<PlayerWidget> > eachPlayer_;
};

#endif
