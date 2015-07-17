#include "DiscardsDialog.h"
#include "../Lib/Constants.h"

DiscardsDialog::DiscardsDialog(GameModel * gameModel, unsigned int playerNum) :
        firstRow(true, UI_SPACING), secondRow(true, UI_SPACING)
{
    Gtk::VBox *dialogContent = this->get_vbox();
    unsigned long first, second;
    //auto discards = gameModel->getPlayerModel(playerNum)->getDiscards();
    std::vector<bool> discards;
    discards.push_back(true);
    discards.push_back(true);
    discards.push_back(true);
    discards.push_back(true);
    discards.push_back(true);
    second = discards.size() / 2;
    if (discards.size() % 2 != 0)
    {
        first = second + 1;
    }
    else
    {
        first = second;
    }
    for (int i = 0; i < first; ++i)
    {
        firstRow.add(*(new Gtk::Label("something")));
    }
    for (int i = 0; i < second; ++i)
    {
        secondRow.add(*(new Gtk::Label("something")));
    }
    dialogContent->add(firstRow);
    dialogContent->add(secondRow);
    Gtk::Button *okButton = add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    show_all_children();
}

DiscardsDialog::~DiscardsDialog()
{

}
