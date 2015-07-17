#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <gtkmm.h>
#include "../Controllers/DeckController.h"
#include "../Controllers/TableController.h"
#include "../Controllers/GameController.h"
#include "../Lib/Observer.h"
#include "../Lib/Constants.h"
#include "AllPlayersWidget.h"
#include "DeckGUI.h"
#include "SeedDialogBox.h"
#include "PlayerSetupDialogBox.h"

// view class derived from observer class
class GameView : public Gtk::Window, public Observer
{
public:
    GameView(GameController *, GameModel *);     // constructor
    virtual ~GameView();                                                    // destructor
    virtual void update();                                              // mutator - update view with model info
    void printDeck() const;                                             // accessor - print deck in order
    void printTable() const;                                            // accessor - print sorted cards on table
protected:
    DeckGUI deck;             // Knows all of the card pixel buffers.

    // Member widgets:
    Gtk::Image * card[52];          // Images to display.
    Gtk::HBox * cardHBoxes[4];
    Gtk::Button startGameButton;
    Gtk::Button endGameButton;
    Gtk::VBox containerBox;
    Gtk::HBox gameButtonHBox;
    AllPlayersWidget allPlayersWidget_;

    // signals
    void onStartGameButtonClicked();
private:
    GameModel *gameModel_;                                              // pointer to game model
    GameController *gameController_;                                    // pointer to game controller
};

#endif