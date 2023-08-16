#ifndef PAWN_H
#define PAWN_H

#include "chessPiece.h"

/**
 * A class representing the Pawn chess piece.
 **/

class Pawn: public ChessPiece {
        bool enPassant; // Can the piece do en Passant. 
        std::tuple<int, int> enPassantPosition; 
    public:
        // Constructor.
        Pawn(bool color, std::tuple<int, int> position, bool hasMoved);
        // Destructor.
        ~Pawn();
        // Possible moves setter.
        void setPossibleMoves(Board *board);
        // en-passant setter.
        void setEnPassant(std::tuple<int, int> to);
        // en-passant setter to false.
        void setNoEnPassant();
};

#endif
