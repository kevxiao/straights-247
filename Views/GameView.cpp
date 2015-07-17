#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../Controllers/GameController.h"
#include "../Models/GameModel.h"
#include "GameView.h"

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
            std::string input;
            std::cout << "Is player " << gameModel_->getCurPlayerNum() + 1 << " a human(h) or a computer(c)?" << std::endl<<">";
            std::getline(std::cin, input);
            gameController_->processInput(input);
            break;
        }

        // output player's turn if starting round
        case START_ROUND:
            std::cout << "A new round begins. It\'s player " << gameModel_->getCurPlayerNum() + 1 << "\'s turn to play." << std::endl;
            break;

        // output table, player's hand and legal moves if starting a human player's turn
        case START_TURN:
        {
            std::shared_ptr<PlayerModel> curPlayer = gameModel_->getPlayerModel(gameModel_->getCurPlayerNum());
            if (!curPlayer->isComputer())
            {
                printTable();
                std::cout << "Your hand:";
                for(unsigned int counter = 0; counter < curPlayer->getHand().size(); counter++)
                {
                    std::cout<<" "<<*(curPlayer->getHand().at(counter));
                }
                std::cout<<std::endl;

                std::cout << "Legal plays:";
                for(unsigned int counter = 0; counter < curPlayer->getLegalMoves().size(); counter++)
                {
                    std::cout<<" "<<curPlayer->getLegalMoves().at(counter);
                }
                std::cout<<std::endl;
            }
            break;
        }

        // ask for input in a human player's turn
        case IN_TURN:
            if (!gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->isComputer())
            {
                std::string player_input;
                std::cout<<">";
                std::getline(std::cin, player_input);
                try 
                {
                    gameController_->processInput(player_input);
                }
                catch (HumanPlayerController::InvalidPlayException invalidPlayEx) 
                {
                    std::cout << "This is not a legal play." << std::endl;
                    update();
                } 
                catch (HumanPlayerController::InvalidDiscardException invalidDiscardEx) 
                {
                    std::cout << "You have a legal play. You may not discard." << std::endl;
                    update();
                }
            }
            break;

        // notify that a computer is taking over for a player if ragequitting
        case RAGEQUIT_COMMAND:
            std::cout << "Player " << gameModel_->getCurPlayerNum() + 1 << " ragequits. A computer will now take over." << std::endl;
            break;

        // print out the move of the player when ending a turn
        case END_TURN:
            std::cout << "Player " << gameModel_->getCurPlayerNum() + 1 << " ";
            if(gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->getLastMove().moveType == MoveType::PLAY_CARD)
            {
                std::cout << "plays ";
            }
            else
            {
                std::cout << "discards ";
            }
            std::cout << gameModel_->getPlayerModel(gameModel_->getCurPlayerNum())->getLastMove().cardValue << "." << std::endl;
            break;

        // print discards and scores of each player on ending a round
        case END_ROUND:
            unsigned int score, discardScore;
            for (unsigned int i = 0; i < NUM_PLAYERS; ++i)
            {
                std::cout << "Player " << i + 1 << "\'s discards: ";
                for (unsigned int j = 0; j < gameModel_->getPlayerModel(i)->getDiscards().size(); ++j)
                {
                    if (j != 0) {
                        std::cout << " ";
                    }
                    std::cout << *(gameModel_->getPlayerModel(i)->getDiscards()[j]);
                };
                score = gameModel_->getPlayerModel(i)->getScore();
                discardScore = gameModel_->getPlayerModel(i)->getValOfDiscards();
                std::cout << std::endl << "Player " << i + 1 << "\'s score: " << score << " + " << discardScore << " = " << score + discardScore << std::endl;
            }
            break;

        // print winner at the end of game
        case END_GAME:
            for (unsigned int i = 0; i < gameModel_->getWinners().size(); ++i)
            {
                std::cout << "Player " << gameModel_->getWinners().at(i) + 1 << " wins!" << std::endl;
            }
            break;

        case EXIT_GAME:
            hide();

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
