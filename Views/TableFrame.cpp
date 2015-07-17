#include "TableFrame.h"
#include "DeckGUI.h"

TableFrame::TableFrame(): Frame("Table"), vBoxContainer(true, UI_SPACING)
{
    vBoxContainer.set_border_width(UI_SPACING);

    add(vBoxContainer);

    for(int i = 0; i < 52; i++)
    {
        card[i] = NULL;
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
        card[j] = new Gtk::Image( nullCardPixbuf );
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

    delete card[(suitOfCard * RANK_COUNT) + rankOfCard];
    card[(suitOfCard * RANK_COUNT) + rankOfCard] = new Gtk::Image( cardPixBuf );

    deleteRows();

    addCardsToRows();

    addRowsToContainer();
    
    show_all_children();
}

void TableFrame::addCardsToRows()
{
    for(int j = 0; j < SUIT_COUNT; j++)
    {
        rowHBoxes[j] = new Gtk::HBox(true, UI_SPACING);
        for (int i = 0; i < RANK_COUNT; i++ )
        {
            rowHBoxes[j]->add( *card[(j * RANK_COUNT) + i] );
        }
    }
}

void TableFrame::addRowsToContainer()
{
    vector<Widget *> currentItems = vBoxContainer.get_children();
    for(unsigned int i = 0; i < currentItems.size(); i++)
    {
        vBoxContainer.remove(*currentItems.at(i));
    }

    for(int j = 0; j < SUIT_COUNT; j++)
    {
        vBoxContainer.add(*rowHBoxes[j]);
    }
}

void TableFrame::deleteCards()
{
    for(int i = 0; i < 52; i++)
    {
        if(card[i] != NULL)
        {
            delete card[i];
            card[i] = NULL;
        }
    }
}

void TableFrame::deleteRows()
{
    vector<Widget *> currentItems = vBoxContainer.get_children();
    for(unsigned int i = 0; i < currentItems.size(); i++)
    {
        vBoxContainer.remove(*currentItems.at(i));
        delete currentItems.at(i);
    }

    for(int i = 0; i < SUIT_COUNT; i++)
    {
        rowHBoxes[i] = NULL;
    }
}
