#include "PlayerSetupDialogBox.h"

PlayerSetupDialogBox::PlayerSetupDialogBox(Gtk::Window & parentWindow):Dialog( "Player Setup", parentWindow, true, true )
{
    Gtk::VBox* contentArea = this->get_vbox();

    for(int i = 0; i < 4; i++)
    {
        playerSetupFrames[i] = new PlayerSetupFrame("Player " + std::to_string(i + 1));
        containerBox.add(*playerSetupFrames[i]);
    }
    contentArea->add(containerBox);

    Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);  	
}

PlayerSetupDialogBox::~PlayerSetupDialogBox()
{
    for(int i = 0; i < 4; i++)
    {
        delete playerSetupFrames[i];
    }
}

vector<bool> PlayerSetupDialogBox::popupAndGetPlayerStatus()
{
    vector<bool> playerStatuses;

    show_all_children();
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            for(int i = 0; i < 4; i++)
            {
                playerStatuses.push_back(playerSetupFrames[i]->isHuman());
            }
            break;
    }
    return playerStatuses; 
}
