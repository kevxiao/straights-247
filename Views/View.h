#include "../Models/GameModel.h"
#include "../Models/DeckModel.h"
#include "../Models/TableModel.h"
#include "../Controllers/GameController.h"
#include "../Lib/Observer.h"

class View : public Observer
{
public:
    View(GameController *, GameModel *, DeckModel *, TableModel *);
    virtual ~View();
    virtual void update();
    void run();
    void printTable() const;
private:
    GameModel *gameModel_;
    DeckModel *deckModel_;
    TableModel *tableModel_;
    GameController *gameController_;
};
