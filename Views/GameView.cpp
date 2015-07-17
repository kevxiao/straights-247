#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

#include "../Controllers/GameController.h"
#include "../Models/GameModel.h"
#include "GameView.h"
#include "RagequitDialog.h"

// create view with required models and controllers, and subscribe to updates
GameView::GameView(GameController * gameController, GameModel * gameModel) : gameModel_(gameModel),
            gameController_(gameController), startGameButton_("Start New Game"), endGameButton_("End Current Game"), quitButton_("Quit Game"),
            containerBox_(false, UI_SPACING), gameButtonHBox_(true, UI_SPACING), allPlayersWidget_(gameController_, gameModel_)
{
    set_title("Straights");
    set_border_width(UI_SPACING);

    add( containerBox_ );
    containerBox_.add(gameButtonHBox_);

    startGameButton_.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onStartGameButtonClicked ) );
    endGameButton_.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onEndGameButtonClicked ) );
    quitButton_.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onQuitButtonClicked ) );
    startGameButton_.set_tooltip_text("Start the game already!");
    endGameButton_.set_tooltip_text("The true ragequit button.");
    quitButton_.set_tooltip_markup("<span foreground=\"red\">Baby don't leave me! T_T</span>");

    gameButtonHBox_.add(startGameButton_);
    gameButtonHBox_.add(endGameButton_);
    gameButtonHBox_.add(quitButton_);

    containerBox_.add(tableFrame_);

    tableFrame_.addCardToTable(Rank::ACE, Suit::CLUB);
    tableFrame_.addCardToTable(Rank::SIX, Suit::CLUB);
    tableFrame_.addCardToTable(Rank::SEVEN, Suit::CLUB);
    tableFrame_.addCardToTable(Rank::SEVEN, Suit::SPADE);
    tableFrame_.addCardToTable(Rank::SEVEN, Suit::DIAMOND);
    tableFrame_.addCardToTable(Rank::SEVEN, Suit::HEART);

    containerBox_.add(allPlayersWidget_);

    gameController_->startGame();

    show_all();

    // subscribe to updates from game model
    gameModel->subscribe(this);
}

// destructor to delete all the models and controller instances
GameView::~GameView()
{
    delete gameModel_;
    delete gameController_;
}

void GameView::onStartGameButtonClicked() {
    gameController_->resetGame();
    SeedDialogBox * seedDialog = new SeedDialogBox(*this, "Pick a seed:");
    seedDialog->popupAndUpdate();
    if(seedDialog->isSeedValid())
    {
        PlayerSetupDialogBox * playerSetupDialog = new PlayerSetupDialogBox(*this);
        std::vector<bool> arePlayersHuman = playerSetupDialog->popupAndGetPlayerStatus();
        delete playerSetupDialog;
        //Note: If isPlayerHuman is empty, the window was closed. Otherwise the i-th element signifies if player i+1 is human or if is dancer
    }
    delete seedDialog;
}

void GameView::onEndGameButtonClicked()
{
    gameController_->resetGame();
}

void GameView::onQuitButtonClicked()
{
    gameController_->processInput("quit");
}

// update the view based on the game state
void GameView::update()
{
    switch (gameModel_->getGameStatus())
    {

        // ask for input for players if in initialization stage
        case INIT_GAME:
        {
            for (unsigned int i = 0; i < NUM_PLAYERS; ++i)
            {
                allPlayersWidget_.enablePlayer(i, false);
            }
            break;
        }

        // output player's turn if starting round
        case START_ROUND:
        {
            std::stringstream ssDialog;
            std::string dialogString;
            ssDialog << "A new round begins. It\'s player " << gameModel_->getCurPlayerNum() + 1 << "\'s turn to play.";
            ssDialog >> dialogString;
            Gtk::MessageDialog scoreDialog("<big><b>" + dialogString + "</b></big>", true);
            scoreDialog.set_title("Round Start");
            scoreDialog.run();
            break;
        }

        // output table, player's hand and legal moves if starting a human player's turn
        case START_TURN:
        {
            allPlayersWidget_.enablePlayer(gameModel_->getCurPlayerNum(), !gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->isComputer());
        }

        // ask for input in a human player's turn
        case IN_TURN:
            break;

        // notify that a computer is taking over for a player if ragequitting
        case RAGEQUIT_COMMAND:
        {
            RagequitDialog rageDialog;
            rageDialog.run();
            break;
        }

        // reflect table and score changes and disable player on ending turn
        case END_TURN:
        {
            allPlayersWidget_.disablePlayer(gameModel_->getCurPlayerNum());
            if (gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->getLastMove().moveType ==
                MoveType::PLAY_CARD) {
                tableFrame_.addCardToTable(
                        gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->getLastMove().cardValue);
            }
            else {
                allPlayersWidget_.setDiscards(gameModel_->getCurPlayerNum(), gameModel_->getPlayerModel(
                        gameModel_->getCurPlayerNum())->getDiscards().size());
            }
            break;
        }

        // print discards and scores of each player to popup dialog on ending a round
        case END_ROUND:
        {
            std::string scoreString;
            std::stringstream ssScore;
            unsigned int score, discardScore;
            for (unsigned int i = 0; i < NUM_PLAYERS; ++i) {
                ssScore << "Player " << std::to_string(i + 1) << "\'s discards: ";
                for (unsigned int j = 0; j < gameModel_->getPlayerModel(i)->getDiscards().size(); ++j) {
                    if (j != 0) {
                        ssScore << " ";
                    }
                    ssScore << *(gameModel_->getPlayerModel(i)->getDiscards()[j]);
                };
                score = gameModel_->getPlayerModel(i)->getScore();
                discardScore = gameModel_->getPlayerModel(i)->getValOfDiscards();
                ssScore << std::endl << "<b>Player " << i + 1 << "\'s score: " << score << " + " << discardScore
                        << " = " << score + discardScore  << "</b>" << std::endl << std::endl;
                allPlayersWidget_.setPoints(i, score + discardScore);
            }
            ssScore >> scoreString;
            Gtk::MessageDialog scoreDialog("<big><b>" + scoreString + "</b></big>", true);
            scoreDialog.set_title("Player Scores");
            scoreDialog.run();
            break;
        }

        // print winner at the end of game to popup dialog
        case END_GAME:
        {
            std::string winString = "";
            for (unsigned int i = 0; i < gameModel_->getWinners().size(); ++i) {
                if (i != 0) {
                    winString += ", ";
                }
                winString += "Player " + gameModel_->getWinners().at(i) + 1;
            }
            winString += "win";
            if (gameModel_->getWinners().size() <= 1) {
                winString += "s";
            }
            winString += "!";
            Gtk::MessageDialog endDialog("<big><b>" + winString + "</b></big>", true);
            endDialog.set_title("Winner!");
            endDialog.run();
            break;
        }

        // close the window and exit the game
        case EXIT_GAME:
            hide();
            break;

        default:
            return;
    }
}

// print out the cards on the table sorted by the suit and the rank
void GameView::printTable() const
{
    auto table = gameModel_->getCardsOnTable();
    std::cout << "Cards on the table:" << std::endl;
    for (auto it = table->cbegin(); it != table->cend(); ++it)
    {
        // list by suit
        switch (it->first)
        {
            case (CLUB):
                std::cout << "Clubs:";
                break;
            case (DIAMOND):
                std::cout << "Diamonds:";
                break;
            case (HEART):
                std::cout << "Hearts:";
                break;
            case (SPADE):
                std::cout << "Spades:";
                break;
            default:
                return;
        }
        // sort by rank since ordered map is sorted by value
        for (auto rit = it->second.cbegin(); rit != it->second.cend(); ++rit)
        {
            std::cout << " ";
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
