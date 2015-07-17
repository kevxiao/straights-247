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
    PlayerWidget(GameController *, GameModel *, unsigned int);                          // constructor
    virtual ~PlayerWidget();                                                            // destructor
    void disable();
    void setActive();
    void setPoints(unsigned int);
    void setDiscards(unsigned int);
protected:
    Gtk::VBox playerBox;
    Gtk::Label name;
    Gtk::Label playerType;
    Gtk::Label points;
    Gtk::Button discards;
    Gtk::Button ragequit;

    // signals
    virtual void discardsClicked();
    virtual void ragequitClicked();
private:
    GameController * gameController_;
    GameModel * gameModel_;
    unsigned int playerNum_;
};

#endif
