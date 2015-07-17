CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++0x `pkg-config gtkmm-2.4 --cflags`
LDFLAGS = `pkg-config gtkmm-2.4 --libs`
OBJECTS = Models/CardModel.o Models/DeckModel.o Models/GameModel.o Models/PlayerModel.o Models/TableModel.o Controllers/GameController.o Controllers/PlayerController.o Controllers/ComputerPlayerController.o Controllers/HumanPlayerController.o Controllers/DeckController.o Controllers/TableController.o Lib/Subject.o Lib/CardType.o Lib/Command.o Views/DeckGUI.o Views/HandFrame.o Views/TableFrame.o Views/PlayerSetupFrame.o Views/PlayerSetupDialogBox.o Views/SeedDialogBox.o Views/RagequitDialog.o Views/DiscardsDialog.o Views/GameView.o Views/AllPlayersWidget.o Views/PlayerWidget.o straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} ${LDFLAGS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}

