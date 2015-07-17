#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <gtkmm.h>
#include "../Controllers/DeckController.h"
#include "../Controllers/TableController.h"
#include "../Controllers/GameController.h"
#include "../Lib/Observer.h"
#include "../Lib/Constants.h"
#include "AllPlayersWidget.h"
#include "TableFrame.h"
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

private:
    GameModel *gameModel_;                                              // pointer to game model
    GameController *gameController_;                                    // pointer to game controller

    // Member widgets:
    Gtk::Button startGameButton;
    Gtk::Button endGameButton;
    Gtk::VBox containerBox;
    Gtk::HBox gameButtonHBox;
    AllPlayersWidget allPlayersWidget_;
    TableFrame tableFrame_;

    // signals
    void onStartGameButtonClicked();
};

#endif
