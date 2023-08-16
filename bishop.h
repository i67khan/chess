#ifndef BISHOP_H
#define BISHOP_H

#include "chessPiece.h"
#include <tuple>

/**
 * A class representing the rook chess piece.
 **/

class Bishop: public ChessPiece {
    public:
        // Constructor.
        Bishop(bool color, std::tuple<int, int> position);
        // Destructor.
        ~Bishop();
        // Possible moves setter.
        void setPossibleMoves(Board *board);
};

#endif
