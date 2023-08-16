#ifndef MOVES_H
#define MOVES_H

#include <memory>
#include <tuple>


class Board;

/**
 * A class representing a Move in chess.
 **/
class Moves {
        std::tuple<int, int> initialPosition; // Initial position on board
        std::tuple<int, int> finalPosition; // Final position on board
        Board* board; // Vector of all legal moves possible by piece.
    public: 
        // Constructor.
        Moves(std::tuple<int, int> initialPosition, std::tuple<int, int> finalPosition, Board *board);
        // Destructor.
        ~Moves();
        // Equality operator.
        bool operator==(const Moves &rhs);
        // Initial position getter.
        std::tuple<int, int> getInitialPosition();
        // Final position getter.
        std::tuple<int, int> getFinalPosition();
        // Board getter.
        Board *getBoard();
};

#endif
