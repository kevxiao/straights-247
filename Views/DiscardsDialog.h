#ifndef DISCARDSDIALOG_H
#define DISCARDSDIALOG_H

#include <gtkmm.h>
#include "../Models/GameModel.h"


class DiscardsDialog : public Gtk::Dialog
{
public:
    DiscardsDialog(GameModel *, unsigned int);
    virtual ~DiscardsDialog();
protected:
    Gtk::HBox firstRow;
    Gtk::HBox secondRow;
};

#endif
