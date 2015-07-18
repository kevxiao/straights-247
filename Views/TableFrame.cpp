#include "TableFrame.h"
#include "DeckGUI.h"

TableFrame::TableFrame(): title_("Table", Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP), tableContainer_(false, 0), vBoxContainer_(true, UI_SPACING)
{
    tableContainer_.set_border_width(UI_SPACING);
    tableContainer_.add(title_);
    tableContainer_.add(vBoxContainer_);

    add(tableContainer_);

    for(int i = 0; i < 52; i++)
    {
        card_[i] = NULL;
    }

    resetTable();
}

TableFrame::~TableFrame()
{
    deleteCards();

    deleteRows();
}

void TableFrame::resetTable()
{
    deleteCards();

    deleteRows();

    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
    for(int j = 0; j < SUIT_COUNT*RANK_COUNT; j++)
    {
        card_[j] = new Gtk::Image( nullCardPixbuf );
    }

    addCardsToRows();

    addRowsToContainer();

    show_all_children();
}

void TableFrame::addCardToTable(CardType cardToAdd)
{
    addCardToTable(cardToAdd.getRank(), cardToAdd.getSuit());
}

void TableFrame::addCardToTable(Rank rankOfCard, Suit suitOfCard)
{
    const Glib::RefPtr<Gdk::Pixbuf> cardPixBuf = deck.getCardImage(rankOfCard, suitOfCard);

    delete card_[(suitOfCard * RANK_COUNT) + rankOfCard];
    card_[(suitOfCard * RANK_COUNT) + rankOfCard] = new Gtk::Image( cardPixBuf );

    deleteRows();

    addCardsToRows();

    addRowsToContainer();
    
    show_all_children();
}

void TableFrame::addCardsToRows()
{
    for(int j = 0; j < SUIT_COUNT; j++)
    {
        rowHBoxes_[j] = new Gtk::HBox(true, UI_SPACING);
        for (int i = 0; i < RANK_COUNT; i++ )
        {
            rowHBoxes_[j]->add( *card_[(j * RANK_COUNT) + i] );
        }
    }
}

void TableFrame::addRowsToContainer()
{
    vector<Widget *> currentItems = vBoxContainer_.get_children();
    for(unsigned int i = 0; i < currentItems.size(); i++)
    {
        vBoxContainer_.remove(*currentItems.at(i));
    }

    for(int j = 0; j < SUIT_COUNT; j++)
    {
        vBoxContainer_.add(*rowHBoxes_[j]);
    }
}

void TableFrame::deleteCards()
{
    for(int i = 0; i < 52; i++)
    {
        if(card_[i] != NULL)
        {
            delete card_[i];
            card_[i] = NULL;
        }
    }
}

void TableFrame::deleteRows()
{
    vector<Widget *> currentItems = vBoxContainer_.get_children();
    for(unsigned int i = 0; i < currentItems.size(); i++)
    {
        vBoxContainer_.remove(*currentItems.at(i));
        delete currentItems.at(i);
    }

    for(int i = 0; i < SUIT_COUNT; i++)
    {
        rowHBoxes_[i] = NULL;
    }
}
