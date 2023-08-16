#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <memory>
#include <tuple>
#include <vector>
#include "board.h"

class Moves;

/**
 * A class representing a chess piece.
 **/
class ChessPiece {
    protected:
        std::tuple<int, int> position; // position.
        bool color; // piece color (white is true, black is false).
        char type; // type of piece. One of Pawn (P) Rook (R) Bishop (B) Knight (N) Queen (Q) King (K).
        bool hasMoved; // Bool if the piece has moved (Primary use for rook, king, and pawn).
        std::vector<Moves> possibleMoves; // Vector of all possible moves made by piece.
        std::vector<Moves> legalMoves; // Vector of all legal moves possible by piece.
    public:
        // Constructor.
        ChessPiece(bool color, std::tuple<int, int> position, char type, bool hasMoved);
        // Destructor.
        virtual ~ChessPiece();
        // Color getter.
        bool getColor();
        // Type getter.
        char getType();
        // Has moved getter.
        bool getHasMoved();
        // Position getter.
        std::tuple<int, int> getPosition() const;
        // Position Setter.
        void setPosition(std::tuple<int, int> newPosition);
        // Possible moves setter.
        virtual void setPossibleMoves(Board *board) = 0;
        // Legal moves setter.
        void setLegalMoves();
        // Checks if any of the possibleMoves checks the enemy king.
        void checkForCheck();
        //Get legal moves
        std::vector<Moves> getLegalMoves() const;
        //Get legal moves
        std::vector<Moves> getPossibleMoves() const;
};

#endif
