#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../Controllers/GameController.h"
#include "../Models/DeckModel.h"
#include "../Models/GameModel.h"
#include "../Models/TableModel.h"
#include "GameView.h"

// create view with required models and controllers, and subscribe to updates
GameView::GameView(GameController * gameController, GameModel * gameModel, DeckModel * deckModel,
            TableModel * tableModel) : gameModel_(gameModel), deckModel_(deckModel),
            tableModel_(tableModel), gameController_(gameController), allPlayersWidget_(gameController_, gameModel_),
            startGameButton("Start new game"), endGameButton("End game"), containerBox(false, UI_SPACING), gameButtonHBox(true, UI_SPACING)
{
    set_title("Straights");
    set_border_width(UI_SPACING);

    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();

    add( containerBox );
    containerBox.add(gameButtonHBox);

    startGameButton.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onStartGameButtonClicked ) );

    gameButtonHBox.add(startGameButton);
    gameButtonHBox.add(endGameButton);

    for(int j = 0; j < SUIT_COUNT; j++)
    {
        cardHBoxes[j] = new Gtk::HBox(true, UI_SPACING);
        for (int i = 0; i < RANK_COUNT; i++ ) {
            card[(j * RANK_COUNT) + i] = new Gtk::Image( nullCardPixbuf );
            cardHBoxes[j]->add( *card[(j * RANK_COUNT) + i] );
        }
        containerBox.add(*cardHBoxes[j]);
    }

    containerBox.add(allPlayersWidget_);

    show_all();

    // subscribe to updates from game model
    gameModel->subscribe(this);
}

// destructor to delete all the models and controller instances
GameView::~GameView()
{
    for (int i = 0; i < 52; i++ ) delete card[i];
    for(int i = 0; i < 4; i++) delete cardHBoxes[i];
    delete gameModel_;
    delete deckModel_;
    delete tableModel_;
    delete gameController_;
}

void GameView::onStartGameButtonClicked() {
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

        // print the deck if input asks for a deck
        case DECK_COMMAND:
            printDeck();
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

        default:
            return;
    }
}

// print out the deck in order
void GameView::printDeck() const
{
    auto deck = deckModel_->getCards();
    for (int i = 0; i < SUIT_COUNT; ++i)
    {
        for (int j = 0; j < RANK_COUNT; ++j)
        {
            if (j != 0) {
                std::cout << " ";
            }
            std::cout << *((*deck)[RANK_COUNT * i + j]);
        }
        std::cout << std::endl;
    }
}

// print out the cards on the table sorted by the suit and the rank
void GameView::printTable() const
{
    auto table = tableModel_->getCardsOnTable();
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
