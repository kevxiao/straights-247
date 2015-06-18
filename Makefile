CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++11
OBJECTS = Models/CardType.o Models/Card.o Models/DeckModel.o Controllers/DeckController.o Models/Command.o Lib/Subject.o straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}

