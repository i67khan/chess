#include <iostream>
#include <vector>
#include <ctype.h>
#include <tuple>
#include "game.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "moves.h"
#include "chessPiece.h"

using namespace std;

Game::Game() {
    chessBoard = new Board();
}

Game::~Game(){
    delete chessBoard;
}

        
void Game::initGame() {
    chessBoard->board[7][0] = chessBoard->createPiece(7,0,'r',false, false);
    chessBoard->board[7][1] = chessBoard->createPiece(7,1,'n',false, false);
    chessBoard->board[7][2] = chessBoard->createPiece(7,2,'b',false, false);
    chessBoard->board[7][3] = chessBoard->createPiece(7,3,'q',false, false);
    chessBoard->board[7][4] = chessBoard->createPiece(7,4,'k',false, false);
    chessBoard->board[7][5] = chessBoard->createPiece(7,5,'b',false, false);
    chessBoard->board[7][6] = chessBoard->createPiece(7,6,'n',false, false);
    chessBoard->board[7][7] = chessBoard->createPiece(7,7,'r',false, false);

    chessBoard->setBlackKing(chessBoard->board[7][4]);
    //==========================================
    for (int i = 0; i < 8; ++i) {
        chessBoard->board[6][i] = chessBoard->createPiece(6,i,'p',false, false);
        chessBoard->board[1][i] = chessBoard->createPiece(1,i,'P',true, false);
        
        chessBoard->setBlackPieces(chessBoard->board[6][i]); // (p,p,p,p,p,p,p,p)
        chessBoard->setBlackPieces(chessBoard->board[7][i]); // (p,p,p,p,p,p,p,p,r,n,b,q,k,b,n,r)

        chessBoard->setWhitePieces(chessBoard->board[1][i]); // (P,P,P,P,P,P,P,P)
    }
    //==========================================
    for (int i = 2; i < 6; ++i) {
        for (int j =0; j < 8; ++j) {
            chessBoard->board[i][j] = nullptr;
        }
    }
    //==========================================
    chessBoard->board[0][0] = chessBoard->createPiece(0,0,'R',true, false);
    chessBoard->board[0][1] = chessBoard->createPiece(0,1,'N',true, false);
    chessBoard->board[0][2] = chessBoard->createPiece(0,2,'B',true, false);
    chessBoard->board[0][3] = chessBoard->createPiece(0,3,'Q',true, false);
    chessBoard->board[0][4] = chessBoard->createPiece(0,4,'K',true, false);
    chessBoard->board[0][5] = chessBoard->createPiece(0,5,'B',true, false);
    chessBoard->board[0][6] = chessBoard->createPiece(0,6,'N',true, false);
    chessBoard->board[0][7] = chessBoard->createPiece(0,7,'R',true, false);

    chessBoard->setWhiteKing(chessBoard->board[0][4]);

    for (int i = 0; i < 8; ++i) {
        chessBoard->setWhitePieces(chessBoard->board[0][i]); //(P,P,P,P,P,P,P,P,R,N,B,Q,K,B,N,R)
    }
    printGraphics();
    chessBoard->printText();
}

void Game::setupGame(char oper, char type, tuple<int,int> pos) {
    int row = get<0>(pos);
    int col = get<1>(pos);
    bool turn = false;
    int val = type;
    if (val >= 65 && val <= 90) {
        turn = true;
    } else {
        turn = false;
    }
    if (oper == '+') {        
        if (chessBoard->board[row][col] == nullptr) {
            chessBoard->board[row][col] = chessBoard->createPiece(row,col,type,turn,false);
        } else {
            chessBoard->removePieceFromVector(row,col);
            delete chessBoard->board[row][col];
            chessBoard->board[row][col] = nullptr;
            updateGraphics(row, col);
            chessBoard->board[row][col] = chessBoard->createPiece(row,col,type,turn,false);
            chessBoard->board[row][col]->setPosition(make_tuple(row, col));
        }
        drawPiece(row,col);
        if (turn == true) {  
            chessBoard->setWhitePieces(chessBoard->board[row][col]);
            if (type == 'K') chessBoard->setWhiteKing(chessBoard->board[row][col]);
        } else {
            chessBoard->setBlackPieces(chessBoard->board[row][col]);
            if (type == 'k') chessBoard->setBlackKing(chessBoard->board[row][col]);
        }
//         bool color = chessBoard->board[row][col]->getColor();
//  //cout << "color: " << color << endl;
//         vector<ChessPiece *> friendlyPieces;
//         if (color != 0) {
//             friendlyPieces = chessBoard->getWhitePieces();
//             chessBoard->setWhiteKing(nullptr);
//         } else { 
//             friendlyPieces = chessBoard->getBlackPieces();
//             chessBoard->setBlackKing(nullptr);
//         }
//         for (auto p : friendlyPieces) {
//             if (p->getType() == 'K' && color != 0) {
//                 chessBoard->setWhiteKing(p);
//             } else if (p->getType() == 'K' && color == 0) {
//                 chessBoard->setBlackKing(p);
//             }
//         }
    } else if (oper == '-') {
        if (chessBoard->board[row][col] != nullptr) {
            chessBoard->removePieceFromVector(row,col);
            bool color = chessBoard->board[row][col]->getColor();
// cout << "color: " << color << endl;
            vector<ChessPiece *> friendlyPieces;
            if (color != 0) {
                friendlyPieces = chessBoard->getWhitePieces();
                chessBoard->setWhiteKing(nullptr);
            } else { 
                friendlyPieces = chessBoard->getBlackPieces();
                chessBoard->setBlackKing(nullptr);
            }
            for (auto p : friendlyPieces) {
                if (p->getType() == 'K' && color != 0) {
                    chessBoard->setWhiteKing(p);
                } else if (p->getType() == 'K' && color == 0) {
                    chessBoard->setBlackKing(p);
                }
            }
            delete chessBoard->board[row][col];
            chessBoard->board[row][col] = nullptr;
            updateGraphics(row, col);
        }
    }
    
    chessBoard->printText();
}

bool Game::validateConfig() {
    int whiteKings = 0;
    int blackKings = 0;
    
    King * blackKing = dynamic_cast<King *>(chessBoard->getBlackKing());
    King * whiteKing = dynamic_cast<King *>(chessBoard->getWhiteKing());
    if (blackKing != nullptr) blackKing->uncheckKing();
    if (whiteKing != nullptr) whiteKing->uncheckKing();
  
// cout << "1.0" << endl;
// cout << "White King: " << chessBoard->getWhiteKing() << " Black King: " << chessBoard->getBlackKing() << endl;

    for (auto p : chessBoard->getWhitePieces()) {
        if (p == nullptr) continue;
        if (p->getType() == 'K' && p->getColor() != 0) ++whiteKings;

        if (whiteKings > 1) {
            cout << "Too many white kings." << endl;
            return 0;
        }
        if (p->getType() == 'P' && (get<0>(p->getPosition()) == 0 || get<0>(p->getPosition()) == 7)) {
            cout << "Pawns in top or bottom row, please remove them" << endl;
            return 0;
        }
        p->setPossibleMoves(chessBoard);
    }
//cout << "2.0" << endl;
    for (auto p : chessBoard->getBlackPieces()) {
        if (p == nullptr) continue;
        if (p->getType() == 'K' && p->getColor() == 0) ++blackKings;

        if (blackKings > 1) {
            cout << "Too many black kings." << endl;
            return 0;
        }
        if (p->getType() == 'P' && (get<0>(p->getPosition()) == 0 || get<0>(p->getPosition()) == 7)) {
            cout << "Pawns in top or bottom row, please remove them" << endl;
            return 0;
        }
        p->setPossibleMoves(chessBoard);
    }

    if (whiteKings == 0) {
        cout << "No white king on board" << endl;
        return 0;
    } else if ( blackKings == 0) {
        cout << "No black king on board" << endl;
        return 0;
    }
// cout << "3.0" << endl;
// cout << "White King: " << chessBoard->getWhiteKing() << " Black King: " << chessBoard->getBlackKing() << endl;
// cout << "White Check: " << chessBoard->getWhiteCheck() << endl;
// cout << "Black Check: " << chessBoard->getBlackCheck() << endl;
    if (chessBoard->getWhiteCheck()) {
        cout << "White king in check" << endl;
        return 0;
    } else if (chessBoard->getBlackCheck()) {
        cout << "Black king in check" << endl;
        return 0;
    }

    return 1;
}

int Game::makeMove(tuple<int, int> initial, tuple<int,int> dest, bool compPlayer) {
    int row_from = get<0>(initial);
    int col_from = get<1>(initial);
    //========================================
    int row_to = get<0>(dest);
    int col_to = get<1>(dest);
    ChessPiece *temp = chessBoard->board[row_from][col_from];
    ChessPiece *destination = chessBoard->board[row_to][col_to];
    if (!(row_from >= 0 && row_from <= 7 &&
          row_to   >= 0 && row_to   <= 7 &&
          col_from >= 0 && col_from <= 7 &&
          col_to   >= 0 && col_to   <= 7)) {
        return -3;
    }

    // we need to validate the move, to make sure its one of our possible moves
    // if it is then we go with the following
    
    bool isValid = false;
    if (temp == nullptr) {
        return -1; // invalid move
    }
    temp->setPossibleMoves(chessBoard);
    temp->setLegalMoves();


    
    for (auto p : temp->getLegalMoves()) {
        if (initial == p.getInitialPosition() && dest == p.getFinalPosition()) {
            isValid = true;
            break;
        } 
    }
    if (isValid) {
        
        if (temp == nullptr) {
            return -1; // invalid move
        }
        
        char c;

        if (compPlayer && !cin.eof()) {
            c = temp->getColor() ? 'Q' : 'q';
        } else if (temp->getType() == 'P') {
            if ((temp->getColor() && row_to == 7) ||
                (!temp->getColor() && row_to == 0)) {
                    cin >> c;
                }
                if (c == 'r' || c == 'R') {
                    c = temp->getColor() ? 'R' : 'r';
                } else if (c == 'N' || c == 'n') {
                    c = temp->getColor() ? 'N' : 'n';
                } else if (c == 'B' || c == 'b') {
                    c = temp->getColor() ? 'B' : 'b';
                } else {
                    c = temp->getColor() ? 'Q' : 'q';
                }
        }

        chessBoard->makeMove(make_tuple(row_from, col_from), make_tuple(row_to, col_to));

        //empty dest
        if (destination == nullptr) {
            if (temp->getType() == 'P' && abs(row_to - row_from) == 1 && abs(col_to - col_from) == 1) {
                int colorFactor = temp->getColor() ? -1 : 1;
                updateGraphics(row_to + colorFactor,col_to);
                drawPiece(row_to,col_to);
            }

            destination = chessBoard->board[row_to][col_to];
            //Castling implementation
            if (temp->getType() == 'K') {
                King *king;
                if (temp->getColor()) {
                    king = dynamic_cast<King *>(chessBoard->getWhiteKing());
                } else {
                    king = dynamic_cast<King *>(chessBoard->getBlackKing());
                }
                if (king->getKingSideCastle() && col_to > col_from) {
                    updateGraphics(row_from,col_from + 3);
                    drawPiece(row_to,col_to - 1);  
                } else if (king->getQueenSideCastle() && col_to < col_from) {;
                    updateGraphics(row_from,col_from - 4);
                    drawPiece(row_to,col_to + 1);
                }   
            }
            updateGraphics(row_from,col_from);
            drawPiece(row_to,col_to);   
        } else if (destination != nullptr) {
            updateGraphics(row_to, col_to);
            updateGraphics(row_from,col_from);
            drawPiece(row_to,col_to);
        }

        if (temp->getType() == 'P') {
            if ((temp->getColor() && row_to == 7) || (!temp->getColor() && row_to == 0)) {//white
                chessBoard->removePieceFromVector(row_to,col_to);
                chessBoard->board[row_to][col_to] = chessBoard->createPiece(row_to,col_to,c,temp->getColor(), true);
                if (temp->getColor()) {
                    chessBoard->setWhitePieces(chessBoard->board[row_to][col_to]);
                } else {
                    chessBoard->setBlackPieces(chessBoard->board[row_to][col_to]);
                }

                delete temp;
                updateGraphics(row_to,col_to);
                drawPiece(row_to,col_to);
            }
        }
        chessBoard->printText(); 
    } else {
        return -2;
    }
    //update list of pieces for either white or black
    return 0;
}

int Game::gameStatus(bool color) {
    vector<ChessPiece *> friendlyPieces = !color ? chessBoard->getWhitePieces() : chessBoard->getBlackPieces();
    vector<ChessPiece *> enemyPieces = color ? chessBoard->getWhitePieces() : chessBoard->getBlackPieces();

    bool checkMatable = false;

    int enemyKnightCount = 0;
    int friendlyKnightCount = 0;

    int enemyBishopCount = 0;
    int friendlyBishopCount = 0;


    for (auto p: friendlyPieces) {
        if (p == nullptr) continue;

        
        if (p->getType() == 'R' || p->getType() == 'Q' || p->getType() == 'P') {
            checkMatable = true;
            break;
        }

        if (p->getType() == 'N') friendlyKnightCount++;
        if (p->getType() == 'B') friendlyBishopCount++;
    }

    for (auto p: enemyPieces) {
        if (p == nullptr) continue;

        if (p->getType() == 'R' || p->getType() == 'Q' || p->getType() == 'P') {
            checkMatable = true;
            break;
        }

        if (p->getType() == 'N') enemyKnightCount++;
        if (p->getType() == 'B') enemyBishopCount++;
    }

    if (!checkMatable) {
        if ((enemyKnightCount <= 1 && friendlyKnightCount <= 1 && (enemyBishopCount + friendlyBishopCount) == 0) ||
            (enemyBishopCount <= 1 && friendlyBishopCount <= 1 && (enemyKnightCount + friendlyKnightCount) == 0)) {
                return 2;
            }

    }

    King * blackKing = dynamic_cast<King *>(chessBoard->getBlackKing());
    King * whiteKing = dynamic_cast<King *>(chessBoard->getWhiteKing());

    blackKing->uncheckKing();
    whiteKing->uncheckKing();

    for (auto p : friendlyPieces) {
        if (p == nullptr) continue;
        p->setPossibleMoves(chessBoard);
    }
    bool hasMove = false;
    for (auto p : enemyPieces) {
        if (p == nullptr) continue;
        p->setPossibleMoves(chessBoard);
        if (!hasMove) {
            p->setLegalMoves();
            if (p->getLegalMoves().size() != 0) { 
                hasMove = true;
            }
        }
    }
    if (hasMove) return 0;
    
    if (chessBoard->getBlackCheck()) {
        return 1;
    } else if (chessBoard->getWhiteCheck()) {
        return 1;
    }

    return 2;
}

void Game::printGraphics() {
    for (int i = 7; i >= 0; i--) {
        w.fillRectangle(0,50*(7-i), 50,50, Xwindow::White);
        w.drawString(20, 50*(7-i)+20, to_string(i+1));
        for (int j = 0; j < 8; j++) {
            if ((i+j)% 2 == 0) {
                string s = "";
                if (chessBoard->board[i][j] != nullptr) {
                    s += chessBoard->board[i][j]->getType();
                    if (chessBoard->board[i][j]->getColor() == false) {
                        s[0] = tolower(s[0]);
                    }
                }
                w.fillRectangle(50*(j+1),50*(7-i),50,50, Xwindow::Red);
                w.drawString(50*(j+1)+20, 50*(7-i)+20, s);
            } else {
                string s = "";
                if (chessBoard->board[i][j] != nullptr) {
                    s += chessBoard->board[i][j]->getType();
                    if (chessBoard->board[i][j] != nullptr && chessBoard->board[i][j]->getColor() == false) {
                        s[0] = tolower(s[0]);
                    }
                }
                w.fillRectangle(50*(j+1),50*(7-i),50,50, Xwindow::White);
                w.drawString(50*(j+1)+20, 50*(7-i)+20, s);
            }
        }
    }
    w.drawString(50*(1)+20, 50*(8)+20, "a");
    w.drawString(50*(2)+20, 50*(8)+20, "b");
    w.drawString(50*(3)+20, 50*(8)+20, "c");
    w.drawString(50*(4)+20, 50*(8)+20, "d");
    w.drawString(50*(5)+20, 50*(8)+20, "e");
    w.drawString(50*(6)+20, 50*(8)+20, "f");
    w.drawString(50*(7)+20, 50*(8)+20, "g");
    w.drawString(50*(8)+20, 50*(8)+20, "h");

}

void Game::updateGraphics(int row, int col) {
    if ((row+col)% 2 == 0) {
        w.fillRectangle(50*(col+1),50*(7-row),50,50, Xwindow::Red);
    } else {
        w.fillRectangle(50*(col+1),50*(7-row),50,50, Xwindow::White);
    }
}

void Game::drawPiece(int row, int col) {
    string s = "";
    if (chessBoard->board[row][col] != nullptr) {
        s += chessBoard->board[row][col]->getType();
        if (chessBoard->board[row][col]->getColor() == false) {
            s[0] = tolower(s[0]);
        }
    }
    w.drawString(50*(col+1)+20, 50*(7-row)+20, s);        
}