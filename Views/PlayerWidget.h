#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <string>
#include <gtkmm.h>
#include "../Controllers/GameController.h"
#include "../Lib/Constants.h"

class PlayerWidget : public Gtk::Frame
{
public:
    PlayerWidget(GameController *, int);                                                  // constructor
    virtual ~PlayerWidget();                                                // destructor
    void setPoints(unsigned int);
    void setDiscards(unsigned int);
private:
    GameController * gameController_;
    int playerNum_;
    Gtk::VBox playerBox_;
    Gtk::Label name_;
    Gtk::Label playerType_;
    Gtk::Label points_;
    Gtk::Button discards_;
    Gtk::Button ragequit_;
};

#endif
