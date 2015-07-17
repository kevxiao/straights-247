#ifndef ALLPLAYERSWIDGET_H
#define ALLPLAYERSWIDGET_H

#include <gtkmm.h>
#include <memory>
#include <vector>
#include "../Controllers/GameController.h"
#include "../Models/GameModel.h"
#include "../Lib/Constants.h"
#include "PlayerWidget.h"
#include "HandFrame.h"


class AllPlayersWidget : public Gtk::VBox
{
public:
    AllPlayersWidget(GameController *, GameModel *);                            // constructor
    virtual ~AllPlayersWidget();                                                // destructor
private:
    GameController *gameController_;                                            // pointer to the gameController
    GameModel *gameModel_;                                                      // pointer to the gameModel
    Gtk::HBox players_;                                                         // hBox to contain PlayerWidgets 
    std::vector<std::shared_ptr<PlayerWidget> > eachPlayer_;                    // vector that holds pointer to each PlayerWidget
    HandFrame handFrame_;                                                       // frame that displays cards in hand 
};

#endif
