#ifndef HANDFRAME_H
#define HANDFRAME_H

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>

#include <iostream>

#include "../Lib/Constants.h"
#include "../Models/GameModel.h"
#include "DeckGUI.h"

class HandFrame : public Gtk::Frame {
public:
    HandFrame(GameModel *);
	virtual ~HandFrame();

    void resetHand();
    void displayPlayerHand();

private:
    void clearContainer();
    void deleteCards();
    void createNewButton(Gtk::Image *);
    void playCard(CardType cardPlayed);
    bool isCardLegalMove(std::shared_ptr<Card> cardToCheck, std::vector<CardType> legalMoves);

    DeckGUI deck;
    GameModel *gameModel_;

    Gtk::HBox hBoxContainer;
    vector <Gtk::Image *> displayedImages;
    vector <Gtk::Button *> displayedCardButtons;
};

#endif
