#include "Command.h"
#include <cassert>
#include <sstream>
using namespace std;

// create command out of a string
Command::Command(std::string commandInStringForm):cardType_(SPADE, ACE)
{
	type_ = BAD_COMMAND;

    // split string into the command and the card type
    string cmd = commandInStringForm.substr(0, commandInStringForm.find(" "));

    // process each command string
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
	} else if (commandInStringForm == "quit") {
		type_ = QUIT;
	} else if (commandInStringForm == "ragequit") {
		type_ = RAGEQUIT;
	}

	assert(type_ != BAD_COMMAND);
}

// create command out of a Type and CardType
Command::Command(Type commandType, CardType card): type_(commandType), cardType_(card)
{
}

// get the command type
Type Command::getType() const
{
    return type_;
}

// get the card type associated with the command
CardType Command::getCardType() const
{
    return cardType_;
}
