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
	SeedDialogBox( Gtk::Window & parentWindow, string title);   // constructor 
	virtual ~SeedDialogBox();                                   // deconstructor

    void popupAndUpdate();                                      // mutator - displays popup and updates seed value
    bool isSeedValid() const;                                   // accessor - returns whether the user entered a seed value and pressed the ok button
    int getSeedValue() const;                                   // accessor - returns the seed value that the user entered
	
private:
    bool isValidSeed;                                           // holds if the user entered a seed value and pressed the ok button
    int seedValue;                                              // holds the seed value that the user entered

    Gtk::HBox container;                                        // main container for elements in this dialog
    Gtk::Label seedPrompt;                                      // label to prompt user for seed
    Gtk::Entry seedEntry;                                       // entry to allow user to enter the seed
};
#endif
