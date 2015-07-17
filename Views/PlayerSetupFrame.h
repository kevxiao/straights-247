#ifndef __PLAYER_SETUP_FRAME_H
#define __PLAYER_SETUP_FRAME_H

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/radiobutton.h>

class PlayerSetupFrame : public Gtk::Frame {
public:
    PlayerSetupFrame( const Glib::ustring& label);  // constructor
	virtual ~PlayerSetupFrame();                    // deconstructor

    bool isHuman() const;                           // accessor - returns if the human radio button was selected or not
private:
    Gtk::VBox vBoxContainer;                        // container for all elements in this frame
    Gtk::RadioButton::Group buttonGroup;            // radio button group that contains the human and computer radio buttons 
    Gtk::RadioButton *humanButton;                  // radio button for human option
    Gtk::RadioButton *computerButton;               // radio button for computer option
};

#endif
