#ifndef HANDFRAME_H
#define HANDFRAME_H

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

#include <iostream>

#include "../Controllers/GameController.h"
#include "../Lib/Constants.h"
#include "../Lib/Command.h"
#include "../Models/GameModel.h"
#include "DeckGUI.h"

class HandFrame : public Gtk::Frame {
public:
    HandFrame(GameModel *, GameController *);   // constructor
	virtual ~HandFrame();                       // deconstructor

    void resetHand();                           // mutator - resets the hand to display 13 blank card images
    void displayPlayerHand(unsigned int);       // mutator - displays the current player's hand

private:
    void clearContainer();                      // mutator - clears the main hBoxContainer
    void deleteCards();                         // mutator - deletes all of the card images and buttons
    void createNewButton(Gtk::Image *);         // mutator - creates a button with the specificed image and adds it to interal vectors
    void playCard(CardType) const;              // mutator - recieves button press and sends play card signal to PlayerModel
    bool isCardLegalMove(std::shared_ptr<Card>, std::vector<CardType>) const;    // accessor - checks if card is in vector of legalMoves

    DeckGUI deck;                               // deckGUI which returns pixbufs for card images
    GameController *gameController_;            // pointer to the gameController
    GameModel *gameModel_;                      // pointer to the gameModel

    Gtk::Label title_;                           // title label for the frame
    Gtk::VBox handContainer_;                    // container to split the text from the images
    Gtk::HBox hBoxContainer_;                    // main container for all elements within this frame
    vector <Gtk::Image *> displayedImages_;      // vector of all card images that are displayed or within buttons
    vector <Gtk::Button *> displayedCardButtons_;// vector of all buttons we are displaying
};

#endif
