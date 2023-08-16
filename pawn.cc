#include <vector>
#include <tuple>
#include "pawn.h"
#include "chessPiece.h"
#include "board.h"
#include "moves.h"

using namespace std;

Pawn::Pawn(bool color, std::tuple<int, int> position, bool hasMoved) : 
    ChessPiece{color, position, 'P', hasMoved}, enPassant{false} {
    if (hasMoved == false) {
        if (color && get<0>(position) != 1) {
            this->hasMoved = true;
        } else if (!color && get<0>(position) != 6) {
            this->hasMoved = true;
        }
    }
}

Pawn::~Pawn() {}

void Pawn::setEnPassant(std::tuple<int, int> to) {
    enPassantPosition = to;
    enPassant = true;
}

void Pawn::setNoEnPassant() {
    enPassant = false;
}

void Pawn::setPossibleMoves(Board *board) {
    possibleMoves.clear();

    if (enPassant) {
        possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(enPassantPosition), get<1>(enPassantPosition)), board));
    }

    if (color && get<0>(position) != 1) {
        hasMoved = true;
    } else if (!color && get<0>(position) != 6) {
        hasMoved = true;
    }
    
    int movesAhead = 1;

    int colorFactor;
    if  (color) {
        colorFactor = 1;
    } else {
        colorFactor = -1;
    }

    if (!hasMoved) {
        movesAhead = 2;
    }


    for (int i = 1; i <= movesAhead; i++) {
        if (get<0>(position) + i * colorFactor > 7  || get<0>(position) + i * colorFactor < 0 ) {
            break;
        }

        auto square = board->getPiece(get<0>(position) + i * colorFactor, get<1>(position));

        if (square != nullptr) {
            break;
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i * colorFactor, get<1>(position)), board));
        }
    }

    for (int i = -1; i <= 1; i++) {
        if (i == 0) {
            continue;
        }

        if (get<0>(position) + colorFactor > 7  || get<0>(position) + colorFactor < 0  || get<1>(position) + i > 7  || get<1>(position) + i < 0) {
            continue;
        }

        auto square = board->getPiece(get<0>(position) + colorFactor, get<1>(position) + i);

        if (square != nullptr && square->getColor() != color) {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + colorFactor, get<1>(position) + i), board));
        } 
    }

    checkForCheck();
}
