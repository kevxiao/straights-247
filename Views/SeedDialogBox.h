#ifndef __MY_DIALOG_BOX_H
#define __MY_DIALOG_BOX_H

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/stock.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

class SeedDialogBox : Gtk::Dialog {
public:
	SeedDialogBox( Gtk::Window & parentWindow, string title);
	virtual ~SeedDialogBox();

    int popupAndGetSeed();
	
private:
    Gtk::HBox                    container;
    Gtk::Label                   seedPrompt;
    Gtk::Entry                   seedEntry;
};
#endif
