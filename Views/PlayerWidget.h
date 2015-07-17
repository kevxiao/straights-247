#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <string>
#include <gtkmm.h>
#include "../Controllers/GameController.h"
#include "../Models/GameModel.h"
#include "../Lib/Constants.h"

class PlayerWidget : public Gtk::Frame
{
public:
    PlayerWidget(GameController *, GameModel *, unsigned int);      // constructor
    virtual ~PlayerWidget();                                        // destructor
    void disable();                                                 // mutator - disables all of the buttons
    void setActive(bool);                                           // mutator - enables all of the buttons
    void setPoints(unsigned int);                                   // mutator - updates the points label
    void setDiscards(unsigned long);                                 // mutator - updates the discards label
private:
    // signals
    virtual void discardsClicked();                                 // mutator - launches the discards dialog for player to see discards
    virtual void ragequitClicked();                                 // mutator - launches ragequit gif and send ragequit command to gameController

    GameController * gameController_;                               // pointer to the GameController
    GameModel * gameModel_;                                         // pointer to the GameModel
    unsigned int playerNum_;                                        // value of player that this widget represents

    //components
    Gtk::VBox playerBox;                                            // container for elements in this widget
    Gtk::Label name;                                                // label that will displays the player "name"
    Gtk::Label playerType;                                          // label that displays the player type
    Gtk::Label points;                                              // label that displays the amount of points the player has currently
    Gtk::Button discards;                                           // button to allow player to view discarded cards
    Gtk::Button ragequit;                                           // button to allow the player to ragequit
};

#endif
