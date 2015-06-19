#include <iostream>
#include <string>
#include "../Controllers/GameController.h"
#include "../Models/DeckModel.h"
#include "../Models/GameModel.h"
#include "View.h"

View::View(GameController * gameController, GameModel * gameModel, DeckModel * deckModel) : gameModel_(gameModel), gameController_(gameController), deckModel_(deckModel) {
    gameModel->subscribe(this);
}

View::~View() {
    delete gameModel_;
}

void View::update() {
    if (gameModel_->gameStatus() == INIT_GAME) {
        char player;
        std::cin >> player;

    }
}

void View::run() {
    gameController_->startGame();
}
