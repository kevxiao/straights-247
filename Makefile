CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++11
OBJECTS = Models/CardType.o Models/Card.o Models/DeckModel.o Models/Command.o Models/GameModel.o Models/PlayerModel.o Models/TableModel.o Controllers/GameController.o Controllers/PlayerController.o Controllers/DeckController.o Controllers/TableController.o Lib/Subject.o Views/View.o straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}

