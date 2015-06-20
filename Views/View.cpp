#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../Controllers/GameController.h"
#include "../Models/DeckModel.h"
#include "../Models/GameModel.h"
#include "../Models/TableModel.h"
#include "View.h"

View::View(GameController * gameController, GameModel * gameModel, DeckModel * deckModel,
           TableModel * tableModel) : gameModel_(gameModel), deckModel_(deckModel),
           tableModel_(tableModel), gameController_(gameController)
{
    gameModel->subscribe(this);
}

View::~View()
{
    delete gameModel_;
    delete deckModel_;
    delete tableModel_;
    delete gameController_;
}

void View::update()
{
    switch (gameModel_->getGameStatus())
    {
        case INIT_GAME:
        {
            std::string input;
            std::cout << "Is player " << gameModel_->getCurPlayerNum() << " a human(h) or a computer(c)?" << std::endl;
            std::getline(std::cin, input);
            gameController_->processInput(input);
            break;
        } //TODO: Deal with braces
        case START_ROUND:
            std::cout << "A new round begins. It\'s player " << gameModel_->getCurPlayerNum() << "\'s turn to play." << std::endl;
            break;
        case START_TURN:
            if (!gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->isComputer())
            {
                printTable();
                // TODO: print hand and legal moves
            }
            break;
        case IN_TURN:
            if (!gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->isComputer())
            {
                std::string player_input;
                std::getline(std::cin, player_input);
                try {
                    gameController_->processInput(player_input);
                } catch (std::string e) {
                    std::cout << e << std::endl;
                    update();
                }

            }
            break;
        case DECK_COMMAND:
            printDeck();
            break;
        case RAGEQUIT_COMMAND:
            std::cout << "Player " << gameModel_->getCurPlayerNum() << " ragequits. A computer will now take over." << std::endl;
            break;
        case END_TURN:

            break;
        case END_ROUND:
            unsigned int score, discardScore;
            for (unsigned int i = 0; i < gameModel_->getNumPlayers(); ++i)
            {
                std::cout << "Player " << i << "\'s discards: ";
                for (unsigned int j = 0; j < gameModel_->getPlayerModel(i)->getDiscards().size(); ++j)
                {
                    if (j != 0) {
                        std::cout << " ";
                    }
                    std::cout << *(gameModel_->getPlayerModel(i)->getDiscards()[j]);
                };
                score = gameModel_->getPlayerModel(i)->getScore();
                discardScore = gameModel_->getPlayerModel(i)->getValOfDiscards();
                std::cout << std::endl << "Player "<< i << "\'s score: " << score << " + " << discardScore << " = " << score + discardScore << std::endl;
            }
            break;
        case END_GAME:
            std::cout << "Player " << gameModel_->getCurPlayerNum() << " wins!";
            return;
        default:
            return;
    }
}

void View::run()
{
    gameController_->startGame();
}

void View::printDeck() const
{
    auto deck = deckModel_->getCards();
    for (int i = 0; i < SUIT_COUNT; ++i)
    {
        for (int j = 0; j < RANK_COUNT; ++j)
        {
            if (j != 0) {
                std::cout << " ";
            }
            std::cout << *((*deck)[SUIT_COUNT * i + j]);
        }
        std::cout << std::endl;
    }
}

void View::printTable() const
{
    auto table = tableModel_->getCardsOnTable();
    std::cout << "Cards on the table:" << std::endl;
    for (auto it = table->cbegin(); it != table->cend(); ++it)
    {
        switch (it->first)
        {
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
        for (auto rit = it->second.cbegin(); rit != it->second.cend(); ++rit)
        {
            if (rit != it->second.cbegin())
            {
                std::cout << " ";
            }
            switch (rit->first)
            {
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
