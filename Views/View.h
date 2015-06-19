#include "../Models/GameModel.h"
#include "../Models/DeckModel.h"
#include "../Controllers/GameController.h"
#include "../Lib/Observer.h"

class View : public Observer
{
public:
    View(GameController *, GameModel *, DeckModel *);
    virtual ~View();
    virtual void update();
    void run();
private:
    GameModel *gameModel_;
    DeckModel *deckModel_;
    GameController *gameController_;
};
