#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include "window.h"
#include "board.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "moves.h"
#include "chessPiece.h"

 Board::Board() {
    board.resize(8, vector< ChessPiece *> (8));
    whiteKing = nullptr;
    blackKing = nullptr;
 }

void Board::setBlackPieces(ChessPiece * ptr) {
    blackPieces.emplace_back(ptr);
}

void Board::setWhitePieces(ChessPiece * ptr) {
    whitePieces.emplace_back(ptr);
}

vector<ChessPiece *> Board::getBlackPieces() {
    return blackPieces;
}

vector<ChessPiece *> Board::getWhitePieces() {
    return whitePieces;
}

ChessPiece* Board::getBlackKing() {
    return blackKing;
}

ChessPiece* Board::getWhiteKing() {
    return whiteKing;
}

void Board::setBlackKing(ChessPiece *king) {
    blackKing = king;
}

void Board::setWhiteKing(ChessPiece *king) {
    whiteKing = king;
}


Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
            }
        }
    }
 }

ChessPiece* Board::createPiece(int row, int col, char c, bool color, bool moved) {
    if (c == 'p' || c == 'P') return new Pawn(color, make_tuple(row,col), moved);
    if (c == 'r' || c == 'R') return new Rook(color, make_tuple(row,col), moved);
    if (c == 'b' || c == 'B') return new Bishop(color, make_tuple(row,col));
    if (c == 'q' || c == 'Q') return new Queen(color, make_tuple(row,col));
    if (c == 'k' || c == 'K') return new King(color, make_tuple(row,col), moved);
    if (c == 'n' || c == 'N') return new Knight(color, make_tuple(row,col));
    return nullptr;
}

Board::Board(const Board& other) {
    board.resize(8, vector< ChessPiece *> (8));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.board[i][j] == nullptr) {
                board[i][j] = nullptr;
                continue;
            } 
            board[i][j] = createPiece(i, j, other.board[i][j]->getType(), other.board[i][j]->getColor(), other.board[i][j]->getHasMoved());
            
            if (board[i][j]->getColor()) {
                setWhitePieces(board[i][j]);
            } else {
                setBlackPieces(board[i][j]);
            }

            if (board[i][j]->getType() == 'K') {
                if (board[i][j]->getColor()) {
                    whiteKing = board[i][j];
                } else {
                    blackKing = board[i][j];
                }
            }
        }
    }
}

Board &Board::operator=(const Board &other) {
    Board b = Board(other);
    return b;
} 

ChessPiece* Board::getPiece(const int row, const int col) {
    return board[row][col];
}



void Board::printText() {
            for (int i = 7; i >= 0; i--) {
                cout << (i + 1) << " ";
                for (int j = 0; j < 8; ++j) {
                    if (board[i][j] != nullptr) {
                        if (board[i][j]->getColor() == false) {
                            char piece = tolower(board[i][j]->getType());
                            cout << piece;
                            continue;
                        }
                        cout << board[i][j]->getType();
                    } else {
                        if ((i + j) % 2 == 0) {
                            cout << '_';
                        } else {
                            cout << ' ';
                        }
                    }
                }
        cout << endl;
        }
         cout << endl;
        cout << "  " << "abcdefgh" << endl;;
}

void Board::removePieceFromVector(const int row_to, const int col_to) {

    vector<ChessPiece *> enemyPiece;
    if (board[row_to][col_to]->getColor()) {
        enemyPiece = whitePieces;
    } else {
        enemyPiece = blackPieces;
    }
    int counter = 0;
    for (auto p : enemyPiece ) {
        if (p == board[row_to][col_to]) {
            enemyPiece.erase(enemyPiece.begin() + counter);
            break;
        }
        counter++;
    }
    if (board[row_to][col_to]->getColor()) {
        whitePieces = enemyPiece;
    } else {
        blackPieces = enemyPiece;
    }
}



int Board::makeMove(tuple<int,int> initial,tuple<int,int> dest) {
    int row_from = get<0>(initial);
    int col_from = get<1>(initial);
    //========================================
    int row_to = get<0>(dest);
    int col_to = get<1>(dest);
    ChessPiece *temp = board[row_from][col_from];
    ChessPiece *destination = board[row_to][col_to];
    if (!(row_from >= 0 && row_from <= 7 &&
          row_to   >= 0 && row_to   <= 7 &&
          col_from >= 0 && col_from <= 7 &&
          col_to   >= 0 && col_to   <= 7)) {
        return -3;
    }
    if (temp == nullptr) {
        return -1; // invalid move
    }
    if (destination == nullptr) {
        if (temp->getType() == 'P' && abs(row_to - row_from) == 1 && abs(col_to - col_from) == 1) {
            int colorFactor = temp->getColor() ? -1 : 1;
            removePieceFromVector(row_to + colorFactor, col_to);
            delete board[row_to + colorFactor][col_to];
            board[row_to + colorFactor][col_to] = nullptr;
        }
        board[row_to][col_to] = board[row_from][col_from];
        board[row_to][col_to]->setPosition(make_tuple(row_to, col_to));
        board[row_from][col_from] = nullptr;
        
        destination = board[row_to][col_to];
        bool checkForEnPassant = false;
        if (destination->getType() == 'P') {
            if ((abs(row_from - row_to) == 2) && (col_from - col_to == 0)) {
                checkForEnPassant = true;
                vector<ChessPiece *> enemyPieces = (destination->getColor()) ? getBlackPieces() : getWhitePieces();
                for (auto p : enemyPieces) {                       
                    if (p != nullptr && p->getType() == 'P') {
                        Pawn *enemyPawn = dynamic_cast<Pawn *>(p);
                        enemyPawn->setNoEnPassant();
                    }
                }                
            }
            if (checkForEnPassant) {
                int colorFactor = destination->getColor() ? -1 : 1;

                if ((col_to + 1 >= 0 && col_to + 1 <= 7) && 
                    board[row_to][col_to + 1] != nullptr &&
                    (board[row_to][col_to + 1])->getType() == 'P' && 
                    (board[row_to][col_to + 1])->getColor() != destination->getColor()) {
                    Pawn *enemyPawn = dynamic_cast<Pawn *>(board[row_to][col_to + 1]);
                    enemyPawn->setEnPassant(make_tuple(row_to + colorFactor, col_to));
                }
                if ( (col_to - 1 >= 0 && col_to - 1 <= 7) &&
                    board[row_to][col_to - 1] != nullptr &&
                    (board[row_to][col_to - 1])->getType() == 'P' &&
                    (board[row_to][col_to - 1])->getColor() != destination->getColor()) {
                    Pawn *enemyPawn = dynamic_cast<Pawn *>(board[row_to][col_to - 1]);
                    enemyPawn->setEnPassant(make_tuple(row_to + colorFactor, col_to));  
                } 
            }
        }
        if (temp->getType() == 'K' && abs(col_to - col_from) == 2) {
            King *king = nullptr;
            if (temp->getColor()) {
                king = dynamic_cast<King *>(getWhiteKing());
            } else {
                king = dynamic_cast<King *>(getBlackKing());
            }
            if (king->getKingSideCastle() && 
                (col_to - 1 >= 0 && col_to - 1 <= 7) && 
                (col_from + 3 >= 0 && col_from + 3 <= 7) &&
                col_to > col_from) {
                board[row_to][col_to - 1] = board[row_from][col_from + 3];
                board[row_to][col_to - 1]->setPosition(make_tuple(row_to, col_to - 1));
                board[row_from][col_from + 3] = nullptr;
            } else if (king->getQueenSideCastle() && 
                (col_to + 1 >= 0 && col_to + 1 <= 7) && 
                (col_from - 4 >= 0 && col_from - 4 <= 7) && 
                col_to < col_from) {
                board[row_to][col_to + 1] = board[row_from][col_from - 4];
                board[row_to][col_to + 1]->setPosition(make_tuple(row_to, col_to + 1));
                board[row_from][col_from - 4] = nullptr;
            }   
        }
    } else if (destination != nullptr) {
        removePieceFromVector(row_to, col_to);
        delete board[row_to][col_to];
        board[row_to][col_to] = board[row_from][col_from];
        board[row_to][col_to]->setPosition(make_tuple(row_to, col_to));
        board[row_from][col_from] = nullptr;

    }
}

bool Board::getBlackCheck() {
    King *king = dynamic_cast<King *>(blackKing);
    return king->getCheck();
}

bool Board::getWhiteCheck() {
    King *king = dynamic_cast<King *>(whiteKing);
    return king->getCheck();
}