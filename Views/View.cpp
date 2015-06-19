#include <iostream>
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
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                std::cout << *(deckModel_->getCards()[13 * i + j]) << " ";
            }
            std::cout << std::endl;
        }
    }
}

void View::run() {
    gameController_->startGame();
}
