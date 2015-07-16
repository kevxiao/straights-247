#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <queue>

#include "PlayerModel.h"
#include "../Lib/Subject.h"
#include "../Lib/Constants.h"

// all the game status needed
enum GameStatus {INIT_GAME, START_ROUND, START_TURN, IN_TURN, DECK_COMMAND, RAGEQUIT_COMMAND, END_TURN, END_ROUND, END_GAME, EXIT_GAME, STATUS_COUNT};

// model of the game entity
class GameModel: public Subject
{
public:
    GameModel();                                                                    // constructor
    ~GameModel();                                                                   // destructor
    GameStatus getGameStatus() const;                                               // accessor - get the status
    void setGameStatus(GameStatus newGameStatus);                                   // mutator - set a specific status
    void addPlayer(std::shared_ptr<PlayerModel> playerToAdd);                       // mutator - add player the game
    std::shared_ptr<PlayerModel> getPlayerModel(unsigned int playerNum) const;      // accessor - get a player model
    unsigned int getCurPlayerNum() const;                                           // accessor - get the current player
    void setCurPlayerNum(unsigned int newPlayerNum);                                // mutator - set the current player
    unsigned int getNumPlayers() const;                                             // accessor - get a constant number of players for this game
    void incrementCurPlayerNum();                                                   // mutator - move to next player
    void setWinners(std::vector<unsigned int>);                                     // mutator - set the winning player(s)
    std::vector<unsigned int> getWinners() const;                                   // accessor - get the winning player(s)

private:
    GameStatus gameStatus_;                                                         // current status of the game
    unsigned int curPlayerNum_;                                                     // current player's turn
    std::vector<std::shared_ptr<PlayerModel> > players_;                            // list of pointers to the players in the game
    std::vector<unsigned int> winners_;                                             // list of winnders
};

#endif
