#include "HandFrame.h"

HandFrame::HandFrame(GameModel *gameModel): Frame("Hand"), 
    gameModel_(gameModel), hBoxContainer(false, UI_SPACING)
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

    for(int i = 0; i < RANK_COUNT; i++)
    {
        displayedImages.push_back(new Gtk::Image( nullCardPixbuf ));

        hBoxContainer.add(*displayedImages.at(i));
    }

    show_all_children();
}

void HandFrame::displayPlayerHand()
{
    clearContainer();

    deleteCards();

    unsigned int curPlayerNum = gameModel_->getCurPlayerNum();
    std::shared_ptr<PlayerModel> playerModel_ = gameModel_->getPlayerModel(curPlayerNum);

    std::vector<std::shared_ptr<Card> > playerHand = playerModel_->getHand();
    std::vector<CardType> legalMoves = playerModel_->getLegalMoves();

    for(unsigned int i = 0; i < playerHand.size(); i++)
    {
        createNewButton( new Gtk::Image (deck.getCardImage( playerHand.at(i)->getRank(), playerHand.at(i)->getSuit())));

        int buttonIndex = displayedCardButtons.size() - 1;

        bool canClick = legalMoves.size() == 0 || isCardLegalMove(playerHand.at(i), legalMoves);
        displayedCardButtons.at(buttonIndex)->set_sensitive(canClick);

        displayedCardButtons.at(buttonIndex)->signal_clicked().connect(sigc::bind<CardType>( sigc::mem_fun(*this, &HandFrame::playCard), CardType(playerHand.at(i)->getSuit(), playerHand.at(i)->getRank())));

        hBoxContainer.add(*displayedCardButtons.at(displayedCardButtons.size() - 1));
    }

    int numOfCards = playerHand.size();

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

void HandFrame::playCard(CardType cardToPlay) const
{
    // Add functiontionality here after
}

bool HandFrame::isCardLegalMove(std::shared_ptr<Card> cardToCheck, std::vector<CardType> legalMoves) const
{
    for(unsigned int i = 0; i < legalMoves.size(); i++)
    {
        if(cardToCheck->hasValue(legalMoves.at(i)))
        {
            return true;
        }
    }
    return false;
}
