#include <iostream>
#include <vector>
#include <cstdlib>
#include "Controllers/GameController.h"
#include "Controllers/DeckController.h"
#include "Models/GameModel.h"
#include "Models/DeckModel.h"
#include "Models/TableModel.h"
#include "Models/Card.h"
#include "Views/View.h"

using namespace std;

int main(int argc, char* argv[])
{
    int firstArg = 0;
    if (argc > 1) {
        firstArg = atoi(argv[1]);
    }
    GameModel *gameModel = new GameModel();
    DeckModel *deckModel = new DeckModel();
    TableModel *tableModel = new TableModel();
    DeckController *deckController = new DeckController((unsigned long) firstArg, deckModel);
    TableController *tableController = new TableController(tableModel);
    GameController *gameController = new GameController(gameModel, deckController, tableController);
    View *view = new View(gameController, gameModel, deckModel, tableModel);
    view->run();
    delete view;
    return 0;
}
