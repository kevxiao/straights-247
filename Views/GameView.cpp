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

    containerBox_.add(allPlayersWidget_);

    show_all();

    // subscribe to updates from game model
    gameModel->subscribe(this);
    gameController_->startGame();
}

// destructor to delete all the models and controller instances
GameView::~GameView()
{
    delete gameModel_;
    delete gameController_;
}

void GameView::onStartGameButtonClicked()
{
    SeedDialogBox * seedDialog = new SeedDialogBox(*this, "Pick a seed:");
    std::vector<bool> arePlayersHuman;
    seedDialog->popupAndUpdate();
    if(seedDialog->isSeedValid())
    {
        unsigned long seedValue = seedDialog->getSeedValue();
        delete seedDialog;
        PlayerSetupDialogBox * playerSetupDialog = new PlayerSetupDialogBox(*this);
        arePlayersHuman = playerSetupDialog->popupAndGetPlayerStatus();
        delete playerSetupDialog;
        if (!arePlayersHuman.empty())
        {
            gameController_->resetGame(seedValue);
            for(unsigned int i = 0; i < arePlayersHuman.size(); ++i)
            {
                gameController_->processInput(arePlayersHuman.at(i) ? "h" : "c");
            }
        }
        //Note: If isPlayerHuman is empty, the window was closed. Otherwise the i-th element signifies if player i+1 is human or if is dancer
    }
    else
    {
        delete seedDialog;
    }
}

void GameView::onEndGameButtonClicked()
{
    gameController_->resetGame();
    for (unsigned int i = 0; i < NUM_PLAYERS; ++i)
    {
        allPlayersWidget_.resetPlayer(i);
    }
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
            for (unsigned int i = 0; i < NUM_PLAYERS; ++i)
            {
                allPlayersWidget_.setType(i, !gameModel_->getPlayerModel(i)->isComputer());
                allPlayersWidget_.disablePlayer(i);
            }
            std::string dialogString = "A new round begins.";
            Gtk::MessageDialog scoreDialog("<big><b>" + dialogString + "</b></big>", true);
            scoreDialog.set_secondary_text("It\'s player " + std::to_string(gameModel_->getCurPlayerNum() + 1) + "\'s turn to play.");
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
            std::string scoreString = "", tempStr;
            std::stringstream ssScore;
            unsigned int score, discardScore;
            for (unsigned int i = 0; i < NUM_PLAYERS; ++i) {
                scoreString += "Player " + std::to_string(i + 1) + "\'s discards: ";
                for (unsigned int j = 0; j < gameModel_->getPlayerModel(i)->getDiscards().size(); ++j) {
                    if (j != 0) {
                        scoreString += " ";
                    }
                    ssScore << *(gameModel_->getPlayerModel(i)->getDiscards()[j]);
                    ssScore >> tempStr;
                    scoreString += tempStr;
                    ssScore.str("");
                    ssScore.clear();
                };
                score = gameModel_->getPlayerModel(i)->getScore();
                discardScore = gameModel_->getPlayerModel(i)->getValOfDiscards();
                scoreString += "\n<b>Player " + std::to_string(i + 1) + "\'s score: " + std::to_string(score) + " + " + std::to_string(discardScore)
                        + " = " + std::to_string(score + discardScore) + "</b>\n\n";
                allPlayersWidget_.setPoints(i, score + discardScore);
            }
            Gtk::MessageDialog scoreDialog("<big><b>" + scoreString + "</b></big>", true);
            scoreDialog.set_title("Player Scores");
            scoreDialog.run();
            tableFrame_.resetTable();
            for(unsigned int i = 0; i < NUM_PLAYERS; ++i)
            {
                allPlayersWidget_.setDiscards(i, 0);
            }
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
                winString += "Player " + std::to_string(gameModel_->getWinners().at(i) + 1);
            }
            winString += " win";
            if (gameModel_->getWinners().size() <= 1) {
                winString += "s";
            }
            winString += "!";
            Gtk::MessageDialog endDialog("<big><b>" + winString + "</b></big>", true);
            endDialog.set_title("Winner!");
            endDialog.run();
            for(unsigned int i = 0; i < NUM_PLAYERS; ++i)
            {
                allPlayersWidget_.resetPlayer(i);
            }
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
