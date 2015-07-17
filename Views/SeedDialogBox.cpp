#include "SeedDialogBox.h"
#include <iostream>
#include <sstream>

SeedDialogBox::SeedDialogBox( Gtk::Window & parentWindow, string title) : Dialog( "New game", parentWindow, true, true ), seedPrompt_(" Enter the starting seed: ") {

    isValidSeed_ = false;
    seedValue_ = 0;

	Gtk::VBox* contentArea = this->get_vbox();

    contentArea->add(container_);

    seedEntry_.set_text("0");

    container_.add(seedPrompt_);
    container_.add(seedEntry_);
	
    Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);  	
}

SeedDialogBox::~SeedDialogBox() {

}

void SeedDialogBox::popupAndUpdate() {
    show_all_children();
    std::stringstream ssSeed;
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            isValidSeed_ = true;
            ssSeed << seedEntry_.get_text();
            ssSeed >> seedValue_;
            break;
        default:
            isValidSeed_ = false;
    }
    hide();
}

bool SeedDialogBox::isSeedValid() const {
    return isValidSeed_;
}

unsigned long SeedDialogBox::getSeedValue() const {
    return seedValue_;
}
