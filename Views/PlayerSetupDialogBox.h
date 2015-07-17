#ifndef __PLAYER_SETUP_DIALOG_BOX_H
#define __PLAYER_SETUP_DIALOG_BOX_H

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/stock.h>
#include <string>
#include <vector>
#include "PlayerSetupFrame.h"

using std::string;
using std::vector;

class PlayerSetupDialogBox : Gtk::Dialog {
public:
	PlayerSetupDialogBox( Gtk::Window & parentWindow);  // constructor
	virtual ~PlayerSetupDialogBox();                    // destructor

    vector<bool> popupAndGetPlayerStatus();             // mutator - displays the popup and returns whether each player is a human or not
	
private:
    Gtk::HBox containerBox;                             // container that holds all of the elements in this dialog
    PlayerSetupFrame *playerSetupFrames[4];             // array of pointers to 4 PlayerSetupFrames to be displayed
};
#endif
