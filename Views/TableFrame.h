#ifndef TABLEFRAME_H
#define TABLEFRAME_H

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>

#include "../Lib/Constants.h"
#include "../Lib/CardType.h"
#include "DeckGUI.h"

class TableFrame : public Gtk::Frame {
public:
    TableFrame();                       // constructor
	virtual ~TableFrame();              // destructor

    void resetTable();                  // mutator - resets the table to display 52 blank card images 
    void addCardToTable(CardType);      // mutator - adds a card to the table and renders the Frame again
    void addCardToTable(Rank, Suit);    // mutator - adds a card to the table and renders the Frame again
private:
    void addCardsToRows();              // mutator - adds all of the cards to the appropriate rows
    void addRowsToContainer();          // mutator - adds all of the rows to the container
    void deleteCards();                 // mutator - deletes the card images
    void deleteRows();                  // mutator - deletes the rowHBoxes

    DeckGUI deck;                       // deckGUI that will retrieve pixbufs for any card that we need to display

    Gtk::VBox vBoxContainer;            // main container for elements in this frame
    Gtk::HBox* rowHBoxes[4];            // hboxes that will each display one row of the cards on the table
    Gtk::Image * card[52];              // images to display.
};

#endif
