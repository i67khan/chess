#include <vector>
#include <tuple>
#include "queen.h"
#include "chessPiece.h"
#include "board.h"
#include "moves.h"

using namespace std;

Queen::Queen(bool color, std::tuple<int, int> position) :
    ChessPiece{color, position, 'Q', false} {}

Queen::~Queen() {}

void Queen::setPossibleMoves(Board *board) {
    possibleMoves.clear();

    // ROOK LIKE
    for (int i = 1; i < 8; i++) {
        if (get<0>(position) + i > 7  || get<0>(position) + i < 0 ) {
            break;
        }

        auto square = board->getPiece(get<0>(position) + i, get<1>(position));

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position)), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position)), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<0>(position) - i > 7  || get<0>(position) - i < 0 ) {
            break;
        }

        auto square = board->getPiece(get<0>(position) - i, get<1>(position));

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position)), board));
            } 
            break;
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position)), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<1>(position) + i > 7  || get<1>(position) + i < 0 ) {
            break;
        }

        auto square = board->getPiece(get<0>(position), get<1>(position) + i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position), get<1>(position) + i), board));
            } 
            break;
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position), get<1>(position) + i), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<1>(position) - i > 7  || get<1>(position) - i < 0 ) {
            break;
        }

        auto square = board->getPiece(get<0>(position), get<1>(position) - i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position), get<1>(position) - i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position), get<1>(position) - i), board));
        }
    }


    // BISHOP LIKE

    for (int i = 1; i < 8; i++) {
        //checks if the postions (+moves?) is within the bounds of the board?
        if (get<0>(position) + i > 7  || get<0>(position) + i < 0 || get<1>(position) + i > 7  || get<1>(position) + i < 0) {
            break;
        }
        //retrieving each peice on the board
        auto square =  board->getPiece(get<0>(position) + i, get<1>(position) + i);
        //if there is no piece on square
        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + i), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<0>(position) + i > 7  || get<0>(position) + i < 0 || get<1>(position) - i > 7  || get<1>(position) - i < 0) {
            break;
        }

        auto square =  board->getPiece(get<0>(position) + i, get<1>(position) - i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) - i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) - i), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<0>(position) - i > 7  || get<0>(position) - i < 0 || get<1>(position) - i > 7  || get<1>(position) - i < 0) {
            break;
        }

        auto square =  board->getPiece(get<0>(position) - i, get<1>(position) - i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) - i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) - i), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<0>(position) - i > 7  || get<0>(position) - i < 0 || get<1>(position) + i > 7  || get<1>(position) + i < 0) {
            break;
        }

        auto square =  board->getPiece(get<0>(position) - i, get<1>(position) + i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) + i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) + i), board));
        }
    }

        for (int i = 1; i < 8; i++) {
        //checks if the postions (+moves?) is within the bounds of the board?
        if (get<0>(position) + i > 7  || get<0>(position) + i < 0 || get<1>(position) + i > 7  || get<1>(position) + i < 0) {
            break;
        }
        //retrieving each peice on the board
        auto square =  board->getPiece(get<0>(position) + i, get<1>(position) + i);
        //if there is no piece on square
        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + i), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<0>(position) + i > 7  || get<0>(position) + i < 0 || get<1>(position) - i > 7  || get<1>(position) - i < 0) {
            break;
        }

        auto square =  board->getPiece(get<0>(position) + i, get<1>(position) - i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) - i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) - i), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<0>(position) - i > 7  || get<0>(position) - i < 0 || get<1>(position) - i > 7  || get<1>(position) - i < 0) {
            break;
        }

        auto square =  board->getPiece(get<0>(position) - i, get<1>(position) - i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) - i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) - i), board));
        }
    }

    for (int i = 1; i < 8; i++) {
        if (get<0>(position) - i > 7  || get<0>(position) - i < 0 || get<1>(position) + i > 7  || get<1>(position) + i < 0) {
            break;
        }

        auto square =  board->getPiece(get<0>(position) - i, get<1>(position) + i);

        if (square != nullptr) {
            if (square->getColor() != color) {
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) + i), board));
            } 
            break;
            
        } else {
            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) - i, get<1>(position) + i), board));
        }
    }

    checkForCheck();
}
