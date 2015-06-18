#include "GameModel.h"

GameModel::GameModel() {
    gameStatus_ = INIT_GAME;
}

GameModel::~GameModel() {
}

GameStatus GameModel::gameStatus() const {
    return gameStatus_;
}

void GameModel::setGameStatus(GameStatus newGameStatus) {
    gameStatus_ = newGameStatus;
}

std::queue<GameEvent *> GameModel::getGameEvents() {
    return gameEvents_;
}
