#ifndef KNIGHT_H
#define KNIGHT_H

#include "chessPiece.h"

/**
 * A class representing the queen chess piece.
 **/

class Knight:public ChessPiece {
    public:
        // Constructor.
        Knight(bool color, std::tuple<int, int> position);
        // Destructor.
        ~Knight();
        // Possible moves setter.
        void setPossibleMoves(Board *board);
};

#endif
