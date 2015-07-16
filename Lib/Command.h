#ifndef _COMMAND_
#define _COMMAND_

#include "CardType.h"

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };     // types of commands

// input command value
class Command
{
public:
    Command(std::string commandInStringForm);                       // constructor - using string
	Command() : type_(BAD_COMMAND), cardType_(SPADE, ACE) {}        // default constructor with bad command
    Type getType() const;                                           // accessor - type of command
    CardType getCardType() const;                                   // accessor - card in command

private:
    Type type_;                                                     // type of command
	CardType cardType_;                                             // card associated with command
};

#endif
