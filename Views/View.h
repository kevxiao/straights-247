#include "../Models/GameModel.h"
#include "../Lib/Observer.h"

class View : public Observer
{
public:
    View();
    virtual ~View();
    virtual void update();

private:
    GameModel gameModel_;
};
