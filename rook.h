#ifndef ROOK_H
#define ROOK_H

#include "chessPiece.h"

/**
 * A class representing the rook chess piece.
 **/

class Rook:public ChessPiece {
    public:
        // Constructor.
        Rook(bool color, std::tuple<int, int> position, bool moved);
        // Destructor.
        ~Rook();
        // Possible moves setter.
        void setPossibleMoves(Board *board);
};

#endif
