#ifndef RAGEQUITDIALOG_H
#define RAGEQUITDIALOG_H

#include <gtkmm.h>

class RagequitDialog : public Gtk::Dialog
{
public:
    RagequitDialog();               // constructor
    virtual ~RagequitDialog();      // destructor
protected:
    Gtk::Image ragequit;            // image that will be displayed in the ragequit dialog
};

#endif
