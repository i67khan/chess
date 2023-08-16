CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla -lX11
EXEC = chess
OBJECTS = main.o window.o board.o game.o computerPlayer.o chessPiece.o moves.o bishop.o rook.o queen.o knight.o pawn.o king.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
