#include "DiscardsDialog.h"
#include "../Lib/Constants.h"

DiscardsDialog::DiscardsDialog(GameModel * gameModel, unsigned int playerNum) :
        firstRow(true, UI_SPACING), secondRow(true, UI_SPACING)
{
    set_title("Discards");
    Gtk::VBox *dialogContent = this->get_vbox();
    unsigned long first, second;
    std::shared_ptr<PlayerModel> playerModel = gameModel->getPlayerModel(playerNum);
    std::vector<std::shared_ptr<Card> > discards = playerModel->getDiscards();

    for(unsigned int i = 0; i < discards.size(); i++)
    {
        const Glib::RefPtr<Gdk::Pixbuf> curCardPixBuff = deck.getCardImage(discards.at(i)->getRank(), discards.at(i)->getSuit());
        discardImages.push_back(new Gtk::Image(curCardPixBuff));
    }

    first = discards.size() / 2 + discards.size() % 2;
    second = discards.size() / 2;

    for (unsigned int  i = 0; i < first; ++i)
    {
        firstRow.add(*discardImages.at(i));
    }
    for (unsigned int i = 0; i < second; ++i)
    {
        secondRow.add(*discardImages.at(i + first));
    }
    dialogContent->add(firstRow);
    dialogContent->add(secondRow);
    Gtk::Button *okButton = add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    show_all_children();
}

DiscardsDialog::~DiscardsDialog()
{
    for(unsigned int i = 0; i < discardImages.size(); i++)
    {
        delete discardImages.at(i);
    }
}
