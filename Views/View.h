#include "../Controllers/DeckController.h"
#include "../Controllers/TableController.h"
#include "../Controllers/GameController.h"
#include "../Lib/Observer.h"

class View : public Observer
{
public:
    View(GameController *, DeckController *, TableController *, GameModel *, DeckModel *, TableModel *);
    virtual ~View();
    virtual void update();
    void run();
    void printDeck() const;
    void printTable() const;
private:
    GameModel *gameModel_;
    DeckModel *deckModel_;
    TableModel *tableModel_;
    GameController *gameController_;
    DeckController *deckController_;
    TableController *tableController_;
};
