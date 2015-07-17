#ifndef DISCARDSDIALOG_H
#define DISCARDSDIALOG_H

#include <gtkmm.h>
#include <vector>

#include "../Models/GameModel.h"
#include "DeckGUI.h"

class DiscardsDialog : public Gtk::Dialog
{
public:
    DiscardsDialog(GameModel *, unsigned int);      // constructor
    virtual ~DiscardsDialog();                      // deconstructor

private:
    DeckGUI deck;                                   // deckgui that retrieves pixbufs for cards that we want to display 

    Gtk::HBox firstRow;                             // hBox that holds the first row of cards
    Gtk::HBox secondRow;                            // hBox that holds the second row of cards
    vector<Gtk::Image *> discardImages;             // vector that holds the images we want to display
};

#endif
