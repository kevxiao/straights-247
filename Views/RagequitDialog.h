#ifndef RAGEQUITDIALOG_H
#define RAGEQUITDIALOG_H

#include <gtkmm.h>

class RagequitDialog : public Gtk::Dialog
{
public:
    RagequitDialog();               // constructor
    virtual ~RagequitDialog();      // destructor
private:
    Gtk::Image ragequit_;           // image that will be displayed in the ragequit dialog
};

#endif
