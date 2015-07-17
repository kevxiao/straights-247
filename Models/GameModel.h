#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <queue>

#include "PlayerModel.h"
#include "../Lib/Subject.h"
#include "../Lib/Constants.h"
#include "TableModel.h"
#include "DeckModel.h"

// all the game status needed
enum GameStatus {INIT_GAME, START_ROUND, START_TURN, IN_TURN, RAGEQUIT_COMMAND, END_TURN, END_ROUND, END_GAME, EXIT_GAME, STATUS_COUNT};

// model of the game entity
class GameModel: public Subject
{
public:
    GameModel(TableModel *, DeckModel *);                                                       // constructor
    ~GameModel();                                                                               // destructor
    GameStatus getGameStatus() const;                                                           // accessor - get the status
    void setGameStatus(GameStatus newGameStatus);                                               // mutator - set a specific status
    void addPlayer(std::shared_ptr<PlayerModel> playerToAdd);                                   // mutator - add player the game
    std::shared_ptr<PlayerModel> getPlayerModel(unsigned int playerNum) const;                  // accessor - get a player model
    unsigned int getCurPlayerNum() const;                                                       // accessor - get the current player
    void setCurPlayerNum(unsigned int newPlayerNum);                                            // mutator - set the current player
    void incrementCurPlayerNum();                                                               // mutator - move to next player
    void setWinners(std::vector<unsigned int>);                                                 // mutator - set the winning player(s)
    std::vector<unsigned int> getWinners() const;                                               // accessor - get the winning player(s)
    void clearPlayers();                                                                        // mutator - delete all the players
    void resetTable();                                                                          // mutator - clear cards on table
    void addCardToTable(std::shared_ptr<Card> cardToAdd);                                       // mutator - add one card to table
    const std::map<Suit, std::map<Rank, std::shared_ptr<Card> > > * getCardsOnTable() const;    // accessor - get the list of cards on table
    void shuffle(unsigned long);                                                                // mutator - shuffle order of cards
    const std::vector<std::shared_ptr<Card> > * getCards() const;                               // accessor - get the cards in the deck in order
    void resetDeck();                                                                           // mutator - reset the deck to the original state

private:
    TableModel * tableModel_;
    DeckModel * deckModel_;
    GameStatus gameStatus_;                                                         // current status of the game
    unsigned int curPlayerNum_;                                                     // current player's turn
    std::vector<std::shared_ptr<PlayerModel> > players_;                            // list of pointers to the players in the game
    std::vector<unsigned int> winners_;                                             // list of winnders
};

#endif
