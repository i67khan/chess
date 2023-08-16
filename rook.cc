#include <vector>
#include <tuple>
#include "rook.h"
#include "chessPiece.h"
#include "board.h"
#include "moves.h"
using namespace std;

Rook::Rook(bool color, std::tuple<int, int> position, bool hasMoved): 
    ChessPiece{color, position, 'R', hasMoved} {
    if (!hasMoved) {
        if (color) {
            if (get<0>(position) != 0 && get<1>(position) != 0 && get<1>(position) != 7) {
                this->hasMoved = true;
            }
        } else {
            if (get<0>(position) != 7 && get<1>(position) != 0 && get<1>(position) != 7) {
                this->hasMoved = true;
            }
        }
    }
}

Rook::~Rook() {}

void Rook::setPossibleMoves(Board *board) {
    possibleMoves.clear();

    if (!hasMoved) {
        if (color) {
            if (get<0>(position) != 0 && get<1>(position) != 0 && get<1>(position) != 7) {
                this->hasMoved = true;
            }
        } else {
            if (get<0>(position) != 7 && get<1>(position) != 0 && get<1>(position) != 7) {
                this->hasMoved = true;
            }
        }
    }

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
    checkForCheck();
}
