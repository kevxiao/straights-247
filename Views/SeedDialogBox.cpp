#include "SeedDialogBox.h"
#include <iostream>

SeedDialogBox::SeedDialogBox( Gtk::Window & parentWindow, string title) : Dialog( "New game", parentWindow, true, true ), seedPrompt(" Enter the starting seed: ") {
	
	Gtk::VBox* contentArea = this->get_vbox();

    contentArea->add(container);

    seedEntry.set_text("0");

    container.add(seedPrompt);
    container.add(seedEntry);
	
    Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);  	
}

SeedDialogBox::~SeedDialogBox() {

}

int SeedDialogBox::popupAndGetSeed() {
    show_all_children();
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            return atoi(seedEntry.get_text().c_str());
            break;
        default:
            return -1;
    }
}
