#include <iostream>
#include <string>
#include <vector>
#include "../Controllers/GameController.h"
#include "../Models/DeckModel.h"
#include "../Models/GameModel.h"
#include "../Models/TableModel.h"
#include "View.h"
#include <type_traits>

View::View(GameController * gameController, GameModel * gameModel, DeckModel * deckModel,
    TableModel * tableModel) : gameModel_(gameModel), gameController_(gameController), deckModel_(deckModel),
    tableModel_(tableModel) {
    gameModel->subscribe(this);
}

View::~View() {
    delete gameModel_;
    delete deckModel_;
    delete tableModel_;
    delete gameController_;
}

void View::update() {
    if (gameModel_->gameStatus() == INIT_GAME) {
        std::vector<Card *> cards = deckModel_->getCards();
        for (int i = 10; i < cards.size() - 10; ++i) {
            tableModel_->addCardToTable(cards[i]);
        }
        printTable();
    }
}

void View::run() {
    gameController_->startGame();
}

void View::printTable() const {
    auto table = tableModel_->getCardsOnTable();
    std::cout << "Cards on the table:" << std::endl;
    for (auto it = table.cbegin(); it != table.cend(); ++it) {
        switch (it->first) {
            case (CLUB):
                std::cout << "Clubs: ";
                break;
            case (DIAMOND):
                std::cout << "Diamonds: ";
                break;
            case (HEART):
                std::cout << "Hearts: ";
                break;
            case (SPADE):
                std::cout << "Spades: ";
                break;
            default:
                return;
        }
        for (auto rit = it->second.cbegin(); rit != it->second.cend(); ++rit) {
            switch (rit->first) {
                case (JACK):
                    std::cout << 'J' << " ";
                    break;
                case (QUEEN):
                    std::cout << 'Q' << " ";
                    break;
                case (KING):
                    std::cout << 'K' << " ";
                    break;
                default:
                    std::cout << int(rit->first) + 1 << " ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}