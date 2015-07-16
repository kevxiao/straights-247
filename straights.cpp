#include <iostream>
#include <gtkmm.h>
#include <vector>
#include <cstdlib>
#include "Controllers/GameController.h"
#include "Controllers/DeckController.h"
#include "Models/GameModel.h"
#include "Models/DeckModel.h"
#include "Models/TableModel.h"
#include "Models/CardModel.h"
#include "Views/GameView.h"

using namespace std;



int main(int argc, char* argv[])
{
    Gtk::Main kit(&argc, &argv);
    int firstArg = 0;
    if (argc > 1) {
        firstArg = atoi(argv[1]);
    }
    // initialize all the required models and controllers
    DeckModel *deckModel = new DeckModel();
    TableModel *tableModel = new TableModel();
    GameModel *gameModel = new GameModel();
    DeckController *deckController = new DeckController((unsigned long) firstArg, deckModel);
    TableController *tableController = new TableController(tableModel);
    GameController *gameController = new GameController(gameModel, deckController, tableController);
    GameView game(gameController, gameModel, deckModel, tableModel);
    // run the view
    kit.run(game);
    return 0;
}
