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
    // initialize all the required models and controllers
    DeckModel *deckModel = new DeckModel();
    TableModel *tableModel = new TableModel();
    GameModel *gameModel = new GameModel(tableModel, deckModel);
    DeckController *deckController = new DeckController(gameModel);
    TableController *tableController = new TableController(gameModel);
    GameController *gameController = new GameController(gameModel, deckController, tableController);
    GameView game(gameController, gameModel);
    // run the view
    kit.run(game);
    return 0;
}
