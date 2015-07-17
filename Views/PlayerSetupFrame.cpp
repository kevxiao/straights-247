#include "PlayerSetupFrame.h"

PlayerSetupFrame::PlayerSetupFrame( const Glib::ustring& label) : Frame(label)
{
    set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	set_shadow_type( Gtk::SHADOW_ETCHED_OUT );

    humanButton = new Gtk::RadioButton(buttonGroup, "Human");
    computerButton = new Gtk::RadioButton(buttonGroup, "Computer");
    computerButton->set_active();

    vBoxContainer.add(*humanButton);
    vBoxContainer.add(*computerButton);
    add(vBoxContainer);
}

PlayerSetupFrame::~PlayerSetupFrame()
{
    delete humanButton;
    delete computerButton;
}

bool PlayerSetupFrame::isHuman() const
{
    return humanButton->get_active();
}
