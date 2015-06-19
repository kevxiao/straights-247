#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <type_traits>

#include "../Controllers/GameController.h"
#include "../Models/DeckModel.h"
#include "../Models/GameModel.h"
#include "../Models/TableModel.h"
#include "View.h"

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
        printDeck();
        std::cout << std::endl;
        std::vector<std::shared_ptr<Card> > cards = deckModel_->getCards();
        for (int i = 10; i < cards.size() - 10; ++i) {
            tableModel_->addCardToTable(cards[i]);
        }
        printTable();
    }
}

void View::run() {
    gameController_->startGame();
}

void View::printDeck() const {
    auto deck = deckModel_->getCards();
    for (int i = 0; i < SUIT_COUNT; ++i) {
        for (int j = 0; j < RANK_COUNT; ++j) {
            if (j != 0) {
                std::cout << " ";
            }
            std::cout << *(deck[SUIT_COUNT * i + j]);
        }
        std::cout << std::endl;
    }
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
            if (rit != it->second.cbegin()) {
                std::cout << " ";
            }
            switch (rit->first) {
                case (JACK):
                    std::cout << 'J';
                    break;
                case (QUEEN):
                    std::cout << 'Q';
                    break;
                case (KING):
                    std::cout << 'K';
                    break;
                default:
                    std::cout << int(rit->first) + 1;
                    break;
            }
        }
        std::cout << std::endl;
    }
}
