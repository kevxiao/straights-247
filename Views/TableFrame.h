#ifndef TABLEFRAME_H
#define TABLEFRAME_H

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>

#include <iostream>

#include "../Lib/Constants.h"
#include "DeckGUI.h"

class TableFrame : public Gtk::Frame {
public:
    TableFrame();
	virtual ~TableFrame();

    void resetTable();
    void addCardToTable(Rank, Suit);
private:
    void addCardsToRows();
    void addRowsToContainer();
    void deleteCards();
    void deleteRows();

    DeckGUI deck;

    Gtk::VBox vBoxContainer;
    Gtk::HBox* rowHBoxes[4];
    Gtk::Image * card[52];          // Images to display.
};

#endif
