CXX = g++
CXXFLAGS = -g -Wall -MMD -O -std=c++0x `pkg-config gtkmm-2.4 --cflags`
LDFLAGS = `pkg-config gtkmm-2.4 --libs`
OBJECTS = Models/CardType.o Models/Card.o Models/DeckModel.o Models/Command.o Models/GameModel.o Models/PlayerModel.o Models/TableModel.o Controllers/GameController.o Controllers/PlayerController.o Controllers/ComputerPlayerController.o Controllers/HumanPlayerController.o Controllers/DeckController.o Controllers/TableController.o Lib/Subject.o Views/View.o straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} ${LDFLAGS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}

