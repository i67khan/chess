#ifndef QUEEN_H
#define QUEEN_H

#include "chessPiece.h"

/**
 * A class representing the queen chess piece.
 **/

class Queen:public ChessPiece {
    public:
        // Constructor.
        Queen(bool color, std::tuple<int, int> position);
        // Destructor.
        ~Queen();
        // Possible moves setter.
        void setPossibleMoves(Board *board);
};

#endif
