#ifndef RAGEQUITDIALOG_H
#define RAGEQUITDIALOG_H

#include <gtkmm.h>

class RagequitDialog : public Gtk::Dialog
{
public:
    RagequitDialog();
    virtual ~RagequitDialog();
protected:
    Gtk::Image ragequit;
};

#endif
