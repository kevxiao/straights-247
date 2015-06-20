#include "Command.h"
#include <cassert>
#include <sstream>
using namespace std;

Command::Command(std::string commandInStringForm):cardType_(SPADE, ACE)
{
	type_ = BAD_COMMAND;
	
    string cmd = commandInStringForm.substr(0, commandInStringForm.find(" "));

	if (cmd == "play" || cmd == "discard") {
	    if (cmd == "discard") {
		    type_ = DISCARD;
        }
        else
        {
            type_ = PLAY;
        }
        assert(commandInStringForm.find(" ") != std::string::npos);
		cardType_ = CardType(commandInStringForm.substr(commandInStringForm.find(" ") + 1, std::string::npos));
	} else if (commandInStringForm == "deck") {
		type_ = DECK;
	} else if (commandInStringForm == "quit") {
		type_ = QUIT;
	} else if (commandInStringForm == "ragequit") {
		type_ = RAGEQUIT;
	}

	assert(type_ != BAD_COMMAND);
}

Type Command::getType() const
{
    return type_;
}

CardType Command::getCardType() const
{
    return cardType_;
}
