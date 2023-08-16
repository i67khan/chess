#include <vector>
#include <memory>
#include <tuple>
#include <algorithm>
#include "king.h"
#include "chessPiece.h"
#include "board.h"
#include "moves.h"
#include "rook.h"

using namespace std;

King::King(bool color, std::tuple<int, int> position, bool hasMoved) :
    ChessPiece{color, position, 'K', hasMoved} {
    if (hasMoved == false) {
        if (color) {
            if (get<0>(position) != 0 || get<1>(position) != 4) {
                this->hasMoved = true;
            }
        } else if (!color) {
            if (get<0>(position) != 7 || get<1>(position) != 4) {
                this->hasMoved = true;
            }
        }
    }
}

King::~King() {}

void King::setPossibleMoves(Board *board) {
    possibleMoves.clear();

    if (color && hasMoved == false) {
        if (get<0>(position) != 0 || get<1>(position) != 4) {
            hasMoved = true;
        }
    } else if (!color && hasMoved == false) {
        if (get<0>(position) != 7 || get<1>(position) != 4) {
            hasMoved = true;
        }
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if  (i == 0  && j == 0) {
                continue;
            }

            if (get<0>(position) + i > 7  || get<0>(position) + i < 0  || get<1>(position) + j > 7  || get<1>(position) + j < 0) {
                continue;
            }

            auto square = board->getPiece(get<0>(position) + i, get<1>(position) + j);

            if (square != nullptr) {
                if (square->getColor() != color) {
                    possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + j), board));
                } 
                continue;
                
            } else {
                
                possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position) + i, get<1>(position) + j), board));
            }
            
        }
    }
    
    kingSideCastle = false;
    queenSideCastle = false;
    if (!hasMoved && !checked) {
        tuple<int, int> initailSquare;
        vector<ChessPiece*> enemyPieces;
        if (color) {
            initailSquare = make_tuple(0, 4);
            enemyPieces = board->getBlackPieces();
        } else {
            initailSquare = make_tuple(7, 4);
            enemyPieces = board->getWhitePieces();
        }

        if (position == initailSquare) {
            if (board->getPiece(get<0>(initailSquare), 5) == nullptr && board->getPiece(get<0>(initailSquare), 6) == nullptr) {
                bool isCovered = false;
                for (auto i: enemyPieces) {
                    if (i == nullptr) {
                        continue;
                    }
                    
                    for (int j = 5; j <= 6; j++) {
                        vector<tuple<int,int>> finalPositions;
                        for (auto enemyMoves: i->getPossibleMoves()) {
                            finalPositions.emplace_back(enemyMoves.getFinalPosition());
                        }
                        if (find(finalPositions.begin(),finalPositions.end(), make_tuple(get<0>(initailSquare), j)) != finalPositions.end()) {
                            isCovered = true;
                            break;
                        }
                    }
                }
                if (!isCovered) {
                    auto kingSideRook = board->getPiece(get<0>(initailSquare), 7);
                    if (kingSideRook != nullptr &&  kingSideRook->getColor() == color && kingSideRook->getType() == 'R') {
                        if (kingSideRook->getHasMoved() == false) {
                            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position), get<1>(position) + 2), board));
                            kingSideCastle = true;
                        }
                    }
                }
            }
            if (board->getPiece(get<0>(initailSquare), 1) == nullptr && 
                board->getPiece(get<0>(initailSquare), 2) == nullptr &&
                board->getPiece(get<0>(initailSquare), 3) == nullptr) {
                bool isCovered = false;
                for (auto i: enemyPieces) {
                    if (i == nullptr) {
                        continue;
                    }
                    for (int j = 1; j <= 3; j++) {
                        vector<tuple<int,int>> finalPositions;
                        for (auto enemyMoves: i->getPossibleMoves()) {
                            finalPositions.emplace_back(enemyMoves.getFinalPosition());
                        }
                        if (find(finalPositions.begin(),finalPositions.end(), make_tuple(get<0>(initailSquare), j)) != finalPositions.end()) {
                            isCovered = true;
                            break;
                        }
                    }
                }
                
                if (!isCovered) {
                    auto queenSideRook = board->getPiece(get<0>(initailSquare), 0);
                    if (queenSideRook != nullptr &&  queenSideRook->getColor() == color && queenSideRook->getType() == 'R') {
                        if (queenSideRook->getHasMoved() == false) {
                            possibleMoves.emplace_back(Moves(position, make_tuple(get<0>(position), get<1>(position) - 2), board));
                            queenSideCastle = true;
                        }
                    }
                }
            }

        }
    }
    

    checkForCheck();
}


void King::checkKing() {
    checked = true;
}

void King::uncheckKing() {
    checked = false;
}

bool King::getCheck() const {
    return checked;
}

bool King::getKingSideCastle() const {
    return kingSideCastle;
}

bool King::getQueenSideCastle() const {
    return queenSideCastle;
}