#include "RagequitDialog.h"

RagequitDialog::RagequitDialog() : ragequit_("Assets/smash.gif")
{
    Glib::RefPtr <Gdk::PixbufAnimation> anim;
    anim = Gdk::PixbufAnimation::create_from_file("Assets/smash.gif");
    ragequit_.set(anim);
    this->get_vbox()->add(ragequit_);
    Gtk::Button *okButton = add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    show_all();
}

RagequitDialog::~RagequitDialog()
{

}