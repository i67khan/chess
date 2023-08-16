#ifndef KING_H
#define KING_H

#include "chessPiece.h"

/**
 * A class representing the king chess piece.
 **/

class King:public ChessPiece {
        bool checked = false; // is this piece checked.
        bool kingSideCastle = false; // if the king can king side castle.
        bool queenSideCastle =  false; // if the king can queen side castle.
    public:
        // Constructor.
        King(bool color, std::tuple<int, int> position, bool hasMoved);
        // Destructor.
        ~King();
        // Possible moves setter.
        void setPossibleMoves(Board *board);
        // Checked setter to true.
        void checkKing();
        // Checked setter to false.
        void uncheckKing();
        // Checked getter.
        bool getCheck() const;
        // King side castle getter.
        bool getKingSideCastle() const;        
        // Queen side castle getter.
        bool getQueenSideCastle() const;
};

#endif
