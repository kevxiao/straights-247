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
    HandFrame(GameModel *);                     // constructor
	virtual ~HandFrame();                       // deconstructor

    void resetHand();                           // mutator - resets the hand to display 13 blank card images
    void displayPlayerHand();                   // mutator - displays the current player's hand

private:
    void clearContainer();                      // mutator - clears the main hBoxContainer
    void deleteCards();                         // mutator - deletes all of the card images and buttons
    void createNewButton(Gtk::Image *);         // mutator - creates a button with the specificed image and adds it to interal vectors
    void playCard(CardType cardPlayed) const;   // mutator - recieves button press and sends play card signal to PlayerModel
    bool isCardLegalMove(std::shared_ptr<Card> cardToCheck, std::vector<CardType> legalMoves) const;    // accessor - checks if card is in vector of legalMoves

    DeckGUI deck;                               // deckGUI which returns pixbufs for card images
    GameModel *gameModel_;                      // pointer to the gameModel

    Gtk::HBox hBoxContainer;                    // main container for all elements within this frame
    vector <Gtk::Image *> displayedImages;      // vector of all card images that are displayed or within buttons
    vector <Gtk::Button *> displayedCardButtons;// vector of all buttons we are displaying
};

#endif
