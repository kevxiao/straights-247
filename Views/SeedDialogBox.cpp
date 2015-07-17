#include "SeedDialogBox.h"
#include <iostream>

SeedDialogBox::SeedDialogBox( Gtk::Window & parentWindow, string title) : Dialog( "New game", parentWindow, true, true ), seedPrompt(" Enter the starting seed: ") {

    isValidSeed = false;
    seedValue = 0;

	Gtk::VBox* contentArea = this->get_vbox();

    contentArea->add(container);

    seedEntry.set_text("0");

    container.add(seedPrompt);
    container.add(seedEntry);
	
    Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);  	
}

SeedDialogBox::~SeedDialogBox() {

}

void SeedDialogBox::popupAndUpdate() {
    show_all_children();
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            isValidSeed = true;
            seedValue = atoi(seedEntry.get_text().c_str());
            break;
        default:
            isValidSeed = false;
    }
    hide();
}

bool SeedDialogBox::isSeedValid() {
    return isValidSeed;
}

int SeedDialogBox::getSeedValue() {
    return seedValue;
}
