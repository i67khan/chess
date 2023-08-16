#include <vector>
#include <tuple>
#include "knight.h"
#include "chessPiece.h"
#include "board.h"
#include "moves.h"
using namespace std;

Knight::Knight(bool color, std::tuple<int, int> position) : 
    ChessPiece{color, position, 'N', false} {}

Knight::~Knight() {}

void Knight::setPossibleMoves(Board *board) {
    possibleMoves.clear();

    
    for (int i = -2; i<= 2; i+= 4) {
        for (int j = -1; j <= 1; j+= 2) {
            if (!(get<0>(position) + i > 7  || get<0>(position) + i < 0  || get<1>(position) + j > 7  || get<1>(position) + j < 0)) {

                auto square =  board->getPiece(get<0>(position) + i, get<1>(position) + j);

                if (square != nullptr) {
                    if (square->getColor() != color) {
                        possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + j), board));
                    } 
                    
                } else {
                    possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + j), board));
                }
            }
        }
    }

    for (int i = -1; i<= 1; i+= 2) {
        for (int j = -2; j <= 2; j+= 4) {
            if (!(get<0>(position) + i > 7  || get<0>(position) + i < 0  || get<1>(position) + j > 7  || get<1>(position) + j < 0)) {

                auto square =  board->getPiece(get<0>(position) + i, get<1>(position) + j);

                if (square != nullptr) {
                    if (square->getColor() != color) {
                        possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + j), board));
                    } 
                    
                } else {
                    possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + j), board));
                }
            }
        }
    }
    
    checkForCheck();
}
