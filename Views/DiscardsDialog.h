#ifndef DISCARDSDIALOG_H
#define DISCARDSDIALOG_H

#include <gtkmm.h>
#include <vector>

#include "../Models/GameModel.h"
#include "DeckGUI.h"

class DiscardsDialog : public Gtk::Dialog
{
public:
    DiscardsDialog(GameModel *, unsigned int);
    virtual ~DiscardsDialog();

private:
    DeckGUI deck;

    Gtk::HBox firstRow;
    Gtk::HBox secondRow;
    vector<Gtk::Image *> discardImages;
};

#endif
