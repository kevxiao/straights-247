#include "HandFrame.h"

HandFrame::HandFrame(GameModel *gameModel): Frame("Hand"), gameModel_(gameModel), hBoxContainer(false, UI_SPACING)
{
    hBoxContainer.set_border_width(UI_SPACING);

    add(hBoxContainer);
    resetHand();
}

HandFrame::~HandFrame()
{
    deleteCards();
}

void HandFrame::resetHand()
{
    vector<Widget *> oldChildren = hBoxContainer.get_children();
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();

    for(unsigned int i = 0; i < oldChildren.size(); i++)
    {
        hBoxContainer.remove(*oldChildren.at(i));
    }
    deleteCards();

    displayedImages.push_back(new Gtk::Image( nullCardPixbuf ));

    hBoxContainer.add(*displayedImages.at(0));

    show_all_children();

    displayPlayerHand();
}

void HandFrame::displayPlayerHand()
{
    //Insert getting player's hand, creating new buttons and images based on cards in hand and putting them in hBoxContainer and displayedCards

    clearContainer();

    deleteCards();
    
    createNewButton( new Gtk::Image (deck.getCardImage( Rank::ACE, Suit::HEART)));

    hBoxContainer.add(*displayedCardButtons.at(0));

    int numOfCards = 1;

    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();

    for(int i = numOfCards; i < RANK_COUNT; i++)
    {
        displayedImages.push_back(new Gtk::Image( nullCardPixbuf ));
        hBoxContainer.add(*displayedImages.at(i));
    }

    show_all_children();
}

void HandFrame::clearContainer()
{
    vector<Widget *> oldChildren = hBoxContainer.get_children();
    for(unsigned int i = 0; i < oldChildren.size(); i++)
    {
        hBoxContainer.remove(*oldChildren.at(i));
    }
}

void HandFrame::deleteCards()
{
    for(unsigned int i = 0; i < displayedImages.size(); i++)
    {
        delete displayedImages.at(i);
    }
    displayedImages.clear();

    for(unsigned int i = 0; i < displayedCardButtons.size(); i++)
    {
        delete displayedCardButtons.at(i);
    }
    displayedCardButtons.clear();
}

void HandFrame::createNewButton(Gtk::Image *buttonImage)
{
    displayedImages.push_back(buttonImage);
    int addedImageIndex = displayedImages.size() - 1;

    displayedCardButtons.push_back(new Gtk::Button());
    int addedButtonNum = displayedCardButtons.size() - 1;

    displayedCardButtons.at(addedButtonNum)->set_image(*displayedImages.at(addedImageIndex));     
}
