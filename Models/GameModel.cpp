#include "GameModel.h"

// constructor for game model
GameModel::GameModel(TableModel * tableModel, DeckModel * deckModel) : tableModel_(tableModel),
        deckModel_(deckModel), gameStatus_(INIT_GAME)
{
}

// default destructor
GameModel::~GameModel() 
{
    delete tableModel_;
    delete deckModel_;
}

// get the game status
GameStatus GameModel::getGameStatus() const 
{
    return gameStatus_;
}

// set the game status and notify observers when new status is set
void GameModel::setGameStatus(GameStatus newGameStatus) 
{
    gameStatus_ = newGameStatus;
    notify();
}

// add a player to the game
void GameModel::addPlayer(std::shared_ptr<PlayerModel> playerToAdd) 
{
    players_.push_back(playerToAdd);
}

// get a player using the identifier
std::shared_ptr<PlayerModel> GameModel::getPlayerModel(unsigned int playerNum) const
{
    std::shared_ptr<PlayerModel> selectedModel = nullptr;
    for(unsigned int counter = 0; counter < players_.size(); counter++)
    {
        if(players_.at(counter)->getPlayerNum() == playerNum)
        {
            selectedModel = players_.at(counter);
        }
    }
    return selectedModel;
}

// get the player whose turn it is
unsigned int GameModel::getCurPlayerNum() const
{
    return curPlayerNum_;
}

// set the player whose turn it will be
void GameModel::setCurPlayerNum(unsigned int newPlayerNum)
{
    curPlayerNum_ = newPlayerNum;
}

// increment and rotate through current players
void GameModel::incrementCurPlayerNum()
{
    ++curPlayerNum_;
    curPlayerNum_ = curPlayerNum_ % NUM_PLAYERS;
}

// set the winners of the game
void GameModel::setWinners(std::vector<unsigned int> winners)
{
    winners_ = winners;
}

// get the list of winners
std::vector<unsigned int> GameModel::getWinners() const
{
    return winners_;
}

// clear all cards from the table
void GameModel::resetTable()
{
    tableModel_->resetTable();
}

// add a card to the table
void GameModel::addCardToTable(std::shared_ptr<Card> cardToAdd)
{
    tableModel_->addCardToTable(cardToAdd);
}

// get all the cards on the table
const std::map<Suit, std::map<Rank, std::shared_ptr<Card> > > * GameModel::getCardsOnTable() const
{
    return tableModel_->getCardsOnTable();
}

// shuffle cards in deck using the seed
void GameModel::shuffle(unsigned long seed)
{
    deckModel_->shuffle(seed);
}

// get the list of cards in the deck in order
const std::vector<std::shared_ptr<Card> > * GameModel::getCards() const
{
    return deckModel_->getCards();
}

// reset cards in deck to original ordered state
void GameModel::resetDeck()
{
    deckModel_->reset();
}