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
    AllPlayersWidget(GameController *, GameModel *);                    // constructor
    virtual ~AllPlayersWidget();                                        // destructor

    void disablePlayer(unsigned int);                                   // mutator - disables a player
    void enablePlayer(unsigned int, bool);                              // mutator - enables a player

    void setDiscards(unsigned int, unsigned long);                      // mutator - sets the number of discards displayed for a player
    void setPoints(unsigned int, unsigned int);                         // mutator - sets the number of points displayed for a player
    void setType(unsigned int, bool);                                   // mutator - sets the player type for a player
    void resetPlayer(unsigned int);                                     // mutator - reset all the values for a player

private:
    GameController *gameController_;                                    // pointer to the gameController
    GameModel *gameModel_;                                              // pointer to the gameModel
    Gtk::HBox players_;                                                 // hBox to contain PlayerWidgets 
    std::vector<std::shared_ptr<PlayerWidget> > eachPlayer_;            // vector that holds pointer to each PlayerWidget
    HandFrame handFrame_;                                               // frame that displays cards in hand 
};

#endif
