#ifndef _COMMAND_
#define _COMMAND_

#include "CardType.h"
#include <istream>

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command{
	Type type;
	CardType cardType;
	
	Command() : type(BAD_COMMAND), cardType(SPADE, ACE) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif
