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
	PlayerSetupDialogBox( Gtk::Window & parentWindow);
	virtual ~PlayerSetupDialogBox();

    vector<bool> popupAndGetPlayerStatus();
	
private:
    Gtk::HBox                         containerBox;
    PlayerSetupFrame *                  playerSetupFrames[4];
};
#endif
