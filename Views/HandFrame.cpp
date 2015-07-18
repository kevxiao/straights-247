#include "HandFrame.h"

HandFrame::HandFrame(GameModel *gameModel, GameController *gameController): gameController_(gameController),
     gameModel_(gameModel), title_("Hand", Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP), handContainer_(false, 0), hBoxContainer_(false, UI_SPACING)
{
    handContainer_.set_border_width(UI_SPACING);

    handContainer_.add(title_);
    handContainer_.add(hBoxContainer_);
    add(handContainer_);
    resetHand();
}

HandFrame::~HandFrame()
{
    deleteCards();
}

void HandFrame::resetHand()
{
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();

    clearContainer();
    title_.set_text("Hand");
    deleteCards();

    for(unsigned int i = 0; i < RANK_COUNT; i++)
    {
        displayedImages_.push_back(new Gtk::Image( nullCardPixbuf ));

        hBoxContainer_.add(*displayedImages_.at(i));
    }

    show_all_children();
}

void HandFrame::displayPlayerHand(unsigned int playerNum)
{
    clearContainer();

    deleteCards();

    std::shared_ptr<PlayerModel> playerModel_ = gameModel_->getPlayerModel(playerNum);

    std::vector<std::shared_ptr<Card> > playerHand = playerModel_->getHand();
    std::vector<CardType> legalMoves = playerModel_->getLegalMoves();

    title_.set_text((legalMoves.size() > 0) ? "Your Hand: Please play a card" : "Your Hand: No legal plays, please discard a card");

    for(unsigned int i = 0; i < playerHand.size(); i++)
    {
        createNewButton( new Gtk::Image (deck.getCardImage( playerHand.at(i)->getRank(), playerHand.at(i)->getSuit())));

        unsigned long buttonIndex = displayedCardButtons_.size() - 1;

        bool canClick = legalMoves.size() == 0 || isCardLegalMove(playerHand.at(i), legalMoves);
        displayedCardButtons_.at(buttonIndex)->set_sensitive(canClick);

        if (legalMoves.size() > 0 && legalMoves.at(0) == CardType(Suit::SPADE, Rank::SEVEN) && !canClick)
        {
            displayedCardButtons_.at(buttonIndex)->set_tooltip_text("I'm sorry, did you mean the SEVEN OF SPADES?!");
        }

        displayedCardButtons_.at(buttonIndex)->signal_clicked().connect(sigc::bind<CardType>( sigc::mem_fun(*this, &HandFrame::playCard), CardType(playerHand.at(i)->getSuit(), playerHand.at(i)->getRank())));

        hBoxContainer_.add(*displayedCardButtons_.at(displayedCardButtons_.size() - 1));
    }

    unsigned long numOfCards = playerHand.size();

    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();

    for(unsigned long i = numOfCards; i < RANK_COUNT; i++)
    {
        displayedImages_.push_back(new Gtk::Image( nullCardPixbuf ));
        hBoxContainer_.add(*displayedImages_.at(i));
    }

    show_all_children();
}

void HandFrame::clearContainer()
{
    vector<Widget *> oldChildren = hBoxContainer_.get_children();
    for(unsigned int i = 0; i < oldChildren.size(); i++)
    {
        hBoxContainer_.remove(*oldChildren.at(i));
    }
}

void HandFrame::deleteCards()
{
    for(unsigned int i = 0; i < displayedImages_.size(); i++)
    {
        delete displayedImages_.at(i);
    }
    displayedImages_.clear();

    for(unsigned int i = 0; i < displayedCardButtons_.size(); i++)
    {
        delete displayedCardButtons_.at(i);
    }
    displayedCardButtons_.clear();
}

void HandFrame::createNewButton(Gtk::Image *buttonImage)
{
    displayedImages_.push_back(buttonImage);
    unsigned long addedImageIndex = displayedImages_.size() - 1;

    displayedCardButtons_.push_back(new Gtk::Button());
    unsigned long addedButtonNum = displayedCardButtons_.size() - 1;

    displayedCardButtons_.at(addedButtonNum)->set_image(*displayedImages_.at(addedImageIndex));     
}

void HandFrame::playCard(CardType cardToPlay) const
{
    Type commandType = PLAY;
    std::shared_ptr<PlayerModel> curPlayer = gameModel_->getPlayerModel(gameModel_->getCurPlayerNum());
    if(curPlayer->getLegalMoves().size() == 0)
    {
        commandType = DISCARD;
    }
    Command playerCommand(commandType, cardToPlay);
    gameController_->processPlayerCommand(playerCommand);
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
