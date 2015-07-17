#ifndef __PLAYER_SETUP_FRAME_H
#define __PLAYER_SETUP_FRAME_H

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/radiobutton.h>

class PlayerSetupFrame : public Gtk::Frame {
public:
    PlayerSetupFrame( const Glib::ustring& label);
	virtual ~PlayerSetupFrame();

    bool isHuman();
private:
    Gtk::VBox                    vBoxContainer;
    Gtk::RadioButton::Group      buttonGroup;
    Gtk::RadioButton *           humanButton;
    Gtk::RadioButton *           computerButton;
};

#endif
