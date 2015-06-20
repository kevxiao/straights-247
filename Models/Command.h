#ifndef _COMMAND_
#define _COMMAND_

#include "CardType.h"

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

class Command
{
public:
    Command(std::string commandInStringForm);
	Command() : type_(BAD_COMMAND), cardType_(SPADE, ACE) {}
    Type getType() const;
    CardType getCardType() const;

private:
    Type type_;
	CardType cardType_;
};

#endif
