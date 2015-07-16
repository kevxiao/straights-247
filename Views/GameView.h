#include <gtkmm.h>
#include "../Controllers/DeckController.h"
#include "../Controllers/TableController.h"
#include "../Controllers/GameController.h"
#include "../Lib/Observer.h"

// view class derived from observer class
class GameView : public Gtk::Window, public Observer
{
public:
    GameView(GameController *, GameModel *, DeckModel *, TableModel *);     // constructor
    virtual ~GameView();                                                    // destructor
    virtual void update();                                              // mutator - update view with model info
    void printDeck() const;                                             // accessor - print deck in order
    void printTable() const;                                            // accessor - print sorted cards on table
private:
    GameModel *gameModel_;                                              // pointer to game model
    DeckModel *deckModel_;                                              // pointer to deck model
    TableModel *tableModel_;                                            // pointer to table model
    GameController *gameController_;                                    // pointer to game controller
};
